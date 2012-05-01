#ifndef THCLIENT_H
#define THCLIENT_H

#include <QThread>
#include <QTcpSocket>

class thclient : public QThread
{
    Q_OBJECT
public:
    explicit thclient(QString Nom = 0);
    bool m_bEtat;
    
signals:
    
public slots:
    void slRecoieNom(QByteArray ba);
};

#endif // THCLIENT_H
