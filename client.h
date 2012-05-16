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
    QStringList MesTaches;
    QStringList MaTache;
    QString tacheChoisi;
    int Ligne;
    int TacheTermine;
    int BonusTotal;
    ~Client();
public slots:
    void slParam();
    void on_btnConnection_clicked();
    void on_btnDeconnection_clicked();
    void slTache(QString tache);
    void slDeconnection();
    void slSelectionValide();
signals:
    void siDisconnect();
    void siTerminerTache(QString);
    void siSelectionnerTache(QString);
    void siAbandonTache(QString);

private slots:
    void on_btnSelectionner_clicked();
    void on_twTacheDispo_cellClicked(int row, int column);

    void on_btnAbandonner_clicked();

    void on_twMesTaches_cellClicked(int row, int column);

    void on_btnTacheTerminer_clicked();

private:
    Ui::Client *ui;
    thclient *m_threadPrincipal;
};

#endif // CLIENT_H
