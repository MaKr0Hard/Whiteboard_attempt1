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

QTabWidget *tabwidget;
std::string snbr;
std::string pnbr;
std::vector <DrawingWidget*> dws;
QColor orange(255, 125, 0);
QColor violet(110, 0, 185);
QSlider *slider;

QIcon makeAnIconFromJustAColour(QColor colour) {
    QPixmap pixmap(22, 22);
    pixmap.fill(colour);
    QIcon icon(pixmap);
    return icon;
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

void Editor::on_action_cran_de_bienvenue_triggered()
{
    MainWindow *welcome = new MainWindow();
    welcome->show();
    this->close();

}




void Editor::on_actionQuitter_triggered()
{
    this->close();
}


void Editor::on_actionFermer_fen_tre_triggered()
{
    this->close();
}


void Editor::on_actionFermer_onglet_triggered()
{


    int index = tabwidget->currentIndex();
    tabwidget->removeTab(index);

}


void Editor::on_actionNouvel_onglet_triggered()
{
    QWidget *widget = new QWidget();
    QVBoxLayout *vbox = new QVBoxLayout();
    MainWindow *welcome = new MainWindow();
    vbox->addWidget(welcome);
    widget->setLayout(vbox);
    tabwidget->addTab(widget, "Bienvenue");
}


void Editor::on_actionNouveau_triggered()
{
    newfile();
}


/*void Editor::on_actionGet_Stroke_Nbr_triggered()
{
    QWidget *widget = new QWidget();
    QVBoxLayout *vbox = new QVBoxLayout();
    QLabel *label = new QLabel();
    QLabel *label2 = new QLabel();

    pnbr = "pnbr : " + std::to_string(*aa);


    snbr = "snbr : " + std::to_string(*bb);
    QString pnbr_s = QString::fromStdString(pnbr);
    QString snbr_s = QString::fromStdString(snbr);
    label->setText(pnbr_s);
    label2->setText(snbr_s);
    vbox->addWidget(label);
    vbox->addWidget(label2);
    widget->setLayout(vbox);
    tabwidget->addTab(widget, "Whatever");
}*/


void Editor::on_actionRedraw_all_triggered()
{
    dw->redraw_all();
}


void Editor::on_actionAnnuler_triggered()
{
    dw->back();
}




void Editor::on_actionRestorer_triggered()
{
    dw->forward();
}


void Editor::on_actionRouge_triggered()
{
    dw->setPenColour(Qt::red);
}


void Editor::on_actionVert_triggered()
{
    dw->setPenColour(Qt::green);
}



void Editor::on_actionBleu_triggered()
{
    dw->setPenColour(Qt::blue);
}


void Editor::on_actionNoir_triggered()
{
    dw->setPenColour(Qt::black);
}


void Editor::on_actionOrange_triggered()
{
    dw->setPenColour(orange);
}


void Editor::on_actionJaune_triggered()
{
    dw->setPenColour(Qt::yellow);
}


void Editor::on_actionViolet_triggered()
{
    dw->setPenColour(violet);
}


void Editor::on_actionBlanc_triggered()
{
    dw->setPenColour(Qt::white);
}


void Editor::on_actionBleu_clair_triggered()
{
    dw->setPenColour(Qt::cyan);
}


void Editor::on_actionGris_triggered()
{
    dw->setPenColour(Qt::gray);
}

void Editor::on_slider_pressed() {
    dw->setPenSize(slider->sliderPosition());
}

void Editor::on_slider_moved(int pos){
    dw->setPenSize(pos);
}