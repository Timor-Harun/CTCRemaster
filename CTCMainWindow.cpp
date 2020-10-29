#include "CTCMainWindow.h"

CTCMainWindow::CTCMainWindow(QWidget* parent)
	: QMainWindow(parent), menuItemRoot(new MenuItemNode)
{
	ui.setupUi(this);
	QSplitter* splitter = new QSplitter(ui.widget_Main);
	splitter->setOpaqueResize(false);
	splitter->addWidget(ui.navTreeView);
	splitter->addWidget(ui.tabWidget);
	splitter->setOrientation(Qt::Orientation::Horizontal);
	splitter->setStretchFactor(0, 1);
	splitter->setStretchFactor(1, 1);

	ui.widget_Main->setLayout(new QHBoxLayout);
	ui.widget_Main->layout()->addWidget(splitter);

	this->setWindowFlag(Qt::FramelessWindowHint);

	QList<QString>* pWidgetFiles;
	QList<QString>* pMenuFiles;
	try
	{
		Q_ASSERT(Python->doStartUp());

	}
	catch (boost::python::error_already_set& e)
	{
		QMessageBox::critical(NULL, "Python Fatal Error!", Python->getLastErrorString());
	}

	pWidgetFiles = &(Python->getWidgetPythonFiles());
	pMenuFiles = &(Python->getMenuPythonFiles());

	for (int i = 0; i < pWidgetFiles->size(); i++)
	{
		ui.navTreeView->addItem(TimorHarun::Utility::getFileNamePrefix(pWidgetFiles->at(i)));
	}
	auto infos = Python->getMenuItemInfos();
	for (auto& info : infos)
	{
		addMenuItem(info);
	}
	WrappedTableWidget* widget = new WrappedTableWidget;

	widget->setVerticalHeaderLabels(QStringList() << "123" << "456");
	widget->setColumnCount(2);
	widget->appendRow({ "123","4567" });
	widget->appendRow({ "345","456567" });
	widget->appendRow({ "7534","456767" });

	widget->setItem(1, 2, "123");
	auto index = widget->findItems("123");
	ui.tabWidget->addTab(widget, "table");

	Console->Button_Clear = ui.button_Console_Clear;
	Console->Button_Filter = ui.button_Console_Filter;
	Console->Button_Serach = ui.button_Console_Serach;
	Console->checkBox_AutoRoll = ui.checkBox_Console_AutoRoll;
	Console->listWidget = ui.listWidget;
	Console->label_Count = ui.label_Console;
	Console->init();

	connect(DialogExecutor::getInstance(), &DialogExecutor::execDialogSignals, [=](const std::string& filePath) {
		WrappedWidget* widget = Python->doGetWidgetCreation(TimorHarun::Utility::getFileNamePrefix(QString::fromStdString(filePath)),true);
		widget->setWindowModality(Qt::ApplicationModal);//设置窗体模态，要求该窗体没有父类，否则无效
		widget->show();
		});

}