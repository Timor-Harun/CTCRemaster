#pragma once
#ifndef CONSOLE_LIST_WIDGET_H
#define CONSOLE_LIST_WIDGET_H

#include <QWidget>
#include <QString>
#include <QVector>
#include <QWheelEvent>
#include <QListWidget>
#include <QScrollBar>
#include <QDateTime>
#include <QHBoxLayout>
#include <unordered_map>

#include "ConsoleMessageItemWidget.h"

//实现控制台 动态加载Item的ListWidget
class ConsoleListWidget :public QWidget
{
	using ItemVector = QVector<Message>;

	Q_OBJECT
private:
	//list 控件应该显示的条目个数
	int          displayCount;
	//动态显示和隐藏的 滚动条
	QScrollBar* scrollBar;
	//用于动态显示的 列表控件
	QListWidget* listWidget;
	//存储了消息的列表的指针
	ItemVector*  msgPtr;
	//存储了要显示的消息的索引数组
	QVector<int> indexes;
	//存储了ItemWidget的指针
	std::unordered_map<int, ConsoleMessageItemWidget*> itemWidgetPtrMap;
	//是否自动滚动到底部
	bool         autoRoll;

	//添加一个Item
	void         addItemInternal(int relativePos, int msgIndex);
	//头插入一个Item
	void         insertItemInternal(int msgIndex);
protected:
	//重载的鼠标滚轮事件
	void		 wheelEvent(QWheelEvent* event);
	//重载的窗口尺寸事件
	void		 resizeEvent(QResizeEvent* event);

public slots:
	//刷新当前显示的条目
	//引发刷新事件共用四种情况：
	//窗口大小Resize，要动态调整显示的个数
	//滚动条value改变，要更新当前显示的Item
	//需要显示的索引改变
	//有新的消息被Print，如果设置了自动滚动，要滚动到最下方的元素
	void         refreshAfterResize();
	void         refreshAfterSliderValueChanged();
	void         refreshAfterIndexesChanged();
	void         refreshAfterPrint(int index);
public:
	//set方法，是否自动滚动，消息指针，有效消息索引数组
	void  setAutoRoll(bool value);
	void  setMessagePtr(ItemVector* _msgPtr);
	void  setValidIndexes(const QVector<int>& _indexes);
	void  clear();
	//构造函数
	explicit	 ConsoleListWidget(QWidget* parent = 0);
	//析构函数
	~ConsoleListWidget();
};
#endif