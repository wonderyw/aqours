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
	Json json(&fin);      //开始解析
	json.writeToStr(str); //如果解析成功，打印出解析出来的json字符，失败则报出异常
	cout << str << endl;  
	cout << endl;
	string str1;
	json.getRoot()->writeToStr(str1);  //读取json元素
	cout << str1 << endl;	
	string str2;   //依次读取元素
	json.getRoot()->toDict()->getValue("key4")->toList()->getValue(1)->writeToStr(str2);
	cout << str2 << endl;

	/*
	Json json;
	JsonDict dict1;
	//构造元素
	JsonValue value1(123.0);
	JsonValue value2(456.0);	
	JsonList value3;
	JsonValue val1(12.0);
	JsonValue val2(34.0);
	//构造一个json字典并且内部包含一个字典
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
	//把元素加入对象
	dict1.setValue("key1", &value1);
	dict1.setValue("key2", &value2);
	dict1.setValue("key3", &value3);
	//把dict2设为根节点,将dict1重定向
	json.setRoot(&dict1);
	json.setRoot(&dict2);
	//打印构造的json字符串
	string str;
	json.writeToStr(str);
	cout << str << endl;

	*/
	system("pause");
	return 0;
}