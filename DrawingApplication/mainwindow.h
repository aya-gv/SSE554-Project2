#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>
#include "canvasarea.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void rectangleTest(QPoint topLeft, QPoint bottomRight);
    void circleTest(QPoint topLeft, QPoint bottomRight);
    void lineTest(QPoint topLeft, QPoint bottomRight);
    void drawTest(QPoint topLeft, QPoint bottomRight);
    void eraseTest(QPoint topLeft, QPoint bottomRight);
    void clearTest();
    void setBrushSizeTest();
    void penColorTest();

protected:
    void closeEvent(QCloseEvent *event) override;

private slots:
    void open();
    void save();
    void penColor();
    void penWidth();

    void on_DrawButton_clicked();
    void on_EraseButton_clicked();
    void on_LineButton_clicked();
    void on_RectangleButton_clicked();
    void on_CircleButton_clicked();
    void on_BrushSizeComboBox_currentIndexChanged(int index);
    void on_ColorSelectionButton_clicked();
    void on_clearButton_clicked();

private:
    void createActions();
    void createMenus();
    bool saveDialog();
    bool saveFile(const QByteArray &fileFormat);

    Ui::MainWindow *ui;

    CanvasArea *canvasArea;

    QMenu *saveAsMenu;
    QMenu *fileMenu;
    QMenu *optionMenu;

    QAction *openAct;
    QList<QAction *> saveAsActs;
    QAction *exitAct;
    QAction *clearScreenAct;
    QAction *penColorAct;
    QAction *penWidthAct;
};

#endif // MAINWINDOW_H
