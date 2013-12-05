#ifndef SERVER_H
#define SERVER_H

#include <QDialog>

#include <QTcpSocket>
//#include <QtWidgets>
#include <QtGui>
#include <QtNetwork>
#include <QtGui/QApplication>
#include <stdlib.h>

//For QT 5
//#include <QtWidgets>

// For QT 4
#include <QtGui/QApplication>
#include <QtGui/QWidget>

#include "userdb.h"
#include "session.h"

#define PORT 41230
#define IP_ADDRESS "192.168.153.192"

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
    void broadcastAll(QString message);
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
     * @param sessionName The name of the disconnecting session.
     */
    void sessionDisconnected(QString sessionName);
private:
    QLabel *statusLabel;
    QPushButton *quitButton;
    QTcpServer *tcpServer;
    QNetworkSession *networkSession;
    UserDB *userDB;
    QList<QString> *chatroomList;
};

#endif // SERVER_H
