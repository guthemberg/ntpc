#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "cap.h"
#include "version.h"
#include "analyserpxAggreg.h"
#include "expressions.h"
#include "analyserpxFlow.h"

char fileName[256] = "cap0";
char baseFileName[100] = "cap";
char logFileName[100] = "logcap";
int tFlag = 1;
int flow_exp = 1;

int analyserpxError = 0;
int STR_MAX_LEN = 1474;

void printHelp( char *progname ){

fprintf( stderr, "%s version " ANALYSERPXCAP_VERSION "\n", progname);
fprintf( stderr, "%s monitors, collects and store traffic that is \n\
visible in a interface. The packets are classified and aggregated \n\
into flows and stored on a binary file. The binay file can be read by \n\
the analyserpx_read program and the flows printed on screen in text format. \n\
\n\
Usage:	%s [-h] [-c count] [-i interface] [ -s snaplen ] [-w file] \n\
	     [-e expression] [-t administrative time] [-l logFileName] \n\
	     [-r input file] [-z number of time bins to change the output] \n\
where\n\
-h	this message\n\
-c	Maximum number of frames to be capured (Default=0 (infinity))\n\
-i	Specify the interface to be listened (Default=active interface)\n\
-s	Maximum number of bytes to be captured in each frame (Default: 1518)\n\
-w	File prefix where collected data will be stored (Default: cap)\n\
-e	Select the traffic that will be captured. See tcpdump expression \n\
	for more details (Default: ip)\n\
-t	Specify the time out in seconds (time bin)  for expired flows to be \n\
	flushed out of the memory (Default: 300)\n\
-z	Specify how many time bins will be considered to generate a new \n\
	output file name. As default, 0 means all day long (Default: 0)\n\
-r	Input file to offline capture\n\
-b	Enabling an optimun flows exportation to Profiling (Enabled by default: 1)\n\
-l	Specify the log file name (Default: logcap)\n\
\n\
Examples:\n\
%s -i eth0 -s 1518 -w cap -e ip -t 300 -l log\n\
	Captures flows of ip traffic from eth0 with at \n\
	maximum 1518 bytes length. The flows will be stored \n\
	on the files cap0, cap1...\n\
\n\
%s -w cap\n\
	Captures all traffic from the active interface.\n\
", progname, progname, progname, progname  );
}

int main(int argc, char **argv){

    loadExpressions();
    
    int index;
    int c;
    opterr = 0;
    cap_config *conf = new_cap_config();
    char *offLineFile = NULL;
    char *data=NULL;
    int fileAdminTime = 300;
    int flow_exp=1;
    int fileExpTime = 0;
    time_t tempo = 0;

    while ((c = getopt(argc, argv, "hi:w:c:s:e:t:z:l:r:b:")) != -1){
	switch (c) {
	case 'i':
	    snprintf(conf->dev,10,"%s",optarg);
	    break;
	case 'w':
	    snprintf(baseFileName,100,"%s",optarg);
    	    time(&tempo);
	    data = (char *) (malloc(sizeof(char)*7));
	    getDate(&tempo,data,6) ;
	    snprintf(fileName,256,"%s%s_0",baseFileName,data);
	    free(data);
	    break;
	case 'c':
	    conf->numOfPackets = atoi(optarg);
	    break;
	case 's':
	    conf->snap_len = atoi(optarg);
	    break;
	case 'e':
	    snprintf(conf->filter_app, 100, "%s",optarg);
	    break;
	case 't':
	    fileAdminTime = atoi(optarg);
	    break;
	case 'z':
	    fileExpTime = atoi(optarg);
	    break;
	case 'l':
	    snprintf(logFileName,100, "%s",optarg);
	    break;
	case 'r':
	    offLineFile = optarg;
	    break;
	case 'b':
	    flow_exp = atoi(optarg);
	    break;
	case 'h':
	    printHelp( argv[0] );
	    return 0;
	case '?':
	    if (isprint(optopt)){
		fprintf(stderr, "Unknown option `-%c'.\n", optopt);
		fprintf(stderr, "Use \"%s -h\" to see valid options\n", argv[0] );
	    } else {
		fprintf(stderr,	"Unknown option character `\\x%x'.\n", optopt);
		fprintf(stderr, "Use \"%s -h\" to see valid options\n", argv[0] );
		}
	    return 1;
	default:
	    abort();
	}
    }
    for (index = optind; index < argc; index++) {
	printf("Non-option argument %s\n", argv[index]);
    }
    printf("Starting program...\n");
    fflush(stdout);
    analyserpxError = analyserpxStart(conf, fileAdminTime, fileExpTime, offLineFile,flow_exp);
    if (analyserpxError) {
	printf("\nThe program will exit with erro code %d\n", analyserpxError);
    }
    else{
    	printf("Capture complete.\n");
    }
    fprintf(stdout, "%s\n","deve deletar");
    freeExpressions();
    fprintf(stdout, "%s - OK\n","deve deletar");
    free(conf);
    return 0;
}
