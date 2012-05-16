#include "client.h"
#include "ui_client.h"

Client::Client(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Client)
{
    ui->setupUi(this);
    ui->twTacheDispo->resizeColumnsToContents();
    ui->twMesTaches->resizeColumnsToContents();
    BonusTotal=0;
    ui->btnDeconnection->setEnabled(false);
    ui->btnSelectionner->setEnabled(false);
    ui->btnAbandonner->setEnabled(false);
    ui->btnTacheTerminer->setEnabled(false);
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
    connect(m_threadPrincipal,SIGNAL(siDeconnection()),this,SLOT(slDeconnection()));
    connect(this,SIGNAL(siSelectionnerTache(QString)),m_threadPrincipal,SLOT(slSelectionnerTache(QString)));
    connect(this,SIGNAL(siAbandonTache(QString)),m_threadPrincipal,SLOT(slAbandonnerTache(QString)));
    connect(m_threadPrincipal,SIGNAL(siSelectionValide()),this,SLOT(slSelectionValide()));
    m_threadPrincipal->start();
}

void Client::on_btnDeconnection_clicked()
{
    ui->twTacheDispo->setEnabled(true);
    m_threadPrincipal->m_bEtat = false;
    emit(siDisconnect());
}
void Client::slParam()
{
    ui->btnConnection->setEnabled(false);
    ui->btnDeconnection->setEnabled(true);
    ui->txtNomUtilisateur->setEnabled(false);
}
void Client::slTache(QString tache)
{
    QStringList list;
    list=tache.split("%");
    list.removeLast();
    MesTaches = list;
    if(MesTaches.count()!=ui->twTacheDispo->rowCount())
    {
        for(int i=0;i<ui->twTacheDispo->rowCount();i++)
        {
           ui->twTacheDispo->removeRow(i);
        }
        ui->twTacheDispo->setRowCount(0);
        ui->twTacheDispo->setColumnCount(6);
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
            ui->twTacheDispo->setItem(ui->twTacheDispo->rowCount()-1,5,new QTableWidgetItem(descTache.at(6)));
        }

        ui->twTacheDispo->resizeColumnsToContents();
    }
    else
    {
        for(int i=0;i<list.size();i++)
        {
            QStringList descTache;
            descTache=list.at(i).split(";");
            if(descTache.at(6)!=ui->twTacheDispo->item(i,5)->text())
            {
                ui->twTacheDispo->setItem(i,5,new QTableWidgetItem(descTache.at(6)));
            }
        }

    }
}

void Client::on_btnSelectionner_clicked()
{
    if(MaTache.at(6)=="1")
    {
        QMessageBox msgBox;
        msgBox.setText("Cette tâche est prise par un autre employé.");
        msgBox.exec();
    }
    else
    {
        emit(siSelectionnerTache(tacheChoisi));
    }
    ui->twTacheDispo->clearSelection();
}
void Client::slSelectionValide()
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
        ui->btnSelectionner->setEnabled(false);
    }
    ui->twTacheDispo->setEnabled(false);
}

void Client::on_twTacheDispo_cellClicked(int row, int column)
{
    MaTache=MesTaches.at(row).split(";");
    tacheChoisi=QString("%1").arg(row);
    ui->btnSelectionner->setEnabled(true);
}

void Client::on_btnAbandonner_clicked()
{
    ui->twMesTaches->removeRow(Ligne);
    ui->btnSelectionner->setEnabled(true);
    ui->btnTacheTerminer->setEnabled(false);
    ui->btnAbandonner->setEnabled(false);
    ui->btnSelectionner->setEnabled(false);
    ui->twTacheDispo->setEnabled(true);
    emit(siAbandonTache(tacheChoisi));
}

void Client::on_twMesTaches_cellClicked(int row, int column)
{
    Ligne=0;
    Ligne=row;
    ui->btnAbandonner->setEnabled(true);
    ui->btnTacheTerminer->setEnabled(true);
}

void Client::on_btnTacheTerminer_clicked()
{
    QString Envoie;
    bool veri=false;
    Envoie+="5;";
    QString Dispo,sMaTache;
    sMaTache=ui->twMesTaches->item(Ligne,0)->text();
    for(int i=0;i< ui->twTacheDispo->rowCount();i++)
    {
        Dispo=ui->twTacheDispo->item(i,0)->text();
        if(sMaTache==Dispo)
        {
           veri=true;
           Envoie+=i;
        }
    }
    if(veri==true)
    {
        MaTache=MesTaches.at(Ligne).split(";");
        ui->twMesTaches->removeRow(Ligne);
        ui->twMesTaches->setRowCount(ui->twMesTaches->rowCount()-1);
        TacheTermine=TacheTermine+1;
        ui->txtTacheTotal->setText(QString("%1").arg(TacheTermine));
        BonusTotal+=MaTache.at(5).toInt();
        ui->txtBonusTotal->setText(QString("%1").arg(BonusTotal));
        ui->twTacheDispo->setEnabled(true);
        ui->btnAbandonner->setEnabled(false);
        ui->btnTacheTerminer->setEnabled(false);
        emit(siTerminerTache(Envoie));
    }
}
void Client::slDeconnection()
{
    ui->twMesTaches->clearContents();
    ui->twMesTaches->setRowCount(0);
    ui->twTacheDispo->clearContents();
    ui->twTacheDispo->setRowCount(0);
    ui->txtNomUtilisateur->setText("");
    ui->btnConnection->setEnabled(true);
    ui->btnDeconnection->setEnabled(false);
    ui->txtNomUtilisateur->setEnabled(true);
}
