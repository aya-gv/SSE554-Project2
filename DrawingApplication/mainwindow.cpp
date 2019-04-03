#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtWidgets>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    canvasArea = new CanvasArea;
    canvasArea->sizePolicy().setVerticalStretch(QSizePolicy::Expanding);
    canvasArea->sizePolicy().setHorizontalStretch(QSizePolicy::Preferred);
    canvasArea->setMinimumSize(500, 500);

    ui->CanvasGrid->addWidget(canvasArea);

    createActions();
    createMenus();

    setWindowTitle(tr("DrawIt"));
    resize(500, 500);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (saveDialog())
    {
        event->accept();
    }
    else
    {
        event->ignore();
    }
}

void MainWindow::open()
{
    if (saveDialog()) {
        QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), QDir::currentPath());
        if (!fileName.isEmpty())
            canvasArea->openImage(fileName);
    }
}

void MainWindow::save()
{
    QAction *action = qobject_cast<QAction *>(sender());
    QByteArray fileFormat = action->data().toByteArray();
    saveFile(fileFormat);
}

void MainWindow::penColor()
{
    QColor newColor = QColorDialog::getColor(canvasArea->penColor());
    if (newColor.isValid())
        canvasArea->setPenColor(newColor);
}

void MainWindow::penWidth()
{
    bool ok;
    int newWidth = QInputDialog::getInt(this, tr("Scribble"), tr("Select pen width:"), canvasArea->penWidth(), 1, 50, 1, &ok);
    if (ok)
        canvasArea->setPenWidth(newWidth);
}

void MainWindow::createActions()
{
    openAct = new QAction(tr("&Open..."), this);
    openAct->setShortcuts(QKeySequence::Open);
    connect(openAct, SIGNAL(triggered()), this, SLOT(open()));

    foreach (QByteArray format, QImageWriter::supportedImageFormats())
    {
        QString text = tr("%1...").arg(QString(format).toUpper());

        QAction *action = new QAction(text, this);
        action->setData(format);
        connect(action, SIGNAL(triggered()), this, SLOT(save()));
        saveAsActs.append(action);
    }

    exitAct = new QAction(tr("&Exit"), this);
    exitAct->setShortcuts(QKeySequence::Quit);
    exitAct->setStatusTip(tr("Exit the application"));
    connect(exitAct, &QAction::triggered, this, &QWidget::close);

    clearScreenAct = new QAction(tr("&Clear Screen"), this);
    clearScreenAct->setShortcut(tr("Ctrl+L"));
    connect(clearScreenAct, SIGNAL(triggered()),
            canvasArea, SLOT(clearScreen()));
}

void MainWindow::createMenus()
{
    saveAsMenu = new QMenu(tr("&Save As"), this);
    foreach (QAction *action, saveAsActs)
        saveAsMenu->addAction(action);

    fileMenu = new QMenu(tr("&File"), this);
    fileMenu->addAction(openAct);
    fileMenu->addMenu(saveAsMenu);
    fileMenu->addAction(exitAct);

    optionMenu = new QMenu(tr("&Options"), this);
    optionMenu->addSeparator();
    optionMenu->addAction(clearScreenAct);

    menuBar()->addMenu(fileMenu);
    menuBar()->addMenu(optionMenu);
}

bool MainWindow::saveDialog()
{
    if (canvasArea->isModified())
    {
       QMessageBox::StandardButton selection;

       QMessageBox::warning(this, tr("DrawIt"), tr("Would you like to save your changes?"), QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
       if (selection == QMessageBox::Save)
       {
           return saveFile("png");
       }
       else if (selection == QMessageBox::Cancel)
       {
           return false;
       }
    }
    return true;
}

bool MainWindow::saveFile(const QByteArray &fileFormat)
{
    QString initialPath = QDir::currentPath() + "/untitled." + fileFormat;

    QString fileName = QFileDialog::getSaveFileName(this, tr("Save As"), initialPath, tr("%1 Files (*.%2);;All Files (*)").arg(QString::fromLatin1(fileFormat.toUpper())).arg(QString::fromLatin1(fileFormat)));
    if (fileName.isEmpty())
    {
        return false;
    }
    else
    {
        return canvasArea->saveImage(fileName, fileFormat.constData());
    }
}

void MainWindow::on_DrawButton_clicked()
{
    canvasArea->setDrawMode(CanvasArea::DrawMode::DRAWING);
}

void MainWindow::on_EraseButton_clicked()
{
    canvasArea->setDrawMode(CanvasArea::DrawMode::ERASE);
}

void MainWindow::on_LineButton_clicked()
{
    canvasArea->setDrawMode(CanvasArea::DrawMode::LINE);
}

void MainWindow::on_RectangleButton_clicked()
{
    canvasArea->setDrawMode(CanvasArea::DrawMode::RECT);
}

void MainWindow::on_CircleButton_clicked()
{
    canvasArea->setDrawMode(CanvasArea::DrawMode::CIRCLE);
}


void MainWindow::on_BrushSizeComboBox_currentIndexChanged(int index)
{
    canvasArea->setPenWidth(index);
}

void MainWindow::on_ColorSelectionButton_clicked()
{
    penColor();
}

void MainWindow::on_clearButton_clicked()
{
    canvasArea->clearScreen();
}

void MainWindow::circleTest(QPoint topLeft, QPoint bottomRight)
{
    canvasArea->exampleCircle(topLeft, bottomRight);
}

void MainWindow::rectangleTest(QPoint topLeft, QPoint bottomRight)
{
    canvasArea->exampleRectangle(topLeft, bottomRight);
}

void MainWindow::lineTest(QPoint topLeft, QPoint bottomRight)
{
    canvasArea->exampleLine(topLeft, bottomRight);
}

void MainWindow::drawTest(QPoint topLeft, QPoint bottomRight)
{
    canvasArea->exampleLine(topLeft, bottomRight);
}
