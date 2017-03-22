#ifndef CLUSTER_H
#define CLUSTER_H

#include <QWidget>
#include <QPixmap>
#include <QtSerialPort/QSerialPort>
#include <QtSvg/QtSvg>
#include <QtSvg/QSvgRenderer>
#include <notificationInfo.h>
#include <notificationManager.h>

class Cluster : public QWidget
{
    Q_OBJECT

public:
    Cluster(QWidget *parent = 0);
    float currentSpeed = 0.0f;
    float lastSpeed = 0.0f;
    int currentLabelSpeed = 0;
    int rS = 0;
    bool a = true;
    bool resourcesLoaded = false;


private slots:
    void readData();

private:
    QSerialPort *serial;
    QPainter *painterOutline;
    QPainter *painterSpeedPointer;
    QPainter *speedLabel;
    QPainter *notTitleLabel;
    QPainter *notBanner;

    QSvgRenderer *outlineRenderer;
    QSvgRenderer *speedPointerRenderer;
    QSvgRenderer *notificationBannerRenderer;
    QByteArray serialData;
    QString serialBuffer;


    NotificationManager *ntManager;
    NotificationInfo *nI;


protected:
    void paintEvent(QPaintEvent *event) override;
};

#endif // CLUSTER_H
