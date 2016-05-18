/*
 * Copyright 2009-2011 Cedric Priscal
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include	"xmlog.h"
#include	"xm_type.h"
#include	"message.h"
#include	"hisense.h"
#include	"air-dehumidifier_msg.h"
#include	"cmdanalysis.h"
static XM_Value xm_FS2value[]={		
		{"weak",0},
		{"strong",1},
		{"auto",2}
};

XM_Command xm_CSFS={//��������
	3,
	0,
	8,
	0,
	0,
	101,
	0,
	0,
	0,
	0,
	0,
	{
		{6,3,sizeof(xm_FS2value)/sizeof(xm_FS2value[0]),xm_FS2value,0,0,1,0},
		{7,1,0,NULL,0,0,1,1},
		{8,1,0,NULL,0,0,1,0}
	},
	{
	}
};

static XM_Value xm_MS2value[]={
		{"continue",0},
		{"normal",1},
		{"auto",2}		
};

XM_Command xm_CSMS={//����ģʽ����
	3,
	0,
	8,
	0,
	0,
	101,
	0,
	0,
	0,
	0,
	0,
	{
		{14,3,sizeof(xm_MS2value)/sizeof(xm_MS2value[0]),xm_MS2value,0,0,1,0},
		{15,1,0,NULL,0,0,1,1},
		{8,1,0,NULL,0,0,1,0}
	},
	{
	}
};

static XM_Value xm_DS2value[]={
		{"off",0},
		{"0.5h",1},
		{"1.0h",2},
		{"1.5h",3},
		{"2.0h",4},
		{"2.5h",5},
		{"3.0h",6},
		{"3.5h",7},
		{"4.0h",8},
		{"4.5h",9},
		{"5.0h",10},
		{"5.5h",11},
		{"6.0h",12},
		{"6.5h",13},
		{"7.0h",14},
		{"7.5h",15},
		{"8.0h",16},
		{"8.5h",17},
		{"9.0h",18},
		{"9.5h",19},
		{"10h",20},
		{"11h",21},
		{"12h",22},
		{"13h",23},
		{"14h",24},
		{"15h",25},
		{"16h",26},
		{"17h",27},
		{"18h",28},
		{"19h",29},
		{"20h",30},
		{"21h",31},
		{"22h",32},
		{"23h",33},
		{"24h",34}
};

XM_Command xm_CSDS={//��ʱ���ػ�
	4,
	0,
	8,
	0,
	0,
	101,
	0,
	0,
	0,
	0,
	0,
	{
		{22,6,sizeof(xm_DS2value)/sizeof(xm_DS2value[0]),xm_DS2value,0,0,1,0},
		{16,1,0,NULL,0,0,1,0},
		{23,1,0,NULL,0,0,1,1},
		{8,1,0,NULL,0,0,1,0}
	},
	{
	}
};

XM_Command xm_CSSD={//ʪ������
	3,
	0,
	8,
	0,
	0,
	101,
	0,
	0,
	0,
	0,
	0,
	{
		{30,7,0,NULL,0,0,1,0},
		{31,1,0,NULL,0,0,1,1},	
		{8,1,0,NULL,0,0,1,0}
	},
	{
	}
};


XM_Command xm_CSWD={//ʪ������
	3,
	0,
	8,
	0,
	0,
	101,
	0,
	0,
	0,
	0,
	0,
	{
		{38,7,0,NULL,0,0,1,0},
		{39,1,0,NULL,0,0,1,1},	
		{8,1,0,NULL,0,0,1,0}
	},
	{
	}
};


XM_Command xm_CSKJ={//��ͣ��ʪ��
	3,
	0,
	8,
	0,
	0,
	101,
	0,
	0,
	0,
	0,
	0,
	{
		{40,1,0,NULL,0,0,1,0},
		{41,1,0,NULL,0,0,1,1},
		{8,1,0,NULL,0,0,1,0}
	},
	{
	}
};


XM_Command xm_CSDJR={//����ȿ���
	3,
	0,
	8,
	0,
	0,
	101,
	0,
	0,
	0,
	0,
	0,
	{
		{42,1,0,NULL,0,0,1,0},
		{43,1,0,NULL,0,0,1,1},
		{8,1,0,NULL,0,0,1,0}
	},
	{
	}
};


XM_Command xm_CSSB={//ˮ�ÿ�ͣ����
	3,
	0,
	8,
	0,
	0,
	101,
	0,
	0,
	0,
	0,
	0,
	{
		{44,1,0,NULL,0,0,1,0},
		{45,1,0,NULL,0,0,1,1},
		{8,1,0,NULL,0,0,1,0},
	},
	{
	}
};


XM_Command xm_CSFNZ={//�����ӿ�ͣ����
	3,
	0,
	8,
	0,
	0,
	101,
	0,
	0,
	0,
	0,
	0,
	{
		{46,1,0,NULL,0,0,1,0},
		{47,1,0,NULL,0,0,1,1},
		{8,1,0,NULL,0,0,1,0},
	},
	{
	}
};

XM_Command xm_CSSBOX={//smartbox��һ���������������ܣ�
	9,
	0,
	8,
	0,
	0,
	101,
	0,
	0,
	0,
	0,
	0,
	{
		{40,1,0,NULL,0,0,1,0},//����
		{41,1,0,NULL,0,0,1,1},
		{14,3,sizeof(xm_MS2value)/sizeof(xm_MS2value[0]),xm_MS2value,0,0,1,0},//ģʽ
		{15,1,0,NULL,0,0,1,1},
		{6,3,sizeof(xm_FS2value)/sizeof(xm_FS2value[0]),xm_FS2value,0,0,1,0},//����
		{7,1,0,NULL,0,0,1,1},
		{30,7,0,NULL,0,0,1,0},//ʪ������
		{31,1,0,NULL,0,0,1,1},	
		{8,1,0,NULL,0,0,1,0}
	},
	{		
	}
};




XM_Command xm_CSZD={//״̬
	1,
	20,
	0,
	9,
	0,
	0,
	0,
	102,
	0,
	0,
	0,
	{
		{7,1,0,NULL,0,1,0,0}
	},
	{
		{6,3,sizeof(xm_FS2value)/sizeof(xm_FS2value[0]),xm_FS2value,0,1,0,0},//�������� 0
		{14,3,sizeof(xm_MS2value)/sizeof(xm_MS2value[0]),xm_MS2value,0,1,0,0},//����ģʽ���� 1
		{16,1,0,NULL,0,1,0,0},//��ʱ���ػ���Ч2
		{22,6,sizeof(xm_DS2value)/sizeof(xm_DS2value[0]),xm_DS2value,0,1,0,0},//��ʱ���ػ�3
		{31,8,0,NULL,0,1,0,0},//ʪ������4
		{39,8,0,NULL,0,1,0,0},//������趨�¶�5
		{47,8,0,NULL,0,1,0,0},//�����¶�6
		{48,1,0,NULL,0,1,0,0},//��ͣ��ʪ��7
		{49,1,0,NULL,0,1,0,0},//����ȿ���8
		{50,1,0,NULL,0,1,0,0},//ˮ�ÿ�ͣ����9
		{51,1,0,NULL,0,1,0,0},//�����ӿ�ͣ����10
		{52,1,0,NULL,0,1,0,0},//��������֮ǰ�з����Ͱ������ƹ�11
		{53,1,0,NULL,0,1,0,0},//��������֮ǰ�з�WIFI���ƹ�12
		{56,1,0,NULL,0,1,0,0},//���������澯13
		{57,1,0,NULL,0,1,0,0},//ʪ�ȴ���������14
		{58,1,0,NULL,0,1,0,0},//���´���������15
		{59,1,0,NULL,0,1,0,0},//���´���������16
		{60,1,0,NULL,0,1,0,0},//ˮ���澯17
		{61,1,0,NULL,0,1,0,0},//ˮ�ù���18
		{71,8,0,NULL,0,1,0,0}//ʵ��ʪ��19
	}
};



XM_Command xm_CSGN={//����
	0,
	18,
	0,
	0,
	6,
	0,
	0,
	102,
	64,
	0,
	0,
	{
	},
	{
		{4,1,0,NULL,0,1,0,0},//���ٿ�����״̬-�ǻ۷�0
		{5,1,0,NULL,0,1,0,0},//���ٿ�����״̬-�߷�1
		{6,1,0,NULL,0,1,0,0},//���ٿ�����״̬-�з�2
		{7,1,0,NULL,0,1,0,0},//���ٿ�����״̬-�ͷ�3
		{13,1,0,NULL,0,1,0,0},//����ģʽ״̬-��������ģʽ4
		{14,1,0,NULL,0,1,0,0},//����ģʽ״̬-��������ģʽ5
		{15,1,0,NULL,0,1,0,0},//����ģʽ״̬-�Զ�����ģʽ6
		{16,1,0,NULL,0,1,0,0},//����ģʽ���������1-��ͨ��ʱ����7
		{17,1,0,NULL,0,1,0,0},//����ģʽ���������1-����ȹ���8
		{18,1,0,NULL,0,1,0,0},//����ģʽ���������1=������¶�����9
		{19,1,0,NULL,0,1,0,0},//����ģʽ���������1-����ʪ������10
		{20,1,0,NULL,0,1,0,0},//����ģʽ���������1-ˮ�ÿ�ͣ����11
		{21,1,0,NULL,0,1,0,0},//����ģʽ���������1-�����ӿ�ͣ����12
		{22,1,0,NULL,0,1,0,0},//����ģʽ���������1-������⹦��13
		{23,1,0,NULL,0,1,0,0},//����ģʽ���������1-��ͣ������14
		{24,1,0,NULL,0,1,0,0},//EEPROM�ɸ�д����15
		{39,8,0,NULL,0,1,0,0},//101#-0#��7�ֽ�Ԥ��λ�Ŀ��ƹ���16
		{47,8,0,NULL,0,1,0,0}//101#-0#��8�ֽ�Ԥ��λ�Ŀ��ƹ���17
	}
};

XM_AT_RET at_cmd_ret_cs[]={
		{"CSZD",XM_SEND_QUERY,102,0,&xm_CSZD},
		{"CSGN",XM_SEND_QUERY,102,64,&xm_CSGN},
		{"CSSET",XM_SEND_SETTING,101,0,NULL}		
};


XM_AT_FUN at_cmd_cs[12]={
	{"CSFS",NULL,0,&xm_CSFS},//��������
	{"CSMS",NULL,0,&xm_CSMS},//����ģʽ����
	{"CSDS",NULL,0,&xm_CSDS},//��ʱ���ػ�
	{"CSSD",NULL,0,&xm_CSSD},//ʪ������
	{"CSWD",NULL,0,&xm_CSWD},//�¶�����
	{"CSKJ",NULL,0,&xm_CSKJ},//��ͣ������
	{"CSDJR",NULL,0,&xm_CSDJR},//����ȿ���
	{"CSSB",NULL,0,&xm_CSSB},//ˮ�ÿ�ͣ����
	{"CSFNZ",NULL,0,&xm_CSFNZ},//�����ӿ�ͣ����
	{"CSZD",NULL,0,&xm_CSZD},//״̬
	{"CSGN",NULL,0,&xm_CSGN},//����
	{"CSSBOX",NULL,0,&xm_CSSBOX}//smartbox��һ���������������ܣ�

};

