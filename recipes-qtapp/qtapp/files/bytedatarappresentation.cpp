#include "bytedatarappresentation.h"
#include "ui_bytedatarappresentation.h"
#include <QDebug>

ByteDataRappresentation::ByteDataRappresentation(int index, bool readOnly, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ByteDataRappresentation),
    _readOnly(readOnly)
{
    ui->setupUi(this);

    ui->label->setText(QString::number(index)+")");

    if(_readOnly)
    {
        for(int i=0;i<8;i++)
        {
            QWidget *checkBoxWidget = new QWidget();
            QLabel *labelUsedAsCheckBox = new QLabel();      // We declare and initialize the checkbox
            QHBoxLayout *layoutCheckBox = new QHBoxLayout(checkBoxWidget); // create a layer with reference to the widget
            layoutCheckBox->addWidget(labelUsedAsCheckBox);            // Set the checkbox in the layer
            layoutCheckBox->setAlignment(Qt::AlignCenter);  // Center the checkbox
            layoutCheckBox->setContentsMargins(0,0,0,0);    // Set the zero padding
            ui->horizontalLayout_2->addWidget(checkBoxWidget);
            labelList.append(labelUsedAsCheckBox);
            //labelUsedAsCheckBox->setMinimumSize(ui->spinBox->height(),ui->spinBox->height());
            labelUsedAsCheckBox->setMinimumSize(20,20);
            labelUsedAsCheckBox->setFrameShape(QFrame::Box);
            ui->spinBox->setEnabled(false);
            ui->spinBox_2->setEnabled(false);
        }
    }
    else
    {
        for(int i=0;i<8;i++)
        {
            QWidget *checkBoxWidget = new QWidget();
            QCheckBox *checkBox = new QCheckBox();      // We declare and initialize the checkbox
            QHBoxLayout *layoutCheckBox = new QHBoxLayout(checkBoxWidget); // create a layer with reference to the widget
            layoutCheckBox->addWidget(checkBox);            // Set the checkbox in the layer
            layoutCheckBox->setAlignment(Qt::AlignCenter);  // Center the checkbox
            layoutCheckBox->setContentsMargins(0,0,0,0);    // Set the zero padding
            ui->horizontalLayout_2->addWidget(checkBoxWidget);
            checkBoxList.append(checkBox);
            connect(checkBox,SIGNAL(stateChanged(int)),this,SLOT(SpinBoxIntUpdateFromCheckbox()));
        }
    }


    connect(ui->spinBox,SIGNAL(valueChanged(int)),this,SLOT(CheckBoxUpdateFromInt(int)));

}

ByteDataRappresentation::~ByteDataRappresentation()
{
    //qDebug() << "deleted";
    delete ui;
}


void ByteDataRappresentation::CheckBoxUpdateFromInt(int val)
{
    if(_readOnly)
    {
        //qDebug() << "read only update";

        int tmp_val = val;
        for(int i=7;i>=0;i--)
        {
            if(tmp_val%2==1)
            {
                labelList.at(i)->setPixmap(QPixmap(":/new/prefix1/pixel_green.png"));
                labelList.at(i)->setScaledContents(true);
                labelList.at(i)->setFrameShape(QFrame::Box);
            }
            else
            {
                labelList.at(i)->setPixmap(QPixmap(":/new/prefix1/pixel_red.png"));
                labelList.at(i)->setScaledContents(true);
                labelList.at(i)->setFrameShape(QFrame::Box);
            }
            tmp_val = (tmp_val >> 1);
        }
    }
    else
    {
        //qDebug() << "not read only update";
        for(int i=0;i<8;i++)
        {
            checkBoxList.at(i)->blockSignals(true);
        }

        int tmp_val = val;

        for(int i=7;i>=0;i--)
        {
            checkBoxList.at(i)->setChecked(tmp_val%2==1);
            tmp_val = (tmp_val >> 1);
        }

        for(int i=0;i<8;i++)
        {
            checkBoxList.at(i)->blockSignals(false);
        }
    }

    //qDebug() << "update checkbox";

}

void ByteDataRappresentation::SpinBoxIntUpdateFromCheckbox()
{

    int tmp_val = 0;

    for(int i=7;i>=0;i--)
    {
        int tmp = (int)checkBoxList.at(i)->isChecked();
        tmp = tmp << (7-i);
        tmp_val += tmp;
    }

    ui->spinBox->blockSignals(true);
    ui->spinBox_2->blockSignals(true);

    ui->spinBox->setValue(tmp_val);
    ui->spinBox_2->setValue(tmp_val);

    ui->spinBox->blockSignals(false);
    ui->spinBox_2->blockSignals(false);
    //qDebug() << "update spinbox";
}

unsigned char ByteDataRappresentation::getValue()
{
    return ui->spinBox->value();
}

void ByteDataRappresentation::setValue(int value)
{
    if(value > ui->spinBox->maximum())
        ui->spinBox->setValue(ui->spinBox->maximum());
    else if(value < ui->spinBox->minimum())
        ui->spinBox->setValue(ui->spinBox->minimum());
    else
        ui->spinBox->setValue(value);

    CheckBoxUpdateFromInt(ui->spinBox->value());
}
