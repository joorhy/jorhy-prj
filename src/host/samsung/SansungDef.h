#ifndef __SANSUNGDEF_H_
#define __SANSUNGDEF_H_

struct SNP_Packet_info
{
    char start_code[4];
    unsigned char ex_channel;
    unsigned char pkt_version;
    unsigned short pkt_size;
    unsigned char control;
    unsigned char payload;
    unsigned char seq;
    unsigned char ctrlId;
};

struct SNP_Continue_header
{
    char ch;
    char cs;
};

struct SNP_Login_req_data
{
    unsigned char ctrlId;
    unsigned char type;
    char pass_word[8];
    char user_name[8];
};

struct SNP_Login_req
{
    SNP_Packet_info packet_header;
    SNP_Continue_header continue_header;
    SNP_Login_req_data continue_data;
};

struct SNP_Login_res_data
{
    unsigned char error;
    unsigned char result;
    unsigned char ctrlId;
    unsigned char rd;
};

struct SNP_Login_res
{
    SNP_Packet_info packet_header;
    SNP_Continue_header continue_header;
    SNP_Login_res_data continue_data;
};

struct SNP_Server_info
{
    SNP_Packet_info packet_header;
    unsigned short model_code;
    unsigned char fw_minor;
    unsigned char fw_major;
    unsigned char mac_addr[6];
    unsigned char trans_type;
    unsigned char video_mux;
    unsigned char sensor_num;
    unsigned char relay_num;
    unsigned char max_video_num;
    unsigned char max_audio_num;
    unsigned short ex_ptz_ch;
    unsigned short active_audio_ch;
    unsigned char tz_min;
    unsigned char tz_hour;
    unsigned int server_cru_time;
    unsigned char unicode;
    unsigned char pal;
    unsigned short ch_name[16][8];
    unsigned char day_light;
    unsigned char unknow[74];
};

struct SNP_condition_req
{
    SNP_Packet_info packet_header;
    SNP_Continue_header continue_header;
    char data[8];
};

struct SNP_condition_rep
{
    SNP_Packet_info packet_header;
    SNP_Continue_header continue_header;
    char data[2];
};

struct SNP_stop_req
{
    SNP_Packet_info packet_header;
    SNP_Continue_header continue_header;
    char data[8];
};

struct SNP_Ptz_cmd
{
    char channel;
    char rd;
    char part[5];
    char part2[5];
};

struct SNP_ptz_req
{
    SNP_Packet_info packet_header;
    SNP_Continue_header continue_header;
    SNP_Ptz_cmd ptz_cmd;
};

struct SNP_ptz_rep
{
    SNP_Packet_info packet_header;
    SNP_Continue_header continue_header;
    char data[4];
};

struct SNP_Encode_type
{
    char channel;
    char video;
    char type;
    char res;
    char frame;
    char bit;
    char atc;
    char data;
};

struct SNP_enc_type_req
{
    SNP_Packet_info packet_header;
    SNP_Continue_header continue_header;
    SNP_Encode_type enc_type;
};

#endif // __SANSUNGDEF_H_
