#include "MindEyeApp.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication application(argc, argv);
    MindEyeApp mindEyeApp;
    mindEyeApp.show();
    return application.exec();
}
