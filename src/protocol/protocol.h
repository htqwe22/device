#ifndef _Included_Protocol
#define _Included_Protocol
#define XM_VER_MID 3
#define XM_VER_SID 2
#define XM_VER_LID 6

/*
v2.0 :
1.֧��102 64��ȡ
2.KTFL/KTSMָ��֧�� *  �ж��Ƿ�֧��
3.�߳���Ϊ32 ͬʱ֧����Ϊ128
V2.1:
1.�޸�ͬ����ʽ
2.�߳���Ϊ64 ͬʱ֧����Ϊ256
3.Ϊ��߱��ز���ͨ���ʣ��ڳ�ʱ��socket ����1�ֽڵ�����
4.����ɾ��ָ����socket
5.�����Ͻӿڼ���
V2.2:
1.��������豸��102 64 ֧���ж�
V2.3:
1.����exitSocket�ӿ�
2.����102_0/102_64ʹ�ñ��ػ�������
V2.4:
1.����ָ��˵��
2.�޸����ֲ���
3.����ָ�������ʽ
4.�����豸�¹̼��෵�������ֽڵĴ���
V2.5:
1.�޸��������������ʧ����
2.�޸���ѯ���������ݵĴ���
3.�޸������������������
4.��ʱ�޸��߳���������
V3.0:
1.֧��ID
2.���ٴ�����ֵ
3.�Ż��߳�ģ��
V3.0.1:
1.�޸İ汾�ţ�֧��"%d.%d.%d"��ʽ
2.�޸�ͬʱ֧�ֵ����������
3.����XMID,XMSSID����
V3.0.2
1.�����Чָ����쳣
2.�����ѯָ��������������
3.�����β�ѯʱ���������
4.�޸�����ִ�з���ֵ
5.�޸����������ʱ�ȴ�����
6.�޸���ʱ����δ����
7.�޸��˳��̴߳������
8.�ȴ��ϴ��������
9.�޸������ʧ��ʱ���ط�����(5-->1)
10.�޸����ʱ�ĵȴ�ʱ��(5-->1)
V3.0.3:
1.����ָ�����Ӳ��������ݶ�ָ��ƴ��
2.�޸�˯��ʱ��ֵ
3.��������Ϣ��ӡ
4.�޸������б��ȴ���
5.���������ʧ�ܺ�������ѯ����δ������
6.�������������ϵ����⣬����socket�˳�ʱ������ͽڵ�
7.����һ����������
8.����crc�ӿ�
9.֧��xcode����
10.����OTAָ��
11.�޸��߳��˳�����
v3.1.0
1.����ṹ����������ϸ��
2.�ָ�������
3.���ӽڵ�ȴ�״̬��־
v3.1.1
1.���ӻ�ȡ���Ľӿ�
2.�޸������������
3.���ӻ�ȡ��������ӿ�
4.�޸��쳣�˳�
5.�޸�KTZD�������
v3.1.2
1.֧���������
2.��鷵�����ݵ�ַ
3.��鷵�ص������뷢�͵������Ƿ�һ��
4.�л�cron��ʽͬ��
5.����ʧ��ʱ���ڸı�socket
6.��鷵�ص������Ƿ���ڲ���Ҫ��
v3.1.3
1.ȥ���Կ����յ�101ָ��������
2.����ָ��ͼ��200ms
v3.1.4
1.���ķ��ش������ʽ
2.ȥ������ʱ����ʱ����
3.���ĵ�ַ����Ĵ���λ��
4.���jniʱ�ڴ�й©
v3.1.5
1.�����ѯ�����������
2.ɾ����������Ĳ�ѯ
3.Э��汾���µ�0620
v3.1.6
1.����KTSS����
2.���ӳ�ʪ����������������λ
3.�޸�һЩ�����������
4.�޸�jni���ڴ�й©
5.�޸�����Լ������
6.���������ʾ
7.�ػ�ʱ��ȡ������
8.���������·���ʾ����ȷ������
v3.1.7
1.�޸��˿�ܣ�������socket����node����ʹ�ã��Լ�����̣߳�����˲������������⣻
2.��������ٶȵ����⣻
3.���XM_NODE���������⣻
4.�޸�һЩ�������⣬����Ҫʹ�ü���߳������������
v3.1.8
1.����˹ػ����ýڵ�ûȡ�������⣻
2.��������·��ŷ���ֵ��������⣻
3.��������ö�ʱ�ػ��������������⣻
4.���ýڵ����Ӹ�Ч����λ��ʹ�ϲ��ڿ��Ʋ��ýڵ�ʱ�ɹظ�Ч��
5.��������·���auto��sweepģʽ�ߵ������⣻
6.������XMCLS���
7.�޸��˷����ķ���ֵ��
8.������ȫ�Ƚ��������ֶ�/�Զ�����λ��ͬ����ȫ��0616Э�飻
v3.1.9
1.�����˴����βεĸ�������չ��7����֧��at����Ķ��������
2.����XMWIFI���
3.���Ӿ����뾲�����ٵİ󶨿��ƣ�
4.�����parse_data�������ó�������⣻
5.�ڷ�������ʱ�����ͬʱ���ؾ������Զ�λ���Ծ���λ���ȣ�
6.�����µ�Լ�������޸���KTKJ,KTYX,KTGX�Ĳ�����
7.�ڲ�֧��ktgn�Ĳ�ѯʱ������8�Ŵ���
v3.2.0
1.ͬ��ios�汾��
2.���apk���뱾��so���˳����޷��ٽ�������⣻
v3.2.1
1.���յ�����ͨ��ʧ�ܵĴ���(error=0),�Ѵ�����ת���ɷ�0����
2.���� XMCS XMSIP ����
3.�Է����ַ��������жϣ����Ϸ��ַ����ش�����XM_ERROR_MAX_CMD_IN_STRING_PARSE_ERROR;
v3.2.2
1.����˳�¿�����jni������
v 3.2.3
1 �ڱ��ص���so��ʹ��so���socket����ʱ���޸Ĳ����˳�ʱ�ر�socket
2,����socket�رմ���
v 3.2.4
1 ����XMEXIT���֪ͨWIFI�˳�socket����
2 �޸�build_packet�������ڴ�����豸��ָ��ʱ��ԭ�����ض�Ӧ���ַ�����
3 �޸�˯��ģʽ˳��
v3.2.5
1 �����˳�ʪ����ģʽ������
2 ������ȫ�Ƚ�������zd��ʾ��λ��
3 �ڷ�ָ��timeoutʱ�����ط�2�Σ�
4 �����µ�wifi����ָ������ϵ�ָ�����ڼ��ݣ�
v3.2.6
1  Ϊsmartbox���Ӷ�Ӧ�豸��ָ���ָ��һ�ο����豸���������
2  ���Ӿ�������ʪ�����ù��ܣ�
*/

#ifdef PLAT_LINUX
#include <jni.h>
#else
#ifndef JavaVM
#define JavaVM void
#endif
#endif



// ��ʼ���������
int xm_init_servsr(char * server_port,int connect);
// ֹͣ�������
void xm_stop_servsr(void);
// ��ȡ��ǰ ����ı���
char * xm_get_packet(int index);
// ��ȡ��ǰ ��������緵������
char * xm_get_parse(int index);
// ��ʼ��socket ����ͷ��ͽڵ�
void xm_init_index(JavaVM *pjvm,int connect_num,int send_num,int max_wait_node);
// ����ԭ���ӿ�
void xm_init(JavaVM *pjvm);
// ����ԭ���ӿڣ�ָ��Ϊ�յ�
int xm_init_withsocket(int socket);
// ʹ�ô����socket 
int xm_init_withsocket_index(int socketfd,int id);
// ����ԭ���ӿڣ�ָ��Ϊ�յ�
int init_socket_client(char * server_ip,char * server_port);
// ����socket 
int xm_init_socket_index(char * server_ip,char * server_port,int id,int reset);
// �˳������̺߳͹ر�����socket
int xm_exit(void);
// �ر�ָ��socket
int xm_exit_socket(int socketfd);
// ����AT ָ��
char * xm_send_index(int index,char *psend,int sendlen);
// ����ԭ���ӿ�
char * xm_send(char *psend);
// ��ȡ�汾��
char * xm_get_version(void);
//�����ýӿ�
int xm_init_flag(char * server_ip,char * server_port,int id,char cflag);
//�����ýӿ�, ������򷵻�ģ��ֵ
int xm_init_virtual(char * server_ip,char * server_port,int id);
//���socket �����socket ���
int xm_get_socket(int index);
//����ָ��������������socket ��������
int init_socket_client(char * server_ip,char * server_port);
//��ָ����socket �������socket ��������
int xm_init_flag_withsocket(int socket_fd,int id,char cflag);
//�����ݽ���crc ��֤
char * crc_data(char *buf,int len,char * strcrc);
//���ϴη��͵ı���
char * xm_get_packet(int index);
//���ϴη��صı���
char * xm_get_parse(int index);
//���ɱ���
char *xm_build_packet(char *pbuf,int *len,int address);
//��������
char * xm_parse_data(char *cmdpbuf,int cmdlen,char *pbuf,int len);
//��������Ĳ���
char *xm_build_para(char *pbuf,int *len);
//��������Ĳ���
char *xm_parse_para(char *cmdpbuf,int cmdlen,char *pbuf,int len);
/*
���ɷ��صı���
����:
status:״̬���泤�Ȳ���1k
pbuf:���յ�����
len:���ĳ���
����:
�ַ���
*/
char* xm_ret_cmd (char * status,char *pbuf,int *len);
int xlf_packet_build(int type_checksum,char sequence,char *sendbuf,char *buf,int buflen,int moblie_type,int moblie_address,int device_type,int device_address);
int js_build_cmd(char *sendbuf,char *buf,int device_type,int device_address,int moblie_type,int moblie_address);
int xlf_packet_pasre(char *retbuf,char *pbuf,int len,int address);

#endif
