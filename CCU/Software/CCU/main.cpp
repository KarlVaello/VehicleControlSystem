

#include <QApplication>

#include "cluster.h"
#include <QtSvg/QtSvg>
#include <QtSvg/QSvgRenderer>
#include <cameraStream.h>


#include <unitCommunication.h>

#include <infotainment.h>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Infotainment *infotainment = new Infotainment();

    UnitCommunication *centralControlUnit_COM = new UnitCommunication(infotainment);
    centralControlUnit_COM->startCom(infotainment);
    Cluster *cluster = new Cluster(0,centralControlUnit_COM,infotainment);


    //CameraStream *leftCamera = new CameraStream("left");
    //leftCamera->show();

    //CameraStream *rightCamera = new CameraStream("right");
    //rightCamera->show();


    cluster->show();
    return app.exec();
}
