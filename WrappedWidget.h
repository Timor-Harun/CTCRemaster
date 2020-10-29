#pragma once

#include <QtWidgets/QWidget>
#include <boost/python.hpp>
#include <QLayout>
#include <QVector>
#include <QStack>
#include <QPushButton>
#include <QLabel>
#include <QCheckBox>
#include <QProgressBar>
#include <QGroupBox>
#include <QLineEdit>
#include <QTabWidget>
#include <QObjectUserData>
#include <QComboBox>
#include <QJsonParseError>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>
#include <QPlainTextEdit>
#include <QButtonGroup>
#include <QRadioButton>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QFontComboBox>
#include <QCloseEvent>

#include "WrappedProgressBar.h"
#include "IPAddress.h"
#include "WrappedTableWidget.h"
#include "ConsoleLogic.h"

class WrappedWidget : public QWidget
{
    Q_OBJECT

public:
    WrappedWidget(QWidget *parent = Q_NULLPTR);

private:
    QString                uuid;
    QVBoxLayout*           mainLayout;
    QSet<QString>          objectNamesSets;
    QStack<QLayout*>       layoutsStack;
    QStack<QWidget*>       widgetsStack;

Q_SIGNALS:
    void signal_ButtonClickEvent(const QString &objectName);
    void signal_EditFinished(const QString &objectName);
    void signal_CheckBoxStageChanged(const QString &objectName);
    void signal_TableSelectedIndexChanged(const QString& objectName,int row);
    void signal_SpinBoxValueChanged(const QString& objectName, int value);
    void signal_ButtonGroupToggled(const QString& objectName, int index,bool value);

    void signal_close();
protected:
    void closeEvent(QCloseEvent* event)
    {
        emit signal_close();
    }
public:
    void setUUID(const QString& uuid);

    QString getUUID();

    void doHorizontalLayout();

    void doVerticalLayout();

    QPushButton* doButton(const QString& objectName, const QString& buttonText);

    QLineEdit* doLineEdit(const QString& objectName);

    void doSpacer(int spacing);

    QComboBox* doComboBox(const QString& objectName, const QStringList& items);

    QCheckBox* doCheckBox(const QString& objectName, const QString& objectText, bool checked);

    WrappedProgressBar* doProgressBar(const QString& objectName, int value, int min, int max);

    WrappedTableWidget* doTable(const QString& objectName, const QStringList& headerLabels);

    IPAddress* doIPAddress(const QString& objectName);

    QLabel* doLabel(const QString& text);

    void doGroupBox(const QString& title);

    void endGroupBox();

    void endLayout();
    
    QSpinBox* doSpinBox(const QString& objectName, int min,int max,int step)
    {
        QSpinBox* box = new QSpinBox;
        box->setObjectName(objectName);
        box->setRange(min, max);
        box->setSingleStep(step);
		layoutsStack.top()->addWidget(box);
		return box;
    }

	QDoubleSpinBox* doDoubleSpinBox(const QString& objectName, double min, double max, double step)
	{
        QDoubleSpinBox* box = new QDoubleSpinBox;
		box->setObjectName(objectName);
		box->setRange(min, max);
		box->setSingleStep(step);
		layoutsStack.top()->addWidget(box);
		return box;
	}

    QPlainTextEdit* doPlainTextEdit(const QString& objectName)
    {
        QPlainTextEdit* edit = new QPlainTextEdit;
        edit->setObjectName(objectName);
		connect(edit, &QPlainTextEdit::textChanged, this, [=]() {emit signal_EditFinished(objectName); });
		layoutsStack.top()->addWidget(edit);
		return edit;
    }

    QButtonGroup* pButtonGroup = nullptr;
  
    QButtonGroup* doBeginButtonGroup(const QString& groupName)
    {
        if (pButtonGroup)
        {
            Console->printWarning(called_info, "you can not call BeginButtonGroup before call EndButtonGroup");
            return nullptr;
        }
        else
        {
            pButtonGroup = new QButtonGroup;
            pButtonGroup->setExclusive(true);
            pButtonGroup->setObjectName(groupName);
            connect(pButtonGroup, (void (QButtonGroup::*)(int,bool))&QButtonGroup::buttonToggled, [=](int index,bool toggled) {
                emit signal_ButtonGroupToggled(groupName, index, toggled);
            });
        }
        return pButtonGroup;
    }

    QRadioButton* doSubButton(const QString& buttonName,const QString &text,bool useIcon,const QString &iconPath = QString())
    {
        if (!pButtonGroup)
        {
            Console->printError(called_info, "you can not call SubButton before call BeginButtonGroup");
            return nullptr;
        }
        else
        {
            QRadioButton* radioButton = new QRadioButton(this);
            radioButton->setObjectName(buttonName);
            radioButton->setText(text);
            if (useIcon)
            {
                radioButton->setIcon(QIcon(iconPath));
            }
            return radioButton;
        }
    }

    void doEndButtonGroup()
    {
		if (!pButtonGroup)
		{
			Console->printWarning(called_info, "you can not call EndButtonGroup before call BeginButtonGroup");
		}
        else
        {
            pButtonGroup = nullptr;
        }
    }

    QTabWidget* pTabWidget = nullptr;

    QTabWidget* beginTab(const QString &tabName)
    {
        if (pTabWidget)
        {
			Console->printWarning(called_info, "you can not call BeginTab before call EndTab");
			return nullptr;
        }
        else
        {
            pTabWidget = new QTabWidget;
            pTabWidget->setObjectName(tabName);
            layoutsStack.top()->addWidget(pTabWidget);
        }
        return pTabWidget;
    }

    void endTab()
    {
		if (!pTabWidget)
		{
			Console->printWarning(called_info, "you can not call EndTab before call BeginTab ");
		}
		else
		{
            pTabWidget = nullptr;
		}
    }
    
    QWidget* beginSubTab(const QString &tabName,const QString &tabTitle)
    {
		if (!pTabWidget)
		{
			Console->printWarning(called_info, "you can not call BeginSubTab before call BeginTab");
		}
        QWidget* widget = new QWidget(pTabWidget);
        widget->setObjectName(tabName);
        widget->setLayout(new QGridLayout);
        layoutsStack.push(widget->layout());
        pTabWidget->addTab(widget, tabTitle);
        return widget;
    }

    void endSubTab()
    {
		if (!pTabWidget)
		{
			Console->printWarning(called_info, "you can not call EndSubTab before call BeginSubTab");
		}
        else
        {
            layoutsStack.pop();
        }
    }
};
