#include "logger.h"
#include "ui_logger.h"

logger::logger(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::logger)
{
    ui->setupUi(this);

    // Open the database
    if (!logDB.open()) {
        // Display error
        QMessageBox::information(this,"Unable to create/open log database","The log file could not be opened / created. Please check console for errors.");
        qDebug() << logDB.lastError().text();   ///< Log the error to the console window if one is open
    } else {
        createEntry("logger.cpp:24", "Database created / opened", false);
    }
}

logger::~logger()
{
    delete ui;
}

bool logger::clearLog() {
    QSqlQuery qry;
    return qry.exec(QString("DELETE * FROM log;"));
}

void logger::createTables() {
    if (logDB.isOpen()) {
        QString qry = "CREATE TABLE log ("
                "id integer primary key, "
                "source varchar(50), "
                "entry varchar(255), "
                "error integer)";
        logDB.exec(qry);
    }
}

void createEntry(QString source,QString text, bool error) {
    QSqlQuery qry;
    int newId = -1;

    // If the query is successful return id
    if (qry.exec(QString("INSERT INTO log VALUES (NULL,'%1','%2','%3')").arg(source).arg(entry).arg(error))) {
        newId = qry.lastInsertId().toInt();
        emit newLogEntry(newId);
    } else {
        qDebug() << "Unable to create log entry";
    }
}
