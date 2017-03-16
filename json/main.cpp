#include <iostream>
#include <cstdlib>
#include "json.h"
#include "exception.h"
#include <fstream>
using namespace std;

int main()
{
	
	ifstream fin("test.json");
	string str;
	Json json(&fin);      //��ʼ����
	json.writeToStr(str); //��������ɹ�����ӡ������������json�ַ���ʧ���򱨳��쳣
	cout << str << endl;  
	cout << endl;
	string str1;
	json.getRoot()->writeToStr(str1);  //��ȡjsonԪ��
	cout << str1 << endl;	
	string str2;   //���ζ�ȡԪ��
	json.getRoot()->toDict()->getValue("key4")->toList()->getValue(1)->writeToStr(str2);
	cout << str2 << endl;

	/*
	Json json;
	JsonDict dict1;
	//����Ԫ��
	JsonValue value1(123.0);
	JsonValue value2(456.0);	
	JsonList value3;
	JsonValue val1(12.0);
	JsonValue val2(34.0);
	//����һ��json�ֵ䲢���ڲ�����һ���ֵ�
	JsonList list2;
	JsonValue value4(21312.0);
	JsonValue value5(2121.0);
	JsonDict dict2;
	list2.append(&value4);
	list2.append(&value5);
	dict2.setValue("try", &dict1);
	dict2.setValue("haha", &list2);

	value3.append(&val1);
	value3.append(&val2);
	//��Ԫ�ؼ������
	dict1.setValue("key1", &value1);
	dict1.setValue("key2", &value2);
	dict1.setValue("key3", &value3);
	//��dict2��Ϊ���ڵ�,��dict1�ض���
	json.setRoot(&dict1);
	json.setRoot(&dict2);
	//��ӡ�����json�ַ���
	string str;
	json.writeToStr(str);
	cout << str << endl;

	*/
	system("pause");
	return 0;
}