#pragma once

//QsciScintilla作为QWidget的控件，需要添加该控件的头文件
#include <Qsci/qsciscintilla.h>
//以python语法作为例子，该语法分析器的头文件
#include <Qsci/qscilexerpython.h>
//设置代码提示功能，依靠QsciAPIs类实现
#include <Qsci/qsciapis.h>
#include <QWidget>
#include <QLayout>
#include <QFile>
#include <QToolBar>
#pragma comment(lib,"qscintilla2_qt5d.lib")

class PythonCodeEditor:public QWidget
{
private:
	QsciScintilla* editor;
public:
	PythonCodeEditor(QWidget* parent = nullptr) :QWidget(parent)
	{
		editor = new QsciScintilla(this);
		//设置语法
		QsciLexerPython* textLexer = new QsciLexerPython;//创建一个词法分析器
		textLexer->setAutoIndentStyle(QsciScintilla::AiMaintain);
		editor->setLexer(textLexer);//给QsciScintilla设置词法分析器

		//行号提示
		editor->setMarginType(0, QsciScintilla::NumberMargin);//设置编号为0的页边显示行号。
		editor->setMarginLineNumbers(0, true);//对该页边启用行号
		editor->setMarginWidth(0, 40);//设置页边宽度
		editor->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
		//代码提示
		QsciAPIs* apis = new QsciAPIs(textLexer);
		bool ret = apis->load("D:\\CTCRemaster\\CTCRemaster\\x64\\Debug\\ApiSets.txt");
		apis->prepare();
		editor->setAutoCompletionSource(QsciScintilla::AcsAll);   //设置源，自动补全所有地方出现的
		editor->setAutoCompletionCaseSensitivity(true);   //设置自动补全大小写敏感
		editor->setAutoCompletionThreshold(1);    //设置每输入一个字符就会出现自动补全的提示

		editor->setWrapMode(QsciScintilla::WrapMode::WrapNone); //文本自动换行模式
		//editor->setWrapVisualFlags(QsciScintilla::WrapFlagByText);

		editor->setEolMode(QsciScintilla::EolWindows); //微软风格换行符
		//editor->setEolVisibility(true);//显示换行符

		//indent
		editor->setIndentationsUseTabs(false);//false用表示用空格代替\t
		editor->setTabWidth(4);//\t宽度设为四个空格
		editor->setIndentationGuides(true);//用tab键缩进时，在缩进位置上显示一个竖点线，缩进有效，在字符串后加空格不显示
		editor->setIndentationWidth(0);//如果在行首部空格位置tab，缩进的宽度字符数，并且不会转换为空格
		editor->setAutoIndent(true);//换行后自动缩进
		editor->setBackspaceUnindents(true);
		editor->setTabIndents(true);//True如果行前空格数少于tabWidth，补齐空格数,False如果在文字前tab同true，如果在行首tab，则直接增加tabwidth个空格
		editor->setBraceMatching(QsciScintilla::SloppyBraceMatch);//括号匹配

		//current line color
		editor->setCaretWidth(2);//光标宽度，0表示不显示光标
		editor->setCaretForegroundColor(QColor("darkCyan"));  //光标颜色
		//selection color
		editor->setSelectionBackgroundColor(Qt::black);//选中文本背景色
		editor->setSelectionForegroundColor(Qt::white);//选中文本前景色

		editor->SendScintilla(QsciScintilla::SCI_SETCODEPAGE, QsciScintilla::SC_CP_UTF8);//设置编码为UTF-8
		QFont line_font;
		line_font.setFamily("微软雅黑");
		line_font.setPointSize(500);
		editor->setFont(line_font);//设置文本字体

		auto pLayout = new QVBoxLayout(this);
		QToolBar* toolBar = new QToolBar;
		toolBar->addAction(QIcon("icons/console/serach.png"), "",[=]() {});
		pLayout->addWidget(toolBar);
		pLayout->addWidget(editor);
		pLayout->setContentsMargins(0, 0, 0, 0);
	}

	~PythonCodeEditor()
	{

	}

	void setFile(const QString& filePath)
	{
		QFile file(filePath);
		if (file.open(QFile::ReadOnly | QFile::Text))
		{
			editor->setText(file.readAll());
		}
		//editor->setText("123");
	}
};

