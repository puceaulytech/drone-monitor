#include <QDebug>
#include <QSqlDriver>
#include <QSqlError>
#include <QSqlQuery>

#include <Database.hpp>

const QString Database::DRIVER("QPSQL");

Database::Database(const QString& database_name, const QString& username, const QString& password, const QString& connection_name) : connection_name(connection_name) {

    if(not QSqlDatabase::isDriverAvailable(DRIVER)) {
        // error handling 
    }

    QSqlDatabase db = QSqlDatabase::addDatabase(DRIVER, connection_name);
    db.setDatabaseName(database_name);
    if(!db.open()) {
        // error handling again
    }
}

Database::~Database()
{
    QSqlDatabase::removeDatabase(connection_name);
}

const bool Database::execute(const QString& sql_statement) {
    QSqlDatabase db = QSqlDatabase::database(connection_name); 
    QSqlQuery query(db);     
    return query.exec(sql_statement);
}
