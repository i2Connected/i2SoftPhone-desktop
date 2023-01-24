#include <QtTest>
#include <QCoreApplication>

// add necessary includes here

class UtilsTester : public QObject
{
	Q_OBJECT
	
public:
	UtilsTester();
	~UtilsTester();
	
private slots:
	void initTestCase();
	void cleanupTestCase();
	void test_case1();
	
};

UtilsTester::UtilsTester()
{
	
}

UtilsTester::~UtilsTester()
{
	
}

void UtilsTester::initTestCase()
{
	
}

void UtilsTester::cleanupTestCase()
{
	
}

void UtilsTester::test_case1()
{
	
}

QTEST_MAIN(UtilsTester)

#include "tst_utilstester.moc"
