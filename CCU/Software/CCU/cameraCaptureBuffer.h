#ifndef CAMERACAPTUREBUFFER_H
#define CAMERACAPTUREBUFFER_H


#include <QAbstractVideoSurface>
#include <QDebug>

class CaptureBuffer : public QAbstractVideoSurface
{
    Q_OBJECT

public:
    int i = 0;
    //CaptureBuffer();
    //~CaptureBuffer();

    QList<QVideoFrame::PixelFormat> supportedPixelFormats(
            QAbstractVideoBuffer::HandleType handleType =
            QAbstractVideoBuffer::NoHandle) const
    {
        QList<QVideoFrame::PixelFormat> formats;
        formats << QVideoFrame::Format_ARGB32;
        formats << QVideoFrame::Format_ARGB32_Premultiplied;
        formats << QVideoFrame::Format_RGB32;
        formats << QVideoFrame::Format_RGB24;
        formats << QVideoFrame::Format_RGB565;
        formats << QVideoFrame::Format_RGB555;
        formats << QVideoFrame::Format_ARGB8565_Premultiplied;
        formats << QVideoFrame::Format_BGRA32;
        formats << QVideoFrame::Format_BGRA32_Premultiplied;
        formats << QVideoFrame::Format_BGR32;
        formats << QVideoFrame::Format_BGR24;
        formats << QVideoFrame::Format_BGR565;
        formats << QVideoFrame::Format_BGR555;
        formats << QVideoFrame::Format_BGRA5658_Premultiplied;
        formats << QVideoFrame::Format_AYUV444;
        formats << QVideoFrame::Format_AYUV444_Premultiplied;
        formats << QVideoFrame::Format_YUV444;
        formats << QVideoFrame::Format_YUV420P;
        formats << QVideoFrame::Format_YV12;
        formats << QVideoFrame::Format_UYVY;
        formats << QVideoFrame::Format_YUYV;
        formats << QVideoFrame::Format_NV12;
        formats << QVideoFrame::Format_NV21;
        formats << QVideoFrame::Format_IMC1;
        formats << QVideoFrame::Format_IMC2;
        formats << QVideoFrame::Format_IMC3;
        formats << QVideoFrame::Format_IMC4;
        formats << QVideoFrame::Format_Y8;
        formats << QVideoFrame::Format_Y16;
        formats << QVideoFrame::Format_Jpeg;
        formats << QVideoFrame::Format_CameraRaw;
        formats << QVideoFrame::Format_AdobeDng;
        return formats;
    }

    bool present(const QVideoFrame &frame)
    {
        qDebug () << "#################################";

        QImage img;

        if (frame.isValid()) {
            QVideoFrame cloneFrame(frame);
            qDebug() << "cloneFrame.pixelFormat: "<<cloneFrame.pixelFormat();

            cloneFrame.map(QAbstractVideoBuffer::ReadOnly);
            const QImage image(cloneFrame.bits(),
                               cloneFrame.width(),
                               cloneFrame.height(),
                               //QVideoFrame::imageFormatFromPixelFormat(cloneFrame .pixelFormat()));
                               QImage::Format_RGB16);
            qDebug()<< "cloneFrame.mappedBytes: "<<cloneFrame.mappedBytes();
            qDebug()<< "cloneFrame.bytesPerLine: "<<cloneFrame.bytesPerLine();
            qDebug()<<image;
            if (i < 50){
                image.save(QString("/Users/cvaello/Desktop/VCS/CCU/Software/CCU/capture/img" + QString::number(i) + ".bmp"),0,0);
                //QByteArray arr((char*)image.bits(),image.byteCount());
            }
            cloneFrame.unmap();
            i++;
            return true;
        }
        return true;
    }
};

#endif // CAMERACAPTUREBUFFER_H
