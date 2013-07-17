#ifndef MOVIEDB_H
#define MOVIEDB_H

#include <QObject>

class movieDB : public QObject
{
    Q_OBJECT
public:
    explicit movieDB(QObject *parent = 0);
    
signals:
    
public slots:
    
};

#endif // MOVIEDB_H
