#pragma once
#ifndef TitleBarWidget_H
#define TitleBarWidget_H
#include <QWidget>
#include <QToolButton>
#include <QEvent>
#include <QStyle>
#include <QLabel>
#include <QMouseEvent>
#include <QLayout>
#include <QMenuBar>
#include <Windows.h>
#include <QApplication>
class TitleBarWidget : public QWidget
{
	Q_OBJECT
private:
	void doPropertySetting()
	{
		//setAutoFillBackground(true);
		//setBackgroundRole(QPalette::ColorRole::Background);
		//setStyleSheet("background-color:#000000");
	}
	void doWidgetInit()
	{
		setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

		QWidget* rightWidget = new QWidget(this);
		QWidget* topRightWidget = new QWidget(rightWidget);
		QWidget* bottomRightWidget = new QWidget(rightWidget);

		iconLabel = new QLabel(this);
		minimizeButton = new QToolButton(bottomRightWidget);
		topmostButton = new QToolButton(bottomRightWidget);
		closeButton = new QToolButton(bottomRightWidget);
		titleLabel = new QLabel(topRightWidget);
		menuBar = new QMenuBar(bottomRightWidget);

		QHBoxLayout* mainLayout = new QHBoxLayout(this);
		QHBoxLayout* topLayout = new QHBoxLayout(topRightWidget);
		QHBoxLayout* bottomLayout = new QHBoxLayout(bottomRightWidget);
		QVBoxLayout* rightLayout = new QVBoxLayout(rightWidget);

		mainLayout->setContentsMargins(10, 0, 5, 0);
		mainLayout->setSpacing(10);

		topLayout->setContentsMargins(5, 10, 0, 0);
		topLayout->setSpacing(0);

		bottomLayout->setContentsMargins(0, 0, 0, 0);
		bottomLayout->setSpacing(5);

		rightLayout->setContentsMargins(0, 0, 0, 0);
		rightLayout->setSpacing(10);

		minimizeButton->setMinimumSize(20, 15);
		//minimizeButton->setIcon(style()->standardPixmap(QStyle::SP_TitleBarMinButton));
		minimizeButton->setStyleSheet(QString::asprintf("QToolButton{border-image:url(:/CTCMainWindow/Icons/min.png)};QToolButton:hovered{background-color:rgb(100,100,100);border-image:url(:/CTCMainWindow/Icons/min.png)}"));

		topmostButton->setMinimumSize(20, 15);
		topmostButton->setStyleSheet(QString::asprintf("border-image:url(:/CTCMainWindow/Icons/topmost.png)"));
		//topmostButton->setIcon(style()->standardPixmap(QStyle::SP_TitleBarContextHelpButton));

		closeButton->setMinimumSize(20, 15);
		closeButton->setStyleSheet(QString::asprintf("border-image:url(:/CTCMainWindow/Icons/close.png)"));
		//closeButton->setIcon(style()->standardPixmap(QStyle::SP_TitleBarCloseButton));

		//menuBar->setMinimumWidth(1000);
		menuBar->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
		menuBar->setStyleSheet({ "QMenuBar{background-color:rgb(240,240,240);}" });
		mainLayout->addWidget(iconLabel);
		mainLayout->addWidget(rightWidget);

		rightLayout->addWidget(topRightWidget);
		rightLayout->addWidget(bottomRightWidget);

		topLayout->addWidget(titleLabel);

		bottomLayout->addWidget(menuBar);
		bottomLayout->addWidget(topmostButton);
		bottomLayout->addWidget(minimizeButton);
		bottomLayout->addWidget(closeButton);

		QFont font = titleLabel->font();
		font.setFamily("微软雅黑");
		font.setPointSize(25);
		titleLabel->setFont(font);
		titleLabel->setText("隐蔽信道实验平台");

		iconLabel->setPixmap(QPixmap("Main_Icon.png").scaled(50, 50));
	}
	void doMenuItemInit()
	{

	}
	void doConnection()
	{
		connect(closeButton, &QToolButton::clicked, [this]() {
			QWidget* parent = parentWidget()->parentWidget();
			parent->close();
			QApplication::quit();
			});
		connect(minimizeButton, SIGNAL(clicked()), this, SLOT(showSmall()));
		connect(topmostButton, SIGNAL(clicked()), this, SLOT(doTopmost()));
	}
public:	TitleBarWidget(QWidget* parent = nullptr) :QWidget(parent)
	{
		doWidgetInit();
		doMenuItemInit();
		doConnection();
	}

public slots:
	void showSmall()
	{
		parentWidget()->parentWidget()->showMinimized();
	}
	void doTopmost()
	{
		//设置窗口置顶
		static bool isTopMost = false;
		if (!isTopMost)
			::SetWindowPos(HWND(parentWidget()->parentWidget()->winId()), HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
		else
			::SetWindowPos(HWND(parentWidget()->parentWidget()->winId()), HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);

		isTopMost = !isTopMost;
	}
	QMenuBar* getMenuBar() { return this->menuBar; }
protected:
	void mousePressEvent(QMouseEvent* me)
	{
		startPos = me->globalPos();
		clickPos = parentWidget()->mapToParent(mapToParent(me->pos()));
	}
	void mouseMoveEvent(QMouseEvent* me)
	{
		parentWidget()->parentWidget()->move(me->globalPos() - clickPos);
	}
private:
	QLabel*      iconLabel;
	QLabel*      titleLabel;
	QToolButton* minimizeButton;
	QToolButton* topmostButton;
	QToolButton* closeButton;
	QPoint       startPos;
	QPoint       clickPos;
	QMenuBar*    menuBar;
};
#endif // !TitleBarWidget_H

