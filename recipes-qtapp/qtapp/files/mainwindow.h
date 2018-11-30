// Author: Roberto Bellinato roberto.bellinato@egicon.com

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <spirpi.h>
//#include <bytedatarappresentation.h>
#include <targetUiElement.h>
#include <QShortcut>
#include <QDebug>
#include <QtWidgets/QGridLayout>
#include <QScrollBar>
#include <QMessageBox>
#include <QInputDialog>
#include <QTime>
#include <intelhex.h>
#include "server.h"
#include <QDir>

//using namespace intelhex;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    intelhex::hex_data* hexData;

    enum Packet{PKT_DIAGNOSTIC=0x01,PKT_WORK=0x02,PKT_TARGET=0x03,PKT_BUZZER=0x04,PKT_VERSION=0x05,
                PKT_READ_EEPROM_SET_ADDR=0x06,PKT_READ_EEPROM_GET_DATA=0x07,PKT_WRITE_EEPROM=0x08,PKT_PROGRAMMING=0x09};
    enum SoundType{SND_NO_SOUND=0x0, SND_1=0x1};
    Q_ENUMS(SoundType)
    char Motor1_pwmPercent;
    char Motor2_pwmPercent;
    char Motor3_pwmPercent;
    char Motor4_pwmPercent;
    char Motor5_pwmPercent;
    char Motor6_pwmPercent;
    char Motor7_pwmPercent;
    char Ev1_pwmPercent;
    char Ev2_pwmPercent;
    char Ev3_pwmPercent;
    char Ev4_pwmPercent;
    char MotorMixer_pwmPercent;
    char MotorHaptic_pwmPercent;
    char Water_Pump_pwmPercent;
    char Air_Pump_pwmPercent;
    char LedCanister;
    char LedOptional;
    char ExtraRequest;
    int notReadyCounter;
    int errorCntMax = 20000;
    int spiErrorCnt = 0;
    int percentCompletion = 0;
    QString xmlPath;
    bool glassPresence;
    bool prevGlassPresence;
    int status;

    void createSingleWidget(int index, QVBoxLayout *layoutVerticalScroll, QString name, QString unityofmeasurement, bool donotAlterateMaxTimeToComplete);
    void initVarFromSettings();

    void saveRecipe(QString path = "recipe.xml");

    void ShowRecipe(int index);

    QByteArray createPacketChkSumLess(Packet pktTipe, bool firstframe, SoundType sound= SND_1, quint16 eepromAddr = 0,char eepromData = 0);
    QMap<int, QByteArray> createRecipePacketList(QString recipe);
    QMap<int, QByteArray> createLoaderPacketList(QString hexFilePath);
public slots:
    void ShowRecipe(QString name);
    void SpiSendReceiveManager();
    void createListWidget();
    void setMinimumTime(int val);
    void LoadRecipeFromXml();
    void AbortOp();

    void on_pushButton_save_clicked();
    void on_pushButton_delete_clicked();
    void on_pushButton_create_clicked();

    bool ShowPrevRecipe();
    bool ShowNextRecipe();
    void Send_PKT_BUZZER();
    void Send_PKT_VERSION();
    void Send_PKT_READ_EEPROM_SET_ADDR();
    void Send_PKT_READ_EEPROM_GET_DATA();
    void Send_PKT_WRITE_EEPROM();

    void EnableAutoRecipeSending();

    void UpdateLedCanister();
    void reprogramming();
    void executeRecipe(QString recipeName);
    void gottopage0();
    void gottopageeng();
    void user1();
    void user2();
    void user3();
    void StrawberryDrink();
    void BananaDrink();
private slots:
    void on_pushButton_execute_clicked();
    void readTemperature();

signals:
    void ShowRecipeSignal(QString);
    void UpdateSpinboxDuration(int);
private:
    Ui::MainWindow *ui;
    QTimer _timer;
    SpiRpi _spiDevice;
    QByteArray qba_toWrite;
    QByteArray next_qba_toWrite;
    QByteArray qba_Read;

    QList<QByteArray> qba_packetToSend;

    QString recipeNameForLasVegasFair;

    //QByteArray qbb;
    QList<targetUiElement*> targetUiWidgetList;
    int _actualMapIndex;
    int _state;

    struct singleMotorData
    {
        QString name;
        int targetGram;
        int targetStep;
        int millisec_start;
    };

    struct recipeData
    {
        QString name;
        int duration_millisec;
        QList<singleMotorData> motorDataList;
        QMap<QString,int> motorNameIndexAssociation;
    };

    QMap<QString,recipeData> recipesMap;
    QMap<QString,int> stepGramFactorMotor;

    QMap<int, QByteArray> recipetoExec;
    QTime timerStartRecipe;
    Server tcpServer;
    QTimer readTemperatureTimer;
    unsigned char raspberryCoreTemperature = 0;

};

#endif // MAINWINDOW_H
