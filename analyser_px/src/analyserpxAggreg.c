#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <signal.h>		//ctrl+c routine
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include "analyserpxAggreg.h"
#include "cap.h"
#include "analyserpxFlow.h"
#include "analyserpxFile.h"
#include "classifier.h"

//char *baseFileName = "cap", *logFileName = "logcap", *fileName = "cap0";

double plot_bytes=0;
double plot_packets=0;
double plot_flows=0;
long tempo=1;
time_t tvSec, tvUSec;
time_t plot_tvSec=0, plot_tvUSec=0;
int onlineCapMode;
int fileAdminTimeOff;
int slotsOffline;
int flow_export=1;
int numo=0;

void limpaHashPraMIM(hash_tab * hash, time_t sec, time_t usec, char *fileName)
{
    flow_t *flow_hsh=NULL;
    init_hash_walk(hash);
    double hashTime=0, lastTime=0;
    lastTime = sec*(1e6) + usec;
    while ((flow_hsh = next_hash_walk(hash))) {
	hashTime = ( (flow_hsh->end_sec)*(1e6) ) + (flow_hsh->end_mic);
	if(flow_export) {
	    printFlowToFile(flow_hsh, fileName);
	    if ( (lastTime - hashTime) > (TIMEOUT*(1e6)) ) {
	        clear_hash_entry(hash, flow_hsh);
	    }
	} else {
	    if ( (lastTime - hashTime) > (TIMEOUT*(1e6)) ) {
	        printFlowToFile(flow_hsh, fileName);
	        clear_hash_entry(hash, flow_hsh);
	    }
	}

    }
    return;
}

void cleanHash(hash_tab * hash, time_t sec, time_t usec, char *fileName)
{
    flow_t *flow_hsh=NULL;
    init_hash_walk(hash);
    double hashTime=0, lastTime=0;
    lastTime = sec*(1e6) + usec;
    while ((flow_hsh = next_hash_walk(hash))) {
	hashTime = ( (flow_hsh->end_sec)*(1e6) ) + (flow_hsh->end_mic);
	if ( (lastTime - hashTime) > (TIMEOUT*(1e6)) ) {
	    printFlowToFile(flow_hsh, fileName);
	    clear_hash_entry(hash, flow_hsh);
	}

    }
    return;
}

int verifyTimeOut(flow_t * flow1, flow_t * flow2)
{
	double temp1 = flow1->end_sec*(1e6) + (flow1->end_mic) ;
    double temp2 = flow2->end_sec*(1e6) + (flow2->end_mic);
    double result = temp2 - temp1;
    return ( result > (TIMEOUT*(1e6)) );
}

void verifyTimeOutHash(flow_t *flow)
{

	static time_t start = 0;
	double dif;
	char *str = malloc(sizeof(char)*1024);
	extern char baseFileName[];
	extern char fileName[];
	static int offCount = 0;
	//u_short i = 0;
	time_t sec=0, usec=0;
	
	
	char *filenameCountStr = malloc(sizeof(char) * 36);
	
	


	
	if(start == 0)
	{
		start = flow->end_sec;
	}
	else
	{
		dif = difftime (flow->end_sec,start);
		if(slotsOffline) {
  		  if(dif >= (((double)fileAdminTimeOff)*slotsOffline))
		  {
			//char *buffer=malloc(sizeof(char)*17);;
			//offCount++;
			//i=getIntLen(offCount);
			//snprintf(buffer,i+1, "%u", offCount);
			//snprintf(str, strlen(baseFileName)+i+1, "%s%u", baseFileName, offCount);
			//printHash(str);
	                sec = tvSec;
                	usec = tvUSec;
			//cleanHash(test_table, sec, usec, fileName);
			snprintf(fileName,256,"%s_%u",baseFileName, offCount);
			limpaHashPraMIM(test_table, sec, usec, fileName); //esta funcao substitui a cleanHash
			offCount++;
			numo=offCount;
			start = 0;
			//free(buffer);

		  }
		} 

	}
	free(str);
	free(filenameCountStr);


}

void addFlow(flow_t * flow, const struct ip *ip, unsigned short ipLen)
{

	flow_t *flow_hsh;
	if(!onlineCapMode)
	{
		verifyTimeOutHash(flow);
	}
    
    flow_hsh = find_hash_entry(test_table, flow);
    flow_t *tmp_flow = createFlow_t(ip->ip_p,ip->ip_p, NULL, NULL, flow->dst_port, flow->src_port,
                        (unsigned int) ntohs(ip->ip_len), 1,
                        flow->ini_sec,
                        flow->end_sec,
                        flow->ini_mic,
                        flow->end_mic, ip->ip_dst, 
			ip->ip_src);
    flow_t *reverse_flow_hsh = find_hash_entry(test_table, tmp_flow);
    if (flow_hsh == NULL) {
	add_hash_entry(test_table, flow);
	u_short classifier = getID(ip, ipLen);
	if((reverse_flow_hsh == NULL)) {
		flow->class_proto = classifier;
	} else {
		u_short tmp_id=0;
		tmp_id = verID(reverse_flow_hsh->class_proto,classifier);
		reverse_flow_hsh->class_proto = tmp_id;
		flow->class_proto = tmp_id;
	}

    } else if (verifyTimeOut(flow_hsh, flow)) {
	extern char fileName[];
	printFlowToFile(flow_hsh, fileName);
	clear_hash_entry(test_table, flow_hsh);
	add_hash_entry(test_table, flow);
	u_short classifier = getID(ip, ipLen);
	if((reverse_flow_hsh == NULL)) {
		flow->class_proto = classifier;
	} else {
		u_short tmp_id=0;
		tmp_id = verID(reverse_flow_hsh->class_proto,classifier);
		reverse_flow_hsh->class_proto = tmp_id;
		flow->class_proto = tmp_id;
	}


    } else {
	u_short classifier=0;
	flow_hsh->n_bytes += flow->n_bytes;
	flow_hsh->n_frames += flow->n_frames;
	flow_hsh->end_sec = flow->ini_sec;
	flow_hsh->end_mic = flow->ini_mic;
	delete_flow(flow);
	if( (flow_hsh->class_proto == PROTO_ID_NONPAYLOAD) ) {//We can't classify a flow with NONPAYLOAD type only because his first packet
		classifier = getID(ip, ipLen);
		if((reverse_flow_hsh == NULL)) {
			flow_hsh->class_proto = classifier;
		} else {
			u_short tmp_id=0;
			tmp_id = verID(reverse_flow_hsh->class_proto,classifier);
			reverse_flow_hsh->class_proto = tmp_id;
			flow_hsh->class_proto = tmp_id;
		}
	}
	else if( (flow_hsh->class_proto < DOWN_BASE_P2P_CLASS_NUMBER) ) {
		classifier = getID(ip, ipLen);
		if( (classifier>=DOWN_BASE_P2P_CLASS_NUMBER) && (classifier<PROTO_ID_NONPAYLOAD) ) {
			if((reverse_flow_hsh == NULL)) {
				flow_hsh->class_proto = classifier;
			} else {
				u_short tmp_id=0;
				tmp_id = verID(reverse_flow_hsh->class_proto,classifier);
				reverse_flow_hsh->class_proto = tmp_id;
				flow_hsh->class_proto = tmp_id;
			}
		}
	} else if ( isSuperClass(flow_hsh->class_proto) ) {
	    	classifier = getID(ip, ipLen);
	    	if( (classifier>=DOWN_BASE_P2P_CLASS_NUMBER)&&(classifier<PROTO_ID_NONPAYLOAD)  ) {
			if((reverse_flow_hsh == NULL)) {
				flow_hsh->class_proto = classifier;
			} else {
				u_short tmp_id=0;
				tmp_id = verID(reverse_flow_hsh->class_proto,classifier);
				reverse_flow_hsh->class_proto = tmp_id;
				flow_hsh->class_proto = tmp_id;
			}
	     	}
	} else if ( (flow_hsh->class_proto>UP_BASE_P2P_CLASS_NUMBER)&&(flow_hsh->class_proto<PROTO_ID_NONPAYLOAD) ){
		classifier = getID(ip, ipLen);
		if( ((classifier<=UP_BASE_P2P_CLASS_NUMBER) && (classifier>=DOWN_BASE_P2P_CLASS_NUMBER)) ) {
			if((reverse_flow_hsh == NULL)) {
				flow_hsh->class_proto = classifier;
			} else {
				reverse_flow_hsh->class_proto = classifier;
				flow_hsh->class_proto = classifier;
			}
		}
	}
    }
    delete_flow(tmp_flow);
}

/*
 * dissect packet
 */
void
mount_flow(u_char * args, const struct pcap_pkthdr *header,
	   const u_char * packet)
{
    char buffer[150];

    //to log messages
    extern char logFileName[];
    flow_t *flow;		//flow structure        

    /* define pointers to packet headers */
    const struct ether_header *ethernet;	/* ethernet header */
    const struct ip *ip;	/* IP header */


    /* ethernet headers are always exactly (time_t)(header->ts.tv_sec)14 bytes */
    int size_ethernet = ETHER_HDR_LEN;
    int size_ip;
    u_short ipLen;
    

    /* define ethernet header */
    ethernet = (struct ether_header *) (packet);

    /* define/compute ip header offset */
    ip = (struct ip *) (packet + size_ethernet);

    size_ip = ip->ip_hl * 4;
    if (size_ip < 20) {
	return;
    }

    u_int16_t src_port, dst_port;

    /* determine protocol */
    switch (ip->ip_p) {
    case IPPROTO_TCP:
	src_port =
	    ((struct tcphdr *) (packet + size_ethernet +
				size_ip))->th_sport;
	dst_port =
	    ((struct tcphdr *) (packet + size_ethernet +
				size_ip))->th_dport;
	break;
    case IPPROTO_UDP:
	src_port =
	    ((struct udphdr *) (packet + size_ethernet +
				size_ip))->uh_sport;
	dst_port =
	    ((struct udphdr *) (packet + size_ethernet +
				size_ip))->uh_dport;
	break;
    case IPPROTO_ICMP:
	    src_port = htons(0);
	    dst_port = htons(0);
	    break;
    default:
	src_port = htons(0);
	dst_port = htons(0);
	break;
    }
    flow = createFlow_t(ip->ip_p, ip->ip_p, NULL, NULL, src_port, dst_port,
			(unsigned int) ntohs(ip->ip_len), 1,
			(time_t) (header->ts.tv_sec),
			(time_t) (header->ts.tv_sec),
			(time_t) (header->ts.tv_usec),
			(time_t) (header->ts.tv_usec), ip->ip_src,
			ip->ip_dst);

    tvSec = (time_t) (header->ts.tv_sec);
    tvUSec = (time_t) (header->ts.tv_usec);
    // impressao de bytes
    //begin
    if(plot_tvSec==0) {
      plot_tvSec=tvSec;
      plot_tvUSec=tvUSec;
    }
    unsigned int bytes_locais=(unsigned int) ntohs(ip->ip_len);
    plot_bytes+=(double)  bytes_locais;
    plot_packets++;
    if( ((( ((tvSec-plot_tvSec)*1000000)+(tvUSec-plot_tvUSec) )/1000000)/1) >tempo  ) {
//      fprintf(stdout,"%.0f\n",plot_bytes);
      snprintf(buffer, 150,"##,%.0f,%ld,%.0f",plot_bytes, num_hash_entries(test_table),plot_packets);
      writeStringToLogFile(logFileName, buffer, NULL);
      plot_bytes=0;
      plot_packets=0;
      tempo++;
    }
    //end
    ipLen = *(unsigned short *) args;
    ipLen -= ETHER_HDR_LEN;
    if((unsigned int)(ntohs(ip->ip_len)) <= ipLen ) {
      addFlow(flow, ip, (unsigned int) ntohs(ip->ip_len));
    } else {
      addFlow(flow, ip, ipLen);
    }

    return;
}

//void printHash(char *fileName)
void printHash()
{
    flow_t *flow_hsh;
    init_hash_walk(test_table);
    extern char baseFileName[];
    extern char fileName[];
    snprintf(fileName,256,"%s_%u",baseFileName, numo);
    while ((flow_hsh = next_hash_walk(test_table))) {
//	fprintf(stdout,"Estamos aqui 1\n");
	printFlowToFile(flow_hsh, fileName);
    }
    clear_hash_table(test_table);

}

void task_ctrl_C(int i)
{
    //printHash("stdout");
    printf("Interrupt received.\nProgram will exit now!\n");
    exit(0);
}

void *verifyHashTimeOut(void *par)
{
	int filenameCount = 0; int flag=1;
	int fileAdminTime = ((admin_t *) par)->interval;
	int fileExpTime = ((admin_t *) par)->hop;
	time_t init = 0, final = 0, sec, usec;
	struct tm *clock = NULL;
	extern int analyserpxError;
	extern char logFileName[];
	extern char baseFileName[];
	extern char fileName[];
	extern int tFlag;
	int interCounter=0;

	char *filenameCountStr = malloc(sizeof(char) * 36);
	char *data = (char *) (malloc(sizeof(char)*7));

	while ((analyserpxError == 0)&&tFlag) {
		sleep(fileAdminTime - (final - init));
		sec = tvSec;
		usec = tvUSec;
		time(&init);
		clock = (struct tm *)localtime(&(init));
		if((interCounter>=fileExpTime)&&(fileExpTime>0)){
			filenameCount++;
              		getDate(&init,data,6) ;
                  	snprintf(filenameCountStr,36,"%s_%u",data,filenameCount);
                        snprintf(fileName,256,"%s%s",baseFileName, filenameCountStr);
			interCounter=0;
		}
		if( ((clock->tm_hour) == 0)&&((clock->tm_min)<((int)((fileAdminTime*2)/60))) ) {
			if(flag) {
				filenameCount=0;
				getDate(&init,data,6) ;
				snprintf(filenameCountStr,36,"%s_%u",data,filenameCount);
				snprintf(fileName,256,"%s%s",baseFileName, filenameCountStr);
			}
			flag=0;
		} else {
			flag=1;
		}
		limpaHashPraMIM(test_table, sec, usec, fileName);
		//cleanHash(test_table, sec, usec, fileName);
		interCounter++;
		time(&final);
	}

	if (analyserpxError) {
		char buffer[50];
		snprintf(buffer, 50,"ERROR CLEANING HASH. ERROR CODE: %u", analyserpxError);
		writeStringToLogFile(logFileName, buffer, NULL);
	}
	free(filenameCountStr);
	free(data);
	//pthread_exit (0);
	return (void *) NULL;
} 

/*void *verifyHashTimeOut(void *par)
{
    int filenameCount = 0;
    int fileAdminTime = *((int *) par);
    time_t init = 0, final = 0, sec, usec;
    extern int analyserpxError;
    extern char logFileName[];
    extern char *baseFileName;
    extern char *fileName;

    char *filenameCountStr = malloc(sizeof(char) * 16);

    while (analyserpxError == 0) {
	sleep(fileAdminTime - (final - init));
	sec = tvSec;
	usec = tvUSec;
	time(&init);
	sprintf(filenameCountStr, "%d", filenameCount++);
	strncpy(fileName, baseFileName,strlen(baseFileName));
	strncat(fileName, filenameCountStr,strlen(filenameCountStr));
	cleanHash(test_table, sec, usec, fileName);
	time(&final);
    }

    if (analyserpxError) {
	char buffer[50];
	sprintf(buffer, "ERROR CLEANING HASH. ERROR CODE: %d", analyserpxError);
	writeStringToLogFile(logFileName, buffer, NULL);
    }

    return (void *) NULL;
}*/
int analyserpxStart(cap_config * conf, int fileAdminTime, int fileExpTime, char *offLineFile, int flow_exp)
{
    extern int analyserpxError;
    pthread_t hashTimeOut;
    extern char baseFileName[];
    extern char fileName[];
    extern int tFlag;
    admin_t *control=(admin_t *)malloc(sizeof(admin_t));
    control->interval=fileAdminTime;
    control->hop=fileExpTime;
    //void *ret;
   
    flow_export=flow_exp; 
    /* interrupt rotine to Ctrl-C */
    signal(SIGINT, task_ctrl_C);

    test_table = init_hash_table("ANALYSERPX_CAP_TABLE", compare_flow, flow_key,
				 delete_flow, HASH_SIZE);

    //pthread_create(&hashTimeOut, NULL, verifyHashTimeOut, &fileAdminTime);

    if (offLineFile == NULL) {
	    onlineCapMode = 1;
	    pthread_create(&hashTimeOut, NULL, verifyHashTimeOut, control);
    }
    else {
	    snprintf(fileName,256,"%s_0",baseFileName);
	    onlineCapMode = 0;	
	    fileAdminTimeOff = fileAdminTime;
	    slotsOffline=control->hop;
    }
    analyserpxError =
	start_capture(mount_flow, (u_char *) & (conf->snap_len), conf,
		      onlineCapMode, offLineFile);
    tFlag=0;
    printHash(fileName);
    if (offLineFile == NULL) {
	//(void)pthread_join(hashTimeOut,&ret);
	pthread_exit(verifyHashTimeOut);
    }
    //printHash(fileName);
    free(control);
    return analyserpxError;
}
