#pragma once
#include <QProgressBar>

class WrappedProgressBar :public QProgressBar
{
	Q_OBJECT

Q_SIGNALS:
	void updateValue_signal(int value);

public:
	WrappedProgressBar(QWidget* parent = nullptr) :QProgressBar(parent)
	{

	}
	~WrappedProgressBar()
	{

	}
	void mySetValue(int value)
	{
		emit updateValue_signal(value);
	}
};