#include "ConsoleMessagePool.h"

void ConsoleMessagePool::pushMessage(const Message& msg)
{
	pool.append(msg);
}

bool ConsoleMessagePool::isEmpty()
{
	return pool.isEmpty();
}

Message ConsoleMessagePool::getLastMessage()
{
	Message msg = pool.front();
	pool.pop_front();
	return msg;
}
