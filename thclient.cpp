#include "thclient.h"

thclient::thclient(QString Nom)
{
    QTcpSocket socketClient;
    QByteArray baNom;
    socketClient.connectToHost("172.16.8.1",60123);
    socketClient.waitForConnected();
    baNom=Nom.toLocal8Bit();

    socketClient.write(baNom);
    socketClient.waitForBytesWritten();

    //socketClient.disconnectFromHost(); // Annonce de déconnexion au serveur
    //socketClient.close(); // Fermeture du socket
}
