#ifndef TESTSUITE_H
#define TESTSUITE_H

#include <QTest>
#include "canvasarea.h"
#include "mainwindow.h"
#include <QList>

class TestSuite
{
public:
    TestSuite();
    bool RunTests();
    QList<QString> getOutput();

private:
    CanvasArea ca;
    MainWindow mw;

    bool TestCase1();
    bool TestCase2();

    QList<QString> output;
};

#endif //TESTSUITE_H
