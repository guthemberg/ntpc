

#define _BSD_SOURCE 1

#include "cap.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


cap_config *new_cap_config()
{
    cap_config *c = (cap_config *) malloc(sizeof(cap_config));
    snprintf(c->dev,10,"%s","");//c->dev = NULL;
    snprintf(c->errbuf,PCAP_ERRBUF_SIZE,"%s","");//c->errbuf = NULL;
    snprintf(c->filter_app,3,"%s","ip");
    //c->filter_app = "ip";
    c->netp=0;
    c->maskp=0;
    c->numOfPackets = 0;
    c->snap_len = 1518;
    c->descr=NULL;
    return c;
}



int start_capture(pcap_handler func, u_char * arg, cap_config * c,
		  int onlineCapMode, char *offLineFile)
{


    pcap_lookupnet(c->dev, &(c->netp), &(c->maskp), c->errbuf);
    if (onlineCapMode == 1) {
        /* set our capture device */
        if (strlen(c->dev) == 0) {
   	    snprintf(c->dev,10,"%s",pcap_lookupdev(c->errbuf));
        }
	/* open capture device in online mode */
	c->descr = pcap_open_live(c->dev, c->snap_len, 1, 0, c->errbuf);
	if (c->descr == NULL) {
	    fprintf(stderr, " (pcap_open_live failed)");
	    return PCAP_OPEN_LIVE_ERROR;
	}
    } else {
	/* open capture device in offline mode */
	c->descr = pcap_open_offline(offLineFile, c->errbuf);
	if (c->descr == NULL) {
	    fprintf(stderr, " (pcap_open_offline failed)");
	    return PCAP_OPEN_LIVE_ERROR;
	}
    }

    /* apply the rules */
    if (pcap_compile(c->descr, &(c->fp), c->filter_app, 0, c->netp) == -1) {
	fprintf(stderr, " (pcap_compile failed)");
	return PCAP_COMPILE_ERROR;
    }

    if (pcap_setfilter(c->descr, &(c->fp)) == -1) {
	fprintf(stderr, " (pcap_setfilter failed)");
	return -1;
    }
    pcap_loop(c->descr, c->numOfPackets, func, arg);

    return 0;

}
