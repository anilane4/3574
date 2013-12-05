#ifndef CHATGUI_H
#define CHATGUI_H

#include <QTcpSocket>
#include <QDialog>

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
class ChatGui : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief ChatGui Default constructor for the chatroom gui has three parameters
     * the first is a QWidget dummy parent, the second will be assigned to the ChatGui's
     * private variable userName, and the third will be assigned to the ChatGui's
     * private variable chatRoom.
     * @param parent QWidget dummy parent
     * @param name username based off of clientmessage's username
     * @param room chatroom name based off of resident chatroom's name
     */
    ChatGui(QWidget *parent = 0, QString name = 0, QString room = 0);
    ~ChatGui();
    /**
     * @brief getUserName returns the userName which should corresponde
     * to the clientmessage's username
     * @return userName
     */
    QString getUserName();
    /**
     * @brief setUserName set the userName to the clientmessage's username
     * @param newName that will be stored in userName
     */
    void setUserName(QString newName);
    /**
     * @brief getChatRoom return name of resident chatroom's name
     * @return chatRoom
     */
    QString getChatRoom();
    /**
     * @brief setChatRoom set the chatRoom private variable to resident
     * chatroom's name
     * @param newRoom that will be stored in chatRoom
     */
    void setChatRoom(QString newRoom);
    /**
     * @brief getChatRoom
     * @return
     */
    QString getMessage();
    /**
     * @brief setMessage
     * @param newMessage
     */
    void setMessage(QString newMessage);
    /**
     * @brief getParticipantList
     * @return
     */
    QList<QString> getParticipantList();
    /**
     * @brief keyPressEvent
     * @param event
     */
    void keyPressEvent(QKeyEvent * event);

signals:
    /**
     * @brief leaveChatRoom signal is used to trigger the clientmessage's
     * slot for updating other chatroom partcicipant's participants list
     * @param chatRoomName name of the resident chatroom
     */
    void leaveChatRoom(QString &chatRoomName);
    /**
     * @brief sendMessage signal is used to trigger the clientmessage's
     * slot for receiving a new message
     * @param outgoingMessage is the message to be sent to other
     * chatroom participants
     */
    void sendMessage(QString &outgoingMessage);

public slots:
    /**
     * @brief receiveMessage slot for receiving signal from clientmessage
     * notifying gui that there is a new messsage
     * @param incomingMessage new message that was received from clientmessage
     * that is to be displayed to chatroom participants
     */
    void receiveMessage(const QString &incomingMessage);
    /**
     * @brief addParticipant slot allowing clientmessage to notifiy gui to
     * update participant list with addition of new participant
     * @param participantName name of the participant that joined
     * @param chatRoomName name of the chatroom that the paricipant joined to
     */
    void addParticipant(const QString &participantName, const QString &chatRoomName);
    /**
     * @brief removeParticipant slot allowing clientmessage to notifiy gui to
     * update participant list with the removal of a participant
     * @param participantName name of the participant that exited
     * @param chatRoomName name of the chatroom that the paricipant exited from
     */
    void removeParticipant(const QString &participantName, const QString &chatRoomName);


private slots:
    /**
     * @brief encodeMessage append message with information required for transmission
     */
    void encodeMessage();
    /**
     * @brief decodeMessage strip message of information used for transmission
     */
    void decodeMessage();


private:
    /**
     * @brief inputLineEdit
     */
    QLineEdit *inputLineEdit;
    /**
     * @brief messagesTextEdit
     */
    QTextEdit *messagesTextEdit;
    /**
     * @brief participantsTextEdit
     */
    QTextEdit *participantsTextEdit;
    /**
     * @brief userName private variable for storing clientmessage's username
     */
    QString userName;
    /**
     * @brief chatRoom private variable for storing the resident chatroom's name
     */
    QString chatRoom;
    /**
     * @brief message private variable for storing the user's message to be sent
     */
    QString message;
    /**
     * @brief listOfMyParticipants
     */
    QList<QString> listOfMyParticipants;
};
//! [0]

#endif
