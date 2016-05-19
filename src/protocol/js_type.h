/*
 * ���ݽṹ�а�ָ�뾡������ǰ��
 */

#ifndef XLF_JS_TYPE__H
#define XLF_JS_TYPE__H
#include "cJSON.h"
#ifdef __cplusplus
extern "C" {
#endif

#define T_HEX	0
#define T_STR	1
#define T_BCD 	2


#pragma pack(push,1)

/*
 * �ַ�������ֵ��ӳ��
 */
#define END_KEY_VAL {NULL,0}
typedef struct key_val{
	char * key;
	u8 val;
}key_val_t;


/*
 * ÿ���ײ�Э��Ԫ�ض�Ӧ�Ľṹ
 * @text ��key==NULL��ʾ����
 */
#define END_POS {NULL,0,0,0,0}
typedef struct pos{
	key_val_t *text; //ӳ���
	u16 offset;		//��ʼ��ַ
	u16	takeLen;	// ռ�ó���
	u8	type_value;	// 0,HEX,BCD 255,����Ϊ�ַ���
	u8 preset;		// ��Ϊ0������Ԥ��ֵ�����ҪԤ��0�����ʼ��ʱ�Ѿ���ɣ�
}pos_t;

/*
 * ÿ��JSON�����Ӧ�Ľṹ
 * @extra_para ������ڣ����� start Ϊ0��ʾ����
 */
#define END_CMD_MAP {NULL,NULL,END_POS,END_POS}
typedef struct cmd_map{
	char *cmd;
	pos_t *set_extral;	//4
//	pos_t autoManual;
	pos_t set;	
	pos_t flag;	
}cmd_map_t;

/*
 * ÿ��JSON����Ӧ�Ľṹ
 * һ��cmd Ӧ�ö�Ӧ��һ�������Э�飬
 * ����cmd_type ��subtype��һһ��Ӧ��
 * ͬʱ�����õĲ�������Ҳ�Ƕ��ģ���·���ʶҲ�Ƕ���
 * @appHeadLenFlag 0����ʾ3�ֽڣ�1����ʾ5�ֽ�
 * @cmd_map ��cmd==NULL ��ʾ����
*/
#define END_PRO_CMD {NULL,NULL,0,0,0,0,0,0}
typedef struct pro_cmd{
	char *opt_cmd;	//��Ӧ��AT + "XXX" ����
	cmd_map_t *cmd_map;	
	u8 cmd_type;
	u8 cmd_subtype;
	u8 set_num;		//Ҫ���õĲ�������
	u8 ret_num;		//����,���ز�������
	u8 link_flag;	//��·���ʶ
	u8 appHeadLenFlag;	//Ӧ�ò��ײ����ȱ�ʶ
}pro_cmd_t;

/*
 * ��ʾ��һ�ֲ�Ʒ
 * @type �豸����
 * 
 * @cmdList Э���б� ��opt_cmdΪNULL��ʾ��Ľ���
 */
 #define END_PRO {NULL,NULL,0}
typedef struct pro{
	char *proName;
	pro_cmd_t *cmdList;
	u8 deviceType;
}pro_t;

#pragma pack(pop)


/*
 * �������ṩ�Ľӿ�
 *
 */





#ifdef __cplusplus
}
#endif
#endif //JS_TYPE.H


