#ifndef _Included_Server
#define _Included_Server
typedef struct _server_arg{
	int xmlen;//�������
	int *pexit;//�˳���־λָ��
	char *serverport;//����˿�
}XM_SERVER;
/*
��������߳�
����:
tid_server:�߳̾��ָ��
server_port:����˿�
nexit:�˳���־λָ��
connect:�������
����:

*/
int servsr_start(pthread_t *tid_server,char * server_port,int *nexit,int connect);
/*
ֹͣ��������߳�
����:
����:
*/
void servsr_stop(void);

#endif
