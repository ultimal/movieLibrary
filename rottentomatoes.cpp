#include "rottentomatoes.h"

rottenTomatoes::rottenTomatoes(QObject *parent, bool searchMode) :
    QObject(parent)
{
    inTheaterMode = searchMode;
    m_manager = new QNetworkAccessManager(this);

    connect (m_manager,SIGNAL(finished(QNetworkReply*)),this,SLOT(finishedReply(QNetworkReply*)));
}

void rottenTomatoes::getInTheater() {
    QString qry = QString("http://api.rottentomatoes.com/api/public/v1.0/lists/movies/in_theaters.json?apikey=hyzk5vrtsy6ne8a6tut98e9t&page_limit=50&page=%1").arg(inTheatersCurrentPage);

    qDebug() << qry;
    m_manager->get(QNetworkRequest(QUrl(qry)));
}

void rottenTomatoes::getMovie(QString movieName) {
    QString qry = tr("http://api.rottentomatoes.com/api/public/v1.0/movies.json?apikey=hyzk5vrtsy6ne8a6tut98e9t&q=%1&page_limit=50&page=%2").arg(movieName).arg(movieCurrentPage);
    movieNameSearch = movieName;
    m_manager->get(QNetworkRequest(QUrl(qry)));
}

void rottenTomatoes::finishedReply(QNetworkReply *pReply) {
    bool ok;

    QByteArray data = pReply->readAll();
    QVariantMap result = parser.parse (data, &ok).toMap();

    if (!ok) { qDebug() << "Paring JSON Failed"; }

    // Calculate the right number of pages, i.e. round to next integer, e.g. 1.2 is 2 pages.
    float cineTotalPagesf = (result["total"].toFloat() + 0.5) / 50;

    if (inTheaterMode) {
        // If we are working with inTheaters
        emit inTheaterResultsAvailable(result);

        // Calculate Total Pages
        inTheatersTotal = qRound(cineTotalPagesf);

        // qDebug() << "Total Movies: " << result["total"];
        // qDebug() << "Total No. Of Pages: " << cineTotalPages;
        // qDebug() << "Movies in List: " << result["movies"].toList().count();
        // qDebug() << "Synopsis: " << result["movies"].toList()[1].toMap()["synopsis"].toString();
        // qDebug() << "Ratings: " << result["movies"].toList()[1].toMap()["ratings"].toMap()["critics_rating"].toString();

        if (inTheatersCurrentPage < inTheatersTotal) {
            inTheatersCurrentPage++;
            getInTheater();
        } else {
            // Let the calling class know we are done
            emit finishedInTheater();
        }

    } else {
        // Movie search mode
        emit movieResultsAvailable(result);
        movieTotal = qRound(cineTotalPagesf);

        if (movieCurrentPage < movieTotal){
            movieCurrentPage++;
            getMovie(movieNameSearch);
        } else {
            // Let the calling class know we are done
            emit finishedMovie();
        }
    }
}
