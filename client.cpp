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
