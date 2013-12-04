#include "sessiontest.h"

void sessiontest::initTestCase()
{
    session = new Session(new QTcpSocket(), new UserDB(), new QList<QString>);
}

void sessiontest::cleanupTestCase()
{
    session->clearDB();
}

void sessiontest::testUserCommand_data()
{
    QTest::addColumn<QString>("command");
    QTest::addColumn<QString>("expected");

    QTest::newRow("Short command") << QString("user|register|")
                                   << QString("ERROR: Command not recognized. Please try again.");
    QTest::newRow("Valid Register") << QString("user|register|user|pass")
                                    << QString("Account user successfully created!");
    QTest::newRow("Valid login") << QString("user|login|user|pass")
                                 << QString("user has been logged in!");
    QTest::newRow("Already logged in") << QString("user|login|user|pass")
                                       << QString("user is already logged in.");
}

void sessiontest::testUserCommand()
{
    QFETCH(QString, command);
    QFETCH(QString, expected);

    QCOMPARE(session->sendTestMessage(command), expected);
}

void sessiontest::testRoomCommand_data()
{
    QTest::addColumn<QString>("command");
    QTest::addColumn<QString>("expected");

    QTest::newRow("Join nonexistent") << QString("room|join|room1")
                                      << QString("room1 does not exist!");
    QTest::newRow("Leave nonexistent") << QString("room|leave|room1")
                                       << QString("room1 does not exist!");
    QTest::newRow("Create room1") << QString("room|create|room1")
                                  << QString("Creating room room1");
    QTest::newRow("Create room1 again") << QString("room|create|room1")
                                        << QString("room1 already exists!");
    QTest::newRow("Join room1") << QString("room|join|room1")
                                << QString("user has joined the chat room room1");
    QTest::newRow("Join room1 again") << QString("room|join|room1")
                                      << QString("user is already in room1");
    QTest::newRow("Leave room1") << QString("room|leave|room1")
                                 << QString("user has left room room1");
    QTest::newRow("Leave room1 again") << QString("room|leave|room1")
                                       << QString("user is not in the chat room room1");
    QTest::newRow("Rejoin room1") << QString("room|join|room1")
                                  << QString("user has joined the chat room room1");
    QTest::newRow("Create room2") << QString("room|create|room2")
                                 << QString("Creating room room2");
}

void sessiontest::testRoomCommand()
{
    QFETCH(QString, command);
    QFETCH(QString, expected);

    QCOMPARE(session->sendTestMessage(command), expected);
}
void sessiontest::testChatCommand_data()
{
    QTest::addColumn<QString>("command");
    QTest::addColumn<QString>("expected");

    QTest::newRow("Room nonexistent") << QString("chat|moor|hello moor")
                                      << QString("moor does not exist!");
    QTest::newRow("User not in room") << QString("chat|room2|hello room2")
                                      << QString("user is not in room2");
    QTest::newRow("Send chat") << QString("chat|room1|hello room1")
                               << QString("Sending chat hello room1");
}

void sessiontest::testChatCommand()
{
    QFETCH(QString, command);
    QFETCH(QString, expected);

    QCOMPARE(session->sendTestMessage(command), expected);
}

void sessiontest::testRequestChatList()
{
    QCOMPARE(session->sendTestMessage("requestList"), QString("room|list|room1 room2 "));
    session->sendTestMessage(QString("room|create|room3"));
    QCOMPARE(session->sendTestMessage("requestList"), QString("room|list|room1 room2 room3 "));
}
