#pragma once
#include <string>
//////////////////////////////////////////////////////
/// @wonderyw 异常处理基类
/// @note  任何异常从该类派生
///////////////////////////////////////////////////////
class Exception
{
protected:
	int m_Time;            ///< @wonderyw 记录异常事件戳
	std::string m_ExcpSrc; ///< @wonderyw 记录异常来源
	std::string m_ExcpDesc;///< @wonderyw 记录异常信息
public:
	int getTime() const;           ///< @wonderyw 获得异常时间
	std::string getSrc() const;    ///< @wonderyw 获得异常来源
	std::string getDesc() const;   ///< @wonderyw 获得异常信息
public:
	/// @wonderyw 空构造函数
	Exception();
	/// @wonderyw      构造函数
	/// @warning    描述不得超过512个字符
	/// @param[in] Src       异常源
	/// @param[in] DescFmt   异常格式
	Exception(std::string Src, const char* DescFmt, ...);
	Exception(const Exception& Org);
	~Exception();
};


//////////////////////////////////////////////////////////
/// @wonderyw   json解析异常
/// @note    派生自Exception,用来描述词法错误
//////////////////////////////////////////////////////////
class ReaderException :public Exception
{
private:
	int m_Line;    ///< @wonderyw 储存异常产生的行
	int m_Row;     ///< @wonderyw 存储异常产生的列
public:
	int getLine();   ///< @wonderyw 获得异常产生的行
	int getRow();    ///< @wonderyw 获得异常产生的列
public:
	/// @wonderyw             构造函数
	/// @note              构造函数会自动把行号和列号添加到Desc字段
	/// @param[in] Src     异常源
	/// @param[in] Desc    异常描述
	/// @param[in] Line    异常产生的行号
	/// @param[in] Row     异常产生的列
	ReaderException(std::string Src, const char* Desc, int Line, int Row);
	~ReaderException();
};
