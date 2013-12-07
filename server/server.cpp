#include "server.h"

Server::Server(QWidget *parent)
:   QDialog(parent), tcpServer(0), networkSession(0)
{
    userDB = new UserDB();
    chatroomList = new QList<QString>();
    statusLabel = new QLabel;
    quitButton = new QPushButton(tr("Quit"));
    quitButton->setAutoDefault(false);

    QNetworkConfigurationManager manager;
    if (manager.capabilities() & QNetworkConfigurationManager::NetworkSessionRequired) {
        // Get saved network configuration
        QSettings settings(QSettings::UserScope, QLatin1String("QtProject"));
        settings.beginGroup(QLatin1String("QtNetwork"));
        const QString id = settings.value(QLatin1String("DefaultNetworkConfiguration")).toString();
        settings.endGroup();

        // If the saved network configuration is not currently discovered use the system default
        QNetworkConfiguration config = manager.configurationFromIdentifier(id);
        if ((config.state() & QNetworkConfiguration::Discovered) !=
            QNetworkConfiguration::Discovered) {
            config = manager.defaultConfiguration();
        }

        networkSession = new QNetworkSession(config, this);
        connect(networkSession, SIGNAL(opened()), this, SLOT(sessionOpened()));

        statusLabel->setText(tr("Opening network session."));
        networkSession->open();
    } else {
        sessionOpened();
    }

        connect(quitButton, SIGNAL(clicked()), this, SLOT(close()));
        connect(tcpServer, SIGNAL(newConnection()), this, SLOT(serviceClient()));

        QHBoxLayout *buttonLayout = new QHBoxLayout;
        buttonLayout->addStretch(1);
        buttonLayout->addWidget(quitButton);
        buttonLayout->addStretch(1);

        QVBoxLayout *mainLayout = new QVBoxLayout;
        mainLayout->addWidget(statusLabel);
        mainLayout->addLayout(buttonLayout);
        setLayout(mainLayout);

        setWindowTitle(tr("QtChat Server"));
}

Server::~Server()
{
    delete userDB;
}

void Server::sessionOpened()
{
    // Save the used configuration
    if (networkSession) {
        QNetworkConfiguration config = networkSession->configuration();
        QString id;
        if (config.type() == QNetworkConfiguration::UserChoice)
            id = networkSession->sessionProperty(QLatin1String("UserChoiceConfiguration")).toString();
        else
            id = config.identifier();

        QSettings settings(QSettings::UserScope, QLatin1String("QtProject"));
        settings.beginGroup(QLatin1String("QtNetwork"));
        settings.setValue(QLatin1String("DefaultNetworkConfiguration"), id);
        settings.endGroup();
    }

    tcpServer = new QTcpServer(this);
    if (!tcpServer->listen(QHostAddress::LocalHost, PORT)) {
        QMessageBox::critical(this, tr("QtChat Server"),
                              tr("Unable to start the server: %1.")
                              .arg(tcpServer->errorString()));
        close();
        return;
    }
    statusLabel->setText(tr("The server is running on\n\nIP: %1\nport: %2\n\n"
                            "Run the QtChat Client now.")
                         .arg("LocalHost").arg(tcpServer->serverPort()));
}

void Server::serviceClient()
{
    qDebug() << "Client connected!";
    QTcpSocket *clientConnection = tcpServer->nextPendingConnection();
    Session *session = new Session(clientConnection, userDB, chatroomList);
    connect(clientConnection, SIGNAL(readyRead()), session, SLOT(readSocket()));
    connect(clientConnection, SIGNAL(disconnected()), clientConnection, SLOT(deleteLater()));
    connect(clientConnection, SIGNAL(disconnected()), session, SLOT(deleteLater()));

    connect(session, SIGNAL(broadcastMessage(QString)), this, SLOT(broadcast(QString)));
    connect(session, SIGNAL(disconnecting(QString)), this, SLOT(sessionDisconnected(QString)));
    connect(this, SIGNAL(broadcastAll(QString)), session, SLOT(receiveMessage(QString)));

    QThread *newThread = new QThread(this);
    connect(clientConnection, SIGNAL(destroyed()), newThread, SLOT(quit()));
    connect(newThread, SIGNAL(finished()), newThread, SLOT(deleteLater()));
    session->moveToThread(newThread);
    newThread->start();
}

void Server::broadcast(QString message)
{
    qDebug() << "Broadcasting " << message;
    emit broadcastAll(message);
}

void Server::sessionDisconnected(QString sessionName)
{
    qDebug() << sessionName << " has disconnected.";
}
