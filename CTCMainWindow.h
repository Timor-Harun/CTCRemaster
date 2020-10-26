#pragma once

#include <QtWidgets/QMainWindow>
#include <QMessageBox>
#include <QSplitter>
#include <QApplication>
#include <QtGui>
#include <QLayout>
#include <QStyle>
#include <QToolButton>
#include <QLayout>
#include <QLabel>
#include <QSpacerItem>
#include <QPushButton>
#include <QTextEdit>
#include <QMenu>
#include <QAction>
#include <QTreeWidgetItem>

#include "ui_CTCMainWindow.h"
#include "PythonScriptSystem.h"
#include "TitleBarWidget.h"
#include "PythonCodeEditor.h"
#include "WrappedWidget.h"
#include "WrappedTableWidget.h"
#include "ConsoleLogic.h"

using namespace TimorHarun::Scripting;

#define Python PythonScriptSystem::getInstance()


class CTCMainWindow : public QMainWindow
{
    Q_OBJECT

private:
    void addMenuItem(const MenuItemInfo & info)
    {
        MenuItemNode* lastNode = NULL;
        int lastIndex = 0;
        if (!menuItemRoot->containsChild(info.path, lastNode,&lastIndex))
        {
            for (int i = lastIndex; i < info.path.size(); i++)
            {
				if (i == info.path.size()-1)
				{
                    auto childNode = lastNode->addChild(info.path[i], info.checkable);
					lastNode->menu->addAction(childNode->action);
					if (info.checkable)
					{
						connect(childNode->action, &QAction::toggled, this, [=](bool value) {
							//没有孩子节点才 调用Action
							Python->invokeMenuItemSlot(info.uuid, value);
						});
					}
					else
					{
						connect(childNode->action, &QAction::triggered, this, [=]() {
							//没有孩子节点才 调用Action
							Python->invokeMenuItemSlot(info.uuid,false);
						});
					}

                    int Keys = 0;

                    if (info.shortCutInfo.useCtrl)  Keys  |= Qt::CTRL;
                    if (info.shortCutInfo.useShift) Keys  |= Qt::SHIFT;
                    if (info.shortCutInfo.keyCode)  Keys  |= info.shortCutInfo.keyCode;

                    childNode->action->setShortcut(Keys);
				}
                else
                {
                    auto current = lastNode->addChild(info.path[i]);
					if (lastNode == menuItemRoot)
					{
						ui.widget_Title->getMenuBar()->addMenu(current->menu);
					}
					else
					{
						lastNode->menu->addMenu(current->menu);
					}
                    lastNode = current;
                }
            }
        }
        else
        {
            /*Nothing to do*/
        }
    }
	void doInitWidgetList()
	{

	}
protected:

	void contextMenuEvent(QContextMenuEvent* event)
	{
		//这里主要针对 treeView设置 右键菜单
		auto rowIndex = ui.navTreeView->currentIndex();
		QStandardItemModel* model = qobject_cast<QStandardItemModel*>(ui.navTreeView->model());
		if (rowIndex.row()>=0)
		{
			QMenu* menu = new QMenu;
			menu->setAttribute(Qt::WA_DeleteOnClose);
		
			QAction * action =  menu->addAction("执行");
			connect(action, &QAction::triggered, [=]() {
				WrappedWidget* widget = Python->doGetWidgetCreation(model->itemFromIndex(rowIndex)->text());

				QWidget* tabContentWidget = new QWidget;
				QVBoxLayout* layout = new QVBoxLayout;
				tabContentWidget->setLayout(layout);
				layout->addSpacerItem(new QSpacerItem(40, 40, QSizePolicy::Minimum, QSizePolicy::Expanding));
				layout->addWidget(widget);
				layout->addSpacerItem(new QSpacerItem(40, 40, QSizePolicy::Minimum, QSizePolicy::Expanding));

				if (!widget) return;
				int index = ui.tabWidget->addTab(tabContentWidget,widget->windowTitle());
				ui.tabWidget->setCurrentIndex(index);
			});

			action = menu->addAction("编辑代码");
			connect(action, &QAction::triggered, [=]() {
				PythonCodeEditor* editor = new PythonCodeEditor;
				editor->setFile(QApplication::applicationDirPath()+"/Scripts/Custom/"+ model->itemFromIndex(rowIndex)->text()+".py");
				QWidget* tabContentWidget = new QWidget;
				QVBoxLayout* layout = new QVBoxLayout;
				tabContentWidget->setLayout(layout);
				layout->addWidget(editor);
				if (!editor) return;
				int index = ui.tabWidget->addTab(tabContentWidget, model->itemFromIndex(rowIndex)->text() + ".py【编辑】");
				ui.tabWidget->setCurrentIndex(index);
				});

			menu->exec(QCursor::pos());
		}
	}

public:
    CTCMainWindow(QWidget *parent = Q_NULLPTR);
private:
	Ui::CTCMainWindowClass ui;
	MenuItemNode* menuItemRoot;
};
