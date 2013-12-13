/**
 * Provides facilities access libpcap library
 */

#ifndef _ANALYSERPX_CAP_
#define _ANALYSERPX_CAP_

#define PCAP_OPEN_LIVE_ERROR 10
#define PCAP_COMPILE_ERROR 11
#define PCAP_SETFILTER_ERROR 12
#include "analyserpxTypes.h"

/**
  * creates a new instance of {@link cap_config} structure
  * defaults values:
  * dev = NULL; (will capture from all interfaces)
  * filter_app = "ip"; (ip packets filter expression)
  * numOfPackets = 0; (no stop)
  * snap_len = 1518; 	
  */
cap_config *new_cap_config();

/** 
  * Start capture proces. All libpcap operations will be performed inside this function
  * @param func		an prototype  function that will be called for every arrived packet
  * @param arg		 	arguments passes to func
  * @param c		 	cap_config struct that contain pcap informations, like device.
  * @param onlineCapMode 	if the capture works online or throught file
  * @param offLineFile	 	if onlineCapMode is '0' then this param inform the file to read from
  */
int start_capture(pcap_handler func, u_char* arg, cap_config *c, int onlineCapMode, char *offLineFile);
void delete_cap_config(void *data);
#endif
