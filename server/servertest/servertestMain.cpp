#include <QtTest>
#include "dbtest.h"
#include "sessiontest.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    dbtest dbt;
    QTest::qExec(&dbt);

    sessiontest st;
    QTest::qExec(&st);

    return 0;
}
