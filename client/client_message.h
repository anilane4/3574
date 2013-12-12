#ifndef CLIENT_MESSAGE_H
#define CLIENT_MESSAGE_H

//#include <QDialog>
#include "dialog.h"
//#include "chatgui.h"

//#include "client.h"

class QDialogButtonBox;
class QLabel;
class QLineEdit;
class QPushButton;
class QNetworkSession;

class client_message : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief client_send_message: public constructor for the client_message() class. Argument sent
     * should be a QString for the client name.
     */
    client_message(QString name);

    /**
     * @brief ~client_send_message: destructor for the clien_message() class
     */
    ~client_message();

    QList<QString> getChatroomList();

    bool signalEmitted();

    Dialog * m_dialog;

signals:
    /**
     * @brief userJoined: signal to be emitted to the chatgui class when a new user joins the chatroom
     * @param username: qstring for the name of the user which joined
     * @param chatroomname: qstring for the name of the chatroom which the user is joining
     */
    void userJoined(QString username, QString chatroomname);

    /**
     * @brief userLeft: signal to be emitted to the chatgui when a user leaves the chatroom
     * @param username qstring for the user which left the chatroom
     * @param chatroomname: qstring for the name of the chatroom which the user is leaving
     */
    void userLeft(QString username, QString chatroomname);

    /**
     * @brief sendMessageToChatGui: signal to be emitted to chatgui when a new message is received
     * @param message: qstring for the message
     */
    void sendMessageToChatGui(QString message);


    /**
     * @brief sendMessagetoServer: method called to send a message to client class.
     * will be responsible for formating the message to include proper header file
     * @param messageToServer: QString containing the actual message to be sent
     */
    void sendMessagetoServer(QString messageToServer);


public slots:
    /**
     * @brief myUserLeft: slot to be called when a chatGUI is closed
     * @param chatroomname: name of the chatroom which was just closed
     */
    void myUserLeft(QString chatroomname);

    /**
     * @brief readMessagefromServer:method called when a message is to be read by the client, will contain the chatroom ID
     * as well as the actual message, and user ID formatted correctly.
     * @param messageFromServer: QString containing the actual message to be sent
     */
    void readMessagefromServer(QString messageFromServer);

private:

    /**
     * @brief launchGUI: method to be called by the client_message constructor which will build a chatroom
     *selection GUI
     */
    void launchGUI();

    /**
     * @brief m_chatroomList: QList containing the list of all of the chatrooms that this client is a member of.
     */
    QList<QString> m_chatroomList;

    /**
     * @brief m_currentMessageRecieved: QString containing the most recently received message for the chatroom
     */
    QString m_currentMessageRecieved;

    /**
     * @brief m_currentMessageSent: QString containing the most recently sent message for the chatroom
     */
    QString m_currentMessageSent;

    /**
     * @brief m_currentMessageSent: QString containing the most recently sent message for the chatroom
     */
    QString m_username;

    bool m_signal;

};


#endif // CLIENT_MESSAGE_H
