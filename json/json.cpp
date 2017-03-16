#define _CRT_SECURE_NO_WARNINGS
#include "json.h"
#include <cstdlib>

std::string doubleToStr(double num)
{
	char buf[20];
	memset(buf, 0, sizeof(buf));
	_itoa(num, buf, 10);
	return buf;
}

////////////////////////////////////////////
/// @wonderyw JSON值
////////////////////////////////////////////
JsonValue::JsonValue()
	:m_Type(JSONVALUETYPE_NULL), m_ValueNumber(0.)
{}

JsonValue::JsonValue(bool Value)   ///< @wonderyw 创建为bool类型
	: m_Type(JSONVALUETYPE_BOOL), m_ValueBool(Value)
{}

JsonValue::JsonValue(double Value) ///< @wonderyw 创建为数值类型
	: m_Type(JSONVALUETYPE_NUMBER), m_ValueNumber(Value)
{}


JsonValue::JsonValue(JSONVALUETYPE Type) ///< @wonderyw 创建为String/List/Dict
	: m_Type(Type)
{}

JsonValue::~JsonValue()
{}


void JsonValue::writeToStr(std::string& OutStr)
{
	switch (m_Type)
	{
	case JSONVALUETYPE_NULL:
		OutStr += "null";
		break;
	case JSONVALUETYPE_BOOL:
		if (m_ValueBool)
			OutStr += "true";
		else
			OutStr += "false";
		break;
	case JSONVALUETYPE_NUMBER:
		OutStr += doubleToStr(m_ValueNumber);
		break;
	default:
		std::cout << "JsonValue::writeToStr Error!" << std::endl;
	}
}

JsonString* JsonValue::toString()   ///< @wonderyw 转换到字符串
{
	return nullptr;
}

JsonList* JsonValue::toList()       ///< @wonderyw 转换到数组
{
	return nullptr;
}

JsonDict* JsonValue::toDict()       ///< @wonderyw 转换到字典
{
	return nullptr;
}

JSONVALUETYPE JsonValue::getType()
{
	return m_Type;
}

bool JsonValue::toNull()
{
	return (m_Type == JSONVALUETYPE_NULL);
}

bool JsonValue::toBool()
{
	if (m_Type != JSONVALUETYPE_BOOL)
		return false;
	return m_ValueBool;
}

double JsonValue::toNumber()
{
	if (m_Type != JSONVALUETYPE_NUMBER)
		return false;
	return m_ValueNumber;
}

bool JsonValue::setValue()
{
	if (m_Type != JSONVALUETYPE_NULL &&
		m_Type != JSONVALUETYPE_BOOL &&
		m_Type != JSONVALUETYPE_NUMBER)
	{
		return false;
	}
	m_Type = JSONVALUETYPE_NULL;
	return true;
}

bool JsonValue::setValue(bool Value)
{

	if (m_Type != JSONVALUETYPE_NULL &&
		m_Type != JSONVALUETYPE_BOOL &&
		m_Type != JSONVALUETYPE_NUMBER)
	{
		return false;
	}
	m_Type = JSONVALUETYPE_BOOL;
	m_ValueNumber = Value;
	return true;
}

bool JsonValue::setValue(double Value)
{

	if (m_Type != JSONVALUETYPE_NULL &&
		m_Type != JSONVALUETYPE_BOOL &&
		m_Type != JSONVALUETYPE_NUMBER)
	{
		return false;
	}
	m_Type = JSONVALUETYPE_NUMBER;
	m_ValueBool = Value;
	return true;
}

///////////////////////////////////////////////////////////
JsonString::JsonString(std::string Value)
	:JsonValue(JSONVALUETYPE_STRING), m_Str(Value)
{}

JsonString::~JsonString()
{}

void JsonString::writeToStr(std::string& OutStr)
{
	OutStr += "\"";
	for (int i = 0; i < m_Str.size(); ++i)
	{
		switch (m_Str[i])
		{
		case '"':
			OutStr += "\"";
			break;
		case '\\':
			OutStr += "\\";
			break;
		case '/':
			OutStr += "/";
			break;
		case '\b':
			OutStr += "\b";
			break;
		case '\f':
			OutStr += "\f";
			break;
		case '\n':
			OutStr += "\n";
			break;
		case '\r':
			OutStr += "\r";
			break;
		case '\t':
			OutStr += "\t";
			break;
		default:
			OutStr += m_Str[i];
			break;
		}
	}
	OutStr += "\"";
}

JsonString* JsonString::toString()           ///< @wonderyw 获得字符串
{
	return nullptr;
}


std::string JsonString::getStr()           ///< @wonderyw 获得字符串
{
	return m_Str;
}

void JsonString::setStr(std::string Value) ///< @wonderyw 设置字符串
{
	m_Str = Value;
}

/////////////////////////////////////////////////////
JsonList::JsonList()
	:JsonValue(JSONVALUETYPE_LIST)
{}

JsonList::~JsonList()
{
	clear();
}

void JsonList::writeToStr(std::string& OutStr)
{
	OutStr += "[ ";
	for (int i = 0; i < m_ObjList.size(); ++i)
	{
		m_ObjList[i]->writeToStr(OutStr);

		if (i != m_ObjList.size() - 1)
			OutStr += ", ";
	}
	OutStr += " ]";
}

JsonList* JsonList::toList()
{
	return this;
}

JsonValue* JsonList::getValue(int Index)
{
	if (Index >= getCount())
		return nullptr;
	return m_ObjList[Index];
}

bool JsonList::setValue(int Index, JsonValue* pNew)
{
	if (Index >= getCount())
		return false;
	delete m_ObjList[Index];
	m_ObjList[Index] = pNew;
	return true;
}

/// @wonderyw     往数组末端追加对象
/// @param[in] pNew对象指针
void JsonList::append(JsonValue* pNew)
{
	if (pNew)
		m_ObjList.push_back(pNew);
}

/// @wonderyw 清空
void JsonList::clear()
{
	
	std::vector<JsonValue*>::iterator i = m_ObjList.begin();
	/*
	while (i != m_ObjList.end())
	{
		if (*i != NULL) 
		{
			delete (*i);
			*i = nullptr;
		}
		++i;
	}
	*/
	
	
	m_ObjList.clear();
}

/// @wonderyw 返回对象数量
int JsonList::getCount()
{
	return m_ObjList.size();
}


//////////////////////////////////////////////////////
/// @wonderyw JSON字典
//////////////////////////////////////////////////////

/// @wonderyw 构造函数
JsonDict::JsonDict()
	:JsonValue(JSONVALUETYPE_DICT)
{}

JsonDict::~JsonDict()
{
	clear();
}

void JsonDict::writeToStr(std::string& OutStr)
{
	OutStr += "{";
	for (int i = 0; i < m_ObjList.size(); ++i)
	{
		JsonValue* pObj = m_Cache[m_ObjList[i]];
		OutStr += "\"";
		OutStr += m_ObjList[i];
		OutStr += "\":";
		pObj->writeToStr(OutStr);

		if (i != m_ObjList.size() - 1)
			OutStr += ", ";
	}
	OutStr += " }";
}

JsonDict* JsonDict::toDict()
{
	return this;
}

JsonValue* JsonDict::getValue(int Index, std::string* pKeyOut)
{
	if (Index > getCount())
		return nullptr;
	else
	{
		if (pKeyOut)
			*pKeyOut = m_ObjList[Index];
		return m_Cache[m_ObjList[Index]];
	}
}

JsonValue* JsonDict::getValue(std::string Name)
{
	if (!contain(Name))
		return nullptr;
	else
		return m_Cache[Name];
}

void JsonDict::setValue(std::string Name, JsonValue* pNew)
{
	if (contain(Name))
	{
		remove(Name);
	}
	m_ObjList.push_back(Name);
	m_Cache[Name] = pNew;
}


bool JsonDict::contain(std::string Name)
{
	return m_Cache.find(Name) != m_Cache.end();
}

bool JsonDict::remove(std::string Name)
{
	if (!contain(Name))
		return false;

	std::vector<std::string>::iterator i = m_ObjList.begin();

	while (i != m_ObjList.end())
	{
		if ((*i) == Name)
		{
			m_ObjList.erase(i);
			break;
		}
		++i;
	}

	std::unordered_map<std::string, JsonValue*>::iterator j = m_Cache.find(Name);
	delete  j->second;
	m_Cache.erase(j);
	return true;
}

/// @wonderyw 清空
void JsonDict::clear()
{
	/*
	std::unordered_map<std::string, JsonValue*>::iterator j = m_Cache.begin();
	while (j != m_Cache.end())
	{
		delete (j->second);
		j++;
	}
	*/
	m_Cache.clear();
	m_ObjList.clear();
}

/// @wonderyw 返回元素个数
int JsonDict::getCount()
{
	return m_ObjList.size();
}

//////////////////////////////////////////////////////////////////////
Json::Json()                        ///< @wonderyw 构造函数
	:m_Root(nullptr)
{
}

Json::Json(const std::string& Str)  ///< @wonderyw 从文本构造JSON
	: m_Root(nullptr)
{
	Reader tmpReader(Str);
	m_Root = parseValue(tmpReader);
}

Json::Json(std::ifstream* pStream)  ///< @wonderyw 从流构造 JSON
{
	Reader tmpReader(pStream);
	m_Root = parseValue(tmpReader);

}

Json::~Json()
{
//	delete m_Root;
}

JsonValue* Json::parseValue(Reader& Context)    ///< @wonderyw 解析一个值
{
	JsonValue* tRet = nullptr;

	Context.ignoreSpace();///< @wonderyw 跳过开头空格
	char tChar = Context.peekChar();
	switch (tChar)
	{
	case '{':
		tRet = parseDict(Context);
		break;
	case '[':
		tRet = parseList(Context);
		break;
	case '"':
		tRet = parseString(Context);
		break;
	case 't':
	{
		Context.match("true", false);
		tRet = new JsonValue(true);
	}
		break;
	case 'f':
	{
		Context.match("false", false);
		tRet = new JsonValue(false);
	}
		break;
	case 'n':
	{
		Context.match("null", false);
		tRet = new JsonValue();
	}
		break;
	default:
		if (tChar == '-' || iswdigit(tChar))
		{
			tRet = parseNumber(Context);
		}
		else
			throw ReaderException("Json::parseValue", "Unexpected char.", Context.getLine(), Context.getRow());
		break;
	}
	return tRet;
}

JsonValue* Json::parseNumber(Reader& Context)   ///< @wonderyw 解析一个数值
{
	std::string tRet;
	Context.ignoreSpace();

	char tChar = Context.peekChar();
	while (isdigit(tChar) || tChar == '-' || tChar == '.' || tChar == 'E' || tChar == 'e')
	{
		Context.readChar();

		tRet += tChar;

		if (Context.isEOF())
			break;
		else
			tChar = Context.peekChar();
	}
	return new JsonValue(atof(tRet.c_str()));
}

JsonString* Json::parseString(Reader& Context)  ///< @wonderyw 解析一个字符串
{
	std::string tRet;
	Context.match('"', true);
	char tChar;
	while ((tChar = Context.readChar()) != '"')
	{
		if (iscntrl(tChar))
		{
			throw ReaderException("Json::parseString", "Unexpected char.", Context.getLine(), Context.getRow());
		}

		if (tChar == '\\')
		{
			tChar = Context.readChar();
			switch (tChar)
			{
			case '"':
				tRet += "\"";
				break;
			case '\\':
				tRet += "\\";
				break;
			case '/':
				tRet += "/";
				break;
			case 'b':
				tRet += "\b";
				break;
			case 'f':
				tRet += "\f";
				break;
			case 'n':
				tRet += "\n";
				break;
			case 'r':
				tRet += "\r";
				break;
			case 't':
				tRet += "\t";
				break;
			case 'u':
				throw ReaderException("Json::parseString", "Unexpected char.", Context.getLine(), Context.getRow());
				break;
			default:
			{
				throw ReaderException("Json::parseString", "Unexpected char.", Context.getLine(), Context.getRow());
				break;
			}
			}
		}
		else
		{
			tRet += tChar;
		}
	}
	return new JsonString(tRet.c_str());
}

JsonList* Json::parseList(Reader& Context)      ///< @wonderyw 解析一个表
{
	JsonList* tRet = new JsonList();
	Context.match('[', true);
	while (1)
	{
		if (Context.tryMatch(']', true, true))
			break;

		JsonValue* tValue = nullptr;
		try
		{
			tValue = parseValue(Context);
		}
		catch (ReaderException&)
		{
			delete tRet;
			throw;
		}


		tRet->append(tValue);

		if (Context.tryMatch(',', true, true))
			continue;
	}
	return tRet;
}

JsonDict* Json::parseDict(Reader& Context)      ///< @wonderyw 解析一个字典
{
	JsonDict* tRet = new JsonDict();

	Context.match('{', true);

	while (1)
	{
		if (Context.tryMatch('}', true, true))
			break;

		//解析键名
		JsonString* tKey = nullptr;

		try
		{
			tKey = parseString(Context);
		}
		catch (ReaderException&)
		{
			delete tRet;
			throw;
		}

		Context.match(':', true);

		//解析键值
		JsonValue* tValue = nullptr;

		try
		{
			tValue = parseValue(Context);
		}
		catch (ReaderException&)
		{
			delete tRet;
			delete tKey;
			throw;
		}
		// 追加
		tRet->setValue(tKey->getStr(), tValue);

		delete tKey;

		if (Context.tryMatch(',', true, true))
			continue;
	}
	return tRet;
}

JsonValue* Json::getRoot()              ///< @wonderyw 解析一个根节点
{
	return m_Root;
}

void Json::setRoot(JsonValue* pValue)   ///< @wonderyw 设置根节点
{
	//m_Root并没有通过new在堆上分配空间，因此m_Root仅仅是一个在栈中指向已有空间的指针，无需下面的delete，若有则会析构错误
//	if (m_Root != NULL)
//		delete m_Root;
	m_Root = pValue;
}

void Json::writeToStr(std::string& pOut)       ///< @wonderyw 写到字符串
{
	if (m_Root)
		m_Root->writeToStr(pOut);
}

void Json::writeToStream(std::ofstream* pOut)  ///< @wonderyw 写到流
{
	std::string tOutStr;
	if (m_Root)
		m_Root->writeToStr(tOutStr);

	(*pOut) << tOutStr << std::endl;
}

