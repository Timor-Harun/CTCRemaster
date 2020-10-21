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
	//ConsoleMessageItemWidget ������Ҫ��Ϊ��������
	//�����ʾ��Ϣ��ͼ�꣬�ұ���������ʾ�ı�
	//�������Ϸ�������ʾ������Ϣ�����·�������ʾ��Ϣ����������
	this->msg = message;
	//����ItemWidget�Ĳ���
	QLayout* layout = new QHBoxLayout;
	setLayout(layout);
	//����layout�������
	layout->setContentsMargins(10, 0, 10, 0);
	layout->setSpacing(1);
	//������ʾ icon �� label ���������
	iconLabel = new QLabel;
	iconLabel->setFixedWidth(Default_Message_Icon_Width);
	iconLabel->setPixmap(getIconByMessageType(message.type).scaled(Default_Message_Icon_Size));
	//���label�ؼ�
	layout->addWidget(iconLabel);

	//�Ұ벿�ֵĴ���
	QWidget* widget_Right = new QWidget;
	//��ֱ����
	layout = new QVBoxLayout;
	widget_Right->setLayout(layout);
	widget_Right->layout()->setSpacing(1);

	//��ʽ���ı�����
	this->msg.calledInfo = (getMessagePrefixString(msg.type) + " " + msg.calledInfo);

	//label �Ĵ���
	calledInfoLabel = new QLabel(this->msg.calledInfo);
	messasgeLabel = new QLabel(msg.message);

	//����������ӵ���ֱ������
	layout->addWidget(calledInfoLabel);
	layout->addWidget(messasgeLabel);

	//��ǰ���ڵ�ˮƽ���ּ����Ұ벿�ֵ��Ӵ���
	this->layout()->addWidget(widget_Right);
}
