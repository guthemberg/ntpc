#ifndef _ANALYSERPX_FLOW_
#define _ANALYSERPX_FLOW_

#define	FORMAT_FLOW_SECONDS 		1
#define	FORMAT_FLOW_DATE_DURATION	2
#define	FORMAT_FLOW_DEFAULT		FORMAT_FLOW_SECONDS

#define	FORMAT_PROTO_ID		1
#define	FORMAT_PROTO_NAME	2
#define	FORMAT_PROTO_DEFAULT	FORMAT_PROTO_ID

/**
  * Compare two flows and return if they are the same base on the flow key
  *
  * @param data1	flow_t one
  * @param data2 	flow_t two
  */
int compare_flow(const void * data1, const void * data2);

/**
  * Determine the flow's key
  *
  * @param data	flow to extract the key
  */
unsigned long flow_key(const void * data);

/**
  * Release the memory allocated for a flow
  *
  * @param data	flow to be released
  */
void delete_flow(void * data);

/** 
  * Create a new flow
  *
  * @param proto		protocol
  * @param *src_if		source interface
  * @param *dst_if		destination interface
  * @param src_port		source port
  * @param dst_port		destination port
  * @param n_bytes		number of bytes
  * @param n_frames		number of frames
  * @param ini_sec		start time in seconds
  * @param end_sec		end time in seconds
  * @param ini_mic		start time in milliseconds (DENIO: MICROSECONDS???)
  * @param end_mic		end time in milliseconds (DENIO: MICROSECONDS???)
  * @param ip_src		source ip
  * @param ip_dst		destination ip
  */
flow_t *createFlow_t( unsigned char proto, unsigned char class_proto, char *src_if, char *dst_if, 
	u_short src_port, u_short dst_port, unsigned int n_bytes, 
	unsigned int n_frames, time_t ini_sec, time_t end_sec, time_t ini_mic, 
	time_t end_mic, struct in_addr ip_src, struct in_addr ip_dst);	 
 
/**
  * Adjust the protocol number to print it on the right format, put 0-3 zeros at the front of the protocol number
  */
void adjustProtocol(char* str_proto, char* final);

/**
  * Convert a flow to string
  *
  * @param flow	source flow
  * @param str		equivalent flow string
  */
void flowToString(char format, char proto_format, flow_t *flow, char* str);

/**
  * Store a flow to a binary file
  *
  * @param flow	flow to be stored
  * @param file	destination file
  */
int printFlowToFile(flow_t *flow, const char *file);

/**
  * Write the string flow header 
  *
  * @param str		pointer to receive the flow text header structure
  */
void printFlowStruct(char format, char* str);

/**
  * Read a flow from a file. The ind parameter concerns the flow to be read, if the first (0),
  * the second (1) or any other. The function return NULL when there is any flow or if the ind
  * is bigger then the flow's number
  *
  * @param flow	destination structure for a new flow
  * @param file	source file with stored flows 
  * @param ind		determine the flow to be read in the file (memory deslocation in the file)
  *
  * @return *flow_t	pointer to the read flow 
  */
flow_t *readFlowFromFile(flow_t *flow, const char *file, int ind);

/**
  * Returns the procol name, given the protocol ID
  *
  * @param proto_id The protocol ID, according to the classification process
  * @return *char	pointer to protocol name 
  */
char * get_protocolName( unsigned char proto_id );

int getDate(time_t *tloc, char *str, int str_len);
u_short getIntLen(unsigned long num);
u_short getDouLen(double num);
#endif
