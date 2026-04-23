/********************************************************************************
** Form generated from reading UI file 'dialog.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_H
#define UI_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_3;
    QTableWidget *info;
    QVBoxLayout *verticalLayout;
    QPushButton *Add;
    QPushButton *DeleteSelected;
    QSpacerItem *verticalSpacer;
    QRadioButton *isAirport;
    QRadioButton *radioButton;
    QLineEdit *lineEdit;
    QComboBox *from;
    QLineEdit *lineEdit_2;
    QComboBox *to;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *Save;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *SaveToFile;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName("Dialog");
        Dialog->resize(550, 404);
        verticalLayout_2 = new QVBoxLayout(Dialog);
        verticalLayout_2->setObjectName("verticalLayout_2");
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        info = new QTableWidget(Dialog);
        info->setObjectName("info");

        horizontalLayout_3->addWidget(info);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        Add = new QPushButton(Dialog);
        Add->setObjectName("Add");

        verticalLayout->addWidget(Add);

        DeleteSelected = new QPushButton(Dialog);
        DeleteSelected->setObjectName("DeleteSelected");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(DeleteSelected->sizePolicy().hasHeightForWidth());
        DeleteSelected->setSizePolicy(sizePolicy);
        DeleteSelected->setMinimumSize(QSize(100, 0));

        verticalLayout->addWidget(DeleteSelected);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        isAirport = new QRadioButton(Dialog);
        isAirport->setObjectName("isAirport");
        isAirport->setChecked(true);

        verticalLayout->addWidget(isAirport);

        radioButton = new QRadioButton(Dialog);
        radioButton->setObjectName("radioButton");

        verticalLayout->addWidget(radioButton);

        lineEdit = new QLineEdit(Dialog);
        lineEdit->setObjectName("lineEdit");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(lineEdit->sizePolicy().hasHeightForWidth());
        lineEdit->setSizePolicy(sizePolicy1);
        lineEdit->setMinimumSize(QSize(102, 0));
        lineEdit->setReadOnly(true);

        verticalLayout->addWidget(lineEdit);

        from = new QComboBox(Dialog);
        from->setObjectName("from");

        verticalLayout->addWidget(from);

        lineEdit_2 = new QLineEdit(Dialog);
        lineEdit_2->setObjectName("lineEdit_2");
        sizePolicy1.setHeightForWidth(lineEdit_2->sizePolicy().hasHeightForWidth());
        lineEdit_2->setSizePolicy(sizePolicy1);
        lineEdit_2->setReadOnly(true);

        verticalLayout->addWidget(lineEdit_2);

        to = new QComboBox(Dialog);
        to->setObjectName("to");

        verticalLayout->addWidget(to);


        horizontalLayout_3->addLayout(verticalLayout);


        verticalLayout_2->addLayout(horizontalLayout_3);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        Save = new QPushButton(Dialog);
        Save->setObjectName("Save");

        horizontalLayout->addWidget(Save);


        verticalLayout_2->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        SaveToFile = new QPushButton(Dialog);
        SaveToFile->setObjectName("SaveToFile");

        horizontalLayout_2->addWidget(SaveToFile);


        verticalLayout_2->addLayout(horizontalLayout_2);


        retranslateUi(Dialog);

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QCoreApplication::translate("Dialog", "Dialog", nullptr));
        Add->setText(QCoreApplication::translate("Dialog", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214", nullptr));
        DeleteSelected->setText(QCoreApplication::translate("Dialog", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214 \320\262\321\213\320\261\321\200\320\260\320\275\320\275\320\276\320\265", nullptr));
        isAirport->setText(QCoreApplication::translate("Dialog", "\320\220\321\215\321\200\320\276\320\277\320\276\321\200\321\202\321\213", nullptr));
        radioButton->setText(QCoreApplication::translate("Dialog", "\320\237\320\276\320\273\321\221\321\202\321\213", nullptr));
        lineEdit->setText(QCoreApplication::translate("Dialog", "\320\236\321\202\320\272\321\203\320\264\320\260", nullptr));
        lineEdit_2->setText(QCoreApplication::translate("Dialog", "\320\232\321\203\320\264\320\260", nullptr));
        Save->setText(QCoreApplication::translate("Dialog", "\320\222\321\213\320\271\321\202\320\270 \320\270 \320\276\320\261\320\275\320\276\320\262\320\270\321\202\321\214", nullptr));
        SaveToFile->setText(QCoreApplication::translate("Dialog", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214 \320\262 \321\204\320\260\320\271\320\273", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_H
