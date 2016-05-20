/*
 * Author Kevin He
 * Created on 18th May,2016
 */

#ifndef JSON_OBJECT__H
#define JSON_OBJECT__H

#include "cJSON.h"
#include <iostream>
#include <string>
using namespace std;

#define NUMERROR -0xaa5555aa
class JSONObject{
	cJSON *root;
    string jsString;
    void flushString();
public:
    JSONObject();
	/*c_string ,C++ string ����*/
	JSONObject(const string &jsStr);
	/*��������*/
	JSONObject(const JSONObject &in);
	
	~JSONObject();
    void clear();
    const string& toString()const;
	/*��ȡһ��key��Ӧ��intֵ*/
	int getNumber(const string &key);
	/*��ȡһ��key��Ӧ��stringֵ*/
	string getString(const string &key);
	/*���һ��int key*/
	JSONObject& putNumber(const string &key,int value);
	/*���һ��string key*/
	JSONObject& putString(const string &key,const string &str);
	/*��JSON��ɾ��һ��key*/
	JSONObject& remove(const string &key);
	/*���ظ�ֵ����*/
	JSONObject& operator = (const JSONObject &in);
    JSONObject& operator = (const string  &jsStr);
    friend ostream& operator <<(ostream &os,JSONObject &obj);
};

#endif



