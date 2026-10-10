#ifndef QACTION_WITH_QACTION_CHILD_H
#define QACTION_WITH_QACTION_CHILD_H

#include <QAction>
#include <QObject>
#include <QWidget>
#include "custom_colour_action.h"

class QAction_with_QAction_child : public QAction
{
    Q_OBJECT
public:
    explicit QAction_with_QAction_child(QObject *parent = nullptr);
    Custom_colour_action *child_action; //TODO : Change the title to reflect better this
};

#endif // QACTION_WITH_QACTION_CHILD_H
