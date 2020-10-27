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
#include "WrappedProgressBar.h"
#include "IPAddress.h"
#include "WrappedTableWidget.h"

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

    void doTab();

    void endTab();
    
    QSpinBox* doSpinBox(const QString& objectName, int min,int max,int step)
    {
        QSpinBox* box = new QSpinBox;
        box->setObjectName(objectName);
        box->setRange(min, max);
        box->setSingleStep(step);
		return box;
    }

	QDoubleSpinBox* doDoubleSpinBox(const QString& objectName, double min, double max, double step)
	{
        QDoubleSpinBox* box = new QDoubleSpinBox;
		box->setObjectName(objectName);
		box->setRange(min, max);
		box->setSingleStep(step);
		return box;
	}

    QButtonGroup* doButtonGroup(const QString& objectName, const QStringList& textList, const QStringList& imageList)
    {
        QButtonGroup* buttonGroup = new QButtonGroup;
        buttonGroup->setExclusive(true);
        buttonGroup->setObjectName(objectName);
		objectNamesSets.insert(objectName);

        int size = textList.size();

        for (int i = 0; i < size; i++)
        {
            QRadioButton* radioButton = new QRadioButton;
            if (i < imageList.size())
            {
                radioButton->setIcon(QIcon(imageList[0]));
            }
            radioButton->setText(textList[i]);
            buttonGroup->addButton(radioButton);
            layoutsStack.top()->addWidget(radioButton);
        }
		connect(buttonGroup, (void (QButtonGroup::*)(int,bool))&QButtonGroup::buttonToggled, this, [=](int index,bool value) {
			const QString& objectName = QObject::sender()->objectName();
            emit signal_ButtonGroupToggled(objectName, index, value);
			});
        return buttonGroup;
    }

    QPlainTextEdit* doPlainTextEdit(const QString& objectName)
    {
        QPlainTextEdit* edit = new QPlainTextEdit;
		connect(edit, &QPlainTextEdit::textChanged, this, [=]() {emit signal_EditFinished(objectName); });
		layoutsStack.top()->addWidget(edit);
		return edit;
    }
};
