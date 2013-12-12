#ifndef CLIENT_H
#define CLIENT_H

#include <QDialog>
#include <QTcpSocket>
#include <QListView>
// For Qt 5
#include <QtWidgets>
// For QT 4
//#include <QtGui/QApplication>
//#include <QtGui/QWidget>


QT_BEGIN_NAMESPACE
class QDialogButtonBox;
class QLabel;
class QLineEdit;
class QPushButton;
class QTextEdit;
class QTcpSocket;
class QNetworkSession;
QT_END_NAMESPACE

//! [0]
class client : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Client When a client is first made teh login screen will
     * first appear
     * @param parent It takes a parameter of QWidget parent to initalize the
     * gui
     */
    client(QWidget *parent = 0);
    /**
     * @brief getInformation This function is for testing purposes
     * to verify that the correct information is getting sent to the server
     * @return It returns the information that was last sent
     */
    QString getInformation();
    /**
     * @brief LoginVerify a function so tell when the login information is correct or not
     * @param login passes in a bool for true or false
     * @return  it returns a message saying that it has either pass or failed
     */
    QString LoginVerify(bool login);
    /**
     * @brief registerVerify simliar function to login except it is for register
     * @param registers passes in a bool
     * @return  it returns a message saying that it has either pass or failed
     */
    QString registerVerify(bool registers);
    /**
     * @brief sendClientMessageCommand This method is for when the the message clent needs to send message to the client message
     * @param command is the message it will send
     */
    void sendClientMessageCommand(QString allTogether);
    //~client();

public slots:

    //for final
    /**
     * @brief sendLogin Slot to send the information to the server when a the login
     * button is pressed
     */
    void sendLogin();
    /**
     * @brief sendRegister Slot to send the information to the server when the register
     * button is pressed
     */
    void sendRegister();
    /**
     * @brief readServerResponse Get back what the server send to show it on the gui
     */
    void readServerResponse();
    /**
     * @brief displayError Slot for if there was a problem with connecting a socket
     * @param socketError
     */
    void displayError(QAbstractSocket::SocketError socketError);
    /**
     * @brief enableStartConnectionButton Slot for helping connect to a socket
     */
    void enableStartConnectionButton();
    /**
     * @brief sessionOpened Slot for opening a socket
     */
    void sessionOpened();
    /**
     * @brief sendCommand when a button is pressed on the login screen it will send the command to the
     * server
     */
    void sendCommand();


    // test
    void startButton();
        void startSession();
        void startConnection();
        void getServer();




private:



    // for final
    /**
     * @brief serverResponseLabel Label for the server response
     */
    QLabel *serverResponseLabel;
    /**
     * @brief hostLabel Label for the knowing the IP
     */
    QLabel *hostLabel;
    /**
     * @brief usernameLabel labe for the username
     */
    QLabel *usernameLabel;
    /**
     * @brief passwordLabel label for the password
     */
    QLabel *passwordLabel;

    /**
     * @brief listChatLabel Label for the list of chat rooms
     */
    QLabel *listChatLabel;
    /**
     * @brief createChatLabel label for the create chat label
     */
    QLabel *createChatLabel;

    /**
     * @brief hostLineEdit Able to write ip in the line
     */
    QLineEdit *hostLineEdit;
    /**
     * @brief usernameLineEdit able to write username into the line
     */
    QLineEdit *usernameLineEdit;
    /**
     * @brief passwordLineEdit able to write password into the line
     */
    QLineEdit *passwordLineEdit;
    /**
     * @brief serverResponseTextEdit allows the server to respond
     */
    QTextEdit *serverResponseTextEdit;
    /**
     * @brief networkSession set up a network
     */
    QNetworkSession *networkSession;

    /**
     * @brief loginButton create a login button
     */
    QPushButton *loginButton;
    /**
     * @brief registerButton creates a register button
     */
    QPushButton *registerButton;
    /**
     * @brief buttonBox creates a button box for the gui
     */
    QDialogButtonBox *buttonBox;
    /**
     * @brief m_blockSize a block size for the gui
     */
    quint16 m_blockSize;
    /**
     * @brief tcpSocket sockets for the client/server
     */
    QTcpSocket *tcpSocket;
    /**
     * @brief m_loginConfirmed a varible for when the user login information is correct
     */
    bool m_loginConfirmed;
    /**
     * @brief m_registerConfirmed a varible for when the user register is correct or not
     */
    bool m_registerConfirmed;
    /**
     * @brief m_information Stores the information being sent
     */
    QString m_information;
    /**
     * @brief m_name A private variable to store the username
     */
    QString m_username;
    // for martin test
    QString currentCommand;
    // this is for local connection for the server note this will get remove when the project is together
    QLabel *serverLabel;
    QLabel *portLabel;
    QLineEdit *serverLineEdit;
    QLineEdit *portLineEdit;
    QLineEdit *commandEdit;
    QLabel *messageLabel;
    QPushButton *connectionButton;
    QPushButton *sendButton;
    QPushButton *quitButton;
    QLabel *enterCommaneLabel;

};
//! [0]

#endif
