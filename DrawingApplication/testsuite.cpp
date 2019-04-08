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
    qDebug() << QString("Test Case 3: ") + (TestCase3() ? QString("Pass") : QString("Fail"));
    qDebug() << QString("Test Case 4: ") + (TestCase4() ? QString("Pass") : QString("Fail"));
    qDebug() << QString("Test Case 5: ") + (TestCase5() ? QString("Pass") : QString("Fail"));
    qDebug() << QString("Test Case 6: ") + (TestCase6() ? QString("Pass") : QString("Fail"));
    qDebug() << QString("Test Case 7: ") + (TestCase7() ? QString("Pass") : QString("Fail"));
    qDebug() << QString("Test Case 8: ") + (TestCase8() ? QString("Pass") : QString("Fail"));
    qDebug() << QString("Test Case 9: ") + (TestCase9() ? QString("Pass") : QString("Fail"));
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

bool TestSuite::TestCase3()

{
    QColor before = ca.penColor();
    QColor after = QColor(Qt::GlobalColor::green);
    if(after == before)
        after = QColor(Qt::GlobalColor::magenta);
    ca.setPenColor(after);

    bool result = ca.penColor() == after;
    QString resultString = QString("Test Case 3: ");
    resultString += result ? QString("PASS") : QString("FAIL");
    output.push_back(resultString);

    return result;
}

bool TestSuite::TestCase4()

{
    QColor before = ca.penColor();
    QColor after = QColor(Qt::GlobalColor::blue);
    if(after == before)
        after = QColor(Qt::GlobalColor::yellow);
    ca.setPenColor(after);

    bool result = ca.penColor() == after;
    QString resultString = QString("Test Case 4: ");
    resultString += result ? QString("PASS") : QString("FAIL");
    output.push_back(resultString);

    return result;
}

bool TestSuite::TestCase5()
{
    QColor before = ca.penColor();
    QColor after = QColor(Qt::GlobalColor::cyan);
    if(after == before)
        after = QColor(Qt::GlobalColor::black);
    ca.setPenColor(after);

    bool result = ca.penColor() == after;
    QString resultString = QString("Test Case 5: ");
    resultString += result ? QString("PASS") : QString("FAIL");
    output.push_back(resultString);

    return result;
}

bool TestSuite::TestCase6()
{
    QColor before = ca.penColor();
    QColor after = QColor(Qt::GlobalColor::gray);
    if(after == before)
        after = QColor(Qt::GlobalColor::darkRed);
    ca.setPenColor(after);

    bool result = ca.penColor() == after;
    QString resultString = QString("Test Case 6: ");
    resultString += result ? QString("PASS") : QString("FAIL");
    output.push_back(resultString);

    return result;
}

bool TestSuite::TestCase7()
{
    ca.setPenWidth(1);
    int before = ca.penWidth();
    ca.setPenWidth(before + 1);
    bool result = ca.penWidth() == before + 1;
    QString resultString = QString("Test Case 7: ");
    resultString += result ? QString("PASS") : QString("FAIL");
    output.push_back(resultString);

    return result;
}

bool TestSuite::TestCase8()
{
    ca.setPenWidth(3);
    int before = ca.penWidth();
    ca.setPenWidth(before + 1);
    bool result = ca.penWidth() == before + 1;
    QString resultString = QString("Test Case 8: ");
    resultString += result ? QString("PASS") : QString("FAIL");
    output.push_back(resultString);

    return result;
}

bool TestSuite::TestCase9()
{
    ca.setPenWidth(4);
    int before = ca.penWidth();
    ca.setPenWidth(before + 1);
    bool result = ca.penWidth() == before + 1;
    QString resultString = QString("Test Case 9: ");
    resultString += result ? QString("PASS") : QString("FAIL");
    output.push_back(resultString);

    return result;
}
