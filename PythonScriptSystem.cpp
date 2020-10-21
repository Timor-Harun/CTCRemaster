#include "PythonScriptSystem.h"

PythonScriptSystem* PythonScriptSystem::instance = nullptr;

WrappedWidget* PythonScriptSystem::doGetWidgetCreation(const QString &fileName)
{
	WrappedWidget* widget = NULL;
	for (int i = 0; i < m_widgetPythonFiles.size(); i++)
	{
		if (m_widgetPythonFiles[i].contains(fileName))
		{
			if(m_threadState)
				PyEval_RestoreThread(m_threadState);
			py_try_begin_safe
			{
				m_PFN_SetCurrentWidgetClassName(stdstr(fileName));
				handle<> classHandle = extract<handle<>>(m_widgetClassNameMap[fileName]());
				call_method<void>(classHandle.get(), "OnGUI");
				std::string _uuid = call_method<std::string>(classHandle.get(), "getUUID");
				object jsonret = m_PFN_GetUIElementsJsonString();
				std::string _json = extract<std::string>(jsonret);

				widget = new WrappedWidget;
				widget->setWindowTitle(fileName);
				widget->setUUID(QString::fromStdString(_uuid));
				handle<> infoHandle = extract<handle<>>(m_PFN_GetCurrentWidgetInfos());

				QJsonParseError jsonError;
				QByteArray byte(_json.c_str());
				QJsonDocument doucment = QJsonDocument::fromJson(byte, &jsonError);  // 转化为 JSON 文档
				if (!doucment.isNull() && (jsonError.error == QJsonParseError::NoError)) {  // 解析未发生错误
					if (doucment.isArray())
					{
						QJsonArray array = doucment.array();
						for (int i = 0; i < array.size(); i++)
						{
							if (array[i].isArray())
							{
								QJsonArray _array = array[i].toArray();
								int typeCode = _array[0].toInt();
								if (typeCode == 0)
								{
									QString objectName = _array[1].toString();
									QString objectText = _array[2].toString();
									QPushButton* btn = widget->doButton(objectName, objectText);
									call_method<void>(infoHandle.get(), "addHandle", objectName.toStdString(), typeCode, boost::shared_ptr<QPushButton>(btn));
								}
								else if (typeCode == 1)
								{
									QString text = _array[1].toString();
									QLabel* label = widget->doLabel(text);
								}
								else if (typeCode == 2)
								{
									QString objectName = _array[1].toString();
									QLineEdit* edit = widget->doLineEdit(objectName);
									call_method<void>(infoHandle.get(), "addHandle", objectName.toStdString(), typeCode, boost::shared_ptr<QLineEdit>(edit));
								}
								else if (typeCode == 3)
								{
									int spacing = _array[1].toInt();
									widget->doSpacer(spacing);
								}
								else if (typeCode == 4)
								{
									widget->doHorizontalLayout();
								}
								else if (typeCode == 5)
								{
									widget->doVerticalLayout();
								}
								else if (typeCode == 6)
								{
									widget->endLayout();
								}
								else if (typeCode == 7)
								{
									QString objectName = _array[1].toString();
									QString objectText = _array[2].toString();
									bool checked = _array[3].toBool();
									QCheckBox* checkBox = widget->doCheckBox(objectName, objectText, checked);
									call_method<void>(infoHandle.get(), "addHandle", objectName.toStdString(), typeCode, boost::shared_ptr<QCheckBox>(checkBox));
								}
								else if (typeCode == 8)
								{
									QString objectName = _array[1].toString();
									int value = _array[2].toInt();
									int min = _array[3].toInt();
									int max = _array[4].toInt();
									WrappedProgressBar* progressBar = widget->doProgressBar(objectName, value, min, max);
									connect(progressBar, &WrappedProgressBar::updateValue_signal, progressBar, &WrappedProgressBar::setValue);
									call_method<void>(infoHandle.get(), "addHandle", objectName.toStdString(), typeCode, boost::shared_ptr<WrappedProgressBar>(progressBar));
								}
								else if (typeCode == 9)
								{
									QString groupName = _array[1].toString();
									widget->doGroupBox(groupName);
								}
								else if (typeCode == 10)
								{
									widget->endGroupBox();
								}
								else if (typeCode == 11)
								{
									QString objectName = _array[1].toString();
									IPAddress * ipAddress = widget->doIPAddress(objectName);
									call_method<void>(infoHandle.get(), "addHandle", objectName.toStdString(), typeCode, boost::shared_ptr<IPAddress>(ipAddress));
								}
								else if (typeCode == 12)
								{
									QString objectName = _array[1].toString();
									QStringList items;
									QJsonArray _jsonArray = _array[2].toArray();
									for (int i = 0; i < _jsonArray.size(); i++)
									{
										items << _jsonArray[i].toString();
									}
									QComboBox* comboBox = widget->doComboBox(objectName, items);
									call_method<void>(infoHandle.get(), "addHandle", objectName.toStdString(), typeCode, boost::shared_ptr<QComboBox>(comboBox));
								}
								else if (typeCode == 13)
								{
									 QString objectName = _array[1].toString();
									 QStringList headers;
									 QJsonArray _jsonArray = _array[2].toArray();
									 for (int i = 0; i < _jsonArray.size(); i++)
									 {
										 headers << _jsonArray[i].toString();
									 }
									 WrappedTableWidget* table = widget->doTable(objectName, headers);
									 table->appendRow({ "1","2","3","4","5","6123" });
									 call_method<void>(infoHandle.get(), "addHandle", objectName.toStdString(), typeCode, boost::shared_ptr<WrappedTableWidget>(table));
								}
							}
						}
					}
				}
				call_method<void>(classHandle.get(), "OnStart");
				QObject::connect(widget, &WrappedWidget::signal_ButtonClickEvent, [=](QString objectName) {
					py_try_begin_safe
					{
						boost::python::list * retList = new boost::python::list;
						m_PFN_SetCurrentUUID(widget->getUUID().toStdString());
						m_PFN_InvokeButtonClickShot(objectName.toStdString());
					}
					py_try_end_safe;
					});


				QObject::connect(widget, &WrappedWidget::signal_EditFinished, [=](QString objectName) {
					py_try_begin_safe
					{
						m_PFN_SetCurrentUUID(widget->getUUID().toStdString());
						m_PFN_InvokeEditFinishedShot(objectName.toStdString());
					}
					py_try_end_safe;
					});

				QObject::connect(widget, &WrappedWidget::signal_CheckBoxStageChanged, [=](QString objectName) {
					py_try_begin_safe
					{
						m_PFN_SetCurrentUUID(widget->getUUID().toStdString());
						m_PFN_InvokeCheckStateChangedShot(objectName.toStdString());
					}
					py_try_end_safe; });
			}
			py_try_end_safe;
			m_threadState = PyEval_SaveThread();
			break;
		}
	}
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
	QString className = getFileNamePrefix(path);
	dict moduleDict = boost::python::dict();
	m_PFN_SetCurrentWidgetClassName(stdstr(className));
	exec_file(path.toStdString().c_str(), moduleDict, moduleDict);
	exec("flag = True", moduleDict, moduleDict);
	exec("inst = None", moduleDict, moduleDict);

	exec(QString("try:inst= %1()\nexcept:flag = False").arg(className).toStdString().c_str());

	bool flag = boost::python::extract<bool>(moduleDict["flag"]);
	if (!flag)
	{
		success = false;
		return QString();
	}
	exec(QString("instType = %1.__base__.__name__").arg(className).toStdString().c_str(), moduleDict, moduleDict);
	const char* instType = boost::python::extract<const char*>(moduleDict["instType"]);
	if (::strcmp(instType ,"Widget") == 0)
	{
		m_widgetPythonFiles.push_back(path);
		auto str = stdstr(className);
		m_widgetClassNameMap[className] = moduleDict[str];
	}

	if (::strcmp(instType, "Widget") == 0)
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
	/********* GUI ********/
	_module_impl_(GUI);
	_bind_pfn_(GUI, GetUIElementsJsonString);
	_bind_pfn_(GUI, InvokeButtonClickShot);
	_bind_pfn_(GUI, SetCurrentWidgetClassName);
	_bind_pfn_(GUI, SetCurrentUUID);
	_bind_pfn_(GUI, GetCurrentWidgetInfos);
	_bind_pfn_(GUI, InvokeEditFinishedShot);
	_bind_pfn_(GUI, InvokeCheckStateChangedShot);

	/********* Debug ********/
	_module_impl_(MenuManager);
	_bind_pfn_(MenuManager, InsertMenuItem);
	_bind_pfn_(MenuManager, GetFunction);
	_bind_pfn_(MenuManager, ClearMenuItem);
	_bind_pfn_(MenuManager, GetMenuItemInfo);

	/********* Debug ********/
	_module_impl_(Debug);
	_bind_pfn_(Debug, injectPoolPtr);
	m_PFN_injectPoolPtr(boost::shared_ptr<ConsoleMessagePool>(Console->getPoolPtr()));
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
	return m_widgetPythonFiles;
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

			ans.push_back(MenuItemInfo(pathList, uuid.c_str(), checkable, shortCutInfo, group, pos));
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
