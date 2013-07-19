#ifndef MOVIELIBRARY_H
#define MOVIELIBRARY_H

#include <QWidget>
#include <QtXml>
#include <QtNetwork>
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QVector>
#include "parser.h" // JSON Parser for Rotten Tomato API
#include "parserrunnable.h"
#include "qjson_export.h"
#include "qobjecthelper.h"
#include "serializer.h"
#include "serializerrunnable.h"
#include "rottentomatoes.h"
#include <QMultimedia>

namespace Ui {
    class movieLibrary;
}

class movieLibrary : public QWidget
{
    Q_OBJECT
    QThread rottenTomatoesThread;

public:
    explicit movieLibrary(QWidget *parent = 0);
    void populateMovies();
    void scanFolders(QString mF);
    void fetchMovieMDB (QString movie);
    void fetchMovieRT (QString movie);
    void fetchCineRT();
    void fillWithInCine(QVariantMap results);
    void addMovieFileToDB (QString Filename);
    void updateMovieInDB (QString Filename,
                          QString name,
                          QString thumbnail,
                          QString poster,
                          QString rating,
                          QString overview);
    void setStatus (int statusNumber, QString status);

    ~movieLibrary();
signals:
    void lookForInTheater();
    void lookForMovie(QString movieName);

public slots:
    void finishedReply(QNetworkReply *pReply);
    void processInTheater(QList<QStringList> inTheaterResult);
    void processMovie(QStringList movieResult);

private:
    Ui::movieLibrary *ui;
    QNetworkAccessManager *m_manager;

    QStringList movieFolderList;

    QString nodeName;
    QString nodeValue;

    QJson::Parser parser;

    int cineCurrentPage;
    int cineTotalPages;

    // Status Variables
    QString inTheaters;
    QString onHDD;
    QString downloadSpeed;
    QString uploadSpeed;

    rottenTomatoes *rtapi;
};

#endif // MOVIELIBRARY_H
