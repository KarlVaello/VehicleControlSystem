

#include <QApplication>

#include "cluster.h"
#include <QtSvg/QtSvg>
#include <QtSvg/QSvgRenderer>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Cluster cluster;
    cluster.show();
    return app.exec();
}
