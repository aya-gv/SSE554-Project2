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
    bool TestCase3();
    bool TestCase4();
    bool TestCase5();
    bool TestCase6();
    bool TestCase7();
    bool TestCase8();
    bool TestCase9();

    QList<QString> output;
};

#endif //TESTSUITE_H
