/****************************************************************************
**
** Copyright (C) 2012 Nokia Corporation and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/
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
**   * Neither the name of Nokia Corporation and its Subsidiary(-ies) nor
**     the names of its contributors may be used to endorse or promote
**     products derived from this software without specific prior written
**     permission.
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

#include <QtGui>

#include "dialog.h"

//! [0]
Dialog::Dialog(QString name)
{
    pressedChatroom = "";
    mainLayout = new QVBoxLayout;
    m_username = name;
    m_layout = new QGridLayout;
    m_layout_2 = new QFormLayout;

    new_chatroom_name = new QLineEdit;

    m_layout_2->addRow(new QLabel("Enter New Chatroom Name"), new_chatroom_name);
    enter_chatroom = new QPushButton("Enter Chatroom");
    m_layout_2->addRow(enter_chatroom);
    connect(enter_chatroom, SIGNAL(clicked()), this, SLOT(entering_chatroom()));
    //m_layout_2->addRow();


    //layout()->removeItem(mainLayout);

    if (layout() != 0)
    {
    QLayoutItem *item;
    while ((item = (layout())->takeAt(0)) != 0)
        layout()->removeItem (item);
    delete layout();
    }


    mainLayout = new QVBoxLayout;

    createMenu();
    gridGroupBox = new QGroupBox(tr("Select Existing Chatroom or Create a new one"));
    horizontalGroupBox = new QGroupBox(tr("Select or Create a chatroom and press Enter Chatroom"));
    //createHorizontalGroupBox();

    createHorizontalGroupBox();
    createGridGroupBox();
    createFormGroupBox();


    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok
                                     | QDialogButtonBox::Cancel);

    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

    mainLayout->setMenuBar(menuBar);

    mainLayout->addWidget(horizontalGroupBox);
    mainLayout->addWidget(gridGroupBox);
    mainLayout->addWidget(formGroupBox);
    //mainLayout->addWidget(buttonBox);

    //setLayout


    setWindowTitle("Welcome, " + m_username);
    setLayout(mainLayout);

    this->repaint();
    this->update();
    this->show();



}

void Dialog::entering_chatroom()
{
    QString newRoom = new_chatroom_name->text();
    if(newRoom != "")
    {

        new_chatroom_name->clear();
        addChatroom(newRoom);
        launchGui(newRoom);
        pressedChatroom = "";

    }
    else if(pressedChatroom != "")
    {
        //addChatroom(pressedChatroom);
        launchGui(pressedChatroom);


        pressedChatroom = "";
    }
}


void Dialog::createMenu()
{
    menuBar = new QMenuBar;

    fileMenu = new QMenu(tr("&File"), this);
    exitAction = fileMenu->addAction(tr("E&xit"));
    menuBar->addMenu(fileMenu);

    connect(exitAction, SIGNAL(triggered()), this, SLOT(accept()));
}


void Dialog::createHorizontalGroupBox()
{

    QHBoxLayout *layout = new QHBoxLayout;
    horizontalGroupBox->setLayout(layout);
}


void Dialog::createGridGroupBox()
{


    gridGroupBox = new QGroupBox();


    for(int i = 0; i < m_chatroomList.size(); i++)
    {
        if(i == 0)
            pressedChatroom = m_chatroomList[i];
        m_layout->addWidget(m_buttonMap[m_chatroomList[i]], i/6, i%6);
        connect(m_buttonMap[m_chatroomList[i]], SIGNAL(pressed()), this, SLOT(roomSelected()));
    }
    gridGroupBox->setLayout(m_layout);
    mainLayout->removeItem(m_layout);
}

void Dialog::roomSelected()
{
    //qDebug() << "button was pressed:";
    for(int i = 0; i < m_chatroomList.size(); i++)
    {
        if(m_buttonMap[m_chatroomList[i]]->hasFocus())
            pressedChatroom = m_chatroomList[i];
    }
    if(pressedChatroom == "")
        qDebug() << "didn't register button press";
}


void Dialog::createFormGroupBox()
{

    formGroupBox = new QGroupBox();


    formGroupBox->setLayout(m_layout_2);
    mainLayout->removeItem(m_layout_2);
}






void Dialog::updateChatrooms()
{
    pressedChatroom = "";
    if (layout() != 0)
    {
    QLayoutItem *item;
    while ((item = (layout())->takeAt(0)) != 0)
        layout()->removeItem (item);
    delete layout();
    }

    mainLayout = new QVBoxLayout;


    createMenu();
    //horizontalGroupBox = new QGroupBox(tr("Horizontal layout"));
    //createHorizontalGroupBox();


    createGridGroupBox();
    createFormGroupBox();


    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok
                                     | QDialogButtonBox::Cancel);

    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));



    mainLayout->setMenuBar(menuBar);

    mainLayout->addWidget(gridGroupBox);
    mainLayout->addWidget(formGroupBox);
    //mainLayout->addWidget(buttonBox);

    //setLayout


    setWindowTitle("Welcome, " + m_username);
    setLayout(mainLayout);
}

void Dialog::addChatroom(QString newChatroom)
{
    QPushButton * temp = new QPushButton(newChatroom);
    qDebug() <<  "here";
    if(m_chatroomList.contains(newChatroom))
        return;
    m_buttonMap.insert(newChatroom, temp);
    m_chatroomList.append(newChatroom);
    updateChatrooms();


}

void Dialog::launchGui(QString chatroomname)
{
    if(m_currentChatrooms.contains(chatroomname))
        return;
    else
        m_currentChatrooms.append(chatroomname);

    //QString name and qstring room

    QDialog * newDialog = new QDialog;

    //connect signals and slots
    QThread * newThread = new QThread;
    QObject * dummyParent = new QObject;
    QPushButton * hello = new QPushButton();
    newDialog->moveToThread(newThread);
    newThread->start();
    qDebug() << "Chatroom " + chatroomname + " started in " << (newThread);
    hello->setText("Chatroom: " + chatroomname);
    hello->resize(130,100);
    hello->show();
}
