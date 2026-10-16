#include "editor.h"
#include "ui_editor.h"
#include "mainwindow.h"
#include <QVBoxLayout>
#include "drawingwidget.h"
#include <QScrollArea>
#include <QLabel>
#include "drawingwidget.h"
#include <QToolBar>
#include <QSlider>
#include <QColorDialog>
#include <QAction>
#include <QPushButton>
#include "custom_colour_action.h"
#include "qaction_with_qaction_child.h"

QTabWidget *tabwidget;
std::string snbr;
std::string pnbr;
std::vector <DrawingWidget*> dws; //TODO : delete
DrawingWidget* current_dw;
QColor orange(255, 125, 0);
QColor violet(110, 0, 185);
QSlider *slider;

QIcon makeAnIconFromJustAColour(QColor colour) {
    QPixmap pixmap(22, 22);
    pixmap.fill(colour);
    QIcon icon(pixmap);
    return icon;
}


void Editor::init_set_colours() {
    ui->actionRouge->setIcon(makeAnIconFromJustAColour(Qt::red));
    ui->actionVert->setIcon(makeAnIconFromJustAColour(Qt::green));
    ui->actionBleu->setIcon(makeAnIconFromJustAColour(Qt::blue));
    ui->actionNoir->setIcon(makeAnIconFromJustAColour(Qt::black));
    ui->actionOrange->setIcon(makeAnIconFromJustAColour(orange));
    ui->actionJaune->setIcon(makeAnIconFromJustAColour(Qt::yellow));

    ui->actionBlanc->setIcon(makeAnIconFromJustAColour(Qt::white));
    ui->actionViolet->setIcon(makeAnIconFromJustAColour(violet));
    ui->actionBleu_clair->setIcon(makeAnIconFromJustAColour(Qt::cyan));
    ui->actionGris->setIcon(makeAnIconFromJustAColour(Qt::gray));
}

QAction_with_QAction_child* action_of_colour_changed;

void Editor::on_custom_color_selected2(const QColor &colour) {
    action_of_colour_changed->child_action->colour = colour;
    action_of_colour_changed->child_action->setIcon(makeAnIconFromJustAColour(colour));
    action_of_colour_changed->setIcon(makeAnIconFromJustAColour(colour));
    on_custom_color_selected(colour);
}

QColorDialog *custom_colour_dialog;

void Editor::change_colour_from_action_w_show_dlg() {
    action_of_colour_changed = qobject_cast<QAction_with_QAction_child*>(sender());
    custom_colour_dialog = new QColorDialog();
    connect(custom_colour_dialog, &QColorDialog::colorSelected, this, &Editor::on_custom_color_selected2);
    custom_colour_dialog->show();
}

void Editor::change_colour_from_action() {
    QAction* action = qobject_cast<QAction*>(sender());
    if (action) {
        QColor colour = QColor(action->data().toLongLong()); //F*ck just use an addwidget on the toolbar
        on_custom_color_selected(colour);
    }
}

void Editor::change_colour_from_custom_colour_action() { //TODO : Maker a menu where the colour can be changed by accessing the colour member
    Custom_colour_action* action = qobject_cast<Custom_colour_action*>(sender());
    if (action) {
        QColor colour = action->colour;
        on_custom_color_selected(colour);
    }
}

Editor::Editor(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Editor)
{
    ui->setupUi(this);
    tabwidget = new QTabWidget();
    tabwidget->setTabsClosable(true);
    tabwidget->setMovable(true);
    Editor::setCentralWidget(tabwidget);
    /*aa = (int *)malloc(sizeof(int));
    bb = (int *)malloc(sizeof(int));*/
    slider = new QSlider(Qt::Horizontal);
    slider->setRange(0, 100);
    slider->setMaximumWidth(200);
    connect(slider, &QSlider::sliderMoved, this, &Editor::on_slider_moved);
    connect(slider, &QSlider::sliderPressed, this, &Editor::on_slider_pressed);
    slider->setSliderPosition(6);
    ui->toolBar_4->addWidget(slider);

    QToolBar *toolbar_5 = new QToolBar();
    toolbar_5->setWindowTitle("Couleurs perso.");
    QToolBar *toolbar_6 = new QToolBar();
    toolbar_6->setWindowTitle("Couleurs perso.");


    QList <QAction*> custom_colrs;
    for (int i = 0; i < 10; i++) {
        QAction *action = new QAction();
        QColor *colour = new QColor();
        action->setData(colour->rgb());
        action->setText(QString::fromStdString(std::to_string(i)));
        connect(action, &QAction::triggered, this, &Editor::change_colour_from_action);
        custom_colrs.append(action);
    }

    QList <Custom_colour_action*> better_custom_colrs;
    for (int i = 0; i < 10; i++) {
        Custom_colour_action *action = new Custom_colour_action();
        QColor *colour = new QColor();
        long random_colour = rand();
        colour->setRgb(random_colour);
        action->setData(colour->rgb());
        action->colour = *colour;
        action->setIcon(makeAnIconFromJustAColour(*colour));
        action->setText(QString::fromStdString(std::to_string(i)));
        connect(action, &QAction::triggered, this, &Editor::change_colour_from_custom_colour_action);
        better_custom_colrs.append(action);
        toolbar_6->addAction(better_custom_colrs[i]);
    }
    ui->menuCouleurs->addSeparator();

    QList <QAction_with_QAction_child*> change_custom_colrs;
    for (int i = 0; i < 10; i++) {
        QAction_with_QAction_child *action = new QAction_with_QAction_child();
        action->setIcon(makeAnIconFromJustAColour(better_custom_colrs[i]->colour));
        action->child_action = better_custom_colrs[i];
        action->setText(QString::fromStdString(std::to_string(i)));
        connect(action, &QAction::triggered, this, &Editor::change_colour_from_action_w_show_dlg);
        change_custom_colrs.append(action);
        ui->menuCouleurs->addAction(change_custom_colrs[i]);
    }

    toolbar_5->addActions(custom_colrs);
    //TODO : delete everything related to this :
    //this->addToolBar(toolbar_5);

    this->addToolBar(toolbar_6);
    connect(tabwidget, &QTabWidget::currentChanged, this, &Editor::on_tab_changed);
    current_dw = dw; //SEGFAULT ?
}

void Editor::setSomeBackForthBtns (bool btn1, bool btn2) {
    //why did i do this
    ui->actionAnnuler->setEnabled(btn1);

    ui->actionRestorer->setEnabled(btn2);
}


/*void Editor::refresh_btns() { // TODo ToDO TODO TODO TODo ToDO TODOOOOOOOO TOODODODODO
    Editor::setSome
}*/


void Editor::newfile() {
    init_set_colours();



    QScrollArea *sa = new QScrollArea();
    QWidget *widget = new QWidget();
    //widget->setMaximumSize(60, 60);
    widget->setMinimumSize(2100, 2790);
    QVBoxLayout *widget_layout = new QVBoxLayout();
    dw = new DrawingWidget();
    if (slider != nullptr) dw->setPenSize(slider->sliderPosition());
    setSomeBackForthBtns(true, true);
    //dw->refreshCallbackEnabledStuff(Editor::refresh_btns);
    widget_layout->addWidget(dw);
    widget->setLayout(widget_layout);
    sa->setWidget(widget);
    tabwidget->addTab(sa, "Sans Titre");
    //tabwidget->addTab(widget, "Sans Titre");
    //dw->setPenColour(Qt::green);



}
Editor::~Editor()
{
    delete ui;
}

#include "editor_stuff.h" //Everything can be found in editor_stuff.h