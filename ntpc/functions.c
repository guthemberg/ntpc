#include "functions.h"

using namespace std;


//Objeto usado para lidar com a eficiencia (COMPLETENESS=COMP)
SelectBC_COMP::SelectBC_COMP()   // Constructor
{
   id = 27;
   precisao = 0.0;
   eficiencia = 0.0;
}

SelectBC_COMP::SelectBC_COMP(const SelectBC_COMP &copyin)   // Copy constructor to handle pass by value.
{
   id = copyin.id;
   precisao = copyin.precisao;
   eficiencia = copyin.eficiencia;
}

// This function is required for built-in STL list functions like sort
int SelectBC_COMP::operator<(const SelectBC_COMP &rhs) const
{
   if( this->eficiencia < rhs.eficiencia) return 1;
   return 0;
}

//Objeto usado para lidar com a precisao (ACCURACY=ACCU)
SelectBC_ACCU::SelectBC_ACCU()   // Constructor
{
   id = 27;
   precisao = 0.0;
   eficiencia = 0.0;
}

SelectBC_ACCU::SelectBC_ACCU(const SelectBC_ACCU &copyin)   // Copy constructor to handle pass by value.
{
   id = copyin.id;
   precisao = copyin.precisao;
   eficiencia = copyin.eficiencia;
}

// This function is required for built-in STL list functions like sort
int SelectBC_ACCU::operator<(const SelectBC_ACCU &rhs) const
{
   if( this->precisao < rhs.precisao) return 1;
   return 0;
}


void teste() {
   printf("Hello World!!!\n");
}

void removeS(TFluxo *p)
  {
    free(p);
  }

void *mallocX (unsigned int nbytes, char *str, char *path) 
{
   void *ptr;
   char tempstr[500];
   ptr = malloc (nbytes);
   if (ptr == NULL) {
      strcpy(tempstr,"");
      sprintf(tempstr,"Socorro! malloc devolveu NULL! em %s\n",str);
      gravaLog(tempstr,path);
      //return NULL;
      exit (EXIT_FAILURE);
   }
   return ptr;
}

/* funcoes para manipulacao de arquivos */
FILE *abreArquivoR (char *str, char *path)
  {
    FILE *p;
    char tempstr[500];
    if (!(p=fopen(str,"rb"))) {
      strcpy(tempstr,"");
      sprintf(tempstr,"\nImpossivel abrir o arquivo: %s\n",str);
      gravaLog(tempstr, path);
      exit(1);
    }
    return p;
  }

FILE *abreArquivoAplus (char *str, char *path)
  {
    FILE *p;
    char tempstr[500];
    if (!(p=fopen(str,"a+"))) {
      strcpy(tempstr,"");
      sprintf(tempstr,"\nImpossivel abrir o arquivo: %s\n",str);
      gravaLog(tempstr,path);
      exit(1);
    }
    return p;
  }
FILE *abreArquivoW (char *str, char *path)
  {
    FILE *p;
    char tempstr[500];
    if (!(p=fopen(str,"w"))) {
      strcpy(tempstr,"");
      sprintf(tempstr,"\nImpossivel abrir o arquivo: %s\n",str);
      gravaLog(tempstr, path);
      exit(1);
    }
    return p;
  }

long getSizeofFile(char *str, char *path)
  {
    FILE *list;
    long size=0;
    list = abreArquivoR(str, path);
    fseek (list, 0, SEEK_END);
    size=ftell (list);
    fclose (list);
    return size;
  }

void fechaArquivo(FILE *p)
  {
    fclose(p);
  }
 
void gravaString (char *cadeia,FILE *filets)
 {
   fprintf(filets,"%s\n",cadeia);
 }

void gravaLog (char *cadeia, char *path)
 {
   FILE *logs;
   char str[256]="";
   snprintf(str,256,"%s%s",path,"/resultados/h_log.txt");
   logs = abreArquivoAplus(str,path);
   fprintf(logs,"%s\n",cadeia);
   fechaArquivo(logs);
 }

int existFile(char *str)
  {
    FILE *p;
//    printf(" eu acho que eh aqui 4\n");
    p=fopen(str,"r");
//    printf(" eu acho que eh aqui 5 antes do p igual a null\n");
    if(p==NULL)
      return 0;
    else
      fechaArquivo(p);
    return 1;
  }

int deleteFile(char *str)
  {
    if (existFile(str))
      return remove(str);
    return 0;
  }

//Funcoes para manipular a hash table
//Funcoes para manipular a hash table

void chargeListe(char *id, char *listfilelocal,int x, int iteracao, double bt, char *path, map<string,TSIp*> &htGeralBCsrcIP, map<string,TSIp*> &htGeralBCsrcPrt, map<string,TSIp*> &htGeralBCdstIP, map<string,TSIp*> &htGeralBCdstPrt, T8Double *tdGeral)
  {
    TCSTime *cstime;
    int linha=0;
    char str[200]="";
    int i=0, no=0;
    map<string,TSIp*> &htAsrcIP=*(new map<string,TSIp*>);
    map<string,TSIp*> &htAdstIP=*(new map<string,TSIp*>);
    map<string,TSIp*> &htAsrcPrt=*(new map<string,TSIp*>);
    map<string,TSIp*> &htAdstPrt=*(new map<string,TSIp*>);
    map<string,TSIp*> &htSsrcIP=*(new map<string,TSIp*>);
    map<string,TSIp*> &htSdstIP=*(new map<string,TSIp*>);
    map<string,TSIp*> &htSsrcPrt=*(new map<string,TSIp*>);
    map<string,TSIp*> &htSdstPrt=*(new map<string,TSIp*>);
    //tabelas que armazenarao os valores da eficiencia e precisao de cada bc
    map<string,TSIp*> &htBCsrcIP=*(new map<string,TSIp*>);
    map<string,TSIp*> &htBCdstIP=*(new map<string,TSIp*>);
    map<string,TSIp*> &htBCsrcPrt=*(new map<string,TSIp*>);
    map<string,TSIp*> &htBCdstPrt=*(new map<string,TSIp*>);
    list<TLFluxo*> &lst=*(new list<TLFluxo*>);
    //variavel que armazenarah o total de p2p para o calculo da eficiencia
    T8Double *td = (T8Double *)mallocX(sizeof(T8Double),"oiamiguinho",path);
    initT8Double(td);
    //incializacao das variaveis globais do profiling
    cstime = (TCSTime *)mallocX(sizeof(TCSTime),"Charge Liste",path);
    cstime->micro=0;
    cstime->sltime=0;
    cstime->m=0;
    TFluxo *tr;
    FILE *list;
    char arg[500], c;
    double timebin=5;
    int index=0,champ=1,control=0,flag=0;
    tr = (TFluxo *)mallocX(sizeof(TFluxo),"Charge Liste",path);
    tr->tipo = 50;
    struct in_addr *moule = (struct in_addr *)mallocX(sizeof(struct in_addr),"Charge Liste",path);
    if(existFile(listfilelocal)){
        list = abreArquivoR(listfilelocal, path);
        do {
          c = getc(list);
          if(control) {
            if(isInvalid(c) ) {
              break;
            }
          }
          if(c==',') {
            arg[index]='\0';
            switch(champ) {
              case 1:
                tr->ini_sec=(time_t)atof(arg);
                break;
              case 2:
                tr->ini_mil=(time_t)atof(arg);
                break;
              case 3:
                tr->end_sec=(time_t)atof(arg);
                break;
              case 4:
                tr->end_mil=(time_t)atof(arg);
                break;
              case 5:
                moule->s_addr = inet_addr(arg);
                tr->ip_src=(*moule);
                break;
              case 6:
                tr->src_port = htons((u_short)atoi(arg));
                break;
              case 7:
                moule->s_addr = inet_addr(arg);
                tr->ip_dst=(*moule);
                break;
              case 8:
                tr->dst_port = htons((u_short)atoi(arg));
                break;
              case 9:
                tr->n_bytes = atof(arg);
                break;
              case 10:
                tr->n_frames = atof(arg);
                break;
              case 11:
                tr->tipo = (u_int)atoi(arg);
                break;
              case 12:
                tr->rumo = (u_int)atoi(arg);
                break;
            }
            index=0;
            champ++;
          } else if(c=='\n') {
            arg[index]='\0';
            switch(champ) {
              case 9:
                tr->n_bytes = atof(arg);
                break;
              case 10:
                tr->n_frames = atof(arg);
                break;
              case 11:
                tr->tipo = (u_int)atoi(arg);
                break;
              case 12:
                tr->rumo = (u_int)atoi(arg);
                break;
            }
              linha++;
            //geraResultado(tr);
            //Alinha abaixo seleciona as aplicacoes P2P apenas
//            if((estPorteBienConnu(ntohs(tr->src_port)))||(estPorteBienConnu(ntohs(tr->dst_port))))
            flag=isToProcess(id,tr->tipo);
            //if(control&&flag) {
            if(control) {
              metsTLFluxo(tr,lst,path);no++;
 	      if(cstime->micro ==0 ) {
 	        cstime->micro = (((double)tr->end_sec)*1000000) + (double)tr->end_mil;
              } else {
                
                //verifica se jah (timebin . X ) minutos
                  /*if(i==274) {
                    timebin=(3);
                  } else if((i==275)||(i==276)) {
                    timebin=(1);
                  } else if((i==277)||(i==278)||(i==279)) {
                    timebin=(1);
                  } else { timebin=5;}*/
                  if((no>1950000)|| ( (((((double)tr->end_sec)*1000000) + (double)tr->end_mil) - (cstime->micro))/60000000 ) >= ((timebin*x)+((i)*(timebin*x))) ) {
                    i++;
                    if(no>1950000) {
                      sprintf(str,"%s:Chegou aqui, antes while %d - %lu, iteracao: %d - PIPOCOU > 1950000",id,linha,(unsigned long)lst.size(),i);
                    }else{
                      sprintf(str,"%s:Chegou aqui, antes while %d - %lu, iteracao: %d",id,linha,(unsigned long)lst.size(),i);
                    }
                    no=0;
                    gravaLog(str,path);
                    linha=0;
                    sprintf(str,"%s%d",id,i);
  		    doAlgorithm1(id,htAsrcIP, htSsrcIP,0,0,bt,path);
  		    doAlgorithm1(id,htAdstIP, htSdstIP,0,1,bt,path);
  		    doAlgorithm1(id,htAsrcPrt, htSsrcPrt,1,0,bt,path);
  		    doAlgorithm1(id,htAdstPrt, htSdstPrt,1,1,bt,path);
                    doBC(flag,str,htSsrcIP,lst,0,0,path);
                    doBC(flag,str,htSdstIP,lst,0,1,path);
                    doBC(flag,str,htSsrcPrt,lst,1,0,path);
                    doBC(flag,str,htSdstPrt,lst,1,1,path);
		    //funcao que calcula as combinacoes
		    doScan(str, htSsrcIP, htSsrcPrt, htSdstIP, htSdstPrt,lst,htBCsrcIP, htBCsrcPrt, htBCdstIP, htBCdstPrt, td,path);
                    //cstime->micro=0;
                    cstime->m=0;
                    zeraTabela(htAsrcIP,0);
                    zeraTabela(htAdstIP,0);
                    zeraTabela(htAsrcPrt,1);
                    zeraTabela(htAdstPrt,1);
                    zeraTabela(htSsrcIP,0);
                    zeraTabela(htSdstIP,0);
                    zeraTabela(htSsrcPrt,1);
                    zeraTabela(htSdstPrt,1);
                    zeraLista(lst);
                    cstime->sltime=cstime->sltime + 1;
                  }
              }
              cstime->m=cstime->m + 1;
	      metsTFluxoProfIP(flag,tr,htAsrcIP,0,path);
	      metsTFluxoProfIP(flag,tr,htAdstIP,1,path);
	      metsTFluxoProfPrt(flag,tr,htAsrcPrt,0,path);
	      metsTFluxoProfPrt(flag,tr,htAdstPrt,1,path);
              //faisQQChose(tr);
            } else {
              if(control) {
                if(cstime->micro ==0 ) {
                  cstime->micro = (((double)tr->end_sec)*1000000) + (double)tr->end_mil;
                } else {
                  if( ( (((((double)tr->end_sec)*1000000) + (double)tr->end_mil) - (cstime->micro))/60000000 ) >= ((timebin*x)+((timebin*x)*i)) ) {
                    i++;
                    sprintf(str,"%s:Chegou aqui, antes while %d - %lu, iteracao: %d",id,linha,(unsigned long)lst.size(),i);
                    gravaLog(str,path);
                    linha=0;
                    sprintf(str,"%s%d",id,i);
  		    doAlgorithm1(id,htAsrcIP, htSsrcIP,0,0,bt,path);
  		    doAlgorithm1(id,htAdstIP, htSdstIP,0,1,bt,path);
  		    doAlgorithm1(id,htAsrcPrt, htSsrcPrt,1,0,bt,path);
  		    doAlgorithm1(id,htAdstPrt, htSdstPrt,1,1,bt,path);
                    doBC(flag,str,htSsrcIP,lst,0,0,path);
                    doBC(flag,str,htSdstIP,lst,0,1,path);
                    doBC(flag,str,htSsrcPrt,lst,1,0,path);
                    doBC(flag,str,htSdstPrt,lst,1,1,path);
		    //funcao que calcula as combinacoes
		    doScan(str, htSsrcIP, htSsrcPrt, htSdstIP, htSdstPrt,lst,htBCsrcIP, htBCsrcPrt, htBCdstIP, htBCdstPrt,td,path);
                    //cstime->micro=0;
                    cstime->m=0;
                    zeraTabela(htAsrcIP,0);
                    zeraTabela(htAdstIP,0);
                    zeraTabela(htAsrcPrt,1);
                    zeraTabela(htAdstPrt,1);
                    zeraTabela(htSsrcIP,0);
                    zeraTabela(htSdstIP,0);
                    zeraTabela(htSsrcPrt,1);
                    zeraTabela(htSdstPrt,1);
                    zeraLista(lst);
                    cstime->sltime=cstime->sltime + 1;
                  }
                }
                cstime->m=cstime->m + 1;
              }

            }
            tr->tipo = 50;
            control=1;
            index=0;
            champ=1;
            if( (iteracao==(i))&&(iteracao) ) break;
          } else {
            arg[index]=c;
            index++;
          }
        } while (c != EOF);
        i++;
        sprintf(str,"%s:Chegou aqui, antes while %d - %lu, iteracao: %d",id,linha,(unsigned long)lst.size(),i);
        gravaLog(str,path);
        //printf("Chegou aqui, depois while %d\n",linha);
        sprintf(str,"%s%d",id,i);
        doAlgorithm1(id,htAsrcIP, htSsrcIP,0,0,bt,path);
        doAlgorithm1(id,htAdstIP, htSdstIP,0,1,bt,path);
        doAlgorithm1(id,htAsrcPrt, htSsrcPrt,1,0,bt,path);
        doAlgorithm1(id,htAdstPrt, htSdstPrt,1,1,bt,path);
        doBC(flag,str,htSsrcIP,lst,0,0,path);
        doBC(flag,str,htSdstIP,lst,0,1,path);
        doBC(flag,str,htSsrcPrt,lst,1,0,path);
        doBC(flag,str,htSdstPrt,lst,1,1,path);
	//funcao que calcula as combinacoes
        doScan(str, htSsrcIP, htSsrcPrt, htSdstIP, htSdstPrt,lst,htBCsrcIP, htBCsrcPrt, htBCdstIP, htBCdstPrt,td,path);
        //imprimindo a precisao das BC
	printHTBCLog(htBCsrcIP, "srcIP",path);
	printHTBCLog(htBCsrcPrt, "srcPrt",path);
	printHTBCLog(htBCdstIP, "dstIP",path);
	printHTBCLog(htBCdstPrt, "dstPrt",path);
	//os quatro procedimentos a seguir sao ustilizadas para armazenar as informacoes das BCs
	addTStoBC(htBCsrcIP, htGeralBCsrcIP,path);
	addTStoBC(htBCsrcPrt, htGeralBCsrcPrt, path);
	addTStoBC(htBCdstIP, htGeralBCdstIP, path);
	addTStoBC(htBCdstPrt, htGeralBCdstPrt, path);
	//adiciona ao contador geral
	addT8Double(td,tdGeral);
	//ordena e imprime as BCs (os quatro proximos procedimentos
	sort(htBCsrcIP, "srcIP",td,path);
	sort(htBCsrcPrt, "srcPrt",td,path);
	sort(htBCdstIP, "dstIP",td,path);
	sort(htBCdstPrt, "dstPrt",td,path);
        cstime->micro=0;
        cstime->m=0;
        zeraTabela(htAsrcIP,0);
        zeraTabela(htAdstIP,0);
        zeraTabela(htAsrcPrt,1);
        zeraTabela(htAdstPrt,1);
        zeraTabela(htSsrcIP,0);
        zeraTabela(htSdstIP,0);
        zeraTabela(htSsrcPrt,1);
        zeraTabela(htSdstPrt,1);
        zeraTabela(htBCsrcIP,0);
        zeraTabela(htBCdstIP,0);
        zeraTabela(htBCsrcPrt,1);
        zeraTabela(htBCdstPrt,1);
        zeraLista(lst);
        cstime->sltime=cstime->sltime + 1;
        free(cstime);
        //remove a tabela criada
        delete &htAsrcIP;
        delete &htAdstIP;
        delete &htAsrcPrt;
        delete &htAdstPrt;
        delete &htSsrcIP;
        delete &htSdstIP;
        delete &htSsrcPrt;
        delete &htSdstPrt;
        delete &htBCsrcIP;
        delete &htBCdstIP;
        delete &htBCsrcPrt;
        delete &htBCdstPrt;
        delete &lst;
    	//finalizacoes desse metodo
	free(td);
        free(moule);
        removeS(tr);
        fclose(list);//fechaArquivo(list);
    }
  }
//convencoes para esta funcao
//i representa se eh porta ou endereco: 0 enderecos IP e diferente de zero portas
//j representa de eh de origem ou destino: 0 para de origem e direfente de zero para de destino
string faisCledesSource(struct in_addr ip_src, u_short src_port, struct in_addr ip_dst, u_short dst_port,int i,int j)
  {
    
    string str;
    char porta[20]="";
    if(i) {
      if(j) {
        sprintf(porta,"%d",ntohs(dst_port));
        str = porta;
      } else {
        sprintf(porta,"%d",ntohs(src_port));
        str = porta;
      } 
    } else {
      if(j)
         str = inet_ntoa(ip_dst);
      else
         str = inet_ntoa(ip_src);
    }
  
    return str;
  }

//i da significado para se serah : 1 destino e 0 para origem
void metsTFluxoProfIP(int flag,TFluxo *nova, map<string,TSIp*> &htA,int i, char *path) {
    TSIp *no,*aux;
   
    if(i) {
      if(htA.find(faisCledesSource(nova->ip_src,nova->src_port,nova->ip_dst,nova->dst_port,0,1)) == htA.end()) {
        no=(TSIp *)mallocX(sizeof(TSIp),"metsTFluxoProfIP",path);
        metsZeroProf(no);
        no->ip=nova->ip_dst;
        no->port=0; 
        no->mi=1; 
        no->pd=0;
        no->n_bytes=nova->n_bytes;
        no->tempo=donneTempsIntervalle(nova);
        no->frames=nova->n_frames;
        if(flag) {
          no->mi_p2p=1; 
          no->n_bytes_p2p=nova->n_bytes;
          no->tempo_p2p=donneTempsIntervalle(nova);
          no->frames_p2p=nova->n_frames;
        } 
        htA[faisCleProf(no,0)] = no;
      } else {
        aux=htA[faisCledesSource(nova->ip_src,nova->src_port,nova->ip_dst,nova->dst_port,0,1)];
        aux->mi=aux->mi+1;
        aux->n_bytes=(aux->n_bytes)+nova->n_bytes;
        aux->tempo=(aux->tempo)+donneTempsIntervalle(nova);
        aux->frames=(aux->frames)+nova->n_frames; 
        if(flag) {
          aux->mi_p2p=aux->mi_p2p+1;
          aux->n_bytes_p2p=(aux->n_bytes_p2p)+nova->n_bytes;
          aux->tempo_p2p=(aux->tempo_p2p)+donneTempsIntervalle(nova);
          aux->frames_p2p=(aux->frames_p2p)+nova->n_frames; 
        } 
      }
    }else {
      if(htA.find(faisCledesSource(nova->ip_src,nova->src_port,nova->ip_dst,nova->dst_port,0,0)) == htA.end()) {
        no=(TSIp *)mallocX(sizeof(TSIp),"metsTFluxoProfIP",path);
        metsZeroProf(no);
        no->ip=nova->ip_src; 
        no->port=0; 
        no->mi=1; 
        no->pd=0; 
        no->n_bytes=nova->n_bytes;
        no->tempo=donneTempsIntervalle(nova);
        no->frames=nova->n_frames; 
        if(flag) {
          no->mi_p2p=1; 
          no->n_bytes_p2p=nova->n_bytes;
          no->tempo_p2p=donneTempsIntervalle(nova);
          no->frames_p2p=nova->n_frames;
        } 
        htA[faisCleProf(no,0)] = no;
      } else {
        aux=htA[faisCledesSource(nova->ip_src,nova->src_port,nova->ip_dst,nova->dst_port,0,0)];
        aux->mi=aux->mi+1;
        aux->n_bytes=(aux->n_bytes)+nova->n_bytes;
        aux->tempo=(aux->tempo)+donneTempsIntervalle(nova);
        aux->frames=(aux->frames)+nova->n_frames; 
        if(flag) {
          aux->mi_p2p=aux->mi_p2p+1;
          aux->n_bytes_p2p=(aux->n_bytes_p2p)+nova->n_bytes;
          aux->tempo_p2p=(aux->tempo_p2p)+donneTempsIntervalle(nova);
          aux->frames_p2p=(aux->frames_p2p)+nova->n_frames; 
        } 
      }
    } 
}

void metsTFluxoProfPrt(int flag,TFluxo *nova, map<string,TSIp*> &htA,int i, char *path) {
    TSIp *no,*aux;
    struct in_addr *moule = (struct in_addr *)mallocX(sizeof(struct in_addr),"metsTFluxoProfPrt",path);
    string str;
    char porta[20]="";
    sprintf(porta,"%d",ntohs(nova->dst_port));
    str = porta;
   
    if(i) {
      if(htA.find(faisCledesSource(nova->ip_src,nova->src_port,nova->ip_dst,nova->dst_port,1,1)) == htA.end()) {
        no=(TSIp *)mallocX(sizeof(TSIp),"metsTFluxoProfPrt",path);
        metsZeroProf(no);
        moule->s_addr = inet_addr("0.0.0.0");
        no->ip=(*moule);
        no->port=nova->dst_port;
        no->mi=1; 
        no->pd=0; 
        no->n_bytes=nova->n_bytes;
        no->tempo=donneTempsIntervalle(nova);
        no->frames=nova->n_frames; 
        if(flag) {
          no->mi_p2p=1; 
          no->n_bytes_p2p=nova->n_bytes;
          no->tempo_p2p=donneTempsIntervalle(nova);
          no->frames_p2p=nova->n_frames;
        } 
        htA[faisCleProf(no,1)] = no;
      //printf("flaisCledes = %s --  faisCleProf = %s -- dst_port = %d -- str->dst_port=%s\n", (faisCledesSource(nova->ip_src,nova->src_port,nova->ip_dst,nova->dst_port,1,1)).c_str(),(faisCleProf(no,1)).c_str(),ntohs(nova->dst_port),str.c_str() );
      } else {
        aux=htA[faisCledesSource(nova->ip_src,nova->src_port,nova->ip_dst,nova->dst_port,1,1)];
        aux->mi=aux->mi+1;
        aux->n_bytes=(aux->n_bytes)+nova->n_bytes;
        aux->tempo=(aux->tempo)+donneTempsIntervalle(nova);
        aux->frames=(aux->frames)+nova->n_frames; 
        if(flag) {
          aux->mi_p2p=aux->mi_p2p+1;
          aux->n_bytes_p2p=(aux->n_bytes_p2p)+nova->n_bytes;
          aux->tempo_p2p=(aux->tempo_p2p)+donneTempsIntervalle(nova);
          aux->frames_p2p=(aux->frames_p2p)+nova->n_frames; 
        } 
      }
    } else {
      if(htA.find(faisCledesSource(nova->ip_src,nova->src_port,nova->ip_dst,nova->dst_port,1,0)) == htA.end()) {
        no=(TSIp *)mallocX(sizeof(TSIp),"metsTFluxoProfPrt",path);
        metsZeroProf(no);
        moule->s_addr = inet_addr("0.0.0.0");
        no->ip=(*moule);
        no->port=nova->src_port;
        no->mi=1; 
        no->pd=0; 
        no->n_bytes=nova->n_bytes;
        no->tempo=donneTempsIntervalle(nova);
        no->frames=nova->n_frames; 
        if(flag) {
          no->mi_p2p=1; 
          no->n_bytes_p2p=nova->n_bytes;
          no->tempo_p2p=donneTempsIntervalle(nova);
          no->frames_p2p=nova->n_frames;
        } 
        htA[faisCleProf(no,1)] = no;
      } else {
        aux=htA[faisCledesSource(nova->ip_src,nova->src_port,nova->ip_dst,nova->dst_port,1,0)];
        aux->mi=aux->mi+1;
        aux->n_bytes=(aux->n_bytes)+nova->n_bytes;
        aux->tempo=(aux->tempo)+donneTempsIntervalle(nova);
        aux->frames=(aux->frames)+nova->n_frames; 
        if(flag) {
          aux->mi_p2p=aux->mi_p2p+1;
          aux->n_bytes_p2p=(aux->n_bytes_p2p)+nova->n_bytes;
          aux->tempo_p2p=(aux->tempo_p2p)+donneTempsIntervalle(nova);
          aux->frames_p2p=(aux->frames_p2p)+nova->n_frames; 
        } 
      }
    }
    free(moule); 
}

string faisCleProf(TSIp *ts,int i) {
    string str;
    char porta[20]="";
  
    if(i) {
      sprintf(porta,"%d",ntohs(ts->port));
      str = porta;
    } else
      str = inet_ntoa(ts->ip);
    return str;

}


void metsZeroProf(TSIp *t) 
  {
    (t)->mi=0;
    (t)->pd=0;
    (t)->id=27;
    (t)->n_bytes=0;
    (t)->tempo=0;
    (t)->frames=0;
    (t)->mi_p2p=0;
    (t)->n_bytes_p2p=0;
    (t)->tempo_p2p=0;
    (t)->frames_p2p=0;
    (t)->precisao=0;
  }


//funcoes da implementacao do profiling

void produisResultTSIp(TSIp *p) {
    printf("%s,%.0f,%.6f\n",inet_ntoa(p->ip),p->mi,p->pd);
}

/*void pourCordeTable(char ch) {
    TSIp *p; int flag=1, conta=0;
    map<string,TSIp*>::iterator itrp;
    switch(ch) {
      case 'A':
        //printf("Tabela A, tamanho:%d\n",contaTableNAOFUNCIONAMAISD('A'));
        printf("-------\n");
        itrp=htA.begin();
        while(itrp!=htA.end()){
          conta++;
          p=itrp->second;
          if(!(conta >= 3)) {
            produisResultTSIp(p);
          } else {
            if(flag) printf("...\n");
            flag=0;
          }
          itrp++;
        }
        printf("-------\n");
        break;
      case 'R':
        //printf("Tabela R, tamanho:%d\n",contaTable('R'));
        printf("-------\n");
        itrp=htR.begin();
        while(itrp!=htR.end()){
          conta++;
          p=itrp->second;
          if(!(conta >= 3)) {
            produisResultTSIp(p);
          } else {
            if(flag) printf("...\n");
            flag=0;
          }
          itrp++;
        }
        printf("-------\n");
        break;
      case 'S':
        printf("Tabela S, tamanho:%d\n",contaTable('S'));
        printf("-------\n");
        itrp=htS.begin();
        while(itrp!=htS.end()){
          conta++;
          p=itrp->second;
          if(!(conta >= 3)) {
            produisResultTSIp(p);
          } else {
            if(flag) printf("...\n");
            flag=0;
          }
          itrp++;
        }
        printf("-------\n");
        break;
      default:
        printf("Erro na remocao de un no profiling\n");
    }

}
*/
void enleveProf(TSIp *p)
  {
    free(p);
  }

u_int removeNOs(map<string,TSIp*> &ht, TSIp *p,int i)
  {
    return ht.erase(faisCleProf(p,i));
  }

void
copyTableAtoR(map<string,TSIp*> &htA, map<string,TSIp*> &htR,int i, char *path)
  {
    TSIp *no,*p;
    map<string,TSIp*>::iterator itrp;

    itrp=htA.begin();
    while(itrp!=htA.end()){
      p=itrp->second;
      no=(TSIp *)mallocX(sizeof(TSIp),"copyTableAtoR",path);
      metsZeroProf(no);
      no->ip=p->ip;
      no->port=p->port;
      no->mi=p->mi;
      no->pd=p->pd;
      no->n_bytes=p->n_bytes;
      no->id=p->id;
      no->tempo=p->tempo;
      no->frames=p->frames;
      no->mi_p2p=p->mi_p2p;
      no->n_bytes_p2p=p->n_bytes_p2p;
      no->tempo_p2p=p->tempo_p2p;
      no->frames_p2p=p->frames_p2p;
      htR[faisCleProf(no,i)] = no;
      itrp++;
    }

  }

void
zeraTabela(map<string,TSIp*> &ht,int i)
  {
    TSIp *p;
    map<string,TSIp*>::iterator itrp;

    itrp=ht.begin();
    while(itrp!=ht.end()){
      p=itrp->second;
      itrp++;
      removeNOs(ht,p,i);
      enleveProf(p);
    }
  }

u_int contaTable(map<string,TSIp*> &ht)
  {
    return ht.size();
  }

double getPD(map<string,TSIp*> &htA, TSIp *host,int i) 
  {
    TSIp *p;
    if(htA.find(faisCleProf(host,i)) == htA.end()) {
      return 0;
    } else {
      p = htA[faisCleProf(host,i)];
      return (p->pd);
    }
    
  }

//os inteiros dessa funcao indicarao se nao zero para porta e zero para ip
u_short getID(double rux,double ruy, double ruz, int x, int y, int z)
  {
    return ( (getLru(rux,x)*3*3) + (getLru(ruy,y)*3) + (getLru(ruz,z)) );
  }

u_short getLru(double ru, int i) 
  {
    double e=0;
    if(i) {
      e=(0.2);
      if( (ru>=0) && (ru<=e) ) return 0; //low
      if( (ru>e) && (ru<(1-e)) ) return 1; //medium
      if( (ru>=(1-e)) && (ru<=(1)) ) return 2; //hight
    } else {
      e=(0.3);
      if( (ru>=0) && (ru<=e) ) return 0; //low
      if( (ru>e) && (ru<(1-e)) ) return 1; //medium
      if( (ru>=(1-e)) && (ru<=(1)) ) return 2; //hight
    }
    return 5;
  }

double getBMBytes(map<string,TSIp*> &ht)
  {
    TSIp *p=NULL;
    double m=0;
    map<string,TSIp*>::iterator itrp;
    itrp=ht.begin();
    while(itrp!=ht.end()){
      p=itrp->second;
      m+=(p->n_bytes);
      itrp++;
    }
    return m;
  }

void contaBPDBytes(map<string,TSIp*> &ht)
  {
    TSIp *p=NULL;

    double m = getBMBytes(ht);
    map<string,TSIp*>::iterator itrp;
    itrp=ht.begin();
    while(itrp!=ht.end()){
      p=itrp->second;
      p->pd=((p->n_bytes)/(m));
      itrp++;
    }
  }


double getM(map<string,TSIp*> &ht)
  {
    TSIp *p;
    double m=0;
    map<string,TSIp*>::iterator itrp;
    itrp=ht.begin();
    while(itrp!=ht.end()){
      p=itrp->second;
      m+=(p->mi);
      itrp++;
    }
    return m;
  } 
//calculo da distribuicao de probabilidade
void contaPD(map<string,TSIp*> &ht)
  { 
    TSIp *p;
    double m = getM(ht);
    map<string,TSIp*>::iterator itrp;
    itrp=ht.begin();
    while(itrp!=ht.end()){
      p=itrp->second;
      p->pd=((p->mi)/(m));
      itrp++;
    }
  }

double getEntropia(map<string,TSIp*> &ht)
  {
    TSIp *p;
    double entropia=0;
    map<string,TSIp*>::iterator itrp;
    itrp=ht.begin();
    while(itrp!=ht.end()){
      p=itrp->second;
      entropia+=((p->pd)*log2(p->pd));
      itrp++;
    }
    if(entropia==0) return 0;
    return ((-1)*entropia);
  }
double getRU(map<string,TSIp*> &ht, char *path)
  {
    double h=0;
    float ru=0;
    double ru1=0;
    u_int modulo=1;
    char str[100]="";
    
    h=getEntropia(ht);
    modulo=contaTable(ht);
    if(modulo<2) modulo=2;
    ru1 = (double)((h)/(log2(modulo)));
    ru = (float)ru1;
    if((ru<0)||(ru>1)) {
      sprintf(str,"[RU]%.16f,[entropia]%.16f,[denomi]%.16f",ru,(double)h,log2(modulo));
      gravaLog(str,path);
    }
    return (double)ru;
  }
void
doBC(int flag, char *id, map<string,TSIp*> &ht,list<TLFluxo*> &lst, int i, int j,char *path) 
  {
    TFluxo *no;
    TSIp *p;
    char str[500]="";
    char option[4]="";
    
    memcpy(option,id,3);
    option[3]='\0';
    no=(TFluxo *)mallocX(sizeof(TFluxo),"doBC",path);
    list<TLFluxo*>::iterator itrp;
    map<string,TSIp*>::iterator itrq;
    //map<string,TSIp*> &htAsrcIP=*(new map<string,TSIp*>);
    //map<string,TSIp*> &htAdstIP=*(new map<string,TSIp*>);
    //map<string,TSIp*> &htAsrcPrt=*(new map<string,TSIp*>);
    //map<string,TSIp*> &htAdstPrt=*(new map<string,TSIp*>);
    map<string,TSIp*> &htX=*(new map<string,TSIp*>);
    map<string,TSIp*> &htY=*(new map<string,TSIp*>);
    map<string,TSIp*> &htZ=*(new map<string,TSIp*>);
    htX.begin();
    htY.begin();
    htZ.begin();
    if(i) {
      if(j) {
        //Vc estah em strcpy(str,"./resultados/DST_PRT.txt");
        itrq=ht.begin();
        while(itrq!=ht.end()){
          p=itrq->second;
          itrp=lst.begin();
          while(itrp!=lst.end()){
            cpTLFtoTF(*itrp,no);
            if(!(memcmp(&(p->port),&(no->dst_port),2))) {
	      //src
              metsTFluxoProfIP(flag,no,htY,0,path);
	      //dst
	      metsTFluxoProfIP(flag,no,htZ,1,path);
	      metsTFluxoProfPrt(flag,no,htX,0,path);
	      //metsTFluxoProfPrt(flag,no,htAdstPrt,1,path);
            }
            itrp++;
          }
          contaPD(htX);
          contaPD(htY);
          contaPD(htZ);
          p->id=getID(getRU(htX,path),getRU(htY,path),getRU(htZ,path),1,0,0);
	  p->precisao=(p->n_bytes_p2p)/(p->n_bytes);
          sprintf(str,"%s,%d,%u,%.0f,%.0f,%.6f,%.0f,%.0f,%.0f,%.6f,%.0f\n",id,ntohs(p->port),p->id,p->mi_p2p,p->n_bytes_p2p,p->tempo_p2p,p->frames_p2p,p->mi,p->n_bytes,p->tempo,p->frames);
          gravaLogS (str, i, j,option,path);
          zeraTabela(htX,1);
          zeraTabela(htY,0);
          zeraTabela(htZ,0);
          itrq++;
        }
        

      } else {
        //Agora vc estah em strcpy(str,"./resultados/SRC_PRT.txt");
        itrq=ht.begin();
        while(itrq!=ht.end()){
          p=itrq->second;
          itrp=lst.begin();
          while(itrp!=lst.end()){
            cpTLFtoTF(*itrp,no);
            if(!(memcmp(&(p->port),&(no->src_port),2))) {
              metsTFluxoProfIP(flag,no,htY,0,path);
	      metsTFluxoProfIP(flag,no,htZ,1,path);
	      metsTFluxoProfPrt(flag,no,htX,1,path);
            }
            itrp++;
          }
          contaPD(htX);
          contaPD(htY);
          contaPD(htZ);
          p->id=getID(getRU(htX,path),getRU(htY,path),getRU(htZ,path),1,0,0);
	  p->precisao=(p->n_bytes_p2p)/(p->n_bytes);
          sprintf(str,"%s,%d,%u,%.0f,%.0f,%.6f,%.0f,%.0f,%.0f,%.6f,%.0f\n",id,ntohs(p->port),p->id,p->mi_p2p,p->n_bytes_p2p,p->tempo_p2p,p->frames_p2p,p->mi,p->n_bytes,p->tempo,p->frames);
          gravaLogS (str, i, j,option,path);
          zeraTabela(htX,1);
          zeraTabela(htY,0);
          zeraTabela(htZ,0);
          itrq++;
        }
        

        //mark 
      }
    } else {
      if(j) {
        //strcpy(str,"./resultados/DST_IP.txt");
        itrq=ht.begin();
        while(itrq!=ht.end()){
          p=itrq->second;
          itrp=lst.begin();
          while(itrp!=lst.end()){
            cpTLFtoTF(*itrp,no);
            if(!(memcmp(&(p->ip),&(no->ip_dst),4))) {
              metsTFluxoProfPrt(flag,no,htY,1,path);
	      metsTFluxoProfIP(flag,no,htZ,0,path);
	      metsTFluxoProfPrt(flag,no,htX,0,path);
            }
            itrp++;
          }
          contaPD(htX);
          contaPD(htY);
          contaPD(htZ);
          p->id=getID(getRU(htX,path),getRU(htY,path),getRU(htZ,path),1,1,0);
	  p->precisao=(p->n_bytes_p2p)/(p->n_bytes);
          sprintf(str,"%s,%s,%u,%.0f,%.0f,%.6f,%.0f,%.0f,%.0f,%.6f,%.0f\n",id,inet_ntoa(p->ip),p->id,p->mi_p2p,p->n_bytes_p2p,p->tempo_p2p,p->frames_p2p,p->mi,p->n_bytes,p->tempo,p->frames);
          gravaLogS (str, i, j,option,path);
          zeraTabela(htX,1);
          zeraTabela(htY,1);
          zeraTabela(htZ,0);
          itrq++;
        }
        

      } else {
        //strcpy(str,"./resultados/SRC_IP.txt");
        itrq=ht.begin();
        while(itrq!=ht.end()){
          p=itrq->second;
          itrp=lst.begin();
          while(itrp!=lst.end()){
            cpTLFtoTF(*itrp,no);
            if(!(memcmp(&(p->ip),&(no->ip_src),4))) {
              metsTFluxoProfPrt(flag,no,htY,1,path);
	      metsTFluxoProfIP(flag,no,htZ,1,path);
	      metsTFluxoProfPrt(flag,no,htX,0,path);
            }
            itrp++;
          }
          contaPD(htX);
          contaPD(htY);
          contaPD(htZ);
          p->id=getID(getRU(htX,path),getRU(htY,path),getRU(htZ,path),1,1,0);
	  p->precisao=(p->n_bytes_p2p)/(p->n_bytes);
          sprintf(str,"%s,%s,%u,%.0f,%.0f,%.6f,%.0f,%.0f,%.0f,%.6f,%.0f\n",id,inet_ntoa(p->ip),p->id,p->mi_p2p,p->n_bytes_p2p,p->tempo_p2p,p->frames_p2p,p->mi,p->n_bytes,p->tempo,p->frames);
          gravaLogS (str, i, j,option,path);
          zeraTabela(htX,1);
          zeraTabela(htY,1);
          zeraTabela(htZ,0);
          itrq++;
        }
        
      }
    }
    removeS(no);
    delete &htX;
    delete &htY;
    delete &htZ;
  } 
void
doAlgorithm1(char *id, map<string,TSIp*> &htA, map<string,TSIp*> &htS, int i,int j,double bt, char *path)
  {
    TSIp *a;
    char str[500]="";
    char option[4]="";
   
    memcpy(option,id,3); 
    option[3]='\0';
    map<string,TSIp*> &htR=*(new map<string,TSIp*>);
    //map<string,TSIp*>::iterator itrp;
    map<string,TSIp*>::iterator itrpq;
    //calculo da distribuicao de probabilidade para o conjunto A
    //fazer isso antes de copiar para o grupo R, para economizar processamento
    //printf("relatorio de testes dentro do Algoritimo 1:\n");
    //printf("O valor de m eh: %.0f\n",cstime->m);
    contaBPDBytes(htA);
    //parametros e inicializacao
    double alfa, alfa0,beta;
    int k;
    alfa0=(0.02); alfa=alfa0; beta=(bt);
    //inicializacao, considera-se que S e R estao zeradas
    //nao eh necessario contabilizar o Pr nesse ponto, pois aqui eh o mesmo de A
    copyTableAtoR(htA,htR,i,path); k=0; /*contaPD('R');*/
    //calculo da incerteza relativa RU de Pr e de theta
    //primeiro, calcula-se a entropia de A que nao mudarah
    double entropia=getEntropia(htA);
    double h0=getEntropia(htA);
    double modulo=contaTable(htR);
    if(modulo<2) modulo=2;
    double ru=((entropia)/(log2(modulo)));
    double theta=ru;
    //printf("Antes do while->Resultados das variaveis na primeira iteracao:\n H(A)=%.6f\nalfa=%.6f\nmodulo=%.6f\ntheta=%.6f\n",entropia,alfa,modulo,theta);
    //printf("Para aqui 1 theta:%.6f e beta:%.6f\n",theta,beta);
    while(theta<=beta) {
      //printf("Para aqui 2\n");
      k++;
      //printf("Resultados das variaveis na %d iteracao:\n H(A)=%.6f\nalfa=%.6f\nmodulo=%.6f\ntheta=%.6f\n",k,entropia,alfa,modulo,theta);
      //pourCordeTable('A');pourCordeTable('R');pourCordeTable('S');
      //getchar();
      if(htR.size()==0) break;
      itrpq=htR.begin();
      while(itrpq!=htR.end()){
        a=itrpq->second;
        itrpq++;
        if((getPD(htA,a,i))>=alfa) {
          htS[faisCleProf(a,i)] = a;
          removeNOs(htR,a,i);
	}
      }
      alfa= ( (alfa) * (pow(2,(-1))) );
      modulo=contaTable(htR);
      if(modulo<2) modulo=2;
      ru=((entropia)/(log2(modulo)));
      theta=ru;
      contaBPDBytes(htR);
      entropia=getEntropia(htR); 
    }
    u_int length = contaTable(htA);
    strcpy(str,"");
    if(length<2)
      sprintf(str,"%d,%d,%.6f,%.6f,%.6f\n",length,contaTable(htS),alfa,h0,(h0/1));
    else
      sprintf(str,"%d,%d,%.6f,%.6f,%.6f\n",length,contaTable(htS),alfa,h0,(h0/log2(length)));
    gravaLogH (str, i, j,option,path);
    //delete hash tables
    zeraTabela(htR,i); 
    //zeraTabela(htS,i);
    delete &htR; 
    //delete &htS; 
  }
double
log2( double num)
{
        return ((log(num))/(log(2) ));
}
void deleteFiles(char *option, char *path)
  {
    deleteFileH(0,0,option,path);
    deleteFileH(0,1,option,path);
    deleteFileH(1,0,option,path);
    deleteFileH(1,1,option,path);
    deleteFileS(0,0,option,path);
    deleteFileS(0,1,option,path);
    deleteFileS(1,0,option,path);
    deleteFileS(1,1,option,path);
  }
void inicializaFiles(char *option,char *path)
  {
    char str[500]="";
    strcpy(str,"");
    sprintf(str,"nA,nS,alpha,Ha,RUa\n");
    gravaLogH (str, 0, 0,option,path);
    gravaLogH (str, 0, 1,option, path);
    gravaLogH (str, 1, 0,option, path);
    gravaLogH (str, 1, 1,option, path);
    strcpy(str,"");
    sprintf(str,"iteracao,chave,id,nr_fluxos_p2p,volume_p2p,tempo_p2p,nr_pacotes_p2p,nr_fluxos,volume,tempo,nr_pacotes\n");
    gravaLogS (str, 0, 0,option,path);
    gravaLogS (str, 0, 1,option,path);
    gravaLogS (str, 1, 0,option,path);
    gravaLogS (str, 1, 1,option,path);
  }
void doProcess(char *listfile, char *option,u_int i, int iteracao, double bt, char *path, map<string,TSIp*> &htGeralBCsrcIP, map<string,TSIp*> &htGeralBCsrcPrt, map<string,TSIp*> &htGeralBCdstIP, map<string,TSIp*> &htGeralBCdstPrt, T8Double *tdGeral){
  deleteFiles(option,path);
  inicializaFiles(option,path);
  chargeListe(option,listfile,i,iteracao,bt,path,htGeralBCsrcIP,htGeralBCsrcPrt,htGeralBCdstIP,htGeralBCdstPrt, tdGeral);
} 

//convencoes para as funcoes abaixo
//i representa se eh porta ou endereco: 0 enderecos IP e diferente de zero portas
//j representa de eh de origem ou destino: 0 para de origem e direfente de zero para de destino
void gravaLogH (char *ch, int i, int j, char *option,char *path)
 {
   FILE *logs;
   char str[256]="";
   if(i) {
     if(j) snprintf(str,256,"%s/resultados/%s_DST_PRT.txt",path,option);
     else snprintf(str,256,"%s/resultados/%s_SRC_PRT.txt",path,option);
   } else {
     if(j) snprintf(str,256,"%s/resultados/%s_DST_IP.txt",path,option);
     else snprintf(str,256,"%s/resultados/%s_SRC_IP.txt",path,option);
   }
   logs = abreArquivoAplus(str,path);
   fprintf(logs,"%s",ch);
   fechaArquivo(logs);
 }
//convencoes para as funcoes abaixo
//i representa se eh porta ou endereco: 0 enderecos IP e diferente de zero portas
//j representa de eh de origem ou destino: 0 para de origem e direfente de zero para de destino
void gravaLogS (char *ch, int i, int j, char *option, char *path)
 {
   FILE *logs;
   char str[256]="";
   if(i) {
     if(j) snprintf(str,256,"%s/resultados/%s_TS_DST_PRT.txt",path,option);
     else snprintf(str,256,"%s/resultados/%s_TS_SRC_PRT.txt",path,option);
   } else {
     if(j) snprintf(str,256,"%s/resultados/%s_TS_DST_IP.txt",path,option);
     else snprintf(str,256,"%s/resultados/%s_TS_SRC_IP.txt",path,option);
   }
   logs = abreArquivoAplus(str,path);
   fprintf(logs,"%s",ch);
   fechaArquivo(logs);
 }

int deleteFileS(int i,int j, char *option,char *path)
  {
    
    char str[256]="";
    if(i) {
      if(j) snprintf(str,256,"%s/resultados/%s_TS_DST_PRT.txt",path,option);
      else snprintf(str,256,"%s/resultados/%s_TS_SRC_PRT.txt",path,option);
    } else {
      if(j) snprintf(str,256,"%s/resultados/%s_TS_DST_IP.txt",path,option);
      else snprintf(str,256,"%s/resultados/%s_TS_SRC_IP.txt",path,option);
    }
    if (existFile(str))
      return remove(str);
    return 0;
  }


int deleteFileH(int i,int j,char *option,char *path)
  {
    
    char str[256]="";
    if(i) {
      if(j) snprintf(str,256,"%s/resultados/%s_DST_PRT.txt",path,option);
      else snprintf(str,256,"%s/resultados/%s_SRC_PRT.txt",path,option);
    } else {
      if(j) snprintf(str,256,"%s/resultados/%s_DST_IP.txt",path,option);
      else snprintf(str,256,"%s/resultados/%s_SRC_IP.txt",path,option);
    }
    if (existFile(str))
      return remove(str);
    return 0;
  }

void geraResultado(TFluxo *p)
  {
//    results = abreArquivoAplus(filename,path);
//    m++;
    printf("%.0f",(double)((p)->ini_sec));
    printf(",%.0f",(double)((p)->ini_mil));
    printf(",%.0f",(double)((p)->end_sec));
    printf(",%.0f",(double)((p)->end_mil));
    printf(",%s",inet_ntoa((p)->ip_src));
    printf(",%d",ntohs((p)->src_port));
    printf(",%s",inet_ntoa((p)->ip_dst));
    printf(",%d",ntohs((p)->dst_port));
    printf(",%.0f",(p)->n_bytes);
    printf(",%.0f",(p)->n_frames);
    printf(",%d",(p)->tipo);
    printf(",%d\n",(p)->rumo);
//    t_bytes_p2p = t_bytes_p2p + (p->prox)->n_bytes;
    //removeS(p);
    //fechaArquivo(results);
  }
void metsTLFluxo(TFluxo *nova, list<TLFluxo*> &lst, char *path) {
    TLFluxo *no;

    no=(TLFluxo *)mallocX(sizeof(TLFluxo),"metsTLFluxo",path);
    no->tempo=donneTempsIntervalle(nova);
    no->ip_src=nova->ip_src;
    no->ip_dst=nova->ip_dst;
    no->src_port=nova->src_port;
    no->dst_port=nova->dst_port;
    no->n_bytes=nova->n_bytes;
    no->n_frames=nova->n_frames;
    no->tipo=nova->tipo;
    lst.push_back(no);
}

void enleveTLFluxo(TLFluxo *p)
  {
    free(p);
  }

void
zeraLista(list<TLFluxo*> &lst)
  {
    list<TLFluxo*>::iterator itrp;

    itrp=lst.begin();
    while(itrp!=lst.end()){
      enleveTLFluxo(*itrp);
      itrp++;
    }
    lst.clear();
  }

void cpTLFtoTF(TLFluxo *nova, TFluxo *no) {

    no->ip_src=nova->ip_src;
    no->ip_dst=nova->ip_dst;
    no->src_port=nova->src_port;
    no->dst_port=nova->dst_port;
    no->n_bytes=nova->n_bytes;
    no->n_frames=nova->n_frames;
    no->tipo=nova->tipo;
    no->ini_sec=0;
    no->ini_mil=0;
    no->end_sec=(time_t)nova->tempo;
    no->end_mil=0;
}

int
estSorteP2P(u_int sorte)
  {
    if( ((sorte)>=1)&&((sorte)<=11) ) return 1;
    if( ((sorte)>=21)&&((sorte)<=23) ) return 1;
    if( ((sorte)>=27)&&((sorte)<=28) ) return 1;
    if( ((sorte)==30)) return 1;
    return 0;
  }
int
estSorteKazaa(u_int sorte)
  {
    if( ((sorte)==1)||((sorte)==21) ) return 1;
    return 0;
  }
int
estSorteDonkey(u_int sorte)
  {
    if( ((sorte)==2)||((sorte)==22) ) return 1;
    return 0;
  }
int
estSorteBittorrent(u_int sorte)
  {
    if( ((sorte)==4) ) return 1;
    return 0;
  }
int
estautreP2P(u_int sorte)
  {
    if((estSorteP2P(sorte))&&(!(estSorteKazaa(sorte)))&&(!(estSorteDonkey(sorte)))&&(!(estSorteBittorrent(sorte)))) return 1;
    return 0;
  }
int
estespecialP2P(u_int sorte)
  {
    if((estSorteP2P(sorte))&&(!(estSorteDonkey(sorte)))&&(!(estSorteBittorrent(sorte)))) return 1;
    return 0;
  }
double
donneTempsIntervalle(TFluxo *tr)
  {
    return (((double)(tr->end_sec)+((double)(tr->end_mil)/1000000))-((double)(tr->ini_sec)+((double)(tr->ini_mil)/1000000)));
  }
int
isToProcess(char *id,u_int tipo)
  {
    //o passo seguinte deicha passar tudo, eh o caso de p2p dentro do tudo
    if( (!(memcmp(id,"a2p",3))) ) return 1;
    if( (!(memcmp(id,"all",3))) ) return 1;
    if( (!(memcmp(id,"p2p",3))) )
      if(estSorteP2P(tipo)) return 1;
    if( (!(memcmp(id,"edk",3))) )
      if(estSorteDonkey(tipo)) return 1;
    if( (!(memcmp(id,"bit",3))) )
      if(estSorteBittorrent(tipo)) return 1;
    if( (!(memcmp(id,"kaz",3))) )
      if(estSorteKazaa(tipo)) return 1;
    if( (!(memcmp(id,"aut",3))) )
      if(estautreP2P(tipo)) return 1;
    if( (!(memcmp(id,"esp",3))) )
      if(estespecialP2P(tipo)) return 1;
    return 0;
  }
int isInvalid(char c)
  {
    int i = (int) c;
    if( ( (i>47)&&(i<58) )||(i==44)||(i==10)||(i==46) ) return 0;
    return 1;
  }

void
doScan(char *id, map<string,TSIp*> &htsrcIP, map<string,TSIp*> &htsrcPrt, map<string,TSIp*> &htdstIP, map<string,TSIp*> &htdstPrt,list<TLFluxo*> &lst, map<string,TSIp*> &htBCsrcIP, map<string,TSIp*> &htBCsrcPrt, map<string,TSIp*> &htBCdstIP, map<string,TSIp*> &htBCdstPrt, T8Double *td, char *path) {
    	char str[1024]="";
        TFluxo *no=(TFluxo *)mallocX(sizeof(TFluxo),"doScan",path);
	list<TLFluxo*>::iterator itrp;
	itrp=lst.begin();
        T8Double *td1 = (T8Double *)mallocX(sizeof(T8Double),"doScan",path);
        T8Double *td2 = (T8Double *)mallocX(sizeof(T8Double),"doScan",path);
        T8Double *td3 = (T8Double *)mallocX(sizeof(T8Double),"doScan",path);
        T8Double *td4 = (T8Double *)mallocX(sizeof(T8Double),"doScan",path);
        T8Double *td5 = (T8Double *)mallocX(sizeof(T8Double),"doScan",path);
        T8Double *td6 = (T8Double *)mallocX(sizeof(T8Double),"doScan",path);
        T8Double *td7 = (T8Double *)mallocX(sizeof(T8Double),"doScan",path);
        T8Double *td8 = (T8Double *)mallocX(sizeof(T8Double),"doScan",path);
        T8Double *td9 = (T8Double *)mallocX(sizeof(T8Double),"doScan",path);
        T8Double *td10 = (T8Double *)mallocX(sizeof(T8Double),"doScan",path);
        T8Double *td11 = (T8Double *)mallocX(sizeof(T8Double),"doScan",path);
        T8Double *tdX = (T8Double *)mallocX(sizeof(T8Double),"doScan",path);
        T8Double *td12 = (T8Double *)mallocX(sizeof(T8Double),"doScan",path);
        T8Double *td13 = (T8Double *)mallocX(sizeof(T8Double),"doScan",path);
        T8Double *td14 = (T8Double *)mallocX(sizeof(T8Double),"doScan",path);
        T8Double *td15 = (T8Double *)mallocX(sizeof(T8Double),"doScan",path);
        T8Double *td16 = (T8Double *)mallocX(sizeof(T8Double),"doScan",path);
	initT8Double(td1);
	initT8Double(td2);
	initT8Double(td3);
	initT8Double(td4);
	initT8Double(td5);
	initT8Double(td6);
	initT8Double(td7);
	initT8Double(td8);
	initT8Double(td9);
	initT8Double(td10);
	initT8Double(td11);
	initT8Double(td12);
	initT8Double(td13);
	initT8Double(td14);
        initT8Double(td15);
        initT8Double(td16);
	//Processamento das tabelas BCs
	//begin
//	printf("tamanho de htsrcIP: %lu e tamanho de htBCsrcIP: %lu\n",htsrcIP.size(),htBCsrcIP.size());
	addTStoBC(htsrcIP,htBCsrcIP,path); 
//	printf("tamanho de htsrcIP: %lu e tamanho de htBCsrcIP: %lu\n",htsrcIP.size(),htBCsrcIP.size());
	addTStoBC(htdstIP,htBCdstIP,path); 
	addTStoBC(htsrcPrt,htBCsrcPrt,path); 
	addTStoBC(htdstPrt,htBCdstPrt,path); 
	//end
	int flag = 0;
	itrp=lst.begin();
        int uniao=0;
        int uniao2=0;
        int uniao3=0;
	int bandeira=0;
	int key1=0,key2=0,key3=0,key4=0;
	int sum=0;
	double erro1=0, erro2=0, erro3=0,erro4=0,erro5=0,erro6=0,erro7=0,erro8=0,erro9=0,erro10=0;
	while(itrp!=lst.end()){
		key3=0;key4=0;
		initT8Double(tdX);
        	cpTLFtoTF(*itrp,no);
		flag=isToProcess(id,no->tipo);
		tdX->mi=1;
		tdX->n_bytes=no->n_bytes;
		tdX->tempo=(*itrp)->tempo;
		tdX->frames=no->n_frames;
                uniao=0;
                uniao2=0;
                uniao3=0;
		bandeira=0;
		if(flag) {
			tdX->mi_p2p=1;
                	tdX->n_bytes_p2p=no->n_bytes;
                	tdX->tempo_p2p=tdX->tempo;
                	tdX->frames_p2p=no->n_frames;
		}
		//tipo 1 - srcIP e dstIP
		sum=0;
		key1=isThereintoBC(htsrcIP, no, 0, 0);
		if(key1) {
			if(key1==1) {
				key2=isThereintoBC(htdstIP, no, 0, 1);
				if(key2==1||key2==2) {
					if(!flag) erro1+=no->n_bytes;
					addT8Double(tdX,td1);
                        		uniao++;
                        		uniao2++;
				} else {
					key3=isThereintoBC(htsrcPrt,no,1,0);
					key4=isThereintoBC(htdstPrt,no,1,1);
					if(key2) { //ou seja, igual a tres
						if(((key3>=1)&&(key3<=3))||((key4>=1)&&(key4<=3))) {
							if(!flag) erro7+=no->n_bytes;
							addT8Double(tdX,td1);
                        				uniao++;
                        				uniao2++;
						}
					} else { //senao, quanto for 0
						if(((key3>=1)&&(key3<=2))||((key4>=1)&&(key4<=2))) {
							if(!flag) erro10+=no->n_bytes;
							addT8Double(tdX,td1);
                        				uniao++;
                        				uniao2++;
						}
					}
				}
			} else {
				key2=isThereintoBC(htdstIP, no, 0, 1);
				if(key2) {
					if(key2==1) {
						if(key1==2) {
							if(!flag) erro5+=no->n_bytes;
							addT8Double(tdX,td1);
                        				uniao++;
                        				uniao2++;
						} else {
							key3=isThereintoBC(htsrcPrt,no,1,0);
							key4=isThereintoBC(htdstPrt,no,1,1);
							if(((key3>=1)&&(key3<=3))||((key4>=1)&&(key4<=3))) {
								if(!flag) erro2+=no->n_bytes;
								addT8Double(tdX,td1);
                        					uniao++;
                        					uniao2++;
							}
						}
					} else {
						sum=key1+key2;
						key3=isThereintoBC(htsrcPrt,no,1,0);
						key4=isThereintoBC(htdstPrt,no,1,1);
						if(sum==4) {
							if(((key3>=1)&&(key3<=2))||((key4>=1)&&(key4<=2))) {
								if(!flag) erro3+=no->n_bytes;
								addT8Double(tdX,td1);
                        					uniao++;
                        					uniao2++;
							}
						} else {
							if(sum==5) {
								key3=isThereintoBC(htsrcPrt,no,1,0);
								key4=isThereintoBC(htdstPrt,no,1,1);
								if((key3==1)||(key4==1)) {
									if(!flag) erro4+=no->n_bytes;
									addT8Double(tdX,td1);
                        						uniao++;
                        						uniao2++;
								}
							}
						}
						
					}
				} else {
					if(key1==2) {
						key3=isThereintoBC(htsrcPrt,no,1,0);
						key4=isThereintoBC(htdstPrt,no,1,1);
						if((key3==1)||(key4==1)) {
							if(!flag) erro6+=no->n_bytes;
							addT8Double(tdX,td1);
                        				uniao++;
                        				uniao2++;
						}
					}
				}
			}
		} else {
			key2=isThereintoBC(htdstIP, no, 0, 1);
			if(key2) {
				if(key2==1) {
					key3=isThereintoBC(htsrcPrt,no,1,0);
					key4=isThereintoBC(htdstPrt,no,1,1);
					if(((key3>=1)&&(key3<=2))||((key4>=1)&&(key4<=2))) {
						if(!flag) erro8+=no->n_bytes;
						addT8Double(tdX,td1);
                        			uniao++;
                        			uniao2++;
					}
				} else {
					if(key2==2) {
						key3=isThereintoBC(htsrcPrt,no,1,0);
						key4=isThereintoBC(htdstPrt,no,1,1);
						if((key3==1)||(key4==1)) {
							if(!flag) erro9+=no->n_bytes;
							addT8Double(tdX,td1);
                        				uniao++;
                        				uniao2++;
						}
					}
				}
			}
		}

		//tipo 2 - srcIP e dstIP e srcPrt
		if( (isThereintoBC(htsrcIP, no, 0, 0)) && (isThereintoBC(htdstIP, no, 0, 1)) && (isThereintoBC(htsrcPrt, no, 1, 0)) ) {
			addT8Double(tdX,td2);
			bandeira++;
		} 
		//tipo 3 - srcIP e dstIP e dstPrt
		if( (isThereintoBC(htsrcIP, no, 0, 0)) && (isThereintoBC(htdstIP, no, 0, 1)) && (isThereintoBC(htdstPrt, no, 1, 1)) ) {
			addT8Double(tdX,td3);
			bandeira++;
		} 
		//tipo 4 - srcIP e srcPrt
		/*if( (isThereintoBC(htsrcIP, no, 0, 0)) && (isThereintoBC(htsrcPrt, no, 1, 0)) ) {
			addT8Double(tdX,td4);
		}*/ 
		key1=isThereintoBC(htsrcIP, no, 0, 0);
		if(key1) {
			if(key1==1) {
				addT8Double(tdX,td4);
                       		uniao++;
                        	uniao2++;
                        	uniao3++;
			} else {
				key2=isThereintoBC(htsrcPrt, no, 1, 0);
				if(key2==1) {
					addT8Double(tdX,td4);
                       			uniao++;
                        		uniao2++;
                        		uniao3++;
				} else {
					if((isThereintoBC(htdstIP, no, 0, 1)==1) || (isThereintoBC(htdstPrt,no,1,1)==1) ) {
						addT8Double(tdX,td4);
                       				uniao++;
                        			uniao2++;
                        			uniao3++;
					} 
				}
			}
		} 
		//tipo 5 - srcIP e srcPrt e dstPrt
		if( (isThereintoBC(htsrcIP, no, 0, 0)) && (isThereintoBC(htsrcPrt, no, 1, 0)) && (isThereintoBC(htdstPrt, no, 1, 1)) ) {
			addT8Double(tdX,td5);
		} 
		//tipo 6 - srcIP e dstPrt
		if( (isThereintoBC(htsrcIP, no, 0, 0)) && (isThereintoBC(htdstPrt, no, 1, 1)) ) {
			addT8Double(tdX,td6);
		} 
		//tipo 7 - dstIP e srcPrt
		if( (isThereintoBC(htdstIP, no, 0, 1)) && (isThereintoBC(htsrcPrt, no, 1, 0)) ) {
			addT8Double(tdX,td7);
                        uniao2++;
		} 
		//tipo 8 - dstIP e srcPrt e dstPrt
		if( (isThereintoBC(htdstIP, no, 0, 1)) && (isThereintoBC(htsrcPrt, no, 1, 0)) && (isThereintoBC(htdstPrt, no, 1, 1)) ) {
			addT8Double(tdX,td8);
		} 
		//tipo 9 - dstIP e dstPrt
		/*if( (isThereintoBC(htdstIP, no, 0, 1)) && (isThereintoBC(htdstPrt, no, 1, 1)) ) {
			addT8Double(tdX,td9);
		}*/ 
		key1=isThereintoBC(htdstIP, no, 0, 1);
		if(key1) {
			if(key1==1) {
				addT8Double(tdX,td9);
	                        uniao++;
                        	uniao2++;
                        	uniao3++;
			} else {
				key2=isThereintoBC(htdstPrt, no, 1, 1);
				if(key2==1) {
					addT8Double(tdX,td9);
	                        	uniao++;
                        		uniao2++;
                        		uniao3++;
				} else {
					if((isThereintoBC(htsrcIP, no, 0, 0)==1) || (isThereintoBC(htsrcPrt,no,1,0)==1) ) {
						addT8Double(tdX,td9);
	                        		uniao++;
                        			uniao2++;
                        			uniao3++;
					} 
				}
			}
		} 
		//tipo 10 - dstPrt e srcPrt
		if( (isThereintoBC(htdstPrt, no, 1, 1)) && (isThereintoBC(htsrcPrt, no, 1, 0)) ) {
			addT8Double(tdX,td10);
		} 
		//tipo 11 - dstIP e srcIP e dstPrt e srcPrt
		if( (isThereintoBC(htsrcIP, no, 0, 0)) && (isThereintoBC(htdstIP, no, 0, 1)) && (isThereintoBC(htdstPrt, no, 1, 1)) && (isThereintoBC(htsrcPrt, no, 1, 0)) ) {
			addT8Double(tdX,td11);
			bandeira++;
		}
                //tipo 12 - uniao de 11, 2, 3
                if(bandeira) addT8Double(tdX,td12);
                //tipo 13 - uniao 1,4,9
                if(uniao) addT8Double(tdX,td13);
                //tipo 14 - uniao 1,7,4,9
                if(uniao2) addT8Double(tdX,td14);
                //tipo 15 - 4,9
                if(uniao3) addT8Double(tdX,td15);
                //tipo 16 - TUDO
                addT8Double(tdX,td16);
		itrp++;
        }
        sprintf(str,"%s,%s,%u,%.0f,%.0f,%.6f,%.0f,%.0f,%.0f,%.6f,%.0f,%.6f,%.6f,%.6f,%.6f",id,"#->#",1,td1->mi_p2p,td1->n_bytes_p2p,td1->tempo_p2p,td1->frames_p2p,td1->mi,td1->n_bytes,td1->tempo,td1->frames,((td1->n_bytes_p2p)/(td1->n_bytes)),((td1->n_bytes_p2p)/(td16->n_bytes_p2p)),((td1->mi_p2p)/(td1->mi)),((td1->mi_p2p)/(td16->mi_p2p)));
        gravaLog(str,path);
        sprintf(str,"%s,%s,%u,%.0f,%.0f,%.6f,%.0f,%.0f,%.0f,%.0f,%.0f,%.0f,%.0f",id,"#-AUX>#",1,erro1,erro2,erro3,erro4,erro5,erro6,erro7,erro8,erro9,erro10);
        gravaLog(str,path);
        sprintf(str,"%s,%s,%u,%.0f,%.0f,%.6f,%.0f,%.0f,%.0f,%.6f,%.0f,%.6f,%.6f,%.6f,%.6f",id,"#->#",2,td2->mi_p2p,td2->n_bytes_p2p,td2->tempo_p2p,td2->frames_p2p,td2->mi,td2->n_bytes,td2->tempo,td2->frames,((td2->n_bytes_p2p)/(td2->n_bytes)),((td2->n_bytes_p2p)/(td16->n_bytes_p2p)),((td2->mi_p2p)/(td2->mi)),((td2->mi_p2p)/(td16->mi_p2p)));
        gravaLog(str,path);
        sprintf(str,"%s,%s,%u,%.0f,%.0f,%.6f,%.0f,%.0f,%.0f,%.6f,%.0f,%.6f,%.6f,%.6f,%.6f",id,"#->#",3,td3->mi_p2p,td3->n_bytes_p2p,td3->tempo_p2p,td3->frames_p2p,td3->mi,td3->n_bytes,td3->tempo,td3->frames,((td3->n_bytes_p2p)/(td3->n_bytes)),((td3->n_bytes_p2p)/(td16->n_bytes_p2p)),((td3->mi_p2p)/(td3->mi)),((td3->mi_p2p)/(td16->mi_p2p)));
        gravaLog(str,path);
        sprintf(str,"%s,%s,%u,%.0f,%.0f,%.6f,%.0f,%.0f,%.0f,%.6f,%.0f,%.6f,%.6f,%.6f,%.6f",id,"#->#",4,td4->mi_p2p,td4->n_bytes_p2p,td4->tempo_p2p,td4->frames_p2p,td4->mi,td4->n_bytes,td4->tempo,td4->frames,((td4->n_bytes_p2p)/(td4->n_bytes)),((td4->n_bytes_p2p)/(td16->n_bytes_p2p)),((td4->mi_p2p)/(td4->mi)),((td4->mi_p2p)/(td16->mi_p2p)));
        gravaLog(str,path);
        sprintf(str,"%s,%s,%u,%.0f,%.0f,%.6f,%.0f,%.0f,%.0f,%.6f,%.0f,%.6f,%.6f,%.6f,%.6f",id,"#->#",5,td5->mi_p2p,td5->n_bytes_p2p,td5->tempo_p2p,td5->frames_p2p,td5->mi,td5->n_bytes,td5->tempo,td5->frames,((td5->n_bytes_p2p)/(td5->n_bytes)),((td5->n_bytes_p2p)/(td16->n_bytes_p2p)),((td5->mi_p2p)/(td5->mi)),((td5->mi_p2p)/(td16->mi_p2p)));
        gravaLog(str,path);
        sprintf(str,"%s,%s,%u,%.0f,%.0f,%.6f,%.0f,%.0f,%.0f,%.6f,%.0f,%.6f,%.6f,%.6f,%.6f",id,"#->#",6,td6->mi_p2p,td6->n_bytes_p2p,td6->tempo_p2p,td6->frames_p2p,td6->mi,td6->n_bytes,td6->tempo,td6->frames,((td6->n_bytes_p2p)/(td6->n_bytes)),((td6->n_bytes_p2p)/(td16->n_bytes_p2p)),((td6->mi_p2p)/(td6->mi)),((td6->mi_p2p)/(td16->mi_p2p)));
        gravaLog(str,path);
        sprintf(str,"%s,%s,%u,%.0f,%.0f,%.6f,%.0f,%.0f,%.0f,%.6f,%.0f,%.6f,%.6f,%.6f,%.6f",id,"#->#",7,td7->mi_p2p,td7->n_bytes_p2p,td7->tempo_p2p,td7->frames_p2p,td7->mi,td7->n_bytes,td7->tempo,td7->frames,((td7->n_bytes_p2p)/(td7->n_bytes)),((td7->n_bytes_p2p)/(td16->n_bytes_p2p)),((td7->mi_p2p)/(td7->mi)),((td7->mi_p2p)/(td16->mi_p2p)));
        gravaLog(str,path);
        sprintf(str,"%s,%s,%u,%.0f,%.0f,%.6f,%.0f,%.0f,%.0f,%.6f,%.0f,%.6f,%.6f,%.6f,%.6f",id,"#->#",8,td8->mi_p2p,td8->n_bytes_p2p,td8->tempo_p2p,td8->frames_p2p,td8->mi,td8->n_bytes,td8->tempo,td8->frames,((td8->n_bytes_p2p)/(td8->n_bytes)),((td8->n_bytes_p2p)/(td16->n_bytes_p2p)),((td8->mi_p2p)/(td8->mi)),((td8->mi_p2p)/(td16->mi_p2p)));
        gravaLog(str,path);
        sprintf(str,"%s,%s,%u,%.0f,%.0f,%.6f,%.0f,%.0f,%.0f,%.6f,%.0f,%.6f,%.6f,%.6f,%.6f",id,"#->#",9,td9->mi_p2p,td9->n_bytes_p2p,td9->tempo_p2p,td9->frames_p2p,td9->mi,td9->n_bytes,td9->tempo,td9->frames,((td9->n_bytes_p2p)/(td9->n_bytes)),((td9->n_bytes_p2p)/(td16->n_bytes_p2p)),((td9->mi_p2p)/(td9->mi)),((td9->mi_p2p)/(td16->mi_p2p)));
        gravaLog(str,path);
        sprintf(str,"%s,%s,%u,%.0f,%.0f,%.6f,%.0f,%.0f,%.0f,%.6f,%.0f,%.6f,%.6f,%.6f,%.6f",id,"#->#",10,td10->mi_p2p,td10->n_bytes_p2p,td10->tempo_p2p,td10->frames_p2p,td10->mi,td10->n_bytes,td10->tempo,td10->frames,((td10->n_bytes_p2p)/(td10->n_bytes)),((td10->n_bytes_p2p)/(td16->n_bytes_p2p)),((td10->mi_p2p)/(td10->mi)),((td10->mi_p2p)/(td16->mi_p2p)));
        gravaLog(str,path);
        sprintf(str,"%s,%s,%u,%.0f,%.0f,%.6f,%.0f,%.0f,%.0f,%.6f,%.0f,%.6f,%.6f,%.6f,%.6f",id,"#->#",11,td11->mi_p2p,td11->n_bytes_p2p,td11->tempo_p2p,td11->frames_p2p,td11->mi,td11->n_bytes,td11->tempo,td11->frames,((td11->n_bytes_p2p)/(td11->n_bytes)),((td11->n_bytes_p2p)/(td16->n_bytes_p2p)),((td11->mi_p2p)/(td11->mi)),((td11->mi_p2p)/(td16->mi_p2p)));
        gravaLog(str,path);
        sprintf(str,"%s,%s,%u,%.0f,%.0f,%.6f,%.0f,%.0f,%.0f,%.6f,%.0f,%.6f,%.6f,%.6f,%.6f",id,"#->#",12,td12->mi_p2p,td12->n_bytes_p2p,td12->tempo_p2p,td12->frames_p2p,td12->mi,td12->n_bytes,td12->tempo,td12->frames,((td12->n_bytes_p2p)/(td12->n_bytes)),((td12->n_bytes_p2p)/(td16->n_bytes_p2p)),((td12->mi_p2p)/(td12->mi)),((td12->mi_p2p)/(td16->mi_p2p)));
        gravaLog(str,path);
        sprintf(str,"%s,%s,%u,%.0f,%.0f,%.6f,%.0f,%.0f,%.0f,%.6f,%.0f,%.6f,%.6f,%.6f,%.6f",id,"#->#",13,td13->mi_p2p,td13->n_bytes_p2p,td13->tempo_p2p,td13->frames_p2p,td13->mi,td13->n_bytes,td13->tempo,td13->frames,((td13->n_bytes_p2p)/(td13->n_bytes)),((td13->n_bytes_p2p)/(td16->n_bytes_p2p)),((td13->mi_p2p)/(td13->mi)),((td13->mi_p2p)/(td16->mi_p2p)));
        gravaLog(str,path);
        sprintf(str,"%s,%s,%u,%.0f,%.0f,%.6f,%.0f,%.0f,%.0f,%.6f,%.0f,%.6f,%.6f,%.6f,%.6f",id,"#->#",14,td14->mi_p2p,td14->n_bytes_p2p,td14->tempo_p2p,td14->frames_p2p,td14->mi,td14->n_bytes,td14->tempo,td14->frames,((td14->n_bytes_p2p)/(td14->n_bytes)),((td14->n_bytes_p2p)/(td16->n_bytes_p2p)),((td14->mi_p2p)/(td16->mi)),((td14->mi_p2p)/(td16->mi_p2p)));
        gravaLog(str,path);
        sprintf(str,"%s,%s,%u,%.0f,%.0f,%.6f,%.0f,%.0f,%.0f,%.6f,%.0f,%.6f,%.6f,%.6f,%.6f",id,"#->#",15,td15->mi_p2p,td15->n_bytes_p2p,td15->tempo_p2p,td15->frames_p2p,td15->mi,td15->n_bytes,td15->tempo,td15->frames,((td15->n_bytes_p2p)/(td15->n_bytes)),((td15->n_bytes_p2p)/(td16->n_bytes_p2p)),((td15->mi_p2p)/(td15->mi)),((td15->mi_p2p)/(td16->mi_p2p)));
        gravaLog(str,path);
        sprintf(str,"%s,%s,%u,%.0f,%.0f,%.6f,%.0f,%.0f,%.0f,%.6f,%.0f,%.6f,%.6f,%.6f,%.6f",id,"#->#",16,td16->mi_p2p,td16->n_bytes_p2p,td16->tempo_p2p,td16->frames_p2p,td16->mi,td16->n_bytes,td16->tempo,td16->frames,((td16->n_bytes_p2p)/(td16->n_bytes)),((td16->n_bytes_p2p)/(td16->n_bytes_p2p)),((td16->mi_p2p)/(td16->mi)),((td16->mi_p2p)/(td16->mi_p2p)));
        gravaLog(str,path);
    	removeS(no);
	addT8Double(td16,td);
	free(td1);
	free(td2);
	free(td3);
	free(td4);
	free(td5);
	free(td6);
	free(td7);
	free(td8);
	free(td9);
	free(td10);
	free(td11);
	free(tdX);
	free(td12);
	free(td13);
	free(td14);
        free(td15);
        free(td16);
}

//i da significado para se serah : 1 destino e 0 para origem
int
isThereintoBC(map<string,TSIp*> &ht, TFluxo *no, int i, int j) {
    TSIp *p;
    if(i) {
      if(j) {
        //Vc estah em strcpy(str,"./resultados/DST_PRT.txt");
	if(ht.find(faisCledesSource(no->ip_src,no->src_port,no->ip_dst,no->dst_port,i,j)) == ht.end()) {
		return 0;
	} else {
        	p=ht[faisCledesSource(no->ip_src,no->src_port,no->ip_dst,no->dst_port,i,j)];
		if((p->id==18)||(p->id==24)||(p->id==25)||(p->id==0)||(p->id==26)||(p->id==17)||(p->id==23)) {
			if((p->id==18)||(p->id==24)) {
				return 1;
			} else {
				if((p->id==25)||(p->id==0)||(p->id==26)) return 2;
				return 3;
			}
		} 
		return 0;
	}
      } else {
        //Agora vc estah em strcpy(str,"./resultados/SRC_PRT.txt");
	if(ht.find(faisCledesSource(no->ip_src,no->src_port,no->ip_dst,no->dst_port,i,j)) == ht.end()) {
		return 0;
	} else {
        	p=ht[faisCledesSource(no->ip_src,no->src_port,no->ip_dst,no->dst_port,i,j)];
		if((p->id==20)||(p->id==17)||(p->id==0)||(p->id==11)||(p->id==23)||(p->id==26)||(p->id==25)) {
			if((p->id==20)||(p->id==17)||(p->id==0)||(p->id==11)||(p->id==23)) {
				return 1;
			} else {
				if((p->id==26)) return 2;
				return 3;
			}
		}
		return 0;
	}
      }
    } else {
      if(j) {
        //strcpy(str,"./resultados/DST_IP.txt");
	if(ht.find(faisCledesSource(no->ip_src,no->src_port,no->ip_dst,no->dst_port,i,j)) == ht.end()) {
		return 0;
	} else {
        	p=ht[faisCledesSource(no->ip_src,no->src_port,no->ip_dst,no->dst_port,i,j)];
		if((p->id==18)||(p->id==0)||(p->id==11)||(p->id==23)||(p->id==26)||(p->id==6)||(p->id==14)||(p->id==24)||(p->id==17)) {
			if((p->id==18)||(p->id==0)||(p->id==11)||(p->id==23)) {
				return 1;
			} else {
				if((p->id==26)||(p->id==6)) return 2;	
				return 3;
			}
		}
		return 0;
	}
      } else {
        //strcpy(str,"./resultados/SRC_IP.txt");
	if(ht.find(faisCledesSource(no->ip_src,no->src_port,no->ip_dst,no->dst_port,i,j)) == ht.end()) {
		return 0;
	} else {
        	p=ht[faisCledesSource(no->ip_src,no->src_port,no->ip_dst,no->dst_port,i,j)];
		if((p->id==5)||(p->id==17)||(p->id==14)||(p->id==26)||(p->id==18)||(p->id==23)||(p->id==0)||(p->id==24)||(p->id==8)||(p->id==6)) {
			if((p->id==5)) {
				return 1;
			} else {
				if((p->id==17)||(p->id==14)||(p->id==26)||(p->id==18)||(p->id==23)||(p->id==0)) return 2;
				return 3;
			}
		} 
		return 0;
	}
      }
    }
}
/*struct tipo_oito_valores_double {
        double mi_p2p;
        n_bytes_p2p;
        tempo_p2p;
        frames_p2p;
        mi;
        n_bytes;
        tempo;
        frames;
};

typedef struct tipo_oito_valores_double T8Double;
*/
void
initT8Double(T8Double *t) {
        t->mi_p2p=0;
        t->n_bytes_p2p=0;
        t->tempo_p2p=0;
        t->frames_p2p=0;
        t->mi=0;
        t->n_bytes=0;
        t->tempo=0;
        t->frames=0;
}
void
addT8Double(T8Double *orig,T8Double *dest) {
        dest->mi_p2p+=orig->mi_p2p;
        dest->n_bytes_p2p+=orig->n_bytes_p2p;
        dest->tempo_p2p+=orig->tempo_p2p;
        dest->frames_p2p+=orig->frames_p2p;
        dest->mi+=orig->mi;
        dest->n_bytes+=orig->n_bytes;
        dest->tempo+=orig->tempo;
        dest->frames+=orig->frames;
}

string faisClepourBC(u_short id)
  {
    
    string str;
    char porta[20]="";
    sprintf(porta,"%d",id);
    str = porta;
  
    return str;
  }

void addValuesTSIp(TSIp *src, TSIp *dst) 
  {
	dst->n_bytes+=src->n_bytes;
	dst->tempo+=src->tempo;
	dst->frames+=src->frames;
	dst->mi+=src->mi;
	dst->n_bytes_p2p+=src->n_bytes_p2p;
	dst->tempo_p2p+=src->tempo_p2p;
	dst->frames_p2p+=src->frames_p2p;
	dst->mi_p2p+=src->mi_p2p;
  }	

void addTStoBC(map<string,TSIp*> &htsrc, map<string,TSIp*> &htdst, char *path) 
  {
     	TSIp *no,*p;
      	map<string,TSIp*>::iterator itr;

      	itr=htsrc.begin();
      	while(itr!=htsrc.end()){
		p=itr->second;
		if(htdst.find(faisClepourBC(p->id))== htdst.end()) {
        		no=(TSIp *)mallocX(sizeof(TSIp),"addTStoBC",path);
        		metsZeroProf(no);
			no->ip=p->ip;
			no->id=p->id;
        		no->port=p->port;
			addValuesTSIp(p,no);
			htdst[faisClepourBC(p->id)]=no;
		} else {
			no=htdst[faisClepourBC(p->id)];
			addValuesTSIp(p,no);
		}
        	itr++;
      	}
	
  }
void printHTBCLog(map<string,TSIp*> &ht, char *desc, char *path)
  {
    	char str[1024]="";
     	TSIp *td1;
      	map<string,TSIp*>::iterator itr;
      	itr=ht.begin();
	//printf("cheguei aqui - %s %d\n",desc,ht.size());
      	while(itr!=ht.end()){
	//printf("cheguei aqui\n");
		td1=itr->second;
        	sprintf(str,"%u,%s,%s,%.0f,%.0f,%.6f,%.0f,%.0f,%.0f,%.6f,%.0f,%.4f,%.4f,%.4f,%.4f",td1->id,"#<>#",desc,td1->mi_p2p,td1->n_bytes_p2p,td1->tempo_p2p,td1->frames_p2p,td1->mi,td1->n_bytes,td1->tempo,td1->frames,td1->mi_p2p/td1->mi,td1->n_bytes_p2p/td1->n_bytes,td1->tempo_p2p/td1->tempo,td1->frames_p2p/td1->frames);
        	gravaLog(str,path);
        	itr++;
	}
	//printf("cheguei aqui\n");
	
  }

void sort(map<string,TSIp*> &ht, char *desc,T8Double *td, char *path) {
	list <SelectBC_COMP> LD;
	list <SelectBC_ACCU> L;
	list <SelectBC_ACCU> LE;
	SelectBC_COMP Ablob;
	SelectBC_ACCU accu;
	map<string,TSIp*>::iterator itr;
	char str[1024]="";
	TSIp *td1;
	
	itr=ht.begin();
	while(itr!=ht.end()){
		td1=itr->second;
		Ablob.id=td1->id;
		Ablob.precisao=td1->n_bytes_p2p/td1->n_bytes;
		Ablob.eficiencia=td1->n_bytes_p2p/td->n_bytes_p2p;
		LD.push_back(Ablob);
		itr++;
	}
	LD.sort();
	list<SelectBC_COMP>::iterator iD;
	int n=1;
	double sum=0;
	for(iD=LD.begin(); iD != LD.end(); ++iD) sum+=(*iD).eficiencia;
	//limiar de eficiencia
	double threshold_COMP=0.01345;
        for(iD=LD.begin(); iD != LD.end(); ++iD) {
		//L.push_front((*iD));
		if(  (((*iD).eficiencia)/sum)> threshold_COMP) {
			n++;
			accu.id=(*iD).id;
			accu.precisao=(*iD).precisao;
			accu.eficiencia=(*iD).eficiencia;
			L.push_front((accu));
		} else {
			sprintf(str,"%s,%s,%d,%.4f,%.4f", "<<0>>",desc,(*iD).id,(*iD).precisao,(*iD).eficiencia);
			gravaLog(str,path);
		}
	}
	//sprintf(str,"<<>>Classes de primeira linha para a dimensao %s:",desc);
	//gravaLog(str,path);
	list<SelectBC_ACCU>::iterator i;
	int count = 1;
	L.sort();
        for(i=L.begin(); i != L.end(); ++i) LE.push_front(*i);
	double *data = (double *)malloc(n*sizeof(double));
	//precisao conceitual de 100
	data[0]=1;
	double sd=0;
	//int flag_head_1=1;
	//int flag_head_1=1;
	for(i=LE.begin(); i != LE.end(); ++i) {
		data[count]=(*i).precisao;
		if(count>1) sd=gsl_stats_sd(data,1,count+1); 
		count++;
		//valor antigo 0.0606
		//foi testado o valor antigo 0.0806//muito alto
		if(sd<0.0606) {
			sprintf(str,"%s,%s,%d,%.4f,%.4f", "<<1>>",desc,(*i).id,(*i).precisao,(*i).eficiencia);
			gravaLog(str,path);
		}else {
			// coservative value if(sd<0.0806) {
			if(sd<0.1006) { //experimental value
				sprintf(str,"%s,%s,%d,%.4f,%.4f","<<2>>",desc, (*i).id,(*i).precisao,(*i).eficiencia);
				gravaLog(str,path);
			} else {
				sprintf(str,"%s,%s,%d,%.4f,%.4f","<<3>>",desc, (*i).id,(*i).precisao,(*i).eficiencia);
				gravaLog(str,path);
			}
		}
	}
	free(data);
}
