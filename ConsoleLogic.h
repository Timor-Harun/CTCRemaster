#pragma once

/*********QT CLASS**********/
#include <qpushbutton.h>
#include <qlineedit.h>
#include <qlistWidget.h>
#include <qlabel.h>
#include <qmenu.h>
#include <qevent.h>
#include <QCheckBox>
#include <QTimer>

/*********Custom CLASS**********/
#include "ConsoleMessageItemWidget.h"
#include "SingletonDialog.h"
#include "IconButton.h"
#include "ConsoleListWidget.h"
#include "ConsoleMessagePool.h"

/********* MACROS **********/
#define Console ConsoleLogic::getInstance()

class ConsoleLogic : public QObject
{
	using MessageVector = QVector<Message>;
	Q_OBJECT
private:
	//记录了三种不同消息的数量
	int					count[3] = { 0,0,0 };
	//显示不同消息的数量的Label
	QLabel*				label_Count;
	//按钮：过滤器，搜索，清除
	QPushButton*		Button_Filter;
	QPushButton*		Button_Serach;
	QPushButton*		Button_Clear;
	//单选框，是否自动滚动
	QCheckBox*          checkBox_AutoRoll;
	ConsoleMessagePool* pool;
	bool                showInfo;
	bool                showWarning;
	bool                showError;

	ConsoleListWidget*  listWidget;
	MessageVector       messages;

	QTimer*             updateTimer;
	void				init();
	void				printInternal(const QString &calledInfo, const QString &message, MessageType type);
	void				updateCountLabel();
	void                onEnabledStageChanged();
protected:
	void				onClickSerach();
	void				onClickClaer();
	void				keyPressEvent(QKeyEvent* e);

	static ConsoleLogic* instance;
public:
	static ConsoleLogic* getInstance()
	{
		if (!ConsoleLogic::instance)
		{
			instance = new ConsoleLogic;
		}
		return instance;
	}
	ConsoleLogic(QObject *parent = NULL);
	~ConsoleLogic();

	ConsoleMessagePool* getPoolPtr()
	{
		return pool;
	}
public:
	void				 printInfo(const QString &calledInfo, const QString &message);
	void				 printWarning(const QString &calledInfo, const QString &message);
	void				 printError(const QString &calledInfo, const QString &message);
	friend class CTCMainWindow;
};
