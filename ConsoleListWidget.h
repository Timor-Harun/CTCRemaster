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

//ʵ�ֿ���̨ ��̬����Item��ListWidget
class ConsoleListWidget :public QWidget
{
	using ItemVector = QVector<Message>;

	Q_OBJECT
private:
	//list �ؼ�Ӧ����ʾ����Ŀ����
	int          displayCount;
	//��̬��ʾ�����ص� ������
	QScrollBar* scrollBar;
	//���ڶ�̬��ʾ�� �б�ؼ�
	QListWidget* listWidget;
	//�洢����Ϣ���б��ָ��
	ItemVector*  msgPtr;
	//�洢��Ҫ��ʾ����Ϣ����������
	QVector<int> indexes;
	//�洢��ItemWidget��ָ��
	std::unordered_map<int, ConsoleMessageItemWidget*> itemWidgetPtrMap;
	//�Ƿ��Զ��������ײ�
	bool         autoRoll;

	//���һ��Item
	void         addItemInternal(int relativePos, int msgIndex);
	//ͷ����һ��Item
	void         insertItemInternal(int msgIndex);
protected:
	//���ص��������¼�
	void		 wheelEvent(QWheelEvent* event);
	//���صĴ��ڳߴ��¼�
	void		 resizeEvent(QResizeEvent* event);

public slots:
	//ˢ�µ�ǰ��ʾ����Ŀ
	//����ˢ���¼��������������
	//���ڴ�СResize��Ҫ��̬������ʾ�ĸ���
	//������value�ı䣬Ҫ���µ�ǰ��ʾ��Item
	//��Ҫ��ʾ�������ı�
	//���µ���Ϣ��Print������������Զ�������Ҫ���������·���Ԫ��
	void         refreshAfterResize();
	void         refreshAfterSliderValueChanged();
	void         refreshAfterIndexesChanged();
	void         refreshAfterPrint(int index);
public:
	//set�������Ƿ��Զ���������Ϣָ�룬��Ч��Ϣ��������
	void  setAutoRoll(bool value);
	void  setMessagePtr(ItemVector* _msgPtr);
	void  setValidIndexes(const QVector<int>& _indexes);
	void  clear();
	//���캯��
	explicit	 ConsoleListWidget(QWidget* parent = 0);
	//��������
	~ConsoleListWidget();
};
#endif