/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout_6;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *text;
    QLineEdit *from;
    QLineEdit *to;
    QHBoxLayout *chooseCities;
    QComboBox *fromCity;
    QComboBox *toCity;
    QGroupBox *Criterias;
    QHBoxLayout *horizontalLayout_2;
    QRadioButton *Price;
    QRadioButton *Time;
    QRadioButton *Combo;
    QRadioButton *OnlyDirect;
    QPushButton *FindPathes;
    QTableWidget *tableWidget;
    QPushButton *AddInfo;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *ChooseFile;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *Edit;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(939, 644);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setMinimumSize(QSize(150, 0));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        horizontalLayout_6 = new QHBoxLayout(centralwidget);
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(7);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setSizeConstraint(QLayout::SizeConstraint::SetNoConstraint);
        text = new QHBoxLayout();
        text->setObjectName("text");
        from = new QLineEdit(centralwidget);
        from->setObjectName("from");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(from->sizePolicy().hasHeightForWidth());
        from->setSizePolicy(sizePolicy1);
        from->setReadOnly(true);

        text->addWidget(from);

        to = new QLineEdit(centralwidget);
        to->setObjectName("to");
        sizePolicy1.setHeightForWidth(to->sizePolicy().hasHeightForWidth());
        to->setSizePolicy(sizePolicy1);
        to->setReadOnly(true);

        text->addWidget(to);


        verticalLayout->addLayout(text);

        chooseCities = new QHBoxLayout();
        chooseCities->setObjectName("chooseCities");
        fromCity = new QComboBox(centralwidget);
        fromCity->setObjectName("fromCity");
        sizePolicy1.setHeightForWidth(fromCity->sizePolicy().hasHeightForWidth());
        fromCity->setSizePolicy(sizePolicy1);
        fromCity->setMinimumSize(QSize(200, 0));
        fromCity->setEditable(false);
        fromCity->setInsertPolicy(QComboBox::InsertPolicy::NoInsert);

        chooseCities->addWidget(fromCity);

        toCity = new QComboBox(centralwidget);
        toCity->setObjectName("toCity");
        sizePolicy1.setHeightForWidth(toCity->sizePolicy().hasHeightForWidth());
        toCity->setSizePolicy(sizePolicy1);
        toCity->setMinimumSize(QSize(200, 0));
        toCity->setEditable(false);
        toCity->setInsertPolicy(QComboBox::InsertPolicy::NoInsert);

        chooseCities->addWidget(toCity);


        verticalLayout->addLayout(chooseCities);

        Criterias = new QGroupBox(centralwidget);
        Criterias->setObjectName("Criterias");
        horizontalLayout_2 = new QHBoxLayout(Criterias);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        Price = new QRadioButton(Criterias);
        Price->setObjectName("Price");
        Price->setChecked(true);

        horizontalLayout_2->addWidget(Price);

        Time = new QRadioButton(Criterias);
        Time->setObjectName("Time");

        horizontalLayout_2->addWidget(Time);

        Combo = new QRadioButton(Criterias);
        Combo->setObjectName("Combo");

        horizontalLayout_2->addWidget(Combo);


        verticalLayout->addWidget(Criterias);

        OnlyDirect = new QRadioButton(centralwidget);
        OnlyDirect->setObjectName("OnlyDirect");
        OnlyDirect->setChecked(false);

        verticalLayout->addWidget(OnlyDirect);

        FindPathes = new QPushButton(centralwidget);
        FindPathes->setObjectName("FindPathes");
        FindPathes->setEnabled(true);
        sizePolicy1.setHeightForWidth(FindPathes->sizePolicy().hasHeightForWidth());
        FindPathes->setSizePolicy(sizePolicy1);
        FindPathes->setMinimumSize(QSize(100, 10));

        verticalLayout->addWidget(FindPathes);

        tableWidget = new QTableWidget(centralwidget);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setMinimumSize(QSize(256, 0));

        verticalLayout->addWidget(tableWidget);

        AddInfo = new QPushButton(centralwidget);
        AddInfo->setObjectName("AddInfo");
        sizePolicy1.setHeightForWidth(AddInfo->sizePolicy().hasHeightForWidth());
        AddInfo->setSizePolicy(sizePolicy1);

        verticalLayout->addWidget(AddInfo);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        ChooseFile = new QPushButton(centralwidget);
        ChooseFile->setObjectName("ChooseFile");
        sizePolicy1.setHeightForWidth(ChooseFile->sizePolicy().hasHeightForWidth());
        ChooseFile->setSizePolicy(sizePolicy1);

        horizontalLayout->addWidget(ChooseFile);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_2);

        Edit = new QPushButton(centralwidget);
        Edit->setObjectName("Edit");
        sizePolicy1.setHeightForWidth(Edit->sizePolicy().hasHeightForWidth());
        Edit->setSizePolicy(sizePolicy1);

        horizontalLayout_5->addWidget(Edit);


        verticalLayout->addLayout(horizontalLayout_5);


        horizontalLayout_6->addLayout(verticalLayout);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 939, 23));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        from->setText(QCoreApplication::translate("MainWindow", "\320\236\321\202\320\272\321\203\320\264\320\260", nullptr));
        to->setText(QCoreApplication::translate("MainWindow", "\320\232\321\203\320\264\320\260", nullptr));
        Criterias->setTitle(QCoreApplication::translate("MainWindow", "\320\232\321\200\320\270\321\202\320\265\321\200\320\270\320\270", nullptr));
        Price->setText(QCoreApplication::translate("MainWindow", "\320\246\320\265\320\275\320\260", nullptr));
        Time->setText(QCoreApplication::translate("MainWindow", "\320\222\321\200\320\265\320\274\321\217", nullptr));
        Combo->setText(QCoreApplication::translate("MainWindow", "\320\232\320\276\320\274\320\261\320\276(\320\246\320\265\320\275\320\260 + \320\222\321\200\320\265\320\274\321\217)", nullptr));
        OnlyDirect->setText(QCoreApplication::translate("MainWindow", "\320\242\320\276\320\273\321\214\320\272\320\276 \320\277\321\200\321\217\320\274\321\213\320\265 \320\277\320\265\321\200\320\265\320\273\321\221\321\202\321\213", nullptr));
        FindPathes->setText(QCoreApplication::translate("MainWindow", "\320\235\320\260\320\271\321\202\320\270", nullptr));
        AddInfo->setText(QCoreApplication::translate("MainWindow", "\320\225\321\211\321\221", nullptr));
        ChooseFile->setText(QCoreApplication::translate("MainWindow", "\320\222\321\213\320\261\321\200\320\260\321\202\321\214 \321\204\320\260\320\271\320\273", nullptr));
        Edit->setText(QCoreApplication::translate("MainWindow", "\320\240\320\265\320\264\320\260\320\272\321\202\320\270\321\200\320\276\320\262\320\260\321\202\321\214 ", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
