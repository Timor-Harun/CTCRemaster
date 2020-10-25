#include "PlotManager.h"

PlotManager* PlotManager::instance = nullptr;

void PlotManager::setDefaultLegend(QLegend* legend)
{
	legend->setAlignment(Qt::AlignBottom);//底部对齐
										  //legend->detachFromChart();
	legend->setBackgroundVisible(true);//设置背景是否可视
									   //legend->setAutoFillBackground(true);//设置背景自动填充
									   //legend->setColor(QColor(255,128,128,128));//设置颜色
									   //legend->setContentsMargins(10,10,10,10);//设置边距left,top,right,bottom
	legend->setLabelColor(QColor(0, 0, 0));//设置标签颜色
	legend->setVisible(false);//设置是否可视
							  //legend->setMaximumHeight(50);
							  //legend->setMaximumWidth(120);
							  //legend->setMaximumSize(10000);
							  //legend->setGeometry(50,50,120,50);//设置几何位置x,y,w,h
							  //legend->setBrush(QBrush(QColor(128,128,128,128)));
							  //legend->setPen(QPen(QColor(192,192, 192,192)));
	legend->setBorderColor(QColor(0, 0, 0, 0));//设置边框颜色
	QFont font = legend->font();
	font.setItalic(!font.italic());
	legend->setFont(font);//设置字体为斜体
	font.setPointSizeF(12);
	legend->setFont(font);//设置字体大小
	legend->setFont(QFont("微软雅黑"));//设置字体类型
}

QChartView* PlotManager::createDefaultChartView(QChart* chart, const std::string& windowTitle)
{
	QChartView* chartView = new QChartView(chart);
	chartView->setWindowTitle(QString::fromStdString(windowTitle));
	chartView->setRenderHint(QPainter::Antialiasing);
	chartView->setMinimumSize(50, 50);
	chartView->setAttribute(Qt::WA_DeleteOnClose);
	return chartView;
}

QChart* PlotManager::createDefalutChart(const std::string& chartTitle)
{
	QChart* chart = new QChart();
	chart->setLocalizeNumbers(true);//数字是否本地化
	chart->setTitle(QString::fromStdString(chartTitle));
	chart->setTitleBrush(QBrush(QColor(0, 0, 0)));//设置标题Brush
	chart->setTitleFont(QFont("微软雅黑"));//设置标题字体
	return chart;
}

void PlotManager::figure(int n)
{
	m_preFigure = n;
	m_holdonFlag = false;
}

void PlotManager::holdOn()
{
	m_holdonFlag = true;
}

void PlotManager::holdOff()
{
	m_holdonFlag = false;
}

void PlotManager::subPlot(int m, int n, int p)
{
	if (!m_subplot_flag)
	{
		m_subplot_flag = true;
		m_subplot_m = m;
		m_subplot_n = n;

	}
	else
	{
		if (m_subplot_m != n || m_subplot_n != n)
		{
			m_subplot_m = m;
			m_subplot_n = n;
		}
	}
	m_subplot_ps = { p };
}

void PlotManager::subPlot(int m, int n, const std::vector<int>& ps)
{
	if (!m_subplot_flag)
	{
		m_subplot_flag = true;
		m_subplot_m = m;
		m_subplot_n = n;

	}
	else
	{
		if (m_subplot_m != n || m_subplot_n != n)
		{
			m_subplot_m = m;
			m_subplot_n = n;
		}
	}
	m_subplot_ps = ps;
}

void PlotManager::plot(std::vector<double> x, std::vector<double> y, const std::string& windowTitle, const std::string& seriesName, const QColor& lineColor, std::string xLabel, std::string yLabel, int lineWidth, const std::string& title)
{
	//实例化一个QLineSeries对象
	QLineSeries* series = new QLineSeries();
	//序列添加数值
	for (int i = 0; i < x.size(); i++)
	{
		*series << QPointF((int)x[i], y[i]);
	}
	series->setName(QString::fromStdString(seriesName));
	series->setPen(QPen(QBrush(lineColor), 1, Qt::SolidLine));
	series->setUseOpenGL(true);
	if (!m_holdonFlag || !m_preChart)
	{
		if (!m_preFigure) m_preFigure = rand();
		QChart* chart = createDefalutChart(title);
		chart->addSeries(series);//添加系列到QChart上
		setDefaultLegend(chart->legend());
		QChartView* chartView = createDefaultChartView(chart, windowTitle);
		placePlotWindow(chartView, chart);
	}
	else
	{
		m_preChart->addSeries(series);
	}
	double xMin, xMax, yMin, yMax;
	xMin = *std::min_element(x.begin(), x.end());
	xMax = *std::max_element(x.begin(), x.end());
	yMin = *std::min_element(y.begin(), y.end());
	yMax = *std::max_element(y.begin(), y.end());
	//创建坐标
	QValueAxis* axisX = new QValueAxis;//X轴
	axisX->setRange(xMin, xMax);//设置坐标轴范围
	axisX->setTitleText("time(secs)");//标题
	axisX->setLabelFormat("%.0f"); //标签格式：每个单位保留几位小数
	axisX->setTickCount(std::min((size_t)10, x.size())); //主分隔个数：0到10分成20个单位
	QValueAxis* axisY = new QValueAxis; //Y 轴
	axisY->setRange(yMin, yMax);
	axisY->setTitleText("value");
	axisY->setLabelFormat("%.2f"); //标签格式
	axisY->setTickCount((std::min((size_t)10, y.size())));

	for (int i = 0; i < m_preChart->series().size(); i++)
	{
		QValueAxis* old_axisX = (QValueAxis*)(m_preChart->axisX(m_preChart->series()[i]));
		QValueAxis* old_axisY = (QValueAxis*)(m_preChart->axisY(m_preChart->series()[i]));

		if (old_axisX && old_axisY)
		{
			axisX->setRange(std::min(old_axisX->min(), xMin), std::max(old_axisX->max(), xMax));
			axisY->setRange(std::min(old_axisY->min(), yMin), std::max(old_axisY->max(), yMax));
		}
		//为序列设置坐标轴
		m_preChart->setAxisX(axisX, m_preChart->series()[i]);
		m_preChart->setAxisY(axisY, m_preChart->series()[i]);
	}
}

void PlotManager::placePlotWindow(QChartView* chartView, QChart* chart)
{
	if (!m_subplot_flag)
	{
		PlotWindow* window = new PlotWindow(chartView);
		m_figureMap[m_preFigure] = window;
		m_preChart = chart;
		m_preFigure = -1;
		m_prePlotWindow = window;
	}
	else
	{
		if (!m_prePlotWindow)
		{
			m_prePlotWindow = new PlotWindow(m_subplot_m, m_subplot_n);
			m_figureMap[m_preFigure] = m_prePlotWindow;
			m_preFigure = -1;
		}
		m_preChart = chart;
		m_prePlotWindow->addSubPlot(m_subplot_ps, chartView);
	}
}

void PlotManager::bar(std::vector<int> values, std::vector<std::string> valueNames, std::string label, std::string windowTitle)
{
	QBarSet* set = new QBarSet(QString::fromStdString(label));
	QStringList categories;
	for (int i = 0; i < values.size(); i++)
	{
		(*set) << values[i];
		categories << QString::fromStdString(valueNames[i]);
	}
	if (!m_holdonFlag || !m_preChart)
	{
		if (!m_preFigure) m_preFigure = rand();
		QBarSeries* series = new QBarSeries();
		series->append(set);
		QChart* chart = createDefalutChart(windowTitle);
		chart->addSeries(series);
		setDefaultLegend(chart->legend());
		QBarCategoryAxis* axis = new QBarCategoryAxis();
		axis->append(categories);
		chart->createDefaultAxes();//创建默认的左侧的坐标轴（根据 QBarSet 设置的值）
		chart->setAxisX(axis, series);//设置坐标轴
		QChartView* chartView = createDefaultChartView(chart, windowTitle);
		placePlotWindow(chartView, chart);
	}
	else
	{
		auto axis = qobject_cast<QBarCategoryAxis*>(m_preChart->axisX());
		axis->append(categories);

		auto series = qobject_cast<QBarSeries*>(m_preChart->series()[0]);
		series->append(set);
	}
}

void PlotManager::pie()
{

}

void PlotManager::bar3D()
{

}

void PlotManager::displayAll()
{
	for (auto p : m_figureMap)
	{
		if (!(p).second->windowTitle().size())
		{
			p.second->setWindowTitle(QString("Figure %1").arg(p.first));
		}
		p.second->show();
	}
	m_figureMap.clear();
}

PlotManager* PlotManager::getInstance()
{
	if (instance == nullptr)
		instance = new PlotManager;
	return instance;
}

PlotManager::PlotManager() :m_preChart(nullptr),
m_prePlotWindow(nullptr),
m_holdonFlag(false),
m_preFigure(-1),
m_subplot_flag(false) {
	srand((unsigned)(time(NULL)));
}
