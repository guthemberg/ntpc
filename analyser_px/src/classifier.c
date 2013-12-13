#include "classifier.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>


void coupeEOF (const unsigned char *payload, const u_short mess_len, char* strg)
{
	
	strncpy(strg,"",1);
	int i=0;
	int c=0;
	
  //assert(payload_len < 500);
	for(i = 0; i < (mess_len); i++)
	{
		if(!(payload[i]=='\0')) {
			strg[c] = payload[i];
			c++;
		}
	}
	strg[c] = '\0';
}

unsigned char *getPayload(const struct ip *iph)
{
    unsigned char *payload = NULL;
    unsigned char *transport = (unsigned char *) iph + iph->ip_hl * 4;
    // if protocol is TCP
    if ((((int) iph->ip_p) == IPPROTO_TCP)) {
	struct tcphdr *tcph = (struct tcphdr *) transport;
	payload = transport + tcph->th_off * 4;
    }
    // if protocol is UDP
    else if ((((int) iph->ip_p) == IPPROTO_UDP)) {
	// udp has a fixed length of 8 bytes
	payload = transport + 8;
    }
    return payload;
}


unsigned short getPayloadLen(const struct ip *iph, u_short ipLen)
{
    unsigned char *transport = (unsigned char *) iph + iph->ip_hl * 4;
    // if protocol is TCP
    if ((((int) iph->ip_p) == IPPROTO_TCP)) {
	struct tcphdr *tcph = (struct tcphdr *) transport;
	return (ipLen - (iph->ip_hl * 4) - (tcph->th_off * 4) );
    }
    // if protocol is UDP
    else if ((((int) iph->ip_p) == IPPROTO_UDP)) {
        // udp has a fixed length of 8 bytes
	return (ipLen - (iph->ip_hl * 4) - (2 * 4) );
    }
    return (ipLen - (iph->ip_hl * 4) );
    //return ipLen - (payload - ((unsigned char *) iph));
}

u_short getID(const struct ip *iph, u_short ipLen)
{
    u_short id_port = 0;
    //char *strg;
    unsigned char *transp = (unsigned char *) iph + iph->ip_hl * 4;
    if ((((int) iph->ip_p) == IPPROTO_TCP)) {
	unsigned char *payload = getPayload(iph);
	u16 mess_len = getPayloadLen(iph, ipLen);
	struct tcphdr* temp = (struct tcphdr*) transp;
	/*if(ntohs(temp->th_sport) == 80 || ntohs(temp->th_dport) == 80) {
                char i[16];
                char d[16];
                strcpy(i, inet_ntoa(iph->ip_src));
                strcpy(d, inet_ntoa(iph->ip_dst));
                a = fopen("msgs.txt", "a+");
                fprintf(a, "src = %s   dest = %s\n", i, d);
		fprintf(a, "sport = %d   dport = %d\n", ntohs(temp->th_sport), ntohs(temp->th_dport));
                fprintf(a, "msg = %s\n\n", payload);
                fclose(a);
        }*/

	if (mess_len == 0)
	    return 3000;	//Nonpayload TCP traffic
/*	if (isHLCS(payload, mess_len))
		return 403; */
	if (isEdk(payload, mess_len))
		return 106;		//eDonkey, eMule, Kademlia 52->106
	if (isEdk_all(payload, mess_len))
		return 106;		//eDonkey, eMule, Kademlia Extended 52->106
	if (isBittorrent(payload, mess_len))
		return 104;		//BitTorrent 54->104
	if (isKazaa(payload, mess_len))
		return 107;		//Kazaa 51->107
	if (isKazaa_all(payload, mess_len))
		return 107;		//Kazaa 51->107
	if (isGnu(payload, mess_len))
		return 110;		//GNU 3 53->110
	if (isGnu_all(payload, mess_len))
		return 110;		//GNU 3 53->110
	if (isSoul(payload, mess_len))
		return 120;		//Soulseek 5 55->120
	if (isAres(payload, mess_len))
		return 103;		//Ares 9  59->103
	if (isMute(payload, mess_len))
		return 115;		//Mute 13    63->115
	/*if(isNap(payload, mess_len))
		return 116;		//OpenNap 11    61->116*/
	if(isEarthS5(payload, mess_len))
		return 124;		//EarthStation5 8	58->124
	if(isMP2P(payload, mess_len))
                return 125;		//MP2P	10	60->125
	if (isXdcc(payload, mess_len))
		return 128;		//Xdcc 14   64->128
	if (isDc(payload, mess_len))
		return 105;		//DirectConnect  67->105
	if (isDc_all(payload, mess_len))
		return 105;		//DirectConnect   67->105
	if (isApple(payload, mess_len))
		return 102;		//AppleJuice 66->102
	if (isWaste(payload, mess_len))
		return 129;		//Waste 65->129

       //strg = (char*)malloc((mess_len+1)*sizeof(char));
       //coupeEOF(payload, mess_len, strg);
       
//       if (isGoBoogy(payload, mess_len)) {
//	       free(strg); return 111;} //new, korean peer-to-peer application, see netfilter's site
//	if (isSoribada(payload, mess_len)) {
//               free(strg); return 119;} //new, korean peer-to-peer application, see netfilter's site
/*	if (isMSN(strg, mess_len)) {
		free(strg); return 306; }
	if (isHTTPQuicktime(strg, mess_len)) {
		free(strg); return 602; }
	if (isHTTPVideo(strg, mess_len)) {
		free(strg); return 606;}
	if (isYouTube(strg, mess_len)) {
		free(strg); return 612;}
	if (isGoogleVideo(strg, mess_len)) {
		free(strg); return 611;}
	if (isZippyVideo(strg, mess_len)) {
		free(strg); return 613;}
	if (isVeoh(strg, mess_len)) {
		free(strg); return 614;}
	if (isVidilife(strg, mess_len)) {
		free(strg); return 615;}
	if (isHTTPAudio(strg, mess_len)) {
		free(strg); return 608;}
	if (isHTTP(strg, mess_len)) {
		free(strg); return 201;}	
	if (isOtherHTTP(strg, mess_len)) {
                free(strg); return 299;} */
//	if (isNap(strg, mess_len)) {
//		free(strg); return 116;} //OpenNap 11    61->116	
//	if (isWinMX(strg, mess_len)) {
//		free(strg); return 126;}   //WinMX 62->126
/*	if (isSMTP(strg, mess_len)) {
		free(strg); return 704;}
	if (isPOP3(strg, mess_len)) {
		free(strg); return 703;}
	if (isOtherMail(strg, mess_len)) {  
                free(strg); return 799;}
	if (isIRC(strg, mess_len) && (ntohs(temp->th_sport) == 6667 || ntohs(temp->th_dport) == 6667)) {
		free(strg); return 303;}
	if (isFTP(strg, mess_len)) {
		free(strg); return 801;}
	if (isDNS(strg, mess_len) && (ntohs(temp->th_sport) == 53 || ntohs(temp->th_dport) == 53)) {
		free(strg); return 501;}
	if (isYahooMess(strg, mess_len)) {
		free(strg); return 308;}
	if (isAIM(strg, mess_len) && (ntohs(temp->th_sport) < 27000 || ntohs(temp->th_dport) < 27000)) {
		free(strg); return 301;}
	if (isOtherChat(strg, mess_len)) {
                free(strg); return 399;}
	if (isRTSP(strg, mess_len)) {
		free(strg); return 601;}
	if (isMMS(strg, mess_len)) {
		free(strg); return 609;}
	if (isOtherVideoTCP(strg, mess_len)) {
		free(strg); return 699;}
	if (isHLDEATH(strg, mess_len)) {
		free(strg); return 416;}
	if (isHL2DEATH(strg, mess_len)) {
		free(strg); return 407;}
	if (isHL2CS(strg, mess_len)){
		free(strg); return 415;}
	if (isVALIDCERTSSL(strg, mess_len)) {
		free(strg); return 1303;}
	if (isSSL(strg, mess_len)){
		free(strg); return 1302;}
	if (isSSH(strg, mess_len)) {
		free(strg); return 1301;}
	if (isNetBios(strg, mess_len)) {
		free(strg); return 506;}
	if (isNbns(strg, mess_len)){
		free(strg); return 509;}
	if (isNbds(strg, mess_len)) {
		free(strg); return 510;}
	if (isMySQL(strg, mess_len)) {
                free(strg); return 802;} */
	//free(strg);
	id_port = getIdbyPort(ntohs(temp->th_sport));
	if(id_port) return id_port;
	id_port = getIdbyPort(ntohs(temp->th_dport));
	if(id_port) return id_port;
	return IPPROTO_TCP; //Unknown application, under TCP traffic
    } else if ((((int) iph->ip_p) == IPPROTO_UDP)) {
	unsigned char *payload = getPayload(iph);
	u16 mess_len = getPayloadLen(iph, ipLen);
	struct udphdr* temp2 = (struct udphdr*) transp;	
	/*if(ntohs(temp2->uh_sport) == 53 || ntohs(temp2->uh_dport) == 53) {
		char i[16];
		char d[16];
		strcpy(i, inet_ntoa(iph->ip_src));
		strcpy(d, inet_ntoa(iph->ip_dst));
		a = fopen("msgs.txt", "a+");
		fprintf(a, "src = %s   dest = %s\n", i, d);
		fprintf(a, "msg = %s\n", payload);
		fclose(a);
	}*/
	if (mess_len == 0)
	    return 3000;	//Nonpayload UDP traffic
/*	if (isHLCS(payload, mess_len))
		return 403; */
	if (isEdku(payload, mess_len))
		return 106;		//edk 22    82->106
	if (isBittorrentu(payload, mess_len))
		return 104;		//BiTtorrent UDP 24    84->104
	if (isKazaau(payload, mess_len))
		return 107;		//kazaa 21     81->107
	if (isGnuu(payload, mess_len))
		return 110;		//gnu 23     83->110
	if (isDcu(payload, mess_len))
		return 105;		//Dc 27              87->105
	if(isEarthu(payload, mess_len))
		return 124;		//EarthStation5 28	88->124

        //strg = (char*)malloc((mess_len+1)*sizeof(char));
        //coupeEOF(payload, mess_len, strg);
/*	if (isDNS(strg, mess_len) && (ntohs(temp2->uh_sport) == 53 || ntohs(temp2->uh_dport) == 53)) {
                free(strg); return 501;}
	if (isGoBoogyu(payload, mess_len)) {
		free(strg); return 111;} //new, korean peer-to-peer, see netfilter's site
	if (isSoribada(payload, mess_len)) {
                free(strg); return 119;} //new, korean peer-to-peer, see netfilter's site
	if (isOtherDNS(strg, mess_len) && (ntohs(temp2->uh_sport) == 53 || ntohs(temp2->uh_dport) == 53)) {
                free(strg); return 599;} */
	/*if(isMP2Pu(strg, mess_len))
		free(strg); return 125;		//MP2P 30	90->125*/
/*	if (isMSN(strg, mess_len)) {
		free(strg); return 306;}
	if (isHTTPQuicktime(strg, mess_len)) {
		free(strg); return 602;}
	if (isHTTPVideo(strg, mess_len)) {
		free(strg); return 606;}
	if (isHTTPAudio(strg, mess_len)) {
		free(strg); return 608;}
	if (isHTTP(strg, mess_len)) {
		free(strg); return 201;}
	if (isSMTP(strg, mess_len)) {
		free(strg); return 704;}
	if (isPOP3(strg, mess_len)) {
		free(strg); return 703;}
	if (isIRC(strg, mess_len) && (ntohs(temp2->uh_sport) == 6667 || ntohs(temp2->uh_dport) == 6667)) {
		free(strg); return 303;}
	if (isFTP(strg, mess_len)) {
		free(strg); return 801;}
	if (isYahooMess(strg, mess_len)) {
		free(strg); return 308;}
	if (isAIM(strg, mess_len) && (ntohs(temp2->uh_sport) < 27000 && ntohs(temp2->uh_dport) < 27000)) {
		free(strg); return 301;}
	if (isOtherChat(strg, mess_len)) {
                free(strg); return 399;}
	if (isRTSP(strg, mess_len)) {
		free(strg); return 601;}
	if (isOtherVideoUDP(strg, mess_len)) {
		free(strg); return 699;}
	if (isHLDEATH(strg, mess_len)) {
		free(strg); return 416;}
	if (isHL2DEATH(strg, mess_len)) {
		free(strg); return 407;}
	if (isHL2CS(strg, mess_len)) {
		free(strg); return 415;}
	if (isVALIDCERTSSL(strg, mess_len)) {
		free(strg); return 1303;}
	if (isSSL(strg, mess_len)) {
		free(strg); return 1302;}
	if (isSSH(strg, mess_len)) {
		free(strg); return 1301;}
	if (isNetBios(strg, mess_len)) {
		free(strg); return 506;}
	if (isNbns(strg, mess_len) && (ntohs(temp2->uh_sport) < 27000 && ntohs(temp2->uh_dport) < 27000)) {
		free(strg); return 509;}
	if (isNbds(strg, mess_len) && (ntohs(temp2->uh_sport) < 27000 && ntohs(temp2->uh_dport) < 27000)) {
		free(strg); return 510;}
	if (isBootstrap(strg, mess_len) && (ntohs(temp2->uh_sport) < 27000 && ntohs(temp2->uh_dport) < 27000)) {
		free(strg); return 511;} */
/*	if(isSkypeToSkype(strg, mess_len)) {
		free(strg); return 1002; }
	if(isSkypeOut(strg, mess_len)){
		free(strg); return 1001; } */
	//free(strg);
	id_port = getIdbyPort(ntohs(ntohs(temp2->uh_sport)));
	if(id_port) return id_port;
	id_port = getIdbyPort(ntohs(ntohs(temp2->uh_dport)));
	if(id_port) return id_port;
	return IPPROTO_UDP;	//Unknown application, under UDP traffic
    } else if (((int) iph->ip_p) == IPPROTO_ICMP) {
	return IPPROTO_ICMP;	//icmp traffic
    }
    //others
    return 19;

}

//Earth
u_short isEarthu(const unsigned char *payload, const u16 mess_len)
{
    unsigned char *t = (unsigned char *) payload;
    if (mess_len < 4)
	return 0;
    t += 2;
    if ((t[0] == 0xcf) && (t[1] == 64))
	return 1;
    return 0;
}

/**
 * MP2P
 */
u_short isMP2Pu(const unsigned char *payload, const u16 mess_len)
{
    unsigned char *t = (unsigned char *) payload;
    if (mess_len < 5)
	return 0;
    t += 2;
    if (((t[0] == 0x00) && (t[1] == 0x00) && (t[2] == 0x00)) && ((t[3] == 0x00) || (t[3] == 0x01) || (t[3] == 0x02) || (t[3] == 0x03) || (t[3] == 0x04)))
	return 1;
    return 0;
}

/**
  *  OpenNap/Napster for TCP
  */
u_short isNap(unsigned char *payload, const u16 mess_len)
{
    /*unsigned char *t = (unsigned char *) payload;

    if (mess_len < 5)
	return 0;
    t += 2;
    if (t[0] == 0x31)
	return 1;
    if ((t[0] == 0x00) && (t[1] == 0x00) && (t[2] == 0xca)
	&& (t[3] == 0x00))
	return 1;
    if ((t[0] == 0xc8) && (t[1] == 0x00))
	return 1;
    if ((t[0] == 0xc9) && (t[1] == 0x00))
	return 1;
    if ((t[0] == 0xcb) && (t[1] == 0x00))
	return 1;
    if ((t[0] == 0xcc) && (t[1] == 0x00))
	return 1;
    if ((t[0] == 0x00) && (t[1] == 0x00))
	return 1;
    if ((t[0] == 0xd6) && (t[1] == 0x00))
	return 1;
    if ((t[0] == 0x02) && (t[1] == 0x00))
	return 1;
    if ((t[0] == 0x03) && (t[1] == 0x00))
	return 1;
    if ((t[0] == 0x06) && (t[1] == 0x00))
	return 1;
    if (mess_len < 6)
	return 0;
	if ((memcmp(t, "SEND", 4) == 0) || (memcmp(t, "GET", 3) == 0))*/
	//char *strg = (char*)malloc((mess_len+1)*sizeof(char));
	//coupeEOF(payload, mess_len, strg);
	//payload[mess_len-1]='\0';
	if (regexec(napster, payload, 0, NULL, 0)==0) {
		//free(strg);
		return 1;
	}
	//free(strg);
    	return 0;
}


/**
  * Earth Station 5 for TCP//Identificacao do frames UDP
  */
u_short isEarthS5(const unsigned char *payload, const u16 mess_len)
{
    unsigned char *t = (unsigned char *) payload;

    if (mess_len < 15)
	return 0;
    if (memcmp(t, "GET /$$$$$$$$$/", 15) == 0)
	return 1;		//Default TCP message
    else
	return 0;
}

/* MP2P for TCP*/
u_short isMP2P(const unsigned char *payload, const u16 mess_len)
{
    unsigned char *t = (unsigned char *) payload;

    if (mess_len < 4)
	return 0;
    if ((memcmp(t, "GO!!", 4) == 0) || (memcmp(t, "MD5", 4) == 0)
	|| ((memcmp(t, "SIZ", 3) == 0) && (t[3] == 0x20))
	|| ((memcmp(t, "STR", 3) == 0) && (t[3] == 0x20)))
	return 1;		//Mess padrao para TCP
    else
	return 0;
}

/*Search for UDP KaZaA commands*/
u_short isKazaau(const unsigned char *payload, const u16 mess_len)
{
    unsigned char *t = (unsigned char *) payload;
    if (mess_len < 6)
	return 0;
    /*implementado das assinaturas do paper do blinc*/
    if (t[0] == 0x27 && t[1] == 0x00 && t[2] == 0x00 && t[3] == 0x00 && (t[4] == 0x29 || t[4] == 0xa9) && t[5] == 0x80)
		return 1;
    if (t[0] == 0x28 && t[1] == 0x00 && t[2] == 0x00 && t[3] == 0x00 && (t[4] == 0x29 || t[4] == 0xa9) && t[5] == 0x00)
                return 1;
    if (t[0] == 0x29 && t[1] == 0x00 && t[2] == 0x00 && t[3] == 0x00 && (t[4] == 0x29 || t[4] == 0xa9))
                return 1;
    /*fim*/
    if (t[mess_len - 1] == 0x00) {
	t += (mess_len - 6);
	if (memcmp(t, "KaZaA", 5) == 0)
	    return 1;
    }

    return 0;
}				/*udp_search_kazaa */

/*check for gnutella get commands and other typical data*/
u_short isGnu_all(const unsigned char *payload, const u16 mess_len)
{

    if (mess_len < 2)
	return 0;
    if ((payload[mess_len - 2] == 0x0d) && (payload[mess_len - 1] == 0x0a)) {

	if (mess_len < 17)
	    return 0;
	if (memcmp(payload, "GNUTELLA CONNECT/", 17) == 0)
	    return 1;
	if (memcmp(payload, "GNUTELLA/", 9) == 0)
	    return 1;


	if ((memcmp(payload, "GET /get/", 9) == 0)
	    || (memcmp(payload, "GET /uri-res/", 13) == 0)) {
	    u16 c = 8;
	    if (mess_len < 30)
	       return 0;
	    const u16 end = mess_len - 22;
	    while (c < end) {
		if (payload[c] == 0x0a && payload[c + 1] == 0x0d
		    && ((memcmp(&payload[c + 2], "X-Gnutella-", 11) == 0)
			|| (memcmp(&payload[c + 2], "X-Queue:", 8) == 0)))
		    return 1;
		c++;
	    }
	}
    }
    return 0;
}

/*intensive but slower check for all direct connect packets*/
u_short isDc_all(const unsigned char *payload, const u16 mess_len)
{
//    unsigned char *t = haystack;

    if (mess_len < 1)
	return 0;
    if (payload[0] == 0x24 && payload[mess_len - 1] == 0x7c) {
	const unsigned char *t = &payload[1];
	/* Client-Hub-Protocol */
	if (mess_len < 6)
	    return 0;
	if (memcmp(t, "Lock ", 5) == 0)
	    return 1;
	/* Client-Client-Protocol, some are already recognized by client-hub (like lock) */
	if (mess_len < 8)
	    return 0;
	if (memcmp(t, "MyNick ", 7) == 0)
	    return 1;
    }
    return 0;
}

/*Search for UDP BitTorrent commands*/
u_short isBittorrentu(const unsigned char *payload, const u16 mess_len)
{
    switch (mess_len) {
    case 24:
	/* ^ 00 00 04 17 27 10 19 80 */
	if ((ntohl(get_u32(payload, 8)) == 0x00000417)
	    && (ntohl(get_u32(payload, 12)) == 0x27101980))
	    return 1;
	break;
    case 44:
//                      if (get_u32(payload, 16) == __constant_htonl(0x00000400) && get_u32(haystack, 36) == __constant_htonl(0x00000104)) 
	if (get_u32(payload, 16) == htonl(0x00000400)
	    && get_u32(payload, 36) == htonl(0x00000104))
	    return 1;
//                      if (get_u32(haystack, 16) == __constant_htonl(0x00000400))
	if (get_u32(payload, 16) == htonl(0x00000400))
	    return 1;
	break;
    case 65:
//                      if (get_u32(haystack, 16) == __constant_htonl(0x00000404) && get_u32(haystack, 36) == __constant_htonl(0x00000104)) 
	if (get_u32(payload, 16) == htonl(0x00000404)
	    && get_u32(payload, 36) == htonl(0x00000104))
	    return 1;
//                      if (get_u32(haystack, 16) == __constant_htonl(0x00000404))
	if (get_u32(payload, 16) == htonl(0x00000404))
	    return 1;
	break;
    case 67:
//                      if (get_u32(haystack, 16) == __constant_htonl(0x00000406) && get_u32(haystack, 36) == __constant_htonl(0x00000104)) 
	if (get_u32(payload, 16) == htonl(0x00000406)
	    && get_u32(payload, 36) == htonl(0x00000104))
	    return 1;
//                      if (get_u32(haystack, 16) == __constant_htonl(0x00000406))
	if (get_u32(payload, 16) == htonl(0x00000406))
	    return 1;
	break;
    case 211:
//                      if (get_u32(haystack, 8) == __constant_htonl(0x00000405)) 
	if (get_u32(payload, 8) == htonl(0x00000405))
	    return 1;
	break;
    case 29:
//                      if ((get_u32(haystack, 8) == __constant_htonl(0x00000401))) 
	if ((get_u32(payload, 8) == htonl(0x00000401)))
	    return 1;
	break;
    case 52:
//                      if (get_u32(haystack,8)  == __constant_htonl(0x00000827) &&
//                      get_u32(haystack,12) == __constant_htonl(0x37502950))
	if (get_u32(payload, 8) == htonl(0x00000827) &&
	    get_u32(payload, 12) == htonl(0x37502950))
	    return 1;
	break;
    default:
	/* this packet does not have a constant size */
//                      if (packet_len >= 40 && get_u32(haystack, 16) == __constant_htonl(0x00000402) && get_u32(haystack, 36) == __constant_htonl(0x00000104)) 
	if (mess_len >= 40 && get_u32(payload, 16) == htonl(0x00000402)
	    && get_u32(payload, 36) == htonl(0x00000104))
	    return 1;
	break;
    }

    /* some extra-bitcomet rules:
     * "d1:" [a|r] "d2:id20:"
     */
    if (mess_len > 30 && get_u8(payload, 8) == 'd'
	&& get_u8(payload, 9) == '1' && get_u8(payload, 10) == ':') {
	if (get_u8(payload, 11) == 'a' || get_u8(payload, 11) == 'r') {
	    if (memcmp(payload + 12, "d2:id20:", 8) == 0)
		return 1;
	}
    }
#if 0
    /* bitlord rules */
    /* packetlen must be bigger than 40 */
    /* first 4 bytes are zero */
    if (mess_len > 40 && get_u32(payload, 8) == 0x00000000) {
	/* first rule: 00 00 00 00 01 00 00 xx xx xx xx 00 00 00 00 */
	if (get_u32(payload, 12) == 0x00000000 &&
	    get_u32(payload, 16) == 0x00010000 &&
	    get_u32(payload, 24) == 0x00000000)
	    return 1;

	/* 00 01 00 00 0d 00 00 xx xx xx xx 00 00 00 00 */
	if (get_u32(payload, 12) == 0x00000001 &&
	    get_u32(payload, 16) == 0x000d0000 &&
	    get_u32(payload, 24) == 0x00000000)
	    return 1;


    }
#endif

    return 0;
}				/*udp_search_bit */

/* search for waste */
u_short isWaste(const unsigned char *payload, const u16 mess_len)
{
    if (mess_len >= 8 && memcmp(payload, "GET.sha1:", 9) == 0)
	return 1;

    return 0;
}

u_short isXdcc(const unsigned char *payload, const u16 mess_len)
{
    /* search in small packets only */
    if (mess_len > 20 && mess_len < 200 && payload[mess_len - 1] == 0x0a
	&& payload[mess_len - 2] == 0x0d
	&& memcmp(payload, "PRIVMSG ", 8) == 0) {

	u16 x = 10;
	const u16 end = mess_len - 13;

	/* is seems to be a irc private massage, chedck for xdcc command */
	while (x < end) {
	    if (payload[x] == ':') {
		if (memcmp(&payload[x + 1], "xdcc send #", 11) == 0)
		    return 1;
	    }
	    x++;
	}
    }
    return 0;
}

u_short isKazaa_all(const unsigned char *payload, const u16 mess_len)
{
    if (mess_len < 2)
	return 0;
    if ((payload[mess_len - 2] == 0x0d) && (payload[mess_len - 1] == 0x0a)) {

	if (mess_len < 5)
	    return 0;
	if (memcmp(payload, "GIVE ", 5) == 0)
	    return 1;

	if (memcmp(payload, "GET /", 5) == 0) {
	    u16 c = 8;
	    if (mess_len < 35)
		return 0;
	    const u16 end = mess_len - 22;
	    while (c < end) {
		if (payload[c] == 0x0a && payload[c + 1] == 0x0d
		    &&
		    ((memcmp(&payload[c + 2], "X-Kazaa-Username: ", 18) ==
		      0)
		     ||
		     (memcmp
		      (&payload[c + 2], "User-Agent: PeerEnabler/",
		       24) == 0)))
		    return 1;
		c++;
	    }
	}
    }
    return 0;
}

u_short isMute(const unsigned char *payload, const u16 mess_len)
{
    if (mess_len == 209 || mess_len == 345 || mess_len == 473
	|| mess_len == 609 || mess_len == 1121) {
	//printk(KERN_DEBUG "size hit: %u",size);
	if (memcmp(payload, "PublicKey: ", 11) == 0) {
	    return 1;

/*			if (memcmp(t+size-14,"\x0aEndPublicKey\x0a",14) == 0)
			{
				printk(KERN_DEBUG "end pubic key hit: %u",size);
				
			}*/
	}
    }
    return 0;
}

u_short isWinMX(const unsigned char *payload, const u16 mess_len)
{
    if (((mess_len) == 4) && (memcmp(payload, "SEND", 4) == 0))
	return 1;
    if (((mess_len) == 3) && (memcmp(payload, "GET", 3) == 0))
	return 1;
    if (mess_len < 10)
	return 0;

    if ((memcmp(payload, "SEND", 4) == 0)
	|| (memcmp(payload, "GET", 3) == 0)) {
	u16 c = 4;
	const u16 end = mess_len - 2;
	u8 count = 0;
	while (c < end) {
	    if (payload[c] == 0x20 && payload[c + 1] == 0x22) {
		c++;
		count++;
		if (count >= 2)
		    return 1;
	    }
	    c++;
	}
    }

    if (mess_len == 149 && payload[0] == '8') {
	if (get_u32(payload, 17) == 0 && get_u32(payload, 21) == 0
	    && get_u32(payload, 25) == 0 &&
	    //get_u16(payload,39) == 0 && get_u16(payload,135) == __constant_htons(0x7edf) && get_u16(payload,147) == __constant_htons(0xf792))
	    get_u16(payload, 39) == 0
	    && get_u16(payload, 135) == htons(0x7edf)
	    && get_u16(payload, 147) == htons(0xf792)) {
	    return 1;
	}
    }
    return 0;
}				/*search_winmx */


u_short isKazaa(const unsigned char *payload, const u16 mess_len)
{
     if (mess_len < 11)
        return 0;
     if ((payload[mess_len-2] == 0x0d) && (payload[mess_len-1] == 0x0a) && memcmp(payload, "GET /.hash=", 11) == 0)
        return 1;
/*    if (mess_len < 11)
	return 0;
    if ((payload[mess_len - 2] == 0x0d) && (payload[mess_len - 1] == 0x0a)
	&& memcmp(payload, "GET /.hash=", 11) == 0)
	return 1;
*/
    /*implementado das assinaturas do paper do blinc*/
    unsigned char *t = (unsigned char *) payload;
    if (mess_len < 28)
        return 0;
    t += 14;
    if (memcmp(payload, "Content-Range:", 14) == 0)
	return 1;
    if (mess_len < 29)
        return 0;
    t += 3;
    if (memcmp(payload, "Retry-After:", 12) == 0)
        return 1;
    /*fim*/
    return 0;
}

u_short isBittorrent(const unsigned char *payload, const u16 mess_len)
{
    if (mess_len > 20) {
	/* test for match 0x13+"BitTorrent protocol" */
	if (payload[0] == 0x13) {
	    if (memcmp(payload + 1, "BitTorrent protocol", 19) == 0)
		return 1;
	}

	/* get tracker commandos, all starts with GET /
	 * then it can follow: scrape| announce
	 * and then ?hash_info=
	 */
	if (memcmp(payload, "GET /", 5) == 0) {
	    /*implementado das assinaturas do paper do bline*/
	    if (memcmp(payload + 5, "torrents/", 9) == 0)
                return 1;
	    /*fim*/
	    /* message scrape */
  	    if (mess_len < 22)
	      return 0;
	    if (memcmp(payload + 5, "scrape?info_hash=", 17) == 0)
		return 1;
  	    if (mess_len < 24)
	      return 0;
	    /* message announce */
	    if (memcmp(payload + 5, "announce?info_hash=", 19) == 0)
		return 1;
	}
    } else {
	/* bitcomet encryptes the first packet, so we have to detect another 
	 * one later in the flow */
	/* first try failed, too many missdetections */
	//if ( size == 5 && get_u32(t,0) == __constant_htonl(1) && t[4] < 3) return (IPP2P_BIT * 100 + 3);

	/* second try: block request packets */
//              if ( mess_len == 17 && get_u32(payload,0) == __constant_htonl(0x0d) && payload[4] == 0x06 && get_u32(payload,13) == __constant_htonl(0x4000) ) return 1;
	if (mess_len == 17 && get_u32(payload, 0) == htonl(0x0d)
	    && payload[4] == 0x06 && get_u32(payload, 13) == htonl(0x4000))
	    return 1;
    }
    /*implementado das assinaturas do paper do blinc*/
    if (mess_len < 7)
	return 0;
    if (payload[0] == 0x00 && payload[1] == 0x00 && payload[5] == 0x00 && payload[6] == 0x00) {
	if (payload[2] == 0x40 && payload[1] == 0x09 && payload[5] == 0x07)
		return 1;
	if (payload[2] == 0x00 && payload[1] == 0x0d && payload[5] == 0x06)
                return 1;
	if (payload[2] == 0x00 && payload[1] == 0x05 && payload[5] == 0x04)
                return 1;
    }
    /*fim*/

    return 0;
}

/*intensive but slower check for all direct connect packets*/
u_short isDc(const unsigned char *payload, const u16 mess_len)
{
    if (mess_len < 1)
	return 0;
    if (payload[0] != 0x24)
	return 0;
    else {
        /*implementado das assinaturas do paper do blinc*/
	if (mess_len < 4)
            return 0;
        if ((memcmp(&payload[1], "Get", 3) == 0) || (memcmp(&payload[1], "Dir", 3) == 0))
	    return 1;
        if (mess_len < 5)
            return 0;
        if (memcmp(&payload[1], "Key ", 4) == 0)
            return 1;
	/*fim*/
	if (mess_len < 6)
	    return 0;
	if (memcmp(&payload[1], "Send|", 5) == 0)
	    return 1;
	/*implementado das assinaturas do paper do blinc*/
	if ((memcmp(&payload[1], "Hello", 5) == 0) || (memcmp(&payload[1], "Quit ", 5) == 0))
            return 1;
	if (mess_len < 7)
            return 0;
	if (memcmp(&payload[1], "MyINFO", 6) == 0)
            return 1;
	if (mess_len < 8)
            return 0;
	if ((memcmp(&payload[1], "RevConn", 7) == 0) || (memcmp(&payload[1], "HubName", 7) == 0) || 
	    (memcmp(&payload[1], "Search ", 7) == 0))
            return 1;
	if (mess_len < 9)
            return 0;
	if ((memcmp(&payload[1], "ConnectT", 8) == 0) || (memcmp(&payload[1], "Supports", 8) == 0) ||
	    (memcmp(&payload[1], "Version ", 8) == 0))
            return 1;
	/*fim*/
	else
	    return 0;
    }
}

/*Search for appleJuice commands*/
u_short isApple(const unsigned char *payload, const u16 mess_len)
{
    if ((mess_len > 7) && (payload[6] == 0x0d) && (payload[7] == 0x0a)
	&& (memcmp(payload, "ajprot", 6) == 0))
	return 1;

    return 0;
}

/*fast check for edonkey file segment transfer command*/
u_short isEdk(const unsigned char *payload, const u16 mess_len)
{
    if (mess_len < 1)
	return 0;
    if (payload[0] != 0xe3)
	return 0;
    else {
	if (mess_len < 5)
	    return 0;
	if (payload[5] == 0x47)
	    return 1;
	    return 0;
    }
}

/*intensive but slower search for some edonkey packets including size-check*/
u_short isEdk_all(const unsigned char *payload, const u16 mess_len)
{
    if (mess_len < 1)
	return 0;
    if (payload[0] != 0xe3)
	return 0;
    else {
	//t += head_len;
	if (mess_len < 5)
	    return 0;
	const u16 cmd = get_u16(payload, 1);
	if (cmd == (mess_len - 5)) {
	    switch (payload[5]) {
	    case 0x01:
		return 1;	/*Client: hello or Server:hello */
	    case 0x4c:
		return 1;	/*Client: Hello-Answer */
	    }
	}
	return 0;
    }
}

u_short isGnu(const unsigned char *payload, const u16 mess_len)
{
    if (mess_len < 9)
	return 0;
    if ((payload[mess_len - 2] == 0x0d) && (payload[mess_len - 1] == 0x0a)) {
	if (memcmp(payload, "GET /get/", 9) == 0)
	    return 1;
	if (mess_len < 13)
	    return 0;
	if (memcmp(payload, "GET /uri-res/", 13) == 0)
	    return 1;
    }
    /*implementado das assinaturas do paper do blinc*/
    if (memcmp(payload, "GNUTELLA", 8) == 0)
            return 1;
    if (memcmp(payload, "X-", 2) == 0) {
	if ((memcmp(payload, "Query", 5) == 0) || (memcmp(payload, "Guess", 5) == 0) || (memcmp(payload, "Ultrap", 6) == 0) ||
	   (memcmp(payload, "Ext-", 4) == 0) || (memcmp(payload, "Try-", 4) == 0) || (memcmp(payload, "Degree", 6) == 0) ||
	   (memcmp(payload, "Lo", 2) == 0) || (memcmp(payload, "Max-", 4) == 0) || (memcmp(payload, "Version", 7) == 0) ||
	   (memcmp(payload, "Dynami", 6) == 0))
		return 1;
    }
    if (mess_len < 11)
	return 0;
    if ((memcmp(payload, "Server: Mor", 11) == 0) || (memcmp(payload, "Server: Lim", 11) == 0))
	return 1;
    if (mess_len < 16)
        return 0;
    if ((memcmp(payload, "User-Agent: Lime", 16) == 0) || (memcmp(payload, "Vendor-Message", 16) == 0))
        return 1;
    if (memcmp(payload, "HTTP/1.1 503 ", 13) == 0) {
	if ((memcmp(payload, "Que", 3) == 0) || (memcmp(payload, "Ful", 3) == 0) || (memcmp(payload, "Not", 3) == 0))
        	return 1;
    }
    if (mess_len < 44)
        return 0;
    unsigned char *t = (unsigned char *) payload;
    t += 33;
    if (memcmp(payload, "Busy Queued", 11) == 0)
	return 1;
    /*fim*/
    return 0;
}

/*Search for SoulSeek commands*/
u_short isSoul(const unsigned char *payload, const u16 mess_len)
{
    /* match: xx xx xx xx | xx = sizeof(payload) - 4 */
    if (mess_len < 9 ) return 0;
    if (get_u32(payload, 0) == (mess_len - 4)) {
	const __u32 m = get_u32(payload, 4);
	/* match 00 yy yy 00, yy can be everything */
	if (get_u8(payload, 4) == 0x00 && get_u8(payload, 7) == 0x00) {
	    return 1;
	}
	/* next match: 01 yy 00 00 | yy can be everything */
	if (get_u8(payload, 4) == 0x01 && get_u16(payload, 6) == 0x0000) {
	    return 1;
	}

	/* other soulseek commandos are: 1-5,7,9,13-18,22,23,26,28,35-37,40-46,50,51,60,62-69,91,92,1001 */
	/* try to do this in an intelligent way */
	/* get all small commandos */
	switch (m) {
	case 7:
	case 9:
	case 22:
	case 23:
	case 26:
	case 28:
	case 50:
	case 51:
	case 60:
	case 91:
	case 92:
	case 1001:
	    return 1;
	}

	if (m > 0 && m < 6) {
	    return 1;
	}
	if (m > 12 && m < 19) {
	    return 1;
	}

	if (m > 34 && m < 38) {
	    return 1;
	}

	if (m > 39 && m < 47) {
	    return 1;
	}

	if (m > 61 && m < 70) {
	    return 1;
	}

    }

    /* match 14 00 00 00 01 yy 00 00 00 STRING(YY) 01 00 00 00 00 46|50 00 00 00 00 */
    /* without size at the beginning !!! */
    if (get_u32(payload, 0) == 0x14 && get_u8(payload, 4) == 0x01) {
	__u32 y = get_u32(payload, 5);
	/* we need 19 chars + string */
	if ((y + 19) <= (mess_len)) {
	    const unsigned char *w = payload + 9 + y;
	    if (get_u32(w, 0) == 0x01
		&& (get_u16(w, 4) == 0x4600 || get_u16(w, 4) == 0x5000)
		&& get_u32(w, 6) == 0x00);
	    return 1;
	}
    }
    return 0;
}


/*Ares for TCP*/
u_short isAres(const unsigned char *payload, const u16 mess_len)
{
    /* all ares packets start with  */
    /*implementado das assinaturas do paper do blinc*/
    if (mess_len < 5)
	return 0;
    if (memcmp(payload, "PUSH ", 5) == 0)
        return 1;
    /*fim*/
    if (mess_len < 6 ) 
	return 0;
    if (payload[1] == 0 && (mess_len - payload[0]) == 3) {
	switch (payload[2]) {
	case 0x5a:
	    /* ares connect */
	    if (mess_len == 6 && payload[5] == 0x05)
		return 1;
	    break;
	case 0x09:
	    /* ares search, min 3 chars --> 14 bytes
	     * lets define a search can be up to 30 chars --> max 34 bytes
	     */
	    if (mess_len >= 14 && mess_len <= 34)
		return 1;
	    break;
	}
    }
    /*implementado das assinaturas do paper do blinc*/
    if (mess_len < 9 )
        return 0;
    if (memcmp(payload, "GET hash:", 9) == 0)
        return 1;
    if (memcmp(payload, "GET sha1:", 9) == 0)
        return 1;
    if (mess_len < 16 )
        return 0;
    if (memcmp(payload, "HTTP/1.1 503 Bus", 16) == 0)
        return 1;
    /*fim*/

    return 0;
}




/**
  * eDonkey for UDP
  */
u_short isEdku(const unsigned char *payload, const u16 mess_len)
{
    unsigned char *t = (unsigned char *) payload;

    if (mess_len < 10)
	return 0;
    t += 8;
    switch (t[0]) {
    case 0xe3:
	{			/*edonkey */
	    switch (t[1]) {
		/* client -> server status request */
	    case 0x96:
		if (mess_len == 14)
		    return 1;
		break;
		/* server -> client status request */
	    case 0x97:
		if (mess_len == 42)
		    return 1;
		break;
		/* server description request */
		/* e3 2a ff f0 .. | size == 6 */
//                                      case 0xa2: if ( (mess_len == 14) && ( get_u16(t,2) == __constant_htons(0xfff0) ) ) return 1;
	    case 0xa2:
		if ((mess_len == 14) && (get_u16(t, 2) == htons(0xfff0)))
		    return 1;
		break;
		/* server description response */
		/* e3 a3 ff f0 ..  | size > 40 && size < 200 */
		//case 0xa3: return ((IPP2P_EDK * 100) + 53);
		//      break;
		case 0x9a:
		if (mess_len == 26)
		    return 1;
		break;

	    case 0x92:
		if (mess_len == 18)
		    return 1;
		break;
	    }
	    break;
	}
    case 0xe4:
	{
	    switch (t[1]) {
		/* e4 20 .. | size == 43 */
	    case 0x20:
		if ((mess_len == 43) && (t[2] != 0x00) && (t[34] != 0x00))
		    return 1;
		break;
		/* e4 00 .. 00 | size == 35 ? */
	    case 0x00:
		if ((mess_len == 35) && (t[26] == 0x00))
		    return 1;
		break;
		/* e4 10 .. 00 | size == 35 ? */
	    case 0x10:
		if ((mess_len == 35) && (t[26] == 0x00))
		    return 1;
		break;
		/* e4 18 .. 00 | size == 35 ? */
	    case 0x18:
		if ((mess_len == 35) && (t[26] == 0x00))
		    return 1;
		break;
		/* e4 52 .. | size = 44 */
	    case 0x52:
		if (mess_len == 44)
		    return 1;
		break;
		/* e4 58 .. | size == 6 */
	    case 0x58:
		if (mess_len == 14)
		    return 1;
		break;
		/* e4 59 .. | size == 2 */
	    case 0x59:
		if (mess_len == 10)
		    return 1;
		break;
		/* e4 28 .. | mess_len == 52,77,102,127... */
	    case 0x28:
		if (((mess_len - 52) % 25) == 0)
		    return 1;
		break;
		/* e4 50 xx xx | size == 4 */
	    case 0x50:
		if (mess_len == 12)
		    return 1;
		break;
		/* e4 40 xx xx | size == 48 */
	    case 0x40:
		if (mess_len == 56)
		    return 1;
		break;
	    case 0x11:
                if (mess_len == 38) /*acrescentado por thiago*/
                    return 1;
                break;
	    }
	    break;
	}
    }				/* end of switch (t[0]) */
    return 0;
}				/*udp_search_edk */


//Gnutella
u_short isGnuu(const unsigned char *payload, const u16 mess_len)
{
    unsigned char *t = (unsigned char *) payload;

    if (mess_len < 11)
	return 0;
    /*implementado das assinaturas do paper do blinc*/
    if (t[0] == 0x47 && t[1] == 0x4e && t[2] == 0x44)
	return 1;
    /*fim*/
    t += 8;
    if (memcmp(t, "GND", 3) == 0)
	return 1;
    if (mess_len < 18)
	return 0;
    if (memcmp(t, "GNUTELLA ", 9) == 0)
	return 1;
    /*implementado das assinaturas do paper do blinc*/
    if (mess_len < 23)
	return 0;
    t += 8;
    if (t[0] == 0x00 && t[1] == 0x01 && t[2] == 0x00 && t[3] == 0x00 && t[4] == 0x00 && t[5] == 0x00 && t[6] == 0x00 && mess_len == 23)
	return 1;
    if (t[0] == 0x01 && t[1] == 0x01 && t[2] == 0x00 && t[3] == 0x1f && t[4] == 0x00 && t[5] == 0x00 && t[6] == 0x00)
	return 1;
    if (mess_len < 27)
	return 0;
    t += 7;
    if (memcmp(t, "LIME ", 4) == 0)
	return 1;
    /*fim*/
    return 0;
}

//DirectConnect UDP
u_short isDcu(const unsigned char *payload, const u16 mess_len)
{
    unsigned char *t = (unsigned char *) payload;
    if (mess_len < 9)
	return 0;
    if ((*(t + 8) == 0x24) && (*(t + mess_len - 1) == 0x7c)) {
	t += 8;
	if (mess_len < 11)
	    return 0;
	if (memcmp(t, "SR ", 3) == 0)
	    return 1;
	if (mess_len < 13)
	    return 0;
	if (memcmp(t, "Ping ", 5) == 0)
	    return 1;
    }
    /*implementado das assinaturas do paper do blinc*/
    if (memcmp(t, "$SR ", 4) == 0)
            return 1;
    if (memcmp(t, "$Pin", 4) == 0)
            return 1;
    /*fim*/
    return 0;
}

u_short isGoBoogy (unsigned char *payload, const u16 mess_len) {

	if ((regexec(goBoogy, payload, 0, NULL, 0)==0)) {
		//free(strg);
		return 1;
	}
	if (mess_len < 5)
		return 0;
	unsigned char *t = (unsigned char *) payload;
	if (memcmp(t, "boogy", 5) == 0)
		return 1;
	if (mess_len < 7)
		return 0;
	if (memcmp(t, "goboogy", 7) == 0)
		return 1;
	return 0;
}

u_short isGoBoogyu (unsigned char *payload, const u16 mess_len) {

	        if ((regexec(goBoogy, payload, 0, NULL, 0)==0)) {
			//free(strg);
			return 1;
		}
		return 0;
}

u_short isHTTP (unsigned char *payload, const u16 mess_len) {
	//char *strg = (char*)malloc((mess_len+1)*sizeof(char));
	//coupeEOF(payload, mess_len, strg);
	//payload[mess_len-1]='\0';
	
	if ((regexec(http, payload, 0, NULL, 0)==0)) {
		//free(strg);
		return 1;
	}
	if (regexec(http2, payload, 0, NULL, 0)==0) {
		//free(strg);
		return 1;
	}
	//free(strg);
	return 0;
}

u_short isAIM (unsigned char *payload, const u16 mess_len) {
	//char *strg = (char*)malloc((mess_len+1)*sizeof(char));
	//coupeEOF(payload, mess_len, strg);
	//payload[mess_len-1]='\0';
	if (regexec(aim, payload, 0, NULL, 0)==0) {
		//free(strg);
		return 1;
	}
	//free(strg);
	return 0;
}

u_short isIRC (unsigned char *payload, const u16 mess_len) {
	//char *strg = (char*)malloc((mess_len+1)*sizeof(char));
	//coupeEOF(payload, mess_len, strg);
	//payload[mess_len-1]='\0';
	
	if (regexec(irc, payload, 0, NULL, 0)==0) {
		//free(strg);
		return 1;
	}
	//free(strg);
	return 0;
}

u_short isMSN (unsigned char *payload, const u16 mess_len) {
	//char *strg = (char*)malloc((mess_len+1)*sizeof(char));
	//coupeEOF(payload, mess_len, strg);
	//payload[mess_len-1]='\0';
	
	if (regexec(msn, payload, 0, NULL, 0)==0) {
		//free(strg);
		return 1;
	}
	//free(strg);
	return 0;
}

u_short isYahooMess (unsigned char *payload, const u16 mess_len) {
	//char *strg = (char*)malloc((mess_len+1)*sizeof(char));
	//coupeEOF(payload, mess_len, strg);
	//payload[mess_len-1]='\0';
	if (regexec(yahooMess, payload, 0, NULL, 0)==0) {
		//free(strg);
		return 1;
	}
	//free(strg);
	return 0;
}

u_short isHLCS (unsigned char *payload, const u16 mess_len) {
	//char *strg = (char*)malloc((mess_len+1)*sizeof(char));
	//coupeEOF(payload, mess_len, strg);
	//payload[mess_len-1]='\0';
	if (regexec(hlcs, payload, 0, NULL, 0)==0) {
		//free(strg);
		return 1;
	}
	//free(strg);
	return 0;
}

u_short isHL2DEATH (const unsigned char *payload, const u16 mess_len) {
	
	return 0;
}

u_short isHL2CS (const unsigned char *payload, const u16 mess_len) {
	
	return 0;
}

u_short isHLDEATH (const unsigned char *payload, const u16 mess_len) {
	
	/*char* t = payload;
	if(mess_len<3) return 0;
	t = t + 1;
	if(memcmp(t, "\x00\x00", 2)) {
		return 1;
		
	} t = t + 1;
	if(mess_len<4) return 0;
	if(memcmp(t, "\x00\x00", 2)) {
		return 1;
		
	}
// 	if(memcmp(payload, "\xff\xff\xff\xff", 4) == 0) {
// 		return 1;
	// 	}*/
	return 0;
}

u_short isQUAKE3 (const unsigned char *payload, const u16 mess_len) {
	
	return 0;
}

u_short isDNS (unsigned char *payload, const u16 mess_len) {
	//char *strg = (char*)malloc((mess_len+1)*sizeof(char));
	//coupeEOF(payload, mess_len, strg);
	//payload[mess_len-1]='\0';
	if (regexec(dns, payload, 0, NULL, 0)==0) {
		//free(strg);
		return 1;
	}
	//free(strg);
	return 0;
}

u_short isRTSP (unsigned char *payload, const u16 mess_len) {
	//char *strg = (char*)malloc((mess_len+1)*sizeof(char));
	//coupeEOF(payload, mess_len, strg);
	//payload[mess_len-1]='\0';
	
	if (regexec(rtsp, payload, 0, NULL, 0)==0) {
		//free(strg);
		return 1;
	}
	//free(strg);
	return 0;
}

u_short isMMS (unsigned char *payload, const u16 mess_len) {
	        //char *strg = (char*)malloc((mess_len+1)*sizeof(char));
		//coupeEOF(payload, mess_len, strg);
		//payload[mess_len-1]='\0';
		
		if (regexec(mms, payload, 0, NULL, 0)==0) {
		        //free(strg);
			return 1;
		}
		//free(strg);
		return 0;
}

u_short isHTTPQuicktime (unsigned char *payload, const u16 mess_len) {
	//char *strg = (char*)malloc((mess_len+1)*sizeof(char));
	//coupeEOF(payload, mess_len, strg);
	//payload[mess_len-1]='\0';
	
	if (regexec(httpQuicktime, payload, 0, NULL, 0)==0) {
		//free(strg);
		return 1;
	}
	//free(strg);
	return 0;
}

u_short isHTTPVideo (unsigned char *payload, const u16 mess_len) {
	//char *strg = (char*)malloc((mess_len+1)*sizeof(char));
	//coupeEOF(payload, mess_len, strg);
	//payload[mess_len-1]='\0';
	
	if (regexec(httpVideo, payload, 0, NULL, 0)==0) {
		//free(strg);
		return 1;
	}
	//free(strg);
	return 0;
}

u_short isHTTPAudio (unsigned char *payload, const u16 mess_len) {
	//char *strg = (char*)malloc((mess_len+1)*sizeof(char));
	//coupeEOF(payload, mess_len, strg);
	//payload[mess_len-1]='\0';
	
	if (regexec(httpAudio, payload, 0, NULL, 0)==0) {
		//free(strg);
		return 1;
	}
	//free(strg);
	return 0;
}

u_short isPOP3 (unsigned char *payload, const u16 mess_len) {
	//char *strg = (char*)malloc((mess_len+1)*sizeof(char));
	//coupeEOF(payload, mess_len, strg);
	//payload[mess_len-1]='\0';
	
	if (regexec(pop3, payload, 0, NULL, 0)==0) {
		//free(strg);
		return 1;
	}
	//free(strg);
	return 0;
}

u_short isSMTP (unsigned char *payload, const u16 mess_len) {
	//char *strg = (char*)malloc((mess_len+1)*sizeof(char));
	//coupeEOF(payload, mess_len, strg);
	//payload[mess_len-1]='\0';
	
	if (regexec(smtp, payload, 0, NULL, 0)==0) {
		//free(strg);
		return 1;
	}
	//free(strg);
	return 0;
}

u_short isFTP (unsigned char *payload, const u16 mess_len) {
	//char *strg = (char*)malloc((mess_len+1)*sizeof(char));
	//coupeEOF(payload, mess_len, strg);
	//payload[mess_len-1]='\0';
	
	if (regexec(ftp, payload, 0, NULL, 0)==0) {
		//free(strg);
		return 1;
	}
	//free(strg);
	return 0;
}

u_short isSkypeOut (unsigned char *payload, const u16 mess_len) {
	
	//char *strg = (char*)malloc((mess_len+1)*sizeof(char));
	//coupeEOF(payload, mess_len, strg);
	//payload[mess_len-1]='\0';
	if (regexec(skypeOut, payload, 0, NULL, 0)==0) {
		//free(strg);
		return 1;
	}
	//free(strg);
	return 0;
}

u_short isSkypeToSkype (unsigned char *payload, const u16 mess_len) {
	
	//char *strg = (char*)malloc((mess_len+1)*sizeof(char));
	//coupeEOF(payload, mess_len, strg);
	//payload[mess_len-1]='\0';
	if (regexec(skypeToSkype, payload, 0, NULL, 0)==0) {
		//free(strg);
		return 1;
	}
	//free(strg);
	return 0;
}

u_short isSSL (unsigned char *payload, const u16 mess_len) {
	//char *strg = (char*)malloc((mess_len+1)*sizeof(char));
	//coupeEOF(payload, mess_len, strg);
	//payload[mess_len-1]='\0';
	if (regexec(ssl, payload, 0, NULL, 0)==0) {
		//free(strg);
		return 1;
	}
	//free(strg);
	return 0;
}

u_short isVALIDCERTSSL (unsigned char *payload, const u16 mess_len) {
	//char *strg = (char*)malloc((mess_len+1)*sizeof(char));
	//coupeEOF(payload, mess_len, strg);
	//payload[mess_len-1]='\0';
	if (regexec(validcertssl, payload, 0, NULL, 0)==0) {
		//free(strg);
		return 1;
	}
	//free(strg);
	return 0;
}

u_short isSSH (unsigned char *payload, const u16 mess_len) {
	//char *strg = (char*)malloc((mess_len+1)*sizeof(char));
	//coupeEOF(payload, mess_len, strg);
	//payload[mess_len-1]='\0';
	if (regexec(ssh, payload, 0, NULL, 0)==0) {
		//free(strg);
		return 1;
	}
	//free(strg);
	return 0;
}

u_short isNetBios (unsigned char *payload, const u16 mess_len) {
	//char *strg = (char*)malloc((mess_len+1)*sizeof(char));
	//coupeEOF(payload, mess_len, strg);
	//payload[mess_len-1]='\0';
	if (regexec(netbios, payload, 0, NULL, 0)==0) {
		//free(strg);
		return 1;
	}
	//free(strg);
	return 0;
}

u_short isNbns (unsigned char *payload, const u16 mess_len) {
	//char *strg = (char*)malloc((mess_len+1)*sizeof(char));
	//coupeEOF(payload, mess_len, strg);
	//payload[mess_len-1]='\0';
	if (regexec(nbns, payload, 0, NULL, 0)==0) {
		//free(strg);
		return 1;
	}
	//free(strg);
	return 0;
}

u_short isNbds (unsigned char *payload, const u16 mess_len) {
	//char *strg = (char*)malloc((mess_len+1)*sizeof(char));
	//coupeEOF(payload, mess_len, strg);
	//payload[mess_len-1]='\0';
	if (regexec(nbds, payload, 0, NULL, 0)==0) {
		//free(strg);
		return 1;
	}
	//free(strg);
	return 0;
}

u_short isBootstrap (unsigned char *payload, const u16 mess_len) {
	//char *strg = (char*)malloc((mess_len+1)*sizeof(char));
	//coupeEOF(payload, mess_len, strg);
	//payload[mess_len-1]='\0';
	if (regexec(bootstrap, payload, 0, NULL, 0)==0) {
		//free(strg);
		return 1;
	}
	//free(strg);
	return 0;
}

u_short isYouTube (unsigned char *payload, const u16 mess_len) {
	//char *strg = (char*)malloc((mess_len+1)*sizeof(char));
	//coupeEOF(payload, mess_len, strg);
	//payload[mess_len-1]='\0';
	if (regexec(youtube, payload, 0, NULL, 0)==0) {
		//free(strg);
		return 1;
	}
	//free(strg);
	return 0;
}

u_short isGoogleVideo (unsigned char *payload, const u16 mess_len) {
	//char *strg = (char*)malloc((mess_len+1)*sizeof(char));
	//coupeEOF(payload, mess_len, strg);
	//payload[mess_len-1]='\0';
	if (regexec(googlevideo, payload, 0, NULL, 0)==0) {
		//free(strg);
		return 1;
	}
	//free(strg);
	return 0;
}

u_short isZippyVideo (unsigned char *payload, const u16 mess_len) {
	//char *strg = (char*)malloc((mess_len+1)*sizeof(char));
	//coupeEOF(payload, mess_len, strg);
	//payload[mess_len-1]='\0';
	if (regexec(zippyvideo, payload, 0, NULL, 0)==0) {
		//free(strg);
		return 1;
	}
	//free(strg);
	return 0;
}

u_short isVeoh (unsigned char *payload, const u16 mess_len) {
	//char *strg = (char*)malloc((mess_len+1)*sizeof(char));
	//coupeEOF(payload, mess_len, strg);
	//payload[mess_len-1]='\0';
	if (regexec(veoh, payload, 0, NULL, 0)==0) {
		//free(strg);
		return 1;
	}
	//free(strg);
	return 0;
}

u_short isVidilife (unsigned char *payload, const u16 mess_len) {
	//char *strg = (char*)malloc((mess_len+1)*sizeof(char));
	//coupeEOF(payload, mess_len, strg);
	//payload[mess_len-1]='\0';
	if (regexec(vidilife, payload, 0, NULL, 0)==0) {
		//free(strg);
		return 1;
	}
	//free(strg);
	return 0;
}

u_short isOtherChat (unsigned char *payload, const u16 mess_len) {
        //char *strg = (char*)malloc((mess_len+1)*sizeof(char));
        //coupeEOF(payload, mess_len, strg);
        //payload[mess_len-1]='\0';
        if (regexec(otherChat, payload, 0, NULL, 0)==0) {
                //free(strg);
                return 1;
        }
        //free(strg);
        return 0;
}

u_short isOtherVideoTCP (unsigned char *payload, const u16 mess_len) {
        //char *strg = (char*)malloc((mess_len+1)*sizeof(char));
        //coupeEOF(payload, mess_len, strg);
        //payload[mess_len-1]='\0';
        if (regexec(otherVideoTCP, payload, 0, NULL, 0)==0) {
                //free(strg);
                return 1;
        }
        //free(strg);
        return 0;
}

u_short isOtherVideoUDP (unsigned char *payload, const u16 mess_len) {
        //char *strg = (char*)malloc((mess_len+1)*sizeof(char));
        //coupeEOF(payload, mess_len, strg);
        //payload[mess_len-1]='\0';
        if (regexec(otherVideoUDP, payload, 0, NULL, 0)==0) {
                //free(strg);
                return 1;
        }
        //free(strg);
        return 0;
}

u_short isOtherMail (unsigned char *payload, const u16 mess_len) {
        //char *strg = (char*)malloc((mess_len+1)*sizeof(char));
        //coupeEOF(payload, mess_len, strg);
        //payload[mess_len-1]='\0';
        if (regexec(otherMail, payload, 0, NULL, 0)==0) {
                //free(strg);
                return 1;
        }
        //free(strg);
        return 0;
}

u_short isOtherHTTP (unsigned char *payload, const u16 mess_len) {
        //char *strg = (char*)malloc((mess_len+1)*sizeof(char));
        //coupeEOF(payload, mess_len, strg);
        //payload[mess_len-1]='\0';
        if (regexec(otherHTTP, payload, 0, NULL, 0)==0) {
                //free(strg);
                return 1;
        }
        //free(strg);
        return 0;
}

u_short isMySQL (unsigned char *payload, const u16 mess_len) {
        //char *strg = (char*)malloc((mess_len+1)*sizeof(char));
        //coupeEOF(payload, mess_len, strg);
        //payload[mess_len-1]='\0';
        if (regexec(mySQL, payload, 0, NULL, 0)==0) {
                //free(strg);
                return 1;
        }
        //free(strg);
        return 0;
}

u_short isOtherDNS (unsigned char *payload, const u16 mess_len) {
        //char *strg = (char*)malloc((mess_len+1)*sizeof(char));
        //coupeEOF(payload, mess_len, strg);
        //payload[mess_len-1]='\0';
        if (regexec(otherDNS, payload, 0, NULL, 0)==0) {
                //free(strg);
                return 1;
        }
        //free(strg);
        return 0;
}

u_short isSoribada (unsigned char *payload, const u16 mess_len) {
        //char *strg = (char*)malloc((mess_len+1)*sizeof(char));
        //coupeEOF(payload, mess_len, strg);
        //payload[mess_len-1]='\0';
        if (regexec(soribada, payload, 0, NULL, 0)==0) {
                //free(strg);
                return 1;
        }
        //free(strg);
        return 0;
}

u_short isAP2PID(u_short id) {
	if( (id>100) && (id<201) ) 
		return 1;
	return 0;
}

u_short verID(u_short old_id, u_short new_id) {
        if(old_id == PROTO_ID_NONPAYLOAD) {//We can't classify a flow with NONPAYLOAD type only because his first packet
                return new_id;
        }
        else if( (old_id < DOWN_BASE_P2P_CLASS_NUMBER) ) {
		if( (new_id>= DOWN_BASE_P2P_CLASS_NUMBER) && (new_id<PROTO_ID_NONPAYLOAD) ) {
			return new_id;
		}
	} else if ( isSuperClass(old_id) ) { 
            	if( (new_id>=DOWN_BASE_P2P_CLASS_NUMBER) && ( (new_id<PROTO_ID_NONPAYLOAD) ) )
                	return new_id;
        } else if ( (old_id>UP_BASE_P2P_CLASS_NUMBER)&&(old_id<PROTO_ID_NONPAYLOAD) ){
                if( (new_id<=UP_BASE_P2P_CLASS_NUMBER) && (new_id>=DOWN_BASE_P2P_CLASS_NUMBER) )
                        return new_id;
        }
	return old_id;
}
u_short isSuperClass(u_short id) {
	if( (id==SSL_SUPER_CLASS_NUMBER) || (id==HTTP_SUPER_CLASS_NUMBER) || (id == 299) ) 
		return 1;
	return 0;
}
u_short getIdbyPort(u_short port) {
	if((port==4661)||(port==4881)||(port==4242)||(port==4662)||(port==4663)||(port==4665)||(port==4672))
		return 106;		//eDonkey, eMule, Kademlia 52->106
	if(((port>=6881)&&(port<=6999))||(port==6969))
                return 104;             //BitTorrent 54->104
	if((port==1214)||(port==1793)||(port==3011)||(port==1034))
                return 107;             //Kazaa 51->107
        if((port==6346))
                return 110;             //GNU 3 53->110
	if((port==4058)||(port==2234)||(port==5534))
                return 120;             //Soulseek 5 55->120
        if((port==4900)||(port==5900))
                return 115;             //Mute 13    63->115
	if((port==6699)||(port==6257)||(port==6666)||(port==7777))
                return 126;   //WinMX 62->126
        if((port==411))
                return 105;             //DirectConnect  67->105
        if((port==41170))
                return 125;             //MP2P  10      60->125
	return 0;
}
