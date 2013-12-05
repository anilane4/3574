
// Martin Anilane


#include <QtGui>
//#include <QtNetwork>

#include "client.h"
client::client(QWidget *parent)
:   QDialog(parent)//, networkSession(0)
{
    // have an empty message
    currentCommand = "hellow world";
    // create the label for the client guis
    serverLabel = new QLabel(tr("&Server name:"));
    portLabel = new QLabel(tr("S&erver port:"));
    usernameLabel =new QLabel(tr("Enter User Name:"));
    passwordLabel = new QLabel(tr("Enter Password:"));
    enterCommaneLabel = new QLabel(tr("Enter command:"));
    serverResponseLabel = new QLabel(tr("Server Response:"));

    // connect to an IP
   /* QString IP;
    QList<QHostAddress> IPList = QNetworkInterface::allAddresses();
    // The first non localhost is used

    for (int i = 0; i < IPList.size(); ++i) {
        if (IPList.at(i) != QHostAddress::LocalHost &&
            IPList.at(i).toIPv4Address()) {
            IP = IPList.at(i).toString();
            break;
        }
    }*/
    // if empty use local host
    /*if (IP.isEmpty())
        IP = QHostAddress(QHostAddress::LocalHost).toString();*/

    // create each line edit
    serverLineEdit = new QLineEdit();
    portLineEdit = new QLineEdit;
    //portLineEdit->setValidator(new QIntValidator(1, 65535, this));
    usernameLineEdit= new QLineEdit;
    passwordLineEdit = new QLineEdit;
    commandEdit = new QLineEdit;

    // the server response needs a QTextEdit
    serverResponseTextEdit = new QTextEdit;
    serverResponseTextEdit->setReadOnly(true);

    // creat a label for each edit
    serverLabel->setBuddy(serverLineEdit);
    portLabel->setBuddy(portLineEdit);
    usernameLabel->setBuddy(usernameLineEdit);
    passwordLabel->setBuddy(passwordLineEdit);
    enterCommaneLabel->setBuddy(commandEdit);
    serverResponseLabel->setBuddy(serverResponseTextEdit);

    // an out put message letting the user know that the server need to be running
    // as well
    messageLabel = new QLabel(tr("Server must be running"));

    //set up send command button
    sendButton = new QPushButton(tr("Send command"));
    sendButton->setDefault(true);
    sendButton->setEnabled(false);
    connectionButton = new QPushButton(tr("Connect"));
    connectionButton->setDefault(true);
    connectionButton->setEnabled(false);
    quitButton = new QPushButton(tr("Quit"));
    loginButton = new QPushButton(tr("login"));
    //loginButton->setDefault(true);
    //loginButton->setEnabled(false);
    registerButton = new QPushButton(tr("register"));
    //registerButton->setDefault(true);
    //registerButton->setEnabled(false);

    //set up box for buttons
    buttonBox = new QDialogButtonBox;
    buttonBox->addButton(connectionButton, QDialogButtonBox::ActionRole);
    buttonBox->addButton(quitButton, QDialogButtonBox::RejectRole);
    buttonBox->addButton(sendButton, QDialogButtonBox::ActionRole);
    buttonBox->addButton(loginButton,QDialogButtonBox::ActionRole);
    buttonBox->addButton(registerButton, QDialogButtonBox::ActionRole);

   // tcpSocket = new QTcpSocket(this);

    // check the tcp ports to see if we can send
    connect(serverLineEdit, SIGNAL(textChanged(QString)),
            this, SLOT(startButton()));
    connect(portLineEdit, SIGNAL(textChanged(QString)),
            this, SLOT(startButton()));
    //set up a connection when the button is pressed
    connect(connectionButton, SIGNAL(clicked()),
            this, SLOT(startConnection()));
    //send a command
    connect(sendButton, SIGNAL(clicked()),
            this, SLOT(sendCommand()));
    //close
    connect(quitButton, SIGNAL(clicked()), this, SLOT(close()));
    // this allows to read from the server
   // connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(getServer()));
    // dissplay a possible error
    /*connect(tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(displayError(QAbstractSocket::SocketError)));*/
    // connection of signal of the login and send
    connect(loginButton,SIGNAL(clicked()),this,SLOT(sendLogin()));
    connect(registerButton,SIGNAL(clicked()),this,SLOT(sendRegister()));

    // set the grid layout of the gui for the client
    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(serverLabel, 0, 0);
    mainLayout->addWidget(serverLineEdit, 0, 1);
    mainLayout->addWidget(portLabel, 1, 0);
    mainLayout->addWidget(portLineEdit, 1, 1);
    mainLayout->addWidget(usernameLabel, 2, 0);
    mainLayout->addWidget(usernameLineEdit, 2, 1);
    mainLayout->addWidget(passwordLabel, 3, 0);
    mainLayout->addWidget(passwordLineEdit,3,1);
    mainLayout->addWidget(enterCommaneLabel, 4, 0);
    mainLayout->addWidget(commandEdit, 4, 1);
    mainLayout->addWidget(serverResponseLabel, 5, 0);
    mainLayout->addWidget(serverResponseTextEdit, 5, 1);
    mainLayout->addWidget(messageLabel, 6, 0, 1, 2);
    mainLayout->addWidget(buttonBox, 7, 0, 1, 2);
    setLayout(mainLayout);

    setWindowTitle(tr("Assign11 client"));
    portLineEdit->setFocus();

   /* QNetworkConfigurationManager manager;
    if (manager.capabilities() & QNetworkConfigurationManager::NetworkSessionRequired) {
        QSettings settings(QSettings::UserScope, QLatin1String("Trolltech"));
        settings.beginGroup(QLatin1String("QtNetwork"));
        const QString id = settings.value(QLatin1String("DefaultNetworkConfiguration")).toString();
        settings.endGroup();

        QNetworkConfiguration config = manager.configurationFromIdentifier(id);
        if ((config.state() & QNetworkConfiguration::Discovered) !=
            QNetworkConfiguration::Discovered) {
            config = manager.defaultConfiguration();
        }

        networkSession = new QNetworkSession(config, this);
        connect(networkSession, SIGNAL(opened()), this, SLOT(startSession()));

        sendButton->setEnabled(false);
        messageLabel->setText(tr("Opening network session."));
        networkSession->open();
    }*/
}

//void client::startConnection()
//{
  //  m_blockSize = 0;
    // check to see if there is a connection to the server
   /* if (tcpSocket->isValid()) {
        messageLabel->setText(tr("Already connected to server"));
        // else connect to one
    } else {
        tcpSocket->connectToHost(serverLineEdit->text(),
                             portLineEdit->text().toInt());

        sendButton->setEnabled(true);
    }*/

//}

void client::sendCommand()
{
    currentCommand = commandEdit->text();
    messageLabel->setText(currentCommand);
    /*QByteArray block;
    QDataStream out (&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_0);
    out << (quint16)0;
    out << currentCommand;
    out.device()->seek(0);
    out << (quint16) (block.size() - sizeof(quint16));

    tcpSocket->write(block);
    m_blockSize = 0;*/
}
/*void client::startSession()
{
    // Save the used configuration
    QNetworkConfiguration config = networkSession->configuration();
    QString id;
    if (config.type() == QNetworkConfiguration::UserChoice)
        id = networkSession->sessionProperty(QLatin1String("UserChoiceConfiguration")).toString();
    else
        id = config.identifier();

    QSettings settings(QSettings::UserScope, QLatin1String("Trolltech"));
    settings.beginGroup(QLatin1String("QtNetwork"));
    settings.setValue(QLatin1String("DefaultNetworkConfiguration"), id);
    settings.endGroup();

    messageLabel->setText(tr("This client requires that you run the "
                            "assign11 server as well."));

    startButton();
}*/



/*void client::getServer()
{
    // this allows to read form the server
    messageLabel->setText(tr("send data to be read"));
    QDataStream in(tcpSocket);
    in.setVersion(QDataStream::Qt_4_0);

    if (m_blockSize == 0) {
        if (tcpSocket->bytesAvailable() < (int)sizeof(quint16))
            return;

        in >> m_blockSize;
    }

    if (tcpSocket->bytesAvailable() < m_blockSize)
        return;

    QString servOutput;
    in >> servOutput;

    messageLabel->setText(servOutput);
    serverResponseTextEdit->setReadOnly(false);
    serverResponseTextEdit->moveCursor(QTextCursor::End);
    serverResponseTextEdit->insertPlainText (servOutput + "\n");
    serverResponseTextEdit->setReadOnly(true);
    connectionButton->setEnabled(true);
}

void client::displayError(QAbstractSocket::SocketError socketError)
{
    // if a error acoured diplay the correct error
    switch (socketError) {
    case QAbstractSocket::RemoteHostClosedError:
        break;
    case QAbstractSocket::HostNotFoundError:
        QMessageBox::information(this, tr("assign11 client"),
                                 tr("The host was not found. Please check the "
                                    "host name and port settings."));
        break;
    case QAbstractSocket::ConnectionRefusedError:
        QMessageBox::information(this, tr("assign11 client"),
                                 tr("The connection was refused by the peer. "
                                    "Make sure the fortune server is running, "
                                    "and check that the host name and port "
                                    "settings are correct."));
        break;
    default:
        QMessageBox::information(this, tr("assign11"),
                                 tr("The following error occurred: %1.")
                                 .arg(tcpSocket->errorString()));
    }

    connectionButton->setEnabled(true);
}

void client::startButton()
{
    // you want to set the enable for the button
    connectionButton->setEnabled((!networkSession || networkSession->isOpen()) &&
                                 !serverLineEdit->text().isEmpty() &&
                                 !portLineEdit->text().isEmpty());

}*/

/*void client::sendClientMessageCommand(QString command)
{
    messageLabel->setText(command);
    QByteArray block;
    QDataStream out (&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_0);
    out << (quint16)0;
    out << command;
    out.device()->seek(0);
    out << (quint16) (block.size() - sizeof(quint16));

    tcpSocket->write(block);
    m_blockSize = 0;

}*/
QString client::LoginVerify(bool login)
{
    if(login == true){
        qDebug()<<"LOGIN GOOD";
        // This is where i create the constructor for the multiple chatrooms
        return "login good";
    }
    return "login bad";
}
QString client::registerVerify(bool registers)
{
    if(registers == true){
        qDebug()<<"REGISTER GOOD";
        // This is where i create the constructor for the multiple chatrooms
        return "register good";
    }
    return "register bad";
}
QString client::getInformation()
{
    return allTogether;
}
void client::sendLogin()
{
    qDebug()<<"sending login";
    QString loginInfo;
    QString passwordInfo;
    loginInfo = usernameLineEdit->text();
    passwordInfo = passwordLineEdit->text();
    qDebug()<<"user name"<<loginInfo;
    qDebug()<<"password"<<passwordInfo;
    //QString allTogether;
    allTogether="login";
    allTogether.append(" ").append(loginInfo).append(" ").append(passwordInfo);
    qDebug()<<"all together"<<allTogether;
    /*messageLabel->setText(allTogether);
    QByteArray block;
    QDataStream out (&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_0);
    out << (quint16)0;
    out << allTogether;
    out.device()->seek(0);
    out << (quint16) (block.size() - sizeof(quint16));

    tcpSocket->write(block);
    m_blockSize = 0;*/
}
void client::sendRegister()
{
    qDebug()<<"sending register";
    QString loginInfo;
    QString passwordInfo;
    loginInfo = usernameLineEdit->text();
    passwordInfo = passwordLineEdit->text();
    qDebug()<<"user name"<<loginInfo;
    qDebug()<<"password"<<passwordInfo;
    //QString allTogether;
    allTogether="register";
    allTogether.append(" ").append(loginInfo).append(" ").append(passwordInfo);
    qDebug()<<"all together"<<allTogether;
   /* messageLabel->setText(allTogether);
    QByteArray block;
    QDataStream out (&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_0);
    out << (quint16)0;
    out << allTogether;
    out.device()->seek(0);
    out << (quint16) (block.size() - sizeof(quint16));

    tcpSocket->write(block);
    m_blockSize = 0;*/
}
void client::enableStartConnectionButton()
{

}
void client::sessionOpened()
{

}
void client::readServerResponse()
{

}
