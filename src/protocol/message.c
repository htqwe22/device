/*
 * Copyright 2009-2011 Cedric Priscal
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include	"xmlog.h"
#include	"xm_type.h"
#include    "protocol.h"
#include	"message.h"
#include	"hisense.h"
#include	"cmdanalysis.h"

uchar New_Msg_Head(XM_PROTOCOL *pxm,uchar * pbuf,uchar Type,uchar SubType,uchar *pData,int DataLen){	
	MessageHead *pMsg=NULL;
	if((!pData && DataLen) || !pbuf){
		XM_E("ERROR head:buff is null\r\n");
		return 0;
	}
	if(Type==0 && SubType==0){
		XM_E("ERROR head:type is error\r\n");
		return 0;
	}
#if DEBUG_AT
	XM_D("build cmd:%p %d\r\n",pData,DataLen);
#endif
#if DEBUG_CMD
	XM_D("New_Msg_Head frame=%d sub_frame=%d\r\n",pxm->xm_frame,pxm->xm_sub_frame);
#endif
	if(pbuf){		
		memset(pbuf,'\0',sizeof(MessageHead));
		pMsg=(MessageHead *)pbuf;
		pMsg->MessageType=Type;
		pMsg->MessageSubType=SubType;
		if (pxm->frame_flag == 1)
			{
			#if DEBUG_CMD
			XM_D("pxm->xm_frame!=0xff\r\n");
			#endif
			pMsg->frame=pxm->xm_frame;
			pMsg->sub_frame=pxm->xm_sub_frame;
			memcpy(pbuf+sizeof(MessageHead),pData,DataLen);
			return sizeof(MessageHead)+DataLen;
			}
		else
			{
			#if DEBUG_CMD
			XM_D("pxm->xm_frame=0xff\r\n");
			#endif
			memcpy(pbuf+(sizeof(MessageHead)-2),pData,DataLen);
			return sizeof(MessageHead)-2+DataLen;
			}
	}
	return sizeof(MessageHead)+DataLen;
}

uchar Proc_Result(XM_PROTOCOL *pxm,MessageHead * pMsg,uchar len){
	int minlen=0;
	char *pbuf=(char *)pMsg;
	uchar MessageHead_len=sizeof(MessageHead);
	#if 1
	XM_D("msg: pxm %p pMsgHead %p len %d MessageHead_len %d\r\n",pxm,pMsg,len,MessageHead_len);
	#endif
	if (pMsg->MessageType < 215 )
		{
		XM_E("Proc_Result: unframe packet! len-2!\r\n");
		MessageHead_len=sizeof(MessageHead)-2;
		}
	if(len<MessageHead_len){
		XM_E("ERROR ret:msg size error\r\n");
		return XM_ERROR_MSG_SIZE;
	}
	if(pxm->node->xm_cmd && pxm->node->xm_cmd->parameter && pxm && pxm->node){
#if DEBUG_CMD
		XM_D("Result:len %d set %d \r\n",len,pxm->node->xm_set);
#endif
		if(pxm->node->xm_set==XM_SEND_SUPPORT){
			minlen=pxm->node->xm_cmd->parameter->support_len;
		}
		if(pxm->node->xm_set==XM_SEND_QUERY){
			minlen=pxm->node->xm_cmd->parameter->query_len;
		}
		if(len >= (MessageHead_len+minlen)){
			memcpy(pxm->XM_Status_Buffer,pbuf+MessageHead_len,len-MessageHead_len);
#if DEBUG_CMD
			printf_buf("Result:",pxm->XM_Status_Buffer,pxm->node->xm_cmd->parameter->query_len);
#endif
			return !(pMsg->Result==1);
		}		
	}
	XM_E("ERROR ret:msg type error\r\n");
	return XM_ERROR_MSG_SIZE;
}


XM_Command xm_KLXSJ={//�´�������
	3,
	0,
	132,
	2,
	0,
	1,
	3,	
	0,
	0,
	0,
	0,
	{
		{7,8,0,NULL,0,1,1,0},
		{15,8,0,NULL,0,1,1,0},
		{1055,1040,0,NULL,0,0,1,0},
	},
	{
	}
};


XM_Command xm_KLKJ={//��������
	0,
	0,
	0,
	0,
	0,
	3,
	1,
	0,
	0,
	0,
	0,
	{
	},
	{
	}
};


XM_Command xm_KLGJ={//�ػ�����
	0,
	0,
	0,
	0,
	0,
	3,
	0,
	0,
	0,
	0,
	0,
	{
	},
	{
	}
};


XM_Command xm_KLCS={//��ѯ���豸��
	0,
	1,
	0,
	16,
	0,
	0,
	0,
	4,
	0,
	0,
	0,
	{		
	},
	{
		{127,128,0,NULL,0,1,0,0},
	}
};


XM_Command xm_KLGXDZ={//��д�豸��ַ����
	3,
	0,
	18,
	18,
	0,
	5,
	0,
	0,
	0,
	0,
	0,
	{
		{127,128,0,NULL,0,0,1,0},
		{135,8,0,NULL,0,0,1,0},
		{142,8,0,NULL,0,0,1,0},
	},
	{
		
	}
};


XM_Command xm_KLCXB={//��ѯ�豸����Ͱ汾����
	0,
	4,
	0,
	4,
	0,
	7,
	1,
	7,
	1,
	0,
	0,	
	{
	},
	{
		{7,8,0,NULL,0,1,0,0},
		{15,8,0,NULL,0,1,0,0},
		{23,8,0,NULL,0,1,0,0},
		{31,8,0,NULL,0,1,0,0},
	}
};


XM_Command xm_KLCCM={//��ѯ˫MCU�豸������汾�ź�Э��汾��
	0,
	3,
	0,
	98,
	0,	
	0,
	0,
	7,
	4,
	0,
	0,
	{
	},
	{
		{7,8,0,NULL,0,1,0,0},
		{15,8,0,NULL,0,1,0,0},
		{783,768,0,NULL,0,1,0,0}
	}
};


XM_Command xm_KLBL={//������λ��������Ȩת��
	0,
	2,
	0,
	2,
	0,
	0,
	0,
	9,
	2,
	0,
	0,
	{
	},
	{
		{7,8,0,NULL,0,1,0,0},
		{15,8,0,NULL,0,1,0,0},
	}
};


XM_Command xm_KLQDDM={//ǿ�ƶ�ȡ�豸��ַ��
	3,
	3,
	18,
	18,
	0,
	10,
	1,
	10,
	0,
	0,
	0,
	{
		{7,8,0,NULL,0,0,1,0},
		{15,8,0,NULL,0,0,1,0},
		{143,128,0,NULL,0,0,1,0},
	},
	{
		{7,8,0,NULL,0,1,0,0},
		{15,8,0,NULL,0,1,0,0},
		{143,128,0,NULL,0,1,0,0},
	}
};


XM_Command xm_KLQDDM3={//ǿ�ƶ�ȡ�豸��ַ��3
	0,
	2,
	0,
	2,
	0,
	0,
	0,
	10,
	4,
	0,
	0,
	{
	},
	{
		{7,8,0,NULL,0,1,0,0},
		{15,8,0,NULL,0,1,0,0},
	}
};

XM_Value xm_BAUND2value[]={
		{"1.2k",1},
		{"2.4k",2},
		{"4.8k",3},
		{"9.6k",4},
		{"14.4k",5},
		{"28.8k",6},
		{"38.4k",7},
		{"57.6k",8},
		{"76.8K",9},
		{"115.2k",10},
		{"250k",11},
		{"500k",12},
		
};

XM_Command xm_KLBAUND={//���ÿյ���ͨ�Ų�����1
	1,
	0,
	1,
	1,
	0,
	26,
	0,
	0,
	0,
	0,
	0,
	{
		{7,8,sizeof(xm_BAUND2value)/sizeof(xm_BAUND2value[0]),xm_BAUND2value,0,0,1,0},
	},
	{
	}
};


XM_Command xm_KLKZJ={//���ư�֮����Ϣ����
	2,
	2,
	2,
	2,
	0,
	30,
	0,
	0,
	0,
	0,
	0,
	{
		{7,8,0,NULL,0,0,1,0},
		{15,8,0,NULL,0,0,1,0}
	},
	{
		{7,8,0,NULL,0,1,0,0},
		{15,8,0,NULL,0,1,0,0}
	}
};


XM_Command xm_KLXZT={//��д״̬��������33
	8,
	8,
	8,
	8,
	0,
	101,
	32,
	102,
	32,
	0,
	0,	
	{
		{7,8,0,NULL,0,0,1,0},
		{15,8,0,NULL,0,0,1,0},
		{23,8,0,NULL,0,0,1,0},
		{31,8,0,NULL,0,0,1,0},
		{39,8,0,NULL,0,0,1,0},
		{47,8,0,NULL,0,0,1,0},
		{55,8,0,NULL,0,0,1,0},
		{63,8,0,NULL,0,0,1,0}
	},
	{
		{7,8,0,NULL,0,1,0,0},
		{15,8,0,NULL,0,1,0,0},
		{23,8,0,NULL,0,1,0,0},
		{31,8,0,NULL,0,1,0,0},
		{39,8,0,NULL,0,1,0,0},
		{47,8,0,NULL,0,1,0,0},
		{55,8,0,NULL,0,1,0,0},
		{63,8,0,NULL,0,1,0,0}
	}
};


XM_Command xm_KLDDLC={//��ѯ�豸����ʹ�ù��ĵ���
	0,
	4,
	0,
	18,
	0,
	0,
	0,
	102,
	48,
	0,
	0,
	{
	},
	{
		{7,8,0,NULL,0,1,0,0},
		{15,8,0,NULL,0,1,0,0},
		{23,8,0,NULL,0,1,0,0},
		{31,8,0,NULL,0,1,0,0},
	}
};


XM_Command xm_KLDDLT={//��ѯ�豸����ʹ�ù��ĵ���
	0,
	1,
	0,
	18,
	0,
	0,
	0,
	102,
	48,
	0,
	0,
	{
	},
	{
		{39,8,0,NULL,0,1,0,0},
	}
};


XM_Command xm_KLDDLZ={//��ѯ�豸����ʹ�ù��ĵ���
	0,
	2,
	0,
	18,
	0,
	0,
	0,
	102,
	48,
	0,
	0,
	{
	},
	{
		{47,8,0,NULL,0,1,0,0},
		{55,8,0,NULL,0,1,0,0},
	}
};


XM_Command xm_KLDDLY={//��ѯ�豸����ʹ�ù��ĵ���
	0,
	2,
	0,
	18,
	0,
	0,
	0,
	102,
	48,
	0,
	0,
	{
	},
	{
		{63,8,0,NULL,0,1,0,0},
		{71,8,0,NULL,0,1,0,0},
	}
};


XM_Command xm_KLDDLJ={//��ѯ�豸����ʹ�ù��ĵ���
	0,
	2,
	0,
	18,
	0,
	0,
	0,
	102,
	48,
	0,
	0,
	{
	},
	{
		{79,8,0,NULL,0,1,0,0},
		{87,8,0,NULL,0,1,0,0},
	}
};


XM_Command xm_KLDDLB={//��ѯ�豸����ʹ�ù��ĵ���
	0,
	2,
	0,
	18,
	0,
	0,
	0,
	102,
	48,
	0,
	0,
	{
	},
	{
		{95,8,0,NULL,0,1,0,0},
		{103,8,0,NULL,0,1,0,0},
	}
};


XM_Command xm_KLDDLN={//��ѯ�豸����ʹ�ù��ĵ���
	0,
	2,
	0,
	18,
	0,
	0,
	0,
	102,
	48,
	0,
	0,
	{
	},
	{
		{111,8,0,NULL,0,1,0,0},
		{119,8,0,NULL,0,1,0,0},
	}
};


XM_Command xm_KLDDL={//��ѯ�豸ʹ�ù��ĵ���
	0,
	4,
	0,
	18,
	0,
	0,
	0,
	102,
	48,
	0,
	0,
	{
	},
	{
		{127,8,0,NULL,0,1,0,0},
		{135,8,0,NULL,0,1,0,0},
		{143,8,0,NULL,0,1,0,0},
		{151,8,0,NULL,0,1,0,0},
	}
};

XM_Command xm_KLXYM={//�豸��Ϣ������
	4,
	4,
	26,
	26,
	0,
	103,
	1,
	103,
	0,
	0,
	0,
	{
		{7,8,0,NULL,0,0,1,0},//��һ���ֽڴ�����������0��ʾʹ��BCD���룬
		{191,184,0,NULL,0,0,1,0},//����23���ֽڱ�ʾ���ݣ�
		{199,8,0,NULL,0,0,1,0},//��2�ֽ�Ϊ�ۼӺ�
		{207,8,0,NULL,0,0,1,0},//��2�ֽ�Ϊ�ۼӺ�
	},
	{
		{7,8,0,NULL,0,1,0,0},//��һ���ֽڴ�����������0��ʾʹ��BCD���룬
		{191,184,0,NULL,0,1,0,0},//����23���ֽڱ�ʾ���ݣ�
		{199,8,0,NULL,0,1,0,0},//��2�ֽ�Ϊ�ۼӺ�
		{207,8,0,NULL,0,1,0,0},//��2�ֽ�Ϊ�ۼӺ�
	}
};


XM_Command xm_EXITHOST={
	0,
	2,
	0,
	2,
	0,
	9,
	2,
	9,
	2,
	0,
	0,
	{
	},
	{
		{7,8,0,NULL,0,1,0,0}, //Ӧ������IP��ַ���λ
		{15,8,0,NULL,0,1,0,0},//Ӧ������IP��ַ���λ
	}
};


XM_AT_RET at_cmd_ret_kl[8]={
		{"KLXYM",XM_SEND_QUERY,103,0,&xm_KLXYM},
		{"KLKZJ",XM_SEND_QUERY,30,0,&xm_KLKZJ},
		{"KLQDDM3",XM_SEND_QUERY,10,4,&xm_KLQDDM3},
		{"KLKJ",XM_SEND_SETTING,3,1,&xm_KLKJ},//��������
		{"KLGJ",XM_SEND_SETTING,3,0,&xm_KLGJ},//�ػ�����
		{"KLXZT",XM_SEND_SETTING,101,32,&xm_KLXZT},//��д״̬��������33
		{"EXITHOST",XM_SEND_SETTING,9,2,&xm_EXITHOST},
		{"KLCXB",XM_SEND_QUERY,7,1,&xm_KLCXB}, //��ѯ˫MCU�豸������汾�ź�Э��汾��
};

XM_AT_FUN at_cmd_kl[23]={
	{"KLXZT",NULL,0,&xm_KLXZT},//��д״̬��������33
	{"KLDDLC",NULL,0,&xm_KLDDLC},//��ѯ�豸����ʹ�ù��ĵ���
	{"KLDDLT",NULL,0,&xm_KLDDLT},//��ѯ�豸����ʹ�ù��ĵ���
	{"KLDDLZ",NULL,0,&xm_KLDDLZ},//��ѯ�豸����ʹ�ù��ĵ���
	{"KLDDLY",NULL,0,&xm_KLDDLY},//��ѯ�豸����ʹ�ù��ĵ���
	{"KLDDLJ",NULL,0,&xm_KLDDLJ},//��ѯ�豸����ʹ�ù��ĵ���
	{"KLDDLB",NULL,0,&xm_KLDDLB},//��ѯ�豸����ʹ�ù��ĵ���
	{"KLDDLN",NULL,0,&xm_KLDDLN},//��ѯ�豸����ʹ�ù��ĵ���
	{"KLDDL",NULL,0,&xm_KLDDL},//��ѯ�豸ʹ�ù��ĵ���
	{"KLXSJ",NULL,0,&xm_KLXSJ},//�´�����������
	{"KLKJ",NULL,0,&xm_KLKJ},//��������
	{"KLGJ",NULL,0,&xm_KLGJ},//�ػ�����
	{"KLCS",NULL,0,&xm_KLCS},//��ѯ���豸��
	{"KLGXDZ",NULL,0,&xm_KLGXDZ},//��д�豸��ַ����
	{"KLCXB",NULL,0,&xm_KLCXB},//��ѯ�豸����Ͱ汾����
	{"KLCCM",NULL,0,&xm_KLCCM},//��ѯ˫MCU�豸������汾�ź�Э��汾��
	{"KLBL",NULL,0,&xm_KLBL},//������λ��������Ȩת��
	{"KLQDDM",NULL,0,&xm_KLQDDM},//ǿ�ƶ�/д�豸��ַ������
	{"KLQDDM3",NULL,0,&xm_KLQDDM3},//ǿ�ƶ�ȡ�豸��ַ��3
	{"KLBAUND",NULL,0,&xm_KLBAUND},//���ÿյ���ͨ�Ų�����1
	{"KLKZJ",NULL,0,&xm_KLKZJ},//���ư�֮����Ϣ����
	{"KLXYM",NULL,0,&xm_KLXYM},////�豸��Ϣ������
	{"EXITHOST",NULL,0,&xm_EXITHOST},
};

