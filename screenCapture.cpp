#include "screenCapture.h"

screenCapture::screenCapture(QObject *parent)
	: QObject(parent)
{


}

screenCapture::~screenCapture()
{


}



void screenCapture::CaptureRawData() {
   /* _timer.start();*/
    MessageBox(NULL, TEXT("da vao luong bat hinh anh "), TEXT("Title of the Message Box"), MB_OK);
    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);
    int quality = 50;

    HDC hScreenDC = GetDC(NULL);
    HDC hMemoryDC = CreateCompatibleDC(hScreenDC);
    HBITMAP hBitmap = CreateCompatibleBitmap(hScreenDC, screenWidth, screenHeight);
    HBITMAP hOldBitmap = (HBITMAP)SelectObject(hMemoryDC, hBitmap);

    BitBlt(hMemoryDC, 0, 0, screenWidth, screenHeight, hScreenDC, 0, 0, SRCCOPY);

    //_timer.start();
    hBitmap = (HBITMAP)SelectObject(hMemoryDC, hOldBitmap);

    BITMAPINFOHEADER bi;
    bi.biSize = sizeof(BITMAPINFOHEADER);
    bi.biWidth = screenWidth;
    bi.biHeight = -screenHeight;
    bi.biPlanes = 1;
    bi.biBitCount = 32;
    bi.biCompression = BI_RGB;
    bi.biSizeImage = 0;
    bi.biXPelsPerMeter = 0;
    bi.biYPelsPerMeter = 0;
    bi.biClrUsed = 0;
    bi.biClrImportant = 0;

    std::vector<BYTE> buf(screenWidth * screenHeight * 4);
    GetDIBits(hMemoryDC, hBitmap, 0, screenHeight, &buf[0], (BITMAPINFO*)&bi, DIB_RGB_COLORS);
    //qint64 elapsed = _timer.elapsed();
    //QString elapsedStr = QString::number(elapsed);
    //ui->lstConsole->addItem("Thoi gian chuyen doi anh thanh QByteArray: " + elapsedStr + "ms");

    DeleteObject(hBitmap);
    DeleteDC(hMemoryDC);
    ReleaseDC(NULL, hScreenDC);
    QByteArray byteArray(reinterpret_cast<char*>(buf.data()), buf.size());
    //qint64 khangg = _timer.elapsed();
    //QString quansat = QString::number(khangg);
    //ui->lstConsole->addItem("Thoi gian chup anh la: " + quansat + " ms");
    /*MessageBox(NULL, TEXT("Da chup va chuan bi tha tin hieu"), TEXT("Title of the Message Box"), MB_OK);*/

    emit rawImageDataIsReady(byteArray, screenWidth, screenHeight, quality);
    //QImage image(reinterpret_cast<const uchar*>(byteArray.constData()), screenWidth, screenHeight, QImage::Format_ARGB32);

    //QByteArray imageData;
    //QBuffer buffer(&imageData);
    //buffer.open(QIODevice::WriteOnly);
    //image.save(&buffer, "JPEG", quality);
    //int datasize = imageData.size();
    //QByteArray imagesize;
    //QDataStream _stream1(&imagesize, QIODevice::WriteOnly);
    //_stream1 << datasize;
    //_server->sendToAll(imagesize + imageData);
    //_timer.start();
    //QImage image(reinterpret_cast<const uchar*>(buf.data()), screenWidth, screenHeight, QImage::Format_ARGB32);
    //QByteArray jpegData;
    //QBuffer buffer(&jpegData);
    //buffer.open(QIODevice::WriteOnlyd
    //image.save(&buffer, "JPEG",40);
    //qint64 kkk = _timer.elapsed();
    //QString kekeke = QString::number(kkk);
    //ui->lstConsole->addItem("Thoi gian chuyen thanh anh server: " + kekeke + " ms"adadaa                             
    //return byteArray;
}