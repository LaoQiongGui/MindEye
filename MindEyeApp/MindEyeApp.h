#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MindEyeApp.h"

class MindEyeApp : public QMainWindow
{
    Q_OBJECT

public:
    MindEyeApp(QWidget *parent = nullptr);
    ~MindEyeApp();

private:
    Ui::MindEyeAppClass ui;
};
