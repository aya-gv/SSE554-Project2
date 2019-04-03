#include <QtWidgets>

#include "canvasarea.h"

CanvasArea::CanvasArea(QWidget *parent)
    : QWidget(parent)
{
    setAttribute(Qt::WA_StaticContents);
    modified = false;
    scribbling = false;
    myPenWidth = 1;
    myPenColor = Qt::black;
}

bool CanvasArea::openImage(const QString &fileName)
{
    QImage loadedImage;
    if (!loadedImage.load(fileName))
        return false;

    QSize newSize = loadedImage.size().expandedTo(size());
    resizeImage(&loadedImage, newSize);
    image = loadedImage;
    modified = false;
    update();
    return true;
}

bool CanvasArea::saveImage(const QString &fileName, const char *fileFormat)
{
    QImage visibleImage = image;
    resizeImage(&visibleImage, size());

    if (visibleImage.save(fileName, fileFormat)) {
        modified = false;
        return true;
    } else {
        return false;
    }
}

void CanvasArea::setPenColor(const QColor &newColor)
{
    myPenColor = newColor;
}

void CanvasArea::setPenWidth(int newWidth)
{
    myPenWidth = newWidth;
}

void CanvasArea::setDrawMode(CanvasArea::DrawMode newMode)
{
    drawMode = newMode;
}

void CanvasArea::clearScreen()
{
    image.fill(qRgb(255, 255, 255));
    modified = true;
    update();
}

void CanvasArea::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        scribbling = true;
        previousImage = image;
        lastPoint = event->pos();

        if(drawMode == ERASE)
        {
            QPixmap pixmap(QSize(20,20));
            pixmap.fill(Qt::transparent);
            QPainter painter(&pixmap);
            QRect r(QPoint(), pixmap.size());
            r.adjust(1,1,-1,-1);
            painter.drawRect(r);
            painter.end();
            QCursor cursor(pixmap);
            QApplication::setOverrideCursor(cursor);
        }
    }
}

void CanvasArea::mouseMoveEvent(QMouseEvent *event)
{
    if ((event->buttons() & Qt::LeftButton) && scribbling){
        switch(drawMode)
        {
        case DRAWING:
            drawLineTo(event->pos());
            break;
        case ERASE:
            erase(event->pos());
            break;
        case LINE:
            drawLine(event->pos());
            break;
        case RECT:
            drawRect(event->pos());
            break;
        case CIRCLE:
            drawCircle(event->pos());
            break;
        default:
            break;
        }
    }
}

void CanvasArea::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && scribbling) {
        switch(drawMode)
        {
        case DRAWING:
            drawLineTo(event->pos());
            break;
        case ERASE:
            erase(event->pos());
            QGuiApplication::setOverrideCursor(QCursor(Qt::CursorShape::ArrowCursor));
            break;
        case LINE:
            drawLine(event->pos());
            break;
        case RECT:
            drawRect(event->pos());
            break;
        case CIRCLE:
            drawCircle(event->pos());
            break;
        default:
            break;
        }
        scribbling = false;
    }
}

void CanvasArea::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QRect dirtyRect = event->rect();
    painter.drawImage(dirtyRect, image, dirtyRect);
}

void CanvasArea::resizeEvent(QResizeEvent *event)
{
    if (width() > image.width() || height() > image.height()) {
        int newWidth = qMax(width() + 128, image.width());
        int newHeight = qMax(height() + 128, image.height());
        resizeImage(&image, QSize(newWidth, newHeight));
        update();
    }
    QWidget::resizeEvent(event);
}

void CanvasArea::drawLineTo(const QPoint &endPoint)
{
    QPainter painter(&image);
    painter.setPen(QPen(myPenColor, myPenWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter.drawLine(lastPoint, endPoint);
    modified = true;

    int rad = (myPenWidth / 2) + 2;
    update(QRect(lastPoint, endPoint).normalized().adjusted(-rad, -rad, +rad, +rad));
    lastPoint = endPoint;
}

void CanvasArea::drawLine(const QPoint &endPoint)
{
    image = previousImage;
    QPainter painter(&image);
    painter.setPen(QPen(myPenColor, myPenWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter.drawLine(lastPoint, endPoint);
    modified = true;
    int rad = (myPenWidth / 2) + 10;
    update(QRect(lastPoint, endPoint).normalized().adjusted(-rad, -rad, +rad, +rad));
}

void CanvasArea::drawRect(const QPoint &endPoint)
{
    image = previousImage;
    QRect rect = QRect(lastPoint, endPoint).normalized();
    QPainter painter(&image);
    painter.setPen(QPen(myPenColor, myPenWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter.drawRect(rect);
    modified = true;
    update(QRect(lastPoint, endPoint).normalized().adjusted(-rect.width() / 2, -rect.height()/2, rect.width()/2, rect.height()/2));
}

void CanvasArea::drawCircle(const QPoint &endPoint)
{
    image = previousImage;
    QRect rect = QRect(lastPoint, endPoint).normalized();
    QPainter painter(&image);
    painter.setPen(QPen(myPenColor, myPenWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter.drawEllipse(rect);
    modified = true;
    update(QRect(lastPoint, endPoint).normalized().adjusted(-rect.width() / 2, -rect.height()/2, rect.width()/2, rect.height()/2));

}

void CanvasArea::erase(const QPoint &endPoint)
{
    QPainter painter(&image);
    painter.setPen(QPen(Qt::GlobalColor::white, 20, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter.drawLine(lastPoint, endPoint);
    modified = true;
    int rad = 10;
    update(QRect(lastPoint, endPoint).normalized().adjusted(-rad, -rad, +rad, +rad));
    lastPoint = endPoint;
}

void CanvasArea::resizeImage(QImage *image, const QSize &newSize)
{
    if (image->size() == newSize)
        return;

    QImage newImage(newSize, QImage::Format_RGB32);
    newImage.fill(qRgb(255, 255, 255));
    QPainter painter(&newImage);
    painter.drawImage(QPoint(0, 0), *image);
    *image = newImage;
}

void CanvasArea::exampleRectangle(QPoint topLeft, QPoint bottomRight)
{
    previousImage = image;
    lastPoint = topLeft;
    drawRect(bottomRight);
}

void CanvasArea::exampleCircle(QPoint topLeft, QPoint bottomRight)
{
    previousImage = image;
    lastPoint = topLeft;
    drawCircle(bottomRight);
}

void CanvasArea::exampleLine(QPoint topLeft, QPoint bottomRight)
{
    previousImage = image;
    lastPoint = topLeft;
    drawLine(bottomRight);
}

void CanvasArea::exampleDraw(QPoint topLeft, QPoint bottomRight)
{
    previousImage = image;
    lastPoint = topLeft;
    drawLineTo(bottomRight);
}
