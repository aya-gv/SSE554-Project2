#include "TestSuite.h"

TestSuite::TestSuite()
{
}

bool TestSuite::RunTests()
{
    output.clear();
    qDebug() << "********Running Unit Tests********";
    qDebug() << QString("Test Case 1: ") + (TestCase1() ? QString("Pass") : QString("Fail"));
    qDebug() << QString("Test Case 2: ") + (TestCase2() ? QString("Pass") : QString("Fail"));
    qDebug() << "***Finished Running Unit Tests***";

    return true;
}

QList<QString> TestSuite::getOutput()
{
    return output;
}


bool TestSuite::TestCase1()

{
    QColor before = ca.penColor();
    QColor after = QColor(Qt::GlobalColor::red);
    if(after == before)
        after = QColor(Qt::GlobalColor::blue);
    ca.setPenColor(after);

    bool result = ca.penColor() == after;
    QString resultString = QString("Test Case 1: ");
    resultString += result ? QString("PASS") : QString("FAIL");
    output.push_back(resultString);

    return result;
}

bool TestSuite::TestCase2()
{
    ca.setPenWidth(2);
    int before = ca.penWidth();
    ca.setPenWidth(before + 1);
    bool result = ca.penWidth() == before + 1;
    QString resultString = QString("Test Case 2: ");
    resultString += result ? QString("PASS") : QString("FAIL");
    output.push_back(resultString);

    return result;
}
