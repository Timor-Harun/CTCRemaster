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
	//���� ��Ϣ���� ���� ͼ���ļ�
	QPixmap			getIconByMessageType(MessageType type);
	//���� ��Ϣ���� ��ȡ ��Ϣ�ı���Ϣǰ׺
	QString		    getMessagePrefixString(MessageType type);

	//�洢��Ϣ
	Message         msg;

	QLabel* iconLabel;
	QLabel* calledInfoLabel;
	QLabel* messasgeLabel;
public:
	MessageType     getType();
	void            setMessage(Message message);
	ConsoleMessageItemWidget(QListWidget* parent, Message message);
};

