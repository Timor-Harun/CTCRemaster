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
public:
    void doHorizontalLayout()
    {
        QWidget* widget = new QWidget;
        QHBoxLayout* hLayout = new QHBoxLayout(widget);
        widget->setLayout(hLayout);
        layoutsStack.push(hLayout);
    }

    void doVerticalLayout()
    {
        QWidget* widget = new QWidget;
        QVBoxLayout* vLayout = new QVBoxLayout(widget);
        widget->setLayout(vLayout);

        layoutsStack.push(vLayout);
    }

    QPushButton* doButton(const QString&objectName, const QString &buttonText)
    {
        QPushButton* button = new QPushButton;
        button->setObjectName(objectName);
        objectNamesSets.insert(objectName);

        button->setText(buttonText);
        connect(button, &QPushButton::clicked, this, [=]() {
            const QString &objectName = QObject::sender()->objectName();
            emit signal_ButtonClickEvent(objectName);
            });

        layoutsStack.top()->addWidget(button);
        return button;
    }
    void setUUID(const QString&uuid)
    {
        this->uuid = uuid;
    }
    const QString &getUUID()
    {
        return this->uuid;
    }

    QLineEdit* doLineEdit(const QString&objectName)
    {
        QLineEdit* lineEdit = new QLineEdit;
        connect(lineEdit, &QLineEdit::editingFinished, this, [=]() {emit signal_EditFinished(objectName); });
        layoutsStack.top()->addWidget(lineEdit);
        return lineEdit;
    }

    void doSpacer(int spacing)
    {
        ((QBoxLayout*)(layoutsStack.top()))->addSpacing(spacing);
    }

    QComboBox* doComboBox(const QString&objectName, const QStringList &items)
    {
        QComboBox* box = new QComboBox;
        box->setObjectName(objectName);
        box->addItems(items);
        return box;
    }

    QCheckBox* doCheckBox(const QString&objectName, const QString&objectText, bool checked)
    {
        QCheckBox* checkBox = new QCheckBox;
        checkBox->setObjectName(objectName);
        checkBox->setText(objectText);
        checkBox->setChecked(checked);

        connect(checkBox, &QCheckBox::toggled, this, [=]() {emit signal_CheckBoxStageChanged(objectName); });
        layoutsStack.top()->addWidget(checkBox);

        return checkBox;
    }

    WrappedProgressBar* doProgressBar(const QString&objectName, int value, int min, int max)
    {
        WrappedProgressBar* progressBar = new WrappedProgressBar;
        progressBar->setObjectName(objectName);
        progressBar->setRange(min, max);
        progressBar->setValue(value);
        layoutsStack.top()->addWidget(progressBar);
        return progressBar;
    }

    WrappedTableWidget* doTable(const QString& objectName,const QStringList &headerLabels) 
    {
        WrappedTableWidget* table = new WrappedTableWidget;
        table->setHeadTitle(headerLabels);
        table->setObjectName(objectName);
        layoutsStack.top()->addWidget(table);
		connect(table, &WrappedTableWidget::itemSelectionChanged, this, [=]() {
			emit signal_TableSelectedIndexChanged(objectName,table->getSelectedRowIndex());
			});
        return table;
    }

    IPAddress* doIPAddress(const QString&objectName)
    {
        IPAddress* address = new IPAddress;
        address->setObjectName(objectName);

        layoutsStack.top()->addWidget(address);
        return address;
    }
    void doGroupBox(const QString&title)
    {
        QGroupBox* groupBox = new QGroupBox(title);
        groupBox->setLayout(new QGridLayout);
        layoutsStack.top()->addWidget(groupBox);
        layoutsStack.push(groupBox->layout());
    }

    void endGroupBox()
    {
        layoutsStack.pop();
    }

    QLabel* doLabel(const QString &text)
    {
        QLabel* label = new QLabel(text);

        layoutsStack.top()->addWidget(label);
        return label;
    }
    void endLayout()
    {
        QLayout* layout = layoutsStack.top();
        layoutsStack.pop();
        QWidget* widget = qobject_cast<QWidget*>(layout->parent());
        layoutsStack.top()->addWidget(widget);
    }

    void doTab()
    {

    }
    void endTab()
    {

    }
};
