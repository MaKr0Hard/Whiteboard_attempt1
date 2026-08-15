#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{// I'll have to the address i use because qtcreator doesn't let you commit with whatever address and if a company named really goes into emails, i'm cooked
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return QApplication::exec();
}
