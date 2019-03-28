#include <QtTest>
#include <QCoreApplication>

// add necessary includes here

class DrawTestCase : public QObject
{
    Q_OBJECT

public:
    DrawTestCase();
    ~DrawTestCase();

private slots:
    void initTestCase();
    void cleanupTestCase();
    void test_case1();

};

DrawTestCase::DrawTestCase()
{

}

DrawTestCase::~DrawTestCase()
{

}

void DrawTestCase::initTestCase()
{

}

void DrawTestCase::cleanupTestCase()
{

}

void DrawTestCase::test_case1()
{

}

QTEST_MAIN(DrawTestCase)

#include "tst_drawtestcase.moc"
