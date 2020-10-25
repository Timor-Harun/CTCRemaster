#pragma once

/********QT INCLUDES********/
#include <QColor>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarCategoryAxis>
#include <QLayout>
#include <QDebug>
#include <QValueAxis>
#include <QResizeEvent>
/**********STL INCLUDES***********/
#include <vector>
#include <unordered_map>
/**********CUSTOMS INCLUDES***********/
#include "PlotWindow.h"

QT_CHARTS_USE_NAMESPACE

#define plt PlotManager::getInstance()

class PlotManager
{
private:
	/********Hold On 实现相关变量********/

	//m_holdonFlag：指示是否启动了Hold On,如果启动了，下次绘制图像将绘制在上一图像上
	bool							  m_holdonFlag;
	//m_preChart：上一图像的指针
	QChart*                           m_preChart;

	/********Figure 实现相关变量********/

	//m_preFigure：指示当前图像的编号，注意不能重复
	int								  m_preFigure;
	//m_figureMap：字典：key代表图像的编号，其通过void figure(int) 声明，Value存储图像编号对应的窗口指针
	std::unordered_map<int, QWidget*> m_figureMap;

	/********subplot 实现相关变量********/

	//m_subplot_m：代表子图有m行
	int								  m_subplot_m;
	//m_subplot_m：代表子图有n列
	int								  m_subplot_n;

	//m_subplot_ps：代表当前图标占用的索引编号
	std::vector<int>				  m_subplot_ps;
	//m_subplot_flag：代表启用了subplot
	bool							  m_subplot_flag;
	//m_prePlotWindow：上一个subplot使用的到的窗口指针
	PlotWindow*						  m_prePlotWindow;

	/********单例类 实现相关变量********/
	static PlotManager*               instance;

	//设置默认图例
	//参数legend：要设置的图例指针
	void         setDefaultLegend(QLegend* legend);

	//创建默认ChartView，并返回指针
	//参数chart：图标指针
	//参数windowTitle：窗口标题
	QChartView*  createDefaultChartView(QChart* chart, const std::string& windowTitle);

	//创建默认Chart，并返回指针
	//参数chartTitle：图表标题
	QChart*      createDefalutChart(const std::string& chartTitle);

	//将图表放置到放置到图表窗口中
	//参数chartView：图标窗口指针
	//参数chart：图表指针
	void         placePlotWindow(QChartView* chartView, QChart* chart);

public:
	//声明并创建一幅图表
	//参数n：图表的编号
	//注意：如果n的数值已经存在了，将覆盖之前编号为n的图表
	void		 figure(int n);

	//设置 在相同的图表上绘制
	void		 holdOn();

	//设置 不在相同的图表上绘制
	void		 holdOff();

	//产生一幅多个子图构成的图表
	//参数m：图表的行的数量
	//参数n：图表的列的数量
	//参数p：子表所占的位置索引
	//注意：如果 上一次 调用subplot 时候m或n不同，将产生新的子图
	void		 subPlot(int m, int n, int p);

	//产生一幅多个子图构成的图表
	//参数m：图表的行的数量
	//参数n：图表的列的数量
	//参数ps：子表所占的位置索引列表
	//注意：子表所占的位置索引列表 在对应的 网格中不能填充一个矩形区域，那么将舍弃当前子图
	void		 subPlot(int m, int n, const std::vector<int>& ps);

	//绘制一幅折线图
	//参数x：x轴数据点的数组
	//参数y：y轴数据点的数组
	//参数windowTitle：图表的窗口标题
	//参数seriesName：当前数据集合的名称
	//参数lineColor：绘制当前数据集所用到的线条颜色
	//参数lineWidth：绘制当前数据集所用到的线条宽度
	//参数xLabel：x轴的标题
	//参数yLabel：y轴的标题
	//参数title：图表的标题
	//注意：x轴，y轴数据点的数组长度必须相同
	void		 plot(std::vector<double> x,
				      std::vector<double> y,
					  const std::string& windowTitle = "",
				      const std::string &seriesName = "line",
				      const QColor &lineColor = QColor(),
					  std::string xLabel = "X",
				      std::string yLabel = "Y",
				      int lineWidth = 1,
				      const std::string &title = "");

	//绘制一幅柱状图
	//参数values：数据点的数组
	//参数valueNames：每一个数据点对应的名称数组
	//参数label：图表的标题
	//参数windowTitle：图表的窗口标题
	void         bar(std::vector<int> values,
					 std::vector<std::string> valueNames, 
					 std::string label,
					 std::string windowTitle);

	void		 pie();
	void		 bar3D();

	//显示所有图表
	void		 displayAll();

	//获取单例类指针
	static PlotManager* getInstance();

	/********构造 与 析构 函数********/
	PlotManager();
	~PlotManager() { instance = nullptr; }
};
