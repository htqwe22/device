#ifndef _Included_Recv
#define _Included_Recv
/*
�����������ݣ������ݱ�־���д���
����:
pxm:socket ����ָ��
pbuf:������յ����ݵ�ָ��
tcp_fd:��Ҫ���յ�socket ���
parse:���ݷ������ǿ���
����:
�������
*/
char recv_tcp(XM_PROTOCOL *pxm,uchar *pbuf,int tcp_fd,int parse);
#endif
