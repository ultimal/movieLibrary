#include "movielibrary.h"
#include <QApplication>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include "moviedb.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QSqlDatabase db;

    // Init queries
    QString create_movies_table = "CREATE TABLE movies (id integer primary key not null, "
            "rtid integer,"
            "title varchar(255),"
            "year varchar(5),"
            "runtime integer,"
            "critics_consensus text,"
            "release_date_theater date, "
            "release_date_dvd date, "
            "rating_mpaa varchar(50), "
            "ratings_critics varchar(50), "
            "ratings_critics_score integer, "
            "ratings_audience varchar(50), "
            "ratings_audience_score integer, "
            "poster_thumbnail text, "
            "poster_poster text, "
            "synopsis text"
            ")";
    QString create_cast_table   = "CREATE TABLE cast (id integer primary key not null, "
            "rtid integer, "
            "name varchar(255), "
            "character_name varchar(255)"
            ")";
    QString create_log_table    = "CREATE TABLE log (id integer primary key not null"
            "source varchar(255), "
            "message text, "
            "error integer"
            ")";

    // Open the database or create it
    db = QSqlDatabase::addDatabase("QSQLITE");

    // Store the database in the "HOME" folder on all OSes

    dbPath = QDir::home().path();
    dbPath.append(QDir::separator().append("movie.db.sqlite"));
    dbPath = QDir::toNativeSeparators(dbPath);

    // When the db is open, verify tables
    if (db.setDatabaseName(dbPath)) {
        // Verify that critical tables exist, if not create them
        if (!tableExists("movies"))     { QSqlQuery::exec(create_movies_table); }
        if (!tableExists("cast"))       { QSqlQuery::exec(create_cast_table); }
        if (!tableExists("log"))        { QSqlQuery::exec(create_log_table); }
    } else {
        qDebug() << "Unable to create database.";
        QApplication::quit();
    }

    movieLibrary *w = new movieLibrary();
    w->show();

    return a.exec();
}
