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
    Session(QTcpSocket *socket, UserDB *userdb, QList<QString> *chatlist);
    /**
     * @brief ~Session. Deconstructor. Emits the diconnecting signal.
     */
    ~Session();
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
    /**
     * @brief sendTestMessage TESTING. Method used for testing helper methods.
     * @param message The message to test.
     */
    QString sendTestMessage(QString message);
    /**
     * @brief clearDB TESTING. Used in testing to clear the database.
     */
    void clearDB();
signals:
    /**
     * @brief broadcastMessage This signal is emitted when a chat message is sent from the client.
     * It gets connected to the server broadcast slot.
     * @param message The message to be sent to the other sessions.
     */
    void broadcastMessage(QString message);
    /**
     * @brief disconnecting This signal is called during the deconstructor. It is used to notify
     * the server that this session is terminating.
     * @param name The name associated with this session.
     */
    void disconnecting(QString name);
private:
    /**
     * @brief readRequest Reads and parses the request sent from the client.
     * Possible request formats
     * user|register|name|password
     * user|login|name|password
     *
     * chat|room|text
     *
     * room|create|roomname
     * room|join|roomname
     * room|leave|roomname
     *
     * requestList
     *
     * @param request A QString containing the request.
     * @return The result of the request.
     */
    QString readRequest(QString request);
    /**
     * @brief handleUserCommand Parses and executes the given command. These commands are
     * specific to a user logging in or registering.
     * @param command The user command to execute.
     * @return A message with the results of the command.
     */
    QString handleUserCommand(QString command);
    /**
     * @brief createChatRoom Creates a new chat room via emitting createNewRoom.
     * Note that is not a critical section. Sessions only add to the list so there
     * is no need to wrap this method in a mutex.
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
     * @brief requestChatList Request a list of all chat rooms from the server.
     * @return A success/error message.
     */
    QString requestChatList();
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
    /**
     * @brief m_chatlist A pointer to the chat room list the server has.
     */
    QList<QString> *m_chatlist;
};

#endif // CLIENTESSION_H
