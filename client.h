#ifndef CLIENT_H
#define CLIENT_H

#include <QMainWindow>
#include "thclient.h"
#include <QtGui>

namespace Ui {
class Client;
}

class Client : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit Client(QWidget *parent = 0);
    ~Client();
    
private slots:
    void on_btnConnection_clicked();

    void on_btnDeconnection_clicked();
signals:
    void siEnvoieNom(QByteArray);
private:
    Ui::Client *ui;
    thclient *m_threadPrincipal;
};

#endif // CLIENT_H
