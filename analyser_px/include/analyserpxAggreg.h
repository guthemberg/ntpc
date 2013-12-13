#ifndef _ANALYSERPXAGGREG_H_
#define _ANALYSERPXAGGREG_H_

#define HASH_SIZE 1000
#define TEST_AMOUNT 100
#include "hashtab.h"
#include "analyserpxTypes.h"

/**
  * Pointer to Hash structure that will be used to save flows
  */
hash_tab *test_table;


/**
  * Clear the hash table based on parameter's condition.
  * The last time for each flow is verified, so the expered flows 
  * are removed from teh hast table ane saved into {@link FILE}
  *
  * @param *hash	a pointer to a hash structure that will be cleaned
  * @param sec		indicate the timestamp seconds of the last packet arrived
  * @param usec		indicate the timestamp miliseconds of the last packet arrived
  * @param *fileName	name/location to save the expired flows
  */ 
void cleanHash(hash_tab *hash, time_t sec, time_t usec, char *fileName);

/**
  * Funcao especifica para o RProf
  */
void limpaHashPraMIM(hash_tab *hash, time_t sec, time_t usec, char *fileName);


/**
  * Verify if a frame belongs to an active flow
  * based on {@link TIMEOUT}.
  * The flow2 parameter is a {@link flow_t}. In this case, it isn't necessary to create a new 
  * structure like frame, only to include a frame in a {@link flow_t} structure.  
  *
  * @param flow1	the old flow
  * @param flow2	the new frame that will be or not be a new flow
  */
int verifyTimeOut(flow_t *flow1, flow_t *flow2);


/**
  * Add a flow to the hash table, it also keep 
  * a {@link ip} to classify the flow based on ip payload.
  *
  * @param flow	flow to be added
  * @param *ip		pointer to the {@link ip}
  * @param ipLen	ip payload size
  */ 
void addFlow(flow_t *flow, const struct ip *ip, unsigned short ipLen);


/**
  * Function called every time when a packet arrives at libpcap
  * 
  * @param *args	argument passed by pcap_loop function
  * @param *header	pointer to a {@link pcap_pkthdr}
  * @param *header 	header of a dumped packet in the file
  * @param *packet	an arrived packet
  */
void
mount_flow(unsigned char *args, const struct pcap_pkthdr *header, const u_char *packet);

/**
  * Save to file all the remained flow tha
  * still into hash
  */
//void printHash(char *fileName);
void printHash();

/**
  * Cath the interrupt SIGINT
  * caused by pressing the "CRT-C" buttons  and 
  * save to file all the remained flow that 
  * still into hash
  * 
  * @param i		interrupt signal
  */ 
void task_ctrl_C(int i);

/**
  * Start all capturing, aggregating, and classifier process.
  *
  * @param *conf		pointer to {@link cap_config} with all libcap needed parameter
  * @param fileAdminTime  	the cicle time to save flows to file
  * @param fileExpTime  	interval counter to output file modification
  * @param *offLineFile		name of file to read the packets 
  */
int analyserpxStart(cap_config *conf, int fileAdminTime, int fileExpTime, char *offLineFile, int flow_exp);


#endif
