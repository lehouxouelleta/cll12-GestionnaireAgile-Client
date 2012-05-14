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
    connect(this,SIGNAL(siTerminerTache(QString)),m_threadPrincipal,SLOT(slTerminerTache(QString)));
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
    MesTaches = list;
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
    bool veri=false;
    QTableWidgetItem *qti;
    for(int i=0;i< ui->twMesTaches->rowCount();i++)
    {
        qti=ui->twMesTaches->item(i,2);
        if(MaTache.at(2)==qti->text())
        {
           veri=true;
        }
    }
    if(veri==false)
    {
        ui->twMesTaches->setColumnCount(5);
        ui->twMesTaches->setRowCount(ui->twMesTaches->rowCount()+1);
        ui->twMesTaches->setItem(ui->twMesTaches->rowCount()-1,0,new QTableWidgetItem(MaTache.at(1)));
        ui->twMesTaches->setItem(ui->twMesTaches->rowCount()-1,1,new QTableWidgetItem(MaTache.at(2)));
        ui->twMesTaches->setItem(ui->twMesTaches->rowCount()-1,2,new QTableWidgetItem(MaTache.at(3)));
        ui->twMesTaches->setItem(ui->twMesTaches->rowCount()-1,3,new QTableWidgetItem(MaTache.at(4)));
        ui->twMesTaches->setItem(ui->twMesTaches->rowCount()-1,4,new QTableWidgetItem(MaTache.at(5)));
    }
}

void Client::on_twTacheDispo_cellClicked(int row, int column)
{
    MaTache=MesTaches.at(row).split(";");
    Ligne=row;
}

void Client::on_btnAbandonner_clicked()
{
    ui->twMesTaches->removeRow(Ligne);
}

void Client::on_twMesTaches_cellClicked(int row, int column)
{
    Ligne=row;
}

void Client::on_btnTacheTerminer_clicked()
{
    QString Envoie;
    MaTache=MesTaches.at(Ligne).split(";");
    ui->twMesTaches->removeRow(Ligne);
    ui->twMesTaches->setRowCount(ui->twMesTaches->rowCount()-1);
    Envoie+="5;";
    Envoie+=MaTache.at(0);
    emit(siTerminerTache(Envoie));
}
