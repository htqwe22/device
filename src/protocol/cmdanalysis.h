#ifndef _Included_cmdanalysis
#define _Included_cmdanalysis
/*
������������ת��ʮ�������ַ�
����:
p_binstr:����������
bin_len:���������鳤��
p_hexstr:���ɺ��ʮ�������ַ��������ַ
����:
����ʮ�������ַ�������
*/
int BIN2HEX(char *  p_binstr, int bin_len, char * p_hexstr);
/*
��ʮ�������ַ�ת�ɶ���������
����:
p_hexstr:ʮ�������ַ���
p_binstr:����������
����:
���������鳤��
*/
int HEX2BIN(char *  p_hexstr, char * p_binstr);
/*
�������� ���Ͳ������������ݺ��ж��Ƿ���Ҫ����
����:
pxm:socket ����ָ��
pnode:���ͽڵ�
����:
�������ڷ��ͽڵ�ṹ��
*/
void proc_cmd(XM_PROTOCOL *pxm,XM_NODE *pnode);
/*
����AT �����ַ���
����:
pxm:socket ����ָ��
pnode:���ͽڵ�
str:AT �����ַ���
strcnt:AT �����ַ�������
����:
��
*/
void strDividing(XM_PROTOCOL *pxm,XM_NODE *pnode,char * str,int strcnt);
/*
�����ؽ��
����:
pxm:socket ����ָ��
pnode:���ͽڵ�
pmsg:���������
code:������
����:
������
*/
uchar build_at_ret(XM_PROTOCOL *pxm,XM_NODE *pnode,char *pmsg,uchar code);
/*
��ȡָ�����豸��������ṹ
����:
address:�豸��ַ
cmd:������
sub:������
pbuf:��������
len:���ݳ���
����:
����ṹ��ָ��
*/
XM_Command * getcommand(uchar address,uchar cmd,uchar sub,char *pbuf,int len);
int Build_Send(XM_PROTOCOL *pxm,XM_NODE *pnode,uchar argc,char **argv);
#endif
