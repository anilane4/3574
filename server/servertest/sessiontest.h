#ifndef SESSIONTEST_H
#define SESSIONTEST_H

#include <QtTest>
#include <QString>
#include "../session.h"

class sessiontest : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void cleanupTestCase();
    void testUserCommand_data();
    void testUserCommand();
    void testRoomCommand_data();
    void testRoomCommand();
    void testChatCommand_data();
    void testChatCommand();
    void testRequestChatList();

private:
    Session *session;
};

#endif // SESSIONTEST_H
