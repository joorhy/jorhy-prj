#ifndef __JO_PCAP_H_
#define __JO_PCAP_H_

#include<stdio.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<pcap.h>
#include<netinet/in.h>
#include<netinet/tcp.h>
#include<string.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include <ctype.h>

#define ETHER_ADDR_LEN 6
///*以太网头*/
struct sniff_ethernet
{
    u_char ether_dhost[ETHER_ADDR_LEN];
    u_char ether_shost[ETHER_ADDR_LEN];
    u_short ether_type;
};

///*IP头*/
struct sniff_ip
{
    u_char ip_vhl;
    u_char ip_tos;
    u_short ip_len;
    u_short ip_id;
    u_short ip_off;
    #define IP_RF 0x8000
    #define IP_DF 0x4000
    #define IP_MF 0x2000
    #define IP_OFFMASK 0x1fff
    u_char ip_ttl;
    u_char ip_p;
    u_short ip_sum;
    struct in_addr ip_src,ip_dst;
};

///*TCP头*/
typedef u_int tcp_seq;
struct sniff_tcp
{
    u_short th_sport;
    u_short th_dport;
    tcp_seq th_seq;
    tcp_seq th_ack;

    u_char th_offx2;
    u_char th_flags;

    u_short th_win;
    u_short th_sum;
    u_short th_urp;
};

///*UDP报头*/
struct sniff_udp
{
    u_short udp_sport;
    u_short udp_dport;
    u_short udp_len;
    u_short udp_sum;
};

///*DNS报头*/
struct sniff_dns
{
    u_short dns_id;
    u_short dns_flag;
    u_short dns_ques;
    u_short dns_ans;
    u_short dns_auth;

    u_short dns_add;
    u_int8_t *dsn_data;
};

#endif //__JO_PCAP_H_
