#include "WrappedWidget.h"

WrappedWidget::WrappedWidget(QWidget *parent)
    : QWidget(parent)
{
    mainLayout = new QVBoxLayout;
    setLayout(mainLayout);
    layoutsStack.push_back(mainLayout);
    
	setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    /*
	*     doGroupBox("1123");
	doHorizontalLayout();
	doButton("123", "345");
	doButton("456", "3675");
	endLayout();

	doGroupBox("345");

	doVerticalLayout();
	doButton("123", "345");
	doButton("456", "3675");
	endLayout();

	doHorizontalLayout();
	doButton("12367", "34546");
	doSpacer(500);
	doButton("45689", "367578");
	endLayout();
	endGroupBox();

	endGroupBox();
    */

}
