#include "movielibrary.h"
#include "ui_movielibrary.h"

movieLibrary::movieLibrary(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::movieLibrary)
{
    ui->setupUi(this);

    ui->frmWhatisthis->hide();
    ui->frmMovieInfo->hide();

    m_manager = new QNetworkAccessManager(this);

    connect (m_manager,SIGNAL(finished(QNetworkReply*)),this,SLOT(finishedReply(QNetworkReply*)));

    // Setup table widget
    QStringList columnLabels;
    columnLabels << "#" << "Title" << "Critic Rating" << "Audience Rating" << "Year" << "Theater Date" << "DVD Date";
    ui->tableWidget->setColumnCount(7);
    qDebug() << ui->tableWidget->columnWidth(1);
    ui->tableWidget->setHorizontalHeaderLabels(columnLabels);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(1,QHeaderView::Stretch);
    ui->tableWidget->verticalHeader()->hide();
    ui->tableWidget->setShowGrid(false);

    ui->tableWidget->setColumnWidth(0,25);
    ui->tableWidget->setColumnWidth(1,400);
    ui->tableWidget->setColumnWidth(2,100);
    ui->tableWidget->setColumnWidth(3,100);
    ui->tableWidget->setColumnWidth(4,100);
    ui->tableWidget->setColumnWidth(5,100);

    ui->tableWidget->verticalHeader()->setDefaultSectionSize(16);

    // Look for DB, if it doesn't exist create it

    // fetchMovieMDB("Transformers");
    // fetchMovieRT ("Transformers");
    scanFolders("C:/data/Media/Movies");
    // cineCurrentPage = 1;
    // fetchCineRT();

}

void movieLibrary::setStatus (int statusNumber, QString status) {
    switch (statusNumber) {
        case 1:
            ui->status_one->setText(status);
        case 2:
            ui->status_two->setText(status);
        case 3:
            ui->status_three->setText(status);
        case 4:
            ui->status_four->setText(status);
        case 5:
            ui->status_five->setText(status);
        case 6:
            ui->status_six->setText(status);
        case 7:
            ui->status_seven->setText(status);
        case 8:
            ui->status_eight->setText(status);
        case 9:
            ui->status_nine->setText(status);
        case 10:
            ui->status_ten->setText(status);
    }
}

void movieLibrary::fillWithInCine(QVariantMap results) {
    int row = ui->tableWidget->rowCount();

    qDebug() << "Row Count: " << row;

    for(int i=1;i<results["movies"].toList().count();i++) {
        ui->tableWidget->insertRow(row);
        ui->tableWidget->setItem(row, 0, new QTableWidgetItem("IT", 0));
        ui->tableWidget->setItem(row, 1, new QTableWidgetItem(results["movies"].toList()[i].toMap()["title"].toString(),1));

        // Don't show a rating if there is none
        QString critics_score = results["movies"].toList()[i].toMap()["ratings"].toMap()["critics_score"].toString();
        if (critics_score != "-1") {
            ui->tableWidget->setItem(row, 2, new QTableWidgetItem(tr("%1:%2").arg(results["movies"].toList()[i].toMap()["ratings"].toMap()["critics_rating"].toString(),results["movies"].toList()[i].toMap()["ratings"].toMap()["critics_score"].toString()),2));
        }
        else {
            ui->tableWidget->setItem(row, 2, new QTableWidgetItem("N/A",2));
        }

        QString audience_score = results["movies"].toList()[i].toMap()["ratings"].toMap()["audience_score"].toString();
        if (audience_score != "0") {
            ui->tableWidget->setItem(row, 3, new QTableWidgetItem(tr("%1,%2").arg(results["movies"].toList()[i].toMap()["ratings"].toMap()["audience_rating"].toString(),results["movies"].toList()[i].toMap()["ratings"].toMap()["audience_score"].toString()),3));
        } else {
            ui->tableWidget->setItem(row, 3, new QTableWidgetItem("N/A",3));
        }

        ui->tableWidget->setItem(row, 4, new QTableWidgetItem(results["movies"].toList()[i].toMap()["year"].toString(),4));
        ui->tableWidget->setItem(row, 5, new QTableWidgetItem(results["movies"].toList()[i].toMap()["release_dates"].toMap()["theater"].toString(),5));
        ui->tableWidget->item(row,0)->setTextAlignment(Qt::AlignHCenter);
        ui->tableWidget->item(row,1)->setTextAlignment(Qt::AlignLeft);
        ui->tableWidget->item(row,2)->setTextAlignment(Qt::AlignHCenter);
        ui->tableWidget->item(row,3)->setTextAlignment(Qt::AlignHCenter);
        ui->tableWidget->item(row,4)->setTextAlignment(Qt::AlignHCenter);
        ui->tableWidget->item(row,5)->setTextAlignment(Qt::AlignHCenter);
        row++;
    }
}

void movieLibrary::fetchMovieMDB(QString movie) {
    m_manager->get(QNetworkRequest(QUrl("http://api.themoviedb.org/2.1/Movie.search/en/xml/1d5ed48aaf08ad72b4832f627a04dca3/"+movie)));
}

void movieLibrary::fetchMovieRT(QString movie) {
    // TODO: Get movie information from RT
    movie = "";
}

void movieLibrary::fetchCineRT() {
    QString qry = QString("http://api.rottentomatoes.com/api/public/v1.0/lists/movies/in_theaters.json?apikey=hyzk5vrtsy6ne8a6tut98e9t&page_limit=50&page=%1").arg(cineCurrentPage);

    qDebug() << qry;
    m_manager->get(QNetworkRequest(QUrl(qry)));
}

void movieLibrary::finishedReply(QNetworkReply *pReply) {

    bool ok;

    QByteArray data = pReply->readAll();

    QVariantMap result = parser.parse (data, &ok).toMap();

    if (!ok) { qDebug() << "Paring JSON Failed"; }

    float cineTotalPagesf = (result["total"].toFloat() + 0.5) / 50;
    cineTotalPages = qRound(cineTotalPagesf);

    setStatus(10,tr("%1: %2").arg("In Theaters",result["total"].toString()));

    qDebug() << "Total Movies: " << result["total"];
    qDebug() << "Total No. Of Pages: " << cineTotalPages;
    qDebug() << "Movies in List: " << result["movies"].toList().count();

    //qDebug() << "Synopsis: " << result["movies"].toList()[1].toMap()["synopsis"].toString();
    //qDebug() << "Ratings: " << result["movies"].toList()[1].toMap()["ratings"].toMap()["critics_rating"].toString();

    fillWithInCine(result);

    if (cineCurrentPage < cineTotalPages) {
        cineCurrentPage++;
        fetchCineRT();
    }
}


void movieLibrary::addMovieFileToDB (QString Filename) {
    Filename = "";
}

void movieLibrary::updateMovieInDB (QString Filename,
                                    QString name,
                                    QString thumbnail,
                                    QString poster,
                                    QString rating,
                                    QString overview) {

}

void movieLibrary::scanFolders(QString mF) {
    QDir movieFolder;
    QFileInfoList movieFileList;
    QStringList filters;

    filters << "*.avi" << "*.mov" << "*.mkv" << "*.mp4";

    QDirIterator it(mF, QDirIterator::Subdirectories);

    int i=0;

    while (it.hasNext()) {
        movieFolder.setPath(it.next());

        // qDebug() << movieFolder.absolutePath();

        movieFileList = movieFolder.entryInfoList(filters);

        int row = ui->tableWidget->rowCount();

        //qDebug() << "Row Count: " << row << " : " << fi.absolutePath();
        if (movieFolder.absolutePath().contains(".avi") ||
            movieFolder.absolutePath().contains(".mov") ||
            movieFolder.absolutePath().contains(".mp4") ||
            movieFolder.absolutePath().contains(".mkv") ||
            movieFolder.absolutePath().contains(".mpg")) {

            ui->tableWidget->insertRow(row);

            ui->tableWidget->setItem(row, 0, new QTableWidgetItem("U", 0));
            ui->tableWidget->setItem(row, 1, new QTableWidgetItem(movieFolder.absolutePath(),1));

            // Don't show a rating if there is none
            ui->tableWidget->item(row,0)->setTextAlignment(Qt::AlignHCenter);
            ui->tableWidget->item(row,1)->setTextAlignment(Qt::AlignLeft);

            row++;
            i++;
        }
    }

    //setStatus(9,tr("%1,%2").arg("On HDD: ",i));
/*
    int row = ui->tableWidget->rowCount();

    foreach (QFileInfo fi, movieFileList) {

        qDebug() << "Row Count: " << row << fi.baseName();

        ui->tableWidget->insertRow(row);
        ui->tableWidget->setItem(row, 0, new QTableWidgetItem("U", 0));
        ui->tableWidget->setItem(row, 1, new QTableWidgetItem(fi.baseName(),1));

        // Don't show a rating if there is none
        ui->tableWidget->item(row,0)->setTextAlignment(Qt::AlignHCenter);
        ui->tableWidget->item(row,1)->setTextAlignment(Qt::AlignLeft);

        row++;
    }*/
}

movieLibrary::~movieLibrary()
{
    delete ui;
}
