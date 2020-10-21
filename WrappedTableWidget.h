#pragma once
#include <QTableWidget>
#include <QHeaderView>
#include <QMouseEvent>

#include <vector>
#include "Utility.h"
class WrappedTableWidget :public QTableWidget
{
	Q_OBJECT
protected:
	void mousePressEvent(QMouseEvent* event)
	{
		// 点击空白处时取消所有已选择项
		auto item = this->itemAt(event->pos());
		if (!item)
		{
			this->clearSelection();
		}
		else
		{
			QTableWidget::mousePressEvent(event);
		}
	}
public:
	WrappedTableWidget(QWidget* parent = nullptr) :QTableWidget(parent)
	{
		this->setSelectionBehavior(QAbstractItemView::SelectRows);
		this->setSelectionMode(QAbstractItemView::SingleSelection);
		this->horizontalHeader()->setHighlightSections(false);
		this->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);    //x先自适应宽度
		//this->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);     //然后设置要根据内容使用宽度的列
	}

	void setHeadTitle(const QStringList& headList)
	{
		this->setColumnCount(headList.size());
		this->setHorizontalHeaderLabels(headList);
		//this->setRowCount(headList.size());
	}

	void appendRow(const std::vector<std::string>& contents)
	{
		this->setRowCount(this->rowCount() + 1);
		setRowItems(this->rowCount() - 1, contents);
	}

	void setItem(int row, int column, const std::string& item)
	{
		QTableWidget::setItem(row, column, new QTableWidgetItem(item.c_str()));
	}
	void setRowItems(int row, const std::vector<std::string>& contents)
	{
		for (int i = 0; i < contents.size(); i++)
		{
			if (!this->item(row, i)) QTableWidget::setItem(row, i, new QTableWidgetItem);
			this->item(row, i)->setText(contents[i].c_str());
		}
	}
	std::string getItem(int row, int column)
	{
		return QTableWidget::item(row, column)->text().toStdString();
	}
	std::vector<std::string> getItems(int row)
	{
		std::vector<std::string> ans;
		for (int i = 0; i < this->columnCount(); i++)
		{
			ans.push_back(QTableWidget::item(row, i)->text().toStdString());
		}
		return ans;
	}
	std::vector<int> findItems(const QString& content)
	{
		auto items = QTableWidget::findItems(content, Qt::MatchFlag::MatchCaseSensitive);

		std::vector<int> rowIndex;
		for (auto item : items)
		{
			rowIndex.push_back(item->row());
		}
		return rowIndex;
	}

	int getSelectedRowIndex()
	{
		int row = this->selectedRanges().front().topRow();
		return row;
	}
};

