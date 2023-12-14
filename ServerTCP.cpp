#include "ServerTCP.h"
#include "ui_ServerTCP.h"

ServerTCP::ServerTCP(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::ServerTCPClass)
{
    ui->setupUi(this);
    mousePos = QCursor::pos();
    _server = nullptr;
}

ServerTCP::~ServerTCP()
{
    delete ui;
}

void ServerTCP::on_btnClear_clicked() {
    ui->lstConsole->clear();

}

void ServerTCP::on_btnStartServer_clicked()
{
    if (_server == nullptr) {
        auto port = ui->spnServerPort->value();
        _server = new MyTCPServer(port);
        connect(_server, &MyTCPServer::newClientConnected, this, &ServerTCP::sendImage);
        connect(_server, &MyTCPServer::dataReceived, this, &ServerTCP::sendImage);
        connect(_server, &MyTCPServer::clientDisconnect, this, &ServerTCP::clientDisconnected);
        connect(_server, &MyTCPServer::Events, this, &ServerTCP::EventRecieve);
        auto state = (_server->isStarted()) ? "1" : "0";
        ui->lblConnectionStatus->setProperty("state", state);
        style()->polish(ui->lblConnectionStatus);
        ui->lstConsole->addItem("Server Start");
    }
    else {
        _server->serverDisconnect();
        ui->lstConsole->addItem("Disconnected");
        _server = nullptr;
    }
 //   _timer.setInterval(1000 / 30);
 //   connect(&_timer, &QTimer::timeout, this, &ServerTCP::on_btnSendToAll_clicked);
	//_timer.start();



}

void ServerTCP::newClinetConnected()
{
    ui->lstConsole->addItem("New Client connected");
    ui->btnStartServer->setText("Disconnect");
    //mouseUpdateTimer = new QTimer(this);
    //connect(mouseUpdateTimer, &QTimer::timeout, this, &ServerTCP::EventRecieve);
    //mouseUpdateTimer->start(10);

    //_timer.setInterval(1000/10);
    //connect(&_timer, &QTimer::timeout, this, &ServerTCP::on_btnSendToAll_clicked);
    //_timer.start();
}

void ServerTCP::EventRecieve(int a, int b , int c) {
    ui->lstConsole->addItem("truyen duoc chuot");
        QPoint currentPos = QCursor::pos();
        DataEvent[0] = a;
        DataEvent[1] = b;
        DataEvent[2] = c;
       /* ui.movePos->setText("Mouse Move Pos: X: " + QString::number(DataEvent[1]) + "Y: " + QString::number(DataEvent[2]));*/
        int type = DataEvent[0];
        QCursor::setPos(DataEvent[1], DataEvent[2]);
        if (type == 0) {
            //ui.Double_click->setText("Type = X: " + QString::number(DataEvent[1]) + "Y: " + QString::number(DataEvent[2]));

        }
        else {
            if (type == 1) {
              /*  ui.Press->setText("Mouse Press L: X: " + QString::number(DataEvent[1]) + "Y: " + QString::number(DataEvent[2]));*/
                mouse_event(MOUSEEVENTF_LEFTDOWN, currentPos.x(), currentPos.y(), 0, 0);
                //mouseInput.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
                //SendInput(1, &mouseInput, sizeof(INPUT));

            }
            else if (type == 2) {
                /*ui.Press->setText("Mouse Press R: X: " + QString::number(DataEvent[1]) + "Y: " + QString::number(DataEvent[2]));*/
                mouse_event(MOUSEEVENTF_RIGHTDOWN, currentPos.x(), currentPos.y(), 0, 0);
                //mouseInput.mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;
                //SendInput(1, &mouseInput, sizeof(INPUT));
            }
            else if (type == 3) {
               /* ui.Release->setText("Mouse Release L: X: " + QString::number(DataEvent[1]) + "Y: " + QString::number(DataEvent[2]));*/
                mouse_event(MOUSEEVENTF_LEFTUP, currentPos.x(), currentPos.y(), 0, 0);
                //mouseInput.mi.dwFlags = MOUSEEVENTF_LEFTUP;
                //SendInput(1, &mouseInput, sizeof(INPUT));
            }
            else if (type == 4) {
              /*  ui.Release->setText("Mouse Release R: X: " + QString::number(DataEvent[1]) + "Y: " + QString::number(DataEvent[2]));*/
                mouse_event(MOUSEEVENTF_RIGHTUP, currentPos.x(), currentPos.y(), 0, 0);
                //mouseInput.mi.dwFlags = MOUSEEVENTF_RIGHTUP;
                //SendInput(1, &mouseInput, sizeof(INPUT));
            }
            else if (type == 5) {
               /* ui.Double_click->setText("Mouse DOuble Click: X: " + QString::number(DataEvent[1]) + "Y: " + QString::number(DataEvent[2]));*/
            }
            else if (type == 6) {
             /*   ui.Double_click->setText("NO MOUSE EVENT: X: " + QString::number(DataEvent[1]) + "Y: " + QString::number(DataEvent[2]) + "   " + QString::number(DataEvent[0]));*/
            }
            else if (type == 7 || type == 8) {
                //INPUT keyInput;
                //keyInput.type = INPUT_KEYBOARD;
                //keyInput.ki.time = 0;
                //keyInput.ki.dwExtraInfo = 0;
                //keyInput.ki.wVk = DataEvent[1];
                //SendInput(0, &keyInput, sizeof(keyInput));
                //keyInput.ki.dwFlags = KEYEVENTF_KEYUP;
                //SendInput(0, &keyInput, sizeof(keyInput));
                keybd_event(DataEvent[1], 0, 0, 0);
                keybd_event(DataEvent[1], 0, KEYEVENTF_KEYUP, 0);
                //INPUT keyInput;
                //keyInput.type = INPUT_KEYBOARD;
                //keyInput.ki.time = 0;
                //keyInput.ki.dwExtraInfo = 0;
                //keyInput.ki.wVk = DataEvent[1];
                //SendInput(0, &keyInput, sizeof(keyInput));
            }
        }
}


//void ClientTCP::device_disconnected()
//{
//    ui->lstConsole->addItem("Disconnected from Device");
//    ui->btnConnect->setText("Connect");
//    ui->grpSendData->setEnabled(false);
//
//}


void ServerTCP::on_btnSendToAll_clicked()
{
  /*  QLabel imageLabel;*/
    //QScreen* screen = QGuiApplication::primaryScreen();
    //QPixmap screenshot = screen->grabWindow(0);
    //QByteArray byteArray;
    //QBuffer buffer(&byteArray);

    //buffer.open(QIODevice::WriteOnly);
    //if (screenshot.save(&buffer, "PNG")) {
    //    buffer.close();
    //    QString pstring = QString::number(byteArray.size());
    //    ui->lstConsole->addItem(pstring);
    //    int totalSize = byteArray.size();
    //    int largePacketSize = 8192; // 65536 bits
    //    int numOfLargePackets = totalSize / largePacketSize + (totalSize % largePacketSize != 0 ? 1 : 0);
    //    int smallPacketSize = largePacketSize / 10;

    //    for (int i = 0; i < numOfLargePackets; ++i) {
    //        int currentPacketSize = qMin(largePacketSize, totalSize - i * largePacketSize);
    //        QByteArray largePacket = byteArray.mid(i * largePacketSize, currentPacketSize);

    //        // Here we send 10 smaller packets
    //        for (int j = 0; j < 10; ++j) {
    //            int currentSmallPacketSize = qMin(smallPacketSize, currentPacketSize - j * smallPacketSize);
    //            QByteArray smallPacket = largePacket.mid(j * smallPacketSize, currentSmallPacketSize);

    //            // Prepare packet with header [packetIndex, totalPackets, currentPacketSize, totalSize]
    //            QByteArray header;
    //            QDataStream headerStream(&header, QIODevice::WriteOnly);//nay phari xuoosng dofng
    //            headerStream << i * 10 + j << numOfLargePackets * 10 << currentSmallPacketSize << totalSize;

    //            _server->sendToAll(header + smallPacket);
    //        }
    //    }
    //}
    //QElapsedTimer timer;
    //timer.start(); 
    QScreen* screen = QGuiApplication::primaryScreen();
    QPixmap screenshot = screen->grabWindow(0);
    QByteArray byteArray;
    QBuffer buffer(&byteArray);
    buffer.open(QIODevice::WriteOnly);
    screenshot.save(&buffer, "JPEG",40);
    buffer.close();
    //qint64 elapsed = timer.elapsed();
    //QString elapsedStr = QString::number(elapsed);
    //ui->lstConsole->addItem(elapsedStr + "ms");
    //QElapsedTimer timer1;
 /*   timer.start();*/
    QByteArray sizeArray; 
    QDataStream sizeStream(&sizeArray, QIODevice::WriteOnly);
    //timer.elapsed();
    //elapsed = timer.elapsed();
    //QString elapsedStr1 = QString::number(elapsed);
    //ui->lstConsole->addItem(elapsedStr1 + "ms");
    //qint64 elapsed = timer.elapsed();
    int dataSize1 = byteArray.size(); 
    sizeStream << dataSize1;
    QString p1string = QString::number(byteArray.size());
 /*   ui->lstConsole->addItem(p1string);
    if (!byteArray.isEmpty()) {
        _server->sendToAll(sizeArray + byteArray);
    }*/
 /*   QElapsedTimer timer1;
    QPixmap test;
    timer1.start();
    test.loadFromData(byteArray);
    timer.elapsed();
    QString kkk = QString::number(byteArray.size());
    ui->lstConsole->addItem(kkk + "bytes");
    QString elapsedStr3 = QString::number(elapsed);
    ui->lstConsole->addItem(elapsedStr3 + "ms");
    QElapsedTimer timer3;
    timer3.start();*/
    //imageLabel.setGeometry(this->rect());
    //imageLabel.setPixmap(test);
    //imageLabel.setScaledContents(true);
    //imageLabel.show();
    //imageLabel.update();
    //timer3.elapsed();
    //qint64 elapsed3 = timer3.elapsed();
    //QString elapsedStr4 = QString::number(elapsed3);
    //ui->lstConsole->addItem(elapsedStr4 + "ms");
    int dataSize = byteArray.size();
    const int packetSize = 1400; 
    int offset = 0;
    //timer.start();
    _server->sendToAll(sizeArray);
    //timer.elapsed();
    //elapsed = timer.elapsed();
    //elapsedStr = QString::number(elapsed);
    //ui->lstConsole->addItem(elapsedStr + "ms");

    //timer1.start();
    while (offset < dataSize) {
        QByteArray packet = byteArray.mid(offset, packetSize);
        _server->sendToAll(packet); 
        offset += packetSize; 
    }
    //timer1.elapsed();
    //QString elapsedStr2 = QString::number(elapsed);
    //ui->lstConsole->addItem(elapsedStr2 + "ms");


    //QScreen* screen = QGuiApplication::primaryScreen();
    //QPixmap screenshot = screen->grabWindow(0);
    //QByteArray byteArray;
    //QBuffer buffer(&byteArray);
    //buffer.open(QIODevice::WriteOnly);
    //screenshot.save(&buffer, "PNG");
    //buffer.close();
/*    QString sizeString = QString::number(byteArray.size());
    if (!byteArray.isEmpty()) {
        _server->sendToAll(sizeString);
    }
    */
    byteArray.clear();
    //auto message = ui->lnMessage->text().trimmed();
    //_server->sendToAll(message);
}


void ServerTCP::sendImage() {
    QScreen* screen = QGuiApplication::primaryScreen();
    QPixmap screenshot = screen->grabWindow(0);
    QByteArray byteArray;
    QBuffer buffer(&byteArray);
    buffer.open(QIODevice::WriteOnly);
    screenshot.save(&buffer, "JPEG", 40);
    buffer.close();
    //qint64 elapsed = timer.elapsed();
    //QString elapsedStr = QString::number(elapsed);
    //ui->lstConsole->addItem(elapsedStr + "ms");
    //QElapsedTimer timer1;
 /*   timer.start();*/
    QByteArray sizeArray;
    QDataStream sizeStream(&sizeArray, QIODevice::WriteOnly);
    //timer.elapsed();
    //elapsed = timer.elapsed();
    //QString elapsedStr1 = QString::number(elapsed);
    //ui->lstConsole->addItem(elapsedStr1 + "ms");
    //qint64 elapsed = timer.elapsed();
    int dataSize1 = byteArray.size();
    sizeStream << dataSize1;
    QString p1string = QString::number(byteArray.size());
    /*   ui->lstConsole->addItem(p1string);
       if (!byteArray.isEmpty()) {
           _server->sendToAll(sizeArray + byteArray);
       }*/
       /*   QElapsedTimer timer1;
          QPixmap test;
          timer1.start();
          test.loadFromData(byteArray);
          timer.elapsed();
          QString kkk = QString::number(byteArray.size());
          ui->lstConsole->addItem(kkk + "bytes");
          QString elapsedStr3 = QString::number(elapsed);
          ui->lstConsole->addItem(elapsedStr3 + "ms");
          QElapsedTimer timer3;
          timer3.start();*/
          //imageLabel.setGeometry(this->rect());
          //imageLabel.setPixmap(test);
          //imageLabel.setScaledContents(true);
          //imageLabel.show();
          //imageLabel.update();
          //timer3.elapsed();
          //qint64 elapsed3 = timer3.elapsed();
          //QString elapsedStr4 = QString::number(elapsed3);
          //ui->lstConsole->addItem(elapsedStr4 + "ms");
    int dataSize = byteArray.size();
    const int packetSize = 1400;
    int offset = 0;
    //timer.start();
    _server->sendToAll(sizeArray);
    //timer.elapsed();
    //elapsed = timer.elapsed();
    //elapsedStr = QString::number(elapsed);
    //ui->lstConsole->addItem(elapsedStr + "ms");

    //timer1.start();
    while (offset < dataSize) {
        QByteArray packet = byteArray.mid(offset, packetSize);
        _server->sendToAll(packet);
        offset += packetSize;
    }
    //timer1.elapsed();
    //QString elapsedStr2 = QString::number(elapsed);
    //ui->lstConsole->addItem(elapsedStr2 + "ms");


    //QScreen* screen = QGuiApplication::primaryScreen();
    //QPixmap screenshot = screen->grabWindow(0);
    //QByteArray byteArray;
    //QBuffer buffer(&byteArray);
    //buffer.open(QIODevice::WriteOnly);
    //screenshot.save(&buffer, "PNG");
    //buffer.close();
/*    QString sizeString = QString::number(byteArray.size());
    if (!byteArray.isEmpty()) {
        _server->sendToAll(sizeString);
    }
    */
    byteArray.clear();
    //auto message = ui->lnMessage->text().trimmed();
    //_server->sendToAll(message);
}

//void ServerTCP::on_btnSendToAll_clicked() {
//    QScreen* screen = QGuiApplication::primaryScreen();
//    QPixmap screenshot = screen->grabWindow(0);
//    QByteArray byteArray;
//    QBuffer buffer(&byteArray);
//    buffer.open(QIODevice::WriteOnly);
//    screenshot.save(&buffer, "JPEG", 40); // Adjust JPEG quality as needed
//    buffer.close();
//
//    int dataSize = byteArray.size();
//    const int packetSize = 8192; // Increase packet size for better performance
//    QByteArray sizeArray;
//    QDataStream sizeStream(&sizeArray, QIODevice::WriteOnly);
//    sizeStream << dataSize;
//    _server->sendToAll(sizeArray);
//
//    for (int offset = 0; offset < dataSize; offset += packetSize) {
//        _server->sendToAll(byteArray.mid(offset, qMin(packetSize, dataSize - offset)));
//    }
//}


void ServerTCP::clientDisconnected()
{
    ui->lstConsole->addItem("Client Disconnected");
}

//void ServerTCP::clientDataReceived(QString message)
//{
//    ui->lstConsole->addItem(message);
//}