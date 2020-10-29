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
#include "DialogExecutor.h"
using namespace TimorHarun::Scripting;

#define Python PythonScriptSystem::getInstance()

class CTCMainWindow : public QMainWindow
{
    Q_OBJECT

private:
	//根据 菜单项信息 添加菜单项 到菜单栏
    void addMenuItem(const MenuItemInfo & info)
    {
		//由于菜单项 有一个具体的路径，所以需要遍历菜单项路径上的节点
		//找到其最后一个公共节点后插入

		//记录上一个遍历到的 菜单项路径节点
        MenuItemNode* lastNode = NULL;

		//记录上一个遍历到的 菜单项路径节点的深度
        int lastIndex = 0;

		//如果不包含 待加入的菜单项的路径
        if (!menuItemRoot->containsChild(info.path, lastNode,&lastIndex))
        {
			//则从最后一个 公共菜单项路径节点开始，依次添加子节点
            for (int i = lastIndex; i < info.path.size(); i++)
            {
				//只有根节点才是Action，否则都是Menu
				if (i == info.path.size()-1)
				{
					//添加子节点
                    auto childNode = lastNode->addChild(info.path[i], info.checkable);
					//添加子目录
					lastNode->menu->addAction(childNode->action);

					//如果Action是checkable（可勾选的），点击事件是toggled，否则是triggered
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
					//绑定 快捷键
                    int Keys = 0;

                    if (info.shortCutInfo.useCtrl)  Keys  |= Qt::CTRL;
                    if (info.shortCutInfo.useShift) Keys  |= Qt::SHIFT;
                    if (info.shortCutInfo.keyCode)  Keys  |= info.shortCutInfo.keyCode;

                    childNode->action->setShortcut(Keys);
				}
                else
                {
					//添加子Menu
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
