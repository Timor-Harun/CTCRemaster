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
/// 根据 控件生成指令 按照 布局顺序 生成 窗口界面，同时绑定UI控件的事件
/// </summary>
class WrappedWidget : public QWidget
{
	Q_OBJECT

public:
	//构造函数以及析构函数
	WrappedWidget(QWidget* parent = Q_NULLPTR);
	~WrappedWidget() {  };

private:
	//窗口对应的uuid值，作为该窗口的唯一标识符
	QString                uuid;

	//窗口的主布局，位于布局栈的栈底
	QVBoxLayout*		   mainLayout;

	//对象名的集合，为了防止子对象包含重复的名称
	QSet<QString>          objectNamesSets;

	//布局栈
	QStack<QLayout*>       layoutsStack;

	//窗口指针栈
	QStack<QWidget*>       widgetsStack;

	//按钮组的指针，用于BeginButtonGroup
	QButtonGroup*          pButtonGroup = nullptr;

	//选项卡窗口的指针,用于BeginTab
	QTabWidget*            pTabWidget = nullptr;

Q_SIGNALS:
	/******** 以下定义了相关信号，当接受来自控件的事件后转发 ********/

	//按钮点击
	void signal_ButtonClickEvent(const QString& objectName);

	//编辑完成
	void signal_EditFinished(const QString& objectName);

	//勾选状态改变
	void signal_CheckBoxStageChanged(const QString& objectName);

	//表格选中行 改变
	void signal_TableSelectedIndexChanged(const QString& objectName, int row);

	//微调框数值改变
	void signal_SpinBoxValueChanged(const QString& objectName, int value);

	//按钮组选中 的按钮改变
	void signal_ButtonGroupToggled(const QString& objectName, int index, bool value);

	//窗口关闭
	void signal_close();

protected:
	//重写关闭事件，当窗口关闭时，发射signal_close，以便主窗口处理并调用相应的方法
	void closeEvent(QCloseEvent* event);
public:
	//设置 唯一ID
	void setUUID(const QString& uuid);

	//获取唯一ID
	QString getUUID();

	/******* 动态 生成 UI 的核心部分 *******/

	/******* 布局部分 *******/

	// 开始水平布局
	void doHorizontalLayout();

	// 开始垂直布局
	void doVerticalLayout();

	// 结束当前布局
	void endLayout();

	// 填充空隙
	void doSpacer(int spacing);

	/******* Display 部分 *******/

	// 生成标签
	QLabel* doLabel(const QString& objectName, const QString& text, bool imageMode,const QString &imagePath);

	// 生成进度条
	WrappedProgressBar* doProgressBar(const QString& objectName, int value, int min, int max);

	// 生成表格
	WrappedTableWidget* doTable(const QString& objectName, const QStringList& headerLabels);

	/******* Clickable 部分 *******/

	// 生成按钮
	QPushButton* doButton(const QString& objectName, const QString& buttonText);

	// 生成按钮组 下的子按钮
	QRadioButton* doSubButton(const QString& buttonName, const QString& text, bool useIcon, const QString& iconPath = QString());

	/******* Editable 部分 *******/

	// 单行编辑框
	QLineEdit* doLineEdit(const QString& objectName);

	// 富文本编辑框
	QPlainTextEdit* doPlainTextEdit(const QString& objectName);

	// 整型微调框
	QSpinBox* doSpinBox(const QString& objectName, int min, int max, int step);

	// 双精度浮点型微调框
	QDoubleSpinBox* doDoubleSpinBox(const QString& objectName, double min, double max, double step);

	// IP地址编辑框
	IPAddress* doIPAddress(const QString& objectName);

	/******* Checkable 部分 *******/

	// 组合框
	QComboBox* doComboBox(const QString& objectName, const QStringList& items);

	// 单选框
	QCheckBox* doCheckBox(const QString& objectName, const QString& objectText, bool checked);

	/******* Container 部分 *******/

	// 开始分组框
	void doGroupBox(const QString& title);

	// 结束分组框
	void endGroupBox();

	// 开始按钮组
	QButtonGroup* doBeginButtonGroup(const QString& groupName);

	// 结束按钮组
	void doEndButtonGroup();

	// 开始选项卡窗口
	QTabWidget* beginTab(const QString& tabName, bool styled);

	// 结束选项卡窗口
	void endTab();

	// 开始子选项卡
	QWidget* beginSubTab(const QString& tabName, const QString& tabTitle);

	// 结束子选项卡
	void endSubTab();
};
#endif
