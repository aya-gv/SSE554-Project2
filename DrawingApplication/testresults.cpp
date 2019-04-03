#include "testresults.h"
#include "ui_testresults.h"
#include <QLabel>
#include <QSpacerItem>

TestResults::TestResults(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TestResults)
{
    ui->setupUi(this);
}

TestResults::~TestResults()
{
    delete ui;
}

void TestResults::setOutput(QList<QString> output)
{
    QString testResultString;
    testResultString = "Test results:\n";
    for(int i = 0; i < output.count(); i++)
    {
        testResultString += output[i] + "\n";
    }
    ui->testResultLog->setText(testResultString);
    mw.show();
}

void TestResults::on_rectangleTest_clicked()
{
    mw.rectangleTest(QPoint(10, 10), QPoint(110, 110));
}

void TestResults::on_circleTest_clicked()
{
    mw.circleTest(QPoint(10, 110), QPoint(110, 210));
}

void TestResults::on_lineTest_clicked()
{
    mw.lineTest(QPoint(10, 210), QPoint(110, 310));
}

void TestResults::on_drawTest_clicked()
{
    mw.drawTest(QPoint(20, 310), QPoint(120, 410));
}
