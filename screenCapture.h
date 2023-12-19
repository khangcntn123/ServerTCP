#pragma once

#include <QObject>
#include <windows.h>
#include <WinUser.h>
#include <Qpixmap>
#include <QBuffer>
#include <QTimer>
#include <QtNetwork/qabstractsocket.h>



class screenCapture  : public QObject
{
	Q_OBJECT

public:
	screenCapture(QObject *parent=nullptr);
	~screenCapture();

signals:
	void rawImageDataIsReady(const QByteArray& rawBitmap, int width, int height, int quality);

public slots:
	void CaptureRawData();
};
