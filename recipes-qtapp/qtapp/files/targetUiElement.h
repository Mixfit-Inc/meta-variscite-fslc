// Author: Roberto Bellinato roberto.bellinato@egicon.com

#ifndef targetUiElement_H
#define targetUiElement_H

#include <QWidget>
#include <QCheckBox>
#include <QLabel>
#include <QSettings>
#include <QTimer>

namespace Ui {
class targetUiElement;
}

class targetUiElement : public QWidget
{
    Q_OBJECT

public:
    explicit targetUiElement(int index, QString name, QString unityofmeasurement, int targetMilliGrams, int *stepPerMilliGram, bool donotAlterateMaxTimeToComplete=false,
                             QWidget *parent = 0);
    ~targetUiElement();

    unsigned char getValue();

    int getTimeToCompleteOperationMilliSec();
    int getTargetGram(){return targetMilliGram;}


    QString getName(){return element_name;}
    int getPwmPercent(){return pwmPercent;}
    int getStartMillisec();


    void reset();
public slots:
    void setStartMillisec(int valInMills);
    void checkAndsetSliderPosition();
    void setMaximumTimeToCompleteOperation(int millisec);
    void setTargetMGramPublic(int milligrams);


private slots:
    int setTargetMGram(int milligrams);
    void sliderMoved();

signals:
    void setEnabledSpinBox(bool enabled);
    void minumumTime(int val);



private:
    Ui::targetUiElement *ui;
    QList<QLabel *> labelList;
    bool _donotAlterateMaxTimeToComplete;
    int stepPerMilliGram;
    int pwmPercent;
    int stepPerSecondAtMotor100PercentOn;
    int targetMilliGram;
    int timeToCompleteOperationMilliSec;
    int maxTimeToCompleteOperationMilliSec;
    int targetStepToDo;
    QString element_name;
};

#endif // targetUiElement_H
