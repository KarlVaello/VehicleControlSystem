#ifndef CLUSTER_H
#define CLUSTER_H

#include <QWidget>
#include <QPixmap>
#include <QtSerialPort/QSerialPort>
#include <QtSvg/QtSvg>
#include <QtSvg/QSvgRenderer>
#include <notificationInfo.h>
#include <notificationManager.h>
#include <notificationWidgetManager.h>
#include <QCamera>
#include <QCameraInfo>
#include <QCameraViewFinder>
#include <unitCommunication.h>

class Cluster : public QWidget
{
    Q_OBJECT

public:
    Cluster(QWidget *parent = 0, UnitCommunication *ccu_COM = 0, Infotainment *infota = 0);
    float currentSpeed = 280.0f;
    float lastSpeed = 280.0f;
    int currentLabelSpeed = 0;
    int rS = 0;
    bool a = true;
    bool resourcesLoaded = false;
    bool isInitClusterAnim_outline = false;
    bool isInitClusterAnim_speedPointer = false;
    float outlineOpacity = 0.0f;
    float postOpacity = 0.0f;

private:

    QTime *time;
    QTimer *timer;

    int speedTry;

    UnitCommunication *centralControlUnit_COM;
    Infotainment *infotaiment;

    /*QPainter *painterOutline;
    QPainter *backGroundRect;
    QPainter *painterSpeedPointer;
    QPainter *speedLabel;
    QPainter *notTitleLabel;
    QPainter *notBanner;
    QPainter *painter_timeLabel;*/


   /* QPainter *painterOutline = new QPainter (this);
    QPainter *backGroundRect = new QPainter (this);
    QPainter *painterSpeedPointer = new QPainter (this);
    QPainter *speedLabel = new QPainter (this);
    QPainter *notTitleLabel = new QPainter (this);
    QPainter *notBanner = new QPainter (this);
    QPainter *painter_timeLabel = new QPainter (this);
*/

    QSvgRenderer *outlineRenderer;
    QSvgRenderer *speedPointerRenderer;



    NotificationManager *ntManager;
    NotificationWidgetManager *ntWidgetManager;
    NotificationInfo *nI;

    QCamera *camera;
    QCameraViewfinder *viewfinder;
protected:
    void paintEvent(QPaintEvent *event) override;
};

#endif // CLUSTER_H
