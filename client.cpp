#include "client.h"
#include "ui_client.h"

Client::Client(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Client)
{
    ui->setupUi(this);
}

Client::~Client()
{
    delete ui;
}

void Client::on_btnConnection_clicked()
{
    QString Nom=ui->txtNomUtilisateur->text();
    m_threadPrincipal = new thclient(Nom);
    //connect(this,SIGNAL(siEnvoieNom(QByteArray)),m_threadPrincipal,SLOT(slRecoieNom(QByteArray)));
    m_threadPrincipal->m_bEtat = true;
    m_threadPrincipal->start();
}

void Client::on_btnDeconnection_clicked()
{
    m_threadPrincipal->m_bEtat = false;
}
