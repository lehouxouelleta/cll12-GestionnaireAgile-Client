#include "thclient.h"

thclient::thclient(QString Nom)
{
    MonNom=Nom;
}
void thclient::run()
{
    QByteArray ba;
    QString baReception;
    QStringList strSplit;
    QTcpSocket socketClient;
    socketClient.connectToHost("172.16.8.1",60123);
    socketClient.waitForConnected();

    //envoie du caractère "0" pour que le serveur comprenne que je suis un nouvelle uitilisateur
    baNom="0";
    baNom+=";";
    baNom+=MonNom.toLocal8Bit();
    //Envoie du tableau de byte
    socketClient.write(baNom);
    socketClient.waitForBytesWritten();
    socketClient.waitForReadyRead();
    baReception = socketClient.read(socketClient.bytesAvailable());
    if(baReception=="#")//le # signifie un ack donc, il a reçue ma connection
    {
        emit(siParam());
    }
    do
    {
        if(socketClient.waitForReadyRead(1000))
        {
            ba=socketClient.read(socketClient.bytesAvailable());
            baReception= QString(ba);
            strSplit= baReception.split(';');
            code=strSplit.at(0);
            if(code!="0")
            {
                    if(code=="\002")
                    {
                        QString t;

                        for(int i=1;i<strSplit.size();i++)
                        {
                            t+=strSplit.at(i);
                            if(i<strSplit.size()-2 && i%6!=0)
                            {
                                t+=';';
                            }
                        }

                        emit(siTache(t));
                    }
                    else
                    {
                        if(code=="8")
                        {
                            code="9";
                        }
                    }
            }
        }
        if(codeClient=="5")
        {
            socketClient.write(Tache);
            socketClient.waitForBytesWritten();
            codeClient="0";
        }

    }while(code!="9");

    baNom="9";
    baNom+=";";
    baNom+=MonNom.toLocal8Bit();
    socketClient.write(baNom);
    socketClient.waitForBytesWritten();
    socketClient.disconnectFromHost(); // Annonce de déconnexion au serveur
    socketClient.close(); // Fermeture du socket
    emit(siDeconnection());
}
void thclient::slDisconnect()
{
    code="9";
}
void thclient::slTerminerTache(QString str)
{
    codeClient="5";
    Tache=str.toLocal8Bit();
}
