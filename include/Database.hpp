#ifndef DATABASE_HPP
#define DATABASE_HPP

#include <QSqlDatabase>
#include <QString>

class Database {
    public:
        Database(QString db_name, QString username, QString pwd, QString cnct_name);
        Database();
        ~Database();

        const bool execute(const QString& query);

    private:
        static const QString DRIVER;
        const QString connection_name;
};

#endif
