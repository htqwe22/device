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

#define XM_SEED_SET_LEN 14
#define XM_SEED_STATUS_LEN 26

static XM_Command powerSet={
	2,
	0,
	XM_SEED_SET_LEN,
	0,
	0,
	101,
	0,
	101,
	0,
	0,
	0,
	{
		{6,7,0,NULL,0,0,1,0},	//���ػ�
		{7,1,0,NULL,0,0,1,1},	//lock or unlock
	},
	{
	}
};

static XM_Command musicSet={//����
	2,
	0,
	XM_SEED_SET_LEN,
	0,
	0,
	101,
	0,
	101,
	0,
	0,
	0,
	{
		{14,7,0,NULL,0,0,1,0},	
		{15,1,0,NULL,0,0,1,1},	
	},
	{
	}
};

static XM_Command SetVolume={//����
	2,
	0,
	XM_SEED_SET_LEN,
	0,
	0,
	101,
	0,
	101,
	0,
	0,
	0,
	{
		{12,1,0,NULL,0,0,1,0},	
		{13,1,0,NULL,0,0,1,1},	
	},
	{
	}
};

static XM_Command lightSet={//����
	2,
	0,
	XM_SEED_SET_LEN,
	0,
	0,
	101,
	0,
	101,
	0,
	0,
	0,
	{
		{21,6,0,NULL,0,0,1,0},	
		{23,1,0,NULL,0,0,1,1},	
	},
	{
	}
};

static XM_Command anionSet={//������
	2,
	0,
	XM_SEED_SET_LEN,
	0,
	0,
	101,
	0,
	101,
	0,
	0,
	0,
	{
		{30,7,0,NULL,0,0,1,0},	
		{31,1,0,NULL,0,0,1,1},	
	},
	{
	}
};

static XM_Command lightTimer={//�ƶ�ʱ
	10,
	0,
	XM_SEED_SET_LEN,
	0,
	0,
	101,
	0,
	101,
	0,
	0,
	0,
	{
		{54,7,0,NULL,0,0,1,0},	//��ǰʱ��Сʱ
		{63,8,0,NULL,0,0,1,0},	//��ǰʱ�����
		{55,1,0,NULL,0,0,1,1},	

		{70,1,0,NULL,0,0,1,0},	// 1��ʱ
		{71,1,0,NULL,0,0,1,1},	

		{38,1,0,NULL,0,0,1,0},	//0��ʾ�ǹص����ã�1��ʾ�����趨
		{37,6,0,NULL,0,0,1,0},	//��ʱСʱ
		{47,8,0,NULL,0,0,1,0},	//��ʱ����
		{39,1,0,NULL,0,0,1,1},	
		{69,6,0,NULL,0,0,1,0},	//ͬʱָ�����ļ����
	},
	{
	}
};


static XM_Command pm25Set={//pm2.5�趨
	2,
	0,
	XM_SEED_SET_LEN,
	0,
	0,
	101,
	0,
	101,
	0,
	0,
	0,
	{
		{78,7,0,NULL,0,0,1,0},	
		{79,1,0,NULL,0,0,1,1},	
	},
	{
	}
};

static XM_Command warningClose={//�������
	3,
	0,
	XM_SEED_SET_LEN,
	0,
	0,
	101,
	0,
	101,
	0,
	0,
	0,
	{
		{85,1,0,NULL,0,0,1,0},	//��ˮλ����
		{86,1,0,NULL,0,0,1,0},	// ��ˮ�ñ���
		{87,1,0,NULL,0,0,1,0},	// ��Ӫ��Һ����
	},
	{
	}
};



XM_Command seedStat={
	1,
	25,
	1,
	XM_SEED_STATUS_LEN,
	0,
	102,
	0,
	102,
	0,
	0,
	0,
	{
		{7,8,0,NULL,0,1,0,0}, //auto or manual
	},
	{
		{ 0,1,0,NULL,0,1,0,0},	// Power State
		{1,1,0,NULL,0,1,0,0},	// Music State
		{2,1,0,NULL,0,1,0,0},	//������
		{3,1,0,NULL,0,1,0,0},	//�ƶ�ʱ����
		
		{14,7,0,NULL,0,1,0,0},	// Light Mask
		
		{23,8,0,NULL,0,1,0,0},	// �¶���������
		{31,8,0,NULL,0,1,0,0},	// �¶�С������

		{39,8,0,NULL,0,1,0,0},	// ʪ����������
		{47,8,0,NULL,0,1,0,0},	// ʪ��С������
		
		{55,1,0,NULL,0,1,0,0},	//�Ƿ�����Ӵ��� ��

		/*�㷨 val*15/100000*/
		{63,8,0,NULL,0,1,0,0},	//PM3.0���λ 10
		{71,8,0,NULL,0,1,0,0},	//PM3.0�θ�λ
		{79,8,0,NULL,0,1,0,0},	//PM3.0�ε�λ
		{87,8,0,NULL,0,1,0,0},	//PM3.0���λ
		/*�㷨 val/10 */
		{159,8,0,NULL,0,1,0,0},	//ʪ��ֵ1    14
		{167,8,0,NULL,0,1,0,0},	//ʪ��ֵ2
		/*�㷨 (val-500)/10 */
		{175,8,0,NULL,0,1,0,0},	//�¶�ֵ1    16
		{183,8,0,NULL,0,1,0,0},	//�¶�ֵ2
		
		{191,1,0,NULL,0,1,0,0},	// �Ƿ��еƱ���
		{190,7,0,NULL,0,1,0,0},	//�Ʊ�����Ϣ
		
		{193,2,0,NULL,0,1,0,0},	//ˮλ����ֵ
		{194,1,0,NULL,0,1,0,0},	//ˮ�ù��ϱ���
		{195,1,0,NULL,0,1,0,0},	//Ӫ��Һ����

        // ADD in 1.7
        {4,1,0,NULL,0,1,0,0},	// ˮѭ��״̬
        {54,1,0,NULL,0,1,0,0}, //�Ƿ���PM2.5��ֵ������У�ʹ��PM3.0���λ�ʹθ�λΪֵ
	}

};

static XM_Command WaterPump={//�������
	3,
	0,
	XM_SEED_SET_LEN,
	0,
	0,
	101,
	0,
	101,
	0,
	0,
	0,
	{
		{94,1,0,NULL,0,0,1,0},	// ˮѭ������
		{95,1,1,NULL,0,0,1,1},	// ˮѭ�����ñ�־
	},
	{
	}
};


XM_AT_FUN at_cmd_Seed[10]={
	{"SEEDStat",NULL,0,&seedStat}, 	//״̬��ѯ
	{"SEEDPSet",NULL,0,&powerSet}, 	//��Դ	
	{"SEEDMSet",NULL,0,&musicSet},	//��������
	{"SEEDVSet",NULL,0,&SetVolume},	//��������
	{"SEEDLSet",NULL,0,&lightSet}, 	//�ƿ���
	{"SEEDAnion",NULL,0,&anionSet},
	{"SEEDLTime",NULL,0,&lightTimer},
	{"SEEDCWarn",NULL,0,&warningClose},
	{"SEEDPm25",NULL,0,&pm25Set},
	
	{"WaterPump",NULL,0,&WaterPump},

};

XM_AT_RET at_cmd_ret_Seed[2]={
	{"SEEDStat",XM_SEND_QUERY,102,0,&seedStat},
	{"DCSET",XM_SEND_SETTING,101,0,NULL},
};

