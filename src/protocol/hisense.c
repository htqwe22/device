/*********************KDA-1131-V01.c***********************
*/
#include	"xmlog.h"
#include	"xm_type.h"
#include    "protocol.h"
#include	"message.h"
#include	"hisense.h"
#include	"cmdanalysis.h"
#include	"air-condition_msg.h"

uchar xm_address1[]={0x1,0x1,'\0'};
uchar xm_address2[]={0xfe,0x1,'\0'};


/* 
֡:
֡ͷ(2) + Ӧ�� + ֡��ʶ1 + ��ʶ2 +  �ֽ���(1/2)+ ��������ݰ�(18~148)+ У���(1/2/4) + ֡β(2)
�����:
Ӧ���ʶ+ ֡��ʶ1 + ֡��ʶ2 + ��ַ��1+ ��ַ��2 +��ַ��3 + ��ַ��4 + ��ַ��5 + ��������ݰ�(10~140)
�����:
Ӧ���ʶ+ ֡��ʶ1 + ����ָ��(2) + ֡��ʶ2 + Ӧ�ò����ݰ�(5~135)
Ӧ�ò�:
��Ϣͷ(5) + ��Ϣ����(0~130)

*/
#if 0
//֡
uchar	XM_KL_Frame_Ack;		   //Usart0���߽���֡Ӧ��
uchar	XM_KL_Frame_Flag_1; 	   //Usart0���߽���֡��ʶ1
uchar	XM_KL_Frame_Size_Count;			   //Usart0���߽���֡�����ֽ�������
uchar	XM_KL_Frame_Checksum_Type;
uchar	XM_KL_Frame_Checksum_Count;		   //Usart0���߽���У��ͽ�������
uchar	XM_KL_Frame_Flag_2; 	   //Usart0���߽���֡��ʶ2
ushort	XM_KL_Frame_Size;			   //Usart0���߽���֡����������ĳ���
uint	XM_KL_Frame_Checksum; 		   //Usart0���߽���У���
//����
uchar	XM_KL_Network_Ack;		   //Usart0���߽�������Ӧ��
uchar	XM_KL_Network_Flag_1;		   //Usart0���߽��������ʶ1
uchar	XM_KL_Network_Address_Struct;		       //�����ַ�ṹ
uchar	XM_KL_Network_Address_Type;		       //�����ַ����
uchar	XM_KL_Network_Address_All;		       //�����ַ����
uchar	XM_KL_Network_Address_Count;		   //Usart0���߽��������ַ����
uchar	pxm->XM_KL_Network_Flag_2;		   //Usart0���߽��������ʶ2
uchar	pxm->XM_KL_Network_Address_Len;		   //Usart0���߽��������ַ�ֽ���
uchar	*pxm->P_XM_KL_Network_Address_1;			   //Usart0���߽���֡��ַ1
uchar	*pxm->P_XM_KL_Network_Address_2;			   //Usart0���߽���֡��ַ2
uchar	*pxm->P_XM_KL_Network_Address_3;			   //Usart0���߽���֡��ַ3
uchar	*pxm->P_XM_KL_Network_Address_4;			   //Usart0���߽���֡��ַ4
uchar	*pxm->P_XM_KL_Network_Address_5;			   //Usart0���߽���֡��ַ5
//�����
uchar	pxm->XM_KL_Transfer_Ack; 	   //Usart0���߽��մ���Ӧ��
uchar	pxm->XM_KL_Transfer_Flag_1;		   //Usart0���߽��մ����ʶ1
uchar	pxm->XM_KL_Transfer_Encryption_Type;		       //Ӧ�ü�������
uchar	pxm->XM_KL_Transfer_Retry_Count;		       //Ӧ���ش�����
uchar	pxm->XM_KL_Transfer_Flag_2;		   //Usart0���߽��մ����ʶ2
uchar	pxm->XM_KL_Transfer_Encryption;		   //Usart0���߽��մ������ָ��
//����������
uchar   *pxm->P_XM_KL_Recv_Frame=NULL;	//USART0��·��Ľ���֡
uchar	*pxm->P_XM_KL_Recv_Frame;		//USART0���������ָ��

//����״̬����
uchar	pxm->XM_KL_Status;		       //֡��������
uchar	pxm->XM_KL_Recv_Count;		   //��ǰ״̬��Ч�ַ���
#define XM_KL_Wait_Head 1 //�ȴ�֡ͷ
#define XM_KL_Find_Head 2 //Ѱ��֡��־
#define XM_KL_Frame_FLAG 3 //����֡����
uchar	pxm->XM_KL_More_Flag;		       //���ڵڶ���ʶ
uchar	*pxm->P_XM_KL_Crc;		//��Ϣͷ
#define XM_KL_Frame_Len 4 //����֡����
#define XM_KL_Network_FLAG 5 //����֡����
#define XM_KL_Network_Address 6 //���������ַ
#define XM_KL_Transfer_FLAG 7 //����Ӧ�ñ�ʶ
#define XM_KL_App_Data 8 //��ȡ��Ϣ����
uchar	*pxm->P_XM_KL_Link_Msg;		//��Ϣͷ
#define XM_KL_Frame_Crc 9 //����У��
#define XM_KL_Frame_End  10 //����֡����


//����������
uchar	*P_XM_KL_Send_Frame;		//USART0���������ָ��

int xm_error=0;
#endif
#define XM_KL_Wait_Head 1 //�ȴ�֡ͷ
#define XM_KL_Find_Head 2 //Ѱ��֡��־
#define XM_KL_Frame_FLAG 3 //����֡����
#define XM_KL_Frame_Len 4 //����֡����
#define XM_KL_Network_FLAG 5 //����֡����
#define XM_KL_Network_Address 6 //���������ַ
#define XM_KL_Transfer_FLAG 7 //����Ӧ�ñ�ʶ
#define XM_KL_App_Data 8 //��ȡ��Ϣ����
#define XM_KL_Frame_Crc 9 //����У��
#define XM_KL_Frame_End  10 //����֡����

//-----------------------------------------------------
void statusInit(XM_PROTOCOL * pxm)
{
	memset(&pxm->xm_status,0,sizeof(XM_PROTOCOL_STATUS));
	pxm->xm_status.XM_KL_Status=XM_KL_Wait_Head;
	pxm->xm_status.P_XM_KL_Recv_Frame=pxm->XM_Frame_Buffer;	
	pxm->xm_crc_type=1;
	if(pxm->xm_addres!=0xff)xm_address1[0]=pxm->xm_addres;
	pxm->xm_addres_1=xm_address1;
	pxm->xm_addres_2=xm_address2;
	
}

int xm_crc(uchar *pbuf,uint len,uchar type){
	int ncrc=0,i,crclen;
	uchar * pcrc_c=pbuf;
	if(!pbuf || !len || type>3){		
		XM_E(" CRC:pbuf %p len %d type %d\r\n",pbuf,len,type);
		return 0;
	}
	#if DEBUG_CRC
	XM_D("CRC:len %d type %d\r\n",len,type);
	#if 1
		printf_buf("crc",(uchar *)pbuf,len);
	#else
	for(i=0;i<len;i++){										
		XM_D("0x%02x ",(uchar)pbuf[i]);
	}
	XM_D("\t\r\n");	
	#endif
	#endif
	switch(type){
		case 0:
		crclen=len;
		for(i=0;i<crclen;i++){
			ncrc+=(uchar)*pcrc_c++;
		}
		ncrc=ncrc&0xff;
		break;
		case 1:
		case 2:
		case 3:
		crclen=len;
		ncrc=0;
		for(i=0;i<crclen;i++){
			ncrc+=(uchar)*pcrc_c++;
#if DEBUG_CRC
			XM_D("CRC:ret 0x%08x \r\n",ncrc);
#endif
		}
		ncrc=ncrc&0xffff;
		break;
	}
#if DEBUG_CRC
	XM_D("CRC:ret 0x%08x \r\n",ncrc);
#endif
	return ncrc;
}

void XM_PRINTF_msg(MessageHead *pMsgHead){

	if(pMsgHead){
		XM_D("MessageType:%d\r\n",pMsgHead->MessageType);
		XM_D("MessageSubType:%d\r\n",pMsgHead->MessageSubType);
		XM_D("Result:%d\r\n",pMsgHead->Result);
	}
	
	
}

void Proc_Encryption(uchar *pdbuf,uchar *pbuf,uchar len,uchar enc){

}

uchar Proc_msg(XM_PROTOCOL *pxm,MessageHead *pMsgHead,uchar len){
	//uchar ret;
	//uchar *pbuf=(uchar *)pMsgHead;
	//XM_Command * pCommand;
	uchar MessageHead_len=sizeof(MessageHead);
	#if DEBUG_RECV
	XM_D("Proc_msg: pxm %p pMsgHead %p len %d\r\n",pxm,pMsgHead,len);
	#endif
	if (pMsgHead->MessageType < 211 )
		{
		XM_E("msg: unframe packet! len-2!\r\n");
		MessageHead_len=sizeof(MessageHead)-2;
		}
	else
		{
		pxm->xm_frame=pMsgHead->frame;
		pxm->xm_sub_frame=pMsgHead->sub_frame;
		}
	if(len<MessageHead_len){
		XM_E("msg: buffer too small\r\n");
		return XM_ERROR_BUF_SMALL;
	}
	if(pMsgHead->MessageType!=pxm->sendcmd || pMsgHead->MessageSubType!=pxm->sendsub){
		XM_E("msg: MessageType %d sendcmd %d MessageSubType %d sendsub %d\r\n",pMsgHead->MessageType,pxm->sendcmd,pMsgHead->MessageSubType,pxm->sendsub);
		return XM_ERROR_WAIT_MOER;
	}
	//pCommand=getcommand(pxm->xm_addres_2[0],pbuf+sizeof(MessageHead),len-sizeof(MessageHead));
	return build_at_ret(pxm,NULL,NULL,Proc_Result(pxm,pMsgHead,len));
	//return ret;
}


uchar Proc_recv(XM_PROTOCOL *pxm,MessageHead *pMsg,uchar len){
#if DEBUG_RS	
	XM_D("config recv:%d\r\n",len);
#endif	
	memcpy(pxm->XM_Status_Buffer,pMsg,len);
	return XM_SUCCESS;
}

uchar Parse_Read (XM_PROTOCOL *pxm,uchar *cstr,uchar (*msg)(XM_PROTOCOL *pxm,MessageHead * pMsgHead,uchar len)){
	uchar nRet=XM_ERROR_WAIT_MOER;
	uchar cValue=(uchar)*cstr;	
	if((pxm->xm_status.P_XM_KL_Recv_Frame-pxm->XM_Frame_Buffer) >= XM_MAX_BUF){
		XM_E("max str len\r\n");
		pxm->xm_status.xm_error=XM_ERROR_FRAME_MAX;
		nRet=XM_ERROR_FRAME_MAX;
		goto err_exit;
	}
	
#if DEBUG_RECV	
	XM_I("parse:str=0x%02x\r\n",(uchar)cValue);
#endif
	if(pxm->xm_status.XM_KL_Status != XM_KL_Wait_Head && cValue == Extension_Byte && pxm->xm_status.IsHaveHead == 0){
			#if DEBUG_RECV
			XM_I("parse:Is Extension_Byte\r\n");
			#endif
			pxm->xm_status.IsHaveHead = 1;			
			pxm->xm_status.oldValue='\0';
			return XM_ERROR_WAIT_MOER;
	}	
	#if DEBUG_RECV
	XM_I("parse:IsHaveHead %d\r\n",pxm->xm_status.IsHaveHead);
	#endif
	if( pxm->xm_status.IsHaveHead == 1 && ((cValue ==BAG_HEAD2 )||(cValue ==BAG_END2))){			
		pxm->xm_status.IsHaveHead = 2;
		uchar cTmp=Extension_Byte;
		Parse_Read(pxm,&cTmp,msg);
		pxm->xm_status.IsHaveHead = 0;
		
	}else if( pxm->xm_status.IsHaveHead == 1 && cValue ==Extension_Byte){
		pxm->xm_status.IsHaveHead = 0;
	}
	#if DEBUG_RECV
	XM_I("parse:pxm->XM_KL_Status=%d\r\n",pxm->xm_status.XM_KL_Status);
	#endif
	switch(pxm->xm_status.XM_KL_Status){
		case XM_KL_Wait_Head:
			if(cValue == BAG_HEAD1){
				pxm->xm_status.XM_KL_Status=XM_KL_Find_Head;
				pxm->xm_status.xm_error=XM_ERROR_FRAME_UNKOWN;
			}			
			#if DEBUG_RECV
			XM_I("parse:pxm->XM_KL_Status=%d\r\n",pxm->xm_status.XM_KL_Status);
			#endif
			break;
		case XM_KL_Find_Head:
			if(cValue == BAG_HEAD2){				
				pxm->xm_status.XM_KL_Status=XM_KL_Frame_FLAG;
				pxm->xm_status.xm_error=XM_ERROR_FRAME_UNKOWN;
				pxm->xm_status.XM_KL_Recv_Count=0;
			}else if(cValue != BAG_HEAD1){
				XM_E("not find BAG_HEAD2\r\n");
				pxm->xm_status.xm_error=XM_ERROR_FRAME_HEAD;
				goto err_exit;
			}			
			#if DEBUG_RECV
			XM_I("parse:pxm->XM_KL_Status=%d\r\n",pxm->xm_status.XM_KL_Status);
			#endif
			break;
		case XM_KL_Frame_FLAG:			
			#if DEBUG_RECV
			XM_I("parse:Frame count=%d\r\n",pxm->xm_status.XM_KL_Recv_Count);
			#endif
			switch(pxm->xm_status.XM_KL_Recv_Count){
				case 1: //���յ�����Ӧ��λһ��Ϊ0
				if(XM_ACK_CEHCK(cValue)){
					if (cValue==0)
						pxm->xm_status.xm_error=XM_ERROR_FRAME_UNKOWN;
					else
					pxm->xm_status.xm_error=cValue;
					XM_E("frame ack %d\r\n",pxm->xm_status.xm_error);
					goto err_exit;
				}
				pxm->xm_status.XM_KL_Frame_Ack=cValue;
				pxm->xm_status.P_XM_KL_Crc=pxm->xm_status.P_XM_KL_Recv_Frame;
				pxm->xm_status.CrcLen++;
				break;
				case 2: //�����ʶ1				
				if(cValue & XM_FLAG_TWO){//��Ҫ����ڶ���ʶ						
					pxm->xm_status.XM_KL_More_Flag=1;
				}
				pxm->xm_status.LenCount=pxm->xm_status.XM_KL_Frame_Size_Count=((cValue&0x80)>>1)+1;
				pxm->xm_status.XM_KL_Frame_Checksum_Type=((cValue&(0x3<<6))>>6);
				if(pxm->xm_status.XM_KL_Frame_Checksum_Type==0)
					pxm->xm_status.CrcCount=pxm->xm_status.XM_KL_Frame_Checksum_Count=1;
				if(pxm->xm_status.XM_KL_Frame_Checksum_Type==1)
					pxm->xm_status.CrcCount=pxm->xm_status.XM_KL_Frame_Checksum_Count=2;
				if(pxm->xm_status.XM_KL_Frame_Checksum_Type==2)
					pxm->xm_status.CrcCount=pxm->xm_status.XM_KL_Frame_Checksum_Count=2;
				if(pxm->xm_status.XM_KL_Frame_Checksum_Type==3)
					pxm->xm_status.CrcCount=pxm->xm_status.XM_KL_Frame_Checksum_Count=4;
				pxm->xm_status.XM_KL_Frame_Flag_1=cValue;
				pxm->xm_status.CrcLen++;
				if(!(pxm->xm_status.XM_KL_Frame_Flag_1 & 0x1)){
					pxm->xm_status.XM_KL_Status=XM_KL_Frame_Len;
					pxm->xm_status.xm_error=XM_ERROR_NETWORK_UNKOWN;
					pxm->xm_status.XM_KL_Recv_Count=0;
				}
				#if DEBUG_RECV
				XM_I("parse:Frame Size_Count=%d, Checksum_Type=%d, Checksum_Count=%d, Flag_1=%d, More_Flag=%d\r\n",pxm->xm_status.XM_KL_Frame_Size_Count,pxm->xm_status.XM_KL_Frame_Checksum_Type,pxm->xm_status.XM_KL_Frame_Checksum_Count,pxm->xm_status.XM_KL_Frame_Flag_1,pxm->xm_status.XM_KL_More_Flag);
				#endif
				break;
				case 3: //�����ʶ2
				if(pxm->xm_status.XM_KL_More_Flag){
					pxm->xm_status.XM_KL_Frame_Flag_2=cValue;
					pxm->xm_status.XM_KL_More_Flag=0;
					pxm->xm_status.CrcLen++;
					pxm->xm_status.XM_KL_Status=XM_KL_Frame_Len;
					pxm->xm_status.xm_error=XM_ERROR_NETWORK_UNKOWN;
					pxm->xm_status.XM_KL_Recv_Count=0;
				}else{
					pxm->xm_status.xm_error=XM_ERROR_FRAME_FLAG;
					XM_E("frame havn't Flag_2\r\n");
					goto err_exit;
				}				
				break;
				default:
					pxm->xm_status.xm_error=XM_ERROR_FRAME_UNKOWN;
					XM_E("unknow frame step\r\n");
					goto err_exit;
				break;
					
			}				
		break;
		case XM_KL_Frame_Len:
			if(pxm->xm_status.LenCount){
				pxm->xm_status.XM_KL_Frame_Size+=cValue<<((pxm->xm_status.LenCount-1)*8);
				pxm->xm_status.LenCount--;
				pxm->xm_status.CrcLen++;
			}
			if(pxm->xm_status.LenCount==0){
				pxm->xm_status.PacketLen=pxm->xm_status.XM_KL_Frame_Size;
				pxm->xm_status.XM_KL_Status=XM_KL_Network_FLAG;
				pxm->xm_status.xm_error=XM_ERROR_NETWORK_UNKOWN;
				pxm->xm_status.XM_KL_Recv_Count=0;
			}			
			if(pxm->xm_status.PacketLen<=0){
				XM_E("Frame Size Fail=%d\r\n",(uint)pxm->xm_status.PacketLen);
				pxm->xm_status.xm_error=XM_ERROR_FRAME_SIZE;
				goto err_exit;
			}
			#if DEBUG_RECV
			XM_I("parse:Frame Size=%d\r\n",(uint)pxm->xm_status.XM_KL_Frame_Size);
			#endif
		break;
		case XM_KL_Network_FLAG:
			switch(pxm->xm_status.XM_KL_Recv_Count){
				case 1: //���յ�����Ӧ��λһ��Ϊ0
				if(XM_ACK_CEHCK(cValue)){
					if (cValue==0)
						pxm->xm_status.xm_error=XM_ERROR_NETWORK_UNKOWN;
					else
						pxm->xm_status.xm_error=cValue;
					XM_E("network ack %d\r\n",pxm->xm_status.xm_error);
					goto err_exit;
				}
				pxm->xm_status.PacketLen--;
				pxm->xm_status.XM_KL_Network_Ack=cValue;
				break;
				case 2: //�����ʶ1				
				if(cValue & XM_FLAG_TWO){//��Ҫ����ڶ���ʶ						
					pxm->xm_status.XM_KL_More_Flag=1;
				}
				pxm->xm_status.XM_KL_Network_Address_Count=(cValue & 0x18)>>3;
				pxm->xm_status.XM_KL_Network_Address_All=(cValue & 0x20)>>5;
				pxm->xm_status.XM_KL_Network_Address_Type=(cValue & 0x40)>>6;								
				pxm->xm_status.XM_KL_Network_Address_Struct=(cValue & 0x80)>>7;
				pxm->xm_status.AddresCount=pxm->xm_status.PacketAddressLen=(pxm->xm_status.XM_KL_Network_Address_Count+1)*2;				
				if(pxm->xm_status.XM_KL_Network_Address_All)
					pxm->xm_status.PacketAddressLen*=5;
				else
					pxm->xm_status.PacketAddressLen*=2;
				pxm->xm_status.PacketLen--;
				pxm->xm_status.XM_KL_Network_Flag_1=cValue;
				if(!(pxm->xm_status.XM_KL_Network_Flag_1 & 0x1)){
					pxm->xm_status.XM_KL_Status=XM_KL_Network_Address;
					pxm->xm_status.xm_error=XM_ERROR_NETWORK_UNKOWN;
					pxm->xm_status.XM_KL_Recv_Count=0;
				}
				#if DEBUG_RECV
				XM_I("parse:PacketAddressLen %d,Address_Count %d\r\n",pxm->xm_status.PacketAddressLen,pxm->xm_status.XM_KL_Network_Address_Count);
				#endif
				break;
				case 3: //�����ʶ2
				if(pxm->xm_status.XM_KL_More_Flag){					
					pxm->xm_status.XM_KL_Network_Flag_2=cValue;
					pxm->xm_status.XM_KL_More_Flag=0;
					pxm->xm_status.PacketLen--;
					pxm->xm_status.XM_KL_Status=XM_KL_Network_Address;
					pxm->xm_status.xm_error=XM_ERROR_NETWORK_UNKOWN;
					pxm->xm_status.XM_KL_Recv_Count=0;
				}else{
					pxm->xm_status.xm_error=XM_ERROR_NETWORK_FLAG;
					XM_E("network havn't Flag_2\r\n");
					goto err_exit;
				}
				
				break;
				default :
					pxm->xm_status.xm_error=XM_ERROR_NETWORK_UNKOWN;
					XM_E("unknow network step\r\n");
					goto err_exit;
				
			}		
		break;
		case XM_KL_Network_Address:
			#if DEBUG_RECV
			XM_I("parse:Recv_Count %d\r\n",pxm->xm_status.XM_KL_Recv_Count);
			#endif
			if(pxm->xm_status.PacketAddressLen){
				if(pxm->xm_status.XM_KL_Recv_Count/pxm->xm_status.AddresCount == 0 && pxm->xm_status.XM_KL_Recv_Count % pxm->xm_status.AddresCount ==1)
					pxm->xm_status.P_XM_KL_Network_Address_1=pxm->xm_status.P_XM_KL_Recv_Frame;
				if(pxm->xm_status.XM_KL_Recv_Count/pxm->xm_status.AddresCount == 1 && pxm->xm_status.XM_KL_Recv_Count % pxm->xm_status.AddresCount ==1)
					pxm->xm_status.P_XM_KL_Network_Address_2=pxm->xm_status.P_XM_KL_Recv_Frame;
				if(pxm->xm_status.XM_KL_Recv_Count/pxm->xm_status.AddresCount == 2 && pxm->xm_status.XM_KL_Recv_Count % pxm->xm_status.AddresCount ==1)
					pxm->xm_status.P_XM_KL_Network_Address_3=pxm->xm_status.P_XM_KL_Recv_Frame;
				if(pxm->xm_status.XM_KL_Recv_Count/pxm->xm_status.AddresCount == 3 && pxm->xm_status.XM_KL_Recv_Count % pxm->xm_status.AddresCount ==1)
					pxm->xm_status.P_XM_KL_Network_Address_4=pxm->xm_status.P_XM_KL_Recv_Frame;
				if(pxm->xm_status.XM_KL_Recv_Count/pxm->xm_status.AddresCount == 4 && pxm->xm_status.XM_KL_Recv_Count % pxm->xm_status.AddresCount ==1)
					pxm->xm_status.P_XM_KL_Network_Address_5=pxm->xm_status.P_XM_KL_Recv_Frame;
				pxm->xm_status.PacketAddressLen--;
				pxm->xm_status.PacketLen--;
			}
			
			if(pxm->xm_status.PacketAddressLen ==0 ){
				pxm->xm_status.XM_KL_Status=XM_KL_Transfer_FLAG;
				pxm->xm_status.xm_error=XM_ERROR_TRANSFER_UNKOWN;
				pxm->xm_status.XM_KL_Recv_Count=0;
			}		
			#if DEBUG_RECV
			XM_I("parse:Frame Size=%d\r\n",(uint)pxm->xm_status.XM_KL_Frame_Size);
			#endif
		break;
		
		case XM_KL_Transfer_FLAG:
			switch(pxm->xm_status.XM_KL_Recv_Count){
				case 1: //���յ�����Ӧ��λһ��Ϊ0
					if(XM_ACK_CEHCK(cValue)){
						if (cValue==0)
							pxm->xm_status.xm_error=XM_ERROR_TRANSFER_UNKOWN;
						else
							pxm->xm_status.xm_error=cValue;
						XM_E("transfer ack %d\r\n",pxm->xm_status.xm_error);
						goto err_exit;
					}
					pxm->xm_status.PacketLen--;
					pxm->xm_status.XM_KL_Transfer_Ack=cValue;
					break;
				case 2: //�����ʶ1				
					if(cValue & XM_FLAG_TWO){//��Ҫ����ڶ���ʶ						
						pxm->xm_status.XM_KL_More_Flag=1;
					}
					pxm->xm_status.XM_KL_Transfer_Encryption_Type=(cValue & 0x3<<6)>>6;
					pxm->xm_status.XM_KL_Transfer_Retry_Count=(cValue & 0xf<<1)>>1;
					pxm->xm_status.PacketLen--;
					pxm->xm_status.XM_KL_Transfer_Flag_1=cValue;
					if(!(pxm->xm_status.XM_KL_Transfer_Flag_1 & 0x1)){
						pxm->xm_status.MsgLen=pxm->xm_status.PacketLen;
						if(pxm->xm_status.MsgLen){
							pxm->xm_status.XM_KL_Status=XM_KL_App_Data;
							pxm->xm_status.XM_KL_Recv_Count=0;
						}else{
							pxm->xm_status.P_XM_KL_Link_Msg=NULL;
							pxm->xm_status.XM_KL_Status=XM_KL_Frame_Crc;
							pxm->xm_status.XM_KL_Recv_Count=0;
						}
					}
					break;
				case 3: //�����ʶ2
					if(pxm->xm_status.XM_KL_More_Flag){
						pxm->xm_status.XM_KL_More_Flag=0;						
						pxm->xm_status.XM_KL_Transfer_Flag_2=cValue;
						pxm->xm_status.PacketLen--;
						pxm->xm_status.MsgLen=pxm->xm_status.PacketLen;
						if(pxm->xm_status.MsgLen){
							pxm->xm_status.XM_KL_Status=XM_KL_App_Data;
							pxm->xm_status.XM_KL_Recv_Count=0;
						}else{
							pxm->xm_status.P_XM_KL_Link_Msg=NULL;
							pxm->xm_status.XM_KL_Status=XM_KL_Frame_Crc;
							pxm->xm_status.XM_KL_Recv_Count=0;
						}
					}else{
						pxm->xm_status.xm_error=XM_ERROR_TRANSFER_FLAG;
						XM_E("transfer havn't Flag_2\r\n");
						goto err_exit;
					}
					
					break;
				default :
					pxm->xm_status.xm_error=XM_ERROR_TRANSFER_UNKOWN;
					XM_E("unknow transfer step\r\n");
					goto err_exit;
				
			}	
		break;
		case XM_KL_App_Data:
			if(pxm->xm_status.XM_KL_Recv_Count==1)
				pxm->xm_status.P_XM_KL_Link_Msg=pxm->xm_status.P_XM_KL_Recv_Frame;
			if(pxm->xm_status.PacketLen)
				pxm->xm_status.PacketLen--;
			
			#if DEBUG_RECV
			XM_I("parse:PacketLen %d\r\n",pxm->xm_status.PacketLen);
			#endif
			if(pxm->xm_status.PacketLen==0){
				pxm->xm_status.XM_KL_Status=XM_KL_Frame_Crc;
				pxm->xm_status.xm_error=XM_ERROR_FRAME_CRC;
				pxm->xm_status.XM_KL_Recv_Count=0;
			}
		break;
		case XM_KL_Frame_Crc:			
#if DEBUG_RECV
			XM_I("parse:Frame_Crc %d\r\n",pxm->xm_status.CrcCount);
#endif
			if(pxm->xm_status.CrcCount){
				pxm->xm_status.XM_KL_Frame_Checksum+=cValue<<((pxm->xm_status.CrcCount-1)*8);
				pxm->xm_status.CrcCount--;
			}
#if DEBUG_RECV
			XM_I("parse:Frame_Crc CrcCount %d\r\n",pxm->xm_status.CrcCount);
#endif
#if DEBUG_RECV
			XM_I("parse:Frame_Crc sum 0x%08x\r\n",pxm->xm_status.XM_KL_Frame_Checksum);
#endif
			if(pxm->xm_status.CrcCount==0){
				uint crcret=0;
				#if DEBUG_RECV
				XM_I("parse:Crc %p ,Frame_Size %d Checksum_Type %d Frame_Checksum %d\r\n",pxm->xm_status.P_XM_KL_Crc,pxm->xm_status.XM_KL_Frame_Size,pxm->xm_status.XM_KL_Frame_Checksum_Type,pxm->xm_status.XM_KL_Frame_Checksum);
				#endif
				pxm->xm_status.CrcLen+=pxm->xm_status.XM_KL_Frame_Size;
				crcret=xm_crc(pxm->xm_status.P_XM_KL_Crc,pxm->xm_status.CrcLen,pxm->xm_status.XM_KL_Frame_Checksum_Type);
				if(pxm->xm_status.XM_KL_Frame_Checksum==crcret){
					pxm->xm_status.XM_KL_Status=XM_KL_Frame_End;
					pxm->xm_status.xm_error=XM_ERROR_FRAME_END2;
					pxm->xm_status.XM_KL_Recv_Count=0;
				}else{
					pxm->xm_status.xm_error=XM_ERROR_FRAME_CRC;
					XM_E("crc fail,val=%u ret=%u\r\n",pxm->xm_status.XM_KL_Frame_Checksum,crcret);
					goto err_exit;
				}
			}
		break;
		
		case XM_KL_Frame_End:
			switch(pxm->xm_status.XM_KL_Recv_Count){
				case 1: //���յ�����Ӧ��λһ��Ϊ0
				if(cValue != BAG_END1){
					pxm->xm_status.xm_error=XM_ERROR_FRAME_END;
					XM_E("not fined end flag\r\n");
					goto err_exit;
				}
				break;
				default: //�����ʶ1				
				if(cValue == BAG_END2){
					//pxm->XM_KL_Status=XM_KL_App_Encryption;
					#if DEBUG_RECV
					XM_I("parse:parse Encryption\r\n");
					#endif
					Proc_Encryption(NULL,pxm->xm_status.P_XM_KL_Link_Msg,pxm->xm_status.MsgLen,0);
					#if DEBUG_RECV
					XM_I("parse:parse msg\r\n");
					#endif
					if(msg){
						nRet=msg(pxm,(MessageHead *)pxm->xm_status.P_XM_KL_Link_Msg,pxm->xm_status.MsgLen);
					}else{
						nRet=0;
					}
					#if DEBUG_RECV
					XM_I("parse:parse ret nRet=%d\r\n",nRet);
					#endif
					pxm->xm_status.XM_KL_Recv_Count=0;
					#if DEBUG_RECV
					XM_I("parse:parse finish\r\n");
					#endif
					pxm->xm_status.XM_KL_Status=XM_KL_Wait_Head;
					pxm->xm_status.xm_error=0x0;
					if(pxm->xm_status.P_XM_KL_Network_Address_1){
						if(pxm->xm_status.P_XM_KL_Network_Address_1[0]==0||pxm->xm_status.P_XM_KL_Network_Address_1[1]==0){
							nRet=pxm->xm_status.xm_error=XM_ERROR_WIFI_ADDRESS;
							XM_E("wifi address error %02x %02x\r\n",pxm->xm_status.P_XM_KL_Network_Address_1[0],pxm->xm_status.P_XM_KL_Network_Address_1[1]);
						}
					}
					if(pxm->xm_status.P_XM_KL_Network_Address_2){
						if(pxm->xm_status.P_XM_KL_Network_Address_2[0]==0||pxm->xm_status.P_XM_KL_Network_Address_2[1]==0){
							nRet=pxm->xm_status.xm_error=XM_ERROR_DEV_ADDRESS;
							XM_E("dev address error %02x %02x\r\n",pxm->xm_status.P_XM_KL_Network_Address_2[0],pxm->xm_status.P_XM_KL_Network_Address_2[1]);
						}
					}					
					goto finish_exit;
				}else{
					pxm->xm_status.xm_error=XM_ERROR_FRAME_END2;
					XM_E("not fined end flag2\r\n");
					goto err_exit;
				}
			}
		break;
#if 0
		case XM_KL_App_Encryption:
			Proc_Encryption(pxm->xm_status.P_XM_KL_Link_Msg,MsgLen,0);
			pxm->xm_status.XM_KL_Status=XM_KL_App_Msg;
			pxm->xm_status.XM_KL_Recv_Count=0;
		break;
		case XM_KL_App_Msg:
			Proc_msg(pxm->xm_status.P_XM_KL_Link_Msg,MsgLen);
			XM_I("parse:finish\r\n");
			goto finish_exit;
		break;
#endif
		default:
			pxm->xm_status.xm_error=XM_ERROR_FRAME_MORE;
			XM_E("unknow step\r\n");
			goto err_exit;
	}
	pxm->xm_status.XM_KL_Recv_Count++;
	if(pxm->xm_status.oldValue == BAG_END1 && cValue == BAG_END2){//���ۺ�ʱ�յ�֡����������Ϊ�ѽ���
		goto err_exit;
	}
	if(pxm->xm_status.P_XM_KL_Crc == NULL && pxm->xm_status.CrcCount){
		pxm->xm_status.P_XM_KL_Crc=pxm->xm_status.P_XM_KL_Recv_Frame;
	}
#if DEBUG_RECV	
	XM_D("pasre:oldValue\r\n");
#endif
	pxm->xm_status.oldValue=*cstr;
#if DEBUG_RECV	
	XM_D("pasre:P_XM_KL_Recv_Frame %p\r\n",pxm->xm_status.P_XM_KL_Recv_Frame);
#endif
	*(pxm->xm_status.P_XM_KL_Recv_Frame++)=*cstr;
#if DEBUG_RECV	
	XM_D("pasre:exit %d\r\n",pxm->xm_status.xm_error);
#endif
	return nRet;
err_exit:	
	nRet=pxm->xm_status.xm_error;
finish_exit:
	return nRet;
}

void move_data(uchar * buf,int len,int offset){
	uchar * pEnd;
	pEnd=buf+len;
	while((pEnd-offset)>=buf){
		*pEnd=*(pEnd-offset);
		pEnd--;
	}
}

uchar Parse_Send (uchar *pData,uchar *pbuf,uchar MsgLen,uchar * Address1,uchar * Address2,uchar * Address3,uchar * Address4,uchar * Address5,uchar Address_Count,uchar Address_All,uchar Address_Type,uchar Address_Struct,uchar EncryptionType,uchar CrcType,uchar nret,uchar Transfer_flag2,uchar Network_flag2,uchar Frame_flag2,uchar Encryption,uchar Retry){

	uint packetlen=0,i;
	uint addres_num=0,transfer_head_num=0,network_head_num=0,frame_head_num=0;
	uchar *P_XM_KL_Send_Frame;
	uchar crc_c;
	ushort crc_s;
	uint crc_i;
	//����Ӧ�ð�
	P_XM_KL_Send_Frame=pData;
	transfer_head_num=2;
	memcpy(P_XM_KL_Send_Frame+transfer_head_num,pbuf,MsgLen);//������Ϣ����
	transfer_head_num+=MsgLen;
	P_XM_KL_Send_Frame[0]=(uchar)nret;
	P_XM_KL_Send_Frame[1]=(EncryptionType&0x3)<<6;
	P_XM_KL_Send_Frame[1]|=(Retry&0xf)<<1;
	if(EncryptionType){
		move_data(P_XM_KL_Send_Frame+2,++transfer_head_num,1);
		P_XM_KL_Send_Frame[2]=Encryption;
	}
	if(Transfer_flag2){
		move_data(P_XM_KL_Send_Frame+2,++transfer_head_num,1);
		P_XM_KL_Send_Frame[2]=Transfer_flag2;
		P_XM_KL_Send_Frame[1]|=0x1;
	}	
	packetlen+=transfer_head_num;
	#if DEBUG_SEND
	printf_buf("Transfer",pData,packetlen);
	#endif
	
	//���������	
	network_head_num =2;	
	move_data(P_XM_KL_Send_Frame,packetlen+network_head_num,network_head_num);
	P_XM_KL_Send_Frame[0]=nret;
	Address_Count %= 9;
	if(Address_Count<2){
		Address_Count=2;
	}
	P_XM_KL_Send_Frame[1]= (Address_Struct & 0x1)<<7 | (Address_Type & 0x1)<<6 | (Address_All & 0x1)<<5 | ((Address_Count/2-1) & 0x3)<<3;
	if(Address_All)
		addres_num=5;
	else
		addres_num=2;	
	move_data(P_XM_KL_Send_Frame+network_head_num,packetlen+Address_Count,Address_Count);
	memcpy(P_XM_KL_Send_Frame+network_head_num,Address1,Address_Count);
	network_head_num+=Address_Count;
	
	move_data(P_XM_KL_Send_Frame+network_head_num,packetlen+Address_Count,Address_Count);
	memcpy(P_XM_KL_Send_Frame+network_head_num,Address2,Address_Count);
	network_head_num+=Address_Count;
	if(Address_All){		
		move_data(P_XM_KL_Send_Frame+network_head_num+Address_Count*2,packetlen+Address_Count,Address_Count);
		memcpy(P_XM_KL_Send_Frame+network_head_num,Address3,Address_Count);
		network_head_num+=Address_Count;
		
		move_data(P_XM_KL_Send_Frame+network_head_num+Address_Count*3,packetlen+Address_Count,Address_Count);
		memcpy(P_XM_KL_Send_Frame+network_head_num,Address4,Address_Count);
		network_head_num+=Address_Count;
		
		move_data(P_XM_KL_Send_Frame+network_head_num+Address_Count*4,packetlen+Address_Count,Address_Count);
		memcpy(P_XM_KL_Send_Frame+network_head_num,Address5,Address_Count);
		network_head_num+=Address_Count;
	}
	
	if(Network_flag2){		
		move_data(P_XM_KL_Send_Frame+2,packetlen+(++network_head_num)-2,1);
		P_XM_KL_Send_Frame[2]=Transfer_flag2;
		P_XM_KL_Send_Frame[1]|=0x1;
	}
	packetlen+=network_head_num;
	#if DEBUG_SEND
	printf_buf("Network",pData,packetlen);
	#endif
	//����֡��	
	frame_head_num=3;
	#if DEBUG_SEND
	printf_buf("flb",pData,packetlen);
	#endif
	move_data(P_XM_KL_Send_Frame,packetlen+frame_head_num,frame_head_num);
	#if DEBUG_SEND
	printf_buf("fla",pData,packetlen+4);
	#endif
	P_XM_KL_Send_Frame[0]=nret;
	CrcType=CrcType&0x3;
	P_XM_KL_Send_Frame[1]=CrcType<<6;
	P_XM_KL_Send_Frame[2]=packetlen & 0xff;
	if(packetlen>255){
		move_data(P_XM_KL_Send_Frame+2,packetlen+(++frame_head_num),1);
		P_XM_KL_Send_Frame[2]=(packetlen & 0xff00)>>8;
		P_XM_KL_Send_Frame[1]|=1<<5;
	}
	
	if(Frame_flag2){
		move_data(P_XM_KL_Send_Frame+2,packetlen+(++frame_head_num),1);
		P_XM_KL_Send_Frame[2]=Frame_flag2;
		P_XM_KL_Send_Frame[1]|=0x1;
	}
	packetlen+=frame_head_num;
	#if DEBUG_SEND
	printf_buf("crc",pData,packetlen);
	#endif
	//XM_PRINTF("crc b len %d %d\t\r\n",packetlen,CrcType);
	switch(CrcType){
		case 0:
		crc_c=xm_crc(P_XM_KL_Send_Frame,packetlen,CrcType);
		P_XM_KL_Send_Frame[packetlen]=crc_c;
		packetlen++;
		break;
		case 1:
		crc_s=xm_crc(P_XM_KL_Send_Frame,packetlen,CrcType);		
		P_XM_KL_Send_Frame[packetlen]=(crc_s & 0xff00)>>8;
		P_XM_KL_Send_Frame[packetlen+1]=(crc_s & 0xff);
		packetlen+=2;
		break;
		case 2:
		crc_s=xm_crc(P_XM_KL_Send_Frame,packetlen,CrcType);
		P_XM_KL_Send_Frame[packetlen]=(crc_s & 0xff00)>>8;
		P_XM_KL_Send_Frame[packetlen+1]=(crc_s & 0xff);
		packetlen+=2;
		break;
		case 3:
		crc_i=xm_crc(P_XM_KL_Send_Frame,packetlen,CrcType);
		P_XM_KL_Send_Frame[packetlen]=(crc_i & 0xff000000)>>24;
		P_XM_KL_Send_Frame[packetlen+1]=(crc_i & 0xff0000)>>16;
		P_XM_KL_Send_Frame[packetlen+2]=(crc_i & 0xff00)>>8;
		P_XM_KL_Send_Frame[packetlen+3]=(crc_i & 0xff);
		packetlen+=4;
		break;
	}
	//XM_PRINTF("crc a len %d %d\t\r\n",packetlen,CrcType);
	#if DEBUG_SEND
	printf_buf("Frame",pData,packetlen);
	#endif
	//����ת����
	
	i=packetlen;
	P_XM_KL_Send_Frame=pData;
	while(i){
		if(*P_XM_KL_Send_Frame==BAG_HEAD1 || *P_XM_KL_Send_Frame==BAG_END1){
			//��������
			move_data(P_XM_KL_Send_Frame,packetlen-i+1,1);			
			*P_XM_KL_Send_Frame=Extension_Byte;
			P_XM_KL_Send_Frame++;
			packetlen++;
		}
		P_XM_KL_Send_Frame++;
		i--;
	}
	P_XM_KL_Send_Frame=pData;
	#if DEBUG_SEND
	printf_buf("F4",pData,packetlen);
	#endif
	//��֡ͷ
	
	move_data(P_XM_KL_Send_Frame,packetlen+2,2);
	P_XM_KL_Send_Frame[0]=BAG_HEAD1;
	P_XM_KL_Send_Frame[1]=BAG_HEAD2;
	packetlen+=2;
	#if DEBUG_SEND
	printf_buf("Head",pData,packetlen);
	#endif
	//��֡β	
	
	P_XM_KL_Send_Frame[packetlen]=BAG_END1;
	P_XM_KL_Send_Frame[packetlen+1]=BAG_END2;	
	packetlen+=2;
#if DEBUG_RS
	printf_buf("Packet",pData,packetlen);
#endif
	return packetlen;
}

//------------------------end------------------------------
