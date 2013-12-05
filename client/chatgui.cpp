#include <QtGui>
#include <QtNetwork>

#include "chatgui.h"

ChatGui::ChatGui(QWidget *parent, QString name, QString room)
:   QDialog(parent)
{
    userName = name;
    chatRoom = room;
    message = "";

    inputLineEdit = new QLineEdit;
    messagesTextEdit = new QTextEdit;
    messagesTextEdit->setReadOnly(true);
    participantsTextEdit = new QTextEdit;
    participantsTextEdit->setReadOnly(true);

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(messagesTextEdit, 2, 0, 10, 90);
    mainLayout->addWidget(participantsTextEdit, 2, 91, 10, 20);
    mainLayout->addWidget(inputLineEdit, 12, 0, 1, 111);
    setLayout(mainLayout);

    setWindowTitle(tr(chatRoom.toLatin1().data()));
}

ChatGui::~ChatGui()
{
    emit leaveChatRoom(chatRoom);
}

QString ChatGui::getUserName()
{
    return userName;
}

void ChatGui::setUserName(QString newName)
{
     userName = newName;
}

QString ChatGui::getChatRoom()
{
     return chatRoom;
}

void ChatGui::setChatRoom(QString newRoom)
{
    chatRoom = newRoom;
}

QString ChatGui::getMessage()
{
     return message;
}

void ChatGui::setMessage(QString newMessage)
{
    message = newMessage;
}

QList<QString> ChatGui::getParticipantList()
{
     return listOfMyParticipants;
}


void ChatGui::keyPressEvent(QKeyEvent * event)
{
    if(event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return)
    {
        message = inputLineEdit->text();
        this->encodeMessage();
    }
}

void ChatGui::receiveMessage(const QString &incomingMessage)
{
    this->setMessage(incomingMessage);
    decodeMessage();
}

void ChatGui::addParticipant(const QString &participantName, const QString &chatRoomName)
{
    if(chatRoomName == chatRoom)
    {
        if(listOfMyParticipants.contains(participantName))
            qDebug() << "User is already a participant!";
        else
        {
        listOfMyParticipants.append(participantName);
        participantsTextEdit->setReadOnly(false);
        participantsTextEdit->moveCursor(QTextCursor::End);
        participantsTextEdit->insertPlainText ("<User: " + participantName + ">\n");
        participantsTextEdit->setReadOnly(true);
        }
    }
}

void ChatGui::removeParticipant(const QString &participantName, const QString &chatRoomName)
{
    if(chatRoomName == chatRoom)
    {
        if(!listOfMyParticipants.contains(participantName))
            qDebug() << "User is not a participant!";
        else
        {
        listOfMyParticipants.removeAt(listOfMyParticipants.indexOf(participantName));
        participantsTextEdit->setReadOnly(false);
        participantsTextEdit->clear();
        participantsTextEdit->moveCursor(QTextCursor::End);
        for(int i = 0; i < listOfMyParticipants.length(); i++)
        {
        participantsTextEdit->insertPlainText ("<User: " + listOfMyParticipants.value(i) + ">\n");
        }
        participantsTextEdit->setReadOnly(true);
        }
    }
}

void ChatGui::encodeMessage()
{
    /*
    if(message.at(0) == '/')
    {
        message.remove(0,1);
        if(message.at(0) == 'A' || message.at(0) == 'a')
        {
            message.remove(0,4);
            message = "Added(" + message + ")\n";
        }
        else if(message.at(0) == 'R' || message.at(0) == 'r')
        {
            message.remove(0,7);
            message = "Removed(" + message + ")\n";
        }
        else if(message.at(0) == 'C' || message.at(0) == 'c')
        {
            message.remove(0,9);
            message = "ChatRoom(" + getChatRoom() + ")\n";
        }
        else if(message.at(0) == 'N' || message.at(0) == 'n')
        {
            message.remove(0,5);
            message = "Name(" + getUserName() + ")\n";
        }
        else
        {
            message = "Invalid Command!\n";
        }
    }
    else
    message = "<" + userName + ": " + message + ">\n";
    decodeMessage();
    */
    emit sendMessage(message);
}

void ChatGui::decodeMessage()
{
    messagesTextEdit->setReadOnly(false);
    messagesTextEdit->moveCursor(QTextCursor::End);
    messagesTextEdit->insertPlainText (message);
    messagesTextEdit->setReadOnly(true);
/*
        if(message.at(0) == 'A')
        {
            message = message.remove(0,6);
            message = message.remove(message.indexOf(")"), message.length());
            this->addParticipant(message,chatRoom);
        }
        else if(message.at(0) == 'R')
        {
            message = message.remove(0,8);
            message = message.remove(message.indexOf(")"), message.length());
            this->removeParticipant(message,chatRoom);
        }
        */

}



