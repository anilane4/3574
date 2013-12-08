#include "client_message.h"
#include <QDebug>

client_message::client_message(QString name)
{
    m_username = name;
    m_dialog = new Dialog(name);

    m_signal = false;
    emit(sendMessagetoServer("requestList"));

}

client_message::~client_message()
{

}

bool client_message::signalEmitted()
{
    return m_signal;
}

QList<QString> client_message::getChatroomList()
{
    return m_chatroomList;
}

void client_message::myUserLeft(QString chatroomname)
{
    m_signal = true;
    //emit(sendMessagetoServer("userleft|" + chatroomname + "|" + m_username));
    emit(sendMessagetoServer("userleft|" + m_username  + "|" + chatroomname));
}

void client_message::readMessagefromServer(QString messageFromServer)
{
    QStringList server_message = messageFromServer.split("|");
    if(server_message[0] == "message")
    {
        qDebug() << "Message:";
        qDebug() << " chatroom name:" << server_message[1] << " user ID:"
                 << server_message[2] << " message text:" << server_message[3];
        m_signal = true;
        emit(sendMessageToChatGui(messageFromServer));
    }
    else if(server_message[1] == "list")
    {
        qDebug() << "Chat Room Update:";

        for(int i = 2; i < server_message.size(); i++)
        {
            qDebug() << " " << server_message[i];
            if( !(m_chatroomList.contains(server_message[i]) ) )
            {
                (*m_dialog).addChatroom(server_message[i]);
                m_chatroomList.append(server_message[i]);
            }
        }
    }
    else if(server_message[1] == "joined")
    {
        qDebug() << "Userjoined:";
        qDebug() << "  chatroom ID:" <<server_message[2] << " name:" << server_message[3];
        m_signal = true;
        emit(userJoined(server_message[2], server_message[3]));
    }
    else if(server_message[1] == "userleft")
    {
        qDebug() << "Userleft:";
        qDebug() << "  chatroom ID:" <<server_message[2] << " name:" << server_message[3];
        m_signal = true;
        emit(userJoined(server_message[2], server_message[3]));
    }
    else
    {
        qDebug() << "invalid message";
    }

}
