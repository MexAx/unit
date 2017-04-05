#include "formjedmjere.h"
#include <QApplication>
#include <QWidget>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FormJedmjere w;
    //w.setFocus();
    w.show();

    return a.exec();
}
