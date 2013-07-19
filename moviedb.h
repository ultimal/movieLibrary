/**
 * SQLite database model. The 'moviedb' class deals with storing data returned
 * by internet queries and local hard drive scans. It can also query data from the
 * database and return the results to the controller. moviedb class manages the
 * opening, creation and deletion of the database and its tables. This class does
 * not initiate any internet communication or connectivity, that has to be handled
 * by the controller.
 */

#ifndef MOVIEDB_H
#define MOVIEDB_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSql>
#include <QSqlError>
#include <QFile>
#include <QDir>
#include <QDebug>

class moviedb : public QObject
{
    Q_OBJECT
public:
    /**
     * Class constructor. Makes sure the database exists in the user's home folder
     * and that the tables are present. If any tables are missing it sets the newDB
     * variable to true and this lets the controller know that it needs to connect to
     * internet services to update the database contents.
     * @param parent a QObject id, representing the parent class for this class.
     * @see newDB()
    explicit moviedb(QObject *parent = 0);

    /**
     * @brief Add a movie to the database. Use this method to create records in the database.
     * This method creates in theater movies and on hard drive movie data in the database.
     * @param id Movie ID returned by the api.
     * @param title Movie name.
     * @param year Year the movie was released in.
     * @param mpaa_rating MPAA rating for the movie.
     * @param runtime Movie run time.
     * @param critics_concensus What the critics are saying about the movie.
     * @param critics_rating The critics rating for the movie.
     * @param critics_score The critics score for the movie.
     * @param audience_rating The audience rating for the movie.
     * @param audience_score The audience score for the movie.
     * @param synopsis An overview of what the movie is about.
     * @param thumbnail Thumbnail image for the movie.
     * @param profile Profile image for the movie.
     * @param theaters In theaters release date.
     * @param dvd DVD release date.
     * @param filename For movies that are on the drive, full file path.
     * @param source Source of data, INTHEATERS, HDD or DVD.
     * @param list_date Date when this data was picked up.
     * @return Returns true if the record was successfully created. False if it could not be created.
     * Incase it returns false, call lastError() to get details on the error that occured.
     * @see lastError()
     */
    bool addMovie(QString id, QString title, QString year, QString mpaa_rating, QString runtime, QString critics_concensus,
                  QString critics_rating, QString critics_score, QString audience_rating, QString audience_score,
                  QString synopsis, QString thumbnail, QString profile, QString theaters, QString dvd,
                  QString filename, QString source, QString list_date);

    /**
     * @brief addCase
     * @param id
     * @param name
     * @param character
     * @return
     */
    bool addCast (QString id, QString name, QString character);


signals:
    
public slots:
    
private:

};

#endif // MOVIEDB_H
