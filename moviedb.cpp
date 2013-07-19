#include "moviedb.h"

moviedb::moviedb(QObject *parent) :
    QObject(parent)
{


}

bool moviedb::openDB() {

    return db.open();
}

bool moviedb::tableExists(QString tableName) {
    // Verify that a table exists in the SQLite DB
    return db.tables().contains(tableName) ? true : false;
}

bool moviedb::closeDB() {
    return db.close();
}

bool moviedb::deleteDB() {
    db.close();

    return QFile::remove(dbPath);
}

QSqlError moviedb::lastError() {
    return db.lastError();
}
