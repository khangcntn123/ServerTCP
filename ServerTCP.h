#pragma once

#include <QTimer>
#include <QScreen>
#include <Qpixmap>
#include <QBuffer>
#include <QGuiApplication>

#include <QtWidgets/QMainWindow>
#include <qstyle.h>
#include <QtNetwork/qhostaddress.h>
#include <QtNetwork/qabstractsocket.h>
#include "MyTCPServer.h"
#include "ui_ServerTCP.h"
#include <qelapsedtimer.h>
#include <QCursor>
#include <QMouseEvent>
#include <iostream>
#include <windows.h>
#include <WinUser.h>




QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class ServerTCP : public QMainWindow
{
    Q_OBJECT

public:
    ServerTCP(QWidget* parent = nullptr);
    ~ServerTCP();

public slots:

    void on_btnClear_clicked();
    void on_btnStartServer_clicked();

    void newClinetConnected();
    void sendImage();
    void on_btnSendToAll_clicked();

    void clientDisconnected();

    //void clientDataReceived(QString message);

    void EventRecieve(int a, int b, int c);


    //void keyPressEvent(QKeyEvent* event);


public:
    int DataEvent[3] = { 0 };
    // DataEvent[0] = 0->8, 0->6 mouse, 7->8 kb
    // DataEvent[1] = x neu la chuot, Virtual Key neu la phim
    // DataEvent[2] = y neu la chuot, 0 neu la phim
    QPoint mousePos;
    //QTimer* mouseUpdateTimer;

    QTimer _timer;

    Ui::ServerTCPClass* ui;
    MyTCPServer* _server;
};
