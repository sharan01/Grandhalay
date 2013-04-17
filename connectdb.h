#ifndef CONNECTDB_H
#define CONNECTDB_H

#include <QtSql>

class ConnectDB
{
public:
    ConnectDB(QString);
    ~ConnectDB();
private:
    QSqlDatabase db;
    const QString PATH_TO_DB;

};

#endif // CONNECTDB_H


