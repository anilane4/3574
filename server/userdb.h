#ifndef USERDB_H
#define USERDB_H

#include <QObject>
#include <QDebug>
#include <QFile>
#include <QDir>
#include <QApplication>
//#include <QtGui/QApplication>
#include <QStringList>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlQueryModel>
#include <QSqlField>
#include <QSqlRecord>
#include <QMutex>

#define DB_NAME "UserInfo.sqlite"

/**
 * @brief This class is the interface for the server to interact with the user
 * information database. This database will be used during login/registration.
 */
class UserDB : public QObject
{
Q_OBJECT
public:
    /**
     * @brief UserDB Constructor. Initialize connection to the database and
     * generate tables if they do not already exist.
     */
    UserDB();
    /**
     * @brief readCommand Parses the request and acts accordingly
     * @param request The requested action
     * @return A QString with the result of the request
     */
    QString readCommand(QString request);
    /**
     * @brief ~UserDB Deconstructor. Clean up connection to database.
     */
    ~UserDB();
    /**
     * @brief clearDB Resets the database. Used in testing only.
     */
    void clearDB();
private:
    /**
     * @brief createTables Initializes the databases if they do not already exist.
     */
    void createTables();

    /**
     * @brief registerUser Registers the user with the database. If the
     * username already exists in the database, a message containing that error
     * is returned.
     * @param username The username of the new user.
     * @param password The password for the new user.
     * @return A message containing the result of the registration.
     */
    QString registerUser(QString username, QString password);

    /**
     * @brief loginUser Validate the username/password combination. Will return True
     * if combination is valid. Returns false if the combination does not exist in the
     * database.
     * @param username The username of the user.
     * @param password The password of the user.
     * @return True if username/password exists in the database, False otherwise.
     */
    QString loginUser(QString username, QString password);

    /**
     * @brief m_db The connection to the database.
     */
    QSqlDatabase m_db;
    /**
     * @brief m_mutex Mutex used to prevent race conditions when accessing the database.
     * Database will follow a single-writer/multiple-reader strategy.
     */
    QMutex m_mutex;
};

#endif // USERDB_H
