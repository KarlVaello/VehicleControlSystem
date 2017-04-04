#include "cameraStream.h"

#include <QCamera>
#include <QCameraInfo>
#include <QCameraViewFinder>
#include <QCameraImageCapture>
#include "cameraCaptureBuffer.h"
#include <QDebug>
#include <QAbstractVideoSurface>
#include <QDebug>
CameraStream::CameraStream( QString cmrNm)
{
    cameraName = cmrNm;

    qDebug() << "Cameras: " << QString::number(QCameraInfo::availableCameras().count()) ;

    QList<QCameraInfo> cameras = QCameraInfo::availableCameras();
    qDebug() << cameras;
    qDebug() << "Camera info device name" << cameras.at(0).deviceName();
    camera = new QCamera(cameras.at(0));

    qDebug() << camera;

    viewfinder = new QCameraViewfinder();
}

CameraStream::~CameraStream()
{

}

void CameraStream::start()
{
    camera->start();
}

void CameraStream::stop()
{
    camera->stop();
}

void CameraStream::show(){


    if (cameraName == "left"){
        viewfinder->setGeometry(30,600,300,200);
    }else{
        viewfinder->setGeometry(600,600,300,200);
    }


    //captureBuffer = new CaptureBuffer;
    //camera->setViewfinder(captureBuffer); bypass, no correct work

    camera->setViewfinder(viewfinder);
    viewfinder->show();

    camera->setCaptureMode(QCamera::CaptureStillImage);
    camera->start(); // to start the viewfinder


}
