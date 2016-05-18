
#include "vanword.h"

#define PowerOn 	0x01
#define PowerOff 	0x00

#define LIG_Y		0x01
#define LIG_N		0x00

#define SOFT		0x01
#define KITCHEN		0x02
#define SHOWER		0x03
#define SAVEPower	0x04
#define SMART		0x05
#define CUSTOM		0X06

static XM_Value if_power[]={
	{STR(PowerOn),PowerOn},
	{STR(PowerOff),PowerOff}
};
static XM_Value if_safe_lig[]={
	{STR(LIG_Y),LIG_Y},
	{STR(LIG_N),LIG_N}
};

static XM_Value sys_mode[]={
	{STR(SOFT),SOFT},
	{STR(KITCHEN),KITCHEN},
	{STR(SAVEPower),SAVEPower},
	{STR(SMART),SMART},
	{STR(CUSTOM),CUSTOM}
};

/* ˵��: 1�����P0�в�����Ч�����ֶ�
 *       itme->num=0
 *       2�����û��P0
 *		   &item=NULL
 */ 



/****** cmdCode 0x40 *******/
VANW_ITEM_T burn_water_stat={		//ȼ����ˮ��״̬
	46,
	46,
	0,
	{
		{7,8, 2,if_power,0,1,0,0},	//���ػ�
		{15,8,2,if_safe_lig,0,1,0,0},	//��ȫ��
		{23,8,6,sys_mode,0,1,0,0},		//ϵͳģʽ
		{31,8,0,NULL,0,1,0,0},			//עˮ����
		{39,8,0,NULL,0,1,0,0},			//��ˮ��
		
		{47,8,0,NULL,0,1,0,0},			//��ˮ�ۼ�����λ
		{55,8,0,NULL,0,1,0,0},			//��ˮ�ۼ�����λ
		
		{63,8,0,NULL,0,1,0,0},			//�Զ��幦��
		{71,8,0,NULL,0,1,0,0},			// �Զ�������ˮ��
		{79,8,0,NULL,0,1,0,0},			// ˮ��������
		{87,8,0,NULL,0,1,0,0},			//������ʾ ����
		{95,8,0,NULL,0,1,0,0},			//��������
		{103,8,0,NULL,0,1,0,0},			//��������
		{111,8,0,NULL,0,1,0,0},			//�������
		{119,8,0,NULL,0,1,0,0},			// ����������
		{127,8,0,NULL,0,1,0,0},			//���ϴ���
		{135,8,0,NULL,0,1,0,0},			//������ʾ
		{143,8,0,NULL,0,1,0,0},			//CO����
		{151,8,0,NULL,0,1,0,0},			//����ˮ��
		{159,8,0,NULL,0,1,0,0},			//��ˮ�¶�
		{167,8,0,NULL,0,1,0,0},			//��ˮ�¶�
		{175,8,0,NULL,0,1,0,0},			//��ǰ����
		
		{183,8,0,NULL,0,1,0,0},			//�ۼ���ˮ����4λ
		{191,8,0,NULL,0,1,0,0},			//�ۼ���ˮ����3λ
		{199,8,0,NULL,0,1,0,0},			//�ۼ���ˮ����2λ
		{207,8,0,NULL,0,1,0,0},			//�ۼ���ˮ�����λ

		{215,8,0,NULL,0,1,0,0},			//�ۼ���������λ
		{223,8,0,NULL,0,1,0,0},			//�ۼ���������λ
		
		{231,8,0,NULL,0,1,0,0},			//�ۼ�ʹ��ʱ���4
		{239,8,0,NULL,0,1,0,0},			//�ۼ�ʹ��ʱ���3
		{247,8,0,NULL,0,1,0,0},			//�ۼ�ʹ��ʱ���2
		{255,8,0,NULL,0,1,0,0},			//�ۼ�ʹ��ʱ���1

		{263,8,0,NULL,0,1,0,0},			// �ۼӿ�������λ
		{271,8,0,NULL,0,1,0,0},			// �ۼӿ�������λ

		{279,8,0,NULL,0,1,0,0},			//ʵʱЧ��
		{287,8,0,NULL,0,1,0,0},			//Ԥ�ȹ���
		{295,8,0,NULL,0,1,0,0},			//Ԥ���¶�
		{303,8,0,NULL,0,1,0,0},			//Ԥ��1Сʱ
		{311,8,0,NULL,0,1,0,0},			//Ԥ��1����
		{319,8,0,NULL,0,1,0,0},			//Ԥ��2Сʱ
		{327,8,0,NULL,0,1,0,0},			//Ԥ��2����
		{335,8,0,NULL,0,1,0,0},			//����������ʾ
		{343,8,0,NULL,0,1,0,0},			//ˮ����ʾ
		{351,8,0,NULL,0,1,0,0},			//��ˮ�¶�
		{359,8,0,NULL,0,1,0,0},			//reserved
		{367,8,0,NULL,0,1,0,0} 		//reserved
	}
};

/****** cmdCode 0x20 *******/
VANW_ITEM_T elect_water_stat={		//����ˮ��״̬
	18,
	18,
	0,
	{
		{7,8,2,if_power,0,1,0,0},	//���ػ�״̬
		{15,8,0,NULL,0,1,0,0},	//ϵͳ����״̬�����Ȼ��������
		{23,8,0,NULL,0,1,0,0},		//����״̬
		{31,8,0,NULL,0,1,0,0},		//ԤԼ״̬
		{39,8,0,NULL,0,1,0,0},		//�ڵ�ˮ��
		{47,8,0,NULL,0,1,0,0},		//ԤԼСʱ
		{55,8,0,NULL,0,1,0,0},		//ԤԼ����
		{63,8,0,NULL,0,1,0,0},		//����ˮ��
		{71,8,0,NULL,0,1,0,0},		//���ù���
		{79,8,0,NULL,0,1,0,0},		//ʣ�����ʱ��
		{87,8,0,NULL,0,1,0,0},		//��ˮ��
		{95,8,0,NULL,0,1,0,0},		//�������
		
		{103,8,0,NULL,0,1,0,0},		//�õ�����λ
		{111,8,0,NULL,0,1,0,0},		//�õ�����λ
		
		{119,8,0,NULL,0,1,0,0},		//���ȼ����ۼ�ʱ���λ
		{127,8,0,NULL,0,1,0,0},		//���ȼ���ʱ���λ
		
		{135,8,0,NULL,0,1,0,0},		//δ����ʱ���λ
		{143,8,0,NULL,0,1,0,0}		//δ����ʱ���λ

		// when setting below is the 
	//	{7,8,0,NULL,0,0,1,0}		//δ����ʱ���λ
	}
};

/****** cmdCode 0x60 *******/
VANW_ITEM_T worm_stove={
	46,
	46,
	0,
	{
		{7,8, 2,if_power,0,1,0,0},	//���ػ�
		{15,8,2,if_safe_lig,0,1,0,0},	//��ȫ��
		{23,8,0,NULL,0,1,0,0},		//����״̬
		{31,8,0,NULL,0,1,0,0},		//����״̬
		{39,8,0,NULL,0,1,0,0},		//����״̬
		{47,8,0,NULL,0,1,0,0},			//��ԡˮ��״̬
		{55,8,0,NULL,0,1,0,0},			//��ů�ȴ���ģʽ
		{63,8,0,NULL,0,1,0,0},			//��ԡģʽ
		{71,8,0,NULL,0,1,0,0},			// ��������
		{79,8,0,NULL,0,1,0,0},			// ���״̬
		{87,8,0,NULL,0,1,0,0},			//ˮ��״̬
		{95,8,0,NULL,0,1,0,0},			//��ͨ��״̬
		{103,8,0,NULL,0,1,0,0},			//�����״̬
		{111,8,0,NULL,0,1,0,0},			//����״̬0��ֹͣ����1�������������з�����
		{119,8,0,NULL,0,1,0,0},			// ����״̬0��ֹͣ����1�����У�
		{127,8,0,NULL,0,1,0,0},			//Զ��������ů״̬
		{135,8,0,NULL,0,1,0,0},			//ˮѹֵ
		{143,8,0,NULL,0,1,0,0},			//��ԡĿ���¶�
		{151,8,0,NULL,0,1,0,0},			//��ԡʵ���¶�
		{159,8,0,NULL,0,1,0,0},			//��ůĿ���¶�
		{167,8,0,NULL,0,1,0,0},			//��ůʵ���¶�
		{175,8,0,NULL,0,1,0,0},			//�����¶�
		{183,8,0,NULL,0,1,0,0},			//��ů����ģʽ
		
		{191,8,0,NULL,0,1,0,0},			//�ۼ�������3
		{199,8,0,NULL,0,1,0,0},			// 2
		{207,8,0,NULL,0,1,0,0},			// 1
		{215,8,0,NULL,0,1,0,0},			//  0
		{223,8,0,NULL,0,1,0,0},			//  ʵʱ������12�ֽ�
		
	 	{319,96,0,NULL,0,1,0,0},			// �������к�
	 #if 0
		{231,8,0,NULL,0,1,0,0},			// �������к�11
		{239,8,0,NULL,0,1,0,0},			// 10
		{247,8,0,NULL,0,1,0,0},			// 9
		{255,8,0,NULL,0,1,0,0},			// 8
		{263,8,0,NULL,0,1,0,0},			// 7
		{271,8,0,NULL,0,1,0,0},			// 6
		{279,8,0,NULL,0,1,0,0},			// 5
		{287,8,0,NULL,0,1,0,0},			// 4
		{295,8,0,NULL,0,1,0,0},			// 3
		{303,8,0,NULL,0,1,0,0},			// 2
		{311,8,0,NULL,0,1,0,0},			// 1
		{319,8,0,NULL,0,1,0,0},			//  0
	#endif	
		{327,8,0,NULL,0,1,0,0},			// FF
		{335,8,0,NULL,0,1,0,0},			// FF
		{343,8,0,NULL,0,1,0,0},			// FF
		{351,8,0,NULL,0,1,0,0},			// FF
		{359,8,0,NULL,0,1,0,0},			// FF
		{367,8,0,NULL,0,1,0,0} 			// FF
	}
};

/****** cmdCode 0x50 *******/
VANW_ITEM_T all_heartBeat={
	0,
	0,
	0,
	{
	}
};


//----------------Below is  electric water heator ---------------

/****** cmdCode 0xdd *******/
VANW_ITEM_T all_refresh={
	0,
	0,
	0,
	{
	}
};

/****** cmdCode 0x01 *******/
VANW_ITEM_T elect_water_kj={
	1,
	0,
	1,
	{
		{7,8,0,NULL,0,0,1,0}
	}

};

/****** cmdCode 0x02 *******/
VANW_ITEM_T elect_water_set={
	1,
	0,
	1,
	{
		{7,8,0,NULL,0,0,1,0}
	}

};

/****** cmdCode 0x03 *******/
VANW_ITEM_T elect_water_temp={
	1,
	0,
	1,
	{
		{7,8,0,NULL,0,0,1,0}
	}

};
/****** cmdCode 0x04 *******/
VANW_ITEM_T elect_water_pwerRating={   	// power rating setting ; unit KW 1 ~5
	1,
	0,
	1,
	{
		{7,8,0,NULL,0,0,1,0}
	}

};

/****** cmdCode 0x05 *******/
VANW_ITEM_T elect_water_appointment={
	4,
	0,
	4,
	{
		{7,8,0,NULL,0,0,1,0}, 	//	hour 	:0~23
		{15,8,0,NULL,0,0,1,0},	// minute	:0~59
		{23,8,0,NULL,0,0,1,0},	// temprature  :35~75
		{31,8,0,NULL,0,0,1,0}	// power rating:1~5
	}

};

/****** cmdCode 0x06 *******/
VANW_ITEM_T elect_water_cancelApoint={
	0,
	0,
	0,
	{
	}

};

//----------------Below is  burn water heator ---------------

/****** cmdCode 0x80 *******/
VANW_ITEM_T burn_water_kj={
	1,
	0,
	1,
	{
		{7,8,0,NULL,0,0,1,0}
	}

};

// safe light
/****** cmdCode 0x81 *******/
VANW_ITEM_T burn_water_light={
	1,
	0,
	1,
	{
		{7,8,0,NULL,0,0,1,0}
	}

};

/****** cmdCode 0x82 *******/
VANW_ITEM_T burn_water_set={
	1,
	0,
	1,
	{
		{7,8,0,NULL,0,0,1,0} //35~48  50,55,60,65
	}

};

/****** cmdCode 0x83 *******/
VANW_ITEM_T burn_water_addWater={
	1,
	0,
	1,
	{
		{7,8,0,NULL,0,0,1,0} //0~99
	}

};

/****** cmdCode 0x84 *******/
VANW_ITEM_T burn_water_callCmd={
	1,
	0,
	1,
	{
		{7,8,0,NULL,0,0,1,0} 
	}

};

/****** cmdCode 0x86 *******/
VANW_ITEM_T burn_water_mode={
	1,
	0,
	1,
	{
		{7,8,0,NULL,0,0,1,0} 
	}

};

/****** cmdCode 0x88 *******/
VANW_ITEM_T burn_water_preHeat={
	6,
	0,
	6,
	{
		{7,8,0,NULL,0,0,1,0}, // 0 ~4 preHeater mode
		{15,8,0,NULL,0,0,1,0}, // temprature
		{23,8,0,NULL,0,0,1,0}, // unit one hour setting
		{31,8,0,NULL,0,0,1,0}, // unit one minutes setting
		{39,8,0,NULL,0,0,1,0}, // unit two houres setting
		{47,8,0,NULL,0,0,1,0}  // unit two minutes setting
	}

};

/****** cmdCode 0x89 *******/
VANW_ITEM_T burn_water_profiles={
	3,
	0,
	3,
	{
		{7,8,0,NULL,0,0,1,0},  // 0 ~4 preHeater mode
		{15,8,0,NULL,0,0,1,0}, // temprature
		{23,8,0,NULL,0,0,1,0}  // unit one hour setting
	}

};

//----------------Below is  Warm Stove ---------------
/****** cmdCode 0xa0 *******/
VANW_ITEM_T warm_stove_kj={
	1,
	0,
	1,
	{
		{7,8,0,NULL,0,0,1,0},  // 1: powerOn 0:powerOff
	}

};

// safe light
/****** cmdCode 0xa1 *******/
VANW_ITEM_T warm_stove_light={
	1,
	0,
	1,
	{
		{7,8,0,NULL,0,0,1,0}
	}

};

/****** cmdCode 0xa2 *******/
VANW_ITEM_T warm_stove_showerTemp={
	1,
	0,
	1,
	{
		{7,8,0,NULL,0,0,1,0}
	}
};

/****** cmdCode 0xa3 *******/
VANW_ITEM_T warm_stove_warmtTemp={
	1,
	0,
	1,
	{
		{7,8,0,NULL,0,0,1,0}	//30 ~80
	}
};

/****** cmdCode 0xa4 *******/
VANW_ITEM_T warm_stove_reset={
	1,
	0,
	1,
	{
		{7,8,0,NULL,0,0,1,0}	//0xff
	}
};

/****** cmdCode 0xa5 *******/
VANW_ITEM_T warm_stove_warmMode={
	1,
	0,
	1,
	{
		{7,8,0,NULL,0,0,1,0}	//0xa0 a1 a2
	}
};

/****** cmdCode 0xa6 *******/
VANW_ITEM_T warm_stove_showerMode={
	1,
	0,
	1,
	{
		{7,8,0,NULL,0,0,1,0}	//0 1
	}
};

/****** cmdCode 0xa7 *******/
VANW_ITEM_T warm_stove_seasonMode={
	1,
	0,
	1,
	{
		{7,8,0,NULL,0,0,1,0}	//0 1
	}
};

/****** cmdCode 0xa8 *******/
VANW_ITEM_T warm_stove_remoteWarmMode={
	1,
	0,
	1,
	{
		{7,8,0,NULL,0,0,1,0}	//0xa0 a1 a2
	}
};





/*����״̬������*/

VANW_AT_T ret_commProduce[1]={
	{"VWGETPROID", XM_SEND_SETTING, COMM_PRODUCT,0xFF,{0x03,0x07},NULL}
};

VANW_AT_T ret_clectWaterHeator[2]={
	{"VWEWZT", XM_SEND_QUERY, ELECT_HEATOR,0x20,{0x03,0x05}, &elect_water_stat},
	{"VWEWHHB",XM_SEND_QUERY, ELECT_HEATOR,0x50,{0x03,0x05},&all_heartBeat}
};

VANW_AT_T ret_burnWaterHeator[2]={
	{"VWBWHZT", XM_SEND_QUERY, BURN_HEATOR,0x40,{0x03,0x05},&burn_water_stat},
	{"VWBWHHB", XM_SEND_QUERY, BURN_HEATOR,0x50,{0x03,0x05},&all_heartBeat}
};

VANW_AT_T ret_warmStoveHeator[2]={
	{"VWWSZT", XM_SEND_QUERY,WARM_STOVE,0x60,{0x03,0x05},&worm_stove},
	{"VWWSHB", XM_SEND_QUERY,WARM_STOVE,0x50,{0x03,0x05},&all_heartBeat}
};


/*���ڿ��Ƶ�����*/


VAN_CMD_T cmd_commProduce[1]={
	{"VWGETPROID", XM_SEND_SETTING, COMM_PRODUCT,0xFF,{0x03,0x06},NULL}
};



/* electric water heator  */
VAN_CMD_T cmd_clectWaterHeator[7]={
	{"VWEWZT", XM_SEND_SETTING, ELECT_HEATOR,0xDD,{0x03,0x01}, &all_refresh},

	{"VWEWKJ",XM_SEND_SETTING,ELECT_HEATOR,0x01,{0x03,0x01},&elect_water_kj},
	{"VWEWSETMD",XM_SEND_SETTING,ELECT_HEATOR,0x02,{0x03,0x01},&elect_water_set},
	{"VWEWTEMP",XM_SEND_SETTING,ELECT_HEATOR,0x03,{0x03,0x01},&elect_water_temp},
	{"VWEWPRT",XM_SEND_SETTING,ELECT_HEATOR,0x04,{0x03,0x01},&elect_water_pwerRating},
	{"VWEWAPNT",XM_SEND_SETTING,ELECT_HEATOR,0x05,{0x03,0x01},&elect_water_appointment},
	{"VWEWCAPNT",XM_SEND_SETTING,ELECT_HEATOR,0x06,{0x03,0x01},&elect_water_cancelApoint}
	
};

/* burn water heator  */
VAN_CMD_T cmd_burnWaterHeator[9]={
	{"VWBWHZT", XM_SEND_SETTING,BURN_HEATOR,0xDD,{0x03,0x01},&all_refresh},
		
	{"VWBWKJ",XM_SEND_SETTING,BURN_HEATOR,0x80,{0x03,0x01},&burn_water_kj},
	{"VWBWLIG",XM_SEND_SETTING,BURN_HEATOR,0x81,{0x03,0x01},&burn_water_light},
	{"VWBWTSET",XM_SEND_SETTING,BURN_HEATOR,0x82,{0x03,0x01},&burn_water_set},
	{"VWBWAW",XM_SEND_SETTING,BURN_HEATOR,0x83,{0x03,0x01},&burn_water_addWater},
	{"VWBWCCMD",XM_SEND_SETTING,BURN_HEATOR,0x84,{0x03,0x01},&burn_water_callCmd},
	{"VWBWMODE",XM_SEND_SETTING,BURN_HEATOR,0x86,{0x03,0x01},&burn_water_mode},
	{"VWBWPREH",XM_SEND_SETTING,BURN_HEATOR,0x88,{0x03,0x01},&burn_water_preHeat},
	{"VWBWPROF",XM_SEND_SETTING,BURN_HEATOR,0x89,{0x03,0x01},&burn_water_profiles}
};

/* worm stove heator  */
VAN_CMD_T cmd_warmStoveHeator[10]={
	{"VWWSZT", XM_SEND_SETTING, WARM_STOVE,0xDD,{0x03,0x01},&all_refresh},

	{"VWWSKJ", XM_SEND_SETTING, WARM_STOVE,0xA0,{0x03,0x01},&warm_stove_kj},
	{"VWWSLIG", XM_SEND_SETTING, WARM_STOVE,0xA1,{0x03,0x01},&warm_stove_light},
	{"VWWSSHWRTMP", XM_SEND_SETTING, WARM_STOVE,0xA2,{0x03,0x01},&warm_stove_showerTemp},
	{"VWWSWRMTEMP", XM_SEND_SETTING, WARM_STOVE,0xA3,{0x03,0x01},&warm_stove_warmtTemp},
	{"VWWSRST", XM_SEND_SETTING, WARM_STOVE,0xA4,{0x03,0x01},&warm_stove_reset},
	{"VWWSWRMMD", XM_SEND_SETTING, WARM_STOVE,0xA5,{0x03,0x01},&warm_stove_warmMode},
	{"VWWSSWRMD", XM_SEND_SETTING, WARM_STOVE,0xA6,{0x03,0x01},&warm_stove_showerMode},
	{"VWWSSNMD", XM_SEND_SETTING, WARM_STOVE,0xA7,{0x03,0x01},&warm_stove_seasonMode},
	{"VWWSRMTMD", XM_SEND_SETTING, WARM_STOVE,0xA8,{0x03,0x01},&warm_stove_remoteWarmMode},
};


