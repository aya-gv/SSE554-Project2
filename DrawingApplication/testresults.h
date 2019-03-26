#ifndef TESTRESULTS_H
#define TESTRESULTS_H

#include <QMainWindow>
#include <QList>
#include "testsuite.h"
#include "mainwindow.h"

namespace Ui {
class TestResults;
}

class TestResults : public QMainWindow
{
    Q_OBJECT

public:
    explicit TestResults(QWidget *parent = 0);
    ~TestResults();

    void setOutput(QList<QString> output);

private slots:
    void on_rectangleTest_clicked();

    void on_circleTest_clicked();

private:
    Ui::TestResults *ui;
    MainWindow mw;
};

#endif // TESTRESULTS_H
