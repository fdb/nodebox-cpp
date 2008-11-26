#include <QtTest/QtTest>

class TestNodeCore : public QObject
{
    Q_OBJECT
private slots:
    void toUpper();
};

void TestNodeCore::toUpper()
{
    QString str = "Hello";
    QCOMPARE(str.toUpper(), QString("HELLO"));
}

QTEST_MAIN(TestNodeCore)
#include "testnodecore.moc"

