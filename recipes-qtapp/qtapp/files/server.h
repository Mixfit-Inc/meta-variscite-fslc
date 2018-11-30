#ifndef SERVER_H
#define SERVER_H

#include <QDialog>
#include <QString>
#include <QVector>

class QLabel;
class QTcpServer;
class QNetworkSession;

class Server : public QObject
{
    Q_OBJECT

public:
    explicit Server(QObject *parent = nullptr);
    enum en_status{ST_IDLE,ST_RUNNING,ST_ERROR} status;


private slots:
    void sessionOpened();
    void receivemessage();

public slots:
    void RecipeListUpdate(QList<QString> newRecipesList);
    void setStatus(en_status stat){status = stat;}
    void setErrorList(QList<unsigned char> errorList){errors = errorList;}
    void setDataLed(unsigned char ledcanister, unsigned char ledoptional);
    void setDataWaterLev(unsigned char waterLevel);
    void setDataDigIn(unsigned char digitalIN);
    //void setDataOther(unsigned char digitalIN, unsigned char waterLevel);
    void setTemperature(unsigned char temperature);

    void setPercentCompletion(unsigned char percentCompletion);
signals:
    void NewRecipeToExec(QString);
    void AbortOperation();
    void reloadXML();

private:
    QTcpServer *tcpServer = nullptr;
    QList<QString> recipesList;
    QList<unsigned char> errors;
    unsigned char _ledcanister=0;
    unsigned char _ledoptional=0;
    unsigned char _digitalIN=0;
    unsigned char _temperature=0;
    unsigned char _waterLevel=0;
    unsigned char _percentCompletion=0;


};

#endif
