#ifndef _Included_Send
#define _Included_Send

typedef struct _send_arg{
	pthread_mutex_t *pmutex;
	XM_PROTOCOL *pxm;
	int xmlen;
	int *pexit;
	JavaVM *pjvm;
}XM_SEND;
/*
�����߳�
����:
arg:����
����:
*/
void *send_thread(void * arg);
/*
����һ�����ݰ��������շ���
����:
pxm:socket ����ָ��
pbuf:��Ҫ���͵�����
len:���ݳ���
����:
�������
*/
uchar send_tcp(XM_PROTOCOL *pxm,uchar *pbuf,uchar len);
/*
����һ���ڵ������,�ȷ���AT ����ٵ� ��proc_cmd �������� ׼�������� �����߳���ɷ���
����:
pxm:socket ����ָ��
pnode:���ͽڵ�
����:
��������ڷ��ͽڵ���
*/
void send_data(XM_PROTOCOL *pxm,XM_NODE * pnode);
#endif
