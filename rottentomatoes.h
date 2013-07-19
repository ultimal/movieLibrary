/**
 * Brief Rotten Tomatoes API. Use this api to connect to the Rotten Tomatoes website
 * and pull data on movies that are either on the hard drive or in theaters. This
 * class also provides data like movie cast crew names for the twitter feed. The
 * movie database is populated using the data that is made available by this class.
 */
#ifndef ROTTENTOMATOES_H
#define ROTTENTOMATOES_H

#include <QObject>
#include <QNetworkRequest>
#include <QNetworkReply>

class rottenTomatoes : public QObject
{
    Q_OBJECT
    QThread rottenTomatoesThread;
public:
    /**
     * @brief rottenTomatoes
     * @param parent
     * @param searchMode In Theater (false) or Movie Search (true)
     */
    explicit rottenTomatoes(QObject *parent = 0, bool searchMode = false);
    
signals:
    void finishedInTheater ();
    void finishedMovie ();
    void inTheaterResultsAvailable(QVariantMap result);
    void movieResultsAvailable(QVariantMap result);

public slots:
    /**
     * @brief Slot is called by req() once there is data available. This slot handles
     * the data that is available. This slot also handles overall availability of the
     * class.
     * @param pReply Object containing the QNetworkReply object returned by the
     * QNetworkRequest class. This object contains the data that is returned by the
     * request.
     */
    void finishedReply (QNetworkReply *pReply);
    void getInTheater();
    void getMovie(QString movieName);

private:
    QString inTheatersQuery;    ///< Query string to be used with the in theaters query
    QString movieQuery;         ///< Query string to be used with specific movie query
    QNetworkAccessManager m_manager;
    int inTheatersTotal;
    int movieTotal;
    int inTheatersCurrentPage;
    int movieCurrentPage;
    QString movieNameSearch;
    bool doneWithResults;
    bool inTheaterMode;
};

#endif // ROTTENTOMATOES_H
