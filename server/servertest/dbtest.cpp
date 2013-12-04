#include "dbtest.h"

void dbtest::initTestCase()
{
    db = new UserDB();
}

void dbtest::cleanupTestCase()
{
    db->clearDB();
}

void dbtest::testNewObject()
{
    QSqlQueryModel model;
    model.setQuery(QString("select * from users"));
    QString result = model.record(0).value("username").toString();
    QCOMPARE(result, QString("admin"));
    result = model.record(0).value("password").toString();
    QCOMPARE(result, QString("admin"));
}

void dbtest::testRegisterUser_data()
{
    QTest::addColumn<QString>("username");
    QTest::addColumn<QString>("password");
    QTest::addColumn<QString>("expected");

    QTest::newRow("Username short") << QString("a") << QString("pass")
                                    << QString("Username must be between 4 and 10 characters.");
    QTest::newRow("Username long") << QString("asdfghjklqw") << QString("pass")
                                    <<  QString("Username must be between 4 and 10 characters.");
    QTest::newRow("Password short") << QString("user") << QString("a")
                                    << QString("Password must be between 4 and 16 characters.");
    QTest::newRow("Password long") << QString("user") << QString("asdfghjklqwertyui")
                                    << QString("Password must be between 4 and 16 characters.");;
    QTest::newRow("Good register") << QString("user") << QString("pass")
                                   << QString("Account user successfully created!");
    QTest::newRow("Second register") << QString("user2") << QString("pass2")
                                   << QString("Account user2 successfully created!");;
    QTest::newRow("Already exists") << QString("user") << QString("newpass")
                                    << QString("Account user already exists. Please choose a different name.");
}

void dbtest::testRegisterUser()
{
    QFETCH(QString, username);
    QFETCH(QString, password);
    QFETCH(QString, expected);

    QString result = db->readCommand(QString("register|" + username + "|" + password));

    QCOMPARE(result, expected);
}

void dbtest::testLoginUser_data()
{
    QTest::addColumn<QString>("username");
    QTest::addColumn<QString>("password");
    QTest::addColumn<QString>("expected");

    QTest::newRow("Doesn't exist") << QString("resu") << QString("pass")
                                   << QString("Account resu does not exist. Please register first.");
    QTest::newRow("Incorrect combo") << QString("user") << QString("ssap")
                                     << QString("Incorrect username/password combination. Please try again.");
    QTest::newRow("Correct combo") << QString("user") << QString("pass")
                                   << QString("user has been logged in!");
}

void dbtest::testLoginUser()
{
    QFETCH(QString, username);
    QFETCH(QString, password);
    QFETCH(QString, expected);

    QString result = db->readCommand(QString("login|" + username + "|" + password));

    QCOMPARE(result, expected);
}
