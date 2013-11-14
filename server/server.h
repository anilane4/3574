#ifndef SERVER_H
#define SERVER_H

#include <QDialog>
#include <QTcpSocket>
#include <QtWidgets>
#include <QtNetwork>
#include <stdlib.h>

#include "userdb.h"
#include "session.h"

class QLabel;
class QPushButton;
class QTcpServer;
class QNetworkSession;

/**
 * @brief The Server class accepts connections and will service requests for
 * chat functions. Connections each receive their Session and are placed into
 * their own thread. Further communication with existing clients is handled in
 * the Session class.
 */
class Server : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Server Constructor Initializes everything necessary for the server
     * GUI and accepting connections.
     * @param parent The parent object of this server.
     */
    Server(QWidget *parent = 0);
    ~Server();

signals:
    /**
     * @brief broadcastAll This signal broadcasts a chat message to all connected sessions.
     * It is connected to every session's receiveMessage slot. It is emitted in the broadcast slot.
     * @param message The message to be sent to the sessions.
     */
    broadcastAll(QString message);
private slots:
    /**
     * @brief sessionOpened Opens a new session with a client.
     */
    void sessionOpened();
    /**
     * @brief serviceClient This sets up the connection with a client.
     */
    void serviceClient();
    /**
     * @brief broadcast This slot is connected to each session's broadcastMessage signal. All the
     * slot does is emit broadcastAll to send the message to all of the connected sessions.
     * @param message The message sent by a session.
     */
    void broadcast(QString message);
    /**
     * @brief sessionDisconnected This slot is connected to every session's disconnecting() signal.
     * The slot will emit broadcastAll() for each chatroom the sessionName was in, telling other sessions
     * to remove sessionName from their chatrooms.
     * @param sessionName The name of the disconnecting session.
     * @param chatrooms A list of all the chatrooms the session was a part of.
     */
    void sessionDisconnected(QString sessionName, QString chatrooms);
    /**
     * @brief updateChatList This slot is connected to each session's updateChatList() signal.
     * newRoom is added to the list of chatroom names. Emits broadcastAll to update sessions on
     * the new room.
     * @param newRoom The name of the new chatroom.
     */
    void updateChatList(QString newRoom);
private:
    QLabel *statusLabel;
    QPushButton *quitButton;
    QTcpServer *tcpServer;
    QNetworkSession *networkSession;
    UserDB *gateDB;
    QList<QString> *chatroomList;
};
