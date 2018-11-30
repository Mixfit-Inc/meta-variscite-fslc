/********************************************************************************
** Form generated from reading UI file 'targetUiElement.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TARGETUIELEMENT_H
#define UI_TARGETUIELEMENT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_targetUiElement
{
public:
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QLabel *label_2;
    QSpinBox *spinBox;
    QSlider *horizontalSlider;

    void setupUi(QWidget *targetUiElement)
    {
        if (targetUiElement->objectName().isEmpty())
            targetUiElement->setObjectName(QStringLiteral("targetUiElement"));
        targetUiElement->setEnabled(true);
        targetUiElement->resize(866, 48);
        QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(targetUiElement->sizePolicy().hasHeightForWidth());
        targetUiElement->setSizePolicy(sizePolicy);
        targetUiElement->setStyleSheet(QLatin1String("QSpinBox::disabled{background:white;color:black}\n"
"QCheckBox::indicator:unchecked:disabled{\n"
"\n"
"}\n"
"QCheckBox::indicator:checked:disabled{\n"
"     image: url(url(:/new/prefix1/pixel_green.svg));\n"
"}\n"
""));
        horizontalLayout_2 = new QHBoxLayout(targetUiElement);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(6, 0, 6, 0);
        label = new QLabel(targetUiElement);
        label->setObjectName(QStringLiteral("label"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy1);
        label->setMinimumSize(QSize(150, 0));
        QFont font;
        font.setBold(true);
        font.setUnderline(true);
        font.setWeight(75);
        label->setFont(font);
        label->setFrameShape(QFrame::NoFrame);
        label->setMargin(0);

        horizontalLayout_2->addWidget(label);

        label_2 = new QLabel(targetUiElement);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setMinimumSize(QSize(50, 0));
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_2->addWidget(label_2);

        spinBox = new QSpinBox(targetUiElement);
        spinBox->setObjectName(QStringLiteral("spinBox"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(spinBox->sizePolicy().hasHeightForWidth());
        spinBox->setSizePolicy(sizePolicy2);
        spinBox->setMaximum(65535);

        horizontalLayout_2->addWidget(spinBox);

        horizontalSlider = new QSlider(targetUiElement);
        horizontalSlider->setObjectName(QStringLiteral("horizontalSlider"));
        QSizePolicy sizePolicy3(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(horizontalSlider->sizePolicy().hasHeightForWidth());
        horizontalSlider->setSizePolicy(sizePolicy3);
        horizontalSlider->setStyleSheet(QLatin1String("QSlider::sub-page:horizontal {\n"
"background: #fff;\n"
"border: 1px solid #777;\n"
"height: 10px;\n"
"border-radius: 4px;\n"
"}\n"
"\n"
"QSlider::add-page:horizontal {\n"
"background: qlineargradient(x1: 0, y1: 0, x2: 1, y2: 0,\n"
"    stop: 0 #bbf, stop: 0.55 #55f , stop: 0.56 #ffffff);\n"
"border: 1px solid #777;\n"
"height: 10px;\n"
"border-radius: 4px;\n"
"}\n"
"\n"
"QSlider::handle:horizontal {\n"
"background: qlineargradient(x1:0, y1:0, x2:1, y2:1,\n"
"    stop:0 #eee, stop:1 #ccc);\n"
"border: 1px solid #777;\n"
"width: 13px;\n"
"margin-top: -2px;\n"
"margin-bottom: -2px;\n"
"border-radius: 4px;\n"
"}\n"
"\n"
"QSlider::handle:horizontal:hover {\n"
"background: qlineargradient(x1:0, y1:0, x2:1, y2:1,\n"
"    stop:0 #fff, stop:1 #ddd);\n"
"border: 1px solid #444;\n"
"border-radius: 4px;\n"
"}"));
        horizontalSlider->setMaximum(10000);
        horizontalSlider->setValue(0);
        horizontalSlider->setOrientation(Qt::Horizontal);

        horizontalLayout_2->addWidget(horizontalSlider);


        retranslateUi(targetUiElement);

        QMetaObject::connectSlotsByName(targetUiElement);
    } // setupUi

    void retranslateUi(QWidget *targetUiElement)
    {
        targetUiElement->setWindowTitle(QApplication::translate("targetUiElement", "Form", 0));
        label->setText(QString());
        label_2->setText(QApplication::translate("targetUiElement", "Name", 0));
    } // retranslateUi

};

namespace Ui {
    class targetUiElement: public Ui_targetUiElement {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TARGETUIELEMENT_H
