
/*
 *#define XM_SEND_SETTING 1
#define XM_SEND_QUERY 0
#define XM_SEND_SUPPORT 2
#define XM_SEND_CONFIG 3
 *
 **/
 
#include "vanword.h"

/*����16����ASCII����Ϣ�����p0*/
extern void vanw_parse_head(p0_t *p0,char *hexstr);

/*��� build info ����Ϣ��������ַ�������retbuf��*/
extern int vanw_build_allstr(char *retbuf,build_info_t *build_info);


struct ctl_id gIdArr[]={
	{0x03,0x01},
	{0x03,0x02},
	{0x03,0x05},
	{0x03,0x06},
	{0x03,0x07}
};




extern VANW_AT_T ret_commProduce[];
extern VANW_AT_T ret_clectWaterHeator[];
extern VANW_AT_T ret_burnWaterHeator[];
extern VANW_AT_T ret_warmStoveHeator[];


extern VAN_CMD_T cmd_commProduce[];
extern VAN_CMD_T cmd_clectWaterHeator[];
extern VAN_CMD_T cmd_burnWaterHeator[];
extern VAN_CMD_T cmd_warmStoveHeator[];


/////////////////////    RETURN STATUS LIST      ////////////////////
VANW_PRO_T ret_product_list[]={
	// num ,list,product,name
	{1,ret_commProduce,COMM_PRODUCT,STR(COMM_PRODUCT)},
	{2,ret_clectWaterHeator,ELECT_HEATOR,NULL},
	{2,ret_burnWaterHeator,BURN_HEATOR,NULL},
	{2,ret_warmStoveHeator,WARM_STOVE,NULL}
};
////////////////////////////////////////////////////////////////



//////////////////////////      CMD LIST        //////////////////////////////
VANW_PRO_CMD_T cmd_product_list[]={
	{1,cmd_commProduce,COMM_PRODUCT,STR(COMM_PRODUCT)},
	{7,cmd_clectWaterHeator,ELECT_HEATOR,NULL},
	{9,cmd_burnWaterHeator,BURN_HEATOR,NULL},
	{10,cmd_warmStoveHeator,WARM_STOVE,NULL}
};
///////////////////////////////////////////////////////////////////////



static u8 xlf_get_value(char *value,XM_Offset *item){
	int i=0;
	if(!value)
		return 0;
	if(item->textlen!=0 || item ){
		xlf_debug("get_value:%d %s\r\n",item->textlen,value);
		for(i=0;i<item->textlen;i++){
				// �Ƚϲ�����˵��AT����Ҫ��text.str�е�һ��
			if(!memcmp(value,item->text[i].str,strlen(item->text[i].str))){
				xlf_debug("get_value:Value %s %d\r\n",item->text[i].str,item->text[i].value);
				//pnode->xm_cmd->parameter=parameter;
				return item->text[i].value;
			}
		}
	}	
	return (u8)atoi(value);
}


static u8 xlf_vanw_parse_para(AT_CMD_T *pnode,char *copyStart,char *value,XM_Offset *pOffset){
	u8 nValue,retlen=0;
	u8 nByteOffset=0,nBitOffset,nMask;
	xlf_debug("parse_para: value %s len %d\r\n",value,pOffset->len);

	if(pOffset->len){
		xlf_debug("parse_para: pOffset %d\r\n",pOffset->offset);
		nBitOffset =7-pOffset->offset%8;
		nByteOffset=pOffset->offset/8;	
		nMask=(0xff>>(8-pOffset->len))<<nBitOffset;
		
		xlf_debug("parse_para:Offset 0x%02x\r\n",nBitOffset);	
		xlf_debug("parse_para:Byte 0x%02x\r\n",nByteOffset);
		xlf_debug("parse_para:nMask 0x%02x\r\n",nMask);
		retlen++;
		if(pOffset->len<=8){
			if(pOffset->preset){
				nValue=1;
			}else{
				nValue=xlf_get_value(value,pOffset);
			}
			/*�����ǹؼ�,�ѵõ���ֵ��ŵ���Ӧ��λ�ã�����Ӱ����������*/
			copyStart[nByteOffset] |=nMask & (nValue<<nBitOffset);
			xlf_debug("Parse_Send:Value 0x%02x\r\n",nValue);
			xlf_debug("Parse_Send:Set 0x%02x\r\n",copyStart[nByteOffset]);
		}else{//����һ���ַ���ֱ�ӿ����ַ�
			nValue=HEX2BIN(value,&copyStart[nByteOffset+1-(pOffset->len/8)]);
			xlf_debug("Parse_Send:buffer %d %s\r\n",nValue,value);
		}
		 return retlen;
	} 
	return 0;
}


static int xlf_Build_Send(AT_CMD_T *pnode,build_info_t *build_info,short argc,char **argv){
	u8 i,ret=0,argcproc=0;
	char *msgSatar;
	HEAD_P0_T headP0;
	headP0.p0_head.head1=0xaa;
	headP0.p0_head.head2=0xaa;
	headP0.device_type=pnode->xm_cmd->device_type;
	// Default answer address is 0, if nessery,can give by JAVA or define in struct VAN_CMD_T
	headP0.answerAddr=0;
	headP0.cmdCode=pnode->xm_cmd->cmdCode;
	xlf_debug("Build_Send: argc %d set %d\r\n",argc,pnode->xm_set);
	memset(pnode->xm_at.XM_At_Ret,'\0',XM_MAX_BUF);
	memcpy(pnode->xm_at.XM_At_Ret,&headP0,sizeof(HEAD_P0_T));

	msgSatar=pnode->xm_at.XM_At_Ret+sizeof(HEAD_P0_T);
	// ��Ϊ��ATָ�����·��������ֻ��Ϊpnode->xm_set ==XM_SEND_SETTING
	// ��һ���Ľ���pnode->xm_set ��Ϊ��ȷ����������ĸ���
	if(pnode->xm_cmd->item){
		for(i=0;i<pnode->xm_cmd->item->num ;i++){
			xlf_debug("Build_Send: parameter %d item->num:%d xm_set:%d \r\n",i,pnode->xm_cmd->item->num,pnode->xm_set);
			if(argcproc > pnode->xm_cmd->item->setNum) //��������˽ṹ�ж���ķ������ݵĸ��������������
				break;
			if(pnode->xm_cmd->item->cmdArry[i].set){
				argcproc++;
				argc--;
				// ���ʵ������Ĳ�������Ӧ���еĲ�������0�Ž�ȥ
				ret=xlf_vanw_parse_para(pnode,msgSatar,argc>=0?argv[argcproc-1]:"0",&pnode->xm_cmd->item->cmdArry[i]);
			}
		}
	}else{ //˵��������P0 ����ֻ��2.5.1, 2.5.2 ������������
		return 0;
	}
	xlf_debug("left argc is %d ,set argcproc is %d \n",argc,argcproc);
	#if VANW_DEBUG
	if(argcproc){
		printf_buf("Build_Send",(uchar *)pnode->xm_at.XM_At_Ret,pnode->xm_cmd->item->setNum+sizeof(HEAD_P0_T));
	}
	#endif
	return pnode->xm_cmd->item->setNum+sizeof(HEAD_P0_T);
}

static void build_at_command(AT_CMD_T *pnode,build_info_t *build_info,int argc){
	int k=0,i = 0,funcNum;
	VAN_CMD_T *pat_cmd=NULL;
	memset(build_info,0,sizeof(build_info_t));
//	pnode->error=XM_ERROR_CMD_NOT_SUPPORT;
	xlf_debug("exec at:cmd  %s argc %d\r\n",pnode->xm_at.getcmd,argc);
	memset(pnode->xm_id,'\0',XM_ID_MAX);
	snprintf(pnode->xm_id,XM_ID_MAX,"%s",pnode->xm_at.getparam[0]);
		
	pnode->error=XM_ERROR_CMD_NOT_SUPPORT;
	for(k=0;k<ARRAY_SIZE(cmd_product_list);k++){
		
		pat_cmd = cmd_product_list[k].cmdList;
		funcNum=cmd_product_list[k].atNum;
		for(i=0;i < funcNum; i++){
			if(!strncmp(pat_cmd->at,pnode->xm_at.getcmd,\
				strlen(pat_cmd->at) > strlen(pnode->xm_at.getcmd)?(int)strlen(pat_cmd->at):(int)strlen(pnode->xm_at.getcmd))){
				xlf_debug("analysis the at %s \n",pat_cmd->at);
				pnode->error=XM_SUCCESS;
				pnode->xm_cmd=pat_cmd;
				pnode->argc=argc;

			//	build_info->conNUM=pat_cmd->conNUM; �ⲿ���������ڴ�JAVA������
			//	build_info->id.dataH=pat_cmd->id.dataH;
			//	build_info->id.dataL=pat_cmd->id.dataL;
				//build_info ʣ�µĲ���������˵
				xlf_debug("build_info:conNum=%d id.dataH=%d id.data.L=%d\n",build_info->conNUM,build_info->id.dataH,build_info->id.dataL);
				return;
			}
			pat_cmd++;
		}
	}
	xlf_debug("ERROR:at cmd not matched\n");
	return;
}


static int atAnalyze(AT_CMD_T *pnode){
	char *cmdStr=pnode->xm_at.XM_At_Buffer;
	int paramIdx=0;
	xlf_debug("\nanalyze:%s\r\n",pnode->xm_at.XM_At_Buffer); 
	
	if(*cmdStr == 'A' && *(cmdStr + 1) == 'T'){
			// �����ؼ��ַ�'+' '=' ','
		 while(*cmdStr != '\0'){
			switch(*cmdStr){
				case '+':
				{
					pnode->xm_at.getcmd=++cmdStr;
					while(*cmdStr != '='  && *cmdStr != '\0' /*&& *cmdStr != '\r' && *cmdStr != '\n'*/){
						cmdStr++;
					}	
					xlf_debug("gcmd:%s\r\n",pnode->xm_at.getcmd);
					break;
				}	
				case '=':/*full through*/
				case ',':
				{
					*cmdStr='\0';
					pnode->xm_at.getparam[paramIdx++]=++cmdStr;
					xlf_debug("gparam:%d %s\r\n",paramIdx,pnode->xm_at.getparam[paramIdx-1]);
					break;
				}
				default:
					cmdStr++;
			}/*end of switch*/ 
			
		}/*end of while*/
	}

	xlf_debug("there paramIdx =%d \n",paramIdx);

	return paramIdx;
}
static void xlf_dividing_str(AT_CMD_T *pnode,build_info_t *build_info,char *str,int strcnt){
	int paraNum=0;

	memset(pnode->xm_at.getparam,0,MAX_CMD_PARAM_NUM);
	xlf_debug("\nstrDividing:%s %d\r\n",pnode->xm_at.XM_At_Buffer,strcnt);
	paraNum = atAnalyze(pnode);
	build_at_command(pnode,build_info,paraNum);
}

static void xlf_add_domain(char *retbuf,uchar value,XM_Offset*pOffset){
	int i=0;
	if(pOffset && pOffset->textlen!=0 ){
		xlf_debug("get_string:%d %d\r\n",pOffset->textlen,value);
		for(i=0;i<pOffset->textlen;i++){
			if(value==pOffset->text[i].value){
				xlf_debug("get_string:Value %s %d\r\n",pOffset->text[i].str,pOffset->text[i].value);
				snprintf(retbuf+strlen(retbuf),XM_MAX_BUF-strlen(retbuf),"%s,",pOffset->text[i].str);
			}
		}
	}
	else{
		snprintf(retbuf+strlen(retbuf),XM_MAX_BUF-strlen(retbuf),"%d,",value);
	}
}

void xlf_parse_hex(char *retbuf,char *at,u8 *value,XM_Offset *pOffset){
	u8 nValue;
//	int i=0;
	u8 nByteOffset=0,nBitOffset,nMask;
	u8 strLen;
	
//	xlf_debug("parse_para: value %s len %d\r\n",value,pOffset->len);
	nBitOffset =7-pOffset->offset%8;
	nByteOffset=pOffset->offset/8;	
	nMask=(0xff>>(8-pOffset->len))<<nBitOffset;
//	xlf_debug("parse_para:Offset 0x%02x\r\n",nBitOffset);	
//	xlf_debug("parse_para:Byte 0x%02x\r\n",nByteOffset);
//	xlf_debug("parse_para:nMask 0x%02x\r\n",nMask);
//	retlen=nByteOffset+1;
//	xlf_debug("Parse_Recv:slen %d\r\n",strLen);
	if(pOffset->len<=8){
		nValue=(value[nByteOffset] & nMask) >>nBitOffset;
//		xlf_debug("Parse_Recv:nValue %d %d\r\n",nValue,value[nByteOffset]);
		xlf_add_domain(retbuf,nValue,pOffset);
//		xlf_debug("Parse_Recv :int Buffer %s\r\n",(char *)retbuf);
	}else{
		//Ĭ�����ַ���
		strLen=pOffset->len/8+(pOffset->len%8?1:0);
		#if 0
		for (i=0;i<strLen;i++)
		{		// �ж��ǿɼ��ַ����ǿ��ַ��������
			if ((value[(pOffset->offset+i*8-pOffset->len)/8]>=0x20 && value[(pOffset->offset+i*8-pOffset->len)/8]<=0x7e)||(value[(pOffset->offset+i*8-pOffset->len)/8]==0))
			{
				LOGD("Parse_Recv  String !!! pxm->XM_Status_Buffer[%d]=0x%x",i,value[(pOffset->offset+i*8-pOffset->len)/8]);
				continue;	
			}
			else	
			{
				LOGD("Parse_Recv  String ERROR!!! pxm->XM_Status_Buffer[%d]=0x%x",i,value[(pOffset->offset+i*8-pOffset->len)/8]);
				snprintf((char *)retbuf,XM_MAX_BUF,"+%s:ERROR,%d",at,XM_ERROR_MAX_CMD_IN_STRING_PARSE_ERROR);
				xlf_debug("Parse_Recv  String ERROR!!: %s\r\n",(char *)retbuf);
				return;
			}
		}	
		#endif
		nValue=BIN2HEX((char*)&(value[(pOffset->offset-pOffset->len+1)/8]),strLen,(char *)retbuf+strlen(retbuf));//(pOffset->len/8)-1
		retbuf[strlen(retbuf)]=',';
		xlf_debug("Parse_Recv:str Buffer %d %s\r\n",nValue,(char *)retbuf);
	}
}

/* ��AA .. ת��AT
 * retbuf:Ҫ���������ַ���
 * bodyP0: ʮ�����Ƶ�����
 * len :ʮ����������ĳ���
 * device_type:�����ֻ���
 * ����ֵ:����ַ����ĳ���
 */
int xlf_vanword_pasre(char * retbuf,char *hexstr,u8 device_type){
	int i,j,k;
//	int error=0;
	VANW_PRO_T *product=NULL;	//��һ����Ʒ
	u8 at_num=0;
	VANW_AT_T  *what_at=NULL;	//��Ʒ�е���һ��AT����
	VANW_ITEM_T *item=NULL;		//AT�����ж�Ӧ�Ĳ����б�
	XM_Offset *pOffset=NULL;	//�б���ÿһ�����ڵ�λ�ú�ռ�ÿռ�����
	u8 *hexData=NULL;
	HEAD_P0_T headP0;

	/* ��ͷ�������������ṹ�����Ϣ*/
	p0_t p0;
	
	memset(&p0,0,sizeof(p0_t));
	/*��һ��ִ����ɺ�p0�Ậ������Ҫ��������Ϣ��data0,�ǽ���������ʮ���������ݣ�len�ǳ���*/
	vanw_parse_head(&p0,hexstr);
	xlf_debug("\r\n: %#x  %#x  %#x   %#x \n",p0.error,p0.id.dataH,p0.id.dataL,p0.len);
//	printf_buf("vanw_parse_head return:",p0.p0_data,p0.len ? p0.len:p0.headDataLen);
	
	//Ԥ��������Ĵ���
//	snprintf(retbuf,XM_MAX_BUF,"+PACKAGE:ERROR,%d,",p0.error ?p0.error:XM_ERROR_FRAME_UNKOWN);
	if(p0.headDataLen){ //˵����û��P0
		if( p0.id.dataH == 0x03 && p0.id.dataL == 0x02 ){ 
			snprintf(retbuf,XM_MAX_BUF,"+PACKAGE:SUCCEED,0,");
			goto pack_tail;
		}
		if(p0.id.dataH == 0x03 && p0.id.dataL == 0x07 ){
			if(p0.error==0){
				snprintf(retbuf,XM_MAX_BUF,"+GETPROID:SUCCEED,");
				xlf_debug("CMD 03 07%s\n",retbuf);
				BIN2HEX((char *)p0.p0_data,p0.headDataLen,&retbuf[strlen(retbuf)]);
				retbuf[strlen(retbuf)]=',';
				goto pack_tail;
			}else{
				snprintf(retbuf,XM_MAX_BUF,"+GETPROID:ERROR,%d,",p0.error);
				goto pack_tail;
			}
		}
	}

#if 0	
	/*�����ȷ���������Ĳ�������AA AA��ʼ�ģ����Ҫ�ڵ����������֮ǰ���*/
	if(p0.p0_data[0] != 0xaa || p0.p0_data[1] != 0xaa){	//˵�����������
		p0.error=XM_ERROR_NO_BODY;
	}
#endif
	memcpy(&headP0,p0.p0_data,sizeof(HEAD_P0_T));
	xlf_debug("device_type:%#x  code cmd:%#x  \n",headP0.device_type,headP0.cmdCode);
	hexData=p0.p0_data+sizeof(HEAD_P0_T);
	if(headP0.cmdCode == 0x50 && p0.len==5 /*����У��*/){//���������
		snprintf(retbuf,XM_MAX_BUF,"AT+WFHB,");
		xlf_debug("get HB from clent\n");
		goto pack_tail;
	}
	xlf_debug("in to serch\n");

	for(i=0;product=&ret_product_list[i],i<ARRAY_SIZE(ret_product_list);i++){
		if(COMM_PRODUCT!=product->device_type && product->device_type !=headP0.device_type) continue;
		xlf_debug("find produce %#x\n",product->device_type);
		what_at= product->atList;
		at_num=product->atNum;
		if(what_at){
			xlf_debug("at list num:%d\n",at_num);
			for(j=0;j<at_num;j++){
//				xlf_debug("what_at->cmdCode %#x  headP0.cmdCode: %#x \n",what_at->cmdCode,headP0.cmdCode);
				if(what_at->cmdCode == headP0.cmdCode){	//�ҵ���
					xlf_debug("find at:%s\n",what_at->at);
					snprintf(retbuf,XM_MAX_BUF,"+%s:",what_at->at);
					if(p0.error){
						snprintf(retbuf,XM_MAX_BUF,"+%s:ERROR,%d,",what_at->at,p0.error);
						goto pack_tail;
					}
					item=what_at->item;
					if(item){
						if(item->num + sizeof(HEAD_P0_T)!= p0.len){	//���Ȳ���
							xlf_debug(" item->num=%ld given p0 len is %ld\n",item->num+sizeof(struct frame_crc) +sizeof(HEAD_P0_T),p0.len);
							p0.error=XM_ERROR_FRAME_SIZE;
							snprintf(retbuf,XM_MAX_BUF,"+%s:ERROR,%s,",what_at->at,STR(XM_ERROR_FRAME_SIZE));
							goto pack_tail;
						}
//						if(item->cmdArry){  //���item->num�����ڣ�����϶�Ҳ�����ڣ�������жϿ���ʡ��

						for(k=0;k<item->num;k++){							
							pOffset=&item->cmdArry[k];
							// ǰ����cmdArry Ҫ����
							if(pOffset->query)
								xlf_parse_hex(retbuf,what_at->at,hexData,pOffset);
						}
						goto pack_tail;
//						}
					}else{//����ǲ���������
						snprintf(retbuf,XM_MAX_BUF,"+%s:SUCCEED,%d,",what_at->at,0);
						goto pack_tail;
					}
				}
				what_at++;
			}
			xlf_debug("the cmdNum %#x not found in the product %#x at return list\n",headP0.cmdCode,headP0.device_type);
		}
	}
	xlf_debug("parse cmd failed err is %d \n",p0.error);
pack_tail:
	if(strlen(retbuf)){
		retbuf[strlen(retbuf)-1]='\r';
		retbuf[strlen(retbuf)]='\n';
		
		xlf_debug("get at str: %s",retbuf);
		return strlen(retbuf);
	}
	return 0;
}


/*at ��ʮ�������ַ�����ת��*/
/* sendbuf:��Ҫ���ص�Ŀ���ַ���
 * buf: atָ��
 * conNum ��Դ���Ӻ�
 * device_type:���ֲ�Ʒ
 * ctl_id_index ��֧�ֵĿ���id�б���������б����� gIdArr
 */
int xlf_vanword_build(char *sendbuf ,char *buf,int conNum,u8 ctl_id_index,u8 device_type){
	int retlen=0,i=0;
	AT_CMD_T pnode={};
	struct frame_crc crc_val={};
	build_info_t build_info={};
	char * str=buf;
	/*��ʱ��һ���������*/
	retlen=strlen(buf);
	xlf_debug("get atStr:%s\n",buf);
	
	if(ctl_id_index >= ARRAY_SIZE(gIdArr)){
		xlf_debug("the give ctrol id is out of supported ctl_id list");
		LOGE("the give ctrol id is out of supported ctl_id list ,index :%d \n",ctl_id_index);
		snprintf(sendbuf,1024,"%s",buf);
		return strlen(buf);	
	}
	/*** ͷ�Ĵ��� ***/
	while((retlen >XM_AT_MIN) && (*str != 'A' || *(str + 1) != 'T')) {
		str++; 
		retlen--;
	}
	memset(pnode.xm_at.XM_At_Buffer,0,XM_MAX_BUF);
	/*��ö����һ������������һ��i*/
	while(*str  != '\0' && *str  != '\r' && *str  != '\n' && retlen > 0 && i < 250)
	{
		/* ���˿ո���ַ�*/
		if(*str  != ' '  && *str != '\t'){			
			// ��ATָ��copy��xm_at.XM_At_Buffer��
			pnode.xm_at.XM_At_Buffer[i++] = *str;
		}
		str++;
		retlen--;	
	}
	str=pnode.xm_at.XM_At_Buffer;
	retlen=i;
//	xlf_debug("buflen:%d str:%s\n",retlen,str);
	if(retlen <= XM_AT_MIN){
		snprintf(sendbuf,1024,"%s",buf);	//����ԭ�����ط���ģ��
		xlf_debug("at CMD lenght error\n");
		return strlen(buf);
	}
	if((memcmp(str,"AT+XM",5)==0)||(memcmp(str,"AT+WHO",6)==0)||(memcmp(str,"AT+WF",5)==0)){			
			pnode.error=XM_ERROR_CMD_EXEC;			
			snprintf(sendbuf,1024,"%s",buf);
			xlf_debug("WIFICOMMAND STRING! %s\r\n",sendbuf);
			return strlen(buf);
	}

	xlf_dividing_str(&pnode,&build_info,str,retlen);
	// ���û���ҵ�
	if(pnode.xm_cmd==NULL){
		xlf_debug("the given cmd:%s note found\n",pnode.xm_at.getcmd);
		snprintf(sendbuf,1024,"%s",buf);
		return strlen(buf);
	}
	if(pnode.xm_cmd->device_type != device_type){
		xlf_debug("Warning ... device ID not matched\n");
	}
	if(pnode.argc){	//���ǲ����ĸ�����˵���Ѿ��ҵ���Ӧ��Atָ��
		for(i=0;i<pnode.argc;i++){
			if(strncmp(pnode.xm_at.getparam[i],"?",1)==0){
			// ���ò��������ǲ�ѯ��ֵΪ0
				pnode.xm_set=XM_SEND_QUERY;
				break;
			// �������һ��������"*"
			}else if(strncmp(pnode.xm_at.getparam[i],"*",1)==0){
				// ��ʾ�ǹ��ܲ�ѯ
				pnode.xm_set=XM_SEND_SUPPORT;
				xlf_debug("xlf_packet_build:XM_SEND_SUPPORT!!\r\n");
				break;
			}else{
			//
				pnode.xm_set=XM_SEND_SETTING;
				xlf_debug("xlf_packet_build:XM_SEND_SETTING!!\r\n");
			}
		}
	}else{		// �����������Ϊ0
		pnode.xm_set=XM_SEND_SETTING;
	}	
	//�õ���Ҫ������֮��
	xlf_debug("pnode.error = %d \n",pnode.error);
#if XM_WITH_ID
	if(pnode.argc<1||(pnode.error!=XM_SUCCESS)){
		xlf_debug("UNPACKETD STRING\r\n");
		pnode.error=XM_ERROR_AT_PRAR;	
		//Ҳ����˵������Ǵ�ID��ָ���������Ϊ1���϶��ǲ��Եģ�ֱ�Ӱ�AT��buf������ȥ
		snprintf(sendbuf,1024,"%s",buf);
		retlen=strlen(sendbuf);
		xlf_debug("UNPACKETD STRING!ERROR %s\r\n",sendbuf);
		return retlen;
	}
	// ����Ƿ�������
	if(pnode.xm_set==XM_SEND_SETTING)
		// �������ò���1��ȥ����������WIFI ID
		pnode.xm_sendlen=xlf_Build_Send(&pnode,&build_info,pnode.argc-1,&pnode.xm_at.getparam[1]);
	else
		pnode.xm_sendlen=xlf_Build_Send(&pnode,&build_info,pnode.argc-2,&pnode.xm_at.getparam[2]);
#else
		pnode.xm_sendlen=xlf_Build_Send(&pnode,&build_info,pnode->argc,pnode.xm_at.getparam);
#endif
		build_info.bodyHex=(u8*)pnode.xm_at.XM_At_Ret;
		
		build_info.conNUM = conNum;
		memcpy(&build_info.id,gIdArr+ctl_id_index,sizeof(build_info.id));
		
		build_info.len=pnode.xm_sendlen;
		xlf_debug("build_info.len=%d\n",pnode.xm_sendlen);
		if(build_info.len>0){
			xlf_crc(build_info.bodyHex,build_info.len,&crc_val);
			build_info.bodyHex[build_info.len++]=crc_val.crc_high;
			build_info.bodyHex[build_info.len++]=crc_val.crc_low;
		}
		xlf_debug("len = %d conNUM:%d\n",build_info.len,build_info.conNUM);
//		printf_buf("before call :",build_info.bodyHex,build_info.len);
		return vanw_build_allstr(sendbuf,&build_info);
}



