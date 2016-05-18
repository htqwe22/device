/********************* xlf_crc.h ***********************
Author:		TaoHe
Create On: 10-08-2015
Modified : 10-13-2015
Info: call crc with initialized value.
**********************************************************/


#ifndef XLF_CRC__H
#define XLF_CRC__H

/** CRC8 �ݲ�����*/
unsigned char do_crc8(const unsigned char *message, unsigned int len,unsigned char crc_reg);

/** CRC16 1021
 * @param message ��Ҫ����У���������ʼ��ַ
 * @param len ҪУ������ݳ���
 * @param crc_reg ��ʼ��CRCֵ����һ�ε��ø�ֵΪ0������ֶ��У��һ���ܳ������ݣ�����ֱ�ӽ�
 *        ǰ��ĵõ���CRCֵ���롣
 */
unsigned short do_crc16_1021(const void *msg, unsigned int len,unsigned short crc_reg) ;

/** CRC32 04C11DB7
 * @param message ��Ҫ����У���������ʼ��ַ
 * @param len ҪУ������ݳ���
 * @param crc_reg ��ʼ��CRCֵ����һ�ε��ø�ֵΪ0������ֶ��У��һ���ܳ������ݣ�����ֱ�ӽ�
 *        ǰ��ĵõ���CRCֵ���롣
 */
unsigned int do_crc32_04C11DB7(const void *msg, unsigned int len,unsigned int crc_reg) ;

#endif // End of xlf_crc.h


