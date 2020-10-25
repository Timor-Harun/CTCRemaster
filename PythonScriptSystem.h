#pragma once

#ifndef PYTHON_SCRIPT_SYSTEM_H
#define PYTHON_SCRIPT_SYSTEM_H

#include <Python.h>
#include <boost/python.hpp>
#include <frameobject.h>

#include <QObject>
#include <QApplication>
#include <QFileInfo>
#include <QDir>
#include <QMessageBox>
#include <QJsonParseError>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>
#include <qglobal.h>
#include "WrappedProgressBar.h"
#include "WrappedWidget.h"
#include "Global.h"
#include "ConsoleLogic.h"
#include "PlotManager.h"
#define BIND_PFN(className,function) m_PFN_##function = object((handle<>(borrowed(PyRun_String(#className"."#function, Py_eval_input, m_main_namespace.ptr(), m_main_namespace.ptr())))));
#define _bind_pfn_(className,function) m_PFN_##function = object((handle<>(borrowed(PyRun_String(#className"."#function, Py_eval_input, dict_##className.ptr(),  dict_##className.ptr())))));

#define _module_declare_(module) 	\
                boost::python::object module_##module;  \
                boost::python::object dict_##module;\
                public:  boost::python::object get##module##Dict() {return this->dict_##module ;}

#define _module_impl_(module) 	\
                module_##module = boost::python::import(#module);  \
                dict_##module = module_##module.attr("__dict__");

#define py_try_begin try
#define py_try_end   catch(boost::python::error_already_set &e) {const QString &str = PythonScriptSystem::getInstance()->getLastErrorString(); QMessageBox::critical(NULL,"Python Fatal Error",str);}

#define py_try_begin_safe PyGILState_STATE lock = PyGILState_Ensure();bool expcetionFlag = false;QString errorStr;try
#define py_try_end_safe   catch(boost::python::error_already_set &e) { errorStr = PythonScriptSystem::getInstance()->getLastErrorString(); expcetionFlag = true;} {PyGILState_Release(lock);if(expcetionFlag){QMessageBox::critical(NULL,"Python Fatal Error",errorStr);}}

using namespace std;
using namespace boost::python;
using namespace TimorHarun::Utility;

class PythonScriptSystem:public QObject
{
	Q_OBJECT

private:
	/*******Main Object*******/
	object m_main_module;
	object m_main_namespace;

	/*******GUI PFN*******/
	object m_PFN_GetUIElementsJsonString;
	object m_PFN_InvokeButtonClickShot;
	object m_PFN_SetCurrentWidgetClassName;
	object m_PFN_SetCurrentUUID;
	object m_PFN_GetCurrentWidgetInfos;
	object m_PFN_InvokeEditFinishedShot;
	object m_PFN_InvokeCheckStateChangedShot;
	object m_PFN_InvokeTableSelectedIndexShot;

	/*******Menu PFN*******/
	object m_PFN_InsertMenuItem;
	object m_PFN_ClearMenuItem;
	object m_PFN_GetFunction;
	object m_PFN_GetMenuItemInfo;

	/*******Plt PFN*******/
	object m_PFN_SetPlotManagerPtr;
	/***********Debug 部分***********/

	//可调用的方法injectPoolPtr，注入ConsoleMessagePool的指针
	object m_PFN_injectPoolPtr;

public:
	PyThreadState* m_threadState = nullptr;
private:
	QMap<QString, object> m_widgetClassNameMap;

	/*******Build-In*******/
	_module_declare_(MenuManager);
	_module_declare_(GUI);
	_module_declare_(Debug);
	_module_declare_(plt);

	/*******File List*******/
	QList<QString> m_widgetPythonFiles;
	QList<QString> m_menuPythonFiles;

	/*******Private Method*******/

	/*******  扫描 指定相对路径下 的Py文件 *******/
	void    doScanPythonFiles(const QString& serachPath);

	/*******  初始化 内建 模块 *******/
	bool    doInitBuildIn();

	/*******  检查 Py文件中定义的类别的基类名称 *******/
	QString checkPythonFileClass(const QString& path, bool& success);

public:
	/*******  获取 窗口信息, 解析 并创建窗口，返回窗口的 Widget *******/
	WrappedWidget* doGetWidgetCreation(const QString &fileName);

	~PythonScriptSystem();
	static PythonScriptSystem* getInstance();

	bool doStartUp();

	/*******  关闭子系统 *******/
	void doShutdown();

	/*******  根据菜单条目的UUID 调用槽函数 *******/
	bool invokeMenuItemSlot(const QString& uuid, bool check);

	/*******  获取Widget窗口Py文件 列表 *******/
	QList<QString>      getWidgetPythonFiles() const;

	/*******  获取Menu的Py文件 列表 *******/
	QList<QString>      getMenuPythonFiles() const;

	/*******  获取所有菜单条目的信息  *******/
	QList<MenuItemInfo> getMenuItemInfos();

	/*******  获取上一条Python 运行错误的信息 *******/
	QString             getLastErrorString() const;
private:
	PythonScriptSystem() = default;
	static PythonScriptSystem* instance;
};

namespace TimorHarun
{
	namespace Scripting
	{
		//class PythonScriptSystem;
	}
}
#endif