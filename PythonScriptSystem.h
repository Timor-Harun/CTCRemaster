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
	/***********Debug ����***********/

	//�ɵ��õķ���injectPoolPtr��ע��ConsoleMessagePool��ָ��
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

	/*******  ɨ�� ָ�����·���� ��Py�ļ� *******/
	void    doScanPythonFiles(const QString& serachPath);

	/*******  ��ʼ�� �ڽ� ģ�� *******/
	bool    doInitBuildIn();

	/*******  ��� Py�ļ��ж�������Ļ������� *******/
	QString checkPythonFileClass(const QString& path, bool& success);

public:
	/*******  ��ȡ ������Ϣ, ���� ���������ڣ����ش��ڵ� Widget *******/
	WrappedWidget* doGetWidgetCreation(const QString &fileName);

	~PythonScriptSystem();
	static PythonScriptSystem* getInstance();

	bool doStartUp();

	/*******  �ر���ϵͳ *******/
	void doShutdown();

	/*******  ���ݲ˵���Ŀ��UUID ���òۺ��� *******/
	bool invokeMenuItemSlot(const QString& uuid, bool check);

	/*******  ��ȡWidget����Py�ļ� �б� *******/
	QList<QString>      getWidgetPythonFiles() const;

	/*******  ��ȡMenu��Py�ļ� �б� *******/
	QList<QString>      getMenuPythonFiles() const;

	/*******  ��ȡ���в˵���Ŀ����Ϣ  *******/
	QList<MenuItemInfo> getMenuItemInfos();

	/*******  ��ȡ��һ��Python ���д������Ϣ *******/
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