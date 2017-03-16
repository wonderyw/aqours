#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include "exception.h"
////////////////////////////////////////////////
/// @wonderyw  �ַ�����ȡ��
////////////////////////////////////////////////
class Reader
{
private:
	std::string m_str;  ///< @wonderyw �����������ַ�����
	int m_pos;          ///< @wonderyw ��ǰָ���ַ����е�λ��
	int m_len;          ///< @wonderyw �ַ����г���
public:
	bool isEOF();     ///< @wonderyw �Ƿ����
	int getLine();    ///< @wonderyw �����к�
	int getRow();     ///< @wonderyw �����к�

	char readChar();  ///< @wonderyw ��ȡһ���ַ�
	char peekChar();  ///< @wonderyw Ԥ��ȡһ���ַ�

	void ignoreSpace();  ///< @wonderyw �����հ��ַ�

	/// @wonderyw ƥ��һ���ַ�
	/// @note  ƥ��һ���ַ���ʧ���������
	/// @param[in] ch Ҫƥ����ַ�
	/// @param[in] bIgnoreSpace ���Կո�
	void match(char ch, bool bIgnoreSpace);

	/// @wonderyw ƥ��һ���ַ���
	/// @note  ƥ��һ���ַ�����ʧ���������
	/// @param[in] str Ҫƥ����ַ���
	/// @param[in] bIgnoreSpace ���Կո�
	void match(std::string str, bool bIgnoreSpace);

	/// @wonderyw ����ƥ��һ���ַ�
	/// @note  ����ƥ��һ���ַ���ʧ���������
	/// @param[in] ch Ҫƥ����ַ�
	/// @param[in] bIgnoreSpace ���Կո�
	/// @param[in] bMatch �����ƥ�䣬�Ƿ�ƥ������ַ�
	/// @return  true=����ƥ�䣬false=ƥ��ʧ��
	bool tryMatch(char ch, bool bIgnoreSpace, bool bMatch);

	/// @wonderyw ����ƥ��һ���ַ���
	/// @note  ����ƥ��һ���ַ�����ʧ���������
	/// @param[in] str Ҫƥ����ַ���
	/// @param[in] bIgnoreSpace ���Կո�
	/// @param[in] bMatch �����ƥ�䣬�Ƿ�ƥ������ַ�
	/// @return  true=����ƥ�䣬false=ƥ��ʧ��
	bool tryMatch(std::string str, bool bIgnoreSpace, bool bMatch);
public:
	/// @wonderyw ���ı�����
	/// @param[in] srcText Ҫ����ƥ���ԭʼ�ַ���
	Reader(const std::string& srcText);

	/// @wonderyw ��������
	/// @param[in] pStream Ҫ����ƥ���ԭʼ������
	Reader(std::ifstream* pStream);
	~Reader();
};

