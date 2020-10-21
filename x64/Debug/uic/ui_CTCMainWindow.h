/********************************************************************************
** Form generated from reading UI file 'CTCMainWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CTCMAINWINDOW_H
#define UI_CTCMAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "ConsoleListWidget.h"
#include "DockTabWidget.h"
#include "QtNavTreeView.h"
#include "TitleBarWidget.h"

QT_BEGIN_NAMESPACE

class Ui_CTCMainWindowClass
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout_2;
    QFrame *line;
    TitleBarWidget *widget_Title;
    QWidget *widget_Main;
    QtNavTreeView *navTreeView;
    DockTabWidget *tabWidget;
    QWidget *tab;
    QDockWidget *dockWidget_Console;
    QWidget *dockWidgetContents;
    QGridLayout *gridLayout;
    QWidget *widget_Console_Main;
    QVBoxLayout *verticalLayout_2;
    QWidget *widget_Console_Top;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_Console;
    QSpacerItem *horizontalSpacer_Console;
    QCheckBox *checkBox_Console_AutoRoll;
    QPushButton *button_Console_Filter;
    QPushButton *button_Console_Serach;
    QPushButton *button_Console_Clear;
    QWidget *widget_Console_Bottom;
    QGridLayout *gridLayout_3;
    ConsoleListWidget *listWidget;
    QMenuBar *menuBar_Main;

    void setupUi(QMainWindow *CTCMainWindowClass)
    {
        if (CTCMainWindowClass->objectName().isEmpty())
            CTCMainWindowClass->setObjectName(QString::fromUtf8("CTCMainWindowClass"));
        CTCMainWindowClass->resize(970, 848);
        CTCMainWindowClass->setStyleSheet(QString::fromUtf8(""));
        centralWidget = new QWidget(CTCMainWindowClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayout_2 = new QGridLayout(centralWidget);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        line = new QFrame(centralWidget);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        gridLayout_2->addWidget(line, 1, 0, 1, 1);

        widget_Title = new TitleBarWidget(centralWidget);
        widget_Title->setObjectName(QString::fromUtf8("widget_Title"));

        gridLayout_2->addWidget(widget_Title, 0, 0, 1, 1);

        widget_Main = new QWidget(centralWidget);
        widget_Main->setObjectName(QString::fromUtf8("widget_Main"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(widget_Main->sizePolicy().hasHeightForWidth());
        widget_Main->setSizePolicy(sizePolicy);
        navTreeView = new QtNavTreeView(widget_Main);
        navTreeView->setObjectName(QString::fromUtf8("navTreeView"));
        navTreeView->setGeometry(QRect(0, 0, 321, 731));
        tabWidget = new DockTabWidget(widget_Main);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(326, -1, 621, 711));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        tabWidget->addTab(tab, QString());

        gridLayout_2->addWidget(widget_Main, 2, 0, 1, 1);

        CTCMainWindowClass->setCentralWidget(centralWidget);
        dockWidget_Console = new QDockWidget(CTCMainWindowClass);
        dockWidget_Console->setObjectName(QString::fromUtf8("dockWidget_Console"));
        dockWidget_Console->setFeatures(QDockWidget::DockWidgetFloatable|QDockWidget::DockWidgetMovable);
        dockWidget_Console->setAllowedAreas(Qt::BottomDockWidgetArea|Qt::LeftDockWidgetArea|Qt::RightDockWidgetArea);
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QString::fromUtf8("dockWidgetContents"));
        gridLayout = new QGridLayout(dockWidgetContents);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        widget_Console_Main = new QWidget(dockWidgetContents);
        widget_Console_Main->setObjectName(QString::fromUtf8("widget_Console_Main"));
        QFont font;
        font.setFamily(QString::fromUtf8("Arial"));
        font.setPointSize(9);
        font.setBold(false);
        font.setWeight(50);
        widget_Console_Main->setFont(font);
        verticalLayout_2 = new QVBoxLayout(widget_Console_Main);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, -1);
        widget_Console_Top = new QWidget(widget_Console_Main);
        widget_Console_Top->setObjectName(QString::fromUtf8("widget_Console_Top"));
        widget_Console_Top->setMaximumSize(QSize(16777215, 35));
        horizontalLayout_4 = new QHBoxLayout(widget_Console_Top);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(10, 1, 10, 1);
        label_Console = new QLabel(widget_Console_Top);
        label_Console->setObjectName(QString::fromUtf8("label_Console"));

        horizontalLayout_4->addWidget(label_Console);

        horizontalSpacer_Console = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_Console);

        checkBox_Console_AutoRoll = new QCheckBox(widget_Console_Top);
        checkBox_Console_AutoRoll->setObjectName(QString::fromUtf8("checkBox_Console_AutoRoll"));

        horizontalLayout_4->addWidget(checkBox_Console_AutoRoll);

        button_Console_Filter = new QPushButton(widget_Console_Top);
        button_Console_Filter->setObjectName(QString::fromUtf8("button_Console_Filter"));
        button_Console_Filter->setMinimumSize(QSize(70, 0));
        button_Console_Filter->setMaximumSize(QSize(80, 16777215));
        QFont font1;
        font1.setPointSize(9);
        button_Console_Filter->setFont(font1);
        button_Console_Filter->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout_4->addWidget(button_Console_Filter);

        button_Console_Serach = new QPushButton(widget_Console_Top);
        button_Console_Serach->setObjectName(QString::fromUtf8("button_Console_Serach"));
        button_Console_Serach->setMaximumSize(QSize(60, 16777215));

        horizontalLayout_4->addWidget(button_Console_Serach);

        button_Console_Clear = new QPushButton(widget_Console_Top);
        button_Console_Clear->setObjectName(QString::fromUtf8("button_Console_Clear"));
        button_Console_Clear->setMaximumSize(QSize(60, 16777215));

        horizontalLayout_4->addWidget(button_Console_Clear);


        verticalLayout_2->addWidget(widget_Console_Top);

        widget_Console_Bottom = new QWidget(widget_Console_Main);
        widget_Console_Bottom->setObjectName(QString::fromUtf8("widget_Console_Bottom"));
        QFont font2;
        font2.setFamily(QString::fromUtf8("Arial"));
        font2.setPointSize(11);
        font2.setBold(false);
        font2.setWeight(50);
        widget_Console_Bottom->setFont(font2);
        gridLayout_3 = new QGridLayout(widget_Console_Bottom);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        gridLayout_3->setContentsMargins(-1, 0, -1, 0);
        listWidget = new ConsoleListWidget(widget_Console_Bottom);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));

        gridLayout_3->addWidget(listWidget, 0, 0, 1, 1);


        verticalLayout_2->addWidget(widget_Console_Bottom);


        gridLayout->addWidget(widget_Console_Main, 0, 0, 1, 1);

        dockWidget_Console->setWidget(dockWidgetContents);
        CTCMainWindowClass->addDockWidget(Qt::BottomDockWidgetArea, dockWidget_Console);
        menuBar_Main = new QMenuBar(CTCMainWindowClass);
        menuBar_Main->setObjectName(QString::fromUtf8("menuBar_Main"));
        menuBar_Main->setGeometry(QRect(0, 0, 970, 23));
        CTCMainWindowClass->setMenuBar(menuBar_Main);

        retranslateUi(CTCMainWindowClass);

        QMetaObject::connectSlotsByName(CTCMainWindowClass);
    } // setupUi

    void retranslateUi(QMainWindow *CTCMainWindowClass)
    {
        CTCMainWindowClass->setWindowTitle(QCoreApplication::translate("CTCMainWindowClass", "Form", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("CTCMainWindowClass", "Tab 1", nullptr));
        dockWidget_Console->setWindowTitle(QCoreApplication::translate("CTCMainWindowClass", "\346\216\247\345\210\266\345\217\260", nullptr));
        label_Console->setText(QCoreApplication::translate("CTCMainWindowClass", "\346\266\210\346\201\257\346\225\260\351\207\217\357\274\232 100  \351\224\231\350\257\257\357\274\23250  \350\255\246\345\221\212\357\274\23250", nullptr));
        checkBox_Console_AutoRoll->setText(QCoreApplication::translate("CTCMainWindowClass", "\350\207\252\345\212\250\346\273\232\345\212\250", nullptr));
        button_Console_Filter->setText(QCoreApplication::translate("CTCMainWindowClass", "\350\277\207\346\273\244\345\231\250", nullptr));
        button_Console_Serach->setText(QCoreApplication::translate("CTCMainWindowClass", "     \346\220\234\347\264\242     ", nullptr));
        button_Console_Clear->setText(QCoreApplication::translate("CTCMainWindowClass", "     \346\270\205\351\231\244     ", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CTCMainWindowClass: public Ui_CTCMainWindowClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CTCMAINWINDOW_H
