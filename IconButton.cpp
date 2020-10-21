#include "IconButton.h"

IconButton::IconButton(std::string iconPath)
{
	setStyleSheet("QToolButton{border:Opx}");
	setIconSize(QSize(width(), height()));
	QPixmap pixmap(iconPath.c_str());
	setIcon(QIcon(pixmap));

	setAttribute(Qt::WA_DeleteOnClose);
}

void IconButton::setButtonSize(int width, int height)
{
	setGeometry(pos().x(), pos().y(), width, height);
}

void IconButton::setPosition(int x, int y)
{
	setGeometry(x, y, width(), height());
}


