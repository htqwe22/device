#include	"xmlog.h"
#include	"xm_type.h"
#include    "protocol.h"

extern XM_AT_FUN at_cmd_kt[];
extern XM_AT_FUN at_cmd_kl[];
extern XM_AT_FUN at_cmd_jh[];
extern XM_AT_FUN at_cmd_cs[];
extern XM_AT_FUN at_cmd_qr[];
extern XM_AT_FUN at_cmd[];
extern XM_AT_FUN at_cmd_oven[];
extern XM_AT_FUN at_cmd_rsq[];
extern XM_AT_FUN at_cmd_rqz[];
struct para_desc{
	int offset;
	char *desc;
};
struct para_desc kt_set[]={
		{6,"����[auto/strong/middle/weak]"},
		{14,"˯��[off/aged/younger/child/general]"},
		{18,"ģʽ[heat/auto/cool/dehumidify/blow]"},
		{20,"����[0/1]"},		
		{22,"����[0/1]"},
		{30,"�����¶�[-64/64]"},
		{38,"����ʪ��[0-100]"},
		{47,"��������¶�[-64/64]"},
		{52,"��������¶Ȳ���[0-32]"},
		{54,"��п���[0/1]"},
		{59,"�Զ�����ģʽ�ͳ�ʪģʽ���¶Ȳ���[0-16]"},
		{61,"��ʾ��[0/1]"},
		{62,"����/�����¶���ʾ����[0/1]"},
		{70,"��ͨ��ʱ���ػ�[0.5h-23h]"},
		{76,"ʵʱʱ�ӵ�Сʱֵ[0-24]"},
		{85,"ʵʱʱ�ӵķ���ֵ[0-60]"},
		{94,"ʵʱ��������[0/1]"},
		{92,"ʵʱ����Сʱֵ[0-24]"},
		{101,"ʵʱ��������ֵ[0-60]"},
		{110,"ʵʱ�ػ�����[0/1]"},
		{108,"ʵʱ�ػ�Сʱֵ[0-24]"},
		{117,"ʵʱ�ػ�����ֵ[0-60]"},
		{122,"��ʪģʽ[auto/1#/2#/3#/4#/5#/6#/7#]"},
		{126,"���·���ģʽ[sweep/auto/1#/2#/3#/4#/5#/6#]"},
		{128,"���·翪ͣ����[0/1]"},
		{130,"���ҷ翪ͣ����[0/1]"},
		{132,"��Ȼ�翪ͣ����[0/1]"},
		{134,"����[0/1]"},
		{138,"���ýڵ�[0/1]"},
		{140,"��Ч[0/1]"},
		{142,"˫ģ[0/1]"},
		{136,"����[0/1]"},
		{144,"����[0/1]"},
		{146,"����[0/1]"},
		{148,"�������[0/1]"},
		{150,"�������[0/1]"},
		{152,"�ǻ���[0/1]"},
		{154,"����[0/1]"},
		{156,"����[0/1]"},
		{158,"����[0/1]"},
		{160,"������[0/1]"},
		{162,"��ʾ������[0/1]"},
		{164,"LEDָʾ��[0/1]"},
		{166,"�������¶��л���ʾ[0/1]"},
		{168,"���ڹ�������ิλ����[0/1]"},
		{170,"����[0/1]"},
		{172,"�ҷ��[0/1]"},
		{190,"��ʾ������ֵ0-255"}
};
struct para_desc kt_status[]={
		{6,"����"},
		{14,"˯��"},
		{19,"ģʽ"},
		{20,"����"},
		{22,"����"},
		{31,"�����¶�"},
		{55,"����ʪ��"},
		{71,"��������¶�"},
		{39,"����ʵ���¶�"},
		{47,"�����̹��¶�"},		
		{63,"����ʵ��ʪ��ֵ"},
		{76,"��������¶Ȳ���"},
		{78,"��п���"},
		{83,"�Զ�����ģʽ�ͳ�ʪģʽ���¶Ȳ���"},
		{86,"����/�����¶���ʾ����"},
		{94,"��ͨ��ʱ���ػ�"},
		{100,"ʵʱʱ�ӵ�Сʱֵ"},
		{109,"ʵʱʱ�ӵķ���ֵ"},
		{118,"ʵʱ��������"},
		{116,"ʵʱ����Сʱ"},
		{125,"ʵʱ��������"},
		{134,"ʵʱ�ػ�����"},
		{132,"ʵʱ�ػ�Сʱ"},
		{141,"ʵʱ�ػ�����"},
		{146,"��ʪģʽ"},
		{150,"���·���ģʽ"},
		{152,"���·翪ͣ����"},
		{153,"���ҷ翪ͣ����"},
		{154,"��Ȼ�翪ͣ����"},
		{155,"����"},
		{156,"����"},
		{157,"���ýڵ�"},
		{158,"��Ч"},
		{159,"˫ģ"},
		{160,"����"},
		{161,"����"},
		{162,"�������"},
		{163,"�������"},
		{164,"�ǻ���"},
		{165,"����"},
		{166,"����"},
		{167,"����"},
		{168,"������"},
		{169,"��ʾ������"},
		{170,"LEDָʾ��"},
		{171,"�������¶��л���ʾ"},
		{172,"���ڹ�������ิλ����"},
		{173,"����"},
		{174,"�ҷ��"},
		{175,"���ڵ�����"},
		{180,"��������֮ǰ�Ƿ��й�����ң���밴�����ƹ�"},
		{181,"��������֮ǰ�Ƿ��й�WIFI���ƹ�"},
		{182,"�յ�������������Ի���"},
		{183,"����EEPROM��������"},
		{184,"�����¶ȴ���������"},
		{185,"�����̹��¶ȴ���������"},
		{186,"����ʪ�ȴ���������"},
		{187,"������ˮ�ù���"},
		{188,"���ڷ�������ת�쳣����"},
		{189,"�����դ�����澯"},
		{190,"���ڵ�ѹ���������"},
		{191,"������ͨ�Ź���"},
		{192,"���ڿ��ư�����ʾ��ͨ�Ź���"},
		{193,"���ڿ��ư��밴����ͨ�Ź���"},
		{194,"WIFI���ư������ڿ��ư�ͨ�Ź���"},
		{195,"���ڿ��ư������ڵ�����ͨ�Ź���"},
		{196,"���ڿ��ư�EEPROM����"},
		{207,"����Ƶ��"},
		{215,"Ŀ��Ƶ��"},
		{223,"������������Ƶ��"},
		{231,"�����¶�"},
		{239,"�������¶�"},
		{247,"�����¶�"},
		{255,"Ŀ�������¶�"},
		{263,"����������ͷ�����"},
		{271,"UABH"},
		{279,"UABL"},
		{287,"UBCH"},
		{295,"UBCL"},
		{303,"UCAH"},
		{311,"UCAL"},
		{319,"IAB"},
		{327,"IBC"},
		{335,"CA"},
		{359,"IUV"},
		{343,"ֱ��ĸ�ߵ�ѹH"},
		{351,"ֱ��ĸ�ߵ�ѹL"},
		{363,"��ͨ��״̬"},
		{364,"�����ʵ�ʹ���״̬"},
		{367,"�������״̬"},
		{368,"�����ǿ�����ڻ�����λ��"},
		{369,"�����ǿ�����ڻ�����"},
		{370,"�����ǿ�����ڻ�ͣ"},
		{371,"�¿عػ�"},
		{372,"һ�϶��־"},
		{373,"��ʪ����־"},
		{374,"�������˪"},
		{375,"������ͨ��˪"},
		{376,"���ͱ�־"},
		{377,"���������ʾ��־"},
		{378,"�����EEPROM�������ر�־"},
		{379,"�����������"},
		{380,"ѹ�������ȴ�"},
		{381,"ѹ����Ԥ����"},
		{382,"��������"},
		{384,"�������ģʽ��ͻ"},
		{385,"����EEPROM����"},
		{386,"�����̹��¶ȴ���������"},
		{387,"�����¶ȴ���������"},
		{388,"���⻷���¶ȴ���������"},
		{389,"��ѹ��ѹ������"},
		{390,"��������������"},
		{391,"�������������ͨ�Ź���"},
		{392,"IPMģ���������"},
		{393,"IPMģ����ȱ���"},
		{394,"���������ѹ����"},
		{395,"������Ƿ��ѹ����"},
		{396,"ĸ�ߵ�ѹ����ѹ����"},
		{397,"ĸ�ߵ�ѹǷ��ѹ����"},
		{398,"PFC����������"},
		{399,"���������������"},
		{400,"���⻷���¶ȹ��ͱ���"},
		{401,"�����¶ȹ��߱���"},
		{402,"ѹ�����ܿ��¶ȱ���"},
		{403,"���ڷ����������ر���"},
		{404,"�����PFC����"},
		{405,"ѹ��������ʧ��"},
		{406,"ѹ����ʧ��"},
		{407,"��������ת"},
		{408,"�����̹ܷ����ر���"},
		{409,"��ýй©"},
		{410,"ѹ�����ͺ�ƥ�����"},
		{411,"ϵͳ��Ƶ�񶯱���"},
		{412,"����ɢ�����¶ȹ��߱���"},
		{413,"ϵͳѹ�����߱���"},
		{416,"�����ֱ������ѹ����"},
		{417,"�����ֱ���͵�ѹ����"},
		{418,"�������������������"},
		{419,"ʧ�����"},
		{420,"�ٶ��ƶ������������Ƿ�����"},
		{421,"�����ƶ������������Ƿ�����"},
		{422,"�����IPM����-����"},
		{423,"�����IPM����-��ƽ"},
		{424,"PFC_IPM����-����"},
		{425,"PFC_IPM����-��ƽ"},
		{426,"PFCͣ��������"},
		{427,"PFC�������������"},
		{428,"ֱ����ѹ����쳣"},
		{429,"PFC�͵�ѹ����Чֵ���������"},
		{430,"ADƫ���쳣�������"},
		{431,"�����PWM�߼����ù���"},
		{432,"�����PWM��ʼ������"},
		{433,"PFC_PWM�߼����ù���"},
		{434,"PFC_PWM��ʼ������"},
		{435,"�¶��쳣"},
		{436,"�����������費ƽ���������"},
		{437,"����������ù���"},
		{438,"MCE����"},
		{439,"����EEPROM����"},
		{440,"�����̹ܹ��ؽ���Ƶ"},
		{441,"�����̹ܹ��ؽ�Ƶ"},
		{442,"�����̹ܹ��ؽ���Ƶ"},
		{443,"�����̹ܹ��ؽ�Ƶ"},
		{444,"ѹ���������ؽ���Ƶ"},
		{445,"ѹ���������ؽ�Ƶ"},
		{446,"�����̹ܶ������Ƶ"},
		{447,"�����̹ܶ��ήƵ"},
		{448,"������ͨ�Ž�Ƶ"},
		{449,"ģ���¶ȹ�����Ƶ"},
		{450,"�������Ƶ"},
		{451,"�������Ƶ"},
		{452,"���ýڵ籣������Ƶ"},
		{453,"���ýڵ籣����Ƶ"},
		{454,"��������������Ƶ"},
		{455,"������������Ƶ"},
		{463,"���ڷ��ת��xx"},
		{471,"���ڷ��ת��00xx"},
		{472,"�з�PM2.5��⹦��"},
		{479,"PM2.5��Ⱦ�̶�"},
		{487,"����PM2.5�����ٷֱȱ�ʾ"},
		{494,"��ʾ������ֵ"}
};

struct para_desc kt_fun[]={
		{7,"���ڷ���֧�ֵ�λ��KTFL"},
		{15,"˯��ģʽ֧������KTSM"},
		{16,"��ʾ����/��ů����KTDR"},
		{17,"���ػ�����λKTKJ"},
		{18,"���ڵ���������ƹ���KTFX"},
		{19,"�����¶�����KTWD"},
		{20,"����ʪ������KTSD"},
		{21,"��������¶Ƚ�������KTTGCZ"},
		{22,"�����¶���в�������KTTGBC"},
		{23,"�Զ��ͳ�ʪ�¶Ȳ���KTWDBC"},
		{31,"����¶Ȳ���ֵ������ֵ��"},
		{39,"�Զ��ͳ�ʪ�¶Ȳ���ֵ������ֵ��"},
		{40,"����/�����¶���ʾת��KTHS"},
		{41,"��ͨ��ʱ���ػ�KTGTT"},
		{42,"ʵʱ��ʱ���ػ�KTGT KTKT"},
		{43,"6λ�ÿɶ����ڷ���λ�ÿ���KTVFM"},
		{44,"���·��ſ���KTVFC"},
		{45,"���ҷ��ſ���KTHFC"},
		{46,"��Ȼ�����KTZRF"},
		{47,"���ȿ�ͣ����KTDR"},
		{55,"��ʪģʽ����KTCS"},
		{56,"���ܿ���KTJN"},
		{57,"���ýڵ����KTBY"},
		{58,"��Ч��ǿ��������KTGX"},
		{59,"˫ģ�л�����KTDM"},
		{60,"���¿���KTQS"},
		{61,"�������KTHF"},
		{62,"����������KTQJ"},
		{63,"����������KTSWQJ"},
		{64,"�ǻ��ۿ���KTZN"},
		{65,"����ģʽ����KTJY"},
		{66,"��������KTYY"},
		{67,"���̿���KTCY"},
		{68,"�����ƿ���KTBJD"},
		{69,"��ʾ��������ʾ����KTXSP"},
		{70,"LEDָʾ�ƿ���KTLED"},
		{71,"�������¶��л���ʾ����KTSRW"},
		{72,"���ڹ�������ิλ����KTGLW"},
		{73,"���ڿ�ͣ����KTZFC"},
		{74,"�ҷ�ڿ�ͣ����KTYFC"},
		{75,"101#-0#��22�ֽ�BIT1��BIT0Ԥ��λ�Ŀ��ƹ���"},
		{76,"101#-0#��11�ֽ�BIT1��BIT0Ԥ��λ�Ŀ��ƹ���"},
		{77,"101#-0#��10�ֽ�BIT2~BIT0Ԥ��λ�Ŀ��ƹ���"},
		{78,"����/�������ƹ���"},
		{87,"101#-0#��23�ֽ�Ԥ��λ�Ŀ��ƹ���"},
		{95,"101#-0#��25�ֽ�Ԥ��λ�Ŀ��ƹ���"},
		{103,"101#-0#��26�ֽ�Ԥ��λ�Ŀ��ƹ���"},
		{111,"101#-0#��27�ֽ�Ԥ��λ�Ŀ��ƹ���"},
		{119,"101#-0#��28�ֽ�Ԥ��λ�Ŀ��ƹ���"},
		{127,"101#-0#��29�ֽ�Ԥ��λ�Ŀ��ƹ���"},
		{135,"101#-0#��30�ֽ�Ԥ��λ�Ŀ��ƹ���"}
};

struct para_desc jh_set[]={
		{6,"����[weak/middle/strong/clear/auto]"},
		{8,"����[0/1]"},
		{14,"ģʽ[cleardust/clearsmell/smart/mute/sleep]"},
		{22,"��ͨ��ʱ���ػ�[0.5h-23h]"},		
		{24,"����[0/1]"},
		{26,"��ͯ��[0/1]"},
		{28,"ˮ���ӿ���[0/1]"},
		{30,"��ʪ������[0/1]"}
};
struct para_desc jh_status[]={
		{6,"�����ٶ�"},
		{14,"����ģʽ"},
		{16,"��ʱ���ػ�����"},
		{22,"��ʱ���ػ�ʱ��"},
		{31,"���ת��"},
		{39,"��������"},
		{47,"���������ٷֱ�"},
		{55,"���ʪ��"},
		{56,"��ͣ������"},
		{57,"��ͯ�����ؿ���"},		
		{58,"ˮ���ӿ�ͣ����"},
		{59,"��ʪ����ͣ����"},
		{60,"������������ʾ"},
		{61,"��������֮ǰ�з����Ͱ������ƹ�"},
		{62,"��������֮ǰ�з����Ͱ������ƹ�"},
		{64,"��ʪת�ֲ���"},
		{65,"ˮ���"},
		{66,"ˮ��δװ��"},
		{67,"ʪ�ȴ���������"},
		{68,"�������"},
		{70,"�糾����������"},
		{71,"������б����"}
};

struct para_desc jh_fun[]={
		{3,"�����ٶ�״̬-�Զ�����"},
		{4,"�����ٶ�״̬-���̹���"},
		{5,"�����ٶ�״̬-�߷繦��"},
		{6,"�����ٶ�״̬-�з繦��"},
		{7,"�����ٶ�״̬-�ͷ繦��	"},	
		{11,"����ģʽ״̬-˯�߹���"},	
		{12,"����ģʽ״̬-��������"},	
		{13,"����ģʽ״̬-���ܹ���"},	
		{14,"����ģʽ״̬-��ζ����"},	
		{15,"����ģʽ״̬-	���̹���"},	
		{16,"��ͨ��ʱ����"},
		{17,"��ͯ������"},
		{18,"ˮ���ӿ�ͣ"},
		{19,"��ʪ����ͣ����"},
		{20,"��������ͣ����"},
		{22,"EEPROM�ɸ�д����"},
		{23,"������⹦��"},
		{24,"101#-0#��5�ֽ�Ԥ��λ�Ŀ��ƹ���"},
		{32,"101#-0#��6�ֽ�Ԥ��λ�Ŀ��ƹ���"}
};

struct para_desc cs_set[]={
		{6,"����[weak/strong/auto]"},
		{8,"����[0/1]"},
		{14,"ģʽ[continue/normal/auto/heat]"},
		{22,"��ͨ��ʱ���ػ�[0.5h-23h]"},
		{30,"ʪ��[0-100]"},		
		{40,"����[0/1]"},
		{42,"�����[0/1]"},
		{44,"ˮ��[0/1]"},
		{46,"������[0/1]"}
};

struct para_desc cs_status[]={
		{6,"����"},
		{14,"ģʽ"},
		{16,"��ʱ���ػ�����"},
		{22,"��ʱ���ػ�ʱ��"},
		{31,"ʪ��"},
		{39,"������趨�¶�"},
		{47,"�����¶�"},
		{48,"��ʪ������"},
		{49,"����ȿ���"},
		{50,"ˮ�ÿ���"},		
		{51,"�����ӿ���"},
		{52,"��������֮ǰ�з����Ͱ������ƹ�"},
		{53,"��������֮ǰ�з�WIFI���ƹ�"},
		{56,"���������澯"},
		{57,"ʪ�ȴ���������"},
		{58,"���´���������"},
		{59,"���´���������"},
		{60,"ˮ���澯"},
		{61,"ˮ�ù���"}
};

struct para_desc cs_fun[]={
		{4,"�ǻ۷�"},
		{5,"�߷�"},
		{6,"�з�"},
		{7,"�ͷ�"},		
		{13,"��������ģʽ"},
		{14,"��������ģʽ"},
		{15,"�Զ�����ģʽ"},
		{16,"��ͨ��ʱ����"},
		{17,"����ȹ���"},
		{18,"������¶�����"},
		{19,"����ʪ������"},
		{20,"ˮ�ÿ�ͣ����"},
		{21,"�����ӿ�ͣ����"},
		{22,"������⹦��"},
		{23,"��ͣ������"},
		{24,"EEPROM�ɸ�д����"},
		{39,"101#-0#��7�ֽ�Ԥ��λ�Ŀ��ƹ���"},
		{47,"101#-0#��8�ֽ�Ԥ��λ�Ŀ��ƹ���"}
};

struct para_desc qr_set[]={
		{6,"����[weak/middle/strong/auto]"},
		{10,"����[0/1]"},
		{14,"ģʽ[fullheat/direct/indoor/auto]"},
		{22,"��ͨ��ʱ���ػ�[0.5h-23h]"}
};
struct para_desc qr_status[]={
		{6,"�����ٶ�"},
		{10,"����"},
		{14,"����ģʽ"},
		{16,"��ʱ���ػ�����"},
		{22,"��ʱ���ػ�ʱ��"},
		{31,"������ת��"},
		{39,"���ڷ��ת��"},
		{47,"������¶�"},
		{55,"��������ʪ��"},
		{63,"���ڲ������̼Ũ�ȸ�λ"},
		{71,"���ڲ������̼Ũ�ȵ�λ"},		
		{72,"������������ʾ"},
		{73,"����������"},
		{74,"���ڷ������"},
		{75,"������¶ȴ���������"},
		{76,"�����ʪ�ȴ���������"},
		{77,"������̼����������"},
		{78,"���ڲ��¶ȴ���������"},
		{79,"���ڲ�ʪ�ȴ���������"}
};

struct para_desc qr_fun[]={
		{7,"����֧�ֵ�λ��"},
		{12,"ȫ�Ȼ���ģʽ"},
		{13,"ֱͨ����ģʽ"},
		{14,"�ط绻��ģʽ"},
		{16,"��ͨ��ʱ����"},
		{17,"���ػ�����λ"},
		{22,"EEPROM�ɸ�д����"},
		{23,"������⹦��"}
};


XM_AT_LIST xm_at_test[]={
#if XM_APP
		{48,at_cmd,0xff,"ģ�����"},
#else
		{48,at_cmd,0xff,"ģ�����"},
#endif
		{23,at_cmd_kl,0xff,"����ͨ��"},
		{53,at_cmd_kt,0x01,"�����յ�"},
		{11,at_cmd_jh,0x18,"��������������"},
		{12,at_cmd_cs,0x15,"������ʪ��"},
		{7,at_cmd_qr,0x19,"����ȫ�Ƚ�����"},
		{15,at_cmd_oven,0x27,"�����濾��"},
		{6,at_cmd_rsq,0x25,"��̫��ˮ��"},
		{5,at_cmd_rqz,0x22,"��̫ȼ����"},
};

		

char *getdesc(uchar offest,struct para_desc *pdesc,int size){
	int i;
	for(i=0;i<size;i++){
		if(pdesc[i].offset==offest)
			return pdesc[i].desc;
	}
	return NULL;
};

char *getktfun(uchar offest){
	int size=sizeof(kt_fun)/sizeof(kt_fun[0]);
	return getdesc(offest,kt_fun,size);
};
char *getktstatus(uchar offest){
	int size=sizeof(kt_status)/sizeof(kt_status[0]);
	return getdesc(offest,kt_status,size);
};
char *getktset(uchar offest){
	int size=sizeof(kt_set)/sizeof(kt_set[0]);
	return getdesc(offest,kt_set,size);
};

char *getjhfun(uchar offest){
	int size=sizeof(jh_fun)/sizeof(jh_fun[0]);
	return getdesc(offest,jh_fun,size);
};
char *getjhstatus(uchar offest){
	int size=sizeof(jh_status)/sizeof(jh_status[0]);
	return getdesc(offest,jh_status,size);
};
char *getjhset(uchar offest){
	int size=sizeof(jh_set)/sizeof(jh_set[0]);
	return getdesc(offest,jh_set,size);
};

char *getcsfun(uchar offest){
	int size=sizeof(cs_fun)/sizeof(cs_fun[0]);
	return getdesc(offest,cs_fun,size);
};
char *getcsstatus(uchar offest){
	int size=sizeof(cs_status)/sizeof(cs_status[0]);
	return getdesc(offest,cs_status,size);
};
char *getcsset(uchar offest){
	int size=sizeof(cs_set)/sizeof(cs_set[0]);
	return getdesc(offest,cs_set,size);
};

char *getqrfun(uchar offest){
	int size=sizeof(qr_fun)/sizeof(qr_fun[0]);
	return getdesc(offest,qr_fun,size);
};
char *getqrstatus(uchar offest){
	int size=sizeof(qr_status)/sizeof(qr_status[0]);
	return getdesc(offest,qr_status,size);
};
char *getqrset(uchar offest){
	int size=sizeof(qr_set)/sizeof(qr_set[0]);
	return getdesc(offest,qr_set,size);
};

int main(int argc,char *args[]){
#ifdef XM_MEM_DEBUG
	mtrace();
#endif
	FILE * fp;
    char buffer[512];
	int j=0,k=0,i=0,s1=0,funcNum,first=0,isset=0,id;
	XM_AT_FUN *pat_cmd;
	char cmdstr[255];
	char * pret;
	XmInitLog(8);
	XmSetLog("cmd",0);
	for(k=0;k<sizeof(xm_at_test)/sizeof(xm_at_test[0]);k++){
		pat_cmd = xm_at_test[k].funlist;
		funcNum = xm_at_test[k].listnum;
		id = xm_at_test[k].type;
#if DEBUG_AT
		XM_V("main at:%d %d %p\r\n",k,funcNum,pat_cmd);
#endif
		XM_V("%d:%s\r\n",k+2,xm_at_test[k].cmddesc);
		s1=1;
		for(i=0;i < funcNum; i++){	
			isset=0;
			
			if(pat_cmd->cmd){
#if XM_APP
				if(strncmp(pat_cmd->cmd,"RET",3)==0 ||  strncmp(pat_cmd->cmd,"OK",2)==0 ||strncmp(pat_cmd->cmd,"ERROR",5)==0 )
					continue;
#endif
				memset(cmdstr,0,255);
				memset(buffer,0,512);
				snprintf(cmdstr,255,"./getcmd.sh %s",pat_cmd->cmd);
				fp=popen(cmdstr,"r");
				fgets(buffer,sizeof(buffer),fp);
			    printf("%s",buffer);
			    pclose(fp);
				
				if(pat_cmd->parameter && strlen(buffer)>2){
					if(pat_cmd->parameter->set_cmd || pat_cmd->parameter->set_sub){
						if(strlen(buffer)>2){
							XM_V("	%d.%d:%s\r\n",k+2,s1,buffer);
							XM_V("		����:%s\r\n",pat_cmd->cmd);
						}
						s1++;
						XM_V("		���ù���:");
						first=0;
						isset=1;					
						for(j=0;j<pat_cmd->parameter->send_num;j++){
								if(pat_cmd->parameter->send[j].set && !pat_cmd->parameter->send[j].preset){
									if(first==0){
										first=1;
									}else{
										XM_V(",");
									}
									switch(id){
										case 1:
										XM_V("%s",getktset(pat_cmd->parameter->send[j].offset));
										//XM_V("%d�ֽ�",pat_cmd->parameter->send[j].len/8?pat_cmd->parameter->send[j].len/8:1);
										break;
										case 0x18:
										XM_V("%s",getjhset(pat_cmd->parameter->send[j].offset));
										//XM_V("%d�ֽ�",pat_cmd->parameter->send[j].len/8?pat_cmd->parameter->send[j].len/8:1);
										break;
										case 0x15:
										XM_V("%s",getcsset(pat_cmd->parameter->send[j].offset));
										//XM_V("%d�ֽ�",pat_cmd->parameter->send[j].len/8?pat_cmd->parameter->send[j].len/8:1);
										break;
										case 0x19:
										XM_V("%s",getqrset(pat_cmd->parameter->send[j].offset));
										//XM_V("%d�ֽ�",pat_cmd->parameter->send[j].len/8?pat_cmd->parameter->send[j].len/8:1);
										break;
									}	
								}
						}
						if(first==0){
							XM_V("�޲���");
						}
						XM_V("\r\n");
						XM_V("		���÷���:");
						first=0;
						for(j=0;j<pat_cmd->parameter->recv_num;j++){
							if(pat_cmd->parameter->recv[j].set){
								if(first==0){
									first=1;
								}else{
									XM_V(",");
								}
								switch(id){
									case 1:
										XM_V("%s",getktstatus(pat_cmd->parameter->recv[j].offset));
										//XM_V("%d�ֽ�",pat_cmd->parameter->recv[j].len/8?pat_cmd->parameter->recv[j].len/8:1);
									break;
									case 0x18:
										XM_V("%s",getjhstatus(pat_cmd->parameter->recv[j].offset));
										//XM_V("%d�ֽ�",pat_cmd->parameter->recv[j].len/8?pat_cmd->parameter->recv[j].len/8:1);
									break;
									case 0x15:
										XM_V("%s",getcsstatus(pat_cmd->parameter->recv[j].offset));
										//XM_V("%d�ֽ�",pat_cmd->parameter->recv[j].len/8?pat_cmd->parameter->recv[j].len/8:1);
									break;
									case 0x19:
										XM_V("%s",getqrstatus(pat_cmd->parameter->recv[j].offset));
										//XM_V("%d�ֽ�",pat_cmd->parameter->recv[j].len/8?pat_cmd->parameter->recv[j].len/8:1);
									break;
								}	
							}
						}
						if(first==0){
							XM_V("ִ�н��");
						}
						XM_V("\r\n");
					}
					
					if((pat_cmd->parameter->query_cmd || pat_cmd->parameter->query_sub) && !isset && (pat_cmd->parameter->recv_num > pat_cmd->parameter->query_len)){
						if(strlen(buffer)>2){
							XM_V("	%d.%d:%s\r\n",k+2,s1,buffer);
							XM_V("		����:%s\r\n",pat_cmd->cmd);
						}
						s1++;
						XM_V("		��ѯ״̬:?\r\n");
						XM_V("		״̬����:");
						first=0;
						for(j=0;j<pat_cmd->parameter->recv_num;j++){
							if(pat_cmd->parameter->recv[j].query ){
								if(first==0){
									first=1;
								}else{
									XM_V(",");
								}								
								if(pat_cmd->parameter->query_cmd==102 && pat_cmd->parameter->query_sub==64){									
									switch(id){
										case 1:
											pret=getktfun(pat_cmd->parameter->recv[j].offset);									
										break;
										case 0x18:
											pret=getjhfun(pat_cmd->parameter->recv[j].offset);									
										break;
										case 0x15:
											pret=getcsfun(pat_cmd->parameter->recv[j].offset);									
										break;
										case 0x19:
											pret=getqrfun(pat_cmd->parameter->recv[j].offset);									
										break;
									}	
								}else{
									switch(id){
										case 1:
											pret=getktstatus(pat_cmd->parameter->recv[j].offset);
										break;
										case 0x18:
											pret=getjhstatus(pat_cmd->parameter->recv[j].offset);
										break;
										case 0x15:
											pret=getcsstatus(pat_cmd->parameter->recv[j].offset);
										break;
										case 0x19:
											pret=getqrstatus(pat_cmd->parameter->recv[j].offset);
										break;
									}	
								}
								XM_V("%s",pret==NULL?"����":pret);
								//XM_V("%d�ֽ�",pat_cmd->parameter->recv[j].len/8?pat_cmd->parameter->recv[j].len/8:1);
							}
						}
						if(first==0){
							XM_V("�޲���");
						}
						XM_V("\r\n");
					}
					
				}
				XM_V("\r\n");
			}
			pat_cmd++;
		}
	}
}


