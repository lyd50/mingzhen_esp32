/**********************************************************************
 *  Copyright(c) 2014-2015 China Mobile M2M Company Limited.
 *  All rights reserved.
 *
 *  閺傚洣娆㈤崥宥囆�: EdpPacket.h
 *  缁狅拷鐟曚焦寮挎潻锟�: Arduino edp packets encapsulation library
 *
 *  閸掓稑缂撻弮銉︽埂: 2015.5.27
 *   
 *  鐠囧瓨妲�:  Arduino edp packets encapsulation library
 *  閻楀牊婀�:  V1.0
 *
 *  娣囶喗鏁奸弮銉︽埂:
 *  娴ｆ粏锟斤拷:  
 *  鐠囧瓨妲�:  
 *
 * 
 **********************************************************************/

#ifndef _EDPKIT_H_
#define _EDPKIT_H_

//using namespace std;
#include <time.h>
#include "EdpKit.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "cJSON.h"  
//#define RET_ERR 0
//#define RET_OK (!(RET_ERR))


/*----------------------------濞戝牊浼呯猾璇茬��--------------------------------------*/
/* 鏉╃偞甯寸拠閿嬬湴 */
#define CONNREQ             0x10
/* 鏉╃偞甯撮崫宥呯安 */
#define CONNRESP            0x20
/* 鏉烆剙褰傞敍鍫ワ拷蹇庣炊閿涘鏆熼幑锟� */
#define PUSHDATA            0x30
/* 鐎涙ê鍋嶉敍鍫ワ拷蹇庣炊閿涘鏆熼幑锟� */
#define SAVEDATA            0x80
/* 鐎涙ê鍋嶇涵顔款吇 */
#define SAVEACK             0x90
/* 閸涙垝鎶ょ拠閿嬬湴 */
#define CMDREQ              0xA0
/* 閸涙垝鎶ら崫宥呯安 */
#define CMDRESP             0xB0
/* 韫囧啳鐑︾拠閿嬬湴 */
#define PINGREQ             0xC0
/* 韫囧啳鐑﹂崫宥呯安 */
#define PINGRESP            0xD0
/* 閸旂姴鐦戠拠閿嬬湴 */
#define ENCRYPTREQ          0xE0
/* 閸旂姴鐦戦崫宥呯安 */
#define ENCRYPTRESP         0xF0

/*--------------------------------------------------------------------*/
#define ERR_UNPACK_CONNRESP_REMAIN              -1000
#define ERR_UNPACK_CONNRESP_FLAG                -1001
#define ERR_UNPACK_CONNRESP_RTN                 -1002
#define ERR_UNPACK_PUSHD_REMAIN                 -1010
#define ERR_UNPACK_PUSHD_DEVID                  -1011
#define ERR_UNPACK_PUSHD_DATA                   -1012
#define ERR_UNPACK_SAVED_REMAIN                 -1020
#define ERR_UNPACK_SAVED_TANSFLAG               -1021
#define ERR_UNPACK_SAVED_DEVID                  -1022
#define ERR_UNPACK_SAVED_DATAFLAG               -1023
#define ERR_UNPACK_SAVED_JSON                   -1024
#define ERR_UNPACK_SAVED_PARSEJSON              -1025
#define ERR_UNPACK_SAVED_BIN_DESC               -1026
#define ERR_UNPACK_SAVED_PARSEDESC              -1027
#define ERR_UNPACK_SAVED_BINLEN                 -1028
#define ERR_UNPACK_SAVED_BINDATA                -1029
#define ERR_UNPACK_PING_REMAIN                  -1030
#define ERR_UNPACK_CMDREQ                       -1031
#define ERR_UNPACK_ENCRYPT_RESP                 -1032
#define ERR_UNPACK_SAVEDATA_ACK                 -1033

#define EDP_BUFFER_SIZE    200
#define PROTOCOL_NAME     "EDP"
#define PROTOCOL_VERSION  1

typedef unsigned char    uint8;
//typedef char             int8;
typedef unsigned short   uint16;
typedef short            int16;
typedef unsigned int     uint32;
typedef int              int32;

typedef enum {
    kTypeFullJson = 0x01,
    kTypeBin = 0x02,
    kTypeSimpleJsonWithoutTime = 0x03,
    kTypeSimpleJsonWithTime = 0x04,
    kTypeString = 0x05
}SaveDataType;

class EdpPacketClass
{
    public:
    EdpPacketClass();
    ~EdpPacketClass();
        
    uint8* GetData(void);
    uint32 GetWritepos(void);
    uint32 GetReadpos(void);
    void  ClearParameter(void);
    int32 CheckCapacity(uint32 len);
    int32 ReadByte(uint8* val);
    int32 ReadBytes(uint8** val, uint32 count);
    int32 ReadUint16(uint16* val);
    int32 ReadUint32(uint32* val);
    int32 ReadStr(char** val);
    int32 ReadRemainlen(uint32* len_val);
    int32 WriteByte(uint8 byte);
    int32 WriteBytes(const void* bytes, uint32 count);
    int32 WriteUint16(uint16 val);
    int32 WriteUint32(uint32 val);
    int32 WriteStr(const char *str);
    int32 WriteRemainlen(uint32 len_val);
    uint8* PacketConnect1(const char* devid, const char* auth_key);
    uint8* PacketConnect2(const char* userid, const char* auth_info);
    uint8* PacketPushdata(const char* dst_devid, const char* data, uint32 data_len);
    uint8* PacketSavedataBinStr(const char* dst_devid, const char* desc_str, const uint8* bin_data, uint32 bin_len);
    uint8* PacketSavedataSimpleString(const char* dst_devid, const char* input);
	uint8* PacketSavedataJson(const char* dst_devid, cJSON* json_obj, int type, uint16 msg_id);
    uint8* PacketCmdResp(const char* cmdid, uint16 cmdid_len,const char* resp, uint32 resp_len);
    uint8* PacketPing(void);
    int32  IsPkgComplete(uint8* bufdata,uint32 buflen);
    uint8  EdpPacketType(uint8* bufdata);
    int32  UnpackConnectResp(uint8* bufdata);
    int32  UnpackCmdReq(uint8* bufdata, char** cmdid, uint16* cmdid_len, char** req, uint32* req_len);
    int32  UnpackPingResp(uint8* bufdata);
    private:
    uint8*  data;          
    uint32  write_pos;     
    uint32  read_pos;      
    uint32  capacity; 
        
};

#endif  //EDP_PACKET_H_



