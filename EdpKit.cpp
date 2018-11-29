#include "EdpKit.h"


/* 
 * 閸戣姤鏆熼崥锟�:  EdpPacketClass
 * 閸旂喕鍏�:    閺嬪嫰锟界姴鍤遍弫锟�
 * 鐠囧瓨妲�:    
 *   
 * 閻╃鍙ч崙鑺ユ殶:
 * 閸欏倹鏆�:    閺冿拷
 *   
 * 鏉╂柨娲栭崐锟�:  閺冿拷       
 */
EdpPacketClass::EdpPacketClass()
{
  this->data=NULL;
  this->write_pos=0;
  this->read_pos=0;
  this->capacity=200;
  
  data=(uint8*)malloc(sizeof(uint8)*200);
  assert(data!=NULL);
}

/* 
 * 閸戣姤鏆熼崥锟�:  ~EdpPacketClass
 * 閸旂喕鍏�:    閺嬫劖鐎崙鑺ユ殶
 * 鐠囧瓨妲�:    
 *   
 * 閻╃鍙ч崙鑺ユ殶:
 * 閸欏倹鏆�:    閺冿拷
 *   
 * 鏉╂柨娲栭崐锟�:  閺冿拷       
 */
EdpPacketClass::~EdpPacketClass()
{
  free(this->data);
  this->data=NULL;
}


/* 
 * 閸戣姤鏆熼崥锟�:  GetData
 * 閸旂喕鍏�:    閼惧嘲褰囬弫鐗堝祦閹存劕鎲抽敍瀛岲P閸栧懐娈戠挧宄邦潗閸︽澘娼�
 * 鐠囧瓨妲�:    
 *          
 * 閻╃鍙ч崙鑺ユ殶:
 * 閸欏倹鏆�:    閺冿拷
    
 * 鏉╂柨娲栭崐锟�:  缁鐎� (uint8*) 
 *          EDP閸栧懐娈戠挧宄邦潗閸︽澘娼�
 */
uint8* EdpPacketClass::GetData(void)
{
  return this->data;
}

/* 
 * 閸戣姤鏆熼崥锟�:  GetWritepos
 * 閸旂喕鍏�:    閼惧嘲褰囬弫鐗堝祦閹存劕鎲抽敍瀛岲P閸栧懐娈戦崘娆庣秴缂冿拷
 * 鐠囧瓨妲�:    
 *          
 * 閻╃鍙ч崙鑺ユ殶:
 * 閸欏倹鏆�:    閺冿拷
    
 * 鏉╂柨娲栭崐锟�:  缁鐎� (uint32) 
 *          EDP閸栧懐娈戦崘娆忓弳娴ｅ秶鐤�
 */
uint32 EdpPacketClass::GetWritepos(void)
{
  return this->write_pos;
}


/* 
 * 閸戣姤鏆熼崥锟�:  GetReadpos
 * 閸旂喕鍏�:    閼惧嘲褰囬弫鐗堝祦閹存劕鎲抽敍瀛岲P閸栧懐娈戠拠璁崇秴缂冿拷
 * 鐠囧瓨妲�:    
 *          
 * 閻╃鍙ч崙鑺ユ殶:
 * 閸欏倹鏆�:    閺冿拷
    
 * 鏉╂柨娲栭崐锟�:  缁鐎� (uint32) 
 *          EDP閸栧懐娈戠拠璁崇秴缂冿拷
 */
uint32 EdpPacketClass::GetReadpos(void)
{
  return this->read_pos;
}

/* 
 * 閸戣姤鏆熼崥锟�:  ClearParameter
 * 閸旂喕鍏�:    闁插秶鐤嗛弫鐗堝祦閹存劕鎲抽敍灞剧槨娑擄拷娑擃亝澧﹂崠鍛毐閺佹澘鍘涚拫鍐暏鐠囥儱鍤遍弫甯礉閻掕泛鎮楅柌宥嗘煀閹垫挸瀵橀弫鐗堝祦
 * 鐠囧瓨妲�:    
 *          
 * 閻╃鍙ч崙鑺ユ殶:
 * 閸欏倹鏆�:    閺冿拷
    
 * 鏉╂柨娲栭崐锟�:  void         
 */
void EdpPacketClass::ClearParameter(void)
{
  this->read_pos=0;
  this->write_pos=0;
  memset(data,0,200);
}

/* 
 * 閸戣姤鏆熼崥锟�:  CheckCapacity
 * 閸旂喕鍏�:    濡拷閺岊櫒uffer閺勵垰鎯侀懗钘夘檮閸愭瑥鍙嗛梹鍨娑撶皞en閻ㄥ嫬鐡ч懞鍌涚ウ閿涘苯顩ч弸婊�绗夋径鐕傜礉閼奉亜濮╅幍鈺佺潔Buffer閻ㄥ嫬顔愰柌蹇ョ礄娑撳秴濂栭崫宄泆ffer閺佺増宓侀敍锟�
 * 鐠囧瓨妲�:    
 *          
 * 閻╃鍙ч崙鑺ユ殶:
 * 閸欏倹鏆�:    閺冿拷
    
 * 鏉╂柨娲栭崐锟�:  void         
 */
int32 EdpPacketClass::CheckCapacity(uint32 len)
{
  uint32 cap_len = capacity;
    int32 flag = 0;
    uint8* pdata = NULL;

    while (cap_len - write_pos < len) /* remain len < len */
    {
        cap_len = cap_len << 1;
        if (++flag > 32)
            break;  /* overflow */
    }
    if (flag > 32)
        return -1;
    if (cap_len > capacity)
    {
        pdata = (uint8*)malloc(sizeof(uint8) * cap_len);
        memcpy(pdata, data, write_pos);
        free(data);
        data = pdata;
        capacity = cap_len;
    }
    return 0;
}

/* 
 * 閸戣姤鏆熼崥锟�:  ReadByte
 * 閸旂喕鍏�:    閹稿DP閸楀繗顔呴敍灞肩矤BUFFER娑擃叀顕伴崣鏍︾娑擃亜鐡ч懞鍌滄畱閺佺増宓�
 * 鐠囧瓨妲�:    
 *          
 * 閻╃鍙ч崙鑺ユ殶:
 * 閸欏倹鏆�:    
    
 * 鏉╂柨娲栭崐锟�:         
 */
int32 EdpPacketClass::ReadByte(uint8* val)
{
    if (read_pos+1 > write_pos) 
        return -1;
    *val =data[read_pos];
    read_pos += 1;
    return 0;
}


/* 
 * 閸戣姤鏆熼崥锟�:  ReadBytes
 * 閸旂喕鍏�:    閹稿DP閸楀繗顔呴敍灞肩矤BUFFER娑擃叀顕伴崣鏈縪unt娑擃亜鐡ч懞鍌滄畱閺佺増宓�
 * 鐠囧瓨妲�:    閸忔湹鑵慥AL閺勭枹ALLOC閸戣姤鏆熼崚鍡涘帳閻ㄥ嫬鐡ㄩ崒銊р敄闂傝揪绱濋崷銊ゅ▏閻€劌鐣稊瀣倵閿涘矂娓剁憰涔玶ee.
 *          
 * 閻╃鍙ч崙鑺ユ殶:
 * 閸欏倹鏆�:    
    
 * 鏉╂柨娲栭崐锟�:         
 */
int32 EdpPacketClass::ReadBytes(uint8** val, uint32 count)
{
    if (read_pos+count > write_pos) 
        return -1;
    *val = (uint8*)malloc(sizeof(uint8) * count);
    memcpy(*val, data+read_pos, count);
    read_pos += count;
    return 0;
}


/* 
 * 閸戣姤鏆熼崥锟�:  ReadUint16
 * 閸旂喕鍏�:    閹稿DP閸楀繗顔呴敍灞肩矤BUFFER娑擃叀顕伴崣鏈NT16閸婏拷
 * 鐠囧瓨妲�:    
 *          
 * 閻╃鍙ч崙鑺ユ殶:
 * 閸欏倹鏆�:    
    
 * 鏉╂柨娲栭崐锟�:         
 */
int32 EdpPacketClass::ReadUint16(uint16* val)
{
    uint8 msb, lsb;
    if (read_pos+2 > write_pos) 
        return -1;
    msb = data[read_pos];
    read_pos++;
    lsb = data[read_pos];
    read_pos++;
    *val = (msb<<8) + lsb;
    return 0;
}

/* 
 * 閸戣姤鏆熼崥锟�:  ReadUint32
 * 閸旂喕鍏�:    閹稿DP閸楀繗顔呴敍灞肩矤BUFFER娑擃叀顕伴崣鏈NT32閸婏拷
 * 鐠囧瓨妲�:    
 *          
 * 閻╃鍙ч崙鑺ユ殶:
 * 閸欏倹鏆�:    
    
 * 鏉╂柨娲栭崐锟�:         
 */
int32 EdpPacketClass::ReadUint32(uint32* val)
{
    int32 i = 0;
    uint32 tmpval = 0;
    if (read_pos+4 > write_pos) 
        return -1;
    while (i++ < 4) {
        tmpval = (tmpval << 8) | (data[read_pos]);
        read_pos++;
    }
    *val = tmpval;
    return 0;
}

/* 
 * 閸戣姤鏆熼崥锟�:  ReadStr
 * 閸旂喕鍏�:    閹稿DP閸楀繗顔呴敍灞肩矤BUFFER娑擃叀顕伴崣鏍х摟缁楋缚瑕�
 * 鐠囧瓨妲�:    val閺勭棳alloc閸戣姤鏆熼崚鍡涘帳閻ㄥ嫬鐡ㄩ崒銊р敄闂傝揪绱濋崷銊ゅ▏閻€劌鐣崥搴ㄦ付鐟曚公ree
 *          
 * 閻╃鍙ч崙鑺ユ殶:
 * 閸欏倹鏆�:    
    
 * 鏉╂柨娲栭崐锟�:         
 */
int32 EdpPacketClass::ReadStr(char** val)
{
    uint16 len = 0;
    int rc = 0;
    /* read str len */
    rc = ReadUint16(&len);
    if (rc) 
        return rc;
    if (read_pos+len > write_pos) 
        return -1;
    /* copy str val */
    *val = (char*)malloc(sizeof(char) * (len + 1));
    memset(*val, 0, len+1);
    strncpy(*val, (const char *)(data + read_pos), len);
    read_pos += len;
    return 0;
}


/* 
 * 閸戣姤鏆熼崥锟�:  ReadRemainlen
 * 閸旂喕鍏�:    閹稿DP閸楀繗顔呴敍灞肩矤BUFFER娑擃叀顕伴崣鏍ㄧХ閹垰澧挎担娆撴毐鎼达拷
 * 鐠囧瓨妲�:    
 *          
 * 閻╃鍙ч崙鑺ユ殶:
 * 閸欏倹鏆�:    
    
 * 鏉╂柨娲栭崐锟�:         
 */
int32 EdpPacketClass::ReadRemainlen(uint32* len_val)
{
    uint32 multiplier = 1;
    uint32 len_len = 0;
    uint8 onebyte = 0;
    int32 rc;
    *len_val = 0;

    do {
        rc = ReadByte(&onebyte);
        if (rc) 
            return rc;
    if(len_len==0)
    {
      *len_val += (onebyte & 0x7f);
        }
    else if(len_len==1)
    {
      *len_val += (onebyte & 0x7f) <<7;
    }
    else if(len_len==2)
    {
      *len_val += (onebyte & 0x7f) <<14;
    }
    else if(len_len==3)
    {
      *len_val += (onebyte & 0x7f) <<21;
    }
    else
    {;}
        len_len++;
        if (len_len > 4) {
            return -1;/*len of len more than 4;*/
        }
    } while((onebyte & 0x80) != 0);
    return 0;
}

/* 
 * 閸戣姤鏆熼崥锟�:  WriteByte
 * 閸旂喕鍏�:    閹稿DP閸楀繗顔呴敍灞界殺娑擄拷娑擃亜鐡ч懞鍌涙殶閹诡喖鍟撻崗顧婦P閸栧懐绱﹂崘璇х礄閺佺増宓侀幋鎰喅data閹碉拷閹稿洨娈戠粚娲？閿涳拷
 * 鐠囧瓨妲�:    
 *          
 * 閻╃鍙ч崙鑺ユ殶:
 * 閸欏倹鏆�:    
    
 * 鏉╂柨娲栭崐锟�:         
 */
int32 EdpPacketClass::WriteByte(uint8 byte)
{
    assert(read_pos == 0);
    if (CheckCapacity(1))
        return -1;
    data[write_pos] = byte;
    write_pos++;
    return 0;
}


/* 
 * 閸戣姤鏆熼崥锟�:  WriteBytes
 * 閸旂喕鍏�:    閹稿DP閸楀繗顔呴敍灞界殺count娑擃亜鐡ч懞鍌涙殶閹诡喖鍟撻崗顧婦P閸栧懐绱﹂崘璇х礄閺佺増宓侀幋鎰喅data閹碉拷閹稿洨娈戠粚娲？閿涳拷
 * 鐠囧瓨妲�:    
 *          
 * 閻╃鍙ч崙鑺ユ殶:
 * 閸欏倹鏆�:    
    
 * 鏉╂柨娲栭崐锟�:         
 */
int32 EdpPacketClass::WriteBytes(const void* bytes, uint32 count) 
{
    assert(read_pos == 0);
    if (CheckCapacity(count))
        return -1;
    memcpy(data + write_pos, bytes, count);
    write_pos += count;
    return 0;
}

/* 
 * 閸戣姤鏆熼崥锟�:  WriteUint16
 * 閸旂喕鍏�:    閹稿DP閸楀繗顔呴敍灞界殺uINT16閸婄厧鍟撻崗顧婦P閸栧懐绱﹂崘璇х礄閺佺増宓侀幋鎰喅data閹碉拷閹稿洨娈戠粚娲？閿涳拷
 * 鐠囧瓨妲�:    
 *          
 * 閻╃鍙ч崙鑺ユ殶:
 * 閸欏倹鏆�:    
    
 * 鏉╂柨娲栭崐锟�:         
 */
int32 EdpPacketClass::WriteUint16(uint16 val)
{
    assert( read_pos == 0);
    return WriteByte(0xff&((val)>>8)) 
        || WriteByte(0xff&(val));
}

/* 
 * 閸戣姤鏆熼崥锟�:  WriteUint32
 * 閸旂喕鍏�:    閹稿DP閸楀繗顔呴敍灞界殺uINT32閸婄厧鍟撻崗顧婦P閸栧懐绱﹂崘璇х礄閺佺増宓侀幋鎰喅data閹碉拷閹稿洨娈戠粚娲？閿涳拷
 * 鐠囧瓨妲�:    
 *          
 * 閻╃鍙ч崙鑺ユ殶:
 * 閸欏倹鏆�:    
    
 * 鏉╂柨娲栭崐锟�:         
 */
int32 EdpPacketClass::WriteUint32(uint32 val)
{
    assert(read_pos == 0);
    return WriteByte((val >> 24) & 0x00FF) 
        || WriteByte((val >> 16) & 0x00FF)
        || WriteByte((val >> 8) & 0x00FF) 
        || WriteByte((val) & 0x00FF);
}

/* 
 * 閸戣姤鏆熼崥锟�:  WriteStr
 * 閸旂喕鍏�:    閹稿DP閸楀繗顔呴敍灞界殺鐎涙顑佹稉鎻掑晸閸忣檵DP閸栧懐绱﹂崘璇х礄閺佺増宓侀幋鎰喅data閹碉拷閹稿洨娈戠粚娲？閿涳拷
 * 鐠囧瓨妲�:    
 *          
 * 閻╃鍙ч崙鑺ユ殶:
 * 閸欏倹鏆�:    
    
 * 鏉╂柨娲栭崐锟�:         
 */
int32 EdpPacketClass::WriteStr(const char *str)
{
    uint16 length = 0;
    assert(read_pos == 0);
    length = strlen(str);
    return WriteUint16(length) 
        || WriteBytes(str, length);
}


/* 
 * 閸戣姤鏆熼崥锟�:  WriteRemainlen
 * 閸旂喕鍏�:    閹稿DP閸楀繗顔呴敍灞界殺濞戝牊浼呴崜鈺�缍戦梹鍨閸婄厧鍟撻崗顧婦P閸栧懐绱﹂崘璇х礄閺佺増宓侀幋鎰喅data閹碉拷閹稿洨娈戠粚娲？閿涳拷
 * 鐠囧瓨妲�:    
 *          
 * 閻╃鍙ч崙鑺ユ殶:
 * 閸欏倹鏆�:    
    
 * 鏉╂柨娲栭崐锟�:         
 */
int32 EdpPacketClass::WriteRemainlen(uint32 len_val)
{
    uint32 remaining_length = len_val;
    int32  remaining_count = 0;
    uint8  byte = 0;

    assert(read_pos == 0);

    do {
        byte = remaining_length % 128;
        remaining_length = remaining_length / 128;
        /* If there are more digits to encode, set the top bit of this digit */
        if (remaining_length > 0) {
            byte = byte | 0x80;
        }
       data[write_pos++] = byte;
        remaining_count++;
    }while(remaining_length > 0 && remaining_count < 5);
    assert(remaining_count != 5);
    return 0;
}
/* 
 * 閸戣姤鏆熼崥锟�:  PacketConnect1 
 * 閸旂喕鍏�:    閹垫挸瀵� 鐠佹儳顦崚鎷岊啎婢跺洣绨惃鍑烡P閸楀繗顔呴崠鍜冪礉鏉╃偞甯寸拋鎯ь槵娴滄垹娈戠拠閿嬬湴閸栧拑绱欓惂璇茬秿鐠併倛鐦夐弬鐟扮础1閿涳拷
 * 鐠囧瓨妲�:    
 *          
 * 閻╃鍙ч崙鑺ユ殶:UnpackConnectResp
 * 閸欏倹鏆�:    devid      鐠佹儳顦琁D閿涘瞼鏁电拠鐤啎婢跺洦妞傞獮鍐插酱鏉╂柨娲栭惃鍑
 *          auth_key   闁村瓨娼堟穱鈩冧紖閿涘苯婀獮鍐插酱閻㈠疇顕惃鍕讲娴犮儲鎼锋担婊嗩嚉鐠佹儳顦惃鍑橮I-KEY鐎涙顑佹稉锟�
    
 * 鏉╂柨娲栭崐锟�:  缁鐎� (uint8*) 
 *          EDP閸栧懐娈戠挧宄邦潗閸︽澘娼�         
 */
uint8* EdpPacketClass::PacketConnect1(const char* devid, const char* auth_key) 
{  
  uint32 remainlen;

  ClearParameter();
  /* msg type */
  WriteByte(CONNREQ);
  /* remain len */
  remainlen = (2+3)+1+1+2+(2+strlen(devid))+(2+strlen(auth_key));
  WriteRemainlen(remainlen);
  /* protocol desc */
  WriteStr(PROTOCOL_NAME);
  /* protocol version */
  WriteByte(PROTOCOL_VERSION);
  /* connect flag */
  WriteByte(0x40);
  /* keep time */
  WriteUint16(1800);//5閸掑棝鎸撻懛锟�30閸掑棝鎸撴稊瀣？
  /* DEVID */
  WriteStr(devid);
  /* auth key */
  WriteStr(auth_key);
    
  return this->data;
}

/* 
 * 閸戣姤鏆熼崥锟�:  PacketConnect2 
 * 閸旂喕鍏�:    閹垫挸瀵� 鐠佹儳顦崚鎷岊啎婢跺洣绨惃鍑烡P閸楀繗顔呴崠鍜冪礉鏉╃偞甯寸拋鎯ь槵娴滄垹娈戠拠閿嬬湴閸栧拑绱欓惂璇茬秿鐠併倛鐦夐弬鐟扮础2閿涳拷
 * 鐠囧瓨妲�:    
 *          
 * 閻╃鍙ч崙鑺ユ殶:UnpackConnectResp
 * 閸欏倹鏆�:    userid      妞ゅ湱娲癐D閿涘苯婀獮鍐插酱濞夈劌鍞芥い鍦窗閺冭泛閽╅崣鎷岀箲閸ョ偟娈戞い鍦窗ID
 *          auth_info   闁村瓨娼堟穱鈩冧紖閿涘苯婀獮鍐插酱閻㈠疇顕拋鎯ь槵閺冭泛锝為崘娆掝啎婢跺洨娈慉UTH_INFO鐏炵偞锟窖嶇礄Json鐎电钖勭�涙顑佹稉璇х礆
    
 * 鏉╂柨娲栭崐锟�:  缁鐎� (uint8*) 
 *          EDP閸栧懐娈戠挧宄邦潗閸︽澘娼�         
 */
uint8* EdpPacketClass::PacketConnect2(const char* userid, const char* auth_info) 
{ 
  uint32 remainlen;
  
  ClearParameter(); 
  /* msg type */
  WriteByte(CONNREQ);
  /* remain len */
  remainlen = (2+3)+1+1+2+2+(2+strlen(userid))+(2+strlen(auth_info));
  WriteRemainlen(remainlen);
  /* protocol desc */
  WriteStr(PROTOCOL_NAME);
  /* protocol version */
  WriteByte(PROTOCOL_VERSION);
  /* connect flag */
  WriteByte(0xC0);
  /* keep time */
  WriteUint16(0x0080);
  /* devid */
  WriteByte(0x00);
  WriteByte(0x00);
  /* USERID */
  WriteStr(userid);
  /* auth info */
  WriteStr(auth_info);
  return this->data;
}


/* 
 * 閸戣姤鏆熼崥锟�:  PacketPushdata
 * 閸旂喕鍏�:    閹垫挸瀵� 鐠佹儳顦崚鎷岊啎婢跺洣绨惃鍑烡P閸楀繗顔呴崠鍜冪礉鐠佹儳顦稉搴ゎ啎婢跺洣绠ｉ梻瀵告畱鏉烆剙褰傞弫鐗堝祦
 * 鐠囧瓨妲�:    
 *          
 * 閻╃鍙ч崙鑺ユ殶:UnpackPushdata
 * 閸欏倹鏆�:    dst_devid   閻╊喚娈戠拋鎯ь槵ID
 *          data        閺佺増宓�
 *          data_len    閺佺増宓侀梹鍨
 *          bin_len     娴滃矁绻橀崚鑸垫殶閹诡噣鏆辨惔锟�     
 * 鏉╂柨娲栭崐锟�:  缁鐎� (uint8*) 
 *          EDP閸栧懐娈戠挧宄邦潗閸︽澘娼�         
 */
uint8* EdpPacketClass::PacketPushdata(const char* dst_devid, const char* data, uint32 data_len)
{ 
    uint32 remainlen;
  ClearParameter();
    /* msg type */
    WriteByte(PUSHDATA);
    /* remain len */
    remainlen = (2+strlen(dst_devid))+data_len;
    WriteRemainlen(remainlen);
    /* dst devid */
    WriteStr(dst_devid);
    /* data */
    WriteBytes(data, data_len);
    return this->data;
}

/* 
 * 閸戣姤鏆熼崥锟�:  PacketSavedataBinStr
 * 閸旂喕鍏�:    閹垫挸瀵� 鐠佹儳顦崚鎷岊啎婢跺洣绨惃鍑烡P閸楀繗顔呴崠鍜冪礉鐎涙ê鍋嶉弫鐗堝祦閿涘潌in閺嶇厧绱￠弫鐗堝祦閿涳拷
 * 鐠囧瓨妲�:    
 *          
 * 閻╃鍙ч崙鑺ユ殶:UnpackSavedataSimpleString
 * 閸欏倹鏆�:    dst_devid   閻╊喚娈戠拋鎯ь槵ID
 *          desc_obj    閺佺増宓侀幓蹇氬牚 鐎涙顑佹稉鍙夌壐瀵骏绱濋垾婕漵_id閳ワ拷:閳ユ蓟xx" xxx娑撹桨绨╂潻娑樺煑閺佺増宓佸ù浣告倳缁夊府绱濈拠锕侇潌 <鐠佹儳顦紒鍫㈩伂閹恒儱鍙嗛崡蹇氼唴2-EDP.docx>  
 *          bin_data    娴滃矁绻橀崚鑸垫殶閹癸拷
 *          bin_len     娴滃矁绻橀崚鑸垫殶閹诡噣鏆辨惔锟�     
 * 鏉╂柨娲栭崐锟�:  缁鐎� (uint8*) 
 *          EDP閸栧懐娈戠挧宄邦潗閸︽澘娼�         
 */
uint8* EdpPacketClass::PacketSavedataBinStr(const char* dst_devid, 
        const char* desc_str, const uint8* bin_data, uint32 bin_len)
{
    uint32 remainlen = 0;
    uint32 desc_len = 0;

    /* check arguments */
    desc_len = strlen(desc_str);
    if (desc_len > (0x01 << 16) || bin_len > (3 * (0x01 << 20)))           
    { /* desc < 2^16 && bin_len < 3M*/
        return 0;
    }
    ClearParameter();
  /* msg type */
  WriteByte(SAVEDATA);
    if (dst_devid)
    {
        /* remain len */
        remainlen = 1+(2+strlen(dst_devid))+1+(2+desc_len)+(4+bin_len);
        WriteRemainlen(remainlen);
        /* translate address flag */
        WriteByte(0x80);
        /* dst devid */
        WriteStr(dst_devid);
    }
    else
    {
        /* remain len */
        remainlen = 1+1+(2+desc_len)+(4+bin_len);
        WriteRemainlen(remainlen);
        /* translate address flag */
        WriteByte(0x00);
    }
    /* bin flag */
    WriteByte(0x02);
    /* desc */ 
    WriteStr(desc_str);
    /* bin data */
    WriteUint32(bin_len);
    WriteBytes(bin_data, bin_len);
    return this->data;
}

/* 
 * 閸戣姤鏆熼崥锟�:  PacketSavedataSimpleString
 * 閸旂喕鍏�:    閹垫挸瀵� 鐠佹儳顦崚鎷岊啎婢跺洣绨惃鍑烡P閸楀繗顔呴崠鍜冪礉鐎涙ê鍋嶉弫鐗堝祦閿涘牅浜掗崚鍡楀娇閸掑棝娈ч惃鍕暆閸楁洖鐡х粭锔胯瑜般垹绱￠敍锟�
 * 鐠囧瓨妲�:    
 *          
 * 閻╃鍙ч崙鑺ユ殶:UnpackSavedataSimpleString
 * 閸欏倹鏆�:    dst_devid      閸涙垝鎶D
            input          娴犮儱鍨庨崣宄板瀻闂呮梻娈戠粻锟介崡鏇炵摟缁楋缚瑕嗚ぐ銏犵础
                           鐠囷箒顫� <鐠佹儳顦紒鍫㈩伂閹恒儱鍙嗛崡蹇氼唴2-EDP.docx>      
 * 鏉╂柨娲栭崐锟�:  缁鐎� (uint8*) 
 *          EDP閸栧懐娈戠挧宄邦潗閸︽澘娼�         
 */
uint8* EdpPacketClass::PacketSavedataSimpleString(const char* dst_devid, const char* input)
{
    //EdpPacket* pkg = NULL;
    uint32 remainlen = 0;
    uint32 input_len = 0;

    ClearParameter();
    input_len = strlen(input);
    /* msg type */
    WriteByte(SAVEDATA);
    if (dst_devid)
    {
        /* remain len */
        remainlen = 1+(2+strlen(dst_devid))+1+(2+input_len);
        WriteRemainlen(remainlen);
        /* translate address flag */
        WriteByte(0x80);
        /* dst devid */
        WriteStr(dst_devid);
    }
    else
    {
        /* remain len */
        remainlen = 1+1+(2+input_len);
        WriteRemainlen(remainlen);
        /* translate address flag */
        WriteByte(0x00);
    }
    /* json flag */
    WriteByte(kTypeString);
    /* json */ 
    WriteStr(input);

    return this->data;
}
/* sava_data (C->S) */

uint8* EdpPacketClass::PacketSavedataJson(const char* dst_devid, cJSON* json_obj, int type, uint16 msg_id)
{
	//EdpPacket* pkg = NULL;
	uint32 remainlen = 0;
	char* json_out = NULL;
	uint32 json_len = 0;
	uint8 flag = 0;

	//pkg = NewBuffer();
	remainlen;
	json_out = cJSON_Print(json_obj);
	json_len = strlen(json_out);
	remainlen = 1 + (msg_id ? 2 : 0) +              /* 閸ュ搫鐣鹃柅澶愩�� + 濞戝牊浼呴弽鍥х箶 */
		(dst_devid ? (2 + strlen(dst_devid)) : 0) + /* 閻╊喚娈戠拋鎯ь槵 */
		1 + (2 + json_len);                         /* 閺佺増宓佺猾璇茬�� + Json娑撴煡鏆辨惔锟� */

													/* msg type */
	WriteByte( SAVEDATA);
	/* remain len */
	WriteRemainlen( remainlen);
	/* flag */
	flag |= dst_devid ? 0x80 : 0;
	flag |= msg_id ? 0x40 : 0;
	WriteByte( flag);

	if (dst_devid)
	{
		WriteStr( dst_devid);
	}

	if (msg_id)
	{
		WriteUint16( msg_id);
	}

	/* json flag */
	WriteByte( type);
	/* json */
	WriteStr( json_out);
	free(json_out);
	//return pkg;

	return this->data;
}







/* 
 * 閸戣姤鏆熼崥锟�:  PacketCmdResp
 * 閸旂喕鍏�:    閸氭垶甯撮崗銉︽簚閸欐垿锟戒礁鎳℃禒銈呮惙鎼达拷
 * 鐠囧瓨妲�:    
 *          
 * 閻╃鍙ч崙鑺ユ殶:UnpackCmdReq
 * 閸欏倹鏆�:    cmdid      閸涙垝鎶D
            cmdid_len  閸涙垝鎶D閻ㄥ嫰鏆辨惔锟�
            resp       閸濆秴绨查惃鍕Х閹拷
            resp_len   閸濆秴绨插☉鍫熶紖閻ㄥ嫰鏆辨惔锟�
            
 * 鏉╂柨娲栭崐锟�:  缁鐎� (uint8*) 
 *          EDP閸栧懐娈戠挧宄邦潗閸︽澘娼�         
 */
uint8* EdpPacketClass::PacketCmdResp(const char* cmdid, uint16 cmdid_len,
       const char* resp, uint32 resp_len)
{
    unsigned remainlen = 0;

    ClearParameter();
    /* 6 = 2 + 4 = len(cmdid_len) + len(resp_len) */
    remainlen = cmdid_len + resp_len + (resp_len ? 6 : 2);
    WriteByte(CMDRESP);
    WriteRemainlen(remainlen);
    WriteUint16(cmdid_len);
    WriteBytes(cmdid, cmdid_len);
    if (resp_len)
    {
      WriteUint32(resp_len);
      WriteBytes(resp, resp_len);
    }
    return this->data;
}

/* 
 * 閸戣姤鏆熼崥锟�:  PacketPing
 * 閸旂喕鍏�:    閹垫挸瀵� 閻㈣精顔曟径鍥у煂鐠佹儳顦禍鎴犳畱EDP閸楀繗顔呴崠鍜冪礉韫囧啳鐑﹂崠锟�
 * 鐠囧瓨妲�:    
 *          
 * 閻╃鍙ч崙鑺ユ殶:UnpackPingResp閿涘瓖dpPacketType
 * 閸欏倹鏆�:    閺冿拷
            
 * 鏉╂柨娲栭崐锟�:  缁鐎� (uint8*) 
 *          韫囧啳鐑﹂崠鍛畱鐠у嘲顫愰崷鏉挎絻         
 */
uint8* EdpPacketClass::PacketPing(void)
{
    ClearParameter();
    /* msg type */
    WriteByte(PINGREQ);
    /* remain len */
    WriteRemainlen(0);
    return this->data;
}

/* 
 * 閸戣姤鏆熼崥锟�:  UnpackConnectResp
 * 閸旂喕鍏�:    鐟欙絽瀵� 閻㈣精顔曟径鍥︾隘閸掓媽顔曟径鍥╂畱EDP閸楀繗顔呴崠鍜冪礉鏉╃偞甯撮崫宥呯安
 * 鐠囧瓨妲�:    
 *          
 * 閻╃鍙ч崙鑺ユ殶:PacketConnect1, PacketConnect2閿涘瓖dpPacketType
 * 閸欏倹鏆�:    bufdata     EDP閸栧懏鏆熼幑锟�
            
 * 鏉╂柨娲栭崐锟�:  缁鐎� (int32) 
 *          =0          鐟欙絾鐎介幋鎰
 *          >0          鏉╃偞甯存径杈Е閿涘苯鍙挎担鎾炽亼鐠愩儱甯崶鐘侯潌<鐠佹儳顦紒鍫㈩伂閹恒儱鍙嗛崡蹇氼唴2-EDP.docx>
 *          <0          鐟欙絾鐎芥径杈Е閿涘苯鍙挎担鎾炽亼鐠愩儱甯崶鐘侯潌閺堢悁閺傚洣娆㈤惃鍕晩鐠囶垳鐖�
 */
int32 EdpPacketClass::IsPkgComplete(uint8* bufdata,uint32 buflen)
{
    uint32 data_len = 0;
    uint32 len_val = 0;
    uint32 len_len = 0;
    uint8* pdigit = NULL;
    uint32 pkg_total_len = 0;
    
    data_len = buflen;
    if (data_len <= 1) 
    {
      return 0;   
    }
    /* recevie remaining len */
    pdigit = bufdata;

    do 
    {
      if (len_len > 4) 
      {
        return -1;  /* protocol error; */
      }
      if (len_len > data_len - 1) 
      {
        return 0;   /* continue receive */
      }
      len_len++;
      pdigit++;
      if(1==len_len)
      {
        len_val += ((*pdigit) & 0x7f);
      }
      else if(2==len_len)
      {
        len_val += ((*pdigit) & 0x7f)<<7;
      }
      else if(3==len_len)
      {
        len_val += ((*pdigit) & 0x7f)<<14;
      }
      else if(4==len_len)
      {
        len_val += ((*pdigit) & 0x7f)<<21;
      }
      else
      {;}
    }while(((*pdigit) & 0x80) != 0);

    pkg_total_len = len_len + 1 + len_val;
    /* receive payload */
    if (pkg_total_len <= (uint32)data_len)
    {
      return pkg_total_len;   /* all data for this pkg is read */
    }
    else
    {
      return 0; 
    }
}

uint8 EdpPacketClass::EdpPacketType(uint8* bufdata)
{
    uint8 mtype = 0x00;
  mtype=*bufdata; 
    return mtype;
}

/* 
 * 閸戣姤鏆熼崥锟�:  UnpackConnectResp
 * 閸旂喕鍏�:    鐟欙絽瀵� 閻㈣精顔曟径鍥︾隘閸掓媽顔曟径鍥╂畱EDP閸楀繗顔呴崠鍜冪礉鏉╃偞甯撮崫宥呯安
 * 鐠囧瓨妲�:    
 *          
 * 閻╃鍙ч崙鑺ユ殶:PacketConnect1, PacketConnect2閿涘瓖dpPacketType
 * 閸欏倹鏆�:    bufdata     EDP閸栧懏鏆熼幑锟�
            
 * 鏉╂柨娲栭崐锟�:  缁鐎� (int32) 
 *          =0          鐟欙絾鐎介幋鎰
 *          >0          鏉╃偞甯存径杈Е閿涘苯鍙挎担鎾炽亼鐠愩儱甯崶鐘侯潌<鐠佹儳顦紒鍫㈩伂閹恒儱鍙嗛崡蹇氼唴2-EDP.docx>
 *          <0          鐟欙絾鐎芥径杈Е閿涘苯鍙挎担鎾炽亼鐠愩儱甯崶鐘侯潌閺堢悁閺傚洣娆㈤惃鍕晩鐠囶垳鐖�
 */
int32 EdpPacketClass::UnpackConnectResp(uint8* bufdata)
{
    uint8  flag, rtn;
  uint32 len_len = 0;
    uint8* pdigit = bufdata+1;
    uint32 len_val = 0;
  do {
    if(len_len==0)
    {
      len_val += (*pdigit & 0x7f);
        }
    else if(len_len==1)
    {
      len_val += (*pdigit & 0x7f) <<7;
    }
    else if(len_len==2)
    {
      len_val += (*pdigit & 0x7f) <<14;
    }
    else if(len_len==3)
    {
      len_val += (*pdigit & 0x7f) <<21;
    }
    else
    {;}
    pdigit++;
        len_len++;
        if (len_len > 4) {
            return ERR_UNPACK_CONNRESP_REMAIN; /*len of len more than 4;*/
        }
    } while((*pdigit & 0x80) != 0);

  if(len_val>0)
  {
    flag = *pdigit++;
    len_val--;
  }
  else
  {
    return ERR_UNPACK_CONNRESP_FLAG;
  }

  if(len_val>0)
  {
    rtn = *pdigit;
    len_val--;
  }
  else
  {
    return ERR_UNPACK_CONNRESP_FLAG;
  }
 
    return (int32)rtn;
}

/* 
 * 閸戣姤鏆熼崥锟�:  UnpackCmdReq
 * 閸旂喕鍏�:    鐟欙絽瀵� 閻㈣精顔曟径鍥︾隘閸掓媽顔曟径鍥╂畱EDP閸楀繗顔呴崠鍜冪礉閸涙垝鎶ょ拠閿嬬湴濞戝牊浼�
 * 鐠囧瓨妲�:    鐟欙絾鐎介崨鎴掓姢鐠囬攱鐪伴崠鍛板箯閸欐牜娈慶mdid閸欏eq闂囷拷鐟曚礁婀担璺ㄦ暏閸氬酣鍣撮弨锟�
 *          
 * 閻╃鍙ч崙鑺ユ殶:PacketCmdResp閿涘瓖dpPacketType
 * 閸欏倹鏆�:    bufdata     EDP閸栧懏鏆熼幑锟�
            cmdid       閼惧嘲褰囬崨鎴掓姢ID
            cmdid_len   閸涙垝鎶D閻ㄥ嫰鏆辨惔锟�
            req         閻€劍鍩涢崨鎴掓姢閻ㄥ嫯鎹ｆ慨瀣╃秴缂冿拷
            req_len     閻€劍鍩涢崨鎴掓姢閻ㄥ嫰鏆辨惔锟�

 * 鏉╂柨娲栭崐锟�:  缁鐎� (int32) 
 *          =0          鐟欙絾鐎介幋鎰
 *          <0          鐟欙絾鐎芥径杈Е閿涘苯鍙挎担鎾炽亼鐠愩儱甯崶鐘侯潌閺堢悁閺傚洣娆㈤惃鍕晩鐠囶垳鐖�
 */
int32 EdpPacketClass::UnpackCmdReq(uint8* bufdata, char* * cmdid, uint16* cmdid_len, 
       char* * req, uint32* req_len)
{
  uint8  msb, lsb;
  uint8  len1,len2,len3,len4;
  uint32 len_len = 0;
    uint8* pdigit = bufdata+1;
    uint32 len_val = 0;

  do {
    if(len_len==0)
    {
      len_val += (*pdigit & 0x7f);
    }
    else if(len_len==1)
    {
      len_val += (*pdigit & 0x7f) <<7;
    }
    else if(len_len==2)
    {
      len_val += (*pdigit & 0x7f) <<14;
    }
    else if(len_len==3)
    {
      len_val += (*pdigit & 0x7f) <<21;
    }
    else
    {;}
    pdigit++;
    len_len++;
        if (len_len > 4) {
            return ERR_UNPACK_CMDREQ; /*len of len more than 4;*/
        }
    } while((*pdigit & 0x80) != 0);

  if(len_val>=2)
  {
    msb=*pdigit++;
    lsb=*pdigit++;
    *cmdid_len=((msb<<8)+lsb);
    len_val-=2;
  }
  else
  {
    return ERR_UNPACK_CMDREQ;
  }
    
  if(len_val>=*cmdid_len)
  {
    *cmdid = (char*)malloc(sizeof(char) * (*cmdid_len+1));
    memset(*cmdid,0, (*cmdid_len+1));
    memcpy(*cmdid, pdigit, (*cmdid_len));
  
    pdigit+=(*cmdid_len);
    len_val-=(*cmdid_len);
  }
  else
  {
    return ERR_UNPACK_CMDREQ;
  }
    
  if(len_val>=4)
  {
    len1=*pdigit++; 
    len2=*pdigit++;   
    len3=*pdigit++;   
    len4=*pdigit++;
    *req_len=(len1<<24)+(len2<<16)+(len3<<8)+(len4);
    len_val-=4;
  }
  else
  {
    return ERR_UNPACK_CMDREQ;
  }
  if(len_val>=*req_len)
  {
    *req = (char*)malloc(sizeof(char) * (*req_len+1));
    memset(*req, 0, (*req_len+1));
    memcpy(*req, pdigit, (*req_len));
    
    pdigit+=(*req_len);
    len_val-=(*req_len);
  }
  else
  {
    return ERR_UNPACK_CMDREQ;
  }
    return 0;
}

/* 
 * 閸戣姤鏆熼崥锟�:  UnpackPingResp
 * 閸旂喕鍏�:    鐟欙絽瀵� 閻㈣精顔曟径鍥︾隘閸掓媽顔曟径鍥╂畱EDP閸楀繗顔呴崠鍜冪礉韫囧啳鐑﹂崫宥呯安
 * 鐠囧瓨妲�:    
 *          
 * 閻╃鍙ч崙鑺ユ殶:PacketPing, GetEdpPacket, EdpPacketType
 * 閸欏倹鏆�:    bufdata     EDP閸栧拑绱濋幒銉︽暪閸掓壆娈戠�瑰本鏆ｉ惃鍕妇鐠哄啿鎼锋惔鏂垮瘶
 * 鏉╂柨娲栭崐锟�:  缁鐎� (int32) 
 *          =0          韫囧啳鐑﹂幋鎰
 *          >0          韫囧啳鐑︽径杈Е閿涘苯鍙挎担鎾炽亼鐠愩儱甯崶鐘侯潌<鐠佹儳顦紒鍫㈩伂閹恒儱鍙嗛崡蹇氼唴EDP.docx>
 *          <0          鐟欙絾鐎芥径杈Е閿涘苯鍙挎担鎾炽亼鐠愩儱甯崶鐘侯潌閺堢悁閺傚洣娆㈤惃鍕晩鐠囶垳鐖�
 */
int32 EdpPacketClass::UnpackPingResp(uint8* bufdata)
{
  uint32 len_val = 0;
  uint32 len_len = 0;
  uint8* pdigit = bufdata+1;
  do {
  if(len_len==0)
  {
    len_val += (*pdigit & 0x7f);
  }
  else if(len_len==1)
  {
    len_val += (*pdigit & 0x7f) <<7;
  }
  else if(len_len==2)
  {
    len_val += (*pdigit & 0x7f) <<14;
  }
  else if(len_len==3)
  {
    len_val += (*pdigit & 0x7f) <<21;
  }
  else
  {;}
  pdigit++;
  len_len++;
  if (len_len > 4) 
  {
     return ERR_UNPACK_PING_REMAIN;  /*len of len more than 4;*/
  }
  } while((*pdigit & 0x80) != 0);
  return 0;
}



