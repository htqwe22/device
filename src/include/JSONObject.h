#ifndef JSON_OBJECT__H
#define JSON_OBJECT__H

#include "cJSON.h"
#include <iostream>
#include <string>
using namespace std;

class JSONObject{
	cJSON *root;
public:
	/*c_string ,C++ string ����*/
	JSONObject(const string &jsStr);
	/*��������*/
	JSONObject(const JSONObject &in);
	
	~JSONObject();
    void clear();
	string toString()const;
	/*��ȡһ��key��Ӧ��intֵ*/
	int getNumber(const string key);
	/*��ȡһ��key��Ӧ��stringֵ*/
	string getString(const string key);
	/*���һ��int key*/
	void putNumber(const string key,int value);
	/*���һ��string key*/
	void putString(const string key,const string str);
	/*��JSON��ɾ��һ��key*/
	JSONObject& remove(const string key);
	/*���ظ�ֵ����*/
	JSONObject& operator = (const JSONObject &in);
    friend ostream& operator <<(ostream &os,JSONObject &obj);
};

#endif



