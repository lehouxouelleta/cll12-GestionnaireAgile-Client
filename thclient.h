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
    QString codeClient;
    QByteArray Tache;
    QString tacheChoisi;
    QString tacheAbandonner;
    QString codeServeur;
signals:
    void siParam();
    void siTache(QString);
    void siDeconnection();
    void siSelectionValide();
public slots:
    void slDisconnect();
    void slTerminerTache(QString);
    void slSelectionnerTache(QString);
    void slAbandonnerTache(QString);
};

#endif // THCLIENT_H
