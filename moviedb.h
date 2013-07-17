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
     * @brief Open the database, create one if it doesn't exist. This function looks
     * for the database in the home path (same for linux/unix/windows), if it finds
     * the database, it opens it otherwise it sets newDB to true and create an empty
     * database. See the moviedb() constructor for details on table verification and
     * creation.
     * @return It returns true if the database is opened / created successfully. It returns
     * false if there are errors. Errors can be accessed using the lastError() function.
     * @see lastError()
     */
    bool openDB();

    /**
     * @brief Close the database. This function closes the connection to the open
     * database. Useful only when application is about to close.
     * @return It returns true if the database is closed successfully.  It returns
     * false if there are errors. Errors can be accessed using the lastError() function.
     * @see lastError()
     */
    bool closeDB();

    /**
     * @brief Delete the database. This function will delete the existing database mostly
     * used to refresh the database or during uninstall.
     * @return It returns true if the database was deleted successfully. It returns
     * false if there are errors. Errors can be accessed using the lastError() function.
     * @see lastError()
     */
    bool deleteDB();

    /**
     * @brief Helper function to verify if a table exists. This function uses the QSQLDatabase
     * function to look for the existence of a table.
     * @param tableName Name of the table to look for.
     * @return It returns true if the table exists and false if it doesn't exist.  It also returns
     * false if there are errors. Errors can be accessed using the lastError() function.
     * @see lastError()
     */
    bool tableExists(QString tableName);

    /**
     * @brief SQL Errors from previous operation. This function returns any errors that might
     * have occured when a SQL operation was executed on the database.
     * @return It returns a QSQLError object with all the details on the error.
     */
    QSqlError lastError();

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
    bool addCase (QString id, QString name, QString character);


signals:
    
public slots:
    
private:
    QSqlDatabase db;    ///< Database adapter.
    QString dbPath;     ///< Path to the database.
    bool newDB;         ///< Tracks if database is being populated for the first time.

    /**
     * @brief Query creates the movies table. The following fields are created: id, title, year,
     * mpaa_rating, runtime, critics_concensus, critics_rating, critics_score, audience_rating,
     * audience_score, synopsis, thumbnail, profile, theaters, dvd, filename, source, list_date
     */
    extern const QString create_movies_table;
    extern const QString create_cast_table;     ///< Query creates the cast table with following fields: id, name, character

    /**
     * @brief Query deletes all the in theater movies. This allows for new data to be loaded to
     * the table.
     */
    extern const QString delete_intheater_records;

    /**
     * @brief Query deletes all records in the tables. This allows for rescans and data refresh.
     */
    extern const QString delete_all_records;
};

#endif // MOVIEDB_H
