#pragma once
#ifndef UTILITY_H
#define UTILITY_H

#include <QString>
#include <QFileInfo>

namespace TimorHarun {
	namespace Utility {
		static QString getFileNamePrefix(const QString& pyFilePath)
		{
			//本质上是读取文件的名称，字符串分割
			QFileInfo fileInfo(pyFilePath);
			QString className = fileInfo.fileName();

			//最后一个斜杠的位置
			int backslashIndex = pyFilePath.lastIndexOf('/');
			int potIndex = pyFilePath.lastIndexOf('.');
			return pyFilePath.mid(backslashIndex + 1, potIndex - backslashIndex - 1);
		}

		static std::string stdstr(const QString&str)
		{
			return str.toStdString();
		}

		static const char* cstr(const QString& str)
		{
			return str.toStdString().c_str();
		}
	}
}

#endif

