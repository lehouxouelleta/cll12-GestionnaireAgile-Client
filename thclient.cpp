#include "thclient.h"

thclient::thclient(QString Nom)
{
    MonNom=Nom;
}
void thclient::run()
{
    QByteArray ba;
    QString baReception;
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
    else
    {
        if(baReception=="@")//nack
        {

        }
    }
    //while(socketClient.waitForReadyRead())

    do
    {
        if(socketClient.waitForReadyRead(1000))
        {
            ba=socketClient.read(socketClient.bytesAvailable());
        }
        else
        {
            if(code!=0)
            {
                switch (code)
                {
                case 1:
                    break;
                }
            }
        }

    }while(code!=9);

    baNom="9";
    baNom+=";";
    baNom+=MonNom.toLocal8Bit();
    socketClient.write(baNom);
    socketClient.waitForBytesWritten();
    socketClient.disconnectFromHost(); // Annonce de déconnexion au serveur
    socketClient.close(); // Fermeture du socket
}
void thclient::slDisconnect()
{
    code=9;
}
