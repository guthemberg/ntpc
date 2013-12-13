#ifndef _ANALYSERPX_TYPES_
#define _ANALYSERPX_TYPES_

#include <sys/types.h>
#include <netinet/in_systm.h>
#include <sys/socket.h>
#include <pcap.h>
#include <arpa/inet.h>
#include <net/if.h>
#include <net/if_arp.h>
#include <netinet/in.h>
#include <netinet/if_ether.h>
#include <netinet/ip.h>
#ifndef __FAVOR_BSD
#define __FAVOR_BSD
#endif 
#include <netinet/tcp.h>
#include <netinet/udp.h>


/*Internet protocol struct*/
struct ip;
/*TCP header struct*/
struct tcphdr;
/*UDP header struct*/
struct udphdr;
/*Ethernet header*/
struct ether_header;
/*Set of libpcap parameters*/
struct cap_config;
/*Flow struct*/
struct flow_t;

/*define the maximum interface name length*/
#define IF_CHAR_SIZE 5
/*default flow timeout*/
#define TIMEOUT 64


/**
  * Set of libpcap parameters
  */
typedef struct {
	
	char dev[10];					/*!< capture device */	
	char errbuf[PCAP_ERRBUF_SIZE];			/*!< error buffer */
	pcap_t *descr;					/*!< sniff handler */
	struct bpf_program fp;				/*!< compiled program */
	bpf_u_int32 maskp;				/*!< subnet mask */
	bpf_u_int32 netp;				/*!< ip */
	char filter_app[100];				/*!< well kown filter expression */
	int numOfPackets;				/*!< number of packets to capture */	
	unsigned short snap_len;			/*!< packet's length to capture */	
} cap_config;

/**
  * Flow type
  */
typedef struct {
	u_short proto; 			/*!< protocol number*/
	u_short class_proto; 		/*!< Classification protocol number*/
  	char 	src_if[IF_CHAR_SIZE],	/*!< source native interface name*/
  		dst_if[IF_CHAR_SIZE];	/*!< destination native interface name*/
  	u_short dst_port,		/*!< source port*/ 
		src_port; 		/*!< destination port*/
  	unsigned int 	n_bytes,	/*!< number of bytes*/ 
			n_frames;	/*!< number of frames*/    
  	time_t 	ini_sec,		/*!< seconds init time*/ 
		ini_mic,		/*!< microseconds init time*/ 
		end_sec,		/*!< seconds end time*/ 
		end_mic;		/*!< microseconds end time*/ 
  	struct in_addr 	src_ip,		/*!< source ip*/
			dst_ip;		/*!< destination ip*/
} flow_t;

/**
  * Adiministration Time type
  */
typedef struct {
        int interval;                                   /*!< flow timeout.Time Bin definition*/
        int hop;                                        /*!< output name file administration. time bins counter*/
} admin_t;

#endif

