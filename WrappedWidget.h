#pragma once
#ifndef WrappedWidget_H
#define WrappedWidget_H

/******* QT Widget Class ********/
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QCheckBox>
#include <QProgressBar>
#include <QGroupBox>
#include <QLineEdit>
#include <QTabWidget>
#include <QComboBox>
#include <QLayout>
#include <QPlainTextEdit>
#include <QButtonGroup>
#include <QRadioButton>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QFontComboBox>

/******* QT Json-Relative Class ********/
#include <QJsonParseError>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include <QVector>
#include <QStack>

/******* QT Event Class ********/
#include <QCloseEvent>

/******* QT Other Class ********/
#include <QDebug>

/******* Custom Class ********/
#include "WrappedTableWidget.h"
#include "WrappedProgressBar.h"
#include "WrappedTabWidget.h"
#include "IPAddress.h"
#include "ConsoleLogic.h"

/// <summary>
/// ���� �ؼ�����ָ�� ���� ����˳�� ���� ���ڽ��棬ͬʱ��UI�ؼ����¼�
/// </summary>
class WrappedWidget : public QWidget
{
	Q_OBJECT

public:
	//���캯���Լ���������
	WrappedWidget(QWidget* parent = Q_NULLPTR);
	~WrappedWidget() {  };

private:
	//���ڶ�Ӧ��uuidֵ����Ϊ�ô��ڵ�Ψһ��ʶ��
	QString                uuid;

	//���ڵ������֣�λ�ڲ���ջ��ջ��
	QVBoxLayout*		   mainLayout;

	//�������ļ��ϣ�Ϊ�˷�ֹ�Ӷ�������ظ�������
	QSet<QString>          objectNamesSets;

	//����ջ
	QStack<QLayout*>       layoutsStack;

	//����ָ��ջ
	QStack<QWidget*>       widgetsStack;

	//��ť���ָ�룬����BeginButtonGroup
	QButtonGroup*          pButtonGroup = nullptr;

	//ѡ����ڵ�ָ��,����BeginTab
	QTabWidget*            pTabWidget = nullptr;

Q_SIGNALS:
	/******** ���¶���������źţ����������Կؼ����¼���ת�� ********/

	//��ť���
	void signal_ButtonClickEvent(const QString& objectName);

	//�༭���
	void signal_EditFinished(const QString& objectName);

	//��ѡ״̬�ı�
	void signal_CheckBoxStageChanged(const QString& objectName);

	//���ѡ���� �ı�
	void signal_TableSelectedIndexChanged(const QString& objectName, int row);

	//΢������ֵ�ı�
	void signal_SpinBoxValueChanged(const QString& objectName, int value);

	//��ť��ѡ�� �İ�ť�ı�
	void signal_ButtonGroupToggled(const QString& objectName, int index, bool value);

	//���ڹر�
	void signal_close();

protected:
	//��д�ر��¼��������ڹر�ʱ������signal_close���Ա������ڴ���������Ӧ�ķ���
	void closeEvent(QCloseEvent* event);
public:
	//���� ΨһID
	void setUUID(const QString& uuid);

	//��ȡΨһID
	QString getUUID();

	/******* ��̬ ���� UI �ĺ��Ĳ��� *******/

	/******* ���ֲ��� *******/

	// ��ʼˮƽ����
	void doHorizontalLayout();

	// ��ʼ��ֱ����
	void doVerticalLayout();

	// ������ǰ����
	void endLayout();

	// ����϶
	void doSpacer(int spacing);

	/******* Display ���� *******/

	// ���ɱ�ǩ
	QLabel* doLabel(const QString& objectName, const QString& text, bool imageMode,const QString &imagePath);

	// ���ɽ�����
	WrappedProgressBar* doProgressBar(const QString& objectName, int value, int min, int max);

	// ���ɱ��
	WrappedTableWidget* doTable(const QString& objectName, const QStringList& headerLabels);

	/******* Clickable ���� *******/

	// ���ɰ�ť
	QPushButton* doButton(const QString& objectName, const QString& buttonText);

	// ���ɰ�ť�� �µ��Ӱ�ť
	QRadioButton* doSubButton(const QString& buttonName, const QString& text, bool useIcon, const QString& iconPath = QString());

	/******* Editable ���� *******/

	// ���б༭��
	QLineEdit* doLineEdit(const QString& objectName);

	// ���ı��༭��
	QPlainTextEdit* doPlainTextEdit(const QString& objectName);

	// ����΢����
	QSpinBox* doSpinBox(const QString& objectName, int min, int max, int step);

	// ˫���ȸ�����΢����
	QDoubleSpinBox* doDoubleSpinBox(const QString& objectName, double min, double max, double step);

	// IP��ַ�༭��
	IPAddress* doIPAddress(const QString& objectName);

	/******* Checkable ���� *******/

	// ��Ͽ�
	QComboBox* doComboBox(const QString& objectName, const QStringList& items);

	// ��ѡ��
	QCheckBox* doCheckBox(const QString& objectName, const QString& objectText, bool checked);

	/******* Container ���� *******/

	// ��ʼ�����
	void doGroupBox(const QString& title);

	// ���������
	void endGroupBox();

	// ��ʼ��ť��
	QButtonGroup* doBeginButtonGroup(const QString& groupName);

	// ������ť��
	void doEndButtonGroup();

	// ��ʼѡ�����
	QTabWidget* beginTab(const QString& tabName, bool styled);

	// ����ѡ�����
	void endTab();

	// ��ʼ��ѡ�
	QWidget* beginSubTab(const QString& tabName, const QString& tabTitle);

	// ������ѡ�
	void endSubTab();
};
#endif
