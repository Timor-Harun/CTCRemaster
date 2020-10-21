#include "ConsoleListWidget.h"

ConsoleListWidget::ConsoleListWidget(QWidget* parent) :
	displayCount(0),
	listWidget(new QListWidget),
	scrollBar(new QScrollBar)
{
	//创建水平布局，并设置为 当前Widget的布局
	QHBoxLayout* layout = new QHBoxLayout;
	setLayout(layout);

	//对于listwidget，隐藏其自带的 滚动条，并添加到布局中
	listWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	layout->addWidget(listWidget);

	//对于滚动条，设置其单步距离为1，并连接其 valueChanged 信号
	scrollBar->setSingleStep(1);
	scrollBar->setValue(0);
	layout->addWidget(scrollBar);
	layout->setContentsMargins(0, 0, 0, 0);
	layout->setSpacing(0);
	connect(scrollBar, &QScrollBar::valueChanged, this, &ConsoleListWidget::refreshAfterSliderValueChanged);

	//设置选取模式
	listWidget->setSelectionMode(QListWidget::SelectionMode::ExtendedSelection);
	//设置qss
	listWidget->setStyleSheet("QListWidget::item:selected"
							 "{background: qlineargradient(x1 : 0, y1 : 0,"
							 "x2 : 0, y2 : 1,"
							 "stop : 0 #6ea1f1, stop: 1 #567dbc);} ");


}

ConsoleListWidget::~ConsoleListWidget()
{
	delete listWidget;
	delete scrollBar;

	listWidget = NULL;
	scrollBar = NULL;
}

//添加一个Item
void ConsoleListWidget::addItemInternal(int relativePos, int msgIndex)
{
	ConsoleMessageItemWidget* widget = NULL;
	//找到对应显示位置的ItemWidget然后更新Message
	if (itemWidgetPtrMap.find(relativePos) != itemWidgetPtrMap.end())
	{
		listWidget->item(relativePos)->setHidden(false);
		widget = itemWidgetPtrMap[relativePos];
		//
		widget->setMessage(msgPtr->at(msgIndex));
	}
	//如果没找到对应位置的ItemWidget,那么就new一个
	else
	{
		ConsoleMessageItemWidget* widget = new ConsoleMessageItemWidget(listWidget, msgPtr->at(msgIndex));
		QListWidgetItem* item = new QListWidgetItem;
		item->setSizeHint(QSize(item->sizeHint().width(), 60));
		widget->setAttribute(Qt::WA_DeleteOnClose);
		listWidget->addItem(item);
		listWidget->setItemWidget(item, widget);
		itemWidgetPtrMap[relativePos] = widget;
	}
}

//头插入一个Item
void ConsoleListWidget::insertItemInternal(int msgIndex)
{
	ConsoleMessageItemWidget* widget = NULL;
	if (itemWidgetPtrMap.find(0) == itemWidgetPtrMap.end())
	{
		listWidget->item(0)->setHidden(false);
		widget = itemWidgetPtrMap[0];
		widget->setMessage(msgPtr->at(msgIndex));
	}
}

void ConsoleListWidget::wheelEvent(QWheelEvent* event)
{
	//获取滚轮的垂直方向的值
	int numDegrees = event->angleDelta().y() / 8;
	//这里取负号，目的是为了实现鼠标往下滚动时是数值增大，往上滚动时是数值减小
	int numSteps = -numDegrees / 15;

	if (event->orientation() == Qt::Vertical) {
		//index为增量后的listWidget应该显示的第一个元素的索引值
		//重新显示条目
		//用于记录Item的数量
		scrollBar->setValue(numSteps + scrollBar->value());
		refreshAfterSliderValueChanged();
	}
	//表示此处已经处理了鼠标的滚动事件，不需要传给父部件处理
	event->accept();
}

void ConsoleListWidget::resizeEvent(QResizeEvent* event)
{
	if (!this->msgPtr)
	{
		QWidget::resizeEvent(event);
		return;
	}
	else
	{
		//height 表示调整尺寸以后的窗口大小
		int height = event->size().height();
		//value 代表滚动条当前的变量大小
		int value = scrollBar->value();
		//计算 应该显示的 Item数量，60是默认的ItemWidget的高度
		displayCount = height / 60;
		//设置滚动条的宽度

		for (int i = displayCount; i < itemWidgetPtrMap.size(); i++)
		{
			listWidget->item(i)->setHidden(true);
		}

		refreshAfterResize();
		//基类的resizeEvent
		event->accept();
		QWidget::resizeEvent(event);
	}
}

void ConsoleListWidget::refreshAfterResize()
{
	//用于记录Item的数量
	int itemCount = 0;
	int startIndex = scrollBar->value();

	for (int i = startIndex; itemCount < displayCount && i < indexes.size(); i++)
	{
		addItemInternal(i - startIndex, indexes[i]);
		itemCount++;
	}
	//如果数量比displayCount小,从startIndex开始向前添加元素
	if (itemCount < displayCount)
	{
		int i = startIndex - 1;
		//从后往前扫描，如果满足条件的Item就插入到第0行，知道数量等于displayCount
		for (; i >= 0 && itemCount < displayCount; i++)
		{
			insertItemInternal(indexes[i]);
			itemCount++;
		}

		//滚动条的value设置成i
		scrollBar->setValue(i);
	}
	scrollBar->setPageStep(displayCount);
	scrollBar->setRange(0, indexes.size() - displayCount);

	if (indexes.size() <= displayCount)
	{
		layout()->removeWidget(scrollBar);
		scrollBar->hide();
	}
	else if (scrollBar->isHidden())
	{
		layout()->addWidget(scrollBar);
		scrollBar->show();
	}

}
void ConsoleListWidget::refreshAfterSliderValueChanged()
{
	//做listWidget的刷新操作，首先清除当前listWidget的所有Item
	//用于记录Item的数量
	int itemCount = 0;
	int startIndex = scrollBar->value();

	for (int i = startIndex; itemCount < displayCount && i < indexes.size(); i++)
	{
		addItemInternal(i - startIndex, indexes[i]);
		itemCount++;
	}
}

void ConsoleListWidget::refreshAfterIndexesChanged()
{
	listWidget->clear();
	itemWidgetPtrMap.clear();

	int itemCount = 0;
	scrollBar->setValue(0);
	scrollBar->setRange(0, indexes.size() - displayCount);
	for (int i = 0; itemCount < displayCount && i < indexes.size(); i++)
	{
		addItemInternal(i, indexes[i]);
		itemCount++;
	}

	if (indexes.size() <= displayCount)
	{
		layout()->removeWidget(scrollBar);
		scrollBar->hide();
	}
	else if (scrollBar->isHidden())
	{
		layout()->addWidget(scrollBar);
		scrollBar->show();
	}

}

void ConsoleListWidget::refreshAfterPrint(int index)
{
	//如果设置了自动滚动才需要做些什么
	indexes.push_back(index);
	scrollBar->setRange(0, indexes.size() - displayCount);
	if (indexes.size() > displayCount)
	{
		layout()->addWidget(scrollBar);
		scrollBar->show();
	}
	if (autoRoll)
	{
		//如果需要输出的数量 比displayCount 小，那么直接追加到末尾
		if (indexes.size() < displayCount)
		{
			addItemInternal(indexes.size() - 1, indexes.back());
		}
		//否则整体要往后推一个元素
		else
		{
			int startIndex = scrollBar->value() + 1;
			int itemCount = 0;
			for (int i = startIndex; itemCount < displayCount && i < indexes.size(); i++)
			{
				addItemInternal(i - startIndex, indexes[i]);
				itemCount++;
			}
			scrollBar->setValue(startIndex);
		}
	}
	else
	{
		/*Nothing to do*/
	}
}
void ConsoleListWidget::setAutoRoll(bool value)
{
	this->autoRoll = value;
}

void ConsoleListWidget::setMessagePtr(ItemVector* _msgPtr)
{
	this->msgPtr = _msgPtr;
}

void ConsoleListWidget::clear()
{
	this->msgPtr = NULL;
	this->listWidget->clear();
}

void ConsoleListWidget::setValidIndexes(const QVector<int>& _indexes)
{
	this->indexes = _indexes;
}
