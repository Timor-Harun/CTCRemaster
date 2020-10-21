#pragma once

//QsciScintilla��ΪQWidget�Ŀؼ�����Ҫ��Ӹÿؼ���ͷ�ļ�
#include <Qsci/qsciscintilla.h>
//��python�﷨��Ϊ���ӣ����﷨��������ͷ�ļ�
#include <Qsci/qscilexerpython.h>
//���ô�����ʾ���ܣ�����QsciAPIs��ʵ��
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
		//�����﷨
		QsciLexerPython* textLexer = new QsciLexerPython;//����һ���ʷ�������
		textLexer->setAutoIndentStyle(QsciScintilla::AiMaintain);
		editor->setLexer(textLexer);//��QsciScintilla���ôʷ�������

		//�к���ʾ
		editor->setMarginType(0, QsciScintilla::NumberMargin);//���ñ��Ϊ0��ҳ����ʾ�кš�
		editor->setMarginLineNumbers(0, true);//�Ը�ҳ�������к�
		editor->setMarginWidth(0, 40);//����ҳ�߿��
		editor->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
		//������ʾ
		QsciAPIs* apis = new QsciAPIs(textLexer);
		bool ret = apis->load("D:\\CTCRemaster\\CTCRemaster\\x64\\Debug\\ApiSets.txt");
		apis->prepare();
		editor->setAutoCompletionSource(QsciScintilla::AcsAll);   //����Դ���Զ���ȫ���еط����ֵ�
		editor->setAutoCompletionCaseSensitivity(true);   //�����Զ���ȫ��Сд����
		editor->setAutoCompletionThreshold(1);    //����ÿ����һ���ַ��ͻ�����Զ���ȫ����ʾ

		editor->setWrapMode(QsciScintilla::WrapMode::WrapNone); //�ı��Զ�����ģʽ
		//editor->setWrapVisualFlags(QsciScintilla::WrapFlagByText);

		editor->setEolMode(QsciScintilla::EolWindows); //΢�����з�
		//editor->setEolVisibility(true);//��ʾ���з�

		//indent
		editor->setIndentationsUseTabs(false);//false�ñ�ʾ�ÿո����\t
		editor->setTabWidth(4);//\t�����Ϊ�ĸ��ո�
		editor->setIndentationGuides(true);//��tab������ʱ��������λ������ʾһ�������ߣ�������Ч�����ַ�����ӿո���ʾ
		editor->setIndentationWidth(0);//��������ײ��ո�λ��tab�������Ŀ���ַ��������Ҳ���ת��Ϊ�ո�
		editor->setAutoIndent(true);//���к��Զ�����
		editor->setBackspaceUnindents(true);
		editor->setTabIndents(true);//True�����ǰ�ո�������tabWidth������ո���,False���������ǰtabͬtrue�����������tab����ֱ������tabwidth���ո�
		editor->setBraceMatching(QsciScintilla::SloppyBraceMatch);//����ƥ��

		//current line color
		editor->setCaretWidth(2);//����ȣ�0��ʾ����ʾ���
		editor->setCaretForegroundColor(QColor("darkCyan"));  //�����ɫ
		//selection color
		editor->setSelectionBackgroundColor(Qt::black);//ѡ���ı�����ɫ
		editor->setSelectionForegroundColor(Qt::white);//ѡ���ı�ǰ��ɫ

		editor->SendScintilla(QsciScintilla::SCI_SETCODEPAGE, QsciScintilla::SC_CP_UTF8);//���ñ���ΪUTF-8
		QFont line_font;
		line_font.setFamily("΢���ź�");
		line_font.setPointSize(500);
		editor->setFont(line_font);//�����ı�����

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

