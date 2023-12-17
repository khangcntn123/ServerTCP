#include "processImage.h"

processImage::processImage(QObject *parent)
	: QObject(parent)
{

}

processImage::~processImage()
{


}



void processImage::createImage(const QByteArray& rawBitmap, int width, int height, int quality) {
    QImage image(reinterpret_cast<const uchar*>(rawBitmap.constData()), width, height, QImage::Format_ARGB32);

    QByteArray imageData;
    QBuffer buffer(&imageData);
    buffer.open(QIODevice::WriteOnly);
    image.save(&buffer, "JPEG", quality);
    emit imagedatareadytosent(imageData);
}