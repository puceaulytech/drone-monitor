#include <QDebug>
#include <QSqlDriver>
#include <QSqlError>
#include <QSqlQuery>
#include <iostream>

#include <Database.hpp>

const QString Database::DRIVER("QPSQL");

Database::Database(QString database_name, QString username, QString password, QString connection_name) : connection_name(connection_name) {

    if(not QSqlDatabase::isDriverAvailable(DRIVER)) {
        // error handling 
    }

    QSqlDatabase db = QSqlDatabase::addDatabase(DRIVER, connection_name);
    db.setDatabaseName(database_name);
    db.setHostName("localhost");
    db.setUserName(username);
    db.setPassword(password);
    if(!db.open()) {
        // error handling again
    } else {
        // check if table exists
        QSqlQuery query("SELECT EXISTS ( SELECT FROM pg_tables WHERE tablename='test' )", db);
        // next entry in record 
        query.next();
        // if the query returns false
        if (!query.value(0).toBool()) {
            query.exec("CREATE TABLE test (id SERIAL, value TEXT)");
        }
    }
}

Database::Database() {}

Database::~Database()
{
    QSqlDatabase::removeDatabase(connection_name);
}

const bool Database::execute(const QString& sql_statement) {
    QSqlDatabase db = QSqlDatabase::database(connection_name); 
    QSqlQuery query(db);     
    return query.exec(sql_statement);
}
