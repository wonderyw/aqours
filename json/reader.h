#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include "exception.h"
////////////////////////////////////////////////
/// @wonderyw  字符流读取类
////////////////////////////////////////////////
class Reader
{
private:
	std::string m_str;  ///< @wonderyw 获得需解析的字符序列
	int m_pos;          ///< @wonderyw 当前指向字符序列的位置
	int m_len;          ///< @wonderyw 字符序列长度
public:
	bool isEOF();     ///< @wonderyw 是否结束
	int getLine();    ///< @wonderyw 返回行号
	int getRow();     ///< @wonderyw 返回列号

	char readChar();  ///< @wonderyw 读取一个字符
	char peekChar();  ///< @wonderyw 预读取一个字符

	void ignoreSpace();  ///< @wonderyw 跳过空白字符

	/// @wonderyw 匹配一个字符
	/// @note  匹配一个字符，失败输出错误
	/// @param[in] ch 要匹配的字符
	/// @param[in] bIgnoreSpace 忽略空格
	void match(char ch, bool bIgnoreSpace);

	/// @wonderyw 匹配一个字符串
	/// @note  匹配一个字符串，失败输出错误
	/// @param[in] str 要匹配的字符串
	/// @param[in] bIgnoreSpace 忽略空格
	void match(std::string str, bool bIgnoreSpace);

	/// @wonderyw 尝试匹配一个字符
	/// @note  尝试匹配一个字符，失败输出错误
	/// @param[in] ch 要匹配的字符
	/// @param[in] bIgnoreSpace 忽略空格
	/// @param[in] bMatch 如果能匹配，是否匹配这个字符
	/// @return  true=可以匹配，false=匹配失败
	bool tryMatch(char ch, bool bIgnoreSpace, bool bMatch);

	/// @wonderyw 尝试匹配一个字符串
	/// @note  尝试匹配一个字符串，失败输出错误
	/// @param[in] str 要匹配的字符串
	/// @param[in] bIgnoreSpace 忽略空格
	/// @param[in] bMatch 如果能匹配，是否匹配这个字符
	/// @return  true=可以匹配，false=匹配失败
	bool tryMatch(std::string str, bool bIgnoreSpace, bool bMatch);
public:
	/// @wonderyw 从文本构造
	/// @param[in] srcText 要进行匹配的原始字符串
	Reader(const std::string& srcText);

	/// @wonderyw 从流构造
	/// @param[in] pStream 要进行匹配的原始数据流
	Reader(std::ifstream* pStream);
	~Reader();
};

