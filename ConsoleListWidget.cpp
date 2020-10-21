#include "ConsoleListWidget.h"

ConsoleListWidget::ConsoleListWidget(QWidget* parent) :
	displayCount(0),
	listWidget(new QListWidget),
	scrollBar(new QScrollBar)
{
	//����ˮƽ���֣�������Ϊ ��ǰWidget�Ĳ���
	QHBoxLayout* layout = new QHBoxLayout;
	setLayout(layout);

	//����listwidget���������Դ��� ������������ӵ�������
	listWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	layout->addWidget(listWidget);

	//���ڹ������������䵥������Ϊ1���������� valueChanged �ź�
	scrollBar->setSingleStep(1);
	scrollBar->setValue(0);
	layout->addWidget(scrollBar);
	layout->setContentsMargins(0, 0, 0, 0);
	layout->setSpacing(0);
	connect(scrollBar, &QScrollBar::valueChanged, this, &ConsoleListWidget::refreshAfterSliderValueChanged);

	//����ѡȡģʽ
	listWidget->setSelectionMode(QListWidget::SelectionMode::ExtendedSelection);
	//����qss
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

//���һ��Item
void ConsoleListWidget::addItemInternal(int relativePos, int msgIndex)
{
	ConsoleMessageItemWidget* widget = NULL;
	//�ҵ���Ӧ��ʾλ�õ�ItemWidgetȻ�����Message
	if (itemWidgetPtrMap.find(relativePos) != itemWidgetPtrMap.end())
	{
		listWidget->item(relativePos)->setHidden(false);
		widget = itemWidgetPtrMap[relativePos];
		//
		widget->setMessage(msgPtr->at(msgIndex));
	}
	//���û�ҵ���Ӧλ�õ�ItemWidget,��ô��newһ��
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

//ͷ����һ��Item
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
	//��ȡ���ֵĴ�ֱ�����ֵ
	int numDegrees = event->angleDelta().y() / 8;
	//����ȡ���ţ�Ŀ����Ϊ��ʵ��������¹���ʱ����ֵ�������Ϲ���ʱ����ֵ��С
	int numSteps = -numDegrees / 15;

	if (event->orientation() == Qt::Vertical) {
		//indexΪ�������listWidgetӦ����ʾ�ĵ�һ��Ԫ�ص�����ֵ
		//������ʾ��Ŀ
		//���ڼ�¼Item������
		scrollBar->setValue(numSteps + scrollBar->value());
		refreshAfterSliderValueChanged();
	}
	//��ʾ�˴��Ѿ����������Ĺ����¼�������Ҫ��������������
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
		//height ��ʾ�����ߴ��Ժ�Ĵ��ڴ�С
		int height = event->size().height();
		//value �����������ǰ�ı�����С
		int value = scrollBar->value();
		//���� Ӧ����ʾ�� Item������60��Ĭ�ϵ�ItemWidget�ĸ߶�
		displayCount = height / 60;
		//���ù������Ŀ��

		for (int i = displayCount; i < itemWidgetPtrMap.size(); i++)
		{
			listWidget->item(i)->setHidden(true);
		}

		refreshAfterResize();
		//�����resizeEvent
		event->accept();
		QWidget::resizeEvent(event);
	}
}

void ConsoleListWidget::refreshAfterResize()
{
	//���ڼ�¼Item������
	int itemCount = 0;
	int startIndex = scrollBar->value();

	for (int i = startIndex; itemCount < displayCount && i < indexes.size(); i++)
	{
		addItemInternal(i - startIndex, indexes[i]);
		itemCount++;
	}
	//���������displayCountС,��startIndex��ʼ��ǰ���Ԫ��
	if (itemCount < displayCount)
	{
		int i = startIndex - 1;
		//�Ӻ���ǰɨ�裬�������������Item�Ͳ��뵽��0�У�֪����������displayCount
		for (; i >= 0 && itemCount < displayCount; i++)
		{
			insertItemInternal(indexes[i]);
			itemCount++;
		}

		//��������value���ó�i
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
	//��listWidget��ˢ�²��������������ǰlistWidget������Item
	//���ڼ�¼Item������
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
	//����������Զ���������Ҫ��Щʲô
	indexes.push_back(index);
	scrollBar->setRange(0, indexes.size() - displayCount);
	if (indexes.size() > displayCount)
	{
		layout()->addWidget(scrollBar);
		scrollBar->show();
	}
	if (autoRoll)
	{
		//�����Ҫ��������� ��displayCount С����ôֱ��׷�ӵ�ĩβ
		if (indexes.size() < displayCount)
		{
			addItemInternal(indexes.size() - 1, indexes.back());
		}
		//��������Ҫ������һ��Ԫ��
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
