/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QStackedWidget *stackedWidget;
    QWidget *page_5;
    QProgressBar *progressBar;
    QTabWidget *tabWidget;
    QWidget *tab;
    QGridLayout *gridLayout_2;
    QLabel *label_recipeName;
    QLabel *label_2;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QPushButton *pushButton_next;
    QLabel *label_3;
    QSpinBox *spinBox;
    QPushButton *pushButton_prev;
    QLabel *label;
    QPushButton *pushButton_create;
    QWidget *tab_2;
    QGridLayout *gridLayout_4;
    QScrollArea *scrollArea_2;
    QWidget *scrollAreaWidgetContents_2;
    QGridLayout *gridLayout_5;
    QLabel *label_6;
    QLabel *label_input;
    QPushButton *pushButton_READ_EEPROM_SET;
    QLineEdit *lineEdit_eeprom_get_data;
    QSpinBox *spinBox_addr_to_read;
    QLabel *label_9;
    QLineEdit *lineEdit_diagnostic;
    QPushButton *pushButton_WRITE_EEPROM;
    QSpinBox *spinBox_data;
    QCheckBox *checkBox_output;
    QPushButton *pushButton_version;
    QLineEdit *lineEdit_version;
    QLabel *label_8;
    QSpinBox *spinBox_addr_to_write;
    QHBoxLayout *horizontalLayout_2;
    QCheckBox *checkBox_LED_0;
    QCheckBox *checkBox_LED_1;
    QCheckBox *checkBox_LED_2;
    QCheckBox *checkBox_LED_3;
    QCheckBox *checkBox_LED_4;
    QCheckBox *checkBox_LED_5;
    QCheckBox *checkBox_LED_6;
    QCheckBox *checkBox_LED_7;
    QCheckBox *checkBox_LED_CupWhite;
    QCheckBox *checkBox_LED_CupRed;
    QLabel *label_5;
    QPushButton *pushButton_READ_EEPROM_GET;
    QLabel *label_7;
    QLabel *label_4;
    QPushButton *pushButton_send_buzzer;
    QComboBox *comboBox;
    QLineEdit *lineEdit_work;
    QWidget *tab_3;
    QGridLayout *gridLayout_6;
    QGridLayout *gridLayout_3;
    QTextEdit *textEdit;
    QWidget *tab_4;
    QGridLayout *gridLayout_8;
    QSpinBox *spinBox_timeAutoDebug;
    QLineEdit *lineEdit_recipeAutomaticRepetition;
    QLabel *label_10;
    QCheckBox *checkBox_autoDebug;
    QTextEdit *textEdit_debug_error;
    QComboBox *comboBox_2;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton_delete;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pushButton_execute;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_save;
    QLabel *label_statusBar;
    QPushButton *pushButtonGoToCustomerPage;
    QWidget *page_6;
    QLabel *label_pageCustomer;
    QPushButton *pushButtongottopageeng;
    QPushButton *pushButton_user1;
    QPushButton *pushButton_user2;
    QPushButton *pushButton_user3;
    QWidget *page;
    QLabel *label_pageDrink;
    QPushButton *pushButtongottopage0;
    QPushButton *pushButtonMakeStrawberryDrink;
    QPushButton *pushButtonMakeBananaDrink;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(800, 480);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setSpacing(0);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName(QStringLiteral("stackedWidget"));
        page_5 = new QWidget();
        page_5->setObjectName(QStringLiteral("page_5"));
        page_5->setMinimumSize(QSize(782, 0));
        progressBar = new QProgressBar(page_5);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setGeometry(QRect(10, 0, 956, 25));
        progressBar->setValue(0);
        tabWidget = new QTabWidget(page_5);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setGeometry(QRect(10, 40, 962, 355));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        gridLayout_2 = new QGridLayout(tab);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        label_recipeName = new QLabel(tab);
        label_recipeName->setObjectName(QStringLiteral("label_recipeName"));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        label_recipeName->setFont(font);

        gridLayout_2->addWidget(label_recipeName, 3, 1, 1, 2);

        label_2 = new QLabel(tab);
        label_2->setObjectName(QStringLiteral("label_2"));
        QFont font1;
        font1.setPointSize(14);
        font1.setBold(true);
        font1.setWeight(75);
        label_2->setFont(font1);
        label_2->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label_2, 0, 1, 1, 1);

        scrollArea = new QScrollArea(tab);
        scrollArea->setObjectName(QStringLiteral("scrollArea"));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 16, 16));
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(scrollAreaWidgetContents->sizePolicy().hasHeightForWidth());
        scrollAreaWidgetContents->setSizePolicy(sizePolicy);
        scrollArea->setWidget(scrollAreaWidgetContents);

        gridLayout_2->addWidget(scrollArea, 7, 0, 1, 3);

        pushButton_next = new QPushButton(tab);
        pushButton_next->setObjectName(QStringLiteral("pushButton_next"));

        gridLayout_2->addWidget(pushButton_next, 0, 2, 1, 1);

        label_3 = new QLabel(tab);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setFont(font1);
        label_3->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label_3, 3, 0, 1, 1);

        spinBox = new QSpinBox(tab);
        spinBox->setObjectName(QStringLiteral("spinBox"));
        spinBox->setCorrectionMode(QAbstractSpinBox::CorrectToNearestValue);
        spinBox->setMaximum(120000);

        gridLayout_2->addWidget(spinBox, 4, 1, 1, 1);

        pushButton_prev = new QPushButton(tab);
        pushButton_prev->setObjectName(QStringLiteral("pushButton_prev"));

        gridLayout_2->addWidget(pushButton_prev, 0, 0, 1, 1);

        label = new QLabel(tab);
        label->setObjectName(QStringLiteral("label"));
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(label, 4, 0, 1, 1);

        pushButton_create = new QPushButton(tab);
        pushButton_create->setObjectName(QStringLiteral("pushButton_create"));

        gridLayout_2->addWidget(pushButton_create, 1, 0, 1, 3);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        gridLayout_4 = new QGridLayout(tab_2);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        scrollArea_2 = new QScrollArea(tab_2);
        scrollArea_2->setObjectName(QStringLiteral("scrollArea_2"));
        scrollArea_2->setWidgetResizable(true);
        scrollAreaWidgetContents_2 = new QWidget();
        scrollAreaWidgetContents_2->setObjectName(QStringLiteral("scrollAreaWidgetContents_2"));
        scrollAreaWidgetContents_2->setGeometry(QRect(0, 0, 783, 301));
        gridLayout_5 = new QGridLayout(scrollAreaWidgetContents_2);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        label_6 = new QLabel(scrollAreaWidgetContents_2);
        label_6->setObjectName(QStringLiteral("label_6"));

        gridLayout_5->addWidget(label_6, 10, 1, 1, 1);

        label_input = new QLabel(scrollAreaWidgetContents_2);
        label_input->setObjectName(QStringLiteral("label_input"));
        label_input->setMinimumSize(QSize(20, 20));
        label_input->setMaximumSize(QSize(20, 20));
        label_input->setFrameShape(QFrame::Box);
        label_input->setScaledContents(true);

        gridLayout_5->addWidget(label_input, 2, 4, 1, 1);

        pushButton_READ_EEPROM_SET = new QPushButton(scrollAreaWidgetContents_2);
        pushButton_READ_EEPROM_SET->setObjectName(QStringLiteral("pushButton_READ_EEPROM_SET"));

        gridLayout_5->addWidget(pushButton_READ_EEPROM_SET, 8, 0, 1, 1);

        lineEdit_eeprom_get_data = new QLineEdit(scrollAreaWidgetContents_2);
        lineEdit_eeprom_get_data->setObjectName(QStringLiteral("lineEdit_eeprom_get_data"));
        lineEdit_eeprom_get_data->setEnabled(true);

        gridLayout_5->addWidget(lineEdit_eeprom_get_data, 9, 1, 1, 6);

        spinBox_addr_to_read = new QSpinBox(scrollAreaWidgetContents_2);
        spinBox_addr_to_read->setObjectName(QStringLiteral("spinBox_addr_to_read"));
        spinBox_addr_to_read->setMaximum(65535);
        spinBox_addr_to_read->setDisplayIntegerBase(16);

        gridLayout_5->addWidget(spinBox_addr_to_read, 8, 2, 1, 1);

        label_9 = new QLabel(scrollAreaWidgetContents_2);
        label_9->setObjectName(QStringLiteral("label_9"));

        gridLayout_5->addWidget(label_9, 3, 0, 1, 1);

        lineEdit_diagnostic = new QLineEdit(scrollAreaWidgetContents_2);
        lineEdit_diagnostic->setObjectName(QStringLiteral("lineEdit_diagnostic"));

        gridLayout_5->addWidget(lineEdit_diagnostic, 4, 1, 1, 6);

        pushButton_WRITE_EEPROM = new QPushButton(scrollAreaWidgetContents_2);
        pushButton_WRITE_EEPROM->setObjectName(QStringLiteral("pushButton_WRITE_EEPROM"));

        gridLayout_5->addWidget(pushButton_WRITE_EEPROM, 10, 0, 1, 1);

        spinBox_data = new QSpinBox(scrollAreaWidgetContents_2);
        spinBox_data->setObjectName(QStringLiteral("spinBox_data"));
        spinBox_data->setMaximumSize(QSize(110, 16777215));
        spinBox_data->setMaximum(255);
        spinBox_data->setDisplayIntegerBase(16);

        gridLayout_5->addWidget(spinBox_data, 10, 6, 1, 1);

        checkBox_output = new QCheckBox(scrollAreaWidgetContents_2);
        checkBox_output->setObjectName(QStringLiteral("checkBox_output"));

        gridLayout_5->addWidget(checkBox_output, 2, 0, 1, 1);

        pushButton_version = new QPushButton(scrollAreaWidgetContents_2);
        pushButton_version->setObjectName(QStringLiteral("pushButton_version"));

        gridLayout_5->addWidget(pushButton_version, 5, 0, 1, 1);

        lineEdit_version = new QLineEdit(scrollAreaWidgetContents_2);
        lineEdit_version->setObjectName(QStringLiteral("lineEdit_version"));

        gridLayout_5->addWidget(lineEdit_version, 5, 1, 1, 6);

        label_8 = new QLabel(scrollAreaWidgetContents_2);
        label_8->setObjectName(QStringLiteral("label_8"));

        gridLayout_5->addWidget(label_8, 8, 1, 1, 1);

        spinBox_addr_to_write = new QSpinBox(scrollAreaWidgetContents_2);
        spinBox_addr_to_write->setObjectName(QStringLiteral("spinBox_addr_to_write"));
        spinBox_addr_to_write->setMaximum(65535);
        spinBox_addr_to_write->setDisplayIntegerBase(16);

        gridLayout_5->addWidget(spinBox_addr_to_write, 10, 2, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        checkBox_LED_0 = new QCheckBox(scrollAreaWidgetContents_2);
        checkBox_LED_0->setObjectName(QStringLiteral("checkBox_LED_0"));

        horizontalLayout_2->addWidget(checkBox_LED_0);

        checkBox_LED_1 = new QCheckBox(scrollAreaWidgetContents_2);
        checkBox_LED_1->setObjectName(QStringLiteral("checkBox_LED_1"));

        horizontalLayout_2->addWidget(checkBox_LED_1);

        checkBox_LED_2 = new QCheckBox(scrollAreaWidgetContents_2);
        checkBox_LED_2->setObjectName(QStringLiteral("checkBox_LED_2"));

        horizontalLayout_2->addWidget(checkBox_LED_2);

        checkBox_LED_3 = new QCheckBox(scrollAreaWidgetContents_2);
        checkBox_LED_3->setObjectName(QStringLiteral("checkBox_LED_3"));

        horizontalLayout_2->addWidget(checkBox_LED_3);

        checkBox_LED_4 = new QCheckBox(scrollAreaWidgetContents_2);
        checkBox_LED_4->setObjectName(QStringLiteral("checkBox_LED_4"));

        horizontalLayout_2->addWidget(checkBox_LED_4);

        checkBox_LED_5 = new QCheckBox(scrollAreaWidgetContents_2);
        checkBox_LED_5->setObjectName(QStringLiteral("checkBox_LED_5"));

        horizontalLayout_2->addWidget(checkBox_LED_5);

        checkBox_LED_6 = new QCheckBox(scrollAreaWidgetContents_2);
        checkBox_LED_6->setObjectName(QStringLiteral("checkBox_LED_6"));

        horizontalLayout_2->addWidget(checkBox_LED_6);

        checkBox_LED_7 = new QCheckBox(scrollAreaWidgetContents_2);
        checkBox_LED_7->setObjectName(QStringLiteral("checkBox_LED_7"));

        horizontalLayout_2->addWidget(checkBox_LED_7);

        checkBox_LED_CupWhite = new QCheckBox(scrollAreaWidgetContents_2);
        checkBox_LED_CupWhite->setObjectName(QStringLiteral("checkBox_LED_CupWhite"));

        horizontalLayout_2->addWidget(checkBox_LED_CupWhite);

        checkBox_LED_CupRed = new QCheckBox(scrollAreaWidgetContents_2);
        checkBox_LED_CupRed->setObjectName(QStringLiteral("checkBox_LED_CupRed"));

        horizontalLayout_2->addWidget(checkBox_LED_CupRed);


        gridLayout_5->addLayout(horizontalLayout_2, 1, 0, 1, 7);

        label_5 = new QLabel(scrollAreaWidgetContents_2);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout_5->addWidget(label_5, 4, 0, 1, 1);

        pushButton_READ_EEPROM_GET = new QPushButton(scrollAreaWidgetContents_2);
        pushButton_READ_EEPROM_GET->setObjectName(QStringLiteral("pushButton_READ_EEPROM_GET"));

        gridLayout_5->addWidget(pushButton_READ_EEPROM_GET, 9, 0, 1, 1);

        label_7 = new QLabel(scrollAreaWidgetContents_2);
        label_7->setObjectName(QStringLiteral("label_7"));

        gridLayout_5->addWidget(label_7, 10, 4, 1, 1);

        label_4 = new QLabel(scrollAreaWidgetContents_2);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout_5->addWidget(label_4, 2, 1, 1, 2);

        pushButton_send_buzzer = new QPushButton(scrollAreaWidgetContents_2);
        pushButton_send_buzzer->setObjectName(QStringLiteral("pushButton_send_buzzer"));

        gridLayout_5->addWidget(pushButton_send_buzzer, 6, 0, 1, 1);

        comboBox = new QComboBox(scrollAreaWidgetContents_2);
        comboBox->setObjectName(QStringLiteral("comboBox"));

        gridLayout_5->addWidget(comboBox, 6, 1, 1, 6);

        lineEdit_work = new QLineEdit(scrollAreaWidgetContents_2);
        lineEdit_work->setObjectName(QStringLiteral("lineEdit_work"));

        gridLayout_5->addWidget(lineEdit_work, 3, 1, 1, 6);

        scrollArea_2->setWidget(scrollAreaWidgetContents_2);

        gridLayout_4->addWidget(scrollArea_2, 0, 0, 1, 4);

        tabWidget->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QStringLiteral("tab_3"));
        gridLayout_6 = new QGridLayout(tab_3);
        gridLayout_6->setObjectName(QStringLiteral("gridLayout_6"));
        gridLayout_3 = new QGridLayout();
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        textEdit = new QTextEdit(tab_3);
        textEdit->setObjectName(QStringLiteral("textEdit"));

        gridLayout_3->addWidget(textEdit, 0, 0, 1, 1);


        gridLayout_6->addLayout(gridLayout_3, 0, 0, 1, 1);

        tabWidget->addTab(tab_3, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName(QStringLiteral("tab_4"));
        gridLayout_8 = new QGridLayout(tab_4);
        gridLayout_8->setObjectName(QStringLiteral("gridLayout_8"));
        spinBox_timeAutoDebug = new QSpinBox(tab_4);
        spinBox_timeAutoDebug->setObjectName(QStringLiteral("spinBox_timeAutoDebug"));
        spinBox_timeAutoDebug->setMaximum(10000);
        spinBox_timeAutoDebug->setValue(30);

        gridLayout_8->addWidget(spinBox_timeAutoDebug, 1, 1, 1, 1);

        lineEdit_recipeAutomaticRepetition = new QLineEdit(tab_4);
        lineEdit_recipeAutomaticRepetition->setObjectName(QStringLiteral("lineEdit_recipeAutomaticRepetition"));

        gridLayout_8->addWidget(lineEdit_recipeAutomaticRepetition, 1, 0, 1, 1);

        label_10 = new QLabel(tab_4);
        label_10->setObjectName(QStringLiteral("label_10"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label_10->sizePolicy().hasHeightForWidth());
        label_10->setSizePolicy(sizePolicy1);

        gridLayout_8->addWidget(label_10, 0, 0, 1, 1);

        checkBox_autoDebug = new QCheckBox(tab_4);
        checkBox_autoDebug->setObjectName(QStringLiteral("checkBox_autoDebug"));

        gridLayout_8->addWidget(checkBox_autoDebug, 1, 2, 1, 1);

        textEdit_debug_error = new QTextEdit(tab_4);
        textEdit_debug_error->setObjectName(QStringLiteral("textEdit_debug_error"));

        gridLayout_8->addWidget(textEdit_debug_error, 2, 0, 1, 3);

        comboBox_2 = new QComboBox(tab_4);
        comboBox_2->setObjectName(QStringLiteral("comboBox_2"));

        gridLayout_8->addWidget(comboBox_2, 0, 1, 1, 2);

        tabWidget->addTab(tab_4, QString());
        layoutWidget = new QWidget(page_5);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(170, 410, 482, 29));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        pushButton_delete = new QPushButton(layoutWidget);
        pushButton_delete->setObjectName(QStringLiteral("pushButton_delete"));

        horizontalLayout->addWidget(pushButton_delete);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        pushButton_execute = new QPushButton(layoutWidget);
        pushButton_execute->setObjectName(QStringLiteral("pushButton_execute"));

        horizontalLayout->addWidget(pushButton_execute);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushButton_save = new QPushButton(layoutWidget);
        pushButton_save->setObjectName(QStringLiteral("pushButton_save"));

        horizontalLayout->addWidget(pushButton_save);

        label_statusBar = new QLabel(page_5);
        label_statusBar->setObjectName(QStringLiteral("label_statusBar"));
        label_statusBar->setGeometry(QRect(110, 450, 571, 17));
        pushButtonGoToCustomerPage = new QPushButton(page_5);
        pushButtonGoToCustomerPage->setObjectName(QStringLiteral("pushButtonGoToCustomerPage"));
        pushButtonGoToCustomerPage->setGeometry(QRect(20, 400, 99, 51));
        stackedWidget->addWidget(page_5);
        page_6 = new QWidget();
        page_6->setObjectName(QStringLiteral("page_6"));
        label_pageCustomer = new QLabel(page_6);
        label_pageCustomer->setObjectName(QStringLiteral("label_pageCustomer"));
        label_pageCustomer->setGeometry(QRect(0, 0, 800, 480));
        label_pageCustomer->setPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/profile")));
        label_pageCustomer->setScaledContents(false);
        label_pageCustomer->setAlignment(Qt::AlignCenter);
        pushButtongottopageeng = new QPushButton(page_6);
        pushButtongottopageeng->setObjectName(QStringLiteral("pushButtongottopageeng"));
        pushButtongottopageeng->setGeometry(QRect(10, 440, 111, 41));
        pushButtongottopageeng->setFocusPolicy(Qt::NoFocus);
        pushButton_user1 = new QPushButton(page_6);
        pushButton_user1->setObjectName(QStringLiteral("pushButton_user1"));
        pushButton_user1->setGeometry(QRect(110, 170, 181, 181));
        pushButton_user1->setFocusPolicy(Qt::NoFocus);
        pushButton_user1->setAutoFillBackground(false);
        pushButton_user2 = new QPushButton(page_6);
        pushButton_user2->setObjectName(QStringLiteral("pushButton_user2"));
        pushButton_user2->setGeometry(QRect(320, 170, 181, 181));
        pushButton_user2->setFocusPolicy(Qt::NoFocus);
        pushButton_user3 = new QPushButton(page_6);
        pushButton_user3->setObjectName(QStringLiteral("pushButton_user3"));
        pushButton_user3->setGeometry(QRect(530, 170, 181, 181));
        pushButton_user3->setFocusPolicy(Qt::NoFocus);
        stackedWidget->addWidget(page_6);
        page = new QWidget();
        page->setObjectName(QStringLiteral("page"));
        label_pageDrink = new QLabel(page);
        label_pageDrink->setObjectName(QStringLiteral("label_pageDrink"));
        label_pageDrink->setGeometry(QRect(0, 0, 800, 480));
        label_pageDrink->setPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/makedrink")));
        label_pageDrink->setScaledContents(false);
        label_pageDrink->setAlignment(Qt::AlignCenter);
        pushButtongottopage0 = new QPushButton(page);
        pushButtongottopage0->setObjectName(QStringLiteral("pushButtongottopage0"));
        pushButtongottopage0->setGeometry(QRect(20, 200, 99, 101));
        pushButtongottopage0->setFocusPolicy(Qt::NoFocus);
        pushButtonMakeStrawberryDrink = new QPushButton(page);
        pushButtonMakeStrawberryDrink->setObjectName(QStringLiteral("pushButtonMakeStrawberryDrink"));
        pushButtonMakeStrawberryDrink->setGeometry(QRect(250, 180, 131, 141));
        pushButtonMakeStrawberryDrink->setFocusPolicy(Qt::NoFocus);
        pushButtonMakeBananaDrink = new QPushButton(page);
        pushButtonMakeBananaDrink->setObjectName(QStringLiteral("pushButtonMakeBananaDrink"));
        pushButtonMakeBananaDrink->setGeometry(QRect(420, 180, 131, 141));
        pushButtonMakeBananaDrink->setFocusPolicy(Qt::NoFocus);
        stackedWidget->addWidget(page);

        gridLayout->addWidget(stackedWidget, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(2);
        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        label_recipeName->setText(QApplication::translate("MainWindow", "Default", 0));
        label_2->setText(QApplication::translate("MainWindow", "RECIPE EDITOR", 0));
        pushButton_next->setText(QApplication::translate("MainWindow", "Next Recipe", 0));
        label_3->setText(QApplication::translate("MainWindow", "RECIPE NAME: ", 0));
        pushButton_prev->setText(QApplication::translate("MainWindow", "Previuos Recipe", 0));
        label->setText(QApplication::translate("MainWindow", "Total Time for recipe (millisec):", 0));
        pushButton_create->setText(QApplication::translate("MainWindow", "Create New Recipe", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("MainWindow", "Tab 1", 0));
        label_6->setText(QApplication::translate("MainWindow", "Addr", 0));
        label_input->setText(QApplication::translate("MainWindow", "Input", 0));
        pushButton_READ_EEPROM_SET->setText(QApplication::translate("MainWindow", "Send_READ_EEPROM_SET_ADDR", 0));
        label_9->setText(QApplication::translate("MainWindow", "Work", 0));
        pushButton_WRITE_EEPROM->setText(QApplication::translate("MainWindow", "Send_WRITE_EEPROM", 0));
        checkBox_output->setText(QApplication::translate("MainWindow", "PIN_30_WRITE", 0));
        pushButton_version->setText(QApplication::translate("MainWindow", "Send_VERSION", 0));
        label_8->setText(QApplication::translate("MainWindow", "Addr", 0));
        checkBox_LED_0->setText(QApplication::translate("MainWindow", "LED0", 0));
        checkBox_LED_1->setText(QApplication::translate("MainWindow", "LED1", 0));
        checkBox_LED_2->setText(QApplication::translate("MainWindow", "LED2", 0));
        checkBox_LED_3->setText(QApplication::translate("MainWindow", "LED3", 0));
        checkBox_LED_4->setText(QApplication::translate("MainWindow", "LED4", 0));
        checkBox_LED_5->setText(QApplication::translate("MainWindow", "LED5", 0));
        checkBox_LED_6->setText(QApplication::translate("MainWindow", "LED6", 0));
        checkBox_LED_7->setText(QApplication::translate("MainWindow", "LED7", 0));
        checkBox_LED_CupWhite->setText(QApplication::translate("MainWindow", "CupWhite", 0));
        checkBox_LED_CupRed->setText(QApplication::translate("MainWindow", "CupRed", 0));
        label_5->setText(QApplication::translate("MainWindow", "Diagnostic", 0));
        pushButton_READ_EEPROM_GET->setText(QApplication::translate("MainWindow", "Send_READ_EEPROM_GET_DATA", 0));
        label_7->setText(QApplication::translate("MainWindow", "Data", 0));
        label_4->setText(QApplication::translate("MainWindow", "PIN31_READ", 0));
        pushButton_send_buzzer->setText(QApplication::translate("MainWindow", "Send_BUZZER", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("MainWindow", "Tab 2", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("MainWindow", "Tab 3", 0));
        label_10->setText(QApplication::translate("MainWindow", "Recipe Name                                                     ----       Time Auto Repetition [secs]", 0));
        checkBox_autoDebug->setText(QApplication::translate("MainWindow", "Enable ", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_4), QApplication::translate("MainWindow", "Tab 4 ", 0));
        pushButton_delete->setText(QApplication::translate("MainWindow", "Delete Recipe", 0));
        pushButton_execute->setText(QApplication::translate("MainWindow", "Execute Current Recipe", 0));
        pushButton_save->setText(QApplication::translate("MainWindow", "Save", 0));
        label_statusBar->setText(QApplication::translate("MainWindow", "Status:", 0));
        pushButtonGoToCustomerPage->setText(QApplication::translate("MainWindow", "Go to\n"
"UI Customer", 0));
        label_pageCustomer->setText(QString());
        pushButtongottopageeng->setText(QApplication::translate("MainWindow", "Go to eng page", 0));
        pushButton_user1->setText(QApplication::translate("MainWindow", "PushButton", 0));
        pushButton_user2->setText(QApplication::translate("MainWindow", "PushButton", 0));
        pushButton_user3->setText(QApplication::translate("MainWindow", "PushButton", 0));
        label_pageDrink->setText(QString());
        pushButtongottopage0->setText(QApplication::translate("MainWindow", "Go to page 0", 0));
        pushButtonMakeStrawberryDrink->setText(QApplication::translate("MainWindow", "Strawberry drink", 0));
        pushButtonMakeBananaDrink->setText(QApplication::translate("MainWindow", "Strawberry drink", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
