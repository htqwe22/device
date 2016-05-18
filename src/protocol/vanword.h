#ifndef __XLF__VANWORD_H
#define __XLF__VANWORD_H

#include "xm_type.h"
#include "xmlog.h"
#include <arpa/inet.h>

#define VANW_DEBUG 1
#if VANW_DEBUG

#ifndef ANDROID
#define xlf_debug(fmt,args...) printf("%s >> %d: "fmt,__func__,__LINE__,##args)
#else
#define xlf_debug(fmt,args...) __android_log_print(ANDROID_LOG_DEBUG, TAG, fmt, ##args)
#endif

#else
#define xlf_debug(fmt,args...)
#endif

// error code
#define XM_ERROR_0307		35



#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))
#define STR(s) #s
#define STR_MAP_VAL(n) ({STR(n),n})
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
// ֧�ֵ��豸����
#define BURN_HEATOR 		0x01
#define ELECT_HEATOR 		0x02
#define WARM_STOVE			0x03
#define COMM_PRODUCT		0XFF

// 1 �ֽڶ���
//
#define	PACKET_MAX_LEN	255
#define	PACKET_MIN_LEN	6
#define	FRAME_ERROR_CTRLID	0x03
#pragma pack(push,1)

struct ctl_id{
	u8 dataH;
	u8 dataL;
};
typedef struct _p0{
	u8 p0_data[256];//��������BODY
	u32 error;		//�����Ľ��
	struct ctl_id id;	//ͨѶ��������ID
	u16 len;		// body�ĳ���
	u8	headDataLen;
}p0_t;

typedef struct _head{
	u8 *bodyHex;
	u8 len;
	u32 conNUM;
	struct ctl_id id;
}build_info_t;



#if 0
/*ÿһ��������Ϣ������*/
typedef struct VANW_Offset{
	u16 offset;//ƫ��
	u16 takeLen;//����
//	u8 	valType;	//�������8λ�ģ��ж�����������������Ͷ���
	uchar textlen;//ӳ�����
	XM_Value *text;//ӳ���
	u8  support;//�ڹ��ܲ�ѯʱ��Ч
	u8  query;//��״̬��ѯ ʱ��Ч
	u8  set;//������ ʱ��Ч
	u8 preset;//Ԥ��ֵ,������ ʱ�Զ���Ч
}VANW_OFFSET_T;
#endif
/*��ÿ��ATָ�����ܽ��ܵĲ�����������*/
typedef struct vanw_item{
	u16  num;// �ܲ������� 	
	u8 queryNum;	//״̬����ʱ�ĸ���
	u8 setNum;		//���õĸ���
	XM_Offset cmdArry[MAX_CMD_PARAM_NUM];//������
}VANW_ITEM_T;

/*����ṹ��ÿ��ATָ��������������device_type��ʵ����ʡ�ԣ���Э����Ҳû��ָ����ͬ�Ĳ�Ʒ���������ͬ��������
 *�������������������ж��ǲ������ATָ��
*/
typedef struct vanw_at_info{
	char *at;	//ATָ��ͷ
	u8 type;	//��������, 0 ��ʾ �����ã�1 ��ʾģ�鴦��,  2 ��ʾ���ش���
	u8 device_type;	//��ʾ����һ�ֲ�Ʒ������01��ȼ�ȣ�02�ǵ���
	u8 cmdCode;
	struct ctl_id id;	//�����ÿ���ID��ӳ��
	VANW_ITEM_T *item;
}VANW_AT_T;

/*����ṹ���ʾ���ĳһ�ֲ�Ʒ������*/
typedef struct vanw_produce{
	int atNum;			//�����Ʒ֧�ֵ�ATָ�������Ҳ��atListԪ�صĸ���
	VANW_AT_T *atList;	//Atָ����б�
	u8 device_type;			//��ʾ����һ�ֲ�Ʒ, ��ˮ������ȼ�����
	char *produceName;	//��Ʒ�����֣�Ҳ�൱��XM_AT_RET_LIST ��˵��
}VANW_PRO_T;

typedef struct vanw_cmd_info{
	char *at;	//ATָ��ͷ
	u8 type;	//��������, 0 ��ʾ �����ã�1 ��ʾģ�鴦��,  2 ��ʾ���ش���
	u8 device_type;	//��ʾ����һ�ֲ�Ʒ������01��ȼ�ȣ�02�ǵ���
	u8 cmdCode;
	struct ctl_id id;	//�����ÿ���ID��ӳ��
//	u32 conNUM;			//�����������������at����������ʱ��Ҫһһƥ���
	VANW_ITEM_T *item;

}VAN_CMD_T;

typedef struct vanw_produce_cmd{
	int atNum;
	VAN_CMD_T *cmdList;
	u8 device_type;
	char *produceName;
}VANW_PRO_CMD_T;



typedef struct head_p0{
	struct frame_head p0_head;
	u8 device_type;
	u8 answerAddr;
	u8 cmdCode;
}HEAD_P0_T;

typedef struct at_cmd{
	int error;
	VAN_CMD_T *xm_cmd;
	char xm_id[XM_ID_MAX];//���������豸ID
	u8 argc;
	u8 xm_set;		//��ʾ�����������, �ֱ������ã���ѯ״̬����ѯ����
	u8 xm_sendlen;
	XM_AT xm_at;

}AT_CMD_T;





#pragma pack(pop)
extern void printf_buf(char * text,unsigned char *pbuf,int len);
extern int BIN2HEX(char *	p_binstr, int bin_len, char * p_hexstr);
extern int HEX2BIN(char *	p_hexstr, char * p_binstr);
extern void xlf_crc(uchar *pbuf,uchar len,struct frame_crc *crc_buf);
int xlf_vanword_build(char *sendbuf ,char *buf,int conNum,u8 ctl_id_index,u8 device_type);
int xlf_vanword_pasre(char * retbuf,char *hexstr,u8 device_type);


#endif



