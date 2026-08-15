#ifndef DRAWINGWIDGET_H
#define DRAWINGWIDGET_H


#include <QWidget>
#include <QPixmap>
#include <QPoint>

typedef struct {
    std::vector<QPoint> points;
    QColor colour;
    int size;
} Stroke;

class DrawingWidget : public QWidget {
    Q_OBJECT
public:
    explicit DrawingWidget(QWidget *parent = nullptr);
    int point_nbr = 0;
    int stroke_nbr = 0;
    void redraw_all();
    void recanvas();
    void back();
    void forward();
    bool forward_enabled = false;
    bool backward_enabled = false;
    void refreshCallbackEnabledStuff (void (*callback)());
    int setPenColour(QColor colour);
    int setPenSize(int size);

protected:
    void mousePressEvent(QMouseEvent *e) override;
    void mouseMoveEvent(QMouseEvent *e) override;
    void paintEvent(QPaintEvent *e) override;

private:
    std::vector <Stroke> last_strokes;
    QPixmap canvas;
    bool drawing = false;
    QPoint lastPos;
    int back_var = 0;
    void ensureCanvas();
    //void setpenconfig(QPen *pen, QPainter *p);

};


#endif // DRAWINGWIDGET_H
