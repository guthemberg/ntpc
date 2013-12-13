#ifndef _FUNCTIONS_H_
#define _FUNCTIONS_H_

#define MAX_SLOT_TIMES 288
#define get_u16(X,O)  (*(__u16 *)(X + O))
#include <stdio.h>
#include <stdlib.h>
#include <pcap.h>
#include <time.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
#include <net/if_arp.h>
#include <net/ethernet.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/in_systm.h>
#include <netinet/tcp.h>
#include <netinet/udp.h>
#include <netinet/ip.h>
#include <netinet/if_ether.h>
#include <string>
#include <map>
#include <list>
//Bibliotecas adicionadas para funcionar para o profiling
#include <math.h>
#include <curses.h>
//funcoes estatisticas
#include <gsl/gsl_statistics.h>

using namespace std;

class SelectBC_COMP
{
	public:
		int id;
		double	precisao;
		double	eficiencia;

	SelectBC_COMP();
	SelectBC_COMP(const SelectBC_COMP &);
	~SelectBC_COMP(){};
	int operator<(const SelectBC_COMP &rhs) const;
};

class SelectBC_ACCU
{
	public:
		int id;
		double	precisao;
		double	eficiencia;

	SelectBC_ACCU();
	SelectBC_ACCU(const SelectBC_ACCU &);
	~SelectBC_ACCU(){};
	int operator<(const SelectBC_ACCU &rhs) const;
};


struct tipo_little_fluxo {
  struct in_addr ip_src,ip_dst;
  u_short dst_port;
  u_short src_port;
  double n_bytes;
  double n_frames;
  u_int tipo;
  double tempo;
};

typedef struct tipo_little_fluxo TLFluxo;

struct tipo_oito_valores_double {
	double mi_p2p;
	double n_bytes_p2p;
	double tempo_p2p;
	double frames_p2p;
	double mi;
	double n_bytes;
	double tempo;
	double frames;
};

typedef struct tipo_oito_valores_double T8Double;
struct tipo_fluxo {
  struct in_addr ip_src,ip_dst;
  u_short dst_port;
  u_short src_port;
  double n_bytes;
  double n_frames;
  u_int rumo;
/*  u_int unused_1;
  double unused_2;
  double unused_3;*/
  time_t ini_sec, ini_mil, end_sec, end_mil;
  struct tipo_socket *prox;
  u_int tipo;
};

//estruturas criadas para a implementacao do profiling
struct tipo_control_slot_time {
	double micro;
	int sltime;
	//onde m eh quantidade de fluxos, sltime eh o contador de 
        //intervalos de tempo, e micro eh o tempo em micro segundos armazenado
	double m;
};

struct tipo_info_IP {
  u_short port;
  struct in_addr ip;
  double mi;
  double pd;
  double precisao;
/*  double rux;
  double ruy;
  double ruz;*/
  u_short id;
  double n_bytes;
  double tempo;
  double frames;
  double n_bytes_p2p;
  double tempo_p2p;
  double frames_p2p;
  double mi_p2p;
}; 

typedef struct tipo_fluxo TFluxo;
//typedef u_int size_t;
typedef unsigned short __u16;
//tipos do profiling
typedef struct tipo_control_slot_time TCSTime;
typedef struct tipo_info_IP TSIp;

//Variaveis de controle
//tabelas para o profiling
/*map<string,TSIp*> htA;
map<string,TSIp*> htS;
map<string,TSIp*> htR;*/

//Variavel utilizada para concatenar strings antes de imprimir
//Variaveis utilizadas na implementacao do Profiling

//Variaveis para arquivos
void *mallocX (unsigned int nbytes, char *str, char *path);
//TFluxo *locate ();
void chargeListe(char *id, char *listfilelocal,int x,int iteracao, double bt, char *path, map<string,TSIp*> &htGeralBCsrcIP, map<string,TSIp*> &htGeralBCsrcPrt, map<string,TSIp*> &htGeralBCdstIP, map<string,TSIp*> &htGeralBCdstPrt,T8Double *tdGeral);
long getSizeofFile(char *str, char *path);
void gravaLog (char *cadeia, char *path);
void removeS(TFluxo *p);

//int comparaString();
/* Funcoes para manioulacao de arquivos */
FILE *abreArquivoR (char *str, char *path);
FILE *abreArquivoAplus (char *str, char *path);
FILE *abreArquivoW (char *str, char *path);
void fechaArquivo(FILE *p);
void gravaString (char *cadeia, FILE *filets);
//void geraResultadoSemRetirar();
int existFile(char *str);
int deleteFile(char *str);
//funcoes da implementacao do profiling, soh lembrando que chargeListe foi
//modificada para tratar do profiling
void metsTFluxoProfIP(int flag, TFluxo *nova,map<string,TSIp*> &htA,int i, char *path);
void metsTFluxoProfPrt(int flag, TFluxo *nova, map<string,TSIp*> &htA, int i, char *path);
string faisCleProf(TSIp *ts,int i);
void metsZeroProf(TSIp *t);
void doAlgorithm1(char *id,map<string,TSIp*> &htA, map<string,TSIp*> &htS, int i,int j, double bt, char *path);
u_int contaTable(map<string,TSIp*> &ht);
double log2( double num);
void doProcess(char *listfile, char *option,u_int i, int iteracao, double bt, char *path, map<string,TSIp*> &htGeralBCsrcIP, map<string,TSIp*> &htGeralBCsrcPrt, map<string,TSIp*> &htGeralBCdstIP, map<string,TSIp*> &htGeralBCdstPrt,T8Double *tdGeral);
void zeraTabela(map<string,TSIp*> &ht,int i);
string faisCledesSource(struct in_addr ip_src, u_short src_port, struct in_addr ip_dst, u_short dst_port,int i,int j);
void produisResultTSIp(TSIp *p);
void pourCordeTable(char ch);
void enleveProf(TSIp *p);
void copyTableAtoR(map<string,TSIp*> &htA, map<string,TSIp*> &htR, char *path);
double getPD(map<string,TSIp*> &htA, TSIp *host,int i);
void contaPR();
double getM(map<string,TSIp*> &ht);
double getBMBytes(map<string,TSIp*> &ht);
void contaPD(map<string,TSIp*> &ht);
void contaBPDBytes(map<string,TSIp*> &ht);
double getEntropia(map<string,TSIp*> &ht);
u_int removeNOs(map<string,TSIp*> &ht, TSIp *p,int i);
int deleteFileH(int i,int j, char *option, char *path);
void gravaLogH (char *ch, int i, int j, char *option, char *path);
void teste();
void deleteFiles(char *option, char *path);
void inicializaFiles(char *option, char *path);
void doBC(int flag, char *id, map<string,TSIp*> &ht, list<TLFluxo*> &lst, int i, int j, char *path);
void metsTLFluxo(TFluxo *nova, list<TLFluxo*> &lst, char *path);
void enleveTLFluxo(TLFluxo *p);
void zeraLista(list<TLFluxo*> &lst);
void cpTLFtoTF(TLFluxo *nova, TFluxo *no);
double getRU(map<string,TSIp*> &ht, char *path);
u_short getLru(double ru, int i);
u_short getID(double rux,double ruy, double ruz, int x, int y, int z);
void gravaLogS (char *ch, int i, int j, char *option, char *path);
int deleteFileS(int i,int j,char *option, char *path);
int estSorteP2P(u_int sorte);
int estSorteKazaa(u_int sorte);
int estSorteDonkey(u_int sorte);
int estSorteBittorrent(u_int sorte);
int estautreP2P(u_int sorte);
int estespecialP2P(u_int sorte);
double donneTempsIntervalle(TFluxo *tr);
int isToProcess(char *id,u_int tipo);
int isInvalid(char c);
void doScan(char *id, map<string,TSIp*> &htsrcIP, map<string,TSIp*> &htsrcPrt, map<string,TSIp*> &htdstIP, map<string,TSIp*> &htdstPrt,list<TLFluxo*> &lsti, map<string,TSIp*> &htBCsrcIP, map<string,TSIp*> &htBCsrcPrt, map<string,TSIp*> &htBCdstIP, map<string,TSIp*> &htBCdstPrt,T8Double *td, char *path);
int isThereintoBC(map<string,TSIp*> &ht, TFluxo *no, int i, int j);
void initT8Double(T8Double *t);
void addT8Double(T8Double *orig,T8Double *dest);
void printHTBCLog(map<string,TSIp*> &ht, char *desc, char *path);
void addTStoBC(map<string,TSIp*> &htsrc, map<string,TSIp*> &htdst, char *path);
void addValuesTSIp(TSIp *src, TSIp *dst);
string faisClepourBC(u_short id);
void sort(map<string,TSIp*> &ht, char *desc,T8Double *td, char *path);
#endif
