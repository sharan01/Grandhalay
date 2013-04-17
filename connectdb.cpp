#include "connectdb.h"

ConnectDB::ConnectDB(QString s) : PATH_TO_DB(s)
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(PATH_TO_DB);
}

ConnectDB::~ConnectDB()
{
    db.close();
}
