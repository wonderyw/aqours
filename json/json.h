#pragma once
#pragma once
////////////////////////////////////////////////////////////////////////////////
/// @file  Json.h
/// @wonderyw Json������
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include "reader.h"


////////////////////////////////////////////////////////////////////////////////
/// @wonderyw JSONԪ������
////////////////////////////////////////////////////////////////////////////////
enum JSONVALUETYPE
{
	JSONVALUETYPE_NULL,   ///< @wonderyw ������
	JSONVALUETYPE_BOOL,   ///< @wonderyw �߼�����
	JSONVALUETYPE_NUMBER, ///< @wonderyw ��������
	JSONVALUETYPE_STRING, ///< @wonderyw �ַ�������
	JSONVALUETYPE_LIST,   ///< @wonderyw ������
	JSONVALUETYPE_DICT,   ///< @wonderyw �ֵ�����
};

class JsonString;
class JsonList;
class JsonDict;

////////////////////////////////////////////////////////////////////////////////
/// @wonderyw JSONֵ
////////////////////////////////////////////////////////////////////////////////
class JsonValue
{
	friend class JsonString;
	friend class JsonList;
	friend class JsonDict;
	friend class Json;
protected:
	JSONVALUETYPE m_Type;  ///< @wonderyw JSON��������
	/// @wonderyw ������
	union
	{
		bool m_ValueBool;     ///< @wonderyw �߼���
		double m_ValueNumber; ///< @wonderyw ������
	};
public:
	/// @wonderyw      д���ַ���
	/// @param[out] OutStr �����Ŀ���ַ���
	virtual void writeToStr(std::string& OutStr);
public: //���ڽӿ�ת��
	virtual JsonString* toString();   ///< @wonderyw ת�����ַ���
	virtual JsonList* toList();       ///< @wonderyw ת��������
	virtual JsonDict* toDict();       ///< @wonderyw ת�����ֵ�
public: //����ת��
	JSONVALUETYPE getType();       ///< @wonderyw ��������

	bool toNull();                 ///< @wonderyw ת����NULL
	///< @note  true��ʾNULL��false��ʾ��NULL
	bool toBool();                 ///< @wonderyw ת����Bool
	///< @note  true��ʾtrue��false��ʾ��false
	double toNumber();             ///< @wonderyw ������
	///< @wonderyw ��Number����0��ʾ
public: // ֵ���Ͳ�������ֵ���ͷ���false
	bool setValue();                 ///< @wonderyw ����ΪNULL
	///< @return ���������ֵ���ͣ��򷵻ؼ�
	bool setValue(bool Value);		 ///< @wonderyw ����Ϊbool
	///< @return ���������ֵ���ͣ��򷵻ؼ�
	bool setValue(double Value);     ///< @wonderyw ����Ϊ����
	///< @return ���������ֵ���ͣ��򷵻ؼ�
public: // �����ֶ�����
	JsonValue();                       ///< @wonderyw ����Ϊnullֵ����
	JsonValue(bool Value);             ///< @wonderyw ����Ϊboolֵ����
	JsonValue(double Value);           ///< @wonderyw ����Ϊ��ֵ����
	JsonValue(JSONVALUETYPE Type);     ///< @wonderyw ����ΪString/List/Dict
	virtual ~JsonValue();
};

////////////////////////////////////////////////////////////////////////////////
/// @wonderyw JSON�ַ���
////////////////////////////////////////////////////////////////////////////////
class JsonString : public JsonValue
{
protected:
	std::string m_Str;   ///< @wonderyw �ַ�������ֵ
public:
	virtual void writeToStr(std::string& OutStr);
public: //���ڽӿ�ת��
	JsonString* toString();   ///< @wonderyw ת�����ַ���
public:
	std::string getStr();           ///< @wonderyw ����ַ���
	void setStr(std::string Value); ///< @wonderyw �����ַ���
public:
	/// @wonderyw     ���캯��
	/// @param[in] Value �ַ���ֵ
	JsonString(std::string Value);
	~JsonString();
};

////////////////////////////////////////////////////////////////////////////////
/// @wonderyw JSON����
/// @note  JsonList���Ḻ�������Ӷ���
////////////////////////////////////////////////////////////////////////////////
class JsonList : public JsonValue
{
protected:
	std::vector<JsonValue*> m_ObjList;   ///< @wonderyw �ڲ�����
public:
	virtual void writeToStr(std::string& OutStr);
public: //���ڽӿ�ת��
	JsonList* toList();       ///< @wonderyw ת��������

public:
	/// @wonderyw     ��ö���
	/// @param[in] Index ����
	/// @return    ������������ڷ���NULL�����򷵻ض���ָ��
	JsonValue* getValue(int Index);

	/// @wonderyw     ���ö���
	/// @param[in] Index ����
	/// @param[in] pNew  ����ָ��
	/// @return    ���ز����Ƿ�ɹ�
	bool setValue(int Index, JsonValue* pNew);

	/// @wonderyw     ������ĩ��׷�Ӷ���
	/// @param[in] pNew ����ָ��
	void append(JsonValue* pNew);

	/// @wonderyw ���
	void clear();

	/// @wonderyw ���ض�������
	int getCount();
public:
	/// @wonderyw ���캯��
	JsonList();
	~JsonList();
};

////////////////////////////////////////////////////////////////////////////////
/// @wonderyw JSON�ֵ�
////////////////////////////////////////////////////////////////////////////////
class JsonDict : public JsonValue
{
protected:
	std::vector<std::string> m_ObjList;                      ///< @wonderyw ��������
	std::unordered_map<std::string, JsonValue*> m_Cache;  ///< @wonderyw �����ֵ仺��
public:
	virtual void writeToStr(std::string& OutStr);
public: //���ڽӿ�ת��
	JsonDict* toDict();       ///< @wonderyw ת�����ֵ�
public:
	/// @wonderyw      ���ض���
	/// @param[in]  Index ��������
	/// @param[out] pKeyOut ��
	/// @return     ���ض���ָ�룬������Խ�緵��NULL
	JsonValue* getValue(int Index, std::string* pKeyOut = NULL);

	/// @wonderyw     ���ض���
	/// @param[in] Name �������
	/// @return    ���ض���ָ�룬�������ڶ��󷵻�NULL
	JsonValue* getValue(std::string Name);

	/// @wonderyw     ���ö���
	/// @note      ��������Ѿ���������ͷ�ԭ�ж���
	/// @param[in] Name �������
	/// @param[in] pNew ����ָ��
	void setValue(std::string Name, JsonValue* pNew);

	/// @wonderyw     �Ƿ��������
	/// @param[in] Name ����ļ���
	/// @return    true=��������false=û��������
	bool contain(std::string Name);

	/// @wonderyw     �Ƴ�����
	/// @param[in] Index �������
	/// @return    true=�ɹ���false=ʧ��
	bool remove(std::string Index);

	/// @wonderyw ���
	void clear();

	/// @wonderyw ����Ԫ�ظ���
	int getCount();
public:
	/// @wonderyw ���캯��
	JsonDict();
	~JsonDict();
};

////////////////////////////////////////////////////////////////////////////////
/// @wonderyw JSON������
/// @note  ע��ý�����ֻ�������һ��Ԫ�ء�
////////////////////////////////////////////////////////////////////////////////
class Json
{
private:
	JsonValue* m_Root;  ///< @wonderyw ���ڵ�
private: // ��������
	JsonValue* parseValue(Reader& Context);    ///< @wonderyw ����һ��ֵ
	JsonValue* parseNumber(Reader& Context);   ///< @wonderyw ����һ����ֵ
	JsonString* parseString(Reader& Context);  ///< @wonderyw ����һ���ַ���
	JsonList* parseList(Reader& Context);      ///< @wonderyw ����һ����
	JsonDict* parseDict(Reader& Context);      ///< @wonderyw ����һ���ֵ�
public:
	JsonValue* getRoot();              ///< @wonderyw ����һ�����ڵ�
	void setRoot(JsonValue* pValue);   ///< @wonderyw ���ø��ڵ�

	void writeToStr(std::string& pOut); ///< @wonderyw д���ַ���
	void writeToStream(std::ofstream* pOut); ///< @wonderyw д����
public:
	Json();                           ///< @wonderyw ���캯��__һ����setRootʹ��
	Json(const std::string& Str);    ///< @wonderyw ���ı�����JSON
	Json(std::ifstream* pStream);         ///< @wonderyw ��������JSON
	~Json();
};
/// @}
