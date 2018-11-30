#include "targetUiElement.h"
#include "ui_targetUiElement.h"
#include <QDebug>


targetUiElement::targetUiElement(int index, QString name, QString unityofmeasurement, int targetMilliGrams,
                                 int* stepPerMilliGrams,  bool donotAlterateMaxTimeToComplete, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::targetUiElement),
    _donotAlterateMaxTimeToComplete(donotAlterateMaxTimeToComplete)
{
    ui->setupUi(this);

    element_name = name;
    ui->label->setText(name);
    ui->label_2->setText(unityofmeasurement);

    stepPerMilliGram=1;
    pwmPercent=100;
    stepPerSecondAtMotor100PercentOn=1000;
    maxTimeToCompleteOperationMilliSec=1;
    timeToCompleteOperationMilliSec=-1;

//    if(_donotAlterateMaxTimeToComplete)
//        ui->spinBox->setMaximum(1);

    QSettings settings("mixfit.ini",QSettings::IniFormat);
    QString tmpName = name.replace(' ','_')+"_stepPerMilliGram";
    if(settings.contains(tmpName))
    {
        stepPerMilliGram = settings.value(tmpName).toInt();
    }
    else
    {
        settings.setValue(tmpName,stepPerMilliGram);
    }
    *stepPerMilliGrams = stepPerMilliGram;

    tmpName = name.replace(' ','_')+"_pwmPercent";
    if(settings.contains(tmpName))
    {
        pwmPercent = settings.value(tmpName).toInt();
    }
    else
    {
        settings.setValue(tmpName,pwmPercent);
    }


    tmpName = name.replace(' ','_')+"_stepPerSecondAtMotor100PercentOn";
    if(settings.contains(tmpName))
    {
        stepPerSecondAtMotor100PercentOn = settings.value(tmpName).toInt();
    }
    else
    {
        settings.setValue(tmpName,stepPerSecondAtMotor100PercentOn);
    }


    ui->spinBox->setValue(targetMilliGrams);
    setTargetMGram(targetMilliGrams);

    connect(ui->horizontalSlider,SIGNAL(valueChanged(int)),this,SLOT(checkAndsetSliderPosition()),Qt::QueuedConnection);
    connect(ui->spinBox,SIGNAL(valueChanged(int)),this,SLOT(setTargetMGram(int)),Qt::QueuedConnection);

    //    connect(this,SIGNAL(setEnabledSpinBox(bool)),ui->spinBox,SLOT(setEnabled(bool)));
    //    connect(this,SIGNAL(setEnabledSpinBox(bool)),ui->horizontalSlider,SLOT(setDisabled(bool)));
    //    emit setEnabledSpinBox(true);

    sliderMoved();
    connect(ui->horizontalSlider,SIGNAL(sliderMoved(int)),this,SLOT(sliderMoved()));

}

targetUiElement::~targetUiElement()
{
    //qDebug() << "deleted";
    delete ui;
}

void targetUiElement::reset()
{
    targetMilliGram = 0;
    timeToCompleteOperationMilliSec = 0;
    maxTimeToCompleteOperationMilliSec = 0;
    targetStepToDo = 0;
}

void targetUiElement::sliderMoved()
{
    int tmp = qRound(ui->horizontalSlider->value()*1.0/ui->horizontalSlider->maximum()*maxTimeToCompleteOperationMilliSec);
    ui->horizontalSlider->setToolTip("start at "+QString::number(tmp)+ " ms");
}


unsigned char targetUiElement::getValue()
{
    return ui->spinBox->value();
}

int targetUiElement::getTimeToCompleteOperationMilliSec()
{
    if(_donotAlterateMaxTimeToComplete)
        return 0;
    else
        return timeToCompleteOperationMilliSec;
}

int targetUiElement::getStartMillisec()
{
    int tmp = qRound(ui->horizontalSlider->value()*1.0/ui->horizontalSlider->maximum()*maxTimeToCompleteOperationMilliSec);
    if(targetMilliGram==0)
        tmp=0;
    return  tmp;
}


int targetUiElement::setTargetMGram(int milligrams)
{
    targetMilliGram = milligrams;
    targetStepToDo = targetMilliGram * stepPerMilliGram;

    if(_donotAlterateMaxTimeToComplete)
    {
        timeToCompleteOperationMilliSec =
                qRound(ui->horizontalSlider->maximum()*1.0 - ui->horizontalSlider->value())*maxTimeToCompleteOperationMilliSec*1.0/ui->horizontalSlider->maximum();
        if(targetMilliGram==0)
            timeToCompleteOperationMilliSec = 0;
    }
    else
    {
        int stepPerSecAtActualPwnRate = stepPerSecondAtMotor100PercentOn * pwmPercent / 100;
        timeToCompleteOperationMilliSec = targetStepToDo*1000.0/stepPerSecAtActualPwnRate;
        if(timeToCompleteOperationMilliSec > maxTimeToCompleteOperationMilliSec)
            maxTimeToCompleteOperationMilliSec = timeToCompleteOperationMilliSec;
    }

    // qDebug() << "setTargetGram time to complete: "<< timeToCompleteOperationMilliSec;

    QTimer::singleShot(1,this,SLOT(checkAndsetSliderPosition()));

    if(_donotAlterateMaxTimeToComplete)
        emit minumumTime(0);
    else
        emit minumumTime(timeToCompleteOperationMilliSec);

    return timeToCompleteOperationMilliSec;
}

void targetUiElement::setStartMillisec(int valInMills)
{
    int tmp = qRound(ui->horizontalSlider->maximum()*valInMills*1.0/maxTimeToCompleteOperationMilliSec);
    ui->horizontalSlider->setValue(tmp);
}

void targetUiElement::setMaximumTimeToCompleteOperation(int millisec)
{
    int tmpStartTime = qRound(ui->horizontalSlider->value()*1.0/ui->horizontalSlider->maximum()*maxTimeToCompleteOperationMilliSec);
    if(timeToCompleteOperationMilliSec > millisec)
    {
        maxTimeToCompleteOperationMilliSec = timeToCompleteOperationMilliSec;
    }
    else
    {
        maxTimeToCompleteOperationMilliSec = millisec;
    }


    if(_donotAlterateMaxTimeToComplete)
    {
        maxTimeToCompleteOperationMilliSec = millisec;
        timeToCompleteOperationMilliSec =
                (ui->horizontalSlider->maximum() - ui->horizontalSlider->value())*maxTimeToCompleteOperationMilliSec*1.0/ui->horizontalSlider->maximum();
        if(targetMilliGram==0)
            timeToCompleteOperationMilliSec = 0;
    }


    int newSlidervalTmp = qRound(tmpStartTime*1.0*ui->horizontalSlider->maximum()/maxTimeToCompleteOperationMilliSec);
    ui->horizontalSlider->blockSignals(true);
    ui->horizontalSlider->setValue(newSlidervalTmp);
    ui->horizontalSlider->blockSignals(false);

    checkAndsetSliderPosition();

}

void targetUiElement::setTargetMGramPublic(int milligrams)
{
    ui->spinBox->setValue(milligrams);
}


void targetUiElement::checkAndsetSliderPosition()
{

    if(_donotAlterateMaxTimeToComplete)
    {
        timeToCompleteOperationMilliSec =
                qRound(ui->horizontalSlider->maximum()*1.0 - ui->horizontalSlider->value())*maxTimeToCompleteOperationMilliSec*1.0/ui->horizontalSlider->maximum();
        if(targetMilliGram==0)
            timeToCompleteOperationMilliSec = 0;
    }

    //qDebug() << "checkAndsetSliderPosition";
    float percentNeed = 1.0*timeToCompleteOperationMilliSec/maxTimeToCompleteOperationMilliSec;


    int value = ui->horizontalSlider->value();
    int maxValue = ui->horizontalSlider->maximum();
    int valueNeeded = percentNeed*maxValue;

    ui->horizontalSlider->blockSignals(true);
    if(((maxValue - value) < valueNeeded))//&& !_donotAlterateMaxTimeToComplete)
    {
        ui->horizontalSlider->setValue(maxValue-valueNeeded);
    }

    value = ui->horizontalSlider->value();

    float gradientStop = valueNeeded*1.0/(maxValue-value);
    if(gradientStop>=0.999)
        gradientStop = 0.999;


    QString tmp1 = QString::number(gradientStop,'f',3);
    QString tmp2 = QString::number(gradientStop+0.001,'f',3);

    // qDebug() << tmp1 << " " << tmp2;

    ui->horizontalSlider->setStyleSheet(
                "QSlider::sub-page:horizontal {                          "
                "background: #fff;                                       "
                "border: 1px solid #777;                                 "
                "height: 10px;                                           "
                "border-radius: 4px;                                     "
                "}                                                       "
                "                                                        "
                "QSlider::add-page:horizontal {                          "
                "background: qlineargradient(x1: 0, y1: 0, x2: 1, y2: 0, "
                " stop: 0 #bbf, stop: "+tmp1+" #55f , stop: "+tmp2+" #ffffff);   "
                                                                   "border: 1px solid #777;                                 "
                                                                   "height: 10px;                                           "
                                                                   "border-radius: 4px;                                     "
                                                                   "}                                                       "
                                                                   "                                                        "
                                                                   "QSlider::handle:horizontal {                            "
                                                                   "background: qlineargradient(x1:0, y1:0, x2:1, y2:1,     "
                                                                   "    stop:0 #eee, stop:1 #ccc);                          "
                                                                   "border: 1px solid #777;                                 "
                                                                   "width: 13px;                                            "
                                                                   "margin-top: -2px;                                       "
                                                                   "margin-bottom: -2px;                                    "
                                                                   "border-radius: 4px;                                     "
                                                                   "}                                                       "
                                                                   "                                                        "
                                                                   "QSlider::handle:horizontal:hover {                      "
                                                                   "background: qlineargradient(x1:0, y1:0, x2:1, y2:1,     "
                                                                   "    stop:0 #fff, stop:1 #ddd);                          "
                                                                   "border: 1px solid #444;                                 "
                                                                   "border-radius: 4px;                                     "
                                                                   "}                                                       "
                );


    sliderMoved();
    ui->horizontalSlider->blockSignals(false);

//    if(ui->label->text().contains("Ev1"))
//    {
//        qDebug() << ui->horizontalSlider->styleSheet();
//        qDebug() << "timeToCompleteOperationMilliSec "<< timeToCompleteOperationMilliSec;
//        qDebug() << "maxTimeToCompleteOperationMilliSec "<< maxTimeToCompleteOperationMilliSec;
//    }

}
