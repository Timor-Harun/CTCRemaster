#include "ConsoleMessageItemWidget.h"

QPixmap ConsoleMessageItemWidget::getIconByMessageType(MessageType type)
{
	if (type == MessageType::Info)
	{
		return "icons/console/console_info.png";
	}
	else if (type == MessageType::Warning)
	{
		return "icons/console/console_warning.png";
	}
	else
	{
		return "icons/console/console_error.png";
	}
}

QString ConsoleMessageItemWidget::getMessagePrefixString(MessageType type)
{
	QString result;

	if (type == MessageType::Info)
	{
		result = "[Info] ";
	}
	else if (type == MessageType::Warning)
	{
		result = "[Warning] ";
	}
	else
	{
		result = "[Error] ";
	}
	QDateTime current_date_time = QDateTime::currentDateTime();
	QString current_date = current_date_time.toString("yyyy.MM.dd hh:mm:ss");
	//result += current_date;

	return result;
}

MessageType ConsoleMessageItemWidget::getType()
{
	return msg.type;
}

void ConsoleMessageItemWidget::setMessage(Message message)
{
	this->msg = message;
	iconLabel->setPixmap(getIconByMessageType(message.type).scaled(Default_Message_Icon_Size));
	calledInfoLabel->setText(getMessagePrefixString(message.type) + " " + message.calledInfo);
	messasgeLabel->setText(message.message);
}

ConsoleMessageItemWidget::ConsoleMessageItemWidget(QListWidget* parent, Message message)
{
	//ConsoleMessageItemWidget 布局主要分为两个部分
	//左边显示消息的图标，右边则用于显示文本
	//其中右上方用于显示调用信息，右下方用于显示消息的主体内容
	this->msg = message;
	//设置ItemWidget的布局
	QLayout* layout = new QHBoxLayout;
	setLayout(layout);
	//设置layout相关属性
	layout->setContentsMargins(10, 0, 10, 0);
	layout->setSpacing(1);
	//设置显示 icon 的 label 的相关属性
	iconLabel = new QLabel;
	iconLabel->setFixedWidth(Default_Message_Icon_Width);
	iconLabel->setPixmap(getIconByMessageType(message.type).scaled(Default_Message_Icon_Size));
	//添加label控件
	layout->addWidget(iconLabel);

	//右半部分的窗口
	QWidget* widget_Right = new QWidget;
	//垂直布局
	layout = new QVBoxLayout;
	widget_Right->setLayout(layout);
	widget_Right->layout()->setSpacing(1);

	//格式化文本部分
	this->msg.calledInfo = (getMessagePrefixString(msg.type) + " " + msg.calledInfo);

	//label 的创建
	calledInfoLabel = new QLabel(this->msg.calledInfo);
	messasgeLabel = new QLabel(msg.message);

	//由上至下添加到垂直布局中
	layout->addWidget(calledInfoLabel);
	layout->addWidget(messasgeLabel);

	//当前窗口的水平布局加入右半部分的子窗口
	this->layout()->addWidget(widget_Right);
}
