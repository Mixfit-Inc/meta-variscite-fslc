// Author: Roberto Bellinato roberto.bellinato@egicon.com

#define SPI_INTERVAL 50
#define MAX_OPERATION_WAIT_TIME 4000
#define PRG_PKT_DIM 101

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QXmlStreamWriter>
#include <QFile>
#include <QMetaEnum>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->label_input->setMinimumSize(20,20);
    notReadyCounter=0;
    LedCanister = 0;
    LedOptional = 0;
    prevGlassPresence = false;
    glassPresence = false;

    QMetaEnum metaenumSnd = metaObject()->enumerator(metaObject()->indexOfEnumerator("SoundType"));

    for(int i=0;i<metaenumSnd.keyCount();i++)
    {
        ui->comboBox->addItem(metaenumSnd.valueToKey(i));
        ui->comboBox_2->addItem(metaenumSnd.valueToKey(i));
    }

    connect(&_timer,SIGNAL(timeout()),this,SLOT(SpiSendReceiveManager()));
    connect(&readTemperatureTimer,SIGNAL(timeout()),this,SLOT(readTemperature()));
    connect(this,SIGNAL(ShowRecipeSignal(QString)),this,SLOT(ShowRecipe(QString)),Qt::QueuedConnection);
    connect(this,SIGNAL(UpdateSpinboxDuration(int)),ui->spinBox,SLOT(setValue(int)),Qt::QueuedConnection);


    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_Q),this,SLOT(close()));

    createListWidget();

    //QTimer::singleShot(10,this,SLOT(close()));


    initVarFromSettings();

    _actualMapIndex = 0;
    LoadRecipeFromXml();

    connect(ui->pushButton_next,SIGNAL(clicked(bool)),this,SLOT(ShowNextRecipe()));
    connect(ui->pushButton_prev,SIGNAL(clicked(bool)),this,SLOT(ShowPrevRecipe()));

    ShowPrevRecipe();


    //    QMap<int,QByteArray> aaa = MainWindow::createRecipePacketList("dddd");
    //    qDebug() << aaa;

    connect(ui->pushButton_send_buzzer,SIGNAL(clicked(bool)),this,SLOT(Send_PKT_BUZZER()));
    connect(ui->pushButton_version,SIGNAL(clicked(bool)),this,SLOT(Send_PKT_VERSION()));
    connect(ui->pushButton_READ_EEPROM_SET,SIGNAL(clicked(bool)),this,SLOT(Send_PKT_READ_EEPROM_SET_ADDR()));
    connect(ui->pushButton_READ_EEPROM_GET,SIGNAL(clicked(bool)),this,SLOT(Send_PKT_READ_EEPROM_GET_DATA()));
    connect(ui->pushButton_WRITE_EEPROM,SIGNAL(clicked(bool)),this,SLOT(Send_PKT_WRITE_EEPROM()));

    connect(ui->checkBox_LED_0,SIGNAL(toggled(bool)),this,SLOT(UpdateLedCanister()));
    connect(ui->checkBox_LED_1,SIGNAL(toggled(bool)),this,SLOT(UpdateLedCanister()));
    connect(ui->checkBox_LED_2,SIGNAL(toggled(bool)),this,SLOT(UpdateLedCanister()));
    connect(ui->checkBox_LED_3,SIGNAL(toggled(bool)),this,SLOT(UpdateLedCanister()));
    connect(ui->checkBox_LED_4,SIGNAL(toggled(bool)),this,SLOT(UpdateLedCanister()));
    connect(ui->checkBox_LED_5,SIGNAL(toggled(bool)),this,SLOT(UpdateLedCanister()));
    connect(ui->checkBox_LED_6,SIGNAL(toggled(bool)),this,SLOT(UpdateLedCanister()));
    connect(ui->checkBox_LED_7,SIGNAL(toggled(bool)),this,SLOT(UpdateLedCanister()));

    connect(ui->checkBox_LED_CupRed,SIGNAL(toggled(bool)),this,SLOT(UpdateLedCanister()));
    connect(ui->checkBox_LED_CupWhite,SIGNAL(toggled(bool)),this,SLOT(UpdateLedCanister()));


    connect(ui->checkBox_autoDebug,SIGNAL(toggled(bool)),this,SLOT(EnableAutoRecipeSending()));



    connect(&tcpServer,SIGNAL(NewRecipeToExec(QString)),this,SLOT(executeRecipe(QString)));
    connect(&tcpServer,SIGNAL(reloadXML()),this,SLOT(LoadRecipeFromXml()),Qt::QueuedConnection);

    connect(&tcpServer,SIGNAL(AbortOperation()),this,SLOT(AbortOp()),Qt::QueuedConnection);


    readTemperatureTimer.start(1000);
    _timer.start(SPI_INTERVAL);

    /* *************** FOR REPROGRAMMING ************/
    /*
    hexData = new intelhex::hex_data("MIXFIT.hex");
    hexData->fill((uint8_t)0xFF);

    qDebug() << "Size: " <<hexData->size();

    qDebug() << "Min Addr: " <<hexData->min_address();	// Lowest address
    qDebug() << "Max Addr: " <<hexData->max_address();	// Highest address
    */
    //QTimer::singleShot(5000,this,SLOT(reprogramming()));


    ui->pushButtongottopage0->setText("");
    ui->pushButtongottopageeng->setText("");
    ui->pushButton_user1->setText("");
    ui->pushButton_user2->setText("");
    ui->pushButton_user3->setText("");
    ui->pushButtonMakeStrawberryDrink->setText("");
    ui->pushButtonMakeBananaDrink->setText("");



    ui->pushButtongottopage0->setStyleSheet("background:rgba(0,0,0,0);");
    ui->pushButtongottopageeng->setStyleSheet("background:rgba(0,0,0,0);");
    ui->pushButton_user1->setStyleSheet("background:rgba(0,0,0,0);");
    ui->pushButton_user2->setStyleSheet("background:rgba(0,0,0,0);");
    ui->pushButton_user3->setStyleSheet("background:rgba(0,0,0,0);");

    ui->pushButtonMakeStrawberryDrink->setStyleSheet("background:rgba(0,0,0,0);");
    ui->pushButtonMakeBananaDrink->setStyleSheet("background:rgba(0,0,0,0);");

    connect(ui->pushButtongottopage0,SIGNAL(clicked(bool)),this,SLOT(gottopage0()));
    connect(ui->pushButtongottopageeng,SIGNAL(clicked(bool)),this,SLOT(gottopageeng()));
    connect(ui->pushButtonGoToCustomerPage,SIGNAL(clicked(bool)),this,SLOT(gottopage0()));
    connect(ui->pushButton_user1,SIGNAL(clicked(bool)),this,SLOT(user1()));
    connect(ui->pushButton_user2,SIGNAL(clicked(bool)),this,SLOT(user2()));
    connect(ui->pushButton_user3,SIGNAL(clicked(bool)),this,SLOT(user3()));

    connect(ui->pushButtonMakeStrawberryDrink,SIGNAL(clicked(bool)),this,SLOT(StrawberryDrink()));
    connect(ui->pushButtonMakeBananaDrink,SIGNAL(clicked(bool)),this,SLOT(BananaDrink()));


}

void MainWindow::gottopage0()
{
    ui->stackedWidget->setCurrentIndex(1);
}
void MainWindow::gottopageeng()
{
    ui->stackedWidget->setCurrentIndex(0);
}
void MainWindow::user1()
{
    recipeNameForLasVegasFair = "user1";
    ui->stackedWidget->setCurrentIndex(2);
}
void MainWindow::user2()
{
    recipeNameForLasVegasFair = "user2";
    ui->stackedWidget->setCurrentIndex(2);
}
void MainWindow::user3()
{
    recipeNameForLasVegasFair = "user3";
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::BananaDrink()
{
    recipeNameForLasVegasFair += "b";
    ui->stackedWidget->setCurrentIndex(1);
    qDebug() << recipeNameForLasVegasFair;
    executeRecipe(recipeNameForLasVegasFair);
}

void MainWindow::StrawberryDrink()
{
    recipeNameForLasVegasFair += "s";
    ui->stackedWidget->setCurrentIndex(1);
    qDebug() << recipeNameForLasVegasFair;
    executeRecipe(recipeNameForLasVegasFair);
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::reprogramming()
{
    recipetoExec = createLoaderPacketList("");
    //_timer.setInterval(7);
}

bool MainWindow::ShowNextRecipe()
{
    bool retVal = true;
    if((_actualMapIndex+1) < recipesMap.count())
    {
        ShowRecipe(_actualMapIndex+1);
    }
    else
    {
        ShowRecipe(_actualMapIndex);
        retVal = false;
    }
    ui->pushButton_next->setEnabled((_actualMapIndex+1) < recipesMap.count());
    ui->pushButton_prev->setEnabled((_actualMapIndex-1) >= 0);
    return retVal;
}

bool MainWindow::ShowPrevRecipe()
{
    bool retVal = true;
    if((_actualMapIndex-1) >=0 )
    {
        ShowRecipe(_actualMapIndex-1);
    }
    else
    {
        ShowRecipe(_actualMapIndex);
        retVal = false;
    }
    ui->pushButton_next->setEnabled((_actualMapIndex+1) < recipesMap.count());
    ui->pushButton_prev->setEnabled((_actualMapIndex-1) >= 0);

    return retVal;
}

void MainWindow::ShowRecipe(int index)
{
    if(index < recipesMap.count())
    {
        QMapIterator<QString, recipeData> i(recipesMap);
        int tmp_cnt=0;
        while (i.hasNext())
        {
            i.next();
            if(tmp_cnt==index)
            {
                ShowRecipe(i.key());
                //emit ShowRecipeSignal(i.key());
                _actualMapIndex = tmp_cnt;
                break;
            }
            tmp_cnt++;
        }
    }
    qDebug() << "actualIndex = " << _actualMapIndex;
}

void MainWindow::ShowRecipe(QString name)
{
    if(recipesMap.contains(name))
    {
        recipeData rcp = recipesMap.value(name);
        ui->label_recipeName->setText(rcp.name);
        int tmp_index = 0;
        ui->spinBox->setMinimum(0);
        foreach (targetUiElement* b, targetUiWidgetList)
        {
            b->reset();
            b->setTargetMGramPublic(0);
        }

        ui->spinBox->setValue(rcp.duration_millisec+1);
        foreach (targetUiElement* b, targetUiWidgetList)
        {
            if(rcp.motorDataList.count()>tmp_index)
            {
                singleMotorData smdt;
                if(rcp.motorNameIndexAssociation.contains(b->getName()))
                {
                    smdt = rcp.motorDataList.at(rcp.motorNameIndexAssociation.value(b->getName()));
                }
                else
                {
                    qDebug() << "Probabile errore nella ricetta XML!";
                    smdt = rcp.motorDataList.at(tmp_index);
                }
                b->setTargetMGramPublic(smdt.targetGram);
                b->setStartMillisec(smdt.millisec_start);
            }
            tmp_index++;
        }
        ui->spinBox->setValue(rcp.duration_millisec);
        //emit UpdateSpinboxDuration(rcp.duration_millisec);
        //qDebug() << "ui->spinBox->value() "<< ui->spinBox->value() << "-"<<rcp.duration_millisec;;
    }
}

void MainWindow::on_pushButton_save_clicked()
{
    saveRecipe();
}

void MainWindow::on_pushButton_execute_clicked()
{
    saveRecipe();
    executeRecipe(ui->label_recipeName->text());
    qDebug() << "keys" << recipetoExec.keys();
}

void MainWindow::readTemperature()
{
    QFile file("/sys/class/thermal/thermal_zone0/temp");
    if (file.open(QIODevice::ReadOnly))
    {
        QString tmp;
        QTextStream in(&file);
        in >> tmp;
        raspberryCoreTemperature = tmp.toInt()/1000;
        float tempf = tmp.toFloat()/1000;
        file.close();
        ui->label_statusBar->setText(QString::number(tempf,'f',1)+" ° C");
    }
    else
    {
      ui->label_statusBar->setText(QString("--- ° C"));
    }
}

void MainWindow::executeRecipe(QString recipeName)
{
    if(recipetoExec.count()==0 && glassPresence)
    {
        percentCompletion=0;
        tcpServer.setPercentCompletion(0);
        recipetoExec = createRecipePacketList(recipeName);
        emit ShowRecipeSignal(recipeName);
    }
}


void MainWindow::on_pushButton_create_clicked()
{
    bool ok;
    QString text = QInputDialog::getText(this, tr("New recipe"),
                                         tr("Insert new recipe name"), QLineEdit::Normal,"", &ok);
    text = text.simplified();
    if (ok)
    {
        if(text.isEmpty())
        {
            QMessageBox msgBox;
            msgBox.setText("Warning! You can't use empty name.");
            msgBox.setIcon(QMessageBox::Warning);
            msgBox.exec();
            return;
        }

        if(recipesMap.contains(text))
        {
            QMessageBox msgBox;
            msgBox.setText("Warning! Invalid name. A recipe with this name already exists");
            msgBox.setIcon(QMessageBox::Warning);
            msgBox.exec();
            return;
        }

        //        recipeData rcp;
        //        rcp.name = text;
        //        recipesMap.insert(rcp.name,rcp);
        ui->label_recipeName->setText(text);
        foreach (targetUiElement* b, targetUiWidgetList)
        {
            b->setTargetMGramPublic(0);
            b->setStartMillisec(0);
        }
        ui->spinBox->setValue(0);
        saveRecipe();
        ui->pushButton_prev->setEnabled(true);
    }
}


void MainWindow::on_pushButton_delete_clicked()
{
    if(recipesMap.count()==1)
    {
        QMessageBox msgBox;
        msgBox.setText("Warning! You can't delete all the recipes. You must have at least one recipe.");
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.exec();
    }

    recipesMap.remove(ui->label_recipeName->text());
    ShowRecipe(0);
    saveRecipe();
}


void MainWindow::LoadRecipeFromXml()
{
    QFile file(xmlPath);
    if(file.open(QIODevice::ReadOnly))
    {
        QXmlStreamReader reader(&file);

        recipesMap.clear();
        recipeData tmpRecipe;

        while (!reader.atEnd())
        {
            reader.readNext();
            if (reader.name() == "recipe")
            {
                if(reader.isStartElement())
                {
                    //qDebug() << "Nuova ricetta: " << reader.attributes().value("name");
                    tmpRecipe.name = reader.attributes().value("name").toString();
                    //qDebug() << "Durata: " << reader.attributes().value("duration");
                    tmpRecipe.duration_millisec = reader.attributes().value("duration").toInt();
                    tmpRecipe.motorDataList.clear();
                }
            }

            singleMotorData tmpMotor;
            if(reader.name() == "Motor")
            {
                //qDebug() << reader.attributes().value("name");
                tmpMotor.name = reader.attributes().value("name").toString();
                //qDebug() << reader.attributes().value("target_mgrams");
                tmpMotor.targetGram = reader.attributes().value("target_mgrams").toInt();

                tmpMotor.targetStep = tmpMotor.targetGram * stepGramFactorMotor.value(tmpMotor.name,1);

                //qDebug() << reader.attributes().value("start_millisec");
                tmpMotor.millisec_start = reader.attributes().value("start_millisec").toInt();
                tmpRecipe.motorDataList.append(tmpMotor);
                tmpRecipe.motorNameIndexAssociation.insert(tmpMotor.name,tmpRecipe.motorDataList.count()-1);
                recipesMap.insert(tmpRecipe.name,tmpRecipe);
                reader.readNext();
            }
        }


        if (reader.hasError())
        {
            qDebug() << "error detected on xml";
        }
        else
        {
            _actualMapIndex = 0;
            ShowPrevRecipe();
        }
    }

    qDebug() << "numero ricette" << recipesMap.count();

    tcpServer.RecipeListUpdate(recipesMap.keys());

}

void MainWindow::AbortOp()
{
    if(recipetoExec.count()>0)
        recipetoExec.clear();

    QMap<int,QByteArray> recipePktList;
    QByteArray targetMsg;
    targetMsg.append((char)0xC3);
    targetMsg.append((char)0x00);//counter place holder
    targetMsg.append((char)PKT_TARGET);
    targetMsg.append((char)0x10);
    targetMsg.append((char)0xFF);
    recipePktList.insert(-3,targetMsg);
    targetMsg.clear();

    targetMsg.append((char)0xC3);
    targetMsg.append((char)0x00);//counter place holder
    targetMsg.append((char)PKT_TARGET);
    targetMsg.append((char)0x20);
    targetMsg.append((char)0xFF);

    targetMsg.append((char) 0x00); // ("MOTOR_1")).targetStep >>8)));
    targetMsg.append((char) 0x00); // ("MOTOR_1")).targetStep >>0)));
    targetMsg.append((char) 0x00); // ("MOTOR_2")).targetStep >>8)));
    targetMsg.append((char) 0x00); // ("MOTOR_2")).targetStep >>0)));
    targetMsg.append((char) 0x00); // ("MOTOR_3")).targetStep >>8)));
    targetMsg.append((char) 0x00); // ("MOTOR_3")).targetStep >>0)));
    targetMsg.append((char) 0x00); // ("MOTOR_4")).targetStep >>8)));
    targetMsg.append((char) 0x00); // ("MOTOR_4")).targetStep >>0)));
    targetMsg.append((char) 0x00); // ("MOTOR_5")).targetStep >>8)));
    targetMsg.append((char) 0x00); // ("MOTOR_5")).targetStep >>0)));
    targetMsg.append((char) 0x00); // ("MOTOR_6")).targetStep >>8)));
    targetMsg.append((char) 0x00); // ("MOTOR_6")).targetStep >>0)));
    targetMsg.append((char) 0x00); // ("MOTOR_7")).targetStep >>8)));
    targetMsg.append((char) 0x00); // ("MOTOR_7")).targetStep >>0)));
    targetMsg.append((char) 0x00); //"Water_Pump"
    targetMsg.append((char) 0x00); //("Water_Pump"
    targetMsg.append((char) 0x00); //airPumpPressure
    targetMsg.append((char) 0x00); //airPumpPressure
    targetMsg.append((char) 0x00); // "Air_Pump"
    targetMsg.append((char) 0x00); // "Air_Pump"
    targetMsg.append((char) 0x00); // "Motor_Mixer"
    targetMsg.append((char) 0x00); // "Motor_Mixer"
    targetMsg.append((char) 0x00); // "Motor_Haptic"
    targetMsg.append((char) 0x00); // "Motor_Haptic"
    targetMsg.append((char) SND_1);


    for(int i = targetMsg.length();i<32;i++)
        targetMsg.append((char)0xFF);

    recipePktList.insert(-2,targetMsg);
    targetMsg.clear();

    recipetoExec = recipePktList;

}

void MainWindow::saveRecipe(QString path)
{
    qDebug() << "SAVING RECIPES XML...";
    recipeData tmpRecipe;
    tmpRecipe.name = ui->label_recipeName->text();
    tmpRecipe.duration_millisec = ui->spinBox->value();
    tmpRecipe.motorDataList.clear();

    foreach (targetUiElement* b, targetUiWidgetList)
    {
        singleMotorData tmpMotor;
        tmpMotor.name =  b->getName();
        tmpMotor.targetGram = b->getTargetGram();
        tmpMotor.targetStep = tmpMotor.targetGram * stepGramFactorMotor.value(tmpMotor.name,1);
        tmpMotor.millisec_start = b->getStartMillisec();
        tmpRecipe.motorDataList.append(tmpMotor);
        tmpRecipe.motorNameIndexAssociation.insert(tmpMotor.name,tmpRecipe.motorDataList.count()-1);
    }
    recipesMap.insert(tmpRecipe.name,tmpRecipe);


    QFile file(xmlPath);
    if(file.open(QIODevice::WriteOnly | QIODevice::Truncate))
    {
        QXmlStreamWriter stream(&file);
        stream.setAutoFormatting(true);
        stream.writeStartDocument();
        stream.writeStartElement("recipes");

        QMapIterator<QString, recipeData> i(recipesMap);
        while (i.hasNext())
        {
            i.next();
            tmpRecipe = i.value();
            stream.writeStartElement("recipe");
            stream.writeAttribute("name", tmpRecipe.name);
            stream.writeAttribute("duration", QString::number(tmpRecipe.duration_millisec));
            foreach (singleMotorData tmpMotor, tmpRecipe.motorDataList)
            {
                stream.writeStartElement("Motor");
                stream.writeAttribute("name",tmpMotor.name);
                //stream.writeAttribute("pwm_percent", QString::number(b->getPwmPercent()));
                stream.writeAttribute("target_mgrams", QString::number(tmpMotor.targetGram));
                stream.writeAttribute("start_millisec", QString::number(tmpMotor.millisec_start));
                stream.writeEndElement();
            }
            stream.writeEndElement();
        }

        stream.writeEndElement();
        stream.writeEndDocument();
        file.close();
    }


    /*

    QMapIterator<QString, recipeData> i(recipesMap);
    while (i.hasNext())
    {
        i.next();
        tmpRecipe = i.value();
        qDebug() << tmpRecipe.name;
        qDebug() <<  "duration" << QString::number(tmpRecipe.duration_millisec);
        foreach (singleMotorData tmpMotor, tmpRecipe.motorDataList)
        {
            qDebug() << "Motor name" << tmpMotor.name;
            qDebug() << "target_mgrams" << QString::number(tmpMotor.targetGram);
            qDebug() << "start_millisec" << QString::number(tmpMotor.millisec_start);
        }
    }
*/

}


void MainWindow::SpiSendReceiveManager()
{
    QByteArray msgRecipeToSend,msgRecipeToSend2;
    static unsigned int SpiSendReceiveCallingCounter=0;
    static unsigned char msgIdcounter = 0;
    static QList<unsigned char> prevErrorList = QList<unsigned char>();
    static int prevStatus = 0xFF;

    int pinReady = _spiDevice.GpioReadPin(31);
    if(pinReady < 1)
    {
        if(SPI_INTERVAL*notReadyCounter >= MAX_OPERATION_WAIT_TIME)
        {
            _spiDevice.GpioWritePin(30,true);
        }
        notReadyCounter++;
        return;
    }

    _spiDevice.GpioWritePin(30,false);
    notReadyCounter=0;

    if(pinReady>0)
    {
        ui->label_input->setPixmap(QPixmap(":/new/prefix1/pixel_green.png"));
    }
    else
    {
        ui->label_input->setPixmap(QPixmap(":/new/prefix1/pixel_red.png"));
    }

    if(ui->checkBox_output->isChecked() || (spiErrorCnt >= 5))
    {
        _spiDevice.GpioWritePin(30,true);
        spiErrorCnt=0;
        SpiSendReceiveCallingCounter=0;
        return;
    }
    else
        _spiDevice.GpioWritePin(30,false);

    SpiSendReceiveCallingCounter++;



    if((status != tcpServer.ST_IDLE) && !glassPresence && prevGlassPresence)
    {
        qDebug() << "Status " << status << " glassPresence " << glassPresence<< " prevGlassPresence " << prevGlassPresence;
        AbortOp();
    }
    prevGlassPresence = glassPresence;


    if(next_qba_toWrite.length()>0)
    {
        qba_toWrite = next_qba_toWrite;
        next_qba_toWrite.clear();
    }
    else
    {
        if(recipetoExec.count()>0)
        {
            if(prevStatus!=tcpServer.ST_RUNNING)
                tcpServer.setStatus(tcpServer.ST_RUNNING);
            prevStatus=tcpServer.ST_RUNNING;
            int elapsed = timerStartRecipe.elapsed();
            QList<int> keysList = recipetoExec.keys();
            std::sort(keysList.begin(),keysList.end());
            int firstKey = keysList.first();
            if(elapsed==0)
                timerStartRecipe.start();
            if(firstKey <= elapsed)
            {
                qDebug() << "toFinish " << recipetoExec.count() << " key sended" <<
                            firstKey  << " elapsed " << elapsed;
                msgRecipeToSend = recipetoExec.take(firstKey);
                keysList.removeFirst();
                if(recipetoExec.count()>0)
                {
                    firstKey = keysList.first();
                    msgRecipeToSend2 = recipetoExec.take(firstKey);
                }
            }
        }
        else
        {
            if(timerStartRecipe.elapsed()>0)
            {
                timerStartRecipe = QTime();
            }
        }


        if(msgRecipeToSend.length()>0)
        {
            qba_toWrite = msgRecipeToSend;
            if(msgRecipeToSend2.length()>0)
                next_qba_toWrite = msgRecipeToSend2;
        }
        else
        {

            if(qba_packetToSend.count()>1)
            {
                qba_toWrite = qba_packetToSend.takeFirst();
                next_qba_toWrite = qba_packetToSend.takeFirst();
            }
            else if(SpiSendReceiveCallingCounter>=10) // SPI_INTERVAL * 10 = 500ms
            {
                if(_timer.interval()!=SPI_INTERVAL)
                    _timer.setInterval(SPI_INTERVAL);

                SpiSendReceiveCallingCounter = 0;
                // se non invio altri messaggi
                //ogni 100 ms invio il pacchetto di diagnostica se non ho messaggi a priorità più alta da inviare
                qba_toWrite = createPacketChkSumLess(PKT_DIAGNOSTIC,true);
                next_qba_toWrite = createPacketChkSumLess(PKT_DIAGNOSTIC,false);
                //qDebug() << QDateTime::currentDateTime().toMSecsSinceEpoch() << " ogni 100 ms.....";
            }
        }
    }


    //calcolo chksum ed aggiunta ID
    if(qba_toWrite.length()>0)
    {
        QByteArray tmp_qba;
        QString tmp_string_for_debug=QDateTime::currentDateTime().toString("HH:mm:ss.zzz - SEND:");
        tmp_qba.append(msgIdcounter);
        qba_toWrite.replace(1,1,tmp_qba);
        msgIdcounter++;

        unsigned char chksum=0;
        foreach (unsigned char byte, qba_toWrite)
        {
            chksum+=byte;
            tmp_string_for_debug+= QString::number(byte,16)+'-';
        }
        qba_toWrite.append(chksum);
        tmp_string_for_debug+= QString::number(chksum,16);

        if(qba_toWrite.at(2)!=PKT_DIAGNOSTIC)
            qDebug() << tmp_string_for_debug;

        QString tmpDebug = ui->textEdit->toPlainText();
        tmpDebug.prepend(tmp_string_for_debug+"\n");

        QByteArray qba_tmp_read;
        qba_tmp_read.resize(qba_toWrite.length());
        qba_tmp_read.fill(0);

        _spiDevice.SpiOpenPort(0);
        _spiDevice.SpiWriteAndRead(0,(unsigned char*)qba_toWrite.data(),(unsigned char*)qba_tmp_read.data(),qba_toWrite.length());
        _spiDevice.SpiClosePort(0);

        //TODO  decodifica del messaggio letto

        tmp_string_for_debug="RECV ";//QDateTime::currentDateTime().toString("HH:mm:ss.zzz - RECV:");;
        chksum=0;
        unsigned char lastChar = 0xFF;
        int lenght = qba_tmp_read.length();
        foreach (char byte, qba_tmp_read)
        {
            lenght--;
            tmp_string_for_debug+= QString::number(byte,16)+'-';
            if(lenght==0)
            {
                lastChar = (unsigned char)byte;
            }
            else
            {
                chksum+=(unsigned char)byte;
            }
        }
        //chksum-=lastChar;

        tmpDebug.prepend(tmp_string_for_debug+"\n");

        if(tmpDebug.length() > 4000)
            tmpDebug.resize(2000);
        ui->textEdit->setPlainText(tmpDebug);

        if(lastChar==chksum)
        {
            spiErrorCnt = 0;
            _state = (0x00FF & qba_tmp_read.at(1));
            int counter = (0x00FF & qba_tmp_read.at(2));
            int type = (0x00FF & qba_tmp_read.at(3));
            int tof = (0x00FF & qba_toWrite.at(3));
            if(tof==0x20)
            {
                switch (type) {
                case PKT_DIAGNOSTIC:
                {
                    int err1 = (0x00FF & qba_tmp_read.at(4));
                    int err2 = (0x00FF & qba_tmp_read.at(5));
                    int err3 = (0x00FF & qba_tmp_read.at(6));
                    int err4 = (0x00FF & qba_tmp_read.at(7));
                    int err5 = 0;
                    int buttons = (0x00FF & qba_tmp_read.at(8));
                    int stat = (0x00FF & qba_tmp_read.at(9));
                    int hours = (((0x00FF & qba_tmp_read.at(10))<<8)|
                                 ((0x00FF & qba_tmp_read.at(11))<<0));
                    percentCompletion = (0x00FF & qba_tmp_read.at(12));
                    if(percentCompletion>100)
                        percentCompletion=100;
                    if(percentCompletion<0)
                        percentCompletion=0;
                    tcpServer.setPercentCompletion(percentCompletion);
                    ui->progressBar->setValue(percentCompletion);
                    tcpServer.setDataDigIn((unsigned char)buttons);
                    glassPresence = (buttons & 0x80)!=0;//0b10000000
                    if(!glassPresence)
                        qDebug() << "DIAG - " << QString::number(buttons,2);
                    status = stat;

                    switch (stat) {
                    case 0:
                        if(prevStatus!=tcpServer.ST_IDLE)
                            tcpServer.setStatus(tcpServer.ST_IDLE);
                        prevStatus=tcpServer.ST_IDLE;
                        break;
                    case 1:
                        if(prevStatus!=tcpServer.ST_RUNNING)
                            tcpServer.setStatus(tcpServer.ST_RUNNING);
                        prevStatus=tcpServer.ST_RUNNING;
                        break;
                    default:
                        break;
                    }

                    QList<unsigned char> errorList;
                    errorList.append(err1);
                    errorList.append(err2);
                    errorList.append(err3);
                    errorList.append(err4);
                    errorList.append(err5);


                    QString str = "Err[1..5]->";
                    str+=QString::number(err1)+',';
                    str+=QString::number(err2)+',';
                    str+=QString::number(err3)+',';
                    str+=QString::number(err4)+',';
                    str+=QString::number(err5)+",Buttons:";
                    str+=QString::number(buttons,2)+" Hours:";
                    str+=QString::number(hours);
                    ui->lineEdit_diagnostic->setText(str);

                    if(prevErrorList!=errorList)
                    {
                        tcpServer.setErrorList(errorList);
                        prevErrorList=errorList;
                        if(errorCntMax>0)
                        {
                            QFile file("errors_debug.txt");
                            if (file.open(QIODevice::WriteOnly | QIODevice::Append))
                            {
                                errorCntMax--;
                                QTextStream out(&file);
                                out << QDateTime::currentDateTime().toString("hh:mm:ss - ") << str << endl;
                                file.close();
                            }
                        }

                        str += "\n"+QDateTime::currentDateTime().toString() +" "+ ui->textEdit_debug_error->toPlainText();

                        if(str.length() > 4000)
                            str.resize(2000);

                        ui->textEdit_debug_error->setText(str);


                    }
                }
                    break;
                case PKT_WORK:
                {
                    int temperature = (0x00FF & qba_tmp_read.at(21));
                    int buttons = (0x00FF & qba_tmp_read.at(22));
                    int water_level = (0x00FF & qba_tmp_read.at(29));
                    int press_1 = (0x00FF & qba_tmp_read.at(30));
                    int press_2 = (0x00FF & qba_tmp_read.at(31));
                    QString str = "Temperature:";
                    str+=QString::number(temperature)+",Buttons:";
                    str+=QString::number(buttons,2)+",Water_level:";
                    str+=QString::number(water_level)+",Press1:";
                    str+=QString::number(press_1)+",Press2:";
                    str+=QString::number(press_2);
                    ui->lineEdit_work->setText(str);

                    tcpServer.setDataDigIn((unsigned char)buttons);
                    tcpServer.setDataWaterLev((unsigned char)water_level);
                    tcpServer.setTemperature((unsigned char)temperature);
//                    glassPresence = (buttons & 0x80)!=0;//0b10000000
//                    if(!glassPresence)
//                        qDebug() << "WORK - " << QString::number(buttons,2);

                }
                    break;
                case PKT_TARGET:
                    break;
                case PKT_BUZZER:
                    break;
                case PKT_VERSION:
                {
                    int fw_verH = (0x00FF & qba_tmp_read.at(4));
                    int fw_verL = (0x00FF & qba_tmp_read.at(5));
                    int hw_verH = (0x00FF & qba_tmp_read.at(6));
                    int hw_verL = (0x00FF & qba_tmp_read.at(7));
                    int boot_verH = (0x00FF & qba_tmp_read.at(8));
                    int boot_verL = (0x00FF & qba_tmp_read.at(9));
                    int ecu_batch = (((0x00FF & qba_tmp_read.at(10))<<8)|
                                     ((0x00FF & qba_tmp_read.at(11))<<0));
                    int ecu_serial = (((0x00FF & qba_tmp_read.at(12))<<8)|
                                      ((0x00FF & qba_tmp_read.at(13))<<0));
                    QString str = "fw_ver:";
                    str+=QString::number(fw_verH)+'.'+
                            QString::number(fw_verL)+",hw_ver:";
                    str+=QString::number(hw_verH)+'.'+
                            QString::number(hw_verL)+",boot_ver:";
                    str+=QString::number(boot_verH)+'.'+
                            QString::number(boot_verL)+",ecu_batch:";
                    str+=QString::number(ecu_batch)+",ecu_serial:";
                    str+=QString::number(ecu_serial);
                    ui->lineEdit_version->setText(str);
                }
                    break;
                case PKT_READ_EEPROM_SET_ADDR:
                    break;
                case PKT_READ_EEPROM_GET_DATA:
                {
                    int data0 = (0x00FF & qba_tmp_read.at(4));
                    int data1 = (0x00FF & qba_tmp_read.at(5));
                    int data2 = (0x00FF & qba_tmp_read.at(6));
                    int data3 = (0x00FF & qba_tmp_read.at(7));
                    QString str = "data: ";
                    str+=QString::number(data0,16)+'-'+
                            QString::number(data1,16)+'-'+
                            QString::number(data2,16)+'-'+
                            QString::number(data3,16);

                    ui->lineEdit_eeprom_get_data->setText(str);
                }
                    break;
                case PKT_WRITE_EEPROM:
                    break;
                case PKT_PROGRAMMING:
                    if(_timer.interval()!=7)
                        _timer.setInterval(7);
                    break;
                default:
                    break;
                }



            }
        }
        else
        {
            spiErrorCnt++;
            qDebug() << "Errore nel checksum: letto -> "<< QString::number(lastChar,16)
                     << " calcolato-> " << QString::number(chksum,16);
            QString str = QDateTime::currentDateTime().toString() +" - Spi ChkSumErr: "
                    +tmp_string_for_debug+"\n"+ ui->textEdit_debug_error->toPlainText();

            if(str.length() > 4000)
                str.resize(2000);

            ui->textEdit_debug_error->setText(str);

            if(errorCntMax>0)
            {
                QFile file("errors_debug.txt");
                if (file.open(QIODevice::WriteOnly | QIODevice::Append))
                {
                    errorCntMax--;
                    QTextStream out(&file);
                    out << QDateTime::currentDateTime().toString("hh:mm:ss") +" - Spi ChkSumErr" << endl;
                    file.close();
                }
            }



        }


        qba_toWrite.clear();
    }

}


void MainWindow::createListWidget()
{
    QWidget *scrollWidget = new QWidget();
    QVBoxLayout *layoutVerticalScroll = new QVBoxLayout(scrollWidget); // create a layer with reference to the widget
    int index = 0;

    targetUiWidgetList.clear();

    createSingleWidget(index++,layoutVerticalScroll,"MOTOR_1","mgrams",false);
    createSingleWidget(index++,layoutVerticalScroll,"MOTOR_2","mgrams",false);
    createSingleWidget(index++,layoutVerticalScroll,"MOTOR_3","mgrams",false);
    createSingleWidget(index++,layoutVerticalScroll,"MOTOR_4","mgrams",false);
    createSingleWidget(index++,layoutVerticalScroll,"MOTOR_5","mgrams",false);
    createSingleWidget(index++,layoutVerticalScroll,"MOTOR_6","mgrams",false);
    createSingleWidget(index++,layoutVerticalScroll,"MOTOR_7","mgrams",false);

    createSingleWidget(index++,layoutVerticalScroll,"Water_Pump","ml",false);
    createSingleWidget(index++,layoutVerticalScroll,"Air_Pump","drop",false);

    createSingleWidget(index++,layoutVerticalScroll,"Ev1","--",true);
    createSingleWidget(index++,layoutVerticalScroll,"Ev2","--",true);
    createSingleWidget(index++,layoutVerticalScroll,"Ev3","--",true);
    createSingleWidget(index++,layoutVerticalScroll,"Ev4","--",true);

    createSingleWidget(index++,layoutVerticalScroll,"Motor_Mixer","msecs",false);
    createSingleWidget(index++,layoutVerticalScroll,"Motor_Haptic","msecs",false);


    ui->scrollArea->setWidget(scrollWidget);

    qDebug() << "create list widget";

}

void MainWindow::createSingleWidget(int index, QVBoxLayout* layoutVerticalScroll, QString name,  QString unityofmeasurement, bool donotAlterateMaxTimeToComplete)
{
    int stepPerMilliGramTmp=0;
    targetUiElement* b = new targetUiElement(index,name, unityofmeasurement,0,&stepPerMilliGramTmp,donotAlterateMaxTimeToComplete);
    stepGramFactorMotor.insert(name,stepPerMilliGramTmp);


    connect(b,SIGNAL(minumumTime(int)),this,SLOT(setMinimumTime(int)));
    connect(ui->spinBox,SIGNAL(valueChanged(int)),b,SLOT(setMaximumTimeToCompleteOperation(int)));

    targetUiWidgetList.append(b);
    layoutVerticalScroll->addWidget(b);            // Set the checkbox in the layer
    layoutVerticalScroll->setAlignment(Qt::AlignCenter);  // Center the checkbox
    layoutVerticalScroll->setContentsMargins(0,0,0,0);    // Set the zero padding
}

void MainWindow::initVarFromSettings()
{
    Motor1_pwmPercent=100;
    Motor2_pwmPercent=100;
    Motor3_pwmPercent=100;
    Motor4_pwmPercent=100;
    Motor5_pwmPercent=100;
    Motor6_pwmPercent=100;
    Motor7_pwmPercent=100;
    Ev1_pwmPercent=100;
    Ev2_pwmPercent=100;
    Ev3_pwmPercent=100;
    Ev4_pwmPercent=100;
    MotorMixer_pwmPercent=100;
    MotorHaptic_pwmPercent=100;
    Water_Pump_pwmPercent=100;
    Air_Pump_pwmPercent=100;
    xmlPath = QDir::homePath()+"/.local/share/mixfit/recipes.xml";

    QSettings settings("mixfit.ini",QSettings::IniFormat);
    QString tmpName = "Motor1_pwmPercent";
    if(settings.contains(tmpName))
    {
        Motor1_pwmPercent = settings.value(tmpName).toInt();
    }
    else
    {
        settings.setValue(tmpName,Motor1_pwmPercent);
    }
    tmpName = "Motor2_pwmPercent";
    if(settings.contains(tmpName))
    {
        Motor2_pwmPercent = settings.value(tmpName).toInt();
    }
    else
    {
        settings.setValue(tmpName,Motor2_pwmPercent);
    }
    tmpName = "Motor3_pwmPercent";
    if(settings.contains(tmpName))
    {
        Motor3_pwmPercent = settings.value(tmpName).toInt();
    }
    else
    {
        settings.setValue(tmpName,Motor3_pwmPercent);
    }
    tmpName = "Motor4_pwmPercent";
    if(settings.contains(tmpName))
    {
        Motor4_pwmPercent = settings.value(tmpName).toInt();
    }
    else
    {
        settings.setValue(tmpName,Motor4_pwmPercent);
    }
    tmpName = "Motor5_pwmPercent";
    if(settings.contains(tmpName))
    {
        Motor5_pwmPercent = settings.value(tmpName).toInt();
    }
    else
    {
        settings.setValue(tmpName,Motor5_pwmPercent);
    }
    tmpName = "Motor6_pwmPercent";
    if(settings.contains(tmpName))
    {
        Motor6_pwmPercent = settings.value(tmpName).toInt();
    }
    else
    {
        settings.setValue(tmpName,Motor6_pwmPercent);
    }
    tmpName = "Motor7_pwmPercent";
    if(settings.contains(tmpName))
    {
        Motor7_pwmPercent = settings.value(tmpName).toInt();
    }
    else
    {
        settings.setValue(tmpName,Motor7_pwmPercent);
    }
    tmpName = "Ev1_pwmPercent";
    if(settings.contains(tmpName))
    {
        Ev1_pwmPercent = settings.value(tmpName).toInt();
    }
    else
    {
        settings.setValue(tmpName,Ev1_pwmPercent);
    }
    tmpName = "Ev2_pwmPercent";
    if(settings.contains(tmpName))
    {
        Ev2_pwmPercent = settings.value(tmpName).toInt();
    }
    else
    {
        settings.setValue(tmpName,Ev2_pwmPercent);
    }
    tmpName = "Ev3_pwmPercent";
    if(settings.contains(tmpName))
    {
        Ev3_pwmPercent = settings.value(tmpName).toInt();
    }
    else
    {
        settings.setValue(tmpName,Ev3_pwmPercent);
    }
    tmpName = "Ev4_pwmPercent";
    if(settings.contains(tmpName))
    {
        Ev4_pwmPercent = settings.value(tmpName).toInt();
    }
    else
    {
        settings.setValue(tmpName,Ev4_pwmPercent);
    }
    tmpName = "MotorMixer_pwmPercent";
    if(settings.contains(tmpName))
    {
        MotorMixer_pwmPercent = settings.value(tmpName).toInt();
    }
    else
    {
        settings.setValue(tmpName,MotorMixer_pwmPercent);
    }

    tmpName = "MotorHaptic_pwmPercent";
    if(settings.contains(tmpName))
    {
        MotorHaptic_pwmPercent = settings.value(tmpName).toInt();
    }
    else
    {
        settings.setValue(tmpName,MotorHaptic_pwmPercent);
    }
    tmpName = "Water_Pump_pwmPercent";
    if(settings.contains(tmpName))
    {
        Water_Pump_pwmPercent = settings.value(tmpName).toInt();
    }
    else
    {
        settings.setValue(tmpName,Water_Pump_pwmPercent);
    }
    tmpName = "Air_Pump_pwmPercent";
    if(settings.contains(tmpName))
    {
        Air_Pump_pwmPercent = settings.value(tmpName).toInt();
    }
    else
    {
        settings.setValue(tmpName,Air_Pump_pwmPercent);
    }
    tmpName = "XmlPath";
    if(settings.contains(tmpName))
    {
        xmlPath = settings.value(tmpName).toString();
    }
    else
    {
        settings.setValue(tmpName,xmlPath);
    }


}


void MainWindow::setMinimumTime(int val)
{

    int min = 0;
    foreach (targetUiElement* b, targetUiWidgetList)
    {
        int tmpmin = b->getTimeToCompleteOperationMilliSec();
        if(b->getTargetGram()>0)
            if(tmpmin>min)
                min = tmpmin;

    }
    if((ui->spinBox->value()<min) || (ui->spinBox->value()==0))
    {
        ui->spinBox->setValue(min);
    }

    ui->spinBox->setMinimum(min);

    //qDebug() << "setMinimumTime - minimo: "<< min;
}


QByteArray MainWindow::createPacketChkSumLess(Packet pktTipe, bool firstframe, SoundType sound, quint16 eepromAddr, char eepromData)
{
    char source = 0xC3;
    char spare = 0xFF;

    QByteArray qba;
    qba.append(source);
    qba.append((char)0);//counter place holder
    qba.append((char)pktTipe);

    if(firstframe)
    {
        qba.append((char)0x10);
        qba.append(spare);
    }
    else
    {
        int lenghtToReach=0;
        qba.append((char)0x20);

        switch (pktTipe) {
        case PKT_DIAGNOSTIC:
            lenghtToReach=13;
            break;
        case PKT_BUZZER:
            qba.append((char)sound);
            lenghtToReach=8;
            break;
        case PKT_VERSION:
            lenghtToReach=15;
            break;
        case PKT_READ_EEPROM_SET_ADDR:
            qba.append((char)(0xFF&(eepromAddr>>8)));
            qba.append((char)(0xFF&(eepromAddr>>0)));
            lenghtToReach=6;
            break;
        case PKT_READ_EEPROM_GET_DATA:
            lenghtToReach=11;
            break;
        case PKT_WRITE_EEPROM:
            qba.append((char)(0xFF&(eepromAddr>>8)));
            qba.append((char)(0xFF&(eepromAddr>>0)));
            qba.append(eepromData);
            lenghtToReach=8;
            break;

        default:
            break;
        }

        for(int i = qba.length();i<lenghtToReach;i++)
            qba.append(spare);

    }
    return qba;
}


QMap<int,QByteArray> MainWindow::createRecipePacketList(QString recipe)
{
    QMap<int,QByteArray> recipePktList;
    int airPumpPressure = 1000;
    if(recipesMap.contains(recipe))
    {
        recipeData rcpData = recipesMap.value(recipe);
        QByteArray targetMsg;

        targetMsg.append((char)0xC3);
        targetMsg.append((char)0x00);//counter place holder
        targetMsg.append((char)PKT_TARGET);
        targetMsg.append((char)0x10);
        targetMsg.append((char)0xFF);
        recipePktList.insert(-3,targetMsg);
        targetMsg.clear();

        targetMsg.append((char)0xC3);
        targetMsg.append((char)0x00);//counter place holder
        targetMsg.append((char)PKT_TARGET);
        targetMsg.append((char)0x20);
        targetMsg.append((char)0xFF);

        singleMotorData motor;

        targetMsg.append((char)(0xFF & (rcpData.motorDataList.at(rcpData.motorNameIndexAssociation.value("MOTOR_1")).targetStep >>8)));
        targetMsg.append((char)(0xFF & (rcpData.motorDataList.at(rcpData.motorNameIndexAssociation.value("MOTOR_1")).targetStep >>0)));
        targetMsg.append((char)(0xFF & (rcpData.motorDataList.at(rcpData.motorNameIndexAssociation.value("MOTOR_2")).targetStep >>8)));
        targetMsg.append((char)(0xFF & (rcpData.motorDataList.at(rcpData.motorNameIndexAssociation.value("MOTOR_2")).targetStep >>0)));
        targetMsg.append((char)(0xFF & (rcpData.motorDataList.at(rcpData.motorNameIndexAssociation.value("MOTOR_3")).targetStep >>8)));
        targetMsg.append((char)(0xFF & (rcpData.motorDataList.at(rcpData.motorNameIndexAssociation.value("MOTOR_3")).targetStep >>0)));
        targetMsg.append((char)(0xFF & (rcpData.motorDataList.at(rcpData.motorNameIndexAssociation.value("MOTOR_4")).targetStep >>8)));
        targetMsg.append((char)(0xFF & (rcpData.motorDataList.at(rcpData.motorNameIndexAssociation.value("MOTOR_4")).targetStep >>0)));
        targetMsg.append((char)(0xFF & (rcpData.motorDataList.at(rcpData.motorNameIndexAssociation.value("MOTOR_5")).targetStep >>8)));
        targetMsg.append((char)(0xFF & (rcpData.motorDataList.at(rcpData.motorNameIndexAssociation.value("MOTOR_5")).targetStep >>0)));
        targetMsg.append((char)(0xFF & (rcpData.motorDataList.at(rcpData.motorNameIndexAssociation.value("MOTOR_6")).targetStep >>8)));
        targetMsg.append((char)(0xFF & (rcpData.motorDataList.at(rcpData.motorNameIndexAssociation.value("MOTOR_6")).targetStep >>0)));
        targetMsg.append((char)(0xFF & (rcpData.motorDataList.at(rcpData.motorNameIndexAssociation.value("MOTOR_7")).targetStep >>8)));
        targetMsg.append((char)(0xFF & (rcpData.motorDataList.at(rcpData.motorNameIndexAssociation.value("MOTOR_7")).targetStep >>0)));

        targetMsg.append((char)(0xFF & (rcpData.motorDataList.at(rcpData.motorNameIndexAssociation.value("Water_Pump")).targetStep>>8)));
        targetMsg.append((char)(0xFF & (rcpData.motorDataList.at(rcpData.motorNameIndexAssociation.value("Water_Pump")).targetStep>>0)));

        targetMsg.append((char)(0xFF & (airPumpPressure>>8)));
        targetMsg.append((char)(0xFF & (airPumpPressure>>0)));

        targetMsg.append((char)(0xFF & (rcpData.motorDataList.at(rcpData.motorNameIndexAssociation.value("Air_Pump")).targetStep>>8)));
        targetMsg.append((char)(0xFF & (rcpData.motorDataList.at(rcpData.motorNameIndexAssociation.value("Air_Pump")).targetStep>>0)));

        targetMsg.append((char)(0xFF & (rcpData.motorDataList.at(rcpData.motorNameIndexAssociation.value("Motor_Mixer")).targetStep>>8)));
        targetMsg.append((char)(0xFF & (rcpData.motorDataList.at(rcpData.motorNameIndexAssociation.value("Motor_Mixer")).targetStep>>0)));

        targetMsg.append((char)(0xFF & (rcpData.motorDataList.at(rcpData.motorNameIndexAssociation.value("Motor_Haptic")).targetStep>>8)));
        targetMsg.append((char)(0xFF & (rcpData.motorDataList.at(rcpData.motorNameIndexAssociation.value("Motor_Haptic")).targetStep>>0)));

        targetMsg.append((char)(0xFF & ui->comboBox_2->currentIndex()));


        for(int i = targetMsg.length();i<32;i++)
            targetMsg.append((char)0xFF);

        recipePktList.insert(-2,targetMsg);
        targetMsg.clear();

        QList<int> startingTime;
        foreach (singleMotorData smd, rcpData.motorDataList)
        {
            if(smd.targetGram!=0)
            {
                startingTime.append(smd.millisec_start);
            }
        }
        std::sort(startingTime.begin(),startingTime.end());


        int timeToadd = 0;
        int lastTimeKeyInserted=0;
        while(startingTime.count()>0)
        {
            int startTime = startingTime.takeFirst();
            bool go = true;
            while((startingTime.count()>0) && go)
            {
                if(startingTime.at(0)<=startTime)
                {
                    startTime = startingTime.takeFirst();
                }
                else
                {
                    go=false;
                }
            }

            targetMsg.append((char)0xC3);
            targetMsg.append((char)0x00);//counter place holder
            targetMsg.append((char)PKT_WORK);
            targetMsg.append((char)0x10);
            targetMsg.append((char)0xFF);

            timeToadd = 0;
            if(recipePktList.contains(startTime-1))
                timeToadd = 1;

            recipePktList.insert(startTime+timeToadd-1,targetMsg);// first frame inserted before second frame
            targetMsg.clear();

            targetMsg.append((char)0xC3);
            targetMsg.append((char)0x00);//counter place holder
            targetMsg.append((char)PKT_WORK);
            targetMsg.append((char)0x20);


            if((rcpData.motorDataList.at(rcpData.motorNameIndexAssociation.value("MOTOR_1")).millisec_start <= startTime)&&
                    (rcpData.motorDataList.at(rcpData.motorNameIndexAssociation.value("MOTOR_1")).targetGram>0))
            {
                targetMsg.append((char)Motor1_pwmPercent);
            }
            else
            {
                targetMsg.append((char)0x00);
            }

            if((rcpData.motorDataList.at(rcpData.motorNameIndexAssociation.value("MOTOR_2")).millisec_start <= startTime)&&
                    (rcpData.motorDataList.at(rcpData.motorNameIndexAssociation.value("MOTOR_2")).targetGram>0))
            {
                targetMsg.append((char)Motor2_pwmPercent);
            }
            else
            {
                targetMsg.append((char)0x00);
            }

            if((rcpData.motorDataList.at(rcpData.motorNameIndexAssociation.value("MOTOR_3")).millisec_start <= startTime)&&
                    (rcpData.motorDataList.at(rcpData.motorNameIndexAssociation.value("MOTOR_3")).targetGram>0))
            {
                targetMsg.append((char)Motor3_pwmPercent);
            }
            else
            {
                targetMsg.append((char)0x00);
            }

            if((rcpData.motorDataList.at(rcpData.motorNameIndexAssociation.value("MOTOR_4")).millisec_start <= startTime)&&
                    (rcpData.motorDataList.at(rcpData.motorNameIndexAssociation.value("MOTOR_4")).targetGram>0))
            {
                targetMsg.append((char)Motor4_pwmPercent);
            }
            else
            {
                targetMsg.append((char)0x00);
            }

            if((rcpData.motorDataList.at(rcpData.motorNameIndexAssociation.value("MOTOR_5")).millisec_start <= startTime)&&
                    (rcpData.motorDataList.at(rcpData.motorNameIndexAssociation.value("MOTOR_5")).targetGram>0))
            {
                targetMsg.append((char)Motor5_pwmPercent);
            }
            else
            {
                targetMsg.append((char)0x00);
            }
            if((rcpData.motorDataList.at(rcpData.motorNameIndexAssociation.value("MOTOR_6")).millisec_start <= startTime)&&
                    (rcpData.motorDataList.at(rcpData.motorNameIndexAssociation.value("MOTOR_6")).targetGram>0))
            {
                targetMsg.append((char)Motor6_pwmPercent);
            }
            else
            {
                targetMsg.append((char)0x00);
            }
            if((rcpData.motorDataList.at(rcpData.motorNameIndexAssociation.value("MOTOR_7")).millisec_start <= startTime)&&
                    (rcpData.motorDataList.at(rcpData.motorNameIndexAssociation.value("MOTOR_7")).targetGram>0))
            {
                targetMsg.append((char)Motor7_pwmPercent);
            }
            else
            {
                targetMsg.append((char)0x00);
            }

            if((rcpData.motorDataList.at(rcpData.motorNameIndexAssociation.value("Ev1")).millisec_start <= startTime)&&
                    (rcpData.motorDataList.at(rcpData.motorNameIndexAssociation.value("Ev1")).targetGram>0))
            {
                targetMsg.append((char)Ev1_pwmPercent);
            }
            else
            {
                targetMsg.append((char)0x00);
            }

            if((rcpData.motorDataList.at(rcpData.motorNameIndexAssociation.value("Ev2")).millisec_start <= startTime)&&
                    (rcpData.motorDataList.at(rcpData.motorNameIndexAssociation.value("Ev2")).targetGram>0))
            {
                targetMsg.append((char)Ev2_pwmPercent);
            }
            else
            {
                targetMsg.append((char)0x00);
            }
            if((rcpData.motorDataList.at(rcpData.motorNameIndexAssociation.value("Ev3")).millisec_start <= startTime)&&
                    (rcpData.motorDataList.at(rcpData.motorNameIndexAssociation.value("Ev3")).targetGram>0))
            {
                targetMsg.append((char)Ev3_pwmPercent);
            }
            else
            {
                targetMsg.append((char)0x00);
            }
            if((rcpData.motorDataList.at(rcpData.motorNameIndexAssociation.value("Ev4")).millisec_start <= startTime)&&
                    (rcpData.motorDataList.at(rcpData.motorNameIndexAssociation.value("Ev4")).targetGram>0))
            {
                targetMsg.append((char)Ev4_pwmPercent);
            }
            else
            {
                targetMsg.append((char)0x00);
            }

            if((rcpData.motorDataList.at(rcpData.motorNameIndexAssociation.value("Motor_Mixer")).millisec_start <= startTime)&&
                    (rcpData.motorDataList.at(rcpData.motorNameIndexAssociation.value("Motor_Mixer")).targetGram>0))
            {
                targetMsg.append((char)MotorMixer_pwmPercent);
            }
            else
            {
                targetMsg.append((char)0x00);
            }

            if((rcpData.motorDataList.at(rcpData.motorNameIndexAssociation.value("Motor_Haptic")).millisec_start <= startTime)&&
                    (rcpData.motorDataList.at(rcpData.motorNameIndexAssociation.value("Motor_Haptic")).targetGram>0))
            {
                targetMsg.append((char)MotorHaptic_pwmPercent);
            }
            else
            {
                targetMsg.append((char)0x00);
            }

            if((rcpData.motorDataList.at(rcpData.motorNameIndexAssociation.value("Air_Pump")).millisec_start <= startTime)&&
                    (rcpData.motorDataList.at(rcpData.motorNameIndexAssociation.value("Air_Pump")).targetGram>0))
            {
                targetMsg.append((char)Air_Pump_pwmPercent);
            }
            else
            {
                targetMsg.append((char)0x00);
            }

            if((rcpData.motorDataList.at(rcpData.motorNameIndexAssociation.value("Water_Pump")).millisec_start <= startTime)&&
                    (rcpData.motorDataList.at(rcpData.motorNameIndexAssociation.value("Water_Pump")).targetGram>0))
            {
                targetMsg.append((char)Water_Pump_pwmPercent);
            }
            else
            {
                targetMsg.append((char)0x00);
            }

            targetMsg.append(LedCanister);
            targetMsg.append(LedOptional);

            for(int i = targetMsg.length();i<30;i++)
                targetMsg.append((char)0xFF);

            targetMsg.append(ExtraRequest);
            targetMsg.append((char)0xFF);

            for(int x = lastTimeKeyInserted; x < (startTime+timeToadd-2); x=x+200)
            {
                if(!recipePktList.contains(x) && !recipePktList.contains(x+1))
                {
                    QByteArray qba = createPacketChkSumLess(PKT_DIAGNOSTIC,true);
                    recipePktList.insert(x,qba);
                    qba = createPacketChkSumLess(PKT_DIAGNOSTIC,false);
                    recipePktList.insert(x+1,qba);
                }
            }

            recipePktList.insert(startTime+timeToadd,targetMsg);
            lastTimeKeyInserted = startTime+timeToadd;
            targetMsg.clear();
        }
        if(!recipePktList.contains(lastTimeKeyInserted+100) && !recipePktList.contains(lastTimeKeyInserted+101))
        {
            QByteArray qba = createPacketChkSumLess(PKT_DIAGNOSTIC,true);
            recipePktList.insert(lastTimeKeyInserted+100,qba);
            qba = createPacketChkSumLess(PKT_DIAGNOSTIC,false);
            recipePktList.insert(lastTimeKeyInserted+101,qba);
        }
    }

    return recipePktList;
}

void MainWindow::Send_PKT_BUZZER()
{
    QByteArray qba;
    SoundType sndType = (SoundType)ui->comboBox->currentIndex();

    qba = createPacketChkSumLess(PKT_BUZZER,true);
    qba_packetToSend.append(qba);
    qba = createPacketChkSumLess(PKT_BUZZER,false,sndType);
    qba_packetToSend.append(qba);

}
void MainWindow::Send_PKT_VERSION()
{
    QByteArray qba;
    qba = createPacketChkSumLess(PKT_VERSION,true);
    qba_packetToSend.append(qba);
    qba = createPacketChkSumLess(PKT_VERSION,false);
    qba_packetToSend.append(qba);
}
void MainWindow::Send_PKT_READ_EEPROM_SET_ADDR()
{
    QByteArray qba;

    quint16 addr = (quint16)(0xFFFF & ui->spinBox_addr_to_read->value());

    qba = createPacketChkSumLess(PKT_READ_EEPROM_SET_ADDR,true);
    qba_packetToSend.append(qba);
    qba = createPacketChkSumLess(PKT_READ_EEPROM_SET_ADDR,false,SND_NO_SOUND,addr);
    qba_packetToSend.append(qba);
}
void MainWindow::Send_PKT_READ_EEPROM_GET_DATA()
{
    QByteArray qba;
    qba = createPacketChkSumLess(PKT_READ_EEPROM_GET_DATA,true);
    qba_packetToSend.append(qba);
    qba = createPacketChkSumLess(PKT_READ_EEPROM_GET_DATA,false);
    qba_packetToSend.append(qba);
}
void MainWindow::Send_PKT_WRITE_EEPROM()
{
    QByteArray qba;

    quint16 addr = (quint16)(0xFFFF & ui->spinBox_addr_to_write->value());
    char data = (char)(0xFF & ui->spinBox_data->value());

    qba = createPacketChkSumLess(PKT_WRITE_EEPROM,true);
    qba_packetToSend.append(qba);
    qba = createPacketChkSumLess(PKT_WRITE_EEPROM,false,SND_NO_SOUND,addr,data);
    qba_packetToSend.append(qba);
}

void MainWindow::EnableAutoRecipeSending()
{
    if(ui->checkBox_autoDebug->isChecked())
    {
        if(ui->lineEdit_recipeAutomaticRepetition->text().length()!=0)
            executeRecipe(ui->lineEdit_recipeAutomaticRepetition->text());
        else
            executeRecipe(ui->label_recipeName->text());
        if(ui->spinBox_timeAutoDebug->value()>0)
            QTimer::singleShot(ui->spinBox_timeAutoDebug->value()*1000,this,SLOT(EnableAutoRecipeSending()));
    }
}

void MainWindow::UpdateLedCanister()
{
    LedCanister = 0;
    LedOptional = 0;
    int i=0;

    int val = ui->checkBox_LED_0->isChecked()?1:0;
    LedCanister |= (val<<i++);
    val = ui->checkBox_LED_1->isChecked()?1:0;
    LedCanister |= (val<<i++);
    val = ui->checkBox_LED_2->isChecked()?1:0;
    LedCanister |= (val<<i++);
    val = ui->checkBox_LED_3->isChecked()?1:0;
    LedCanister |= (val<<i++);
    val = ui->checkBox_LED_4->isChecked()?1:0;
    LedCanister |= (val<<i++);
    val = ui->checkBox_LED_5->isChecked()?1:0;
    LedCanister |= (val<<i++);
    val = ui->checkBox_LED_6->isChecked()?1:0;
    LedCanister |= (val<<i++);
    val = ui->checkBox_LED_7->isChecked()?1:0;
    LedCanister |= (val<<i++);

    val = ui->checkBox_LED_CupWhite->isChecked()?1:0;
    LedOptional |= (val<<1);
    val = ui->checkBox_LED_CupRed->isChecked()?1:0;
    LedOptional |= (val<<2);


    qDebug() << "LED CANISTER " << QString::number((quint8)LedCanister,2);
    qDebug() << "LED OPTIONAL " << QString::number((quint8)LedOptional,2);

    tcpServer.setDataLed(LedCanister,LedOptional);

}




QMap<int,QByteArray> MainWindow::createLoaderPacketList(QString hexFilePath)
{
    QMap<int,QByteArray> recipePktList;
    int cnt=0;

    QByteArray targetMsg;

    targetMsg.append((char)0xC3);
    targetMsg.append((char)0x00);//counter place holder
    targetMsg.append((char)PKT_PROGRAMMING);
    targetMsg.append((char)0x10);
    targetMsg.append((char)0xFF);
    recipePktList.insert(cnt++,targetMsg);
    targetMsg.clear();

    unsigned int address = 0x80000;
    qDebug() << "Inizio: " << QDateTime::currentDateTime();
    while(address<0x180000)
    {
        unsigned int lastAddr = address;
        targetMsg.append((char)0xC3);
        targetMsg.append((char)0x00);//counter place holder
        targetMsg.append((char)PKT_PROGRAMMING);
        targetMsg.append((char)0x20);


        for(int i=address;i<(address+(PRG_PKT_DIM-5));i++)
        {
            targetMsg.append((char)hexData->get(i));
            lastAddr = i;
        }

        recipePktList.insert(cnt++,targetMsg);
        address = lastAddr+1;
        targetMsg.clear();
    }
    qDebug() << "Inizio: " << QDateTime::currentDateTime();
    qDebug() << "How Many msg: " <<recipePktList.count();

    return recipePktList;
}
