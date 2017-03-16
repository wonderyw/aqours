#pragma once
#include <string>
//////////////////////////////////////////////////////
/// @wonderyw �쳣�������
/// @note  �κ��쳣�Ӹ�������
///////////////////////////////////////////////////////
class Exception
{
protected:
	int m_Time;            ///< @wonderyw ��¼�쳣�¼���
	std::string m_ExcpSrc; ///< @wonderyw ��¼�쳣��Դ
	std::string m_ExcpDesc;///< @wonderyw ��¼�쳣��Ϣ
public:
	int getTime() const;           ///< @wonderyw ����쳣ʱ��
	std::string getSrc() const;    ///< @wonderyw ����쳣��Դ
	std::string getDesc() const;   ///< @wonderyw ����쳣��Ϣ
public:
	/// @wonderyw �չ��캯��
	Exception();
	/// @wonderyw      ���캯��
	/// @warning    �������ó���512���ַ�
	/// @param[in] Src       �쳣Դ
	/// @param[in] DescFmt   �쳣��ʽ
	Exception(std::string Src, const char* DescFmt, ...);
	Exception(const Exception& Org);
	~Exception();
};


//////////////////////////////////////////////////////////
/// @wonderyw   json�����쳣
/// @note    ������Exception,���������ʷ�����
//////////////////////////////////////////////////////////
class ReaderException :public Exception
{
private:
	int m_Line;    ///< @wonderyw �����쳣��������
	int m_Row;     ///< @wonderyw �洢�쳣��������
public:
	int getLine();   ///< @wonderyw ����쳣��������
	int getRow();    ///< @wonderyw ����쳣��������
public:
	/// @wonderyw             ���캯��
	/// @note              ���캯�����Զ����кź��к���ӵ�Desc�ֶ�
	/// @param[in] Src     �쳣Դ
	/// @param[in] Desc    �쳣����
	/// @param[in] Line    �쳣�������к�
	/// @param[in] Row     �쳣��������
	ReaderException(std::string Src, const char* Desc, int Line, int Row);
	~ReaderException();
};
