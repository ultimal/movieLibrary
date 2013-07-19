#ifndef LOGGER_H
#define LOGGER_H

#include <QWidget>
#include <QSqlDatabase>
#include <QSql>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlQuery>

namespace Ui {
    class logger;
}

class logger : public QWidget
{
    Q_OBJECT
    
public:
    explicit logger(QWidget *parent = 0);
    ~logger();

    void clearLog();
    void createTables();

signals:
    void newLogEntry (int logID);

public slots:
    void createEntry(QString source,QString text, bool error);
    
private:
    Ui::logger *ui;
};

#endif // LOGGER_H
