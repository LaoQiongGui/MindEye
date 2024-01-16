#pragma once

#include <QtWidgets/QMainWindow>
#include <qabstractbutton.h>
#include "ui_MindEyeApp.h"

class MindEyeApp : public QMainWindow
{
    Q_OBJECT

public:
    MindEyeApp(QWidget *parent = nullptr);
    ~MindEyeApp();

private slots:
    void onIsaacBeginBtnClicked();
    void onIsaacTerminateBtnClicked();

private:
    Ui::MindEyeAppClass ui;
};
