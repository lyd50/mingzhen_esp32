#include <rom/rtc.h>

void closeall() ;/**/

void chaolvchongxi();

void check_wifi();

void count_function();

void detect(unsigned long yongshi); 

void decide_chaolv_chxi(unsigned long long1);

void edp_command_parse();

void edp_first_connect();

void edp_packet_send();

void edp_upload_int(String data_stream_id, int datapoint) ;

void edp_reponse(int response_type);

void edp_upload_string(String data_stream_id, String datapoint);

void edp_heartbeat();

void eeprom_read();

void print_reset_reason(RESET_REASON reason);//启动原因

void rcvDebug(unsigned char *rcv, int len);

void send_order() ;

void Serial2_command_parse();

void serial_print(byte *rcv, int len);

void tiaoshi(String pingmuxianshi);

void verbose_print_reset_reason(RESET_REASON reason);

void wifi_connecte(String ssid, String password);

void xianshiping_sendorder1(String kongjian, int value) ;

void xianshiping_sendorder2(String kongjian, String text) ;


