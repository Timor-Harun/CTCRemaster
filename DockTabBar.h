#pragma once

#include <QTabBar>
#include <Qt>
#include <QMouseEvent>
#include <QMenu>

class DockTabBar:public QTabBar
{
	Q_OBJECT
public:
	QMenu* m_TabBarMenu;
	DockTabBar(QWidget* parent = nullptr) :QTabBar(parent)
	{
		m_TabBarMenu = new QMenu;
		setMouseTracking(true);
	}

protected:
	void mousePressEvent(QMouseEvent* event)
	{
		QTabBar::mousePressEvent(event);
		return;
		if (event->button() & Qt::LeftButton)
		{
			m_isDrag = true;
			m_mousePressPoint = event->pos();
		}
		else if (event->button() & Qt::RightButton)
		{
			m_TabBarMenu->clear();
			int index = this->tabAt(event->pos());
			setCurrentIndex(index);
			m_TabBarMenu->addAction(new QAction(tabText(index)));
			m_TabBarMenu->exec(QCursor::pos());
		}
	}

	void mouseMoveEvent(QMouseEvent* event)
	{
		int index = this->currentIndex();

		if (m_isDrag)
		{
			QPoint Point = event->pos();
			//拖动的垂直距离大于Bar的高度的话就新建一个窗口 
			if (qAbs(m_mousePressPoint.y() - Point.y()) > this->height())
			{
				emit startDragTab(index);
			}
		}
		QTabBar::mouseMoveEvent(event);
	}

	void mouseReleaseEvent(QMouseEvent* event)
	{
		if (event ->button()& Qt::LeftButton)
		{
			m_mouseReleasePoint = event->pos();
			if (qAbs(m_mousePressPoint.y() - m_mouseReleasePoint.y()) > this->height())
			{
				emit endDragTab();
			}
		}
		QTabBar::mouseReleaseEvent(event);
	}

Q_SIGNALS:
	void startDragTab(int index);
	void endDragTab();
private:
	bool      m_isDrag;
	QPoint    m_mousePressPoint;
	QPoint    m_mouseReleasePoint;
};

