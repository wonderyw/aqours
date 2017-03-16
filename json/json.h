#pragma once
#pragma once
////////////////////////////////////////////////////////////////////////////////
/// @file  Json.h
/// @wonderyw Json解析器
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include "reader.h"


////////////////////////////////////////////////////////////////////////////////
/// @wonderyw JSON元素类型
////////////////////////////////////////////////////////////////////////////////
enum JSONVALUETYPE
{
	JSONVALUETYPE_NULL,   ///< @wonderyw 空类型
	JSONVALUETYPE_BOOL,   ///< @wonderyw 逻辑类型
	JSONVALUETYPE_NUMBER, ///< @wonderyw 数字类型
	JSONVALUETYPE_STRING, ///< @wonderyw 字符串类型
	JSONVALUETYPE_LIST,   ///< @wonderyw 表类型
	JSONVALUETYPE_DICT,   ///< @wonderyw 字典类型
};

class JsonString;
class JsonList;
class JsonDict;

////////////////////////////////////////////////////////////////////////////////
/// @wonderyw JSON值
////////////////////////////////////////////////////////////////////////////////
class JsonValue
{
	friend class JsonString;
	friend class JsonList;
	friend class JsonDict;
	friend class Json;
protected:
	JSONVALUETYPE m_Type;  ///< @wonderyw JSON对象类型
	/// @wonderyw 数据域
	union
	{
		bool m_ValueBool;     ///< @wonderyw 逻辑型
		double m_ValueNumber; ///< @wonderyw 数字型
	};
public:
	/// @wonderyw      写到字符串
	/// @param[out] OutStr 输出的目的字符串
	virtual void writeToStr(std::string& OutStr);
public: //用于接口转换
	virtual JsonString* toString();   ///< @wonderyw 转换到字符串
	virtual JsonList* toList();       ///< @wonderyw 转换到数组
	virtual JsonDict* toDict();       ///< @wonderyw 转换到字典
public: //类型转换
	JSONVALUETYPE getType();       ///< @wonderyw 返回类型

	bool toNull();                 ///< @wonderyw 转换到NULL
	///< @note  true表示NULL，false表示非NULL
	bool toBool();                 ///< @wonderyw 转换到Bool
	///< @note  true表示true，false表示非false
	double toNumber();             ///< @wonderyw 到数字
	///< @wonderyw 非Number型用0表示
public: // 值类型操作，非值类型返回false
	bool setValue();                 ///< @wonderyw 设置为NULL
	///< @return 如果对象不是值类型，则返回假
	bool setValue(bool Value);		 ///< @wonderyw 设置为bool
	///< @return 如果对象不是值类型，则返回假
	bool setValue(double Value);     ///< @wonderyw 设置为数字
	///< @return 如果对象不是值类型，则返回假
public: // 用于手动创建
	JsonValue();                       ///< @wonderyw 创建为null值类型
	JsonValue(bool Value);             ///< @wonderyw 创建为bool值类型
	JsonValue(double Value);           ///< @wonderyw 创建为数值类型
	JsonValue(JSONVALUETYPE Type);     ///< @wonderyw 创建为String/List/Dict
	virtual ~JsonValue();
};

////////////////////////////////////////////////////////////////////////////////
/// @wonderyw JSON字符串
////////////////////////////////////////////////////////////////////////////////
class JsonString : public JsonValue
{
protected:
	std::string m_Str;   ///< @wonderyw 字符串字面值
public:
	virtual void writeToStr(std::string& OutStr);
public: //用于接口转换
	JsonString* toString();   ///< @wonderyw 转换到字符串
public:
	std::string getStr();           ///< @wonderyw 获得字符串
	void setStr(std::string Value); ///< @wonderyw 设置字符串
public:
	/// @wonderyw     构造函数
	/// @param[in] Value 字符串值
	JsonString(std::string Value);
	~JsonString();
};

////////////////////////////////////////////////////////////////////////////////
/// @wonderyw JSON数组
/// @note  JsonList将会负责销毁子对象
////////////////////////////////////////////////////////////////////////////////
class JsonList : public JsonValue
{
protected:
	std::vector<JsonValue*> m_ObjList;   ///< @wonderyw 内部数组
public:
	virtual void writeToStr(std::string& OutStr);
public: //用于接口转换
	JsonList* toList();       ///< @wonderyw 转换到数组

public:
	/// @wonderyw     获得对象
	/// @param[in] Index 索引
	/// @return    如果索引不存在返回NULL，否则返回对象指针
	JsonValue* getValue(int Index);

	/// @wonderyw     设置对象
	/// @param[in] Index 索引
	/// @param[in] pNew  对象指针
	/// @return    返回操作是否成功
	bool setValue(int Index, JsonValue* pNew);

	/// @wonderyw     往数组末端追加对象
	/// @param[in] pNew 对象指针
	void append(JsonValue* pNew);

	/// @wonderyw 清空
	void clear();

	/// @wonderyw 返回对象数量
	int getCount();
public:
	/// @wonderyw 构造函数
	JsonList();
	~JsonList();
};

////////////////////////////////////////////////////////////////////////////////
/// @wonderyw JSON字典
////////////////////////////////////////////////////////////////////////////////
class JsonDict : public JsonValue
{
protected:
	std::vector<std::string> m_ObjList;                      ///< @wonderyw 对象数组
	std::unordered_map<std::string, JsonValue*> m_Cache;  ///< @wonderyw 对象字典缓存
public:
	virtual void writeToStr(std::string& OutStr);
public: //用于接口转换
	JsonDict* toDict();       ///< @wonderyw 转换到字典
public:
	/// @wonderyw      返回对象
	/// @param[in]  Index 对象索引
	/// @param[out] pKeyOut 键
	/// @return     返回对象指针，若索引越界返回NULL
	JsonValue* getValue(int Index, std::string* pKeyOut = NULL);

	/// @wonderyw     返回对象
	/// @param[in] Name 对象键名
	/// @return    返回对象指针，若不存在对象返回NULL
	JsonValue* getValue(std::string Name);

	/// @wonderyw     设置对象
	/// @note      如果对象已经存在则会释放原有对象
	/// @param[in] Name 对象键名
	/// @param[in] pNew 对象指针
	void setValue(std::string Name, JsonValue* pNew);

	/// @wonderyw     是否包含对象
	/// @param[in] Name 对象的键名
	/// @return    true=包含对象，false=没包含对象
	bool contain(std::string Name);

	/// @wonderyw     移除对象
	/// @param[in] Index 对象键名
	/// @return    true=成功，false=失败
	bool remove(std::string Index);

	/// @wonderyw 清空
	void clear();

	/// @wonderyw 返回元素个数
	int getCount();
public:
	/// @wonderyw 构造函数
	JsonDict();
	~JsonDict();
};

////////////////////////////////////////////////////////////////////////////////
/// @wonderyw JSON解析器
/// @note  注意该解析器只会解析第一个元素。
////////////////////////////////////////////////////////////////////////////////
class Json
{
private:
	JsonValue* m_Root;  ///< @wonderyw 根节点
private: // 解析函数
	JsonValue* parseValue(Reader& Context);    ///< @wonderyw 解析一个值
	JsonValue* parseNumber(Reader& Context);   ///< @wonderyw 解析一个数值
	JsonString* parseString(Reader& Context);  ///< @wonderyw 解析一个字符串
	JsonList* parseList(Reader& Context);      ///< @wonderyw 解析一个表
	JsonDict* parseDict(Reader& Context);      ///< @wonderyw 解析一个字典
public:
	JsonValue* getRoot();              ///< @wonderyw 解析一个根节点
	void setRoot(JsonValue* pValue);   ///< @wonderyw 设置根节点

	void writeToStr(std::string& pOut); ///< @wonderyw 写到字符串
	void writeToStream(std::ofstream* pOut); ///< @wonderyw 写到流
public:
	Json();                           ///< @wonderyw 构造函数__一般结合setRoot使用
	Json(const std::string& Str);    ///< @wonderyw 从文本构造JSON
	Json(std::ifstream* pStream);         ///< @wonderyw 从流构造JSON
	~Json();
};
/// @}
