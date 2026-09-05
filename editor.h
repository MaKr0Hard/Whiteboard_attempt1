#ifndef EDITOR_H
#define EDITOR_H

#include <QMainWindow>
#include "drawingwidget.h"


namespace Ui {
class Editor;
}

class Editor : public QMainWindow
{
    Q_OBJECT

public:

    explicit Editor(QWidget *parent = nullptr);
    ~Editor();
    QTabWidget *tabwidget;
    void newfile();
    int* aa = 0;
    int* bb = 0;
    std::string snbr;
    std::string pnbr;
    DrawingWidget *dw;
    //void refresh_btns();

private slots:
    void on_action_cran_de_bienvenue_triggered();


    void on_actionQuitter_triggered();

    void on_actionFermer_fen_tre_triggered();

    void on_actionFermer_onglet_triggered();

    void on_actionNouvel_onglet_triggered();

    void on_actionNouveau_triggered();

    //void on_actionGet_Stroke_Nbr_triggered();



    void on_actionRedraw_all_triggered();

    void on_actionAnnuler_triggered();

    void on_actionRestorer_triggered();

    void on_actionRouge_triggered();

    void on_actionVert_triggered();

    void on_actionBleu_triggered();

    void on_actionNoir_triggered();

    void on_actionOrange_triggered();

    void on_actionJaune_triggered();

    void on_actionViolet_triggered();

    void on_actionBlanc_triggered();

    void on_actionBleu_clair_triggered();

    void on_actionGris_triggered();

    void on_slider_moved(int pos);

    void on_slider_pressed();

    void on_actionPerso_triggered();

    void on_custom_color_selected(const QColor &color);
private:
    Ui::Editor *ui;
    void setSomeBackForthBtns (bool btn1, bool btn2);

};

#endif // EDITOR_H
