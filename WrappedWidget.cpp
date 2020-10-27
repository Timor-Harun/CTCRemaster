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
void WrappedWidget::setUUID(const QString& uuid)
{
	this->uuid = uuid;
}
QString WrappedWidget::getUUID()
{
	return this->uuid;
}
void WrappedWidget::doHorizontalLayout()
{
	QWidget* widget = new QWidget;
	QHBoxLayout* hLayout = new QHBoxLayout(widget);
	widget->setLayout(hLayout);
	layoutsStack.push(hLayout);
}
void WrappedWidget::doVerticalLayout()
{
	QWidget* widget = new QWidget;
	QVBoxLayout* vLayout = new QVBoxLayout(widget);
	widget->setLayout(vLayout);

	layoutsStack.push(vLayout);
}
QPushButton* WrappedWidget::doButton(const QString& objectName, const QString& buttonText)
{
	QPushButton* button = new QPushButton;
	button->setObjectName(objectName);
	objectNamesSets.insert(objectName);

	button->setText(buttonText);
	connect(button, &QPushButton::clicked, this, [=]() {
		const QString& objectName = QObject::sender()->objectName();
		emit signal_ButtonClickEvent(objectName);
		});

	layoutsStack.top()->addWidget(button);
	return button;
}
QLineEdit* WrappedWidget::doLineEdit(const QString& objectName)
{
	QLineEdit* lineEdit = new QLineEdit;
	connect(lineEdit, &QLineEdit::editingFinished, this, [=]() {emit signal_EditFinished(objectName); });
	layoutsStack.top()->addWidget(lineEdit);
	return lineEdit;
}
void WrappedWidget::doSpacer(int spacing)
{
	((QBoxLayout*)(layoutsStack.top()))->addSpacing(spacing);
}
QComboBox* WrappedWidget::doComboBox(const QString& objectName, const QStringList& items)
{
	QComboBox* box = new QComboBox;
	box->setObjectName(objectName);
	box->addItems(items);
	return box;
}
QCheckBox* WrappedWidget::doCheckBox(const QString& objectName, const QString& objectText, bool checked)
{
	QCheckBox* checkBox = new QCheckBox;
	checkBox->setObjectName(objectName);
	checkBox->setText(objectText);
	checkBox->setChecked(checked);

	connect(checkBox, &QCheckBox::toggled, this, [=]() {emit signal_CheckBoxStageChanged(objectName); });
	layoutsStack.top()->addWidget(checkBox);

	return checkBox;
}
WrappedProgressBar* WrappedWidget::doProgressBar(const QString& objectName, int value, int min, int max)
{
	WrappedProgressBar* progressBar = new WrappedProgressBar;
	progressBar->setObjectName(objectName);
	progressBar->setRange(min, max);
	progressBar->setValue(value);
	layoutsStack.top()->addWidget(progressBar);
	return progressBar;
}
WrappedTableWidget* WrappedWidget::doTable(const QString& objectName, const QStringList& headerLabels)
{
	WrappedTableWidget* table = new WrappedTableWidget;
	table->setHeadTitle(headerLabels);
	table->setObjectName(objectName);
	layoutsStack.top()->addWidget(table);
	connect(table, &WrappedTableWidget::itemSelectionChanged, this, [=]() {
		emit signal_TableSelectedIndexChanged(objectName, table->getSelectedRowIndex());
		});
	return table;
}
IPAddress* WrappedWidget::doIPAddress(const QString& objectName)
{
	IPAddress* address = new IPAddress;
	address->setObjectName(objectName);

	layoutsStack.top()->addWidget(address);
	return address;
}
void WrappedWidget::doGroupBox(const QString& title)
{
	QGroupBox* groupBox = new QGroupBox(title);
	groupBox->setLayout(new QGridLayout);
	layoutsStack.top()->addWidget(groupBox);
	layoutsStack.push(groupBox->layout());
}
void WrappedWidget::endGroupBox()
{
	layoutsStack.pop();
}
QLabel* WrappedWidget::doLabel(const QString& text)
{
	QLabel* label = new QLabel(text);

	layoutsStack.top()->addWidget(label);
	return label;
}
void WrappedWidget::endLayout()
{
	QLayout* layout = layoutsStack.top();
	layoutsStack.pop();
	QWidget* widget = qobject_cast<QWidget*>(layout->parent());
	layoutsStack.top()->addWidget(widget);
}
void WrappedWidget::doTab()
{

}
void WrappedWidget::endTab()
{

}