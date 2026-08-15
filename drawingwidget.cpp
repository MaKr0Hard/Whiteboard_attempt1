// DrawingWidget.cpp
#include "drawingwidget.h"
#include <QMouseEvent>
#include <QPainter>
#include <vector>
#include <iostream>
#include <unistd.h>
#include <chrono>
#include <thread>




//std::vector<Stroke> DrawingWidget::last_strokes;
//std::vector<std::vector<QPoint>>* last_strokes_ptr = &last_strokes;
void (*callback_ptr)();
QPen pen(Qt::black);
QColor colour_drawn_now;
int size_now;


void setpenconfig(QPen *pen, QPainter *p) { //Add a stroke parameter

    //pen->setWidth(6);
    pen->setCapStyle(Qt::RoundCap);
    pen->setJoinStyle(Qt::RoundJoin);
    p->setPen(*pen);

}



void DrawingWidget::ensureCanvas() {
    if (canvas.isNull() || canvas.size() != size()) {
        QPixmap newCanvas(size());
        newCanvas.fill(Qt::white);           // background
        if (!canvas.isNull()) {
            QPainter p(&newCanvas);
            p.drawPixmap(0, 0, canvas);      // keep old drawing
        }
        canvas = newCanvas;
    }
}

void DrawingWidget::recanvas() {
    QPixmap newCanvas(size());
    newCanvas.fill(Qt::white);           // background
    canvas = newCanvas;
}

void DrawingWidget::redraw_all() {
    auto start = std::chrono::steady_clock::now();
    recanvas();
    QPainter p(&canvas);
    p.setRenderHint(QPainter::Antialiasing, true);
    QPen pen(Qt::black);
    setpenconfig(&pen, &p);


    for (int i = 0; i < (last_strokes.size() - back_var); i++){
        if (last_strokes[i].points.size() > 1) {
            pen.setColor(last_strokes[i].colour); //TODO: PUT THEM ALL IN setpenconfig()
            pen.setWidth(last_strokes[i].size);
            p.setPen(pen);
            for (int j = 0; j < (last_strokes[i].points.size() - 1); j++){

                p.drawLine(last_strokes[i].points[j], last_strokes[i].points[j + 1]);

            }
        } else if (last_strokes[i].points.size() == 1) {
            pen.setColor(last_strokes[i].colour);
            pen.setWidth(last_strokes[i].size);
            p.setPen(pen);
            p.drawPoint(last_strokes[i].points[0]);
        } else printf("wtf\n");

    }
    update();
    // 2. Stop the timer
    auto end = std::chrono::steady_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    // 4. Print the result
    std::cout << "Elapsed time: " << duration << " milliseconds" << std::endl;
    //usleep(1000000);
}

void refresh_stuff () {
    if (callback_ptr != nullptr) { // you won't get me here segfault !
        callback_ptr();
    } else {
        printf("We were close from segfaulting... \n");
    }
}

DrawingWidget::DrawingWidget(QWidget *parent)
    : QWidget(parent)
{
    stroke_nbr = 0;
    point_nbr = 0;
    int back_var = 0;
}

void DrawingWidget::mousePressEvent(QMouseEvent *e) {
    if (e->button() == Qt::LeftButton) {

        /*if (back_var > 0) {
            //forward_enabled = false;
            for (int i = 0; i < (back_var); i++) {
                last_strokes.erase(last_strokes.end());
            }
            back_var = 0;
        }*/ //TODO : PLEASE FIX YOURSELF

        point_nbr = 0;
        ensureCanvas();
        drawing = true;
        lastPos = e->pos();

        // draw a dot immediately
        QPainter p(&canvas);
        p.setRenderHint(QPainter::Antialiasing, true);
        pen.setWidth(size_now);
        pen.setColor(colour_drawn_now);
        setpenconfig(&pen, &p);

        p.drawPoint(lastPos);
        last_strokes.push_back({});
        last_strokes[stroke_nbr].points.push_back(lastPos);
        last_strokes[stroke_nbr].colour = colour_drawn_now;
        last_strokes[stroke_nbr].size = size_now;
        point_nbr++;
        stroke_nbr++;


        std::cout << std::to_string(point_nbr) << " ";
        std::cout << std::to_string(stroke_nbr) << "\n";
        backward_enabled = true;
        refresh_stuff();
        update();
    }
}

void DrawingWidget::refreshCallbackEnabledStuff (void (*callback)()) {
    callback_ptr = callback;
}



void DrawingWidget::mouseMoveEvent(QMouseEvent *e) {
    if (!drawing) return;

    ensureCanvas();

    QPainter p(&canvas);
    p.setRenderHint(QPainter::Antialiasing, true);

    pen.setWidth(size_now);
    pen.setCapStyle(Qt::RoundCap);
    pen.setJoinStyle(Qt::RoundJoin);
    p.setPen(pen);

    QPoint cur = e->pos();
    p.drawLine(lastPos, cur);

    lastPos = cur;
    last_strokes[stroke_nbr - 1].points.push_back(lastPos);
    point_nbr++;
    update();
}



void DrawingWidget::back() {
    if (back_var != last_strokes.size()) {
    back_var++;
    redraw_all();
    }
    if (back_var == last_strokes.size()) {
        backward_enabled = false;
    }
}

void DrawingWidget::forward() {
    if (back_var != 0) {
    back_var--;
        redraw_all();
    }
    if (back_var == 0) {
        forward_enabled = true;
    }
}

void DrawingWidget::paintEvent(QPaintEvent *) {
    ensureCanvas();
    QPainter w(this);
    w.drawPixmap(0, 0, canvas);
}

int DrawingWidget::setPenColour(QColor colour) {

    colour_drawn_now = colour; // TODO: DO NOT LET A COLOUR BE SET WHILE DRAWING
    return 0;

}

int DrawingWidget::setPenSize(int size) {
    size_now = size;
    return 0;
}
