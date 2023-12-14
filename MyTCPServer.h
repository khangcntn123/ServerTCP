#pragma once




#include <QObject>
#include <QtNetwork/qtcpserver.h>
#include <QtNetwork/qtcpsocket.h>


class MyTCPServer : public QObject
{
    Q_OBJECT
public:
    explicit MyTCPServer(int port, QObject* parent = nullptr);
    bool isStarted() const;
    void sendToAll(QByteArray message);
    void serverDisconnect();
signals:
    void newClientConnected();
    void clientDisconnect();
    void dataReceived();
    void Events(int a,int b, int c);

private slots:
    void on_client_connecting();

    void clientDisconnected();

    void clientDataReady();


private:
    QTcpServer* _server;
    QList<QTcpSocket*> _socketsList;
    bool _isStarted;
};

