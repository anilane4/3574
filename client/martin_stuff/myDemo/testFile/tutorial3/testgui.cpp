/****************************************************************************
**
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Digia Plc and its Subsidiary(-ies) nor the names
**     of its contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

//! [0]
#include <QtGui>
#include <QtTest/QtTest>
#include <QDialog>
//#include <QTcpSocket>
#include <QListView>
//#include"../../3574/newFinal/3574/client/martin_stuff/client.h"
#include"/home/martin/myDemo/testFile/help/client.h"
class TestGui: public QObject
{
    Q_OBJECT

private slots:
    void testRegisterButton();
    void testLoginButton();
    void testLoginVerify();
    void testRegisterVerify();

};
//! [0]

//! [1]
void TestGui::testLoginVerify()
{
    QWidget *parent;
    client *hello= new client(parent);
    QString verify;
    verify = hello->LoginVerify(true);
    QCOMPARE(QString("login good"),verify);
    verify = hello->LoginVerify(false);
    QCOMPARE(QString("login bad"),verify);
}
void TestGui::testRegisterVerify()
{
    QWidget *parent;
    client *hello= new client(parent);
    QString verify;
    verify = hello->registerVerify(true);
    QCOMPARE(QString("register good"),verify);
    verify = hello->registerVerify(false);
    QCOMPARE(QString("register bad"),verify);
}

void TestGui::testRegisterButton()
{
    //QLineEdit lineEdit;
    QWidget *parent;
    client *hello= new client(parent);
    QString help;

    QTest::keyClicks(hello->usernameLineEdit, "hello");
    QTest::keyClicks(hello->passwordLineEdit, "world");
    QTest::mouseClick(hello->registerButton,Qt::LeftButton);
    help = hello->getInformation();

    QCOMPARE(QString("register hello world"), help);
    QTest::keyClick(hello->usernameLineEdit, Qt::Key_Backspace);
    QTest::keyClick(hello->passwordLineEdit, Qt::Key_Backspace);
    QTest::keyClick(hello->usernameLineEdit, Qt::Key_Backspace);
    QTest::keyClick(hello->passwordLineEdit, Qt::Key_Backspace);
    QTest::keyClick(hello->usernameLineEdit, Qt::Key_Backspace);
    QTest::keyClick(hello->passwordLineEdit, Qt::Key_Backspace);
    QTest::keyClick(hello->usernameLineEdit, Qt::Key_Backspace);
    QTest::keyClick(hello->passwordLineEdit, Qt::Key_Backspace);
    QTest::keyClick(hello->usernameLineEdit, Qt::Key_Backspace);
    QTest::keyClick(hello->passwordLineEdit, Qt::Key_Backspace);
    QTest::keyClick(hello->usernameLineEdit, Qt::Key_Backspace);
    QTest::keyClick(hello->passwordLineEdit, Qt::Key_Backspace);
    QTest::keyClick(hello->usernameLineEdit, Qt::Key_Backspace);
    QTest::keyClick(hello->passwordLineEdit, Qt::Key_Backspace);

    QTest::keyClicks(hello->usernameLineEdit, "test");
    QTest::keyClicks(hello->passwordLineEdit, "WORLD");
    QTest::mouseClick(hello->registerButton,Qt::LeftButton);
    help = hello->getInformation();

    QCOMPARE(QString("register test WORLD"), help);

    QTest::keyClick(hello->usernameLineEdit, Qt::Key_Backspace);
    QTest::keyClick(hello->passwordLineEdit, Qt::Key_Backspace);
    QTest::keyClick(hello->usernameLineEdit, Qt::Key_Backspace);
    QTest::keyClick(hello->passwordLineEdit, Qt::Key_Backspace);
    QTest::keyClick(hello->usernameLineEdit, Qt::Key_Backspace);
    QTest::keyClick(hello->passwordLineEdit, Qt::Key_Backspace);
    QTest::keyClick(hello->usernameLineEdit, Qt::Key_Backspace);
    QTest::keyClick(hello->passwordLineEdit, Qt::Key_Backspace);
    QTest::keyClick(hello->usernameLineEdit, Qt::Key_Backspace);
    QTest::keyClick(hello->passwordLineEdit, Qt::Key_Backspace);
    QTest::keyClick(hello->usernameLineEdit, Qt::Key_Backspace);
    QTest::keyClick(hello->passwordLineEdit, Qt::Key_Backspace);
    QTest::keyClick(hello->usernameLineEdit, Qt::Key_Backspace);
    QTest::keyClick(hello->passwordLineEdit, Qt::Key_Backspace);

    QTest::keyClicks(hello->usernameLineEdit, "HeLLo");
    QTest::keyClicks(hello->passwordLineEdit, "HAHAHAHmwha");
    QTest::mouseClick(hello->registerButton,Qt::LeftButton);
    help = hello->getInformation();

    QCOMPARE(QString("register HeLLo HAHAHAHmwha"), help);
}

void TestGui::testLoginButton()
{
    //QLineEdit lineEdit;
    QWidget *parent;
    client *hello= new client(parent);
    QString help;

    QTest::keyClicks(hello->usernameLineEdit, "hello");
    QTest::keyClicks(hello->passwordLineEdit, "world");
    QTest::mouseClick(hello->loginButton,Qt::LeftButton);
    help = hello->getInformation();

    QCOMPARE(QString("login hello world"), help);
    QTest::keyClick(hello->usernameLineEdit, Qt::Key_Backspace);
    QTest::keyClick(hello->passwordLineEdit, Qt::Key_Backspace);
    QTest::keyClick(hello->usernameLineEdit, Qt::Key_Backspace);
    QTest::keyClick(hello->passwordLineEdit, Qt::Key_Backspace);
    QTest::keyClick(hello->usernameLineEdit, Qt::Key_Backspace);
    QTest::keyClick(hello->passwordLineEdit, Qt::Key_Backspace);
    QTest::keyClick(hello->usernameLineEdit, Qt::Key_Backspace);
    QTest::keyClick(hello->passwordLineEdit, Qt::Key_Backspace);
    QTest::keyClick(hello->usernameLineEdit, Qt::Key_Backspace);
    QTest::keyClick(hello->passwordLineEdit, Qt::Key_Backspace);
    QTest::keyClick(hello->usernameLineEdit, Qt::Key_Backspace);
    QTest::keyClick(hello->passwordLineEdit, Qt::Key_Backspace);
    QTest::keyClick(hello->usernameLineEdit, Qt::Key_Backspace);
    QTest::keyClick(hello->passwordLineEdit, Qt::Key_Backspace);

    QTest::keyClicks(hello->usernameLineEdit, "test");
    QTest::keyClicks(hello->passwordLineEdit, "WORLD");
    QTest::mouseClick(hello->loginButton,Qt::LeftButton);
    help = hello->getInformation();

    QCOMPARE(QString("login test WORLD"), help);

    QTest::keyClick(hello->usernameLineEdit, Qt::Key_Backspace);
    QTest::keyClick(hello->passwordLineEdit, Qt::Key_Backspace);
    QTest::keyClick(hello->usernameLineEdit, Qt::Key_Backspace);
    QTest::keyClick(hello->passwordLineEdit, Qt::Key_Backspace);
    QTest::keyClick(hello->usernameLineEdit, Qt::Key_Backspace);
    QTest::keyClick(hello->passwordLineEdit, Qt::Key_Backspace);
    QTest::keyClick(hello->usernameLineEdit, Qt::Key_Backspace);
    QTest::keyClick(hello->passwordLineEdit, Qt::Key_Backspace);
    QTest::keyClick(hello->usernameLineEdit, Qt::Key_Backspace);
    QTest::keyClick(hello->passwordLineEdit, Qt::Key_Backspace);
    QTest::keyClick(hello->usernameLineEdit, Qt::Key_Backspace);
    QTest::keyClick(hello->passwordLineEdit, Qt::Key_Backspace);
    QTest::keyClick(hello->usernameLineEdit, Qt::Key_Backspace);
    QTest::keyClick(hello->passwordLineEdit, Qt::Key_Backspace);

    QTest::keyClicks(hello->usernameLineEdit, "HeLLo");
    QTest::keyClicks(hello->passwordLineEdit, "HAHAHAHmwha");
    QTest::mouseClick(hello->loginButton,Qt::LeftButton);
    help = hello->getInformation();

    QCOMPARE(QString("login HeLLo HAHAHAHmwha"), help);
}
//! [1]

//! [2]
QTEST_MAIN(TestGui)
#include "testgui.moc"
//! [2]
