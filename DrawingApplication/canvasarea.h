#ifndef CANVASAREA_H
#define CANVASAREA_H

#include <QColor>
#include <QImage>
#include <QPoint>
#include <QWidget>

class CanvasArea : public QWidget
{
public:
    Q_OBJECT

public:

    enum DrawMode
    {
        NONE = 0,
        DRAWING = 1,
        ERASE = 2,
        LINE = 3,
        RECT = 4
    };

    CanvasArea(QWidget *parent = 0);

    bool openImage(const QString &fileName);
    bool saveImage(const QString &fileName, const char *fileFormat);
    void setPenColor(const QColor &newColor);
    void setPenWidth(int newWidth);
    void setDrawMode(DrawMode newMode);

    bool isModified() const { return modified; }
    QColor penColor() const { return myPenColor; }
    int penWidth() const { return myPenWidth; }

public slots:
    void clearScreen();

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

private:
    void drawLineTo(const QPoint &endPoint);
    void drawLine(const QPoint &endPoint);
    void drawRect(const QPoint &endPoint);
    void erase(const QPoint &endPoint);
    void resizeImage(QImage *image, const QSize &newSize);

    bool modified;
    bool scribbling;
    int myPenWidth;
    QColor myPenColor;
    QImage image;
    QImage previousImage;
    QPoint lastPoint;

    DrawMode drawMode;
};

#endif // CANVASAREA_H
