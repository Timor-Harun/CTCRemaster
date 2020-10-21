#pragma once
#include <QListWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QDateTime>

#include "Global.h"

#define Default_Message_Icon_Size  QSize(30,30)
#define Default_Message_Icon_Width 30

class ConsoleMessageItemWidget :public QWidget
{
private:
	//根据 消息类型 加载 图标文件
	QPixmap			getIconByMessageType(MessageType type);
	//根据 消息类型 获取 消息文本信息前缀
	QString		    getMessagePrefixString(MessageType type);

	//存储消息
	Message         msg;

	QLabel* iconLabel;
	QLabel* calledInfoLabel;
	QLabel* messasgeLabel;
public:
	MessageType     getType();
	void            setMessage(Message message);
	ConsoleMessageItemWidget(QListWidget* parent, Message message);
};

