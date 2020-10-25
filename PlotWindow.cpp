#include "PlotWindow.h"

PlotWindow::PlotWindow(QChartView* chartView) :m_menuBar(new QMenuBar), m_chartView(chartView)
{
	setMinimumSize(800, 600);
	setCentralWidget(m_chartView);
	this->setAttribute(Qt::WA_DeleteOnClose);
	this->setMenuBar(m_menuBar);
	QMenu* menu_File = new QMenu("ÎÄ¼þ(&F)");
	menu_File->addAction("½ØÍ¼(&S)", [=]() {
		QString path = QFileDialog::getSaveFileName(NULL, "±£´æ»æÖÆÍ¼Ïñ½ØÍ¼",
			QApplication::applicationDirPath(),
			"BMP Image (*.bmp);;JPEG Image (*.jpg);;PNG Image (*.png)");
		QPixmap pixmap = m_chartView->grab();
		if (!pixmap.save(path))
		{
			qDebug() << "Save Image File Failed";
		}
		});
	menu_File->addSeparator();
	menu_File->addAction("ÍË³ö(&Q)", [=]() {this->close(); });
	m_menuBar->addMenu(menu_File);
}

void PlotWindow::resizeEvent(QResizeEvent* event)
{
	if (m_subplot_m && m_subplot_n)
	{
		QSize size = event->size();
		int w = size.width() / m_subplot_n;
		int h = size.height() / m_subplot_m;

		for (int i = 0; i < m_subplot_m * m_subplot_n; i++)
		{
			auto _layout = qobject_cast<QGridLayout*>(centralWidget()->layout());
			QWidget* widget = _layout->itemAt(i)->widget();
			widget->setFixedSize(w - 1, h - 1);
		}
	}
	QMainWindow::resizeEvent(event);
}

PlotWindow::PlotWindow(int m, int n) :m_menuBar(new QMenuBar), m_chartView(nullptr), m_subplot_m(m), m_subplot_n(n)
{
	m_grid = std::vector<std::vector<bool>>(m_subplot_m, std::vector<bool>(m_subplot_n));

	QGridLayout* layout = new QGridLayout;

	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < m; j++)
		{
			QWidget* widget = new QWidget;
			widget->setMinimumSize(50, 50);
			layout->addWidget(widget, i, j);
		}
	}
	QWidget* widget = new QWidget;
	widget->setLayout(layout);
	layout->setContentsMargins(9, 9, 9, 9);
	layout->setHorizontalSpacing(5);
	layout->setVerticalSpacing(5);

	this->setMinimumSize(800, 600);
	this->setCentralWidget(widget);
	this->setAttribute(Qt::WA_DeleteOnClose);
	this->setMenuBar(m_menuBar);
	QMenu* menu_File = new QMenu("ÎÄ¼þ(&F)");
	menu_File->addAction("½ØÍ¼(&S)", [=]() {
		QString path = QFileDialog::getSaveFileName(NULL, "±£´æ»æÖÆÍ¼Ïñ½ØÍ¼",
						QApplication::applicationDirPath(),
						"BMP Image (*.bmp);;JPEG Image (*.jpg);;PNG Image (*.png)");
		QPixmap pixmap = centralWidget()->grab();
		if (!pixmap.save(path))
		{
			qDebug() << "Save Image File Failed";
		}
		});
	menu_File->addSeparator();
	menu_File->addAction("ÍË³ö(&Q)", [=]() {this->close(); });
	m_menuBar->addMenu(menu_File);
}

void PlotWindow::addSubPlot(int index, QWidget* chartWidget)
{
	int m = index / m_subplot_m;
	int n = index % m_subplot_m;

	QGridLayout* layout = qobject_cast<QGridLayout*>(this->centralWidget()->layout());
	QWidget* widget = layout->itemAt(index - 1)->widget();
	delete widget;
	widget = NULL;
	layout->addWidget(chartWidget, m, n);
}

bool PlotWindow::checkRectValid(const std::vector<int>& indexes, int& xMin, int& yMin, int& xMax, int& yMax)
{
	xMin = yMin = INT_MAX;
	xMax = yMax = INT_MIN;
	for (int i = 0; i < indexes.size(); i++)
	{
		int x = (indexes[i] - 1) / m_subplot_m;
		int y = (indexes[i] - 1) % m_subplot_m;

		xMax = std::max(x, xMax);
		xMin = std::min(x, xMin);
		yMax = std::max(y, yMax);
		yMin = std::min(y, yMin);
	}

	int w = xMax - xMin + 1;
	int l = yMax - yMin + 1;

	std::unordered_set<int> set;

	for (int i = 0; i < indexes.size(); i++)
	{
		int x = (indexes[i] - 1) / m_subplot_m - xMin;
		int y = (indexes[i] - 1) % m_subplot_m - yMin;

		int index = w * y + x;
		if (set.find(index) == set.end())
		{
			set.insert(index);
		}
		else
		{
			return false;
		}
	}
	return true;
}

void PlotWindow::addSubPlot(std::vector<int> indexes, QWidget* chartWidget)
{
	int xMin, yMin, xMax, yMax;
	if (checkRectValid(indexes, xMin, yMin, xMax, yMax))
	{
		QGridLayout* layout = qobject_cast<QGridLayout*>(this->centralWidget()->layout());
		for (int i = 0; i < indexes.size(); i++)
		{
			QWidget* widget = layout->itemAt(indexes[i] - 1)->widget();
			layout->replaceWidget(widget, chartWidget);
			//layout->removeWidget(widget);
			delete widget;
			widget = NULL;
		}
		//layout->addWidget(chartWidget, xMin, yMin,xMax-xMin+1, yMax - yMin+1);
	}
}
