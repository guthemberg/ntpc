#include "functions.h"


int main(int argc, char *argv[])
{
  	double limit=0;
  	double beta=0;
  	char str[256]="";
  	char temp_str[256]="";
  	char path[512]="";
  	char command[512]="";
  	char filename[512]="";
	char dir_version[256]="";
  	time_t tempo = time(NULL);
  	time_t tempox = time(NULL);
	struct tm *data=NULL;
	int day=1, month=1, period=1, year=2005;
	
	//criar tabelas gerais 	
	map<string,TSIp*> &htGeralBCsrcIP=*(new map<string,TSIp*>);
	map<string,TSIp*> &htGeralBCsrcPrt=*(new map<string,TSIp*>);
	map<string,TSIp*> &htGeralBCdstIP=*(new map<string,TSIp*>);
	map<string,TSIp*> &htGeralBCdstPrt=*(new map<string,TSIp*>);
	//criar cotador geral
	T8Double *tdGeral = (T8Double *)mallocX(sizeof(T8Double),"called in main from traning.c","/tmp/teste.txt");
	initT8Double(tdGeral);

	//corpo do programa
	//os parametros 4 e 5 tratam do dia e do mes respectivamente
	//jah o parametro 6 trata da quantidade de dias a serem avaliados
  	fprintf(stdout,"Inicio do Processamento\n...");
  	if( (argv[1]!=NULL) && (argv[2]!=NULL) && (argv[3]!=NULL) && (argv[4]!=NULL) && (argv[5]!=NULL) && (argv[6]!=NULL) && (argv[7]!=NULL) && (argv[8]!=NULL) ) {
		//controle do periodo BEGIN_CONTROL
		day=atoi(argv[4]); month=atoi(argv[5]); year=atoi(argv[6]);period=atoi(argv[7]);
		int dia=day;
		while( dia <= (day+period) ) {
			if(dia<10) {
				if(month<10) snprintf(str,256,"%s/0%d0%d%d/",argv[1],dia, month,year);
				else snprintf(str,256,"%s/0%d%d%d/",argv[1],dia, month,year);
			} else {
				if(month<10) snprintf(str,256,"%s/%d0%d%d/",argv[1],dia, month,year);
				else snprintf(str,256,"%s/%d%d%d/",argv[1],dia, month,year);
			}
			//Processamento de um arquivo
			beta=atof(argv[3]);
    			if( !((beta>0.45)&&(beta<0.95)) ) beta=0.9;
    			tempo = time(NULL);
			data=localtime(&(tempo));
			snprintf(dir_version,512,"%s_%d%d%d_%dh%dm%ds","training_results",data->tm_mday,(data->tm_mon)+1,(data->tm_year)-100,(data->tm_hour),data->tm_min,data->tm_sec);
			snprintf(command,512,"/bin/csh %s/scripts/prepare_dir.sh %s %s",argv[8],str,dir_version);
			system(command); //descompacta result.txt.gz e cria hierarquia de diretorios
			snprintf(path,512,"%s/%s/",str,dir_version);//diretorio onde serao armazenados os resultados
			snprintf(filename,512,"%s/result.txt",str);//caminho completo com o nome do arquivo de entrada
  			gravaLog("Inicio do Processamento\n...",path);
			sprintf(temp_str,"Inicializacao --- Opcao : [%s]. tempo: %s. Diretotio do arquivo de entrada:[%s]. Beta:%.2f.",argv[2],asctime( localtime(&(tempo)) ),argv[1],beta);
    			gravaLog(temp_str,path);
    			//verifica as opcoes fornecidas
			//"esp" eh uma opcao especial que envolve gnu+kaz+aut
			if((!(memcmp(argv[2],"all",3)))||(!(memcmp(argv[2],"bit",3)))||(!(memcmp(argv[2],"edk",3)))||(!(memcmp(argv[2],"kaz",3)))||(!(memcmp(argv[2],"aut",3)))||(!(memcmp(argv[2],"esp",3)))||(!( memcmp(argv[2],"p2p",3) )) ) {
      				if(existFile(filename)) {
       					// O ultimo argumento da funcao abaixo trata das iteracoes, 
					// valores positivos indicam um limite
					snprintf(command,512,"processando: %s \n...\n",filename);
  					fprintf(stdout,command);
       					doProcess(filename,argv[2],1,0,beta,path,htGeralBCsrcIP,htGeralBCsrcPrt,htGeralBCdstIP,htGeralBCdstPrt,tdGeral);
					snprintf(command,512,"fim do processamento de : %s \n.",filename);
  					fprintf(stdout,command);
				} else { gravaLog("Arquivo de entrada invalido!",path); }
    			} else {
      				gravaLog("Opcao Invalida !",path);
    			}
    			tempox = time(NULL);
    			limit = ((difftime(tempox,tempo))) ;
    			sprintf(temp_str,"Finalizacao --- Opcao : [%s]. tempo: %s. Diretotio do arquivo de entrada:[%s]. Duracao: %.3f segundos",argv[2],asctime( localtime(&(tempo)) ),argv[1],limit);
    			gravaLog(temp_str,path);

			snprintf(command,512,"/bin/csh %s/scripts/finish_dir.sh %s",argv[8],str);
			system(command); //compacta result.txt
			dia++;
		} 
		//imprimindo resultado do treinamento
		if(strlen(path) > 1) {
        		sort(htGeralBCsrcIP, "srcIP",tdGeral,path);
        		sort(htGeralBCsrcPrt, "srcPrt",tdGeral,path);
        		sort(htGeralBCdstIP, "dstIP",tdGeral,path);
        		sort(htGeralBCdstPrt, "dstPrt",tdGeral,path);
		}
		//controle do periodo END_CONTROL

  	} else {
    		fprintf(stdout,"Numero de parametros insuficiente em traning.c. Use:\n#program_name prefix_dir type beta day month year period script_dir");
  	}


	//deletando o contador geral
	free(tdGeral);
	//deleta tabelas
	zeraTabela(htGeralBCsrcIP,0);
	zeraTabela(htGeralBCdstIP,0);
	zeraTabela(htGeralBCsrcPrt,1);
	zeraTabela(htGeralBCdstPrt,1);
	delete &htGeralBCsrcIP;
	delete &htGeralBCdstIP;
	delete &htGeralBCsrcPrt;
	delete &htGeralBCdstPrt;
  
  	//mansagem de finalizacao
	if(strlen(path) > 1) gravaLog("Processo finalizado",path);
	else fprintf(stdout,"Processo finalizado");
	
  	return EXIT_SUCCESS;
}
