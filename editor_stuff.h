#ifndef EDITOR_STUFF_H
#define EDITOR_STUFF_H

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
    current_dw->back();
}




void Editor::on_actionRestorer_triggered()
{
    current_dw->forward();
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
    dw->setPenColour(violet); //TODO : all this redundant crap needs its own header
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

QColorDialog *col_dialog;

void Editor::on_custom_color_selected(const QColor &color) {
    dw->setPenColour(color);
    //delete col_dialog; //TODO: check if causes memleak
}

void Editor::on_actionPerso_triggered() {
    col_dialog = new QColorDialog();
    connect(col_dialog, &QColorDialog::colorSelected, this, &Editor::on_custom_color_selected);
    col_dialog->show();
}

void Editor::on_tab_changed(int index) {
    std::puts("Tab changed");
    QScrollArea* sa = qobject_cast<QScrollArea*>(tabwidget->currentWidget());
    QWidget* widget = sa->widget();
    QVBoxLayout* lay = qobject_cast<QVBoxLayout *>(widget->layout());
    QLayoutItem* item = lay->itemAt(0);
    current_dw = qobject_cast<DrawingWidget *>(item->widget());
}

#endif // EDITOR_STUFF_H
