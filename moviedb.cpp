#include "moviedb.h"

moviedb::moviedb(QObject *parent) :
    QObject(parent)
{


}

bool moviedb::tableExists(QString tableName) {
    // Verify that a table exists in the SQLite DB
    return db.tables().contains(tableName) ? true : false;
}

bool moviedb::addMovie(QString id,
                       QString title,
                       QString year,
                       QString mpaa_rating,
                       QString runtime,
                       QString critics_concensus,
                       QString critics_rating,
                       QString critics_score,
                       QString audience_rating,
                       QString audience_score,
                       QString synopsis,
                       QString thumbnail,
                       QString profile,
                       QString theaters,
                       QString dvd,
                       QString filename,
                       QString source,
                       QString list_date) {
    // Add entry to DB
    QSqlQuery qry;
    return qry.exec(tr("INSERT INTO movies VALUES (null,%1,%2,%3,%4,%5,%6,%7,%8,%9,%10,%11,%12,%13,%14,%15,%16,%17,%18)")
             .arg(id)
             .arg(title)
             .arg(year)
             .arg(mpaa_rating)
             .arg(runtime)
             .arg(critics_concensus)
             .arg(critics_rating)
             .arg(critics_score)
             .arg(audience_rating)
             .arg(audience_score)
             .arg(synopsis)
             .arg(thumbnail)
             .arg(profile)
             .arg(theaters)
             .arg(dvd)
             .arg(filename)
             .arg(source)
             .arg(list_date));
}

bool moviedb::addCast(QString id, QString name, QString character) {
    QSqlQuery qry;
    return qry.exec(tr("INSERT INTO cast VALUES (null,%1,%2,%3)")
                    .arg(id)
                    .arg(name)
                    .arg(character));
}
