#ifndef _Included_xm_type
#define _Included_xm_type

#include	<stdio.h>
#include	<stdlib.h>
#include    <string.h>
#include   <unistd.h>
#include    <pthread.h>
#include    <semaphore.h>
#include    <errno.h>
#include    <time.h>
#ifdef PLAT_LINUX
#include    <unistd.h>
#include    <sys/time.h>
#endif

#ifdef PLAT_LINUX
#ifdef XM_MEM_DEBUG
#include <mcheck.h>
#endif
#include <jni.h>
#else
#define JavaVM void
#endif
typedef unsigned char uchar;
typedef unsigned short ushort;
typedef	unsigned int uint;
typedef unsigned long ulong;
struct _at_fun;
#define USE_SEM 0
#define SEM_TIMEOUT 10
#define WAIT_TIMEOUT 100

#ifdef PLAT_LINUX
#ifdef ANDROID
#define  MAX_SEND_POOL 128
#define  XM_CONNECT_NUM 1
#else
#define  MAX_SEND_POOL 4096
#define  XM_CONNECT_NUM 1024
#endif
#else
#define  MAX_SEND_POOL 128
#define  XM_CONNECT_NUM 1
#endif
#define XM_RE_SEND 1
#define  MAX_CMD_NUM 64

//debug
#define DEBUG_VERIFY 0
#define DEBUG_MAIN 1
#define DEBUG_SEND 0
#define DEBUG_RECV 0
#define DEBUG_CRC 0
#define DEBUG_AT 0
#define DEBUG_SCOKET 0
#define DEBUG_THREAD 0
#define DEBUG_CMD 0
#define DEBUG_RS 1

#define TRUE	1
#define FALSE	0
#define XM_APP 0
#define XM_WITH_ID 1
#define XM_SEND_SETTING 1
#define XM_SEND_QUERY 0
#define XM_SEND_SUPPORT 2
#define XM_SEND_CONFIG 3

//**********************λ��������*********************************
#define SETB(x,y)	(x|=1<<y)	//��X�е�Yλ��1
#define CLRB(x,y)	(x&=~(1<<y))	//��X�е�Yλ��0
#define GETB(x,y)	(x&(1<<y))	//���X�е�Yλ����
#define XORB(x,y)	(x^=(1<<y))	//��X�е�Yλȡ��

//buf max
#define XM_ADDRES_MAX 24
#define XM_AT_MIN 3
#define XM_ID_MAX 32

#define XM_ERROR_MODUEL_RET_FAIL  0
#define XM_ERROR_MODUEL_NOT_SUPPORT  8
#define XM_ERROR_NET_SEND_FAIL  101
#define XM_ERROR_NET_RECV_FAIL  102
#define XM_ERROR_BUILD_PACKET_FAIL  103
#define XM_ERROR_RECV_FULL  104
#define XM_ERROR_RECV_TIMEOUT  105
#define XM_ERROR_SOCKET_FAIL  106
#define XM_ERROR_WAIT_MOER  107
#define XM_ERROR_VAIL  108
#define XM_ERROR_NOMACH_CMD  109
#define XM_ERROR_BUF_SMALL  110
#define XM_ERROR_PARAMETER  111
#define XM_ERROR_BUILD_MSG  112
#define XM_ERROR_MSG_SIZE  113
#define XM_ERROR_CONNECT  114
#define XM_ERROR_DNS  115
#define XM_ERROR_SOCKET_TIMEOUT  116
#define XM_ERROR_THEARD  117
#define XM_ERROR_NOT_INIT  118
#define XM_ERROR_CMD_NOT_SUPPORT  119
#define XM_ERROR_CMD_TYPE  120
#define XM_ERROR_CMD_EXEC  121
#define XM_ERROR_SOCKET_SEND  122
#define XM_ERROR_SOCKET_BREAK  123
#define XM_ERROR_INIT  124
#define XM_ERROR_AT_PRAR 125
#define XM_ERROR_NOT_SEND 126
#define XM_ERROR_LOCK 127
#define XM_ERROR_NODE 128
#define XM_ERROR_SOCKET_EXIT  129
#define XM_ERROR_MALLOC  130
#define XM_ERROR_INDEX  131
#define XM_ERROR_NODE_FULL  132
#define XM_ERROR_FORCE_CLOSE_NODE  133
#define XM_ERROR_FORCE_CLOSE_CONNETCTION  134


#define XM_ERROR_FRAME_MAX 10
#define XM_ERROR_FRAME_HEAD 11
#define XM_ERROR_FRAME_ACK 12
#define XM_ERROR_FRAME_SUPPORT 13
#define XM_ERROR_FRAME_FLAG 14
#define XM_ERROR_FRAME_UNKOWN 15
#define XM_ERROR_FRAME_SIZE 16
#define XM_ERROR_FRAME_CRC 17
#define XM_ERROR_FRAME_END 18
#define XM_ERROR_FRAME_END2 19
#define XM_ERROR_FRAME_MORE 20
#define XM_ERROR_NETWORK_ACK 21
#define XM_ERROR_NETWORK_SUPPORT 22
#define XM_ERROR_NETWORK_FLAG 23
#define XM_ERROR_NETWORK_UNKOWN 24
#define XM_ERROR_TRANSFER_ACK 25
#define XM_ERROR_TRANSFER_SUPPORT 26
#define XM_ERROR_TRANSFER_FLAG 27
#define XM_ERROR_TRANSFER_UNKOWN 28
#define XM_ERROR_DEV_ADDRESS 29
#define XM_ERROR_WIFI_ADDRESS 30
#define XM_ERROR_MAX_CMD_IN_ONE_SOCKET 31
#define XM_ERROR_MAX_CMD_IN_STRING_PARSE_ERROR 32

#define XM_SUCCESS 0

#define XM_ERROR_NO_BODY	33
#define XM_ERROR_NO_AT		34

/*Add by Tao He*/
/* type of Frame Check Sum*/
#define FCS_1BYTE_ADD 	0
#define FCS_2BYTES_ADD	1
#define FCS_2BYTES_CRC	2
#define FCS_4BYTES_CRC	3



//at cmd
#define MAX_CMD_PARAM_NUM 256
#define XM_MAX_BUF 1024
#define  XM_SELECT_TIMEOUT 2
#define  XM_SELECT_TIME 1
#define  XM_SELECT_TIME_US 0
#define MAX_AT_CMD_NUM 1
#pragma pack(1)
typedef struct _str2int{
	char *str;
	uchar  value;
}XM_Value;

typedef struct _offset_struct{
	ushort offset;//ƫ��
	ushort  len;//����
	uchar textlen;//ӳ�����
	XM_Value *text;//ӳ���
	uchar  support;//�ڹ��ܲ�ѯʱ��Ч
	uchar  query;//��״̬��ѯ ʱ��Ч
	uchar  set;//������ ʱ��Ч
	uchar preset;//Ԥ��ֵ,������ ʱ�Զ���Ч
}XM_Offset;

typedef struct _command_struct{
	uchar  send_num;//���͵Ĳ�������
	uchar  recv_num;//���յĲ�������
	uchar  set_len;//���÷����ַ�����
	uchar  query_len;//״̬�����ַ�����
	uchar  support_len;//����֧�ֲ�ѯ�����ַ�����
	uchar  set_cmd;//���õ�����
	uchar  set_sub;//����������
	uchar  query_cmd;//״̬������
	uchar  query_sub;//״̬��������
	uchar  support_cmd;//����֧�ֲ�ѯ������
	uchar  support_sub;//����֧�ֲ�ѯ��������
	XM_Offset send[MAX_CMD_PARAM_NUM];//���Ͳ�����
	XM_Offset recv[MAX_CMD_PARAM_NUM];//���ղ�����
}XM_Command;

typedef struct _xm_at{
/*����ָ����������*/ 
	char *getcmd;
	char *getparam[MAX_CMD_PARAM_NUM];
	char XM_At_Buffer[XM_MAX_BUF]; //������������
	char XM_At_Ret[XM_MAX_BUF]; //���淵�ؽ��
}XM_AT;

typedef struct _xm_protocol_status{
	uchar	XM_KL_Frame_Ack;		   //Usart0���߽���֡Ӧ��
	uchar	XM_KL_Frame_Size_Count; 		   //Usart0���߽���֡�����ֽ�������
	uchar	XM_KL_Frame_Checksum_Type;
	uchar	XM_KL_Frame_Checksum_Count; 	   //Usart0���߽���У��ͽ�������
	uchar	XM_KL_Frame_Flag_1; 	   //Usart0���߽���֡��ʶ1
	uchar	XM_KL_Frame_Flag_2; 	   //Usart0���߽���֡��ʶ2
	ushort	XM_KL_Frame_Size;			   //Usart0���߽���֡����������ĳ���
	uint	XM_KL_Frame_Checksum;		   //Usart0���߽���У���
	uchar	XM_KL_Network_Ack;		   //Usart0���߽�������Ӧ��
	uchar	XM_KL_Network_Flag_1;		   //Usart0���߽��������ʶ1
	uchar	XM_KL_Network_Address_Struct;			   //�����ַ�ṹ
	uchar	XM_KL_Network_Address_Type; 		   //�����ַ����
	uchar	XM_KL_Network_Address_All;			   //�����ַ����
	uchar	XM_KL_Network_Address_Count;		   //Usart0���߽��������ַ����
	uchar	XM_KL_Network_Flag_2;		   //Usart0���߽��������ʶ2
	uchar	XM_KL_Network_Address_Len;		   //Usart0���߽��������ַ�ֽ���
	uchar	*P_XM_KL_Network_Address_1; 		   //Usart0���߽���֡��ַ1
	uchar	*P_XM_KL_Network_Address_2; 		   //Usart0���߽���֡��ַ2
	uchar	*P_XM_KL_Network_Address_3; 		   //Usart0���߽���֡��ַ3
	uchar	*P_XM_KL_Network_Address_4; 		   //Usart0���߽���֡��ַ4
	uchar	*P_XM_KL_Network_Address_5; 		   //Usart0���߽���֡��ַ5
	uchar	XM_KL_Transfer_Ack; 	   //Usart0���߽��մ���Ӧ��
	uchar	XM_KL_Transfer_Flag_1;		   //Usart0���߽��մ����ʶ1
	uchar	XM_KL_Transfer_Encryption_Type; 		   //Ӧ�ü�������
	uchar	XM_KL_Transfer_Retry_Count; 		   //Ӧ���ش�����
	uchar	XM_KL_Transfer_Flag_2;		   //Usart0���߽��մ����ʶ2
	uchar	XM_KL_Transfer_Encryption;		   //Usart0���߽��մ������ָ��
	uchar	*P_XM_KL_Recv_Frame;		//USART0���������ָ��	
	//����״̬����
	uchar	XM_KL_Status;			   //֡��������
	uchar	XM_KL_Recv_Count;		   //��ǰ״̬��Ч�ַ���
	uchar	XM_KL_More_Flag;			   //���ڵڶ���ʶ
	uchar	*P_XM_KL_Crc;		// CRC��ʼ
	uchar	*P_XM_KL_Link_Msg;		//��Ϣͷ

	uchar oldValue;	
	uchar LenCount;
	uchar CrcCount;
	uchar CrcLen;
	short PacketLen;	
	uchar AddresCount;
	uint PacketAddressLen;
	uint MsgLen;
	uchar IsHaveHead;
	ushort xm_error;

}XM_PROTOCOL_STATUS;

struct frame_head{
	uchar head1;
	uchar head2;
};
struct frame_end{
	uchar end1;
	uchar end2;
};
struct frame_struct{
	uchar ack;
	uchar flag;
	uchar len;
};
struct frame_crc{
	uchar crc_high;
	uchar crc_low;
};
struct network_struct{
	uchar ack;
	uchar flag;
	uchar destination_module;
	uchar destination_no;
	uchar source_module;
	uchar source_no;	
};
struct transfer_struct{
	uchar ack;
	uchar flag;
};
struct message_struct{
	uchar type;
	uchar sub;
	uchar respon;
	uchar frame;
	uchar frameno;
	uchar data[255];	
	uchar source_module;
	uchar source_no;
	uchar destination_module;
	uchar destination_no;
	int error;
	int use_size;
	int data_size;
};

#pragma pack( )

typedef struct _xm_sync{
#if USE_SEM
	sem_t sem;
#else
	pthread_cond_t cond;
#endif
	pthread_mutex_t mutex;
	int value;
	int is_wait;
	time_t timeout;	//����ʱ��ʱ��	
}XM_SYNC;
#define TP_DATA_IS_WAIT(psync) \
do \
{ \
	while(1) \
	{ \
		pthread_mutex_lock(&psync->mutex); \
		if(psync->is_wait) \
		{ \
			pthread_mutex_unlock(&psync->mutex); \
			break; \
		} \
		pthread_mutex_unlock(&psync->mutex); \
		sleep(1); \
	} \
}while(0)

typedef struct _xm_node{
	XM_SYNC sync;
#if XM_WITH_ID
	char xm_id[XM_ID_MAX];//���������豸ID
#endif
	char *atbuf;//AT �����
	int atlen;//AT �����ĳ���
	int xm_sendlen;//��Ҫ���͵��ֽ���
	int index;//��Ӧsocket �������е����
	int id;//�ڵ�����
	uchar is_wait;//�ڵ��ڵȴ�״̬
	uchar address;//�豸��ַ
	uchar argc;//AT ����Ĳ�������
	uchar errorid;	//�������
	uchar xm_set;//��ʾ�����������, �ֱ������ã���ѯ״̬����ѯ����
	uchar xm_sendready;//���� ׼����
	XM_AT xm_at;//AT �ṹ������AT ��������ݺͷ�����������Լ����ؽ��
	struct _at_fun *xm_cmd;//���ڴ��������ṹָ��
	struct _xm_node *end;//��һ���ڵ�
	
}XM_NODE;

typedef struct _xm_protocol{
	pthread_mutex_t mutex;
#if XM_WITH_ID
	char xm_id[XM_ID_MAX];
#endif
	XM_NODE *node;//���ͽڵ�ָ�룬��������ṹ��Ŀǰֻ֧��һ���ڵ�
	int xm_socket_client;//socket ���
	int xm_index;//�����е����
	time_t timeout;	//����ʱ��ʱ��
	uchar xm_addres;//�豸��ַ
	uchar xm_frame;//�豸֡���
	uchar xm_sub_frame;//�豸֡�����
	uchar	XM_Frame_Buffer[XM_MAX_BUF]; //֡����
	uchar xm_addres_type;//��ַ����,���Э���ĵ�
	uchar xm_addres_count;//��ַ����,���Э���ĵ�
	uchar xm_addres_all;//�Ƿ���ȫ����ַ��Ч,���Э���ĵ�
	uchar xm_addres_struct;//��ַ����ɷ�ʽ,���Э���ĵ�
	uchar xm_crc_type;//У������,���Э���ĵ�
	uchar xm_encryption_type;//��������,���Э���ĵ�
	uchar xm_exit;//�˳���־	
	uchar xm_seting;//��Ҫ��������
	uchar XM_Status_Buffer[XM_MAX_BUF];//����״̬
	uchar XM_Setting_Buffer[XM_MAX_BUF];//������������
	uchar XM_Status_Value[XM_MAX_BUF];	//��ʱ������
	char XM_At_Send[XM_MAX_BUF]; //���淢�͵�����
	char XM_At_Recv[XM_MAX_BUF]; //������յķ���
	uchar	*xm_addres_1;//��ַ1 ,���Э���ĵ�
	uchar	*xm_addres_2;//��ַ2 ,���Э���ĵ�
	uchar	*xm_addres_3;//��ַ3 ,���Э���ĵ�
	uchar	*xm_addres_4;//��ַ4 ,���Э���ĵ�
	uchar	*xm_addres_5;//��ַ5 ,���Э���ĵ�
	int	xm_waitsend;//��ʾ�Ƿ���Ҫ�ȴ�����
	uchar	xm_send;//��ʾ�Ƿ���Ҫ����
	uchar	xm_sendready;//����׼���ã��ȴ�����
	uchar	xm_parse;//��Ҫ�Է��ؽ�����з���
	uchar   sendcmd;//�ϴε�������
	uchar   sendsub;//�ϴε�������
	XM_PROTOCOL_STATUS xm_status;//����ֵ���� ��״̬����	
	char *getparam[MAX_CMD_PARAM_NUM];//AT �Ĳ���ָ��
	int node_count; //һ��socket���������͸���
	int resend_count;//�ط��Ĵ�����Ŀǰ�ط�3��
	int xm_sended;//��ʾ�ѷ���
	// ADD by Tao He
	uchar frame_flag; //��ʾ�Ƿ��ж���������ֽڵ�frame����frame NO
}XM_PROTOCOL;

typedef struct _xm_server_map{
#if XM_WITH_ID
	char xm_id[XM_ID_MAX];
#endif
	int xm_socket_client;
	int xm_socket_module;
	int xm_module_id;
	int xm_socket_virtual;
	int client_ip_addr;
	int client_l4_port;
	int module_ip_addr;
	int module_l4_port;
	XM_PROTOCOL xm_protocl;
}XM_SERVER_MAP;

typedef struct _at_fun{
	char *cmd;// AT ��������
	uchar (*set)(XM_PROTOCOL *pxm,XM_NODE *pnode,uchar *pbuf,uchar argc,char **argv);//������
	uchar type;	//��������, 0 ��ʾ �����ã�1 ��ʾģ�鴦��,  2 ��ʾ���ش���
	XM_Command *parameter;//�������
}XM_AT_FUN;

typedef struct _at_return{
	char *cmd;//AT
	uchar type;// ��������
	uchar major;// ������
	uchar minor;// ������
	XM_Command *parameter;//�������
}XM_AT_RET;

typedef struct _at_fun_lsit{
	int listnum;//����ڵ���
	XM_AT_FUN *funlist; //��������
	uchar type;	//�豸��ַ
	char * cmddesc;	//˵�� 
}XM_AT_LIST;

typedef struct _at_fun_ret_lsit{
	int listnum;//����ڵ���
	XM_AT_RET *funlist; //��������
	uchar type;	//�豸��ַ
	char * cmddesc;	//˵�� 
}XM_AT_RET_LIST;

void xm_wait_init(XM_SYNC * psync);
void xm_wait_sync(XM_SYNC * psync);
void xm_wait_lock(XM_SYNC * psync);
void xm_wait_signal(XM_SYNC * psync);
void xm_wait_broadcast(XM_SYNC * psync);
void xm_wait_unlock(XM_SYNC * psync);
#endif
