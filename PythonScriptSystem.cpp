#include "PythonScriptSystem.h"

PythonScriptSystem* PythonScriptSystem::instance = nullptr;

WrappedWidget* PythonScriptSystem::doGetWidgetCreation(const QString &fileName, bool isDialog)
{
	//窗口的指针
	WrappedWidget* widget = NULL;
	
	//如果不是对话框，此处不用PyEval_RestoreThread，原因未知
	if (m_threadState && !isDialog)
		PyEval_RestoreThread(m_threadState);
	py_try_begin_safe
	{
		//设置当前执行的Widget类名，以将Widget的CreateCommand（Json信息）存入字典中
		m_PFN_SetCurrentWidgetClassName(stdstr(fileName));

		//获取的类的对象的句柄
		handle<> classHandle = extract<handle<>>(m_widgetClassNameMap[fileName]());

		//执行OnGUI函数，产生CreateCommand的字符串信息
		call_method<void>(classHandle.get(), "OnGUI");

		//获取窗口的UUID值
		std::string _uuid = call_method<std::string>(classHandle.get(), "getUUID");

		//获取当前CreateCommand的Json字符串对应的object
		object jsonret = m_PFN_GetUIElementsJsonString();

		//抽取jsonret为std::string类型
		std::string _json = extract<std::string>(jsonret);

		//正式创建窗口
		widget = new WrappedWidget;
		widget->setAttribute(Qt::WA_DeleteOnClose);
		widget->setWindowTitle(fileName);
		widget->setUUID(QString::fromStdString(_uuid));
		
		//创建窗口信息（WidgetInfo）对象
		handle<> infoHandle = extract<handle<>>(m_PFN_GetCurrentWidgetInfos());

		//初始化解析Json所需的变量
		QJsonParseError jsonError;
		QByteArray byte(_json.c_str());
		QJsonDocument doucment = QJsonDocument::fromJson(byte, &jsonError);  // 转化为 JSON 文档

		// 如果解析未发生错误，则开始动态生成UI元素
		if (!doucment.isNull() && (jsonError.error == QJsonParseError::NoError)) {  
			if (doucment.isArray())
			{
				QJsonArray array = doucment.array();
				for (int i = 0; i < array.size(); i++)
				{
					if (array[i].isArray())
					{
						QJsonArray _array = array[i].toArray();
						//第0个元素代表窗口类别
						int typeCode = _array[0].toInt();

						#pragma region Display
						/******* Display 类型 *******/

						//QLabel类型
						if (typeCode == WindowCommandType::Label)
						{
							QString text = _array[1].toString();
							QLabel* label = widget->doLabel(text);
						}

						//WrappedProgressBar类型（SetValue变为发射信号，以便在多线程中更新）
						else if (typeCode == WindowCommandType::ProgressBar)
						{
							QString				objectName = _array[1].toString();
							int					value = _array[2].toInt();
							int					min = _array[3].toInt();
							int					max = _array[4].toInt();
							WrappedProgressBar* progressBar = widget->doProgressBar(objectName, value, min, max);
							//特别注意：此处updateValue_signal，需要绑定槽函数setValue，否则无法更新
							connect(progressBar, &WrappedProgressBar::updateValue_signal, progressBar, &WrappedProgressBar::setValue);
							call_method<void>(infoHandle.get(), "addHandle", objectName.toStdString(), typeCode, boost::shared_ptr<WrappedProgressBar>(progressBar));
						}
						#pragma endregion

						#pragma region Clickable
						/******* Clickable 类型 *******/

						//QPushButton类型
						else if (typeCode == WindowCommandType::Button)
						{
							QString      objectName = _array[1].toString();
							QString      objectText = _array[2].toString();
							QPushButton* btn = widget->doButton(objectName, objectText);
							//add Handle 代表 把对应控件的指针传递给Python，下同
							call_method<void>(infoHandle.get(),
											  "addHandle",
											  objectName.toStdString(),
											  typeCode, boost::shared_ptr<QPushButton>(btn));
						}
						else if (typeCode == WindowCommandType::SubButton)
						{
							QString      objectName = _array[1].toString();
							QString      text       = _array[2].toString();
							QString      iconPath   = _array[3].toString();
							QRadioButton*button     = widget->doSubButton(objectName, text, !iconPath.isEmpty(), iconPath);
							call_method<void>(infoHandle.get(),
											  "addHandle",
											  objectName.toStdString(),
											  typeCode, boost::shared_ptr<QRadioButton>(button));
						}
						#pragma endregion

						#pragma region Editable
						/******* Editable 类型 *******/

						//QLineEdit类型
						else if (typeCode == WindowCommandType::LineEdit)
						{
							QString    objectName = _array[1].toString();
							QLineEdit* edit = widget->doLineEdit(objectName);
							call_method<void>(infoHandle.get(),
								"addHandle",
								objectName.toStdString(),
								typeCode,
								boost::shared_ptr<QLineEdit>(edit));
						}

						//特殊类型：IP编辑框
						else if (typeCode == WindowCommandType::IPAddressEdit)
						{
							QString objectName = _array[1].toString();
							IPAddress* ipAddress = widget->doIPAddress(objectName);

							call_method<void>(infoHandle.get(),
								"addHandle",
								objectName.toStdString(),
								typeCode, boost::shared_ptr<IPAddress>(ipAddress));
						}
						//QSpinBox类型(整数类型微调框)
						else if (typeCode == WindowCommandType::SpinBox)
						{
							QString objectName = _array[1].toString();
							int min            = _array[2].toInt();
							int max            = _array[3].toInt();
							int step           = _array[4].toInt();
							QSpinBox* spinBox  = widget->doSpinBox(objectName, min, max, step);
							call_method<void>(infoHandle.get(), 
								              "addHandle",
								              objectName.toStdString(), 
								              typeCode, boost::shared_ptr<QSpinBox>(spinBox));
						}
						//QDoubleSpinBox类型(双精度浮点数 类型微调框)
						else if (typeCode == WindowCommandType::DoubleSpinBox)
						{
							QString objectName      = _array[1].toString();
							double  min             = _array[2].toDouble();
							double  max             = _array[3].toDouble();
							double  step            = _array[4].toDouble();
							QDoubleSpinBox* spinBox = widget->doDoubleSpinBox(objectName, min, max, step);

							call_method<void>(infoHandle.get(), 
								              "addHandle",
								              objectName.toStdString(),
								              typeCode, boost::shared_ptr<QDoubleSpinBox>(spinBox));
						}
						// QPlainTextEdit类型(富文本编辑框)
						else if (typeCode == WindowCommandType::PlainTextEdit)
						{
							QString objectName = _array[1].toString();
							QPlainTextEdit* edit = widget->doPlainTextEdit(objectName);
							call_method<void>(infoHandle.get(), "addHandle", objectName.toStdString(), typeCode, boost::shared_ptr<QPlainTextEdit>(edit));
						}
						#pragma endregion

						#pragma region Checkable
						/******* Checkable or Selectable 类型 *******/

						//QCheckBox类型
						else if (typeCode == WindowCommandType::CheckBox)
						{
							QString objectName = _array[1].toString();
							QString objectText = _array[2].toString();
							bool    checked = _array[3].toBool();
							QCheckBox* checkBox = widget->doCheckBox(objectName, objectText, checked);
							call_method<void>(infoHandle.get(),
								"addHandle",
								objectName.toStdString(),
								typeCode, boost::shared_ptr<QCheckBox>(checkBox));
						}

						//QComboBox类型
						else if (typeCode == WindowCommandType::ComboBox)
						{
							QString     objectName = _array[1].toString();
							QJsonArray _jsonArray = _array[2].toArray();

							//此处需要构建一个QStringList，将所有条目存入其中，以便ComboBox初始化
							QStringList items;
							for (auto& obj : _jsonArray)
							{
								items << obj.toString();
							}
							QComboBox* comboBox = widget->doComboBox(objectName, items);
							call_method<void>(infoHandle.get(),
								"addHandle",
								objectName.toStdString(),
								typeCode, boost::shared_ptr<QComboBox>(comboBox));
						}
						//QFontComboBox (选择字体类型，未实现)
						else if (typeCode == WindowCommandType::FontComboBox)
						{
							Console->printWarning(called_info, "doFontComboBox is not implement");
						}
						#pragma endregion

						#pragma region Container
						/******* Container 类型 *******/

						//执行 创建 Group
						else if (typeCode == WindowCommandType::BeginGroup)
						{
							QString groupName = _array[1].toString();
							widget->doGroupBox(groupName);
						}
						//结束 Group
						else if (typeCode == WindowCommandType::EndGroup)
						{
							widget->endGroupBox();
						}

						else if (typeCode == WindowCommandType::TableView)
						{
							QString     objectName = _array[1].toString();
							QJsonArray _jsonArray  = _array[2].toArray();

							//注意此处需要构建 tab 的表头标题的列表
							QStringList headers;
							for (int i = 0; i < _jsonArray.size(); i++)
							{
								headers << _jsonArray[i].toString();
							}
							WrappedTableWidget* table = widget->doTable(objectName, headers);
							call_method<void>(infoHandle.get(), 
								              "addHandle",
								              objectName.toStdString(), 
								              typeCode, boost::shared_ptr<WrappedTableWidget>(table));
						}
						// QButtonGroup类型(用于存储 互斥的 RadioButton)
						else if (typeCode == WindowCommandType::BeginButtonGroup)
						{
							QString    objectName      = _array[1].toString();

							QButtonGroup* buttonGroup = widget->doBeginButtonGroup(objectName);
							call_method<void>(infoHandle.get(),
								              "addHandle",
								              objectName.toStdString(), 
								              typeCode, boost::shared_ptr<QButtonGroup>(buttonGroup));
						}

						else if (typeCode == WindowCommandType::EndButtonGroup)
						{
							widget->doEndButtonGroup();
						}

						else if (typeCode == WindowCommandType::BeginTab)
						{
							QString     objectName = _array[1].toString();
							QTabWidget* tabWidget  = widget->beginTab(objectName);
							call_method<void>(infoHandle.get(),
								"addHandle",
								objectName.toStdString(),
								typeCode, boost::shared_ptr<QTabWidget>(tabWidget));
						}

						else if (typeCode == WindowCommandType::EndTab)
						{
							widget->endTab();
						}

						else if (typeCode == WindowCommandType::BeginSubTab)
						{
							QString     tabName  = _array[1].toString();
							QString     tabTitle = _array[2].toString();
							QWidget*	tabSubWidget = widget->beginSubTab(tabName, tabTitle);
							call_method<void>(infoHandle.get(),
											 "addHandle",
											  tabName.toStdString(),
											  typeCode, boost::shared_ptr<QWidget>(tabSubWidget));
						}

						else if (typeCode == WindowCommandType::EndSubTab)
						{
							widget->endSubTab();
						}
						#pragma endregion

						#pragma region Layout
						/******* Layout 类型 *******/

						//QHBoxLayout类型
						else if (typeCode == WindowCommandType::HLayout)
							widget->doHorizontalLayout();

						//QVHBoxLayout类型
						else if (typeCode == WindowCommandType::VLayout)
							widget->doVerticalLayout();

						//执行EndLayout
						else if (typeCode == WindowCommandType::EndLayout)
							widget->endLayout();

						//QSpacer类型
						else if (typeCode == WindowCommandType::Spacer)
						{
							int spacing = _array[1].toInt();
							widget->doSpacer(spacing);
						}	
						#pragma endregion
					}
				}
			}
		}
		QObject::connect(widget, &WrappedWidget::signal_ButtonClickEvent, [=](const QString &objectName) {
			py_try_begin_safe
			{
				boost::python::list * retList = new boost::python::list;
				m_PFN_SetCurrentUUID(widget->getUUID().toStdString());
				m_PFN_InvokeButtonClickShot(objectName.toStdString());
			}
			py_try_end_safe;
			});

		QObject::connect(widget, &WrappedWidget::signal_EditFinished, [=](const QString& objectName) {
			py_try_begin_safe
			{
				m_PFN_SetCurrentUUID(widget->getUUID().toStdString());
				m_PFN_InvokeEditFinishedShot(objectName.toStdString());
			}
			py_try_end_safe;
			});

		QObject::connect(widget, &WrappedWidget::signal_CheckBoxStageChanged, [=](const QString& objectName) {
			py_try_begin_safe
			{
				m_PFN_SetCurrentUUID(widget->getUUID().toStdString());
				m_PFN_InvokeCheckStateChangedShot(objectName.toStdString());
			}
			py_try_end_safe; });

		QObject::connect(widget, &WrappedWidget::signal_TableSelectedIndexChanged, [=](const QString& objectName,int index) {
			py_try_begin_safe
			{
				m_PFN_SetCurrentUUID(widget->getUUID().toStdString());
				m_PFN_InvokeTableSelectedIndexShot(objectName.toStdString(),index);
			}
			py_try_end_safe; 
		});

		QObject::connect(widget, &WrappedWidget::signal_SpinBoxValueChanged, [=](const QString& objectName) {
			py_try_begin_safe
			{
				m_PFN_SetCurrentUUID(widget->getUUID().toStdString());
				m_PFN_InvokeSpinBoxValueChangedShot(objectName.toStdString());
			}
			py_try_end_safe;
			});

		QObject::connect(widget, &WrappedWidget::signal_ButtonGroupToggled, [=](const QString& objectName,int index,bool value) {
			py_try_begin_safe
			{
				m_PFN_SetCurrentUUID(widget->getUUID().toStdString());
				m_PFN_InvokeButtonGroupToggledShot(objectName.toStdString(), index);
			}
			py_try_end_safe;
			});
		//初始化完毕后，调用OnStart方法
		call_method<void>(infoHandle.get(), "addWidgetHandle",boost::shared_ptr<QWidget>(widget));

		//初始化完毕后，调用OnStart方法
		call_method<void>(classHandle.get(), "OnStart");

		//绑定Close事件，并在Close事件中调用OnClose;
		connect(widget, &WrappedWidget::signal_close, [=]() {
			py_try_begin_safe
			{
				call_method<void>(classHandle.get(), "OnClose");
				widget->close();
			}
			py_try_end_safe;
			});
	}
	py_try_end_safe;
	if (!isDialog)
		m_threadState = PyEval_SaveThread();
	return widget;
}

void PythonScriptSystem::doScanPythonFiles(const QString& serachPath)
{
	QDir* dir = new QDir(serachPath);
	if (!dir->exists())
		return;

	QStringList filter;
	filter << "*.py";

	QList<QFileInfo>* dirInfoList = new QList<QFileInfo>(dir->entryInfoList(QDir::Dirs));
	QList<QFileInfo>* fomatInfoList = new QList<QFileInfo>(dir->entryInfoList(filter));

	for (int i = 0; i < dirInfoList->count(); i++) {
		if (dirInfoList->at(i).fileName() == "." || dirInfoList->at(i).fileName() == "..")
			continue;
		QString dirTmp = dirInfoList->at(i).filePath();
		doScanPythonFiles(dirTmp);
	}
	for (int i = 0; i < fomatInfoList->count(); i++) {
		auto str = fomatInfoList->at(i).filePath();

		bool success = false;
		QString className = checkPythonFileClass(str, success);
		if (success)
		{

		}
	}
	delete dirInfoList;
	delete dir;
}

QString PythonScriptSystem::checkPythonFileClass(const QString& path, bool& success)
{
	//获取py文件的名称，py文件内必须要有一个 与 文件名 相同的类
	QString className = getFileNamePrefix(path);

	//临时字典
	dict moduleDict = boost::python::dict();

	//设置当前窗口类名，因为调用后会 记录 添加了@GUI.Slot的槽函数方法
	m_PFN_SetCurrentWidgetClassName(stdstr(className));
	
	//执行对应的脚本文件
	exec_file(path.toStdString().c_str(), moduleDict, moduleDict);

	//flag ：代表包含与文件名相同的类
	exec("flag = True", moduleDict, moduleDict);

	//inst ：代表一个类className 的对象
	exec("inst = None", moduleDict, moduleDict);

	//执行py语句，初始化一个类的对象，如果抛出异常则说明，不存在与文件名相同的类，或者__init__构造函数有非默认参数
	exec(QString("try:inst= %1()\nexcept:flag = False").arg(className).toStdString().c_str(),moduleDict,moduleDict);

	//抽取flag的值
	bool flag = boost::python::extract<bool>(moduleDict["flag"]);
	if (!flag)
	{
		success = false;
		return QString();
	}
	
	//检查基类类型来判断py文件的功能（Menu类型，Widget类型等等..）
	exec(QString("instType = %1.__base__.__name__").arg(className).toStdString().c_str(), moduleDict, moduleDict);
	//抽取instType
	const char* instType = boost::python::extract<const char*>(moduleDict["instType"]);

	//如果是Widget类型
	if (_is_class_widget_(instType))
	{
		std::string classNameStr = stdstr(className);

		//写入 key-value 为:类名-python 类 的Map中，以便后续构造
		m_widgetClassNameMap[className] = moduleDict[classNameStr];

		//判断Widget类型（显示在tab，对话框模式：即模态模式）
		exec("isTabWidget = inst.isTabMode()", moduleDict, moduleDict);
		exec("isDialog = inst.isDialogMode()", moduleDict, moduleDict);

		//抽取对应变量的值
		bool isTabWidget = boost::python::extract<bool>(moduleDict["isTabWidget"]);
		bool isDialog = boost::python::extract<bool>(moduleDict["isDialog"]);

		//如果是To tab的widget，添加到m_tabModeWidgetPythonFiles中，否则添加到DialogExecutor中
		if (isTabWidget)
			m_tabModeWidgetPythonFiles.push_back(path);
		else
			DialogExecutor::getInstance()->appendDialog(className.toStdString(), path.toStdString(), isDialog);
	}

	else if (_is_class_menu_(instType))
		m_menuPythonFiles.push_back(path);

	else {}
	//释放资源
	exec("del instType,flag,inst ", moduleDict, moduleDict);

	success = true;
	m_PFN_SetCurrentWidgetClassName(stdstr(""));
	return instType;
}

PythonScriptSystem::~PythonScriptSystem() { instance = nullptr; }

PythonScriptSystem* PythonScriptSystem::getInstance()
{
	if (instance == nullptr)
		instance = new PythonScriptSystem;
	return instance;
}

bool PythonScriptSystem::doInitBuildIn()
{
	/********* Debug ********/
	_module_impl_(Debug);
	_bind_pfn_(Debug, injectPoolPtr);
	m_PFN_injectPoolPtr(boost::shared_ptr<ConsoleMessagePool>(Console->getPoolPtr()));

	/********* GUI ********/
	_module_impl_(GUI);
	_bind_pfn_(GUI, GetUIElementsJsonString);
	_bind_pfn_(GUI, InvokeButtonClickShot);
	_bind_pfn_(GUI, SetCurrentWidgetClassName);
	_bind_pfn_(GUI, SetCurrentUUID);
	_bind_pfn_(GUI, GetCurrentWidgetInfos);
	_bind_pfn_(GUI, InvokeEditFinishedShot);
	_bind_pfn_(GUI, InvokeCheckStateChangedShot);
	_bind_pfn_(GUI, InvokeTableSelectedIndexShot);
	_bind_pfn_(GUI, SetDialogExecutorPtr);

	m_PFN_SetDialogExecutorPtr(boost::shared_ptr<DialogExecutor>(DialogExecutor::getInstance()));
	/********* Menu ********/
	_module_impl_(MenuManager);
	_bind_pfn_(MenuManager, InsertMenuItem);
	_bind_pfn_(MenuManager, GetFunction);
	_bind_pfn_(MenuManager, ClearMenuItem);
	_bind_pfn_(MenuManager, GetMenuItemInfo);

	/********* Plt ********/
	_module_impl_(plt);
	_bind_pfn_(plt, SetPlotManagerPtr);
	m_PFN_SetPlotManagerPtr(boost::shared_ptr<PlotManager>(plt));
	return true;
}

bool PythonScriptSystem::doStartUp()
{
	Py_Initialize();
	if (!Py_IsInitialized())
		return false;
	PyEval_InitThreads();

	m_main_module = object((handle<>(boost::python::borrowed(PyImport_AddModule("__main__")))));
	m_main_namespace = m_main_module.attr("__dict__");
	PyRun_SimpleString("import sys");
	PyRun_SimpleString("import traceback");

	//添加Python的目录
	auto a = QString("sys.path.append('%1')").arg(QApplication::applicationDirPath() + "/Scripts/BuildIn");
	PyRun_SimpleString(QString("sys.path.append('%1')").arg(QApplication::applicationDirPath() + "/Scripts/BuildIn").toStdString().data());
	PyRun_SimpleString(QString("sys.path.append('%1')").arg(QApplication::applicationDirPath() + "/Scripts/Custom").toStdString().data());
	if (!doInitBuildIn())
	{
		return false;
	}
	doScanPythonFiles(QApplication::applicationDirPath() + "/Scripts/Custom");
	return true;
}

void PythonScriptSystem::doShutdown()
{

}

bool PythonScriptSystem::invokeMenuItemSlot(const QString& uuid, bool check)
{
	py_try_begin_safe
	{
		object callable = m_PFN_GetFunction(stdstr(uuid));
		callable();
	}
	py_try_end_safe
	return true;
}

QList<QString> PythonScriptSystem::getWidgetPythonFiles() const
{
	return m_tabModeWidgetPythonFiles;
}

QList<QString> PythonScriptSystem::getMenuPythonFiles() const
{
	return m_menuPythonFiles;
}

QList<MenuItemInfo> PythonScriptSystem::getMenuItemInfos()
{
	QList<MenuItemInfo> ans;
	try {
		boost::python::list menuItemInfos = extract<boost::python::list>(m_PFN_GetMenuItemInfo());
		for (int i = 0; i < len(menuItemInfos); i++)
		{
			boost::python::list menuItemInfo = extract<boost::python::list>(menuItemInfos[i]);
			std::string uuid = extract<std::string>(menuItemInfo[0]);
			boost::python::list paths = extract<boost::python::list>(menuItemInfo[1]);

			QStringList pathList;
			for (int j = 0; j < len(paths); j++)
			{
				pathList.append(QString(extract<const char*>(paths[j])));
			}
			bool checkable = extract<bool>(menuItemInfo[2]);
			int group = extract<int>(menuItemInfo[3]);
			int pos = extract<int>(menuItemInfo[4]);

			boost::python::list shortCutInfoList = extract<boost::python::list>(menuItemInfo[5]);
			bool modifierCtrl = extract<bool>(shortCutInfoList[0]);
			bool modifierShift = extract<bool>(shortCutInfoList[1]);
			char keyCode = extract<char>(shortCutInfoList[2]);

			MenuItemShortCutInfo shortCutInfo(modifierCtrl, modifierShift, keyCode);

			ans.push_back(MenuItemInfo(pathList, QString::fromStdString(uuid), checkable, shortCutInfo, group, pos));
		}
	}

	catch (...)
	{
		const QString & message = getLastErrorString();
	}
	return ans;
}

QString PythonScriptSystem::getLastErrorString() const
{
	std::string lastError;
	PyObject* type = NULL, * value = NULL, * traceback = NULL;

	PyErr_Fetch(&type, &value, &traceback);
	if (type)
	{
		lastError = lastError + "Exception Class:[" + PyExceptionClass_Name(type) + "]\n";
	}

	if (value)
	{
		PyObject* line = PyObject_Str(value);
		if (line && (PyUnicode_Check(line)))
			lastError = lastError + "Line:" + reinterpret_cast<char*>(PyUnicode_1BYTE_DATA(line)) + "\n TraceBack:\n";
	}

	if (traceback)
	{
		for (PyTracebackObject* tb = (PyTracebackObject*)traceback;
			NULL != tb;
			tb = tb->tb_next)
		{
			PyObject* line = PyUnicode_FromFormat("File \"%U\", line %d, in %U\n",
				tb->tb_frame->f_code->co_filename,
				tb->tb_lineno,
				tb->tb_frame->f_code->co_name);
			lastError = lastError + reinterpret_cast<char*>(PyUnicode_1BYTE_DATA(line)) + "\n";
		}
	}
	return lastError.c_str();
}
