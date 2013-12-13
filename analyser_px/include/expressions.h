#ifndef _EXPRESSIONS_H_
#define _EXPRESSIONS_H_
#include <regex.h>
#include <stdio.h>

/*The types were defined to agree with the IPP2P functions*/
typedef unsigned char u8;
typedef unsigned char __u8;
typedef unsigned short u16;
typedef unsigned short __u16;
typedef unsigned long int u32;
typedef unsigned long int __u32;

/**
* Regular expressions
**/
regex_t* http;
regex_t* http2;
regex_t* dns;
regex_t* aim;
regex_t* irc;
regex_t* msn;
regex_t* aim;
regex_t* yahooMess;
regex_t* rtsp;
regex_t* httpQuicktime;
regex_t* httpVideo;
regex_t* httpAudio;
regex_t* pop3;
regex_t* smtp;
regex_t* ftp;
regex_t* hlcs;
regex_t* skypeToSkype;
regex_t* skypeOut;
regex_t* ssh;
regex_t* ssl;
regex_t* validcertssl;
regex_t* netbios;
regex_t* nbns;
regex_t* nbds;
regex_t* bootstrap;
regex_t* googlevideo;
regex_t* youtube;
regex_t* zippyvideo;
regex_t* veoh;
regex_t* vidilife;
regex_t* napster; //added recently
regex_t* otherChat;
regex_t* otherVideoTCP;
regex_t* otherVideoUDP;
regex_t* otherMail;
regex_t* mySQL;
regex_t* otherDNS;
regex_t* otherHTTP;
regex_t* mms;
/*new*/
regex_t* goBoogy; //Korean peer-to-peer -> netfilter's site
regex_t* soribada; //Korean peer-to-peer -> netfilter's site
FILE *a;

/**
* Function to allocate memory for regex_t pointers
**/
void allocateMemory();

/**
* Function to load the regular expresions
**/
void loadExpressions();


void freeExpressions();
#endif
