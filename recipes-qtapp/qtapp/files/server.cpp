#include "server.h"

#include <QtNetwork>
#include <QtCore>

#include "server.h"

Server::Server(QObject *parent)
    : QObject(parent),
      tcpServer(new QTcpServer(this))
{
    sessionOpened();
    connect(tcpServer, &QTcpServer::newConnection, this, &Server::receivemessage);

    ///////////////////////////////////////////////////
    ///////////////////////////////////////////////////
    ///
    /// List of recipes named "Recipe_X" where x [0-2000]
    ///
    for(int i=0; i<2000; i++)
        recipesList.append("Recipe_"+QString::number(i));
    ///////////////////////////////////////////////////
    ///////////////////////////////////////////////////
}

void Server::RecipeListUpdate(QList<QString> newRecipesList)
{
    recipesList = newRecipesList;
}

void Server::setDataLed(unsigned char ledcanister, unsigned char ledoptional)
{
    _ledcanister = ledcanister;
    _ledoptional = ledoptional;
}

void Server::setPercentCompletion(unsigned char percentCompletion)
{
    _percentCompletion = percentCompletion;
}


void Server::setDataDigIn(unsigned char digitalIN)
{
    _digitalIN   = digitalIN;
}

void Server::setDataWaterLev(unsigned char waterLevel)
{
    _waterLevel  = waterLevel;
}

//void Server::setDataOther(unsigned char digitalIN, unsigned char waterLevel)
//{
//    _digitalIN   = digitalIN;
//    _waterLevel  = waterLevel;
//}

void Server::setTemperature(unsigned char temperature)
{
    _temperature = temperature;
}


void Server::sessionOpened()
{
    if (!tcpServer->listen(QHostAddress::LocalHost,20486)) {
        qDebug() << "Unable to start the server";
        return;
    }
    QString ipAddress;
    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
    // use the first non-localhost IPv4 address
    for (int i = 0; i < ipAddressesList.size(); ++i) {
        if (ipAddressesList.at(i) != QHostAddress::LocalHost &&
                ipAddressesList.at(i).toIPv4Address()) {
            ipAddress = ipAddressesList.at(i).toString();
            break;
        }
    }
    // if we did not find one, use IPv4 localhost
    if (ipAddress.isEmpty())
        ipAddress = QHostAddress(QHostAddress::LocalHost).toString();
    qDebug() <<  QString("The server is running on\n\nIP: %1\nport: %2\n\nRun the message Client example now.").arg(ipAddress).arg(tcpServer->serverPort());
}

void Server::receivemessage()
{
    bool reveivedAll = false;
    int retryCnt = 0;

    QTcpSocket *clientConnection = tcpServer->nextPendingConnection();


    connect(clientConnection, &QAbstractSocket::disconnected,
            clientConnection, &QObject::deleteLater);

    QByteArray receivedMsg;
    QByteArray response;
    response.append(0x0A);

    quint64 time = QDateTime::currentMSecsSinceEpoch();
    clientConnection->waitForReadyRead(500);
    qDebug() << "elapsed for response: " << QDateTime::currentMSecsSinceEpoch()-time;


    do
    {
        retryCnt++;

        receivedMsg.append(clientConnection->readAll());
        if(receivedMsg.length()>=3)
        {
            int lenght = 0xFF;
            int reqType = 0;
            bool nok = false;
            if(receivedMsg.at(0)==0xAA)
            {
                lenght = receivedMsg.at(1);
                reqType = receivedMsg.at(2);
            }
            else
            {
                nok = true;
            }

            if(lenght!=(receivedMsg.length()-2) && (retryCnt<4))
            {
                // used in case of tcp fragmentation
                QThread::msleep(1);
                continue;
            }
            reveivedAll = true;

            switch (reqType) {
            case 0xE0:
                if((lenght>0)&& !nok)
                {
                    QString recipeName = receivedMsg.mid(3,lenght);

                    qDebug() << recipeName;
                    quint64 time = QDateTime::currentMSecsSinceEpoch();
                    bool glassPresence = (_digitalIN & 0x80)!=0;//0b10000000
                    if(recipesList.contains(recipeName) && glassPresence)
                    {
                        response.append(0x01);
                        response.append(reqType);
                        setPercentCompletion(0);
                        emit NewRecipeToExec(recipeName);
                        setPercentCompletion(0);
                    }
                    else
                    {
                        response.append(0x02);
                        response.append(0xFE);
                        response.append(0x02); // error code 0x02 --> recipe name not exist
                    }
                    qDebug() << "elapsed: " << QDateTime::currentMSecsSinceEpoch()-time;
                }
                else
                {
                    nok = true;
                    response.append(0x02);
                    response.append(0xFE);
                    response.append(0x01); // error code 0x01 --> protocol error
                }
                break;
            case 0xE1:
                if(!nok)
                {
                    response.append(0x01);
                    response.append(reqType);
                    emit AbortOperation();
                }
                else
                {
                    response.append(0x01);
                    response.append(0xFE);
                }
                break;
            case 0xE2:
                if(!nok)
                {
                    response.append(0x0C);//lenght placeholder
                    response.append(reqType);
                    response.append((char)status);

                    //assure that there are only 5 errors
                    for(int i=errors.count();i<5;i++)
                        errors.append((char)0x00);
                    for(int i=errors.count();i>5;i--)
                        errors.takeLast();

                    foreach (char err, errors)
                        response.append(err);
                    response.append(_ledoptional);
                    response.append(_ledcanister);
                    response.append(_digitalIN);
                    response.append(_temperature);
                    response.append(_waterLevel);
                    response.append(_percentCompletion);
                }
                else
                {
                    response.append(0x01);
                    response.append(0xFE);
                }
                break;
            case 0xE3:
                if(!nok)
                {
                    response.append(0x01);//lenght placeholder
                    response.append(reqType);
                    long temp = QDateTime::currentDateTime().toMSecsSinceEpoch();
                    emit reloadXML();
                    temp = QDateTime::currentDateTime().toMSecsSinceEpoch() - temp;
                    qDebug() << "Tempo per parsare l'xml "<< temp;
                }
                else
                {
                    response.append(0x01);
                    response.append(0xFE);
                }
                break;
            default:
                break;
            }
        }

    } while(!reveivedAll && retryCnt<5);


    QString debugStr = "";
    foreach (char val, receivedMsg) {
        debugStr += QString::number(val,16)+"-";
    }

    qDebug() << "receivedMsg: "<< debugStr;
    

    QByteArray len;
    len.append((unsigned char)(response.length()-2));
    response.replace(1,1,len);

    debugStr = "";
    foreach (char val, response) {
        debugStr += QString::number(val,16)+"-";
    }

    qDebug() << "response: "<< debugStr;

    clientConnection->write(response);
    clientConnection->waitForBytesWritten(100);
    clientConnection->disconnectFromHost();
}
