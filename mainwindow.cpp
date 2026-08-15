#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "editor.h"
#include <QPixmap>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    MainWindow::setCentralWidget(ui->verticalLayoutWidget);
    QPixmap home(":/mainwindow/go-home.png");
    ui->label_3->setPixmap(home);
    ui->label_3->setScaledContents(false);
    ui->label_3->setMaximumWidth(49);
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_3_clicked()
{
    this->close();
}


void MainWindow::on_pushButton_2_clicked()
{
    Editor *editor = new Editor();
    editor->show();
    editor->newfile();
    this->close();
}

