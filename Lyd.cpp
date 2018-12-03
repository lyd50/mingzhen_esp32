#include <Arduino.h>
#include "canshu.h"
#include "EEPROM.h"
//#include "hz.h"
#define EEPROM_SIZE 200
#include <rom/rtc.h>


void rcvDebug(unsigned char *rcv, int len)
{
	int i;

	Serial.print("edp鎺ユ敹鐨勬暟鎹�");
	Serial.println(len, DEC);
	for (i = 0; i < len; i++)
	{
		Serial.print(rcv[i], 10);
		Serial.print(" ");
	}
	Serial.println("");
}

void edp_reponse(int response_type)
{
	//ESP.wdtFeed();

	unsigned long time = millis() + 4000;
	while (!edp_client.available() && millis() < time)
		;

	int byte_count = edp_client.available();
	//memset(buffer, 0, 200);
	if (byte_count > 0) //??????
	{
		//buffer=   client.readBytesUntil('\r')
		for (int e = 0; e < byte_count; e++)
		{ //edp.UnpackConnectResp=edp_client.read();
			edp_buffer[e] = edp_client.read();
		}
		rcvDebug(edp_buffer, byte_count);
		//tiaoshi("??????????"+ edp.UnpackConnectResp(edp_buffer)) ;
		switch (response_type)
		{ //?锟�?????????

		case 1:

			//Serial.println("edp???????");
			//0x20 0x02 0x0 0x0

			if (edp_buffer[0] == 0x20 && edp_buffer[2] == 0x00 && edp_buffer[3] == 0x00)
			{
				Serial.println("EDP杩炴帴鎴愬姛");
				edpConnected = true;
				edp_disconnect_count = 0;
				//f_zhuang_tai("EDP ??????");
				//edp_upload_string("wifi", "wifi??????????");
			}

			else
			{
				//edp_upload_string("edp????", "???????????????????????????");//??????????????????????????

				edpConnected = false;
				edp_disconnect_count++; //????????????1
				//f_zhuang_tai("edp ????????????????????");

				//log_write("edp ????????????????????");//??????
				Serial.println("鏈夋暟锟�?锛屼絾鏁版嵁涓嶏拷?锟斤紝EDP杩炴帴澶辫触");
			}

			break;
			//????????2????? 208 0 ?? 0xD0 0
		case 2:
			//Serial.println("edp ???????");

			if (edp_buffer[0] == B11010000 && edp_buffer[1] == B00000000)
			{
				edpConnected = true;
				edp_disconnect_count = 0; //??????????
				//edp_upload_string("????", "???????????????????????");//
				Serial.println("EDP璇锋眰蹇冭烦鎴愬姛");
				//f_zhuang_tai("???????????????????????");
			}
			else
			{
				//??????????????????????????????????????????????????????????????
				//edp_upload_string("????", "?????????????????????");
				//f_zhuang_tai("??????????????????????????");
				edpConnected = false;   //????????????閿熸枻锟�??
				edp_disconnect_count++; //????????????1
				Serial.println("EDP璇锋眰蹇冭烦杩斿洖鏈夋暟锟�?浣嗘暟锟�?閿欙拷??");
			}
			break;
		}
	}

	else
	{
		Serial.println("娌℃湁鎺ユ敹鍒版暟锟�?");
		edpConnected = false;
		edp_disconnect_count++; //edp????????????1
								//f_zhuang_tai("??閿熸枻锟�?????EDP??????????");
	}
}

void edp_packet_send()
{ // ???????????????锟斤拷??????? ??锟斤拷???????
	//client.flush();
	while (edp_client.available())
	{
		edp_client.read();
	} //????????????
	if (!edp_client.connected())
	{
		edp_client.connect(edp_server, edp_port);
		Serial.print("?????edp???????? ");
		Serial.println((String)edp_server);
	}
	if (edp_client.connected())
	{
		//Serial.println("edp????????????");

		edp_client.write(edp.GetData(), edp.GetWritepos());

		//Serial.println("edp?????????");
		//???????????????????????????????
		/*if (ji_qi_shi_yan == true)//??????
		{
			xintiao_jiange = millis() + 60000; //???1???????????.???????????
		}
		else//??????????
		{
			xintiao_jiange = millis() + 200000; //???5???????????.??????????
		}*/
		//client.flush();//????锟斤拷????锟斤拷?????????????????????????????
	}
	else
	{
		Serial.println("edp?????????????");
	}
}

void wifi_connecte(String ssid, String password)
{
	if (ssid != "") //锟斤拷锟斤拷锟斤拷WiFi锟斤拷锟斤拷锟斤拷为锟斤拷
	{
		//delay(10);
		// We start by connecting to a WiFi network
		Serial.println();
		Serial.print("锟斤拷锟斤拷锟斤拷...");
		Serial.println(ssid);
		if (wifi_pass != "") //锟斤拷要锟斤拷锟斤拷
		{

			WiFi.begin(ssid.c_str(), password.c_str());
		}
		else
		{
			WiFi.begin(ssid.c_str()); //锟斤拷锟斤拷要锟斤拷锟斤拷锟斤拷锟斤拷
		}

		for (int i7 = 0; i7 < 15; i7++) //锟筋长锟饺达拷15锟斤拷
		{
			//ESP.wdtFeed();//锟斤拷止锟斤拷锟斤拷wifi时锟斤拷锟斤拷锟斤拷锟斤拷锟�??
			if (WiFi.status() != WL_CONNECTED)
			{
				delay(800);
				Serial.print(".");
			}
			else
			{
				wifi_connected = true;
				// wifi_ip = WiFi.localIP();

				Serial.println("");
				Serial.print("锟斤拷锟接碉拷锟斤拷");
				Serial.println(wifi_ssid);
				Serial.print("IP address: ");
				Serial.println(WiFi.localIP());
				//log_write("wifi锟斤拷锟接成癸拷");
				i7 = 20; //为锟斤拷锟斤拷锟斤拷锟斤拷WiFi锟斤拷锟斤拷锟剿筹拷循锟斤拷
			}
		}
	}
}

void edp_first_connect()
{
	if (!edp_client.connected())
	{
		edp_client.connect(edp_server, edp_port);
		Serial.print("锟斤拷锟接碉拷edp锟斤拷锟斤拷锟斤拷锟斤拷 ");
		Serial.println((String)edp_server);
	}
	if (edp_client.connected())
	{
		Serial.println("edp锟斤拷锟斤拷锟斤拷锟斤拷锟接成癸拷");

		edp.PacketConnect1(device_id, apikey);
		edp_packet_send();
		edp.ClearParameter();

		// Serial.println("??????????????");
		edp_reponse(1);
	}
	else
	{
		Serial.println("edp锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷失锟斤拷");
	}
}

void closeall() /*?????????*/
{
	digitalWrite(chaolv, LOW);
	//digitalWrite(rushui, LOW);
	//digitalWrite(chongxi, LOW);
	digitalWrite(jingshui, LOW);
	digitalWrite(gaoyabeng, LOW);
	digitalWrite(zongjin, LOW);
	digitalWrite(youxian, LOW);
	//digitalWrite(jiare, LOW);
}
void count_function()
{
	count++;
	delay(3);
}
void detect(unsigned long yongshi) /*???????,??锟斤拷????*/
{
	count = 0; /*????????????,???????*/
	unsigned long begintime2 = millis();
	unsigned long endtime2;
	attachInterrupt(digitalPinToInterrupt(shuiliu_chuanganqi), count_function, FALLING);
	do
	{
		endtime2 = millis();
	} while (endtime2 - begintime2 < yongshi);

	detachInterrupt(digitalPinToInterrupt(shuiliu_chuanganqi));
}

void decide_chaolv_chxi(unsigned long long1)
{
	//zhishuizongshijian = zhishuizongshijian + long1;
	//EEPROM.writeLong(3, zhishuizongshijian);

	accumulative = accumulative + long1;

	if (accumulative > leiji_biaozhun * 60000)
	{
		chaolv_chxi = true;
		accumulative = 0;
	}
}

void xianshiping_sendorder1(String kongjian, int value) //?????????
{

	Serial2.print(kongjian + ".val=" + value + "");
	for (int i = 0; i < 3;)
	{
		Serial2.write(0xff);
		i++;
	};
}

void xianshiping_sendorder2(String kongjian, String text) //?????????
{
	if (page == 0)
	{
		Serial2.print(kongjian + ".txt=\"" + text + "\"");
		for (int i = 0; i < 3;)
		{
			Serial2.write(0xff);
			i++;
		}
		delay(1500);
	}
}

void tiaoshi(String pingmuxianshi)
{

	if (tiaoshikg == true)
	{

		Serial.println(pingmuxianshi);
	}
}

void check_wifi() //锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷
{
	if (WiFi.status() != WL_CONNECTED)
	{
		wifi_connecte(wifi_ssid, wifi_pass); //wifi 15锟斤拷锟斤拷锟斤拷
	}
	if ((WiFi.status() != WL_CONNECTED)) //15锟斤拷锟斤拷锟接猴拷没锟斤拷锟斤拷锟接成癸拷
	{
		xianshiping_sendorder2("zhuangtai", "wifi锟斤拷锟斤拷锟接诧拷锟缴癸拷锟斤拷锟饺达拷锟铰达拷");
		if (tiaoshikg == true) //锟斤拷锟斤拷状态
		{
			xintiao_jiange = millis() + 60000; //锟斤拷锟�??1锟斤拷锟接凤拷锟斤拷锟斤拷锟斤拷.锟酵硷拷锟斤拷锟斤拷锟斤拷锟斤拷
		}
		else //锟斤拷锟斤拷锟斤拷锟斤拷状态
		{
			xintiao_jiange = millis() + 200000; //锟斤拷锟�??200锟斤拷锟斤拷臃锟斤拷锟斤拷锟斤拷锟�??.锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷
		}
		wifi_disconnect_count++;
		//log_write("wifi锟斤拷锟接诧拷锟缴癸拷锟斤拷锟饺达拷200锟斤拷锟斤拷麓锟斤拷锟斤拷锟�??");
		tiaoshi("wifi锟斤拷锟斤拷锟接诧拷锟缴癸拷锟斤拷锟饺达拷锟铰达拷");
	}
	else //15锟轿猴拷WiFi锟斤拷锟斤拷锟斤拷锟剿伙拷wifi没锟叫断匡拷
	{

		wifi_disconnect_count = 0; //WiFi锟斤拷锟斤拷失锟杰达拷锟斤拷锟斤拷锟斤拷

		edp_first_connect();
		/*if (edpConnected == true) {
				edp_upload_string("wifi", "wifi锟斤拷锟斤拷锟斤拷锟接成癸拷");
				f_zhuang_tai("wifi锟斤拷锟斤拷锟斤拷锟接成癸拷");
				//log_write("wifi锟斤拷锟斤拷锟斤拷锟接成癸拷");
				Serial.println("wifi锟斤拷锟斤拷锟斤拷锟接成癸拷");

			}*/
	}
}
void edp_heartbeat()
{
	//ESP.wdtFeed();
	if (WiFi.status() == WL_CONNECTED) //wifi锟斤拷锟斤拷状态
	{

		edp.PacketPing(); //??? 192 0  0xC0 0
		if (tiaoshikg == true)
		{
			rcvDebug(edp.GetData(), edp.GetWritepos());
		}

		edp_packet_send();

		Serial.println("?????????????");

		//???????
		edp.ClearParameter();

		edp_reponse(2); //锟剿猴拷锟斤拷锟斤拷锟斤拷确锟斤拷edp锟角凤拷锟斤拷锟斤拷
	}
	else
	{
		Serial.println("wifi锟较匡拷锟斤拷");
		check_wifi();
	}
}

void edp_upload_int(String data_stream_id, int datapoint) //锟较达拷WiFi锟脚猴拷强锟斤拷锟角革拷值
{
	if (edpConnected == true)
	{

		//ESP.wdtFeed();
		//Serial.println("锟较达拷锟斤拷一锟斤拷锟斤拷锟斤拷");
		String input = "{\"" + data_stream_id + "\":" + datapoint + "}\"";

		cJSON *cj = cJSON_Parse(input.c_str());

		edp.PacketSavedataJson("", cj, 3, 0);
		edp_packet_send();
		cJSON_Delete(cj); //锟斤拷锟斤拷锟缴撅拷锟斤拷锟絥odemcu锟斤拷锟斤拷锟斤拷
		while (edp_client.available())
		{
			edp_client.read();
		} //锟斤拷锟斤拷锟秸存储确锟斤拷
		edp.ClearParameter();
	}
}
void edp_upload_string(String data_stream_id, String datapoint)
{
	if (edpConnected == true)
	{

		//ESP.wdtFeed();
		//Serial.println("锟较达拷锟斤拷一锟斤拷锟街凤拷锟斤拷");

		String input = ",;";
		input += data_stream_id + ",";
		input += datapoint; //锟斤拷确锟斤拷式

		//EdpPacket*	edp = NewBuffer();

		edp.PacketSavedataSimpleString(device_id, input.c_str());
		edp_packet_send();
		while (edp_client.available())
		{
			edp_client.read();
		} //锟斤拷锟斤拷锟秸存储确锟斤拷

		//DeleteBuffer(&edp);
		edp.ClearParameter();
	}
}

void edp_command_parse() //约锟斤拷锟斤拷锟斤拷锟侥革拷锟斤拷锟斤拷,10锟斤拷锟斤拷前锟斤拷锟斤拷锟�??前锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟酵ｏ拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷值锟斤拷锟斤拷锟斤拷锟斤拷
{
	int order_type = (int(buffer[44]) - 48) * 10; //Serial.println(order_type);
	order_type = order_type + (int(buffer[45]) - 48);
	int value;

	//Serial.println(value);
	switch (order_type)
	{
		/*------------------------------------锟斤拷锟斤拷停止锟斤拷锟斤拷锟斤拷?锟斤拷------------------------------------------*/
	case 1:								   //约锟斤拷锟斤拷压锟斤拷锟截非接地端匡拷锟狡ｏ拷
		value = int(buffer[46] - 48) * 10; //Serial.println(value);
		value = value + (int(buffer[47]) - 48);
		switch (value)
		{
		case 1: //锟斤拷压锟斤拷锟截接碉拷锟斤拷痈叩锟轿伙拷谢锟�??  0101

			Serial.println("锟斤拷锟斤拷状态转锟斤拷");
			guanbi = !guanbi;   //要锟斤拷锟斤拷锟斤拷锟街碉拷锟戒。
			if (guanbi == true) //锟斤拷值时
			{
				//edp_upload_int("停锟斤拷", 1);

				EEPROM.writeBool(106, true); //106
				guanbi = true;
				//digitalWrite(D5, LOW);//锟斤拷压锟斤拷锟截接地ｏ拷锟斤拷锟斤拷锟斤拷锟斤拷
				edp_upload_string("锟斤拷锟斤拷锟斤拷", "锟斤拷锟斤拷值锟斤拷效锟斤拷锟窖撅拷锟叫伙拷");
				edp_upload_string("锟斤拷锟斤拷状态", "停锟斤拷");
			}
			else
			{
				//digitalWrite(D5, HIGH);//锟斤拷压锟斤拷锟截接高碉拷位锟斤拷停止锟斤拷锟斤拷
				guanbi = false;
				EEPROM.write(403, 0); //写锟斤拷eeprom
				//edp_upload_int("锟斤拷锟斤拷", 0);
				edp_upload_string("锟斤拷锟斤拷锟斤拷", "锟斤拷锟斤拷值锟斤拷效锟斤拷锟窖撅拷锟叫伙拷");
				edp_upload_string("锟斤拷锟斤拷状态", "锟斤拷锟斤拷");
			}
			break;
		default:
			edp_upload_string("锟斤拷锟斤拷锟斤拷", "锟斤拷锟斤拷值锟斤拷效");
			EEPROM.commit();

			break;
		}

		break;
		/*-------------------------------------------锟借定锟斤拷水时浓水------------------------------------------*/
	case 2:								   //锟斤拷水时浓水  02{V}
		value = int(buffer[46] - 48) * 10; //Serial.println(value);
		value = value + (int(buffer[47]) - 48);

		if (10 < value < 30)
		{
			//nongshui = value;
			// EEPROM.write(400, nongshui); //写锟斤拷eeprom
			Serial.println("锟斤拷水时浓水锟借定锟缴癸拷");
			edp_upload_string("锟斤拷锟斤拷锟斤拷", "锟斤拷锟斤拷值锟斤拷效锟斤拷锟斤拷水时浓水锟斤拷小锟借定锟缴癸拷");

			// f_zhuang_tai("锟斤拷锟斤拷值锟斤拷效锟斤拷锟斤拷水时浓水锟斤拷小锟借定锟缴癸拷");
			// upload_alert_standard(); //锟较憋拷锟斤拷锟斤拷锟斤拷准
		}
		EEPROM.commit();
		break;
		/*-------------------------------------------锟借定洗膜时浓水------------------------------------------*/

	case 3: //洗膜浓水 03{V}

		if ((buffer[1] == 45))
		{
			value = int(buffer[46]) - 48;
		}
		if ((buffer[1] == 46))
		{
			value = int(buffer[46] - 48) * 10; //Serial.println(value);
			value = value + (int(buffer[47]) - 48);
		}
		//ximo_sudu = value;
		//EEPROM.write(402, ximo_sudu); //写锟斤拷eeprom
		Serial.println("洗膜时浓水锟借定锟缴癸拷");
		edp_upload_string("锟斤拷锟斤拷锟斤拷", "锟斤拷锟斤拷值锟斤拷效锟斤拷洗膜时浓水锟斤拷小锟借定锟缴癸拷");
		//upload_alert_standard(); //锟较憋拷锟斤拷锟斤拷锟斤拷准

		// f_zhuang_tai("锟斤拷锟斤拷值锟斤拷效锟斤拷洗膜时浓水锟斤拷小锟借定锟缴癸拷");
		EEPROM.commit();
		break;
		/*-------------------------------------------压锟斤拷桶失效时锟斤拷锟借定------------------------------------------------*/
	case 4: //04{V}
		if ((buffer[1] == 45))
		{
			value = int(buffer[46]) - 48;
		}
		// yalitong_shuiman_fenzhong = value;
		// EEPROM.write(401, yalitong_shuiman_fenzhong); //写锟斤拷eeprom

		Serial.println("压锟斤拷桶失效时水锟斤拷时锟斤拷锟借定锟缴癸拷");
		edp_upload_string("锟斤拷锟斤拷锟斤拷", "锟斤拷锟斤拷值锟斤拷效锟斤拷压锟斤拷桶失效时水锟斤拷时锟斤拷锟借定锟缴癸拷");
		// edp_upload_int("压锟斤拷桶失效锟斤拷锟绞憋拷锟�??", yalitong_shuiman_fenzhong);
		// upload_alert_standard(); //锟较憋拷锟斤拷锟斤拷锟斤拷准

		// f_zhuang_tai("锟斤拷锟斤拷值锟斤拷效锟斤拷压锟斤拷桶失效时水锟斤拷时锟斤拷锟借定锟缴癸拷");
		EEPROM.commit();
		break;
		/*-------------------------------------------锟斤拷锟斤拷锟斤拷锟�??-------------------------*/
	case 5: //0599
		if ((buffer[1] == 46))
		{
			value = int(buffer[46] - 48) * 10; //Serial.println(value);
			value = value + (int(buffer[47]) - 48);
		}
		if (value == 99)

		{
			chxu_update = true;
			Serial.println("锟秸碉拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟�??锟狡伙拷锟斤拷停锟斤拷状态锟铰革拷锟斤拷");
			edp_upload_string("锟斤拷锟斤拷锟斤拷", "锟秸碉拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟�??锟狡伙拷锟斤拷停锟斤拷状态锟铰革拷锟斤拷");
		}

		/*-------------------------------------------缺省锟斤拷锟斤拷------------------------------------------*/

	default:
		//edp_upload_string("锟斤拷锟斤拷锟斤拷", "锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷效");
		break;
	}
}


void Serial2_command_parse() //????????????
{							 /*------------------------------????????????-------------------------------*/
	if (buffer[0] == 0x0)
	{
		Serial.print(order_sended);
		Serial.println(": 0x00");
	}
	if (buffer[0] == 0x02)
	{
		Serial.print(order_sended);
		Serial.println(": 0x02");
	}
	if (buffer[0] == 0x03)
	{
		Serial.print(order_sended);
		Serial.println(": 0x03");
	}
	if (buffer[0] == 0x04)
	{
		Serial.print(order_sended);
		Serial.println(": 0x04");
	}
	if (buffer[0] == 0x05)
	{
		Serial.print(order_sended);
		Serial.println(": 0x05");
	}
	if (buffer[0] == 0x11)
	{
		Serial.print(order_sended);
		Serial.println(": 0x11");
	}
	if (buffer[0] == 0x12)
	{
		Serial.print(order_sended);
		Serial.println(": 0x12");
	}
	//1A?????????????????閿熸枻鎷�,?????????閿熸枻鎷�????????
	if (buffer[0] == 0x1A)
	{
		Serial.print(order_sended);
		Serial.println(": 0x1A");
	}
	if (buffer[0] == 0x1B)
	{
		Serial.print(order_sended);
		Serial.println(": 0X1B");
	}
	if (buffer[0] == 0x1C)
	{
		Serial.print(order_sended);
		Serial.println(": 0X1C");
	}
	if (buffer[0] == 0x1D)
	{
		Serial.print(order_sended);
		Serial.println(": 0X1D");
	}
	if (buffer[0] == 0x1E)
	{
		Serial.print(order_sended);
		Serial.println(": 0X1E");
	}
	if (buffer[0] == 0x1F)
	{
		Serial.print(order_sended);
		Serial.println(": 0X1F");
	}
	if (buffer[0] == 0x23)
	{
		Serial.print(order_sended);
		Serial.println(": 0X23");
	}
	if (buffer[0] == 0x24)
	{
		Serial.print(order_sended);
		Serial.println(": 0X24");
	}

	/*------------------------------寰楀嚭椤甸潰鍙�-------------------------------*/
	if (buffer[0] == 0x66) //
	{
		page = buffer[1]; //
		tiaoshi("???" + (String)page);

		Serial.print("page:");
		Serial.println(page);
		if (pre_page != page)
		{
			set_once = true; //鍥犱负椤靛彿涓嶅悓锛屽厑璁镐紶閫佹暟鎹�

			pre_page = page;
		}
	}
/*---------------------------鍦�0鍙烽〉锛屽埌2鍙疯�剧疆椤甸潰:-------------------------------*/
	if (page == 0)
	{
		if (buffer[0] == 0x90)
		{ xsp_shezhi=true;
			Serial2.print("page 2"); //鍒拌�剧疆椤�
			for (int i = 0; i < 3;)
			{
				Serial2.write(0xff);
				i++;
			}     

		}
	}
/*----------------------------鍦�2鍙烽〉-鍒�0鍙疯�剧疆椤甸潰:-------------------------------*/
if (page == 2)
	{
		if (buffer[0] == 0x98)
		{
			xsp_shezhi=false;
			xianshiping_sendorder2("zhuangtai","涓插彛灞忓弬鏁拌�剧疆瀹屾垚");
			//edp_upload_string("鐘舵€�","涓插彛灞忓弬鏁拌�剧疆瀹屾垚");
			Serial2.print("page 0"); //鍒伴�栭〉
			for (int i = 0; i < 3;)
			{
				Serial2.write(0xff);
				i++;
			}
		}
	}


	/*-----------------------------3鍙疯秴婊よ�剧疆椤甸潰:-------------------------------*/
	if (page == 3)
	{ if (buffer[0] == 0x90)
		{
			chaolv_chongxi_maichong_dixian = buffer[1];
			EEPROM.writeByte(0, chaolv_chongxi_maichong_dixian); //0
			eeprom_write = true;
		}

		if (buffer[0] == 0x91)
		{
			loushui_maich_biaozhun = buffer[1];
			EEPROM.writeByte(2, loushui_maich_biaozhun); //
			eeprom_write = true;
		}

		if (buffer[0] == 0x92)
		{
			chxi_cishu = buffer[1];
			EEPROM.writeByte(4, chxi_cishu); //
			eeprom_write = true;
		}

		if (buffer[0] == 0x93)
		{
			leiji_biaozhun = buffer[1]; //
			EEPROM.writeByte(6, leiji_biaozhun);
			eeprom_write = true;
		}
            if (buffer[0] == 0x98)
		{Serial2.print("page 2"); //鍒拌�剧疆椤�
			for (int i = 0; i < 3;)
			{
				Serial2.write(0xff);
				i++;
			}           
		}
	}
	/*------------------------------4鍙烽〉闈�:璁剧疆鍒舵按鏈夊叧-----------------------------*/
	if (page == 4)
	{
		if (buffer[0] == 0x90)
		{
			zhishuishijian_set = buffer[1];			  //
			EEPROM.writeByte(50, zhishuishijian_set); //50

			tiaoshi("??????????:" + (String)zhishuishijian_set);
			eeprom_write = true;
		}

		if (buffer[0] == 0x91)
		{
			zhishui_maichong_biaozhun = buffer[1];
			EEPROM.writeByte(52, zhishui_maichong_biaozhun); //52???
			eeprom_write = true;
		}

		if (buffer[0] == 0x92)
		{
			chaoshi_cishu = buffer[1];
			EEPROM.writeByte(54, chaoshi_cishu); //????54???
			eeprom_write = true;
		}
		if (buffer[0] == 0x93)
		{
			shuimandengdaishijian_set = buffer[1]; //??43???
			EEPROM.writeByte(56, shuimandengdaishijian_set);
			eeprom_write = true;
		}
		if (buffer[0] == 0x98)
		{Serial2.print("page 2"); //鍒拌�剧疆椤�
			for (int i = 0; i < 3;)
			{
				Serial2.write(0xff);
				i++;
			}
		}
	}
	/*-----------------------------5鍙烽〉闈�:娲楄啘璁剧疆------------------------------*/
	if (page == 5)
	{
		if (buffer[0] == 0x90) //
		{
			jingshuiximo_shichang = buffer[1];
			EEPROM.writeByte(100, jingshuiximo_shichang); //
			eeprom_write = true;
		}

		if (buffer[0] == 0x91) //
		{
			ximo_shuiliu_jiance_cishu = buffer[1];
			EEPROM.writeByte(102, ximo_shuiliu_jiance_cishu); //
			eeprom_write = true;
		}
		if (buffer[0] == 0x92) //
		{
			moci_ximo_maichong_biaozhun = buffer[1];
			EEPROM.writeByte(104, moci_ximo_maichong_biaozhun); //????51???
			eeprom_write = true;
		}
		if (buffer[0] == 0x98)
		{Serial2.print("page 2"); //鍒拌�剧疆椤�
			for (int i = 0; i < 3;)
			{
				Serial2.write(0xff);
				i++;
			}
		}
	}
	/*------------------------------13?????:wifi????-------------------------------*/

	/*------------------------------7鍙蜂寒搴﹂〉闈㈠�勭悊--------------------------------------*/
	if (page == 7)
	{
		if (buffer[0] == 0x72)
		{
			//Serial.println("huo qu liang du");
			brightness = buffer[1];
			// p.putChar("brightness", brightness);
		}
		if (buffer[0] == 0x98)
		{Serial2.print("page 2"); //鍒拌�剧疆椤�
			for (int i = 0; i < 3;)
			{
				Serial2.write(0xff);
				i++;
			}
		}
	}
	/*-----------------------------9鍙烽〉闈�:娓╁害璁″簭鍙�----------------------------*/
	if (eeprom_write == true)
	{
		tiaoshi("?閿熸枻鎷�???");
		if (EEPROM.commit())
		{
			tiaoshi("???閿熸枻鎷�??");
			eeprom_write = false;
		}
		else
		{
			tiaoshi("閿熸枻鎷�?????");
		}
		if (buffer[0] == 0x98)

		{Serial2.print("page 2"); //鍒拌�剧疆椤�
			for (int i = 0; i < 3;)
			{
				Serial2.write(0xff);
				i++;
			}
		}
	}
}




void send_order() //锟斤拷锟斤拷锟斤拷锟筋，锟截达拷锟斤拷示锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟街�
{
	/*-----------------------------3锟斤拷页锟斤拷:锟斤拷锟斤拷锟斤拷锟斤拷---------------------------------*/
	if (page == 3)
	{

		if (set_once == true)
		{

			xianshiping_sendorder1("n0", chaolv_chongxi_maichong_dixian);
			xianshiping_sendorder1("n1", loushui_maich_biaozhun);
			xianshiping_sendorder1("n2", chxi_cishu);
			xianshiping_sendorder1("n3", leiji_biaozhun);
			set_once = false;
		}
	}
	/*----------------------------4锟斤拷页锟斤拷:锟斤拷水锟斤拷锟斤拷-----------------------------*/
	if (page == 4)
	{
		if (set_once == true)
		{
			xianshiping_sendorder1("n0", zhishuishijian_set);
			xianshiping_sendorder1("n1", zhishui_maichong_biaozhun);
			xianshiping_sendorder1("n2", chaoshi_cishu);
			xianshiping_sendorder1("n3", shuimandengdaishijian_set);

			set_once = false;
		}
	}
	/*------------------------------5锟斤拷洗膜锟斤拷锟斤拷---------------------------------*/
	if (page == 5)
	{
		if (set_once == true)
		{
			xianshiping_sendorder1("n0", jingshuiximo_shichang);
			xianshiping_sendorder1("n1", ximo_shuiliu_jiance_cishu);
			xianshiping_sendorder1("n2", moci_ximo_maichong_biaozhun);
			// xianshiping_sendorder1("n3", dcf_chxi_shichang);
			set_once = false;
		}
	}
	/*-------------------------------11锟斤拷锟斤拷锟斤拷页锟芥处锟斤拷----------------------------------*/
	if (page == 7)
	{
		if (set_once == true)
		{

			xianshiping_sendorder1("n0", brightness);
			set_once = false;
		}
	}
}
void serial_print(byte *rcv, int len)
{
	int i;
	Serial.print("jie shou:");
	Serial.println(len, DEC);
	for (i = 0; i < len; i++)
	{
		Serial.print(rcv[i], 16);
		Serial.print(" ");
	}
	Serial.println("");
}
void chaolvchongxi()
{	
	xianshiping_sendorder2("zhuangtai", "锟斤拷锟节筹拷洗锟斤拷锟斤拷"); //?????????? ???????????????
	for (int i = 0; i < chxi_cishu; i++) //????趨??
	{    
		chaolvchongxi_zongcishu = chaolvchongxi_zongcishu + 1;
		//String s = itoa(chaolvchongxi_zongcishu, str, 10);
		EEPROM.writeULong(8, chaolvchongxi_zongcishu);  //?????????
		
		if (EEPROM.commit())
		{
			tiaoshi("锟缴癸拷写锟斤拷");
		}
		else
		{
			tiaoshi("写锟斤拷失锟斤拷");
		}

		xianshiping_sendorder2("shuju", "锟斤拷锟剿筹拷洗锟斤拷锟斤拷锟斤拷" + (String)chaolvchongxi_zongcishu);
		delay(2000);
		tiaoshi("chongxi chlv");
		digitalWrite(zongjin,LOW);
		digitalWrite(chaolv, HIGH); //????????

		Serial.println(chaolvchongxi_zongcishu, DEC);

		detect(3000); //?3??
		delay(2000);
		digitalWrite(zongjin,HIGH);         

		xianshiping_sendorder2("shuju", "锟斤拷锟剿筹拷洗锟斤拷锟斤拷锟斤拷锟斤拷" + (String)count);
		
		delay(2000);
		digitalWrite(chaolv, LOW);
		//delay(8000); //??????
	}

	chaolv_chxi = false; //????????????
	/*detect(5000);		 //?5??
	if (count > 30)		 //????????????锟斤拷???????????
	{
		xianshiping_sendorder2("zhuangtai", "锟斤拷锟剿筹拷洗锟斤拷欧锟铰┧�");
		delay(1000);
	}
	else
	{
		xianshiping_sendorder2("zhuangtai", "锟斤拷锟剿筹拷洗锟斤拷欧锟斤拷锟铰┧�");
		delay(1000);
	}*/
}
void eeprom_read()
{
	if (!EEPROM.begin(EEPROM_SIZE))
	{
		Serial.println("failed to initialise EEPROM");
		delay(1000000);
	}

	EEPROM.writeULong(60, 1); //?????????????

	chaolv_chongxi_maichong_dixian = EEPROM.readByte(0); //锟斤拷锟剿筹拷洗锟斤拷锟斤拷锟斤拷锟�
	loushui_maich_biaozhun = EEPROM.readByte(2);		 //锟斤拷锟斤拷漏水锟斤拷锟斤拷锟阶�
	chxi_cishu = EEPROM.readByte(4);					 //锟斤拷锟截筹拷锟剿筹拷洗锟斤拷锟斤拷
	leiji_biaozhun = EEPROM.readByte(6);				 //锟斤拷水锟桔计多长时锟斤拷锟较匆伙拷纬锟斤拷锟�
	chaolvchongxi_zongcishu = EEPROM.readULong(8);		 //锟杰达拷锟斤拷
	// tiaoshi("?????????" + (String)chaolvchongxi_zongcishu);

	zhishuishijian_set = EEPROM.readByte(50); //锟斤拷锟斤拷锟斤拷水锟斤拷时,50
	tiaoshi("锟斤拷水锟斤拷时锟斤拷" + (String)zhishuishijian_set);
	zhishui_maichong_biaozhun = EEPROM.readByte(52); //锟斤拷水时锟斤拷小锟斤拷锟斤拷锟斤拷,52
													 // tiaoshi("???????????" + (String)zhishui_maichong_biaozhun);
	chaoshi_cishu = EEPROM.readByte(54);			 //锟斤拷水时锟斤拷锟斤拷某锟绞憋拷锟斤拷锟�
	shuimandengdaishijian_set = EEPROM.readByte(56); //锟斤拷水锟斤拷欧锟斤拷乇蘸锟斤拷水锟斤拷锟饺达拷时锟斤拷 56
	zhishuizongshijian = EEPROM.readULong(60);		 //锟斤拷水锟斤拷时锟斤拷   锟斤拷60锟斤拷址锟斤拷始锟斤拷锟斤拷锟剿�锟斤拷时锟斤拷,占4锟斤拷锟街斤拷
	tiaoshi("?????????" + (String)zhishuizongshijian);

	jingshuiximo_shichang = EEPROM.readByte(100);		//锟斤拷水洗膜时锟斤拷
	ximo_shuiliu_jiance_cishu = EEPROM.readByte(102);   //洗膜水锟斤拷锟斤拷锟斤拷锟斤拷 102
	moci_ximo_maichong_biaozhun = EEPROM.readByte(104); //洗膜末锟斤拷锟斤拷锟斤拷锟阶硷拷锟斤拷锟斤拷诖锟街碉拷锟轿�锟斤拷锟斤拷失效 104
	guanbi = EEPROM.readBool(106);
}

void print_reset_reason(RESET_REASON reason)
{
  switch ( reason)
  {
    case 1 : Serial.println ("POWERON_RESET");
	        reason1= "Vbat power on reset";    break;                    /**<1,  Vbat power on reset*/
    case 3 : Serial.println ("SW_RESET");
	        reason1= "Software reset digital core";      break;          /**<3,  Software reset digital core*/
    case 4 : Serial.println ("OWDT_RESET");
	     reason1="Legacy watch dog reset digital core";    break;         /**<4,  Legacy watch dog reset digital core*/
    case 5 : Serial.println ("DEEPSLEEP_RESET");
	         reason1="Deep Sleep reset digital core";      break;        /**<5,  Deep Sleep reset digital core*/
    case 6 : Serial.println ("SDIO_RESET"); 
	 reason1="Reset by SLC module, reset digital core";
	                                                      break;         /**<6,  Reset by SLC module, reset digital core*/
    case 7 : Serial.println ("TG0WDT_SYS_RESET"); 
	 reason1="Timer Group0 Watch dog reset digital core"; 
	                                                        break;       /**<7,  Timer Group0 Watch dog reset digital core*/
    case 8 : Serial.println ("TG1WDT_SYS_RESET"); 
	 reason1="Timer Group1 Watch dog reset digital core"; 
	                                                   break;                /**<8,  Timer Group1 Watch dog reset digital core*/
    case 9 : Serial.println ("RTCWDT_SYS_RESET"); 
	 reason1="RTC Watch dog Reset digital core";       break;                 /**<9,  RTC Watch dog Reset digital core*/
    case 10 : Serial.println ("INTRUSION_RESET");
	  reason1="Instrusion tested to reset CPU";  break;                      /**<10, Instrusion tested to reset CPU*/
    case 11 : Serial.println ("TGWDT_CPU_RESET"); 
	 reason1=" Time Group reset CPU";  break;                                  /**<11, Time Group reset CPU*/
    case 12 : Serial.println ("SW_CPU_RESET"); 
	 reason1="Software reset CPU";             break;                       /**<12, Software reset CPU*/
    case 13 : Serial.println ("RTCWDT_CPU_RESET"); 
	 reason1="RTC Watch dog Reset CPU";  break;                      	    /**<13, RTC Watch dog Reset CPU*/
    case 14 : Serial.println ("EXT_CPU_RESET"); 
	 reason1="for APP CPU reseted by PRO CPU";  break;                    /**<14, for APP CPU, reseted by PRO CPU*/
    case 15 : Serial.println ("RTCWDT_BROWN_OUT_RESET"); 
	 reason1="Reset when the vdd voltage is not stable";  break;           /**<15, Reset when the vdd voltage is not stable*/
    case 16 : Serial.println ("RTCWDT_RTC_RESET");
	  reason1="RTC Watch dog reset digital core and rtc module";  break;      /**<16, RTC Watch dog reset digital core and rtc module*/
    default : Serial.println ("NO_MEAN");reason1="NO_MEAN";
  }
}

void verbose_print_reset_reason(RESET_REASON reason)
{
  switch ( reason)
  {
    case 1  : Serial.println ("Vbat power on reset");
	    reason2="Vbat power on reset";      break; 
    case 3  : Serial.println ("Software reset digital core"); 
	reason2="Software reset digital core"; break;
    case 4  : Serial.println ("Legacy watch dog reset digital core");
	 reason2="Legacy watch dog reset digital core"; break;
    case 5  : Serial.println ("Deep Sleep reset digital core");
	 reason2="Deep Sleep reset digital core"; break;
    case 6  : Serial.println ("Reset by SLC module, reset digital core");
	 reason2="Reset by SLC module, reset digital core"; break;
    case 7  : Serial.println ("Timer Group0 Watch dog reset digital core"); 
	reason2="Timer Group0 Watch dog reset digital core"; break;
    case 8  : Serial.println ("Timer Group1 Watch dog reset digital core"); 
	reason2="Timer Group1 Watch dog reset digital core"; break;
    case 9  : Serial.println ("RTC Watch dog Reset digital core"); 
	reason2="RTC Watch dog Reset digital core"; break;
    case 10 : Serial.println ("Instrusion tested to reset CPU");
	 reason2="Instrusion tested to reset CPU"; break;
    case 11 : Serial.println ("Time Group reset CPU"); 
	reason2="Time Group reset CPU"; break;
    case 12 : Serial.println ("Software reset CPU");
	 reason2="Software reset CPU"; break;
    case 13 : Serial.println ("RTC Watch dog Reset CPU");
	 reason2="RTC Watch dog Reset CPU"; break;
    case 14 : Serial.println ("for APP CPU reseted by PRO CPU"); 
	reason2="for APP CPU, reseted by PRO CPU"; break;
    case 15 : Serial.println ("Reset when the vdd voltage is not stable");
	 reason2="Reset when the vdd voltage is not stable"; break;
    case 16 : Serial.println ("RTC Watch dog reset digital core and rtc module");
	 reason2="RTC Watch dog reset digital core and rtc module"; break;
    default : Serial.println ("NO_MEAN"); reason2="NO_MEAN"; 
  }
}
