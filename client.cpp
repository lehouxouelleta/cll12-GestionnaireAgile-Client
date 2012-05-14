#include "client.h"
#include "ui_client.h"

Client::Client(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Client)
{
    ui->setupUi(this);
    ui->twTacheDispo->resizeColumnsToContents();
    ui->twMesTaches->resizeColumnsToContents();
}

Client::~Client()
{
    delete ui;
}

void Client::on_btnConnection_clicked()
{
    QString Nom=ui->txtNomUtilisateur->text();
    m_threadPrincipal = new thclient(Nom);
    connect(m_threadPrincipal,SIGNAL(siParam()),this,SLOT(slParam()));
    connect(this,SIGNAL(siDisconnect()),m_threadPrincipal,SLOT(slDisconnect()));
    connect(m_threadPrincipal,SIGNAL(siTache(QString)),this,SLOT(slTache(QString)));
    m_threadPrincipal->start();
}

void Client::on_btnDeconnection_clicked()
{
    m_threadPrincipal->m_bEtat = false;
    emit(siDisconnect());
}
void Client::slParam()
{
    ui->btnConnection->setEnabled(false);
    ui->txtNomUtilisateur->setEnabled(false);
}
void Client::slTache(QString tache)
{
    QStringList list;
    list=tache.split("%");
    list.removeLast();
    for(int i=0;i<ui->twTacheDispo->rowCount();i++)
    {
       ui->twTacheDispo->removeRow(i);
    }
    ui->twTacheDispo->setRowCount(0);
    ui->twTacheDispo->setColumnCount(5);
    for(int i=0;i<list.size();i++)
    {
        QStringList descTache;
        descTache=list.at(i).split(";");
        ui->twTacheDispo->setRowCount(ui->twTacheDispo->rowCount()+1);
        ui->twTacheDispo->setItem(ui->twTacheDispo->rowCount()-1,0,new QTableWidgetItem(descTache.at(1)));
        ui->twTacheDispo->setItem(ui->twTacheDispo->rowCount()-1,1,new QTableWidgetItem(descTache.at(2)));
        ui->twTacheDispo->setItem(ui->twTacheDispo->rowCount()-1,2,new QTableWidgetItem(descTache.at(3)));
        ui->twTacheDispo->setItem(ui->twTacheDispo->rowCount()-1,3,new QTableWidgetItem(descTache.at(4)));
        ui->twTacheDispo->setItem(ui->twTacheDispo->rowCount()-1,4,new QTableWidgetItem(descTache.at(5)));
    }

    ui->twTacheDispo->resizeColumnsToContents();
}

void Client::on_btnSelectionner_clicked()
{

}
