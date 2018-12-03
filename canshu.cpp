#include <WiFi.h>
#include <WiFiClient.h>
#include "EdpKit.h"
#include <OneWire.h>
#include <DallasTemperature.h>
/*--------------------------------输入输出，18脚测温------------------------------------------*/
int diyakg=23, ximo_gaoyakg = 22, yinyong_gaoyakg = 21, shengchan_gaoyakg = 19, jingshui_chaoyakg = 5, shuiliu_chuanganqi = 14;
int chaolv = 27, jingshui = 26, zongjin = 25, gaoyabeng = 33, youxian = 32, jiare = 35;
/* ---------------------------------------edp-----------------------------------------*/
bool wifi_connected = false;
unsigned int version = 20181128;
bool chxu_update = false;
const char *edp_server = "jjfaedp.hedevice.com";
unsigned int edp_port = 876;
bool edpConnected = false;
const char *apikey = "29R0uDMDtEHy9=HDEj17uO4Xx0U=", *device_id = "505210713";
unsigned char edp_buffer[200];	//???????
unsigned long xintiao_jiange = 0; //???????????
unsigned long guanbi_dingshi;	 //???????????????????????
WiFiClient edp_client;			  //
EdpPacketClass edp;				  //????EDP????
//unsigned char packettype;

/*------------------------------------------------------wifi------------------------------------------------ */

//const char *ssid = "";
//const char *password = "";
String former_wifi_ssid = "", wifi_ssid = "lydwifi", former_wifi_pass = "", wifi_pass = "19711128";
//bool you_fangwen=false;
int wifi_disconnect_count = 0, edp_disconnect_count = 0;
/*--------------------------------水流传感器-------------------------------------------*/
volatile long count = 0; //????????????????

/*--------------------------------超滤-------------------------------------------*/
byte chaolv_chongxi_maichong_dixian = 20;
byte loushui_maich_biaozhun = 10;
//unsigned int chaolvchongxi_zongcishu = 0; /*??????????*/
unsigned long accumulative = 0; /*?????????*/
byte chxi_cishu = 2;			//?????????????
byte leiji_biaozhun = 30;
bool chaolv_chxi = false, loushui_bool = false; //?????????????
unsigned long chaolvchongxi_zongcishu = 0;


/*--------------------------------调试-------------------------------------------*/
bool tiaoshikg = true;
/*--------------------------------显示屏串口-------------------------------------------*/
byte buffer[200]; //??????????
unsigned int buffer_index = 0;
byte brightness = 30; //???????50
bool set_once = true; //???????????
byte page = 0;		  //???0?????
byte pre_page = 50;   //???????????锟斤拷???????
String pre_kongjian, pre_text;
//byte ff_starter = 0;
byte terminator = 0; //?????????
bool parse_ready = false;
bool eeprom_write = false;
bool xsp_shezhi = false;
String order_sended = ""; 

/*--------------------------------制水-------------------------------------------*/
bool guanbi = false;			  //远程控制 true关机 false运行
byte zhishuishijian_set = 50;	 //?????????50?????255????
unsigned long zhishuizongshijian; //
byte zhishui_zong_add = 5;
byte zhishui_dan_add = 30;

bool yinyong_zhishui = false, shchan_zhishui = false;
byte shuimandengdaishijian_set = 6; //??????????????????? 6?????

byte zhishui_maichong_biaozhun = 30;

byte chaoshi_cishu = 0; /*????2?锟斤拷???????????*/
byte feishuiguoshao_times = 0;
unsigned long zhishui_starttime = 0, zhishui_endtime = 0;



/*--------------------------------洗膜-------------------------------------------*/
byte jingshuiximo_shichang = 6; //?????6????,??锟斤拷????
bool xuyao_ximo = false;
byte moci_ximo_maichong_biaozhun = 9, ximo_shuiliu_jiance_cishu = 10;
//byte dcf_chxi_shichang = 40; //??????????????
unsigned long ximo_begin = 0;

/*--------------------------------报警-------------------------------------------*/
String state = ""; //??????
unsigned long alarm_jiange = 0;
bool jingshui_chaoya = false, feishuiguoshao = false, alarm1 = false;


unsigned long begintime = 0, endtime, begintime2 = 0, endtime2;
unsigned long begintime_baohu = 0, endtime_baohu = 0;
/*-------------------------------启动原因------------------------------------------*/
String reason1,reason2;
