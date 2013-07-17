#include "movielibrary.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    movieLibrary *w = new movieLibrary();

    w->show();

    return a.exec();
}
