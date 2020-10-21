#pragma once

#include <QTabWidget>
#include <QAction>
#include <QEvent>
#include <QTabBar>
#include <QMenu>
#include <QMimeData>
#include <QDrag>
#include "DockTabBar.h"

class DockTabWidget:public QTabWidget
{
	Q_OBJECT
public:
	DockTabWidget(QWidget* parent = nullptr) :QTabWidget(parent)
	{
		DockTabBar* tabBar = new DockTabBar(this);
		m_pDragWidget = NULL;
		setTabBar(tabBar);
		setMovable(true);
		setTabShape(QTabWidget::Triangular);
		setMouseTracking(true);
	}
	QString m_dragTabLabel;
	QWidget* m_pDragWidget;
	int m_dragIndex;
private slots:
	void startDrag(int index)
	{
		m_dragTabLabel = this->tabText(index);
		m_pDragWidget = this->widget(index);
		m_dragIndex = index;
	}
	void endDrag()
	{
		DockTabWidget* pWidget = new DockTabWidget(NULL);
		if (m_pDragWidget)
		{
			//新建一个独立的窗口  
			removeTab(m_dragIndex);
			pWidget->addTab(m_pDragWidget, m_dragTabLabel);
			pWidget->show();
		}
	}
protected:
	void contextMenuEvent(QContextMenuEvent* event)
	{

	}
};

