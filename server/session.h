#ifndef CLIENTESSION_H
#define CLIENTESSION_H

#include <QObject>
#include <QTcpSocket>
#include <QThread>
#include <QStringList>
#include  "userdb.h"

/**
 * @brief The Session class Represents a client session with the server. Class stores
 * pointers to all of the data structures the server will need to properly service a
 * client connection.
 */
class Session : public QObject
{
Q_OBJECT
public:
    /**
     * @brief Session Constructor. Set the pointers to all of the pertinent data structures.
     * @param socket The socket the client is connected over.
     * @param userdb The interface to the user database.
     */
    Session(QTcpSocket *socket, UserDB *userdb);
public slots:
    /**
     * @brief readSocket Read the data on the socket and call the appropriate helper function
     * to handle the data. Data on the socket should follow the structure: <message type> [data]
     * where <message type> is the type of message; user, chatlist, chat and [data] is the data
     * of the message.
     */
    void readSocket();
    /**
     * @brief receiveMessage This slot is connected to the servers broadcastAll signal. It will
     * receive all chat messages being sent through the server and will only handle messages
     * relevant to this session (all messages to chatrooms that this session is in).
     * @param message The message being sent across the server.
     */
    void receiveMessage(QString message);

signals:
    /**
     * @brief broadcastMessage This signal is emitted when a chat message is sent from the client.
     * It gets connected to the server broadcast slot.
     * @param message The message to be sent to the other sessions.
     */
    broadcastMessage(QString message);
    /**
     * @brief createNewRoom This signal is emitted when the client requests to create a new chat room.
     * It is connected to the server's updateChatList() slot.
     * @param roomName The name of the room to create.
     */
    createNewRoom(QString roomName);
    /**
     * @brief disconnecting This signal is called during the deconstructor. It is used to notify
     * the server that this session is terminating.
     * @param name The name associated with this session.
     */
    disconnecting(QString name);
private:
    /**
     * @brief readRequest Reads and parses the request sent from the client.
     * @param request A QString containing the request.
     * @return The result of the request.
     */
    QString readRequest(QString request);
    /**
     * @brief createChatRoom Creates a new chat room via emitting createNewRoom.
     * @param roomName The name of the room to create.
     * @return A success/error message.
     */
    QString createChatRoom(QString roomName);
    /**
     * @brief joinChatRoom Join the specified chat room.
     * Emits broadcastMessage to update other sessions that this session joined
     * the room.
     * @param roomName The name of the chat room to join.
     * @return A success/error message.
     */
    QString joinChatRoom(QString roomName);
    /**
     * @brief leaveChatRoom Leave the specified chat room.
     * Emits broadcastMessage to update other sessions that this session left
     * the room.
     * @param roomName The name of the chat room to leave.
     * @return A success/error message.
     */
    QString leaveChatRoom(QString roomName);
    /**
     * @brief sendChatMessage Send a chat message to the specified chat room.
     * Emits broadcastMessage to send the message to the other sessions.
     * @param message The message to send.
     * @return A success/error message.
     */
    QString sendChatMessage(QString message);

    /**
     * @brief m_name The username of the client associated with this session.
     */
    QString m_name;
    /**
     * @brief m_socket The socket connecting the server to the client.
     */
    QTcpSocket *m_socket;
    /**
     * @brief m_userdb A pointer to the user database interface object.
     */
    UserDB *m_userdb;
    /**
     * @brief loggedIn This is a lock that represents if the user is logged into the server
     * or not.
     */
    bool loggedIn;
    /**
     * @brief m_chatrooms A list of chat rooms this client is currently in.
     */
    QList<QString> m_chatrooms;
};

#endif // CLIENTESSION_H
