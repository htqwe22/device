/*********************KDA-1131-V01.h***********************
author:		ChenJianbo
edit date:	2012.11.26

**********************************************************/
#ifndef _Included_Hisense
#define _Included_Hisense

//**********************ͨ��֡�����ֶ���***************************
#define BAG_HEAD1	0xf4
#define BAG_HEAD2	0xf5
#define	Extension_Byte	0xf4		//������F4����չ�ֽ�	
#define BAG_END1	0xf4
#define BAG_END2	0xfb
#define XM_ACK_FAIL 0
#define XM_ACK_SUCC 1
#define XM_ACK_NOT_SUPPORT 8
#define XM_FLAG_TWO 1
#define XM_FLAG_ADD 0
#define XM_FLAG_SHORTADD 1
#define XM_FLAG_SHORTCRC 2
#define XM_FLAG_CRC 3

#define XM_ACK_CEHCK(x)  (x!=XM_ACK_SUCC)
/*
��ʼ��socket �ṹ��Э���������,Ŀǰָ�� У����Ϊ���ֽ�
����:
pxm:socket ����ָ��
����:
��
*/
void statusInit(XM_PROTOCOL * pxm);
/*
��������ִ�н������ȷʱ�� ��build_at_ret
����:
pxm:socket ����ָ��
pMsgHead:��Ϣͷָ��,��Ϊ���������Ǹ�������ͷ���棬�������ģ�����ֱ��תȡ����
len:���ݳ���
����:
������
*/
uchar Proc_msg(XM_PROTOCOL *pxm,MessageHead * pMsgHead,uchar len);

/*
�����������Ҫ������ֱ�ӿ������յ�������
����:
pxm:socket ����ָ��
pMsgHead:��Ϣͷָ��,��Ϊ���������Ǹ�������ͷ���棬�������ģ�����ֱ��תȡ����
len:���ݳ���
����:
������
*/
uchar Proc_recv(XM_PROTOCOL *pxm,MessageHead * pMsgHead,uchar len);
/*
�Խ��յ����ݽ��з��������ֽڽ��У����ݻ�����XM_Frame_Buffer
����:
pxm:socket ����ָ��
cstr:�ֽ�
msg:���������
����:
������,����XM_ERROR_WAIT_MOER ��ʾ��Ҫ��������
*/
uchar Parse_Read (XM_PROTOCOL *pxm,uchar *cstr,uchar (*msg)(XM_PROTOCOL *pxm,MessageHead * pMsgHead,uchar len));

/*
���ɱ���
����:
pData:���汨�ĵ�ָ��
pbuf:���������
MsgLen:��������ݵĳ���
....����Ϊ���Ĳ���
����:
���ĳ���
*/
uchar Parse_Send (uchar *pData,uchar *pbuf,uchar MsgLen,uchar * Address1,uchar * Address2,uchar * Address3,uchar * Address4,uchar * Address5,uchar Address_Count,uchar Address_All,uchar Address_Type,uchar Address_Struct,uchar EncryptionType,uchar CrcType,uchar nret,uchar Transfer_flag2,uchar Network_flag2,uchar Frame_flag2,uchar Encryption,uchar Retry);
//------------------------end------------------------------
#endif
