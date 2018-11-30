/********************************************************************************
** Form generated from reading UI file 'bytedatarappresentation.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BYTEDATARAPPRESENTATION_H
#define UI_BYTEDATARAPPRESENTATION_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ByteDataRappresentation
{
public:
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QSpinBox *spinBox;
    QSpinBox *spinBox_2;

    void setupUi(QWidget *ByteDataRappresentation)
    {
        if (ByteDataRappresentation->objectName().isEmpty())
            ByteDataRappresentation->setObjectName(QStringLiteral("ByteDataRappresentation"));
        ByteDataRappresentation->setEnabled(true);
        ByteDataRappresentation->resize(400, 48);
        QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(ByteDataRappresentation->sizePolicy().hasHeightForWidth());
        ByteDataRappresentation->setSizePolicy(sizePolicy);
        ByteDataRappresentation->setStyleSheet(QLatin1String("QSpinBox::disabled{background:white;color:black}\n"
"QCheckBox::indicator:unchecked:disabled{\n"
"\n"
"}\n"
"QCheckBox::indicator:checked:disabled{\n"
"     image: url(url(:/new/prefix1/pixel_green.svg));\n"
"}\n"
""));
        horizontalLayout_2 = new QHBoxLayout(ByteDataRappresentation);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(6, 0, 6, 0);
        label = new QLabel(ByteDataRappresentation);
        label->setObjectName(QStringLiteral("label"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy1);
        QFont font;
        font.setBold(true);
        font.setUnderline(true);
        font.setWeight(75);
        label->setFont(font);
        label->setFrameShape(QFrame::NoFrame);
        label->setMargin(0);

        horizontalLayout_2->addWidget(label);

        spinBox = new QSpinBox(ByteDataRappresentation);
        spinBox->setObjectName(QStringLiteral("spinBox"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(1);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(spinBox->sizePolicy().hasHeightForWidth());
        spinBox->setSizePolicy(sizePolicy2);
        spinBox->setMaximum(255);

        horizontalLayout_2->addWidget(spinBox);

        spinBox_2 = new QSpinBox(ByteDataRappresentation);
        spinBox_2->setObjectName(QStringLiteral("spinBox_2"));
        spinBox_2->setEnabled(true);
        sizePolicy2.setHeightForWidth(spinBox_2->sizePolicy().hasHeightForWidth());
        spinBox_2->setSizePolicy(sizePolicy2);
        spinBox_2->setMaximum(255);
        spinBox_2->setDisplayIntegerBase(16);

        horizontalLayout_2->addWidget(spinBox_2);


        retranslateUi(ByteDataRappresentation);
        QObject::connect(spinBox, SIGNAL(valueChanged(int)), spinBox_2, SLOT(setValue(int)));
        QObject::connect(spinBox_2, SIGNAL(valueChanged(int)), spinBox, SLOT(setValue(int)));

        QMetaObject::connectSlotsByName(ByteDataRappresentation);
    } // setupUi

    void retranslateUi(QWidget *ByteDataRappresentation)
    {
        ByteDataRappresentation->setWindowTitle(QApplication::translate("ByteDataRappresentation", "Form", 0));
        label->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class ByteDataRappresentation: public Ui_ByteDataRappresentation {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BYTEDATARAPPRESENTATION_H
