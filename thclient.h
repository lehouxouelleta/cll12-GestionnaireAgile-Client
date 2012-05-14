#ifndef THCLIENT_H
#define THCLIENT_H

#include <QThread>
#include <QTcpSocket>
#include <QtGui>

class thclient : public QThread
{
    Q_OBJECT
public:
    explicit thclient(QString Nom = 0);
    bool m_bEtat;
    void run();
    QByteArray baNom;
    QString MonNom;
    QTcpSocket *socketClient;
    QString code;
signals:
    void siParam();
    void siTache(QString);
public slots:
    void slDisconnect();
};

#endif // THCLIENT_H
