#include "userdb.h"

UserDB::UserDB()
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName(qApp->applicationDirPath()
                         + QDir::separator()
                         + DB_NAME);
    if (!m_db.open()) {
        qDebug() << "Error opening database." << m_db.lastError().text() << "Exiting.";
        exit(1);
    }
    createTables();
}

UserDB::~UserDB()
{
    m_db.close();
}

QString UserDB::readCommand(QString request)
{
    QStringList list = request.split('|', QString::SkipEmptyParts);
    if (list.size() != 3) return QString("Command not recognized. Please try again.");

    QString command = list.first();

    if (!QString::compare(command, "register", Qt::CaseInsensitive))
        return registerUser(list.at(1), list.last());
    else if (!QString::compare(command, "login", Qt::CaseInsensitive))
        return loginUser(list.at(1), list.last());

    return QString("Command not recognized. Please try again.");
}

void UserDB::createTables()
{
    QSqlQuery query(m_db);
    // Username max 10 characters. Password max 16 characters.
    query.exec("create table users(username varchar(10) primary key, password varchar(16))");
    query.exec("insert into users values('admin', 'admin')");
}

QString UserDB::registerUser(QString username, QString password)
{
    m_mutex.lock();
    QSqlQueryModel model;
    model.setQuery(QString("select username from users where username='%1'").arg(username));
    QString result = model.record(0).value("username").toString();
    if (!QString::compare(result, username)) {
        m_mutex.unlock();
        return QString("Account " + username + " already exists. Please choose a different name.");
    }

    if (username.length() > 10 || username.length() < 4) {
        m_mutex.unlock();
        return QString("Username must be between 4 and 10 characters.");
    }
    if (password.length() > 16 || password.length() < 4) {
        m_mutex.unlock();
        return QString("Password must be between 4 and 16 characters.");
    }

    QSqlQuery query(m_db);
    bool ret = query.exec(QString("insert into users values('%1', '%2')").arg(username).arg(password));

    m_mutex.unlock();
    if (ret)
        return QString("Account " + username + " successfully created!");
    else
        return QString("Sorry but I goofed trying to register your account. Sorry bout that.");
}

QString UserDB::loginUser(QString username, QString password)
{
    QSqlQueryModel model;
    model.setQuery(QString("select username, password from users where username='%1'").arg(username));
    QString result = model.record(0).value("username").toString();
    QString storedPass = model.record(0).value("password").toString();
    if (QString::compare(result, username) != 0)
        return QString("Account " + username + " does not exist. Please register first.");

    if (!QString::compare(storedPass, password))
        return QString(username + " has been logged in!");
    else
        return QString("Incorrect username/password combination. Please try again.");
}

void UserDB::clearDB()
{
    QSqlQuery query(m_db);
    query.exec("drop table users");
    createTables();
}
