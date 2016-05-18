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
#include	"air-cleansing_msg.h"
#include	"cmdanalysis.h"
static XM_Value xm_FS2value[]={
		{"weak",0},
		{"middle",1},
		{"strong",2},
		{"clear",3},
		{"auto",4},
		{"auto",5},
		{"auto",6},
		{"auto",7}
};

XM_Command xm_JHFS={//�����ٶ�����
	3,
	0,
	6,
	0,
	0,
	101,
	0,
	0,
	0,
	0,
	0,
	{
		{6,7,sizeof(xm_FS2value)/sizeof(xm_FS2value[0]),xm_FS2value,0,0,1,0},
		{7,1,0,NULL,0,0,1,1},
		{8,1,0,NULL,0,0,1,0}
	},
	{
	}
};

static XM_Value xm_MS2value[]={
		{"cleardust",0},
		{"clearsmell",1},
		{"smart",2},
		{"mute",3},
		{"sleep",4},
};

XM_Command xm_JHMS={//����ģʽ����
	3,
	0,
	6,
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
		{"10h",29},
		{"20h",30},
		{"21h",31},
		{"22h",32},
		{"23h",33}
};

XM_Command xm_JHDS={//��ʱ���ػ�
	4,
	0,
	6,
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
		{23,1,0,NULL,0,0,1,1},
		{16,1,0,NULL,0,0,1,0},
		{8,1,0,NULL,0,0,1,0}
	
	},
	{
	}
};

XM_Command xm_JHKJ={//��ͣ������
	3,
	0,
	6,
	0,
	0,
	101,
	0,
	0,
	0,
	0,
	0,
	{
		{24,1,0,NULL,0,0,1,0},
		{25,1,0,NULL,0,0,1,1},
		{8,1,0,NULL,0,0,1,0}
	},
	{
	}
};

XM_Command xm_JHRT={//��ͯ�����ؿ���
	3,
	0,
	6,
	0,
	0,
	101,
	0,
	0,
	0,
	0,
	0,
	{
		{26,1,0,NULL,0,0,1,0},
		{27,1,0,NULL,0,0,1,1},
		{8,1,0,NULL,0,0,1,0}
	},
	{
	}
};

XM_Command xm_JHSLZ={//ˮ���ӿ�ͣ����
	3,
	0,
	6,
	0,
	0,
	101,
	0,
	0,
	0,
	0,
	0,
	{
		{28,1,0,NULL,0,0,1,0},
		{29,1,0,NULL,0,0,1,1},
		{8,1,0,NULL,0,0,1,0}
	},
	{
	}
};

XM_Command xm_JHSBOX={//smartbox��һ���������������ܣ�
	11,
	0,
	6,
	0,
	0,
	101,
	0,
	0,
	0,
	0,
	0,
	{
		{24,1,0,NULL,0,0,1,0},//����
		{25,1,0,NULL,0,0,1,1},
		{14,3,sizeof(xm_MS2value)/sizeof(xm_MS2value[0]),xm_MS2value,0,0,1,0},//ģʽ
		{15,1,0,NULL,0,0,1,1},
		{6,7,sizeof(xm_FS2value)/sizeof(xm_FS2value[0]),xm_FS2value,0,0,1,0},//����
		{7,1,0,NULL,0,0,1,1},
		{30,1,0,NULL,0,0,1,0},//��ʪ����ͣ����
		{31,1,0,NULL,0,0,1,1},
		{38,7,0,NULL,0,0,1,0},//��ʪ��ʪ������
		{39,1,0,NULL,0,0,1,1},
		{8,1,0,NULL,0,0,1,0}
	},
	{		
	}
};



XM_Command xm_JHJSJ={//��ʪ����ͣ����
	3,
	0,
	6,
	0,
	0,
	101,
	0,
	0,
	0,
	0,
	0,
	{
		{30,1,0,NULL,0,0,1,0},
		{31,1,0,NULL,0,0,1,1},
		{8,1,0,NULL,0,0,1,0}
	},
	{
	}
};

XM_Command xm_JHHS={//��ʪ��ʪ������
	3,
	0,
	6,
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




XM_Command xm_JHZD={//״̬
	1,
	24,
	0,
	10,
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
		{6,7,sizeof(xm_FS2value)/sizeof(xm_FS2value[0]),xm_FS2value,0,1,0,0},////�����ٶ����� 0
		{14,3,sizeof(xm_MS2value)/sizeof(xm_MS2value[0]),xm_MS2value,0,1,0,0},//����ģʽ����1
		{16,1,0,NULL,0,1,0,0},//��ʱ���ػ�����2
		{22,6,sizeof(xm_DS2value)/sizeof(xm_DS2value[0]),xm_DS2value,0,1,0,0},//��ʱ���ػ�ʱ��3
		{31,8,0,NULL,0,1,0,0},//���ת��4
		{39,8,0,NULL,0,1,0,0},//��������5
		{47,8,0,NULL,0,1,0,0},//���������ٷֱ�6
		{55,8,0,NULL,0,1,0,0},//���ʪ��7
		{56,1,0,NULL,0,1,0,0},//��ͣ������8
		{57,1,0,NULL,0,1,0,0},//��ͯ�����ؿ���9
		{58,1,0,NULL,0,1,0,0},	//ˮ���ӿ�ͣ����10
		{59,1,0,NULL,0,1,0,0},//��ʪ����ͣ����11
		{60,1,0,NULL,0,1,0,0},//������������ʾ12
		{61,1,0,NULL,0,1,0,0},//��������֮ǰ�з����Ͱ������ƹ�13
		{62,1,0,NULL,0,1,0,0},//��������֮ǰ�з����Ͱ������ƹ�14
		{64,1,0,NULL,0,1,0,0},//��ʪת�ֲ���15
		{65,1,0,NULL,0,1,0,0},//ˮ���16
		{66,1,0,NULL,0,1,0,0},//ˮ��δװ��17
		{67,1,0,NULL,0,1,0,0},//ʪ�ȴ���������18
		{68,1,0,NULL,0,1,0,0},//�������19
		{69,1,0,NULL,0,1,0,0},//�糾����������20
		{70,1,0,NULL,0,1,0,0},//��ζ����������21
		{71,1,0,NULL,0,1,0,0},//������б����22
		{79,8,0,NULL,0,1,0,0}//ʪ�ȿ���ʪ������23
	}
};

XM_Command xm_JHGN={//���ܲ�ѯ
	0,
	19,
	0,
	0,
	5,
	0,
	0,
	102,
	64,
	0,
	0,
	{
	},
	{
		{3,1,0,NULL,0,1,0,0},//�����ٶ�״̬-�Զ�����
		{4,1,0,NULL,0,1,0,0},//�����ٶ�״̬-���̹���
		{5,1,0,NULL,0,1,0,0},//�����ٶ�״̬-�߷繦��
		{6,1,0,NULL,0,1,0,0},//�����ٶ�״̬-�з繦��
		{7,1,0,NULL,0,1,0,0},//�����ٶ�״̬-�ͷ繦��		
		{11,1,0,NULL,0,1,0,0},//����ģʽ״̬-˯�߹���	
		{12,1,0,NULL,0,1,0,0},//����ģʽ״̬-��������	
		{13,1,0,NULL,0,1,0,0},//����ģʽ״̬-���ܹ���	
		{14,1,0,NULL,0,1,0,0},//����ģʽ״̬-��ζ����	
		{15,1,0,NULL,0,1,0,0},//����ģʽ״̬-	���̹���	
		{16,1,0,NULL,0,1,0,0},//��ͨ��ʱ����
		{17,1,0,NULL,0,1,0,0},//��ͯ������
		{18,1,0,NULL,0,1,0,0},//ˮ���ӿ�ͣ
		{19,1,0,NULL,0,1,0,0},//��ʪ����ͣ����
		{20,1,0,NULL,0,1,0,0},//��������ͣ����
		{22,1,0,NULL,0,1,0,0},//EEPROM�ɸ�д����
		{23,1,0,NULL,0,1,0,0},//������⹦��
		{24,8,0,NULL,0,1,0,0},//101#-0#��5�ֽ�Ԥ��λ�Ŀ��ƹ���
		{32,8,0,NULL,0,1,0,0}//101#-0#��6�ֽ�Ԥ��λ�Ŀ��ƹ���
	}
};

XM_Command xm_EXTEND={//��չ�Ĳ�ѯ״̬
	1,
	3,
	1,
	8,
	0,
	0,
	0,
	102,
	8,
	0,
	0,
	{
		{7,1,0,NULL,0,1,0,0}
	},
	{
		{7,7,0,NULL,0,1,0,0},//�����¶�
		{15,8,0,NULL,0,1,0,0},//ʣ��ʹ��ʱ��Сʱ��λ
		{23,8,0,NULL,0,1,0,0},//ʣ��ʹ��ʱ��Сʱ��λ
	}
};


XM_AT_RET at_cmd_ret_jh[4]={
		{"JHZD",XM_SEND_QUERY,102,0,&xm_JHZD},
		{"JHGN",XM_SEND_QUERY,102,64,&xm_JHGN},
		{"JHSET",XM_SEND_SETTING,101,0,NULL},
		{"JHEXTEND",XM_SEND_QUERY,102,8,&xm_EXTEND}
};

XM_AT_FUN at_cmd_jh[12]={
	{"JHFS",NULL,0,&xm_JHFS},//�����ٶ�����
	{"JHMS",NULL,0,&xm_JHMS},//����ģʽ����
	{"JHDS",NULL,0,&xm_JHDS},//��ʱ���ػ�
	{"JHKJ",NULL,0,&xm_JHKJ},//��ͣ������
	{"JHRT",NULL,0,&xm_JHRT},//��ͯ�����ؿ���
	{"JHSLZ",NULL,0,&xm_JHSLZ},//ˮ���ӿ�ͣ����
	{"JHJSJ",NULL,0,&xm_JHJSJ},//��ʪ����ͣ����
	{"JHHS",NULL,0,&xm_JHHS},//ʪ������
	{"JHZD",NULL,0,&xm_JHZD},//״̬
	{"JHGN",NULL,0,&xm_JHGN},//���ܲ�ѯ
	{"JHSBOX",NULL,0,&xm_JHSBOX},//smartbox��һ���������������ܣ�
	{"JHEXTEND",NULL,0,&xm_EXTEND},
};

