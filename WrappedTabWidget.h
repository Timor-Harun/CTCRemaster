#pragma once

#include <QTabWidget>
#include "CustomTabStyle.h"

class WrappedTabWidget:public QTabWidget
{
	Q_OBJECT
public:
	WrappedTabWidget(QWidget* parent = nullptr) :QTabWidget(parent)
	{
		tabBar()->setStyle(new CustomTabStyle);
		setTabPosition(QTabWidget::West);
	}
	~WrappedTabWidget()
	{

	}
};

