#ifndef CONNECTION_H
#define CONNECTION_H
#include <QSqlDatabase>
bool mylinkDatabase(){
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(databaseName);
    if (!db.open()) {
        return false;
    }
    return true;
}
#endif // CONNECTION_H
