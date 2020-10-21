#include "ConsoleLogic.h"
#include <QSplitter>

ConsoleLogic* ConsoleLogic::instance = nullptr;
void ConsoleLogic::init()
{
	QMenu* menu = new QMenu;

	QAction* action_info = new QAction("Information");
	action_info->setCheckable(true);
	action_info->setChecked(true);

	QAction* action_warning = new QAction("Warning");
	action_warning->setCheckable(true);
	action_warning->setChecked(true);

	QAction* action_eror = new QAction("Error");
	action_eror->setCheckable(true);
	action_eror->setChecked(true);

	connect(action_info, &QAction::toggled, this, [=](bool value)
		{
			showInfo = value;
			onEnabledStageChanged();
		});
	connect(action_warning, &QAction::toggled, this, [=](bool value)
		{
			showWarning = value;
			onEnabledStageChanged();
		});

	connect(action_eror, &QAction::toggled, this, [=](bool value)
		{
			showError = value;
			onEnabledStageChanged();
		});

	connect(Button_Serach, &QPushButton::clicked, this, &ConsoleLogic::onClickSerach);
	connect(Button_Clear, &QPushButton::clicked, this, &ConsoleLogic::onClickClaer);


	connect(checkBox_AutoRoll, &QCheckBox::toggled, listWidget, &ConsoleListWidget::setAutoRoll);

	menu->addActions({ action_info ,action_warning,action_eror });
	menu->addSeparator();

	Button_Filter->setMenu(menu);

	listWidget->setMessagePtr(&messages);

	updateTimer->setInterval(10);
	connect(updateTimer, &QTimer::timeout, [=]() {
		while (!pool->isEmpty())
		{
			messages.append(pool->getLastMessage());
			count[(int)(messages.back().type)]++;
			listWidget->refreshAfterPrint(messages.size() - 1);
		}
		updateCountLabel();
		});
	updateTimer->start();
}

void ConsoleLogic::onClickSerach()
{
	QString content;
	SingletonDialog::setInstanceType("ConsoleSerach");
	SingletonDialog* dialog = new SingletonDialog;

	dialog->setParent(listWidget);

	dialog->setStyleSheet("QDialog{background-color: rgb(255, 255, 255);border: 1px solid gray}");
	dialog->setGeometry(listWidget->size().width() - 250, 0, 230, 50);


	QLabel* l = new QLabel("Find");
	l->setParent(dialog);
	l->setGeometry(10, 15, 100, 20);
	l->setAttribute(Qt::WA_DeleteOnClose);

	QLineEdit* edit = new QLineEdit;
	edit->setGeometry(50, 15, 100, 20);
	edit->setParent(dialog);
	edit->setAttribute(Qt::WA_DeleteOnClose);

	IconButton* icon_Serach = new IconButton("icons/console/serach.png");
	IconButton* icon_Close = new IconButton("icons/console/close.png");

	icon_Serach->setParent(dialog);
	icon_Serach->setPosition(170, 15);
	icon_Serach->setFixedSize(20, 20);

	icon_Close->setParent(dialog);
	icon_Close->setPosition(200, 15);
	icon_Close->setFixedSize(20, 20);


	dialog->show();

	icon_Close->addClickEvent([=]() {
		dialog->close();
		});

	icon_Serach->addClickEvent([=]() {
		QVector<int> indexes;
		for (int i = 0; i < messages.size(); i++)
		{
			if (messages[i].serach(edit->text()))
			{
				indexes.push_back(i);
			}
		}
		listWidget->setValidIndexes(indexes);
		listWidget->refreshAfterIndexesChanged();
		});
}

void ConsoleLogic::onClickClaer()
{
	listWidget->clear();
}

void ConsoleLogic::printInfo(const QString & calledInfo, const QString & message)
{
	pool->pushMessage(Message(calledInfo, message, MessageType::Info));
}

void ConsoleLogic::printWarning(const QString & calledInfo,const QString & message)
{
	pool->pushMessage(Message(calledInfo, message, MessageType::Warning));
}

void ConsoleLogic::printError(const QString & calledInfo, const QString & message)
{
	pool->pushMessage(Message(calledInfo, message, MessageType::Error));
}

void ConsoleLogic::printInternal(const QString & calledInfo, const QString & message, MessageType type)
{
	pool->pushMessage(Message(calledInfo, message, type));
	//messages.push_back(Message(calledInfo, message, type));
	return;
	if ((type == MessageType::Info && !showInfo) ||
		(type == MessageType::Warning && !showWarning) ||
		(type == MessageType::Error && !showError))
	{
		/*Nothing*/
	}
	else
	{
		listWidget->refreshAfterPrint(messages.size()-1);
	}

}

void ConsoleLogic::updateCountLabel()
{
	this->label_Count->setText(QString("Í¨Öª£º %1  ´íÎó£º%2  ¾¯¸æ£º%3").arg(count[0]).arg(count[1]).arg(count[2]));
}

void ConsoleLogic::onEnabledStageChanged()
{
	QVector<int> indexes;
	for (int i = 0; i < messages.size(); i++)
	{
		if ((messages.at(i).type == MessageType::Info && !showInfo) ||
			(messages.at(i).type == MessageType::Warning && !showWarning) ||
			(messages.at(i).type == MessageType::Error && !showError))
		{
			continue;
		}
		indexes.push_back(i);
	}
	listWidget->setValidIndexes(indexes);
	listWidget->refreshAfterIndexesChanged();
}

void ConsoleLogic::keyPressEvent(QKeyEvent* e)
{
	if (listWidget->hasFocus())
	{
		if (e->modifiers() == Qt::KeyboardModifiers::enum_type::ControlModifier && e->key() == Qt::Key::Key_F)
		{
			this->onClickSerach();
		}
	}
}

ConsoleLogic::ConsoleLogic(QObject* parent)
	: QObject(parent), pool(new ConsoleMessagePool), updateTimer(new QTimer){}

ConsoleLogic::~ConsoleLogic() {}