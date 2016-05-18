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
#include	"cmdanalysis.h"

#define XM_RSQ_SET_LEN 12
#define XM_RSQ_STATUS_LEN 19

XM_Command xm_RSQKJ={//���ػ�
	3,
	0,
	XM_RSQ_SET_LEN,
	XM_RSQ_STATUS_LEN,
	0,
	101,
	0,
	0,
	0,
	0,
	0,
	{		
		{7,8,0,NULL,0,0,1,0},
		{15,8,0,NULL,0,0,1,0},
		{23,8,0,NULL,0,0,1,0}
	},
	{

	}
};




XM_Command xm_RSQWD={//�¶�����
	3,
	0,
	XM_RSQ_SET_LEN,
	XM_RSQ_STATUS_LEN,
	0,
	101,
	0,
	0,
	0,
	0,
	0,
	{		
		{7,8,0,NULL,0,0,1,0},
		{15,8,0,NULL,0,0,1,0},
		{23,8,0,NULL,0,0,1,0}
	},
	{

	}
};


XM_Command xm_RSQ50LOCK={//50���¶�������
	3,
	0,
	XM_RSQ_SET_LEN,
	XM_RSQ_STATUS_LEN,
	0,
	101,
	0,
	0,
	0,
	0,
	0,
	{
		{7,8,0,NULL,0,0,1,0},
		{15,8,0,NULL,0,0,1,0},
		{23,8,0,NULL,0,0,1,0}
	},
	{

	}
};

XM_Command xm_RSQPRODUCT={//��Ʒ�ͺŶ�ȡ��д��
	0,
	4,
	0,
	26,
	0,
	103,
	0,
	103,
	0,
	0,
	0,
	{
	},
	{
		{7,8,0,NULL,0,1,0,0},//��һ���ֽڴ�����������0��ʾʹ��BCD���룬
		{191,184,0,NULL,0,1,0,0},//����23���ֽڱ�ʾ���ݣ�
		{199,8,0,NULL,0,1,0,0},//��2�ֽ�Ϊ�ۼӺ�
		{207,8,0,NULL,0,1,0,0},//��2�ֽ�Ϊ�ۼӺ�
	}
};



XM_Command xm_RSQZD={//��ˮ��״̬��ѯ
	0,
	19,
	0,
	XM_RSQ_STATUS_LEN,
	0,
	0,
	0,
	102,
	0,
	0,
	0,
	{	
	},
	{
		{7,8,0,NULL,0,1,0,0},//��������״̬
		{15,8,0,NULL,0,1,0,0},//co����
		{23,8,0,NULL,0,1,0,0},//ȼ������
		{31,8,0,NULL,0,1,0,0},//COŨ�ȣ�Ԥ����
		{39,8,0,NULL,0,1,0,0},//ȼ��Ũ�ȣ�Ԥ����
		{47,8,0,NULL,0,1,0,0},//����ʱ�䣨��λ��
		{55,8,0,NULL,0,1,0,0},//����ʱ�䣨��λ��
		{63,8,0,NULL,0,1,0,0},//��ˮ�¶�
		{71,8,0,NULL,0,1,0,0},//�趨�¶�
		{79,8,0,NULL,0,1,0,0},//50���¶���
		{87,8,0,NULL,0,1,0,0},//�趨�¶�60������
		{95,8,0,NULL,0,1,0,0},//ȼ��״̬
		{103,8,0,NULL,0,1,0,0},//Ԥ����Ӧ0���ޣ�1 �ֶ���2���Զ�
		{111,8,0,NULL,0,1,0,0},//������Ӧ��Ԥ����
		{119,8,0,NULL,0,1,0,0},//���ϴ���
		{127,8,0,NULL,0,1,0,0},//Ԥ������0
		{135,8,0,NULL,0,1,0,0},//Ԥ������1
		{143,8,0,NULL,0,1,0,0},//Ԥ������2
		{151,8,0,NULL,0,1,0,0}//Ԥ������3
	}
};



XM_Command xm_RSQOTHREZD={//��ˮ������״̬��ѯ (Ԥ��)
	0,
	18,
	0,
	0,
	6,
	0,
	0,
	102,
	1,
	0,
	0,
	{
	},
	{
		{7,8,0,NULL,0,1,0,0},//Ԥ������0
		{15,8,0,NULL,0,1,0,0},//Ԥ������1
		{23,8,0,NULL,0,1,0,0},//Ԥ������2
		{31,8,0,NULL,0,1,0,0},//Ԥ������3
		{39,8,0,NULL,0,1,0,0},//Ԥ������4
		{47,8,0,NULL,0,1,0,0},//Ԥ������5
		{55,8,0,NULL,0,1,0,0},//Ԥ������6
		{63,8,0,NULL,0,1,0,0},//Ԥ������7
		{71,8,0,NULL,0,1,0,0},//Ԥ������8
		{79,8,0,NULL,0,1,0,0},//Ԥ������9
		{87,8,0,NULL,0,1,0,0},//Ԥ������10
		{95,8,0,NULL,0,1,0,0},//Ԥ������11
		{103,8,0,NULL,0,1,0,0},//Ԥ������12
		{111,8,0,NULL,0,1,0,0},//Ԥ������13
		{119,8,0,NULL,0,1,0,0},//Ԥ������14
		{127,8,0,NULL,0,1,0,0},//Ԥ������15
		{135,8,0,NULL,0,1,0,0},//Ԥ������16
		{143,8,0,NULL,0,1,0,0},//Ԥ������17
		{151,8,0,NULL,0,1,0,0}//Ԥ������18
	}
};

XM_Command xm_RSQPERHEAT={//Ԥ�ȹ�������
	5,
	0,
	XM_RSQ_SET_LEN,
	XM_RSQ_STATUS_LEN,
	0,
	101,
	0,
	0,
	0,
	0,
	0,
	{	
		{7,8,0,NULL,0,0,1,0},
		{15,8,0,NULL,0,0,1,0},
		{23,8,0,NULL,0,0,1,0},
		{30,3,0,NULL,0,0,1,0},// 0 ȡ����1 �ֶ���2���Զ�
		{31,1,0,NULL,0,0,1,1},  
	},
	{
	
	}
};


XM_Command xm_RSQGN={//���ܲ�ѯ
	0,
	7,
	0,
	10,
	0,
	102,
	64,
	102,
	64,
	0,
	0,
	{		
	},
	{
		{7,8,0,NULL,0,1,0,0},// ����
		{15,8,0,NULL,0,1,0,0},//����¶�
		{23,8,0,NULL,0,1,0,0},//����¶�

		{28,1,0,NULL,0,1,0,0},//50�����Ƿ�ɲ���
		{29,1,0,NULL,0,1,0,0},//����н������й���
		{30,1,0,NULL,0,1,0,0},//�Ƿ���Ԥ�ȹ���
		{31,1,0,NULL,0,1,0,0},//�Ƿ���50��������
	}
};


XM_AT_RET at_cmd_ret_rsq[]={
		{"RSQZD",XM_SEND_QUERY,102,0,&xm_RSQZD},
		{"RSQPRODUCT",XM_SEND_QUERY,103,0,&xm_RSQPRODUCT},
		{"RSQGN",XM_SEND_QUERY,102,64,&xm_RSQGN},
		{"RSQSET",XM_SEND_QUERY,101,0,&xm_RSQZD}		
};


XM_AT_FUN at_cmd_rsq[8]={
	{"RSQKJ",NULL,0,&xm_RSQKJ},//���ػ�����
	{"RSQWD",NULL,0,&xm_RSQWD},//�¶�����
	{"RSQ50LOCK",NULL,0,&xm_RSQ50LOCK},//50���¶�������	
	{"RSQPRODUCT",NULL,0,&xm_RSQPRODUCT},//��Ʒ�ͺŲ�ѯ
	{"RSQGN",NULL,0,&xm_RSQGN},
	{"RSQZD",NULL,0,&xm_RSQZD},//��ˮ��״̬��ѯ
	{"RSQPERHEAT",NULL,0,&xm_RSQPERHEAT},//��ˮ��Ԥ�ȹ���
	{"RSQOTHREZD",NULL,0,&xm_RSQOTHREZD},//��ˮ������״̬��ѯ (Ԥ��)	
};

