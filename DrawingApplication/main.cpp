#include "mainwindow.h"
#include "testsuite.h"
#include "testresults.h"
#include <QApplication>
#include <QtTest/QTest>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    TestSuite ts;
    TestResults tests;
    MainWindow w;

    //ToDo: Add command line arg for this section instead of true
    //Example: if(a.arguments().contains("testmode"))
    if(true)
    {
        ts.RunTests();

        tests.setOutput(ts.getOutput());
        tests.show();
    }
    else
    {
        w.show();
    }

    return a.exec();
}
