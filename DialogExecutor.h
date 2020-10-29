#pragma once
#include <QObject>
#include <vector>
#include <string>

class DialogExecutor:public QObject
{
	Q_OBJECT
private:
	std::vector<std::pair<std::string, std::string>> dialogNames;
	std::vector<bool> isDialogModes;

	static DialogExecutor* instance;
Q_SIGNALS:
	void execDialogSignals(const std::string &dialogFilePath);
public:
	void appendDialog(const std::string& dialogName, const std::string& dialogFilePath,bool dialogMode)
	{
		dialogNames.push_back(std::make_pair(dialogName, dialogFilePath));
		isDialogModes.push_back(dialogMode);
	}

	int getDialogIndex(const std::string& dialogName)
	{
		for (int i = 0;i<dialogNames.size();i++)
		{
			if (dialogNames[i].first == dialogName)
				return i;
		}
		return -1;
	}
	
	void exec(int index)
	{
		assert(index != -1);
		emit execDialogSignals(dialogNames[index].second);
	}
public:
	DialogExecutor() {}
	~DialogExecutor() { instance = nullptr; }

	static DialogExecutor* getInstance() 
	{
		if (instance == nullptr)
			instance = new DialogExecutor;
		return instance;
	}

	Q_DISABLE_COPY(DialogExecutor);
};