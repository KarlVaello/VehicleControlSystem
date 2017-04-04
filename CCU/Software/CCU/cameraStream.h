#ifndef CAMERASTREAM_H
#define CAMERASTREAM_H


#include <QCamera>
#include <QCameraInfo>
#include <QCameraViewFinder>
#include <QCameraImageCapture>
#include "cameraCaptureBuffer.h"
#include <QAbstractVideoSurface>
#include <QDebug>
class CameraStream : public QWidget
{
    Q_OBJECT

public:

    QCamera *camera;
    QCameraViewfinder *viewfinder;
    QCameraImageCapture *imageCapture;
    CaptureBuffer* captureBuffer;

    CameraStream(QString cameraName);
    ~CameraStream();

    void  start();

    void  stop();
    void  show();

    QString cameraName;

};

#endif // CAMERASTREAM_H
