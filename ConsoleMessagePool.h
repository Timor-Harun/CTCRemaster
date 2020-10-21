#pragma once

#include <QString>
#include <QVector>
#include "Global.h"

class ConsoleMessagePool
{
private:
	QVector<Message> pool;
public:
	void pushMessage(const Message& msg);

	bool isEmpty();

	Message getLastMessage();
};

