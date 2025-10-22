/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QLabel *label_10;
    QPushButton *btnLogin;
    QLineEdit *lineUser;
    QLineEdit *linePass;
    QLabel *label_11;
    QLabel *label_41;
    QWidget *page_1;
    QDateEdit *dateEdit;
    QLineEdit *lineEdit_5;
    QLabel *label_5;
    QLabel *label_2;
    QLineEdit *lineEdit_4;
    QLabel *label;
    QLabel *label_7;
    QPushButton *btnGestionClients_PageStock;
    QLineEdit *lineEdit_3;
    QPushButton *pushButton_5;
    QPushButton *pushButton_4;
    QDateEdit *dateEdit_2;
    QPushButton *btnGestionEmployes_PageStock;
    QLabel *label_4;
    QLabel *label_6;
    QLineEdit *lineEdit;
    QLabel *labelImage;
    QLabel *label_8;
    QLineEdit *lineEdit_2;
    QLabel *label_3;
    QComboBox *comboBox;
    QPushButton *btnGestionSponsors_PageStock;
    QPushButton *btnGestionFournisseurs_PageStock;
    QGroupBox *groupBox_3;
    QTableWidget *tableWidget;
    QLabel *label_48;
    QGroupBox *groupBox_5;
    QPushButton *pushButton_20;
    QPushButton *pushButton_17;
    QPushButton *pushButton_21;
    QRadioButton *radioButton_10;
    QRadioButton *radioButton_11;
    QRadioButton *radioButton_12;
    QLineEdit *lineEdit_28;
    QLabel *label_49;
    QGroupBox *groupBox_7;
    QPushButton *pushButton_3;
    QPushButton *pushButton_22;
    QPushButton *btnBack_PageStock;
    QWidget *page_2;
    QPushButton *btnBack_PageClients;
    QLabel *label_47;
    QLabel *label_59;
    QLabel *label_58;
    QWidget *page_3;
    QPushButton *btnGestionStock_Page_Employes;
    QPushButton *btnGestionClients_Page_Employes;
    QLineEdit *lineEdit_16;
    QPushButton *btnGestionSponsors_Page_Employes;
    QPushButton *btnGestionFournisseurs_Page_Employes;
    QLabel *label_17;
    QLabel *label_18;
    QDateEdit *dateEdit_3;
    QLabel *label_19;
    QRadioButton *radioButton;
    QRadioButton *radioButton_2;
    QRadioButton *radioButton_3;
    QLabel *label_20;
    QSpinBox *spinBox;
    QLabel *label_21;
    QSpinBox *spinBox_2;
    QLabel *label_22;
    QCheckBox *checkBox;
    QCheckBox *checkBox_3;
    QCheckBox *checkBox_2;
    QLabel *label_25;
    QDateEdit *dateEdit_4;
    QLabel *label_26;
    QLabel *label_27;
    QLineEdit *lineEdit_17;
    QLineEdit *lineEdit_18;
    QPushButton *btnBack_Page_Employes;
    QLabel *label_46;
    QGroupBox *groupBox_10;
    QTableWidget *tableWidget_4;
    QGroupBox *groupBox_11;
    QWidget *page_4;
    QLabel *label_45;
    QLabel *label_31;
    QLabel *label_54;
    QWidget *page_5;
    QMenuBar *menubar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1477, 1179);
        MainWindow->setStyleSheet(QString::fromUtf8("QMainWindow {\n"
"    background-image: url(:/images/background.jpg); /* chemin de ton image */\n"
"    background-repeat: no-repeat;\n"
"    background-position: center;\n"
"    background-attachment: fixed;\n"
"\n"
"  \n"
"}\n"
"\n"
" /* Labels */ QLabel { font-size: 14px; font-weight: bold; color: #A5D6A7; /* vert p\303\242le */ } /* Champs de saisie */ QLineEdit { border: 1px solid #2E7D32; border-radius: 6px; padding: 6px; background-color: #2C2C2C; color: #E0E0E0; } QLineEdit:focus { border: 1px solid #66BB6A; /* vert clair */ background-color: #333333; } /* Boutons */ QPushButton { background-color: #2E7D32; /* vert sombre */ color: white; border-radius: 8px; padding: 6px 14px; font-weight: bold; } QPushButton:hover { background-color: #388E3C; } QPushButton:pressed { background-color: #1B5E20; } /* Table des produits */ QTableWidget { background-color: #2C2C2C; border: 1px solid #424242; gridline-color: #555555; selection-background-color: #2E7D32; /* vert s\303\251lection */ selection-color: white; co"
                        "lor: #E0E0E0; font-size: 13px; } QHeaderView::section { background-color: #2E7D32; color: white; font-weight: bold; padding: 6px; border: 1px solid #1B5E20; } /* GroupBox (cadres) */ QGroupBox { border: 2px solid #2E7D32; border-radius: 8px; margin-top: 10px; padding: 10px; font-weight: bold; color: #66BB6A; /* vert clair */ } QGroupBox::title { subcontrol-origin: margin; subcontrol-position: top left; padding: 0 8px; }"));
        MainWindow->setDocumentMode(true);
        MainWindow->setDockNestingEnabled(true);
        MainWindow->setUnifiedTitleAndToolBarOnMac(true);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName("stackedWidget");
        stackedWidget->setGeometry(QRect(30, 0, 1301, 1101));
        stackedWidget->setAutoFillBackground(false);
        stackedWidget->setStyleSheet(QString::fromUtf8("QMainWindow { background-color: #1E1E1E; /* fond sombre */ font-family: \"Segoe UI\"; font-size: 14px; color: #E0E0E0; /* texte clair */ } /* Labels */ QLabel { font-size: 14px; font-weight: bold; color: #A5D6A7; /* vert p\303\242le */ } /* Champs de saisie */ QLineEdit { border: 1px solid #2E7D32; border-radius: 6px; padding: 6px; background-color: #2C2C2C; color: #E0E0E0; } QLineEdit:focus { border: 1px solid #66BB6A; /* vert clair */ background-color: #333333; } /* Boutons */ QPushButton { background-color: #2E7D32; /* vert sombre */ color: white; border-radius: 8px; padding: 6px 14px; font-weight: bold; } QPushButton:hover { background-color: #388E3C; } QPushButton:pressed { background-color: #1B5E20; } /* Table des produits */ QTableWidget { background-color: #2C2C2C; border: 1px solid #424242; gridline-color: #555555; selection-background-color: #2E7D32; /* vert s\303\251lection */ selection-color: white; color: #E0E0E0; font-size: 13px; } QHeaderView::section { background-color: #2E7D32; color: white; f"
                        "ont-weight: bold; padding: 6px; border: 1px solid #1B5E20; } /* GroupBox (cadres) */ QGroupBox { border: 2px solid #2E7D32; border-radius: 8px; margin-top: 10px; padding: 10px; font-weight: bold; color: #66BB6A; /* vert clair */ } QGroupBox::title { subcontrol-origin: margin; subcontrol-position: top left; padding: 0 8px; }\n"
""));
        page = new QWidget();
        page->setObjectName("page");
        label_10 = new QLabel(page);
        label_10->setObjectName("label_10");
        label_10->setGeometry(QRect(410, 190, 91, 31));
        btnLogin = new QPushButton(page);
        btnLogin->setObjectName("btnLogin");
        btnLogin->setGeometry(QRect(520, 330, 91, 41));
        lineUser = new QLineEdit(page);
        lineUser->setObjectName("lineUser");
        lineUser->setGeometry(QRect(610, 190, 113, 31));
        linePass = new QLineEdit(page);
        linePass->setObjectName("linePass");
        linePass->setGeometry(QRect(610, 240, 113, 31));
        linePass->setEchoMode(QLineEdit::EchoMode::Password);
        label_11 = new QLabel(page);
        label_11->setObjectName("label_11");
        label_11->setGeometry(QRect(410, 240, 71, 31));
        label_41 = new QLabel(page);
        label_41->setObjectName("label_41");
        label_41->setGeometry(QRect(680, 50, 451, 281));
        label_41->setTabletTracking(true);
        label_41->setAcceptDrops(true);
        label_41->setAutoFillBackground(false);
        label_41->setPixmap(QPixmap(QString::fromUtf8("a.png")));
        label_41->setScaledContents(true);
        label_41->setWordWrap(true);
        label_41->setOpenExternalLinks(true);
        stackedWidget->addWidget(page);
        page_1 = new QWidget();
        page_1->setObjectName("page_1");
        dateEdit = new QDateEdit(page_1);
        dateEdit->setObjectName("dateEdit");
        dateEdit->setGeometry(QRect(280, 410, 110, 41));
        dateEdit->setStyleSheet(QString::fromUtf8("font-size: 14px; font-weight: bold; color: #A5D6A9;"));
        lineEdit_5 = new QLineEdit(page_1);
        lineEdit_5->setObjectName("lineEdit_5");
        lineEdit_5->setGeometry(QRect(280, 350, 113, 31));
        label_5 = new QLabel(page_1);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(40, 280, 101, 41));
        label_2 = new QLabel(page_1);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(40, 100, 101, 41));
        lineEdit_4 = new QLineEdit(page_1);
        lineEdit_4->setObjectName("lineEdit_4");
        lineEdit_4->setGeometry(QRect(280, 280, 113, 31));
        label = new QLabel(page_1);
        label->setObjectName("label");
        label->setGeometry(QRect(30, 30, 131, 61));
        label_7 = new QLabel(page_1);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(40, 410, 161, 41));
        btnGestionClients_PageStock = new QPushButton(page_1);
        btnGestionClients_PageStock->setObjectName("btnGestionClients_PageStock");
        btnGestionClients_PageStock->setGeometry(QRect(40, 0, 131, 31));
        lineEdit_3 = new QLineEdit(page_1);
        lineEdit_3->setObjectName("lineEdit_3");
        lineEdit_3->setGeometry(QRect(280, 160, 113, 31));
        pushButton_5 = new QPushButton(page_1);
        pushButton_5->setObjectName("pushButton_5");
        pushButton_5->setGeometry(QRect(710, 90, 101, 24));
        pushButton_4 = new QPushButton(page_1);
        pushButton_4->setObjectName("pushButton_4");
        pushButton_4->setGeometry(QRect(440, 90, 91, 24));
        dateEdit_2 = new QDateEdit(page_1);
        dateEdit_2->setObjectName("dateEdit_2");
        dateEdit_2->setGeometry(QRect(280, 470, 110, 41));
        dateEdit_2->setStyleSheet(QString::fromUtf8("font-size: 14px; font-weight: bold; color: #A5D6A7;"));
        btnGestionEmployes_PageStock = new QPushButton(page_1);
        btnGestionEmployes_PageStock->setObjectName("btnGestionEmployes_PageStock");
        btnGestionEmployes_PageStock->setGeometry(QRect(210, 0, 131, 31));
        label_4 = new QLabel(page_1);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(40, 220, 101, 41));
        label_6 = new QLabel(page_1);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(40, 340, 101, 41));
        lineEdit = new QLineEdit(page_1);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setGeometry(QRect(280, 50, 113, 31));
        labelImage = new QLabel(page_1);
        labelImage->setObjectName("labelImage");
        labelImage->setGeometry(QRect(610, 590, 171, 81));
        label_8 = new QLabel(page_1);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(40, 470, 161, 41));
        lineEdit_2 = new QLineEdit(page_1);
        lineEdit_2->setObjectName("lineEdit_2");
        lineEdit_2->setGeometry(QRect(280, 110, 113, 31));
        label_3 = new QLabel(page_1);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(40, 150, 101, 41));
        comboBox = new QComboBox(page_1);
        comboBox->setObjectName("comboBox");
        comboBox->setGeometry(QRect(280, 220, 121, 31));
        comboBox->setMinimumSize(QSize(0, 31));
        btnGestionSponsors_PageStock = new QPushButton(page_1);
        btnGestionSponsors_PageStock->setObjectName("btnGestionSponsors_PageStock");
        btnGestionSponsors_PageStock->setGeometry(QRect(400, 0, 131, 31));
        btnGestionFournisseurs_PageStock = new QPushButton(page_1);
        btnGestionFournisseurs_PageStock->setObjectName("btnGestionFournisseurs_PageStock");
        btnGestionFournisseurs_PageStock->setGeometry(QRect(580, 0, 151, 31));
        groupBox_3 = new QGroupBox(page_1);
        groupBox_3->setObjectName("groupBox_3");
        groupBox_3->setGeometry(QRect(590, 160, 491, 251));
        tableWidget = new QTableWidget(groupBox_3);
        if (tableWidget->columnCount() < 3)
            tableWidget->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setGeometry(QRect(100, 20, 301, 211));
        tableWidget->setColumnCount(3);
        label_48 = new QLabel(page_1);
        label_48->setObjectName("label_48");
        label_48->setGeometry(QRect(810, -20, 221, 151));
        label_48->setPixmap(QPixmap(QString::fromUtf8(":/a.png")));
        groupBox_5 = new QGroupBox(page_1);
        groupBox_5->setObjectName("groupBox_5");
        groupBox_5->setGeometry(QRect(470, 460, 671, 61));
        pushButton_20 = new QPushButton(groupBox_5);
        pushButton_20->setObjectName("pushButton_20");
        pushButton_20->setGeometry(QRect(480, 20, 181, 31));
        pushButton_17 = new QPushButton(groupBox_5);
        pushButton_17->setObjectName("pushButton_17");
        pushButton_17->setGeometry(QRect(40, 20, 181, 31));
        pushButton_21 = new QPushButton(groupBox_5);
        pushButton_21->setObjectName("pushButton_21");
        pushButton_21->setGeometry(QRect(260, 20, 181, 31));
        radioButton_10 = new QRadioButton(page_1);
        radioButton_10->setObjectName("radioButton_10");
        radioButton_10->setGeometry(QRect(540, 60, 101, 24));
        radioButton_10->setStyleSheet(QString::fromUtf8("font-size: 14px; font-weight: bold; color: #A5D6A7;\n"
""));
        radioButton_11 = new QRadioButton(page_1);
        radioButton_11->setObjectName("radioButton_11");
        radioButton_11->setGeometry(QRect(540, 90, 101, 24));
        radioButton_11->setStyleSheet(QString::fromUtf8("font-size: 14px; font-weight: bold; color: #A5D6A7;\n"
""));
        radioButton_12 = new QRadioButton(page_1);
        radioButton_12->setObjectName("radioButton_12");
        radioButton_12->setGeometry(QRect(540, 120, 101, 24));
        radioButton_12->setStyleSheet(QString::fromUtf8("font-size: 14px; font-weight: bold; color: #A5D6A7;\n"
""));
        lineEdit_28 = new QLineEdit(page_1);
        lineEdit_28->setObjectName("lineEdit_28");
        lineEdit_28->setGeometry(QRect(840, 90, 113, 31));
        label_49 = new QLabel(page_1);
        label_49->setObjectName("label_49");
        label_49->setGeometry(QRect(490, 560, 161, 41));
        groupBox_7 = new QGroupBox(page_1);
        groupBox_7->setObjectName("groupBox_7");
        groupBox_7->setGeometry(QRect(10, 620, 411, 61));
        pushButton_3 = new QPushButton(groupBox_7);
        pushButton_3->setObjectName("pushButton_3");
        pushButton_3->setGeometry(QRect(240, 20, 131, 31));
        pushButton_22 = new QPushButton(groupBox_7);
        pushButton_22->setObjectName("pushButton_22");
        pushButton_22->setGeometry(QRect(30, 20, 131, 31));
        btnBack_PageStock = new QPushButton(page_1);
        btnBack_PageStock->setObjectName("btnBack_PageStock");
        btnBack_PageStock->setGeometry(QRect(1100, 670, 91, 41));
        stackedWidget->addWidget(page_1);
        page_2 = new QWidget();
        page_2->setObjectName("page_2");
        btnBack_PageClients = new QPushButton(page_2);
        btnBack_PageClients->setObjectName("btnBack_PageClients");
        btnBack_PageClients->setGeometry(QRect(1030, 690, 101, 31));
        label_47 = new QLabel(page_2);
        label_47->setObjectName("label_47");
        label_47->setGeometry(QRect(900, 40, 221, 151));
        label_47->setPixmap(QPixmap(QString::fromUtf8(":/a.png")));
        label_59 = new QLabel(page_2);
        label_59->setObjectName("label_59");
        label_59->setGeometry(QRect(480, 370, 251, 71));
        label_59->setPixmap(QPixmap(QString::fromUtf8("../../../../../Downloads/icone-statistique-fond-clair-symbole-donnees-entreprise-graphique-analysant-analytique-contour-plat_.png")));
        label_59->setScaledContents(true);
        label_58 = new QLabel(page_2);
        label_58->setObjectName("label_58");
        label_58->setGeometry(QRect(500, 570, 171, 20));
        stackedWidget->addWidget(page_2);
        page_3 = new QWidget();
        page_3->setObjectName("page_3");
        btnGestionStock_Page_Employes = new QPushButton(page_3);
        btnGestionStock_Page_Employes->setObjectName("btnGestionStock_Page_Employes");
        btnGestionStock_Page_Employes->setGeometry(QRect(30, 10, 131, 31));
        btnGestionClients_Page_Employes = new QPushButton(page_3);
        btnGestionClients_Page_Employes->setObjectName("btnGestionClients_Page_Employes");
        btnGestionClients_Page_Employes->setGeometry(QRect(250, 10, 131, 31));
        lineEdit_16 = new QLineEdit(page_3);
        lineEdit_16->setObjectName("lineEdit_16");
        lineEdit_16->setGeometry(QRect(360, 110, 113, 31));
        btnGestionSponsors_Page_Employes = new QPushButton(page_3);
        btnGestionSponsors_Page_Employes->setObjectName("btnGestionSponsors_Page_Employes");
        btnGestionSponsors_Page_Employes->setGeometry(QRect(440, 10, 131, 31));
        btnGestionFournisseurs_Page_Employes = new QPushButton(page_3);
        btnGestionFournisseurs_Page_Employes->setObjectName("btnGestionFournisseurs_Page_Employes");
        btnGestionFournisseurs_Page_Employes->setGeometry(QRect(630, 10, 151, 31));
        label_17 = new QLabel(page_3);
        label_17->setObjectName("label_17");
        label_17->setGeometry(QRect(70, 120, 121, 16));
        label_18 = new QLabel(page_3);
        label_18->setObjectName("label_18");
        label_18->setGeometry(QRect(70, 170, 131, 20));
        dateEdit_3 = new QDateEdit(page_3);
        dateEdit_3->setObjectName("dateEdit_3");
        dateEdit_3->setGeometry(QRect(360, 170, 110, 26));
        dateEdit_3->setStyleSheet(QString::fromUtf8("font-size: 14px; font-weight: bold; color: #A5D6A7;"));
        label_19 = new QLabel(page_3);
        label_19->setObjectName("label_19");
        label_19->setGeometry(QRect(70, 250, 91, 20));
        radioButton = new QRadioButton(page_3);
        radioButton->setObjectName("radioButton");
        radioButton->setGeometry(QRect(160, 250, 101, 24));
        radioButton->setStyleSheet(QString::fromUtf8("font-size: 14px; font-weight: bold; color: #A5D6A7;\n"
""));
        radioButton_2 = new QRadioButton(page_3);
        radioButton_2->setObjectName("radioButton_2");
        radioButton_2->setGeometry(QRect(340, 250, 131, 24));
        radioButton_2->setStyleSheet(QString::fromUtf8("font-size: 14px; font-weight: bold; color: #A5D6A7;\n"
"\n"
""));
        radioButton_3 = new QRadioButton(page_3);
        radioButton_3->setObjectName("radioButton_3");
        radioButton_3->setGeometry(QRect(240, 290, 131, 24));
        radioButton_3->setStyleSheet(QString::fromUtf8("font-size: 14px; font-weight: bold; color: #A5D6A7;\n"
""));
        label_20 = new QLabel(page_3);
        label_20->setObjectName("label_20");
        label_20->setGeometry(QRect(80, 420, 131, 20));
        spinBox = new QSpinBox(page_3);
        spinBox->setObjectName("spinBox");
        spinBox->setGeometry(QRect(310, 420, 42, 26));
        spinBox->setStyleSheet(QString::fromUtf8("font-size: 14px; font-weight: bold; color: #A5D6A7;"));
        label_21 = new QLabel(page_3);
        label_21->setObjectName("label_21");
        label_21->setGeometry(QRect(80, 470, 151, 20));
        spinBox_2 = new QSpinBox(page_3);
        spinBox_2->setObjectName("spinBox_2");
        spinBox_2->setGeometry(QRect(310, 470, 42, 26));
        spinBox_2->setStyleSheet(QString::fromUtf8("font-size: 14px; font-weight: bold; color: #A5D6A7;"));
        label_22 = new QLabel(page_3);
        label_22->setObjectName("label_22");
        label_22->setGeometry(QRect(80, 560, 91, 20));
        checkBox = new QCheckBox(page_3);
        checkBox->setObjectName("checkBox");
        checkBox->setGeometry(QRect(200, 550, 91, 24));
        checkBox->setStyleSheet(QString::fromUtf8("font-size: 14px; font-weight: bold; color: #A5D6A7;"));
        checkBox_3 = new QCheckBox(page_3);
        checkBox_3->setObjectName("checkBox_3");
        checkBox_3->setGeometry(QRect(200, 590, 111, 24));
        checkBox_3->setStyleSheet(QString::fromUtf8("font-size: 14px; font-weight: bold; color: #A5D6A7;"));
        checkBox_2 = new QCheckBox(page_3);
        checkBox_2->setObjectName("checkBox_2");
        checkBox_2->setGeometry(QRect(200, 620, 161, 24));
        checkBox_2->setStyleSheet(QString::fromUtf8("font-size: 14px; font-weight: bold; color: #A5D6A7;"));
        label_25 = new QLabel(page_3);
        label_25->setObjectName("label_25");
        label_25->setGeometry(QRect(70, 210, 141, 20));
        dateEdit_4 = new QDateEdit(page_3);
        dateEdit_4->setObjectName("dateEdit_4");
        dateEdit_4->setGeometry(QRect(360, 210, 110, 26));
        dateEdit_4->setStyleSheet(QString::fromUtf8("font-size: 14px; font-weight: bold; color: #A5D6A7;"));
        label_26 = new QLabel(page_3);
        label_26->setObjectName("label_26");
        label_26->setGeometry(QRect(70, 350, 63, 20));
        label_27 = new QLabel(page_3);
        label_27->setObjectName("label_27");
        label_27->setGeometry(QRect(310, 350, 63, 20));
        lineEdit_17 = new QLineEdit(page_3);
        lineEdit_17->setObjectName("lineEdit_17");
        lineEdit_17->setGeometry(QRect(140, 350, 113, 21));
        lineEdit_18 = new QLineEdit(page_3);
        lineEdit_18->setObjectName("lineEdit_18");
        lineEdit_18->setGeometry(QRect(380, 350, 113, 20));
        btnBack_Page_Employes = new QPushButton(page_3);
        btnBack_Page_Employes->setObjectName("btnBack_Page_Employes");
        btnBack_Page_Employes->setGeometry(QRect(840, 640, 111, 41));
        label_46 = new QLabel(page_3);
        label_46->setObjectName("label_46");
        label_46->setGeometry(QRect(880, 50, 221, 151));
        label_46->setPixmap(QPixmap(QString::fromUtf8(":/a.png")));
        groupBox_10 = new QGroupBox(page_3);
        groupBox_10->setObjectName("groupBox_10");
        groupBox_10->setGeometry(QRect(550, 80, 491, 251));
        tableWidget_4 = new QTableWidget(groupBox_10);
        if (tableWidget_4->columnCount() < 3)
            tableWidget_4->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget_4->setHorizontalHeaderItem(0, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget_4->setHorizontalHeaderItem(1, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget_4->setHorizontalHeaderItem(2, __qtablewidgetitem5);
        tableWidget_4->setObjectName("tableWidget_4");
        tableWidget_4->setGeometry(QRect(50, 40, 301, 171));
        tableWidget_4->setColumnCount(3);
        groupBox_11 = new QGroupBox(page_3);
        groupBox_11->setObjectName("groupBox_11");
        groupBox_11->setGeometry(QRect(40, 80, 471, 591));
        stackedWidget->addWidget(page_3);
        page_4 = new QWidget();
        page_4->setObjectName("page_4");
        label_45 = new QLabel(page_4);
        label_45->setObjectName("label_45");
        label_45->setGeometry(QRect(860, 50, 221, 151));
        label_45->setPixmap(QPixmap(QString::fromUtf8(":/a.png")));
        label_31 = new QLabel(page_4);
        label_31->setObjectName("label_31");
        label_31->setGeometry(QRect(570, 380, 241, 381));
        label_31->setPixmap(QPixmap(QString::fromUtf8("../../../../MOHAME~1/AppData/Local/Temp/Rar$DRa49232.39344.rartemp/youssef/images/s.png")));
        label_31->setScaledContents(true);
        label_54 = new QLabel(page_4);
        label_54->setObjectName("label_54");
        label_54->setGeometry(QRect(510, 380, 381, 441));
        label_54->setPixmap(QPixmap(QString::fromUtf8("../../../../MOHAME~1/AppData/Downloads/s.png")));
        label_54->setScaledContents(true);
        stackedWidget->addWidget(page_4);
        page_5 = new QWidget();
        page_5->setObjectName("page_5");
        page_5->setStyleSheet(QString::fromUtf8("QMainWindow {\n"
"    background-image: url(:/images/background.jpg); /* chemin de ton image */\n"
"    background-repeat: no-repeat;\n"
"    background-position: center;\n"
"    background-attachment: fixed;\n"
"}\n"
" /* Labels */ QLabel { font-size: 14px; font-weight: bold; color: #A5D6A7; /* vert p\303\242le */ } /* Champs de saisie */ QLineEdit { border: 1px solid #2E7D32; border-radius: 6px; padding: 6px; background-color: #2C2C2C; color: #E0E0E0; } QLineEdit:focus { border: 1px solid #66BB6A; /* vert clair */ background-color: #333333; } /* Boutons */ QPushButton { background-color: #2E7D32; /* vert sombre */ color: white; border-radius: 8px; padding: 6px 14px; font-weight: bold; } QPushButton:hover { background-color: #388E3C; } QPushButton:pressed { background-color: #1B5E20; } /* Table des produits */ QTableWidget { background-color: #2C2C2C; border: 1px solid #424242; gridline-color: #555555; selection-background-color: #2E7D32; /* vert s\303\251lection */ selection-color: white; color: #E0E0E0; fon"
                        "t-size: 13px; } QHeaderView::section { background-color: #2E7D32; color: white; font-weight: bold; padding: 6px; border: 1px solid #1B5E20; } /* GroupBox (cadres) */ QGroupBox { border: 2px solid #2E7D32; border-radius: 8px; margin-top: 10px; padding: 10px; font-weight: bold; color: #66BB6A; /* vert clair */ } QGroupBox::title { subcontrol-origin: margin; subcontrol-position: top left; padding: 0 8px; }"));
        stackedWidget->addWidget(page_5);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1477, 21));
        MainWindow->setMenuBar(menubar);

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(3);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label_10->setText(QCoreApplication::translate("MainWindow", "Name : ", nullptr));
        btnLogin->setText(QCoreApplication::translate("MainWindow", "Login", nullptr));
        lineUser->setText(QString());
        linePass->setText(QString());
        label_11->setText(QCoreApplication::translate("MainWindow", "Password : ", nullptr));
        label_41->setText(QString());
        label_5->setText(QCoreApplication::translate("MainWindow", "Prix : ", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Quantite :", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", " Nom Du Produit : ", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "Date de fabriquation :  ", nullptr));
        btnGestionClients_PageStock->setText(QCoreApplication::translate("MainWindow", "Gestion Clients", nullptr));
        pushButton_5->setText(QCoreApplication::translate("MainWindow", "Recherche : ", nullptr));
        pushButton_4->setText(QCoreApplication::translate("MainWindow", " TRI : ", nullptr));
        btnGestionEmployes_PageStock->setText(QCoreApplication::translate("MainWindow", "Gestion Employes", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "Categorie : ", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "fOURNISSEUR :", nullptr));
        labelImage->setText(QCoreApplication::translate("MainWindow", "labelImage", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "Date d expiration : ", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Reference  : ", nullptr));
        btnGestionSponsors_PageStock->setText(QCoreApplication::translate("MainWindow", "Gestion Sponsors", nullptr));
        btnGestionFournisseurs_PageStock->setText(QCoreApplication::translate("MainWindow", "Gestion Fournisseurs", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("MainWindow", "Affichage : ", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MainWindow", "Nom Produit", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MainWindow", "Quantite", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("MainWindow", "Prix", nullptr));
        label_48->setText(QString());
        groupBox_5->setTitle(QString());
        pushButton_20->setText(QCoreApplication::translate("MainWindow", "Supprimer", nullptr));
        pushButton_17->setText(QCoreApplication::translate("MainWindow", "Modfier ", nullptr));
        pushButton_21->setText(QCoreApplication::translate("MainWindow", "Valider", nullptr));
        radioButton_10->setText(QCoreApplication::translate("MainWindow", "A-Z", nullptr));
        radioButton_11->setText(QCoreApplication::translate("MainWindow", "Quantite ", nullptr));
        radioButton_12->setText(QCoreApplication::translate("MainWindow", "Prix", nullptr));
        label_49->setText(QCoreApplication::translate("MainWindow", "Statistiques : ", nullptr));
        groupBox_7->setTitle(QString());
        pushButton_3->setText(QCoreApplication::translate("MainWindow", "EXPORT PDF", nullptr));
        pushButton_22->setText(QCoreApplication::translate("MainWindow", "Upload Image ", nullptr));
        btnBack_PageStock->setText(QCoreApplication::translate("MainWindow", "LogOut", nullptr));
        btnBack_PageClients->setText(QCoreApplication::translate("MainWindow", "LogOut", nullptr));
        label_47->setText(QString());
        label_59->setText(QString());
        label_58->setText(QCoreApplication::translate("MainWindow", "Statistiques clients:", nullptr));
        btnGestionStock_Page_Employes->setText(QCoreApplication::translate("MainWindow", "Gestion Stock", nullptr));
        btnGestionClients_Page_Employes->setText(QCoreApplication::translate("MainWindow", "Gestion Clients", nullptr));
        btnGestionSponsors_Page_Employes->setText(QCoreApplication::translate("MainWindow", "Gestion Sponsors", nullptr));
        btnGestionFournisseurs_Page_Employes->setText(QCoreApplication::translate("MainWindow", "Gestion Fournisseurs", nullptr));
        label_17->setText(QCoreApplication::translate("MainWindow", "Nom Employe  :", nullptr));
        label_18->setText(QCoreApplication::translate("MainWindow", "Date de naissances", nullptr));
        label_19->setText(QCoreApplication::translate("MainWindow", "Etat civil", nullptr));
        radioButton->setText(QCoreApplication::translate("MainWindow", "C\303\251libataire", nullptr));
        radioButton_2->setText(QCoreApplication::translate("MainWindow", "Mari\303\251(e)", nullptr));
        radioButton_3->setText(QCoreApplication::translate("MainWindow", "Divorc\303\251(e)", nullptr));
        label_20->setText(QCoreApplication::translate("MainWindow", "Nombre d'enfants :", nullptr));
        label_21->setText(QCoreApplication::translate("MainWindow", "Ann\303\251e d'experiences : ", nullptr));
        label_22->setText(QCoreApplication::translate("MainWindow", "Diplome : ", nullptr));
        checkBox->setText(QCoreApplication::translate("MainWindow", "opticien", nullptr));
        checkBox_3->setText(QCoreApplication::translate("MainWindow", "vendeure", nullptr));
        checkBox_2->setText(QCoreApplication::translate("MainWindow", "employe de stock", nullptr));
        label_25->setText(QCoreApplication::translate("MainWindow", "Date d'embauche", nullptr));
        label_26->setText(QCoreApplication::translate("MainWindow", "Poste :", nullptr));
        label_27->setText(QCoreApplication::translate("MainWindow", "Salaire : ", nullptr));
        btnBack_Page_Employes->setText(QCoreApplication::translate("MainWindow", "LogOut", nullptr));
        label_46->setText(QString());
        groupBox_10->setTitle(QCoreApplication::translate("MainWindow", "Affichage : ", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget_4->horizontalHeaderItem(0);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("MainWindow", "Nom Employe", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget_4->horizontalHeaderItem(1);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("MainWindow", "Poste ", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget_4->horizontalHeaderItem(2);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("MainWindow", "Salaire", nullptr));
        groupBox_11->setTitle(QString());
        label_45->setText(QString());
        label_31->setText(QString());
        label_54->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
