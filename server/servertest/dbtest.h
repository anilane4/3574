#ifndef DBTEST_H
#define DBTEST_H

#include <QtTest>
#include <QSql>
#include <QString>
#include "../userdb.h"

class dbtest : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void cleanupTestCase();
    void testNewObject();
    void testRegisterUser_data();
    void testRegisterUser();
    void testLoginUser_data();
    void testLoginUser();

private:
    UserDB *db;
};

#endif // DBTEST_H
