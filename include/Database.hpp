#ifndef DATABASE_HPP
#define DATABASE_HPP

#include <QSqlDatabase>
#include <QString>

class Database {
    public:
        Database(const QString& db_name, const QString& username, const QString& pwd, const QString&);
        ~Database();

        const bool execute(const QString&);

    private:
        static const QString DRIVER;
        const QString connection_name;
};

#endif
