#pragma once
#include "Utility.h"
#include <QMenu>
//get the basename of one file
#define file_BaseName(path) QFileInfo(path).baseName()

//get the called info
#define called_info QString("File:")+file_BaseName(__FILE__)+" "+__FUNCTION__+"() at Line:"+QString::number(__LINE__)
enum  MessageType {
	Info = 0,
	Warning = 1,
	Error = 2
};

//Message of Console
typedef struct Message
{
	//called Info can be presented as : function_something(...) in Line xx
	QString         calledInfo;
	//main content of message
	QString         message;
	//type of message (Info,Warning,Error)
	MessageType     type;

	Message() {}
	Message(QString     _calledInfo,
			QString     _message,
			MessageType _type) :
			calledInfo(_calledInfo),
			message(_message),
			type(_type)
	{}

	bool serach(const QString &content)
	{
		int calledInfoPos = this->calledInfo.indexOf(content);
		int messagePos = this->message.indexOf(content);

		bool calledInfoMatched = false;
		bool messageMatched = false;

		int contentSize = content.size();
		if (calledInfoPos != -1)
		{
			calledInfoMatched = true;
		}
		if (messagePos != -1)
		{
			messageMatched = true;
		}
		return calledInfoMatched || messageMatched;
	}

}Message;

struct MenuItemShortCutInfo
{
	bool useCtrl;
	bool useShift;
	char keyCode;

	MenuItemShortCutInfo(bool _useCtrl, 
		                 bool _useShift,
		                 char _keyCode) :
						 useCtrl(_useCtrl),
						 useShift(_useShift),
						 keyCode(_keyCode) {};
};
struct MenuItemInfo
{
	QStringList path;
	QString uuid;
	bool checkable;
	MenuItemShortCutInfo shortCutInfo;
	int group;
	int pos;

	MenuItemInfo(const QStringList &_path, 
		         const QString &_uuid,
		         bool _checkable,
				 MenuItemShortCutInfo _shortCutInfo,
				 int _group,
				 int _pos) :
		         path(_path),
		         uuid(_uuid),
		         checkable(_checkable),
		         shortCutInfo(_shortCutInfo),
	             group(_group),
	             pos(_pos) {};
};
class MenuItemNode
{
public:
	MenuItemNode() :action(nullptr), menu(nullptr) {};
	MenuItemNode(const QString& actionName, bool checkable) :action(new QAction(actionName)), isRoot(false) { action->setCheckable(checkable); }
	MenuItemNode(const QString& menuName) :menu(new QMenu(menuName)), isRoot(true) { }

	union
	{
		QAction* action;
		QMenu* menu;
	};

	bool isRoot;
	QList<MenuItemNode*> children;

	bool containsChild(const QStringList& _val, MenuItemNode*& last, int* index) {
		if (*index == _val.size())
		{
			return true;
		}
		last = this;
		for (auto node : children)
		{
			if (!node->isRoot)
			{
				if (node->action->text() == _val[*index])
				{
					(*index)++;
					return node->containsChild(_val, last, index);
				}
			}
			else
			{
				if (node->menu->title() == _val[*index])
				{
					(*index)++;
					return node->containsChild(_val, last, index);
				}
			}
		}
		return false;
	}

	MenuItemNode* addChild(const QString& actionName, bool checkable)
	{
		auto item = new MenuItemNode(actionName, checkable);
		children.push_back(item);
		return item;
	}
	MenuItemNode* addChild(const QString& actionName)
	{
		auto item = new MenuItemNode(actionName);
		children.push_back(item);
		return item;
	}
};