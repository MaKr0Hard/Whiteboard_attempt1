#ifndef CUSTOM_COLOUR_ACTION_H
#define CUSTOM_COLOUR_ACTION_H

#include <QAction>
#include <QObject>
#include <QWidget>

class Custom_colour_action : public QAction
{
    Q_OBJECT
public:
    explicit Custom_colour_action(QObject *parent = nullptr);
    QColor colour;
};

#endif // CUSTOM_COLOUR_ACTION_H
