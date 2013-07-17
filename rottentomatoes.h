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

public:
    explicit rottenTomatoes(QObject *parent = 0);
    
signals:
    

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

private:
    QString inTheatersQuery;    ///< Query string to be used with the in theaters query
    QString movieQuery;         ///< Query string to be used with specific movie query
    QNetworkRequest req;        ///< Network request object to POST / GET queries

};

#endif // ROTTENTOMATOES_H
