#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <netinet/in.h>
#include "analyserpxTypes.h"
#include "analyserpxFile.h"
#include "analyserpxFlow.h"
#include "classifier.h"

int compare_flow(const void *data1, const void *data2)
{
    const flow_t *check1 = (const flow_t *) data1;
    const flow_t *check2 = (const flow_t *) data2;
    return (check1->src_ip.s_addr != check2->src_ip.s_addr
	    || check1->dst_ip.s_addr != check2->dst_ip.s_addr
	    || check1->dst_port != check2->dst_port
	    || check1->src_port != check2->src_port
	    || check1->proto != check2->proto);
}

unsigned long flow_key(const void *data)
{
    const flow_t *what = (const flow_t *) data;

    return (unsigned) what->src_ip.s_addr * 59 + what->dst_ip.s_addr +
	what->proto + ((unsigned) what->dst_port << 16) + what->src_port;
}

void delete_flow(void *data)
{
    if (!data)
	return;
    free(data);
}

flow_t *createFlow_t(unsigned char proto, unsigned char class_proto, char *src_if, char *dst_if,
		     u_short src_port, u_short dst_port,
		     unsigned int n_bytes, unsigned int n_frames,
		     time_t ini_sec, time_t end_sec, time_t ini_mic,
		     time_t end_mic, struct in_addr src_ip,
		     struct in_addr dst_ip)
{
    flow_t *flow = (flow_t *) malloc(sizeof(flow_t));
    if (flow == NULL)
	return NULL;
    flow->proto = proto;
    flow->class_proto = class_proto;
    if (src_if != NULL) {
	strncpy(flow->src_if, src_if,strlen(src_if));
    } else
	flow->src_if[0] = '\0';

    if (dst_if != NULL) {
	strncpy(flow->dst_if, dst_if, IF_CHAR_SIZE);
    } else
	flow->dst_if[0] = '\0';

    flow->src_port = src_port;
    flow->dst_port = dst_port;
    flow->n_bytes = n_bytes;
    flow->n_frames = n_frames;
    flow->ini_sec = ini_sec;
    flow->end_sec = end_sec;
    flow->ini_mic = ini_mic;
    flow->end_mic = end_mic;
    flow->src_ip = src_ip;
    flow->dst_ip = dst_ip;
    return flow;

}

int printFlowToFile(flow_t * flow, const char *file)
{
    int len1=strlen("stdout");
    int len2=strlen(file);
    if(!(memcmp("stdout",file,len1>len2?len1:len2)) ) {
	char *buffer = malloc(sizeof(char)*1024);
	char proto_format = FORMAT_PROTO_DEFAULT;
	char flow_format = FORMAT_FLOW_DEFAULT;
	snprintf(buffer,2,"%s","");
	flowToString(flow_format, proto_format, flow, buffer);
	fprintf(stdout,"%s\n",buffer);
	free(buffer);
    } else {
    	FILE *printFlow = openFile(file, "a+b", NULL, NULL);
    	if (printFlow == NULL) {
		//ERROR OPENING FILE
		return 1;
    	}
    	if (fwrite(flow, sizeof(flow_t), 1, printFlow) != 1) {
		//ERROR
		closeFile(printFlow);
		return 1;
    	}
    	closeFile(printFlow);
    	return 0;
    }
    return 0;
}

flow_t *readFlowFromFile(flow_t * flow, const char *file, int ind)
{
	FILE *readFlow = openFile(file, "rb", NULL, NULL);
    	fseek(readFlow, ind * sizeof(flow_t), SEEK_SET);
    	if (fread(flow, sizeof(flow_t), 1, readFlow) != 1) {
		//ERROR
		closeFile(readFlow);
		return NULL;
    	}
    	closeFile(readFlow);
    	return flow;
}

void adjustProtocol(char* str_proto, char* final) {
	if(strcmp(str_proto, "6") == 0 || strcmp(str_proto, "17") == 0 || strcmp(str_proto, "1") == 0
		  || strcmp(str_proto, "19") == 0) {
		strncpy(final, "0000",4);
	} else {
		if(strlen(str_proto) == 1) {
			strncat(final, "000",3);
		} else if (strlen(str_proto) == 2){
			strncat(final, "00",2);
		} else if(strlen(str_proto) == 3){
			strncat(final, "0",1);
		}
		strncat(final, str_proto,strlen(str_proto));
	}
}

void flowToString(char format, char proto_format, flow_t * flow, char *str){
    static char temp[256];
    static char srcIp[16]; //added because a possible error in the function sprintf 
    static char dstIp[16]; //added because a possible error in the function sprintf
    static char str_proto[50];
    char final[15] = "";
	
	strncpy(srcIp, inet_ntoa(flow->src_ip),16);
    strncpy(dstIp, inet_ntoa(flow->dst_ip),16);
    
    if( proto_format == FORMAT_PROTO_NAME ){
	strncpy( str_proto, get_protocolName( flow->class_proto ), 50 );
    } else {
	snprintf( str_proto,50, "%u", flow->class_proto );
	adjustProtocol(str_proto, final);
    }
    

    if( format == FORMAT_FLOW_DATE_DURATION ){
	static unsigned long inisec, inimil, endsec, endmil, flowduration;
//	static struct tm tm;
	static char str_start[80];

	inisec = (long) (flow->ini_sec); 
	inimil = (long) (flow->ini_mic) / 1000; // interpreted as microseconds
	endsec = (long) (flow->end_sec); 
	endmil = (long) (flow->end_mic) / 1000; // interpreted as microseconds

	// calculates flow duration
	snprintf( str_start,80, "%ld", inisec*1000000+inimil );
	//printf("inisec=%ld, inimil=%d, endsec=%ld, endmil=%d\n", inisec, inimil,endsec, endmil );
	//strptime( str_start, "%s", &tm);	
	//strftime( str_start, sizeof(str_start), "%Y-%m-%d_%H:%M:%S", &tm);
	if( inimil > endmil ) {
		endsec--;
		endmil += 1000;
	}
	//printf("inisec=%ld, inimil=%d, endsec=%ld, endmil=%d\n", inisec, inimil,endsec, endmil );
	flowduration = (endsec-inisec)*1000 + (endmil-inimil);

/*	sprintf(temp, "start=[%s]inimil=[:%d] duracao=[%ld] ifsrc=[%s] ifdst=[%s] srcip=[%s] dstip=[%s] srcport=[%d] dstport=[%d] bytes=[%.0d] packets[%.0d] proto=[%s]", 
		str_start, 
		inimil,
		flowduration,
		flow->src_if, 
		flow->dst_if, 
		inet_ntoa(flow->src_ip), 
		inet_ntoa(flow->dst_ip), 
		ntohs(flow->src_port), 
		ntohs(flow->dst_port), 
		flow->n_bytes, 
		flow->n_frames, 
		str_proto );*/
	snprintf(temp, 256,"%s:%03ldu %8ld %s %d %s %d %.0d %.0d %s %d", 
		str_start, 
		inimil,
		flowduration,
		/*flow->src_if, 
		flow->dst_if, */
		srcIp,  
		ntohs(flow->src_port), 
		dstIp,
		ntohs(flow->dst_port), 
		flow->n_bytes, 
		flow->n_frames, 
		final,
		flow->proto);
    } else {
    	
	// default format FORMAT_FLOW_SECONDS
	snprintf(temp,256, "%.0f,%.0f,%.0f,%.0f,%s,%d,%s,%d,%.0d,%.0d,%s,%d", 
		(double) (flow->ini_sec), 
		(double) (flow->ini_mic), 
		(double) (flow->end_sec), 
		(double) (flow->end_mic), 
		/*(char *) (flow->src_if), 
		(char *) flow->dst_if, */
		srcIp, 
		(int) ntohs(flow->src_port), 
		dstIp, 
		(int) ntohs(flow->dst_port), 
		(int) flow->n_bytes, 
		(int) flow->n_frames, 
		final,
	        flow->proto);
    }
    *str = '\0';
    strncat( str, temp,strlen(temp) );
}

void printFlowStruct(char format, char *str)
{
    if( format == FORMAT_FLOW_DATE_DURATION ){
	    strncpy( str, "ini_flow duration src_ip src_port dst_ip dst_port n_bytes n_frames app transp_prot",256);
    } else {
	// default format FORMAT_FLOW_SECONDS
	    strncpy( str, "ini_sec ini_mic end_sec end_mic src_ip src_port dst_ip dst_port n_bytes n_frames app transp_prot",256);
    }
}

char * get_protocolName( unsigned char proto_id ){
	switch ( proto_id ) {
		case PROTO_ID_TCP:		return( PROTO_NAME_TCP );
		case PROTO_ID_EDONKEY:		return( PROTO_NAME_EDONKEY );
		case PROTO_ID_BITTORRENT:	return( PROTO_NAME_BITTORRENT );
		case PROTO_ID_KAZAA:		return( PROTO_NAME_KAZAA );
		case PROTO_ID_GNU:		return( PROTO_NAME_GNU );
		case PROTO_ID_SOULSEEK:		return( PROTO_NAME_SOULSEEK );
		case PROTO_ID_ARES:		return( PROTO_NAME_ARES );
		case PROTO_ID_WINMX:		return( PROTO_NAME_WINMX );
		case PROTO_ID_MUTE:		return( PROTO_NAME_MUTE );
		case PROTO_ID_XDCC:		return( PROTO_NAME_XDCC );
		case PROTO_ID_DIRECTCONNECT:	return( PROTO_NAME_DIRECTCONNECT );
		case PROTO_ID_APPLEJUICE:	return( PROTO_NAME_APPLEJUICE );
		case PROTO_ID_WASTE:		return( PROTO_NAME_WASTE );
		case PROTO_ID_UDP:		return( PROTO_NAME_UDP );
		/*case PROTO_ID_EDKUDP:		return( PROTO_NAME_EDKUDP );
		case PROTO_ID_BITTORRENTUDP:	return( PROTO_NAME_BITTORRENTUDP );
		case PROTO_ID_KAZAAUDP:		return( PROTO_NAME_KAZAAUDP );
		case PROTO_ID_GNUUDP:		return( PROTO_NAME_GNUUDP );*/
		case PROTO_ID_ICMP:		return( PROTO_NAME_ICMP );
		case PROTO_ID_OTHER:		return( PROTO_NAME_OTHER );
		//NEW
		case PROTO_ID_HTTP:		return( PROTO_NAME_HTTP );
		case PROTO_ID_UNKNOWN:		return( PROTO_NAME_UNKNOWN );
		case PROTO_ID_NONPAYLOAD:	return( PROTO_NAME_NONPAYLOAD );
		case PROTO_ID_AIM:		return( PROTO_NAME_AIM );
		case PROTO_ID_IRC:		return( PROTO_NAME_IRC );
		case PROTO_ID_MSN:		return( PROTO_NAME_MSN );
		case PROTO_ID_YAHOOMESS:	return( PROTO_NAME_YAHOOMESS );
		case PROTO_ID_HLCS:		return( PROTO_NAME_HLCS );
		case PROTO_ID_HL2DEATH:		return( PROTO_NAME_HL2DEATH );
		case PROTO_ID_HL2CS:		return( PROTO_NAME_HL2CS );
		case PROTO_ID_HLDEATH:		return( PROTO_NAME_HLDEATH );
		case PROTO_ID_DNS:		return( PROTO_NAME_DNS );
		case PROTO_ID_RTSP:		return( PROTO_NAME_RTSP );
		case PROTO_ID_HTTPQUICKTIME:	return( PROTO_NAME_HTTPQUICKTIME );
		case PROTO_ID_HTTPVIDEO:	return( PROTO_NAME_HTTPVIDEO );
		case PROTO_ID_HTTPAUDIO:	return( PROTO_NAME_HTTPAUDIO );
		case PROTO_ID_POP3:		return( PROTO_NAME_POP3 );
		case PROTO_ID_SMTP:		return( PROTO_NAME_SMTP );
		case PROTO_ID_FTP:		return( PROTO_NAME_FTP );
		case PROTO_ID_SKYPETOSKYPE:	return( PROTO_NAME_SKYPETOSKYPE );
		case PROTO_ID_SKYPEOUT: 	return( PROTO_NAME_SKYPEOUT );
		case PROTO_ID_SSL:		return( PROTO_NAME_SSL );
		case PROTO_ID_VALIDCERTSSL:	return( PROTO_NAME_VALIDCERTSSL );
		case PROTO_ID_SSH:	 	return( PROTO_NAME_SSH );
		case PROTO_ID_NETBIOS:	 	return( PROTO_NAME_NETBIOS );
		case PROTO_ID_NBNS:	 	return( PROTO_NAME_NBNS );
		case PROTO_ID_NBDS:	 	return( PROTO_NAME_NBDS );
		case PROTO_ID_BOOTSTRAP: 	return( PROTO_NAME_BOOTSTRAP );
		//end
		default: return( PROTO_NAME_OTHER );
	}
}

int getDate(time_t *tloc, char *str, int str_len) {
	if(str_len<6) return 0;
	struct tm *clock = (struct tm *)localtime((tloc));
	if((clock->tm_mon+1)>9) {
        	if((clock->tm_mday)>9)
                	snprintf(str,7, "%d%d0%d", clock->tm_mday,clock->tm_mon+1,(clock->tm_year)-100);
                else
                	snprintf(str,7, "0%d%d0%d", clock->tm_mday,clock->tm_mon+1,(clock->tm_year)-100);
	} else {
        	if((clock->tm_mday)>9)
                	snprintf(str,7, "%d0%d0%d", clock->tm_mday,clock->tm_mon+1,(clock->tm_year)-100);
                else
                	snprintf(str,7, "0%d0%d0%d", clock->tm_mday,clock->tm_mon+1,(clock->tm_year)-100);
	}
	return 1;
}
u_short getIntLen(unsigned long num) {
	unsigned long number=10;
	unsigned long bigest=1000000000;
	u_short i = 1;

	while(number<=num) {
		i++;
		number=number*10;
		if(number>=bigest) return i;
	}
	return i;
}
u_short getDouLen(double num) {
	unsigned long number=10;
	unsigned long bigest=1000000000;
	u_short i = 1;

	while(number<=num) {
		i++;
		number=number*10;
		if(number>=bigest) return i;
	}
	return i;
}
