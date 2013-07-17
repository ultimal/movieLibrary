#include "moviedb.h"

moviedb::moviedb(QObject *parent) :
    QObject(parent)
{

    // Init queries
    create_movies_table = "CREATE TABLE Movies";
    create_cast_table   = "CREATE TABLE Cast";
    delete_all_records  = "DROP TABLE Movies";
    delete_intheater_records = "DELETE * FROM Movies WHERE source IN ('INTHEATERS')";

    // When the db is open, verify tables
    if (openDB()) {
        // Verify that critical tables exist, if not create them
        if (!tableExists("rt_movies")) { }
        if (!tableExists("hdd_movies")) { }
        if (!tableExists("rt_ratings")) { }
    } else {
        qDebug() << "Unable to create database.";
    }
}

bool moviedb::openDB() {
    // Open the database or create it
    db = QSqlDatabase::addDatabase("QSQLITE");

    // Store the database in the "HOME" folder on all OSes

    dbPath = QDir::home().path();
    dbPath.append(QDir::separator().append("movie.db.sqlite"));
    dbPath = QDir::toNativeSeparators(dbPath);

    db.setDatabaseName(dbPath);

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
