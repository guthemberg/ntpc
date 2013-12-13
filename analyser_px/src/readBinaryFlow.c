#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "analyserpxTypes.h"
#include "analyserpxFile.h"
#include "analyserpxFlow.h"
#include "version.h"

void sintaxe( char *progname ){
	fprintf( stderr, "%s version " ANALYSERPXREAD_VERSION "\n", progname);
	fprintf( stderr, "%s reads a file with flows previously captured \n\
by analyserpx_cap and prints it in text format. \n\
\n\
Usage:	%s [-h] [-d] [-s] file\n\
where\n\
-h	This message\n\
-d	Prints the start data and time in a human readable format. \n\
	The end time is substituted by the flow duration (in miliseconds). \n\
-s	Print protocol name instead of protocol ID\n\
file	The file containing flows captured with analyserpx_cap\n\
", progname, progname  );
}

int main(int argc, char **argv) {
    char flow_format = FORMAT_FLOW_DEFAULT;
    char proto_format = FORMAT_PROTO_DEFAULT;

    int c;	// option
    int entry_count = 0;
    flow_t *flow = (flow_t *) malloc(sizeof(flow_t));
    char buffer[1024];
    char *fileName = NULL;

    while ((c = getopt(argc, argv, "hsdf:")) != -1){
	switch (c) {
	case 'd':
	    flow_format = FORMAT_FLOW_DATE_DURATION;
	    break;
	case 'f':
	    fileName = optarg;
	    break;
	case 's':
	    proto_format = FORMAT_PROTO_NAME;
	    break;
	case 'h':
	    sintaxe( argv[0] );
	    return( 0 );
	    break;
	}
    }
//     printf("default proto format = %d\n", proto_format );
//     printf("default format = %d\n", flow_format );
//     printf("optind=%d, argc=%d, argv[1]=%s, filename=%s\n", optind, argc, argv[1], fileName );

    //argc -= optind; argv += optind;
    if( fileName == NULL ) {
	if( argc > optind ){
		fileName = argv[ optind ];
	} else {
		sintaxe(argv[0]);
	}
    }

//     if (argc == 1) {
// 	printf("\nENTER FILENAME\n");
// 	return 1;
//     }
//     fileName = argv[1];

    printFlowStruct( flow_format, buffer);
    printf("#%s\n", buffer);

    int i = 0;
    while ((flow = readFlowFromFile(flow, fileName, i++))) {
	entry_count++;
	flowToString(flow_format, proto_format, flow, buffer);
	fprintf( stdout, "%s\n", buffer);
    }
    fprintf( stderr, "#%d entries found\n", entry_count);
    exit(0);
}
