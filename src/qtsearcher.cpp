#include "qtsearcher.h"


#include <QApplication>

#include "statuswindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow window;
    window.show();
    return app.exec();
}