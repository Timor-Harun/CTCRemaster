#pragma once
#include <QToolButton>
#include <string>

class IconButton :public QToolButton
{
public:
	IconButton(std::string iconPath);
	void setButtonSize(int width, int height);
	void setPosition(int x, int y);

	template<typename Func>
	void addClickEvent(const typename QtPrivate::FunctionPointer<Func>::Object* receiver, Func slot)
	{
		connect(this, &IconButton::clicked, receiver, slot);
	}

	template<typename Func>
	void addClickEvent(Func slot)
	{
		connect(this, &IconButton::clicked, this, slot);
	}
};

