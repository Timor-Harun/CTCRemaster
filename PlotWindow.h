#pragma once
/********QT INCLUDES********/
#include <QMainWindow>
#include <QChartView>
#include <QMenuBar>
#include <QFileDialog>
#include <QApplication>
#include <QGridLayout>
#include <QDebug>
#include <QMenu>
/********STL INCLUDES********/
#include <unordered_set>

QT_CHARTS_USE_NAMESPACE

class PlotWindow :public QMainWindow
{
private:
	//菜单栏指针
	QMenuBar*                         m_menuBar;
	//指向图表窗口的指针
	QChartView*                       m_chartView;
	//子图的行数
	int								  m_subplot_m;
	//子图的列数
	int								  m_subplot_n;
	std::vector<std::vector<bool>>	  m_grid;

	//检查子图所占的索引位置是否能完全填充一个矩形区域
	bool checkRectValid(const std::vector<int>& indexes, int& xMin, int& yMin, int& xMax, int& yMax);

protected:
	//重写 窗口重设大小事件
	void resizeEvent(QResizeEvent* event);
public:
	//启用子图时候的构造函数
	//参数m：子图的行数
	//参数n：子图的列数
	PlotWindow(int m, int n);

	//不启用子图时候的构造函数
	//参数chartView：图标窗口指针
	PlotWindow(QChartView* chartView);

	//添加子图窗口
	//参数index：子图所占的索引位置
	//参数chartWidget：子图的窗口指针
	void addSubPlot(int index, QWidget* chartWidget);

	//添加子图窗口
	//参数indexes：子图所占的索引位置数组
	//参数chartWidget：子图的窗口指针
	void addSubPlot(std::vector<int> indexes, QWidget* chartWidget);
};