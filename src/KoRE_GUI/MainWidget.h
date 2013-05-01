#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include "ui_MainWidget.h"

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent = 0);
    ~MainWidget();

private:
    Ui::MainWidget ui;
};

#endif // MAINWIDGET_H
