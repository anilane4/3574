#include "session.h"

Session::Session(QTcpSocket *socket, UserDB *userdb, QList<QString> *chatlist) :
    m_socket(socket), m_userdb(userdb), m_chatlist(chatlist)
{
    loggedIn = false;
    m_name = "New session";
}

Session::~Session()
{
    for (int i = 0; i < m_chatrooms.size(); i++)
        emit broadcastMessage("room|remove|" + m_chatrooms.at(i) + "|" + m_name);
    emit disconnecting(m_name);
}

void Session::readSocket()
{
    Q_ASSERT(QObject::thread() == QThread::currentThread());
    QByteArray requestArray;
    requestArray = m_socket->readAll();

    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_0);
    out << (quint16)0;
    out << readRequest(QString(requestArray));
    out.device()->seek(0);
    out << (quint16)(block.size() - sizeof(quint16));

    m_socket->write(block);
}

void Session::receiveMessage(QString message)
{
    qDebug() << m_name << " has recieved " << message;
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_0);
    out << (quint16)0;
    out << message;
    out.device()->seek(0);
    out << (quint16)(block.size() - sizeof(quint16));

    m_socket->write(block);
}

QString Session::readRequest(QString request)
{
    qDebug()<<"hey";
    qDebug()<<request;
    QStringList list = request.split('|', QString::SkipEmptyParts);
    qDebug()<<list;
    QString command = list.first();
    if (!QString::compare(command, "requestList", Qt::CaseInsensitive))
            return requestChatList();

    if (list.size() < 3) return QString("ERROR: Command not recognized. Please try again.");

    if (!QString::compare(command, "user", Qt::CaseInsensitive))
        return handleUserCommand(request.remove(0, 5));
    else if (!QString::compare(command, "chat", Qt::CaseInsensitive))
        return sendChatMessage(request.remove(0, 5));
    else if (!QString::compare(command, "room", Qt::CaseInsensitive)) {
        if (!QString::compare(list.at(1), "create", Qt::CaseInsensitive))
            return createChatRoom(request.remove(0, 12));
        else if (!QString::compare(list.at(1), "join", Qt::CaseInsensitive))
            return joinChatRoom(request.remove(0, 10));
        else if (!QString::compare(list.at(1), "leave", Qt::CaseInsensitive))
            return leaveChatRoom(request.remove(0, 11));
        else
            return QString("ERROR: Command not recognized. Please try again.");
    }

    return QString("ERROR: Command not recognized. Please try again.");
}

QString Session::handleUserCommand(QString command)
{
    if (loggedIn) return QString(m_name + " is already logged in.");

    QString result = m_userdb->readCommand(command);
    if (result.contains(QString(" has been logged in!"))) {
        loggedIn = true;
        m_name = result.replace(" has been logged in!", "");
        return result + " has been logged in!";
    }

    return result;
}

QString Session::createChatRoom(QString roomName)
{
    if (!loggedIn) return QString("You must login before using chat commands!");

    if (m_chatlist->contains(roomName))
        return QString(roomName + " already exists!");

    m_chatlist->append(roomName);
    emit broadcastMessage("requestList");
    return QString("Creating room " + roomName);
}

QString Session::joinChatRoom(QString roomName)
{
    if (!loggedIn) return QString("You must login before using chat commands!");

    if (!m_chatlist->contains(roomName))
        return QString(roomName + " does not exist!");

    if (m_chatrooms.contains(roomName))
        return QString(m_name + " is already in " + roomName);

    m_chatrooms.append(roomName);
    emit broadcastMessage(QString("room|join|" + roomName + "|" + m_name));
    return QString(m_name + " has joined the chat room " + roomName);
}

QString Session::leaveChatRoom(QString roomName)
{
    if (!loggedIn) return QString("You must login before using chat commands!");

    if (!m_chatlist->contains(roomName))
        return QString(roomName + " does not exist!");

    if (!m_chatrooms.contains(roomName))
        return QString(m_name + " is not in the chat room " + roomName);

    m_chatrooms.removeOne(roomName);
    emit broadcastMessage(QString("room|remove|" + roomName + "|" + m_name));
    return QString(m_name + " has left room " + roomName);
}

QString Session::sendChatMessage(QString message)
{
    if (!loggedIn) return QString("You must login before using chat commands!");

    QStringList list = message.split('|', QString::SkipEmptyParts);
    QString room = list.first();
    QString text = list.last();

    if (!m_chatlist->contains(room))
        return QString(room + " does not exist!");

    if (!m_chatrooms.contains(room))
        return QString(m_name + " is not in " + room);

    emit broadcastMessage(QString("chat|" + room + "|" + m_name + "|" + text));
    return QString("Sending chat " + text);
}

QString Session::requestChatList()
{
    if (!loggedIn) return QString("You must login before using chat commands!");

    QString result;
    for (int i = 0; i < m_chatlist->size(); i++)
        result.append(m_chatlist->at(i) + " ");

    return QString("room|list|" + result);
}

QString Session::sendTestMessage(QString message) { return readRequest(message); }
void Session::clearDB() { m_userdb->clearDB(); }
