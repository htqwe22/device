#ifndef _Included_Client
#define _Included_Client

/*
�ڽڵ������м���һ�����ͽڵ�
����:
index: socket ��������
atcmd:Ҫ���͵�AT ����
len:AT ����ĳ���
nexit:�˳���־λ��ָ��
����:
�ڵ����ݵ�ָ��
*/
XM_NODE * client_new_node(int index,char *atcmd,int len,int *nexit);
/*
����:
tid_send: �߳̾����ָ��
nexit:�˳���־λ��ָ��
����:
*/
void client_clean_client(JavaVM *pjvm,pthread_t *tid_send,int *nexit);
/*
��ʼ��socket����ͷ��ͽڵ�
����:
tid_send: �߳̾����ָ��
nexit:�˳���־λ��ָ��
connect_num:���������
send_num:�������
����:
�ɹ�����0
*/
int client_init_client(JavaVM *pjvm,pthread_t *tid_send,int *nexit,int connect_num,int send_num);
/*
����:
index: socket ��������
����:
socket�����������-1
*/
int client_get_socket(int index);
/*
��ȡsocket ��������
����:
socket_fd: socket���
����:
socket �������ţ�������-1
*/
int client_get_index(int socket_fd);
/*
��ȡsocket�����ָ��
����:
index: socket ��������
����:
socket�����ָ��
*/
XM_PROTOCOL * client_get_client(int index);
/*
��ʼ��ȫ����
����:
����:
*/
void client_init_lock(void);
/*
���ָ����socket�������ؽڵ�, ���ر�socket
����:
socketfd:socket���
����:
�ɹ�Ϊ0
*/
int client_exit_client(int socketfd);
/*
��socket �����м���һ��socket���
����:
socket:socket���
id:�豸��ַ
����:
����socket ����ָ��,������NULL
*/
XM_PROTOCOL * client_new_index(int socket,int id);
void client_clear_socket();
#endif
