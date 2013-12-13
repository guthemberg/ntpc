/**
 * P2P Classifier module
 * Bsased on IPP2P Project (http://www.ipp2p.org/)
 */

#ifndef _CLASSIFIER_H_
#define _CLASSIFIER_H_

#include "analyserpxTypes.h"
#include "expressions.h"

/*Convertion function-like macro to interger types to*/
#define get_u8(X,O)  (*(__u8 *)(X + O))
#define get_u16(X,O)  (*(__u16 *)(X + O))
#define get_u32(X,O)  (*(__u32 *)(X + O))
/*Smallest classification number*/
#define UP_BASE_P2P_CLASS_NUMBER 200  //minor classification number
#define DOWN_BASE_P2P_CLASS_NUMBER 101  //minor classification number
#define HTTP_SUPER_CLASS_NUMBER 201  //minor classification number
#define SSL_SUPER_CLASS_NUMBER 1302  //minor classification number

/* The last column of the flow file (printed file) identify the tranport protocol below the IP, it can be filled
 * with one of these numbers: 0 for UDP and 1 for TCP
 * or it also can be filled with 2 that identifies ICMP or 3 (Unknown type)
 */

#define PROTO_ID_TCP		IPPROTO_TCP
#define PROTO_ID_EDONKEY	106	// also "Emule" and "Kademlia"
#define PROTO_ID_BITTORRENT	104
#define PROTO_ID_KAZAA		107
#define PROTO_ID_GNU		110
#define PROTO_ID_GOOBOGY        111 //new, korean per-to-peer, see netfilter's site
#define PROTO_ID_SORIBADA       119 //new, korean per-to-peer, see netfilter's site
#define PROTO_ID_SOULSEEK	120
#define PROTO_ID_ARES		103
#define PROTO_ID_WINMX		126
#define PROTO_ID_MUTE		115
#define PROTO_ID_NAP		116
#define PROTO_ID_XDCC		128
#define PROTO_ID_DIRECTCONNECT	105
#define PROTO_ID_APPLEJUICE	102
#define PROTO_ID_WASTE		129
#define PROTO_ID_UDP		IPPROTO_UDP
/*#define PROTO_ID_EDKUDP		130
#define PROTO_ID_BITTORRENTUDP	131
#define PROTO_ID_KAZAAUDP	132
#define PROTO_ID_GNUUDP		133*/
#define PROTO_ID_ICMP		IPPROTO_ICMP
#define PROTO_ID_OTHER		19
//new
#define PROTO_ID_UNKNOWN	0
#define PROTO_ID_NONPAYLOAD	3000
#define PROTO_ID_HTTP		201
#define PROTO_ID_OTHERHTTP      299
#define PROTO_ID_AIM		301
#define PROTO_ID_IRC		303
#define PROTO_ID_MSN		306
#define PROTO_ID_YAHOOMESS	308
#define PROTO_ID_OTHERCHAT	399
#define PROTO_ID_HLCS		403
#define PROTO_ID_HL2DEATH	407
#define PROTO_ID_HL2CS		415
#define PROTO_ID_HLDEATH	416
#define PROTO_ID_QUAKE3		417
#define PROTO_ID_DNS		501
#define PROTO_ID_NETBIOS	506
#define PROTO_ID_NBNS		509
#define PROTO_ID_NBDS		510
#define PROTO_ID_BOOTSTRAP	511
#define PROTO_ID_OTHERDNS       599
#define PROTO_ID_RTSP		601
#define PROTO_ID_HTTPQUICKTIME	602
#define PROTO_ID_HTTPVIDEO	606
#define PROTO_ID_HTTPAUDIO	608
#define PROTO_ID_MMS	        609
#define PROTO_ID_GOOGLEVIDEO	611
#define PROTO_ID_YOUTUBE	612
#define PROTO_ID_ZIPPYVIDEO	613
#define PROTO_ID_VEOH		614
#define PROTO_ID_VIDILIFE	615
#define PROTO_ID_OTHERVIDEO	699
#define PROTO_ID_POP3		703
#define PROTO_ID_SMTP		704
#define PROTO_ID_OTHERMAIL	799
#define PROTO_ID_FTP		801
#define PROTO_ID_MYSQL          802
#define PROTO_ID_SKYPETOSKYPE	1002
#define PROTO_ID_SKYPEOUT	1001
#define PROTO_ID_SSH		1301
#define PROTO_ID_SSL		1302
#define PROTO_ID_VALIDCERTSSL	1303
//end

#define PROTO_NAME_TCP			"TCP"
#define PROTO_NAME_EDONKEY		"eDonkey"
#define PROTO_NAME_EMULE		"eMule"
#define PROTO_NAME_KADEMLIA		"KademliaExt"
#define PROTO_NAME_BITTORRENT		"BitTorrent"
#define PROTO_NAME_KAZAA		"Kazaa"
#define PROTO_NAME_GNU			"GNU"
#define PROTO_NAME_GOBOOGY              "Goboogy"
#define PROTO_NAME_SORIBADA             "Soribada"
#define PROTO_NAME_SOULSEEK		"Soulseek"
#define PROTO_NAME_ARES			"Ares"
#define PROTO_NAME_WINMX		"WinMX"
#define PROTO_NAME_MUTE			"Mute"
#define PROTO_NAME_NAP			"Napster"
#define PROTO_NAME_XDCC			"Xdcc"
#define PROTO_NAME_DIRECTCONNECT	"DirectConnect"
#define PROTO_NAME_APPLEJUICE		"AppleJuice"
#define PROTO_NAME_WASTE		"Waste"
#define PROTO_NAME_UDP			"UDP"
/*#define PROTO_NAME_EDKUDP		"edkUDP"
#define PROTO_NAME_BITTORRENTUDP	"BiTtorrentUDP"
#define PROTO_NAME_KAZAAUDP		"kazaaUDP"
#define PROTO_NAME_GNUUDP		"gnuUDP"*/
#define PROTO_NAME_ICMP			"ICMP"
#define PROTO_NAME_OTHER		"Other"
//new
#define PROTO_NAME_UNKNOWN		"Unknwon"
#define PROTO_NAME_NONPAYLOAD		"NonPayload"
#define PROTO_NAME_HTTP			"HTTP"
#define PROTO_NAME_OTHERHTTP            "OtherHTTP"
#define PROTO_NAME_AIM			"AIM"
#define PROTO_NAME_IRC			"IRC"
#define PROTO_NAME_MSN			"MSNMessenger"
#define PROTO_NAME_YAHOOMESS		"YahooMessenger"
#define PROTO_NAME_OTHERCHAT            "OtherChat"
#define PROTO_NAME_HLCS			"HalfLifeCounterStrike"
#define PROTO_NAME_HL2DEATH		"HalfLife2Deathmatch"
#define PROTO_NAME_HL2CS		"HalfLife2CounterStrike"
#define PROTO_NAME_HLDEATH		"HalfLifeDeathmatch"
#define PROTO_NAME_QUAKE3		"Quake3"
#define PROTO_NAME_DNS			"DNS"
#define PROTO_NAME_OTHERDNS             "OtherDNS"
#define PROTO_NAME_RTSP			"RTSP"
#define PROTO_NAME_HTTPQUICKTIME	"HTTPQuicktime"
#define PROTO_NAME_HTTPVIDEO		"HTTPVideo"
#define PROTO_NAME_YOUTUBE		"YouTube"
#define PROTO_NAME_GOOGLEVIDEO		"GoogleVideo"
#define PROTO_NAME_ZIPPYVIDEO		"ZippyVideo"
#define PROTO_NAME_VEOH			"Veoh"
#define PROTO_NAME_VIDILIFE		"Vidilife"
#define PROTO_NAME_MMS	                "MMS"
#define PROTO_NAME_OTHERVIDEO           "OtherVideo"
#define PROTO_NAME_HTTPAUDIO		"HTTPAudio"
#define PROTO_NAME_POP3			"POP3"
#define PROTO_NAME_SMTP			"SMTP"
#define PROTO_NAME_FTP			"FTP"
#define PROTO_NAME_MYSQL                "MySQL"
#define PROTO_NAME_OTHERMAIL		"OtherMail"
#define PROTO_NAME_SKYPETOSKYPE		"SkypeToSkype"
#define PROTO_NAME_SKYPEOUT		"SkypeOut"
#define PROTO_NAME_SSL			"SSL"
#define PROTO_NAME_VALIDCERTSSL		"VALIDCERTSSL"
#define PROTO_NAME_SSH			"SSH"
#define PROTO_NAME_NETBIOS		"NetBios"
#define PROTO_NAME_NBNS			"NBNS"
#define PROTO_NAME_NBDS			"NBDS"
#define PROTO_NAME_BOOTSTRAP		"Bootstrap"
//end new

/*The types were defined to agree with the IPP2P functions*/
/*typedef unsigned char u8;
typedef unsigned char __u8;
typedef unsigned short u16;
typedef unsigned short __u16;
typedef unsigned long int u32;
typedef unsigned long int __u32;
typedef unsigned short u_short;*/

/**
  * getID returns the type recognized by the ipp2p signature-matching classifier
  * @param *iph		IP header structure (payload included).
  * @param *ipLen		Colected IP packet length.
  */
u_short getID(const struct ip *iph, u_short ipLen);
/**
  * Look for the BitTorrent messege's signature in payload message from TCP segments.
  * @param *payload		Message string.
  * @param *mess_len		Message string length.
  */
u_short isBittorrent (const unsigned char *payload, const u16 mess_len);
/**
  * Look for the Ares application's signature in payload message from TCP segments.
  * @param *payload		Message string.
  * @param *mess_len		Message string length.
  */
u_short isAres (const unsigned char *payload, const u16 mess_len);
/**
  * Look for the Soul application's signature in payload message from TCP segments.
  * @param *payload		Message string.
  * @param *mess_len		Message string length.
  */
u_short isSoul (const unsigned char *payload, const u16 mess_len);
/**
  * Look for the eDonkey application's signature in payload message from UDP segments.
  * @param *payload		Message string.
  * @param *mess_len		Message string length.
  */
u_short isEdku (const unsigned char *payload, const u16 mess_len);
/**
  * Look for the GNU application's signature in payload message from UDP segments.
  * @param *payload		Message string.
  * @param *mess_len		Message string length.
  */
u_short isGnuu (const unsigned char *payload, const u16 mess_len);
/**
  * Look for the Direct Connect application's signature in payload message from UDP segments.
  * @param *payload		Message string.
  * @param *mess_len		Message string length.
  */
u_short isDcu (const unsigned char *payload, const u16 mess_len);
/**
  * Look for the Apple Juice application's signature in payload message from UDP segments.
  * @param *payload		Message string.
  * @param *mess_len		Message string length.
  */
u_short isApple(const unsigned char *payload, const u16 mess_len);
/**
  * Look for the Kazaa application's signature in payload message from TCP segments.
  * @param *payload		Message string.
  * @param *mess_len		Message string length.
  */
u_short isKazaa (const unsigned char *payload, const u16 mess_len);
/**
  * Look for the Direct Connect application's signature in payload message from TCP segments.
  * @param *payload		Message string.
  * @param *mess_len		Message string length.
  */
u_short isDc (const unsigned char *payload, const u16 mess_len);
/**
  * Look for the GNU application's signature in payload message from TCP segments.
  * @param *payload		Message string.
  * @param *mess_len		Message string length.
  */
u_short isGnu (const unsigned char *payload, const u16 mess_len);
/**
  * Look for the eDonkey application's signature in payload message from TCP segments.
  * @param *payload		Message string.
  * @param *mess_len		Message string length.
  */
u_short isEdk (const unsigned char *payload, const u16 mess_len);
/**
  * Look for the eDonkey application's signature in payload message from TCP segments (low way).
  * @param *payload		Message string.
  * @param *mess_len		Message string length.
  */
u_short isEdk_all (const unsigned char *payload, const u16 mess_len);
/**
  * Look for the WinMX application's signature in payload message from TCP segments.
  * @param *payload		Message string.
  * @param *mess_len		Message string length.
  */
u_short isWinMX (const unsigned char *payload, const u16 mess_len);
/**
  * Look for the Mute application's signature in payload message from TCP segments.
  * @param *payload		Message string.
  * @param *mess_len		Message string length.
  */
u_short isMute (const unsigned char *payload, const u16 mess_len);
/**
  * Look for the XDCC application's signature in payload message from TCP segments.
  * @param *payload		Message string.
  * @param *mess_len		Message string length.
  */
u_short isXdcc (const unsigned char *payload, const u16 mess_len);
/**
  * Look for the Waste application's signature in payload message from TCP segments.
  * @param *payload		Message string.
  * @param *mess_len		Message string length.
  */
u_short isWaste(const unsigned char *payload, const u16 mess_len);
/**
  * Look for the BitTorrent application's signature in payload message from UDP segments.
  * @param *payload		Message string.
  * @param *mess_len		Message string length.
  */
u_short isBittorrentu (const unsigned char *payload, const u16 mess_len);
/**
  * Look for the Kazaa application's signature in payload message from TCP segments (low way).
  * @param *payload		Message string.
  * @param *mess_len		Message string length.
  */
u_short isKazaa_all (const unsigned char *payload, const u16 mess_len);
/**
  * Look for the Direct Connect application's signature in payload message from TCP segments (low way).
  * @param *payload		Message string.
  * @param *mess_len		Message string length.
  */
u_short isDc_all (const unsigned char *payload, const u16 mess_len);
/**
  * Look for the GNU application's signature in payload message from TCP segments (low way).
  * @param *payload		Message string.
  * @param *mess_len		Message string length.
  */
u_short isGnu_all (const unsigned char *payload, const u16 mess_len);
/**
  * Look for the Kazaa application's signature in payload message from UDP segments.
  * @param *payload		Message string.
  * @param *mess_len		Message string length.
  */
u_short isKazaau (const unsigned char *payload, const u16 mess_len);
/**
  * Look for the MP2P application's signature in payload message from TCP segments.
  * @param *payload		Message string.
  * @param *mess_len		Message string length.
  */
u_short isMP2P (const unsigned char *payload, const u16 mess_len);
/**
  * Look for the OpenNap application's signature in payload message from TCP segments.
  * @param *payload		Message string.
  * @param *mess_len		Message string length.
  */
u_short isNap (unsigned char *payload, const u16 mess_len);
/**
  * Look for the EarthS5 application's signature in payload message from TCP segments.
  * @param *payload		Message string.
  * @param *mess_len		Message string length.
  */
u_short isEarthS5 (const unsigned char *payload, const u16 mess_len);
/**
  * Look for the MP2P application's signature in payload message from UDP segments.
  * @param *payload		Message string.
  * @param *mess_len		Message string length.
  */
u_short isMP2Pu (const unsigned char *payload, const u16 mess_len);
/**
  * Look for the Eartha pplication's signature in payload message from UDP segments.
  * @param *payload		Message string.
  * @param *mess_len		Message string length.
  */
u_short isEarthu (const unsigned char *payload, const u16 mess_len);
/**
  * Look for the GoBoogy application's signature in payload message from UDP segments.
  * @param *payload             Message string.
  * @param *mess_len            Message string length.
  */
u_short isGoBoogyu (unsigned char *payload, const u16 mess_len);
/**
  * Look for the GoBoogy application's signature in payload message from TCP segments.
  * @param *payload             Message string.
  * @param *mess_len            Message string length.
  */
u_short isGoBoogy (unsigned char *payload, const u16 mess_len);
/**
  * Look for the Soribada application's signature in payload message from TCP/UDP segments.
  * @param *payload             Message string.
  * @param *mess_len            Message string length. 
  */
u_short isSoribada (unsigned char *payload, const u16 mess_len);
/**
 * Look for the HTTP protocol's signature in payload message from TCP/UDP segments.
 * @param *payload		Message string.
 * @param *mess_len		Message string length.
 */
u_short isHTTP (unsigned char *payload, const u16 mess_len);
/**
 * Look for the AIM protocol's signature in payload message from TCP/UDP segments.
 * @param *payload		Message string.
 * @param *mess_len		Message string length.
 */
u_short isAIM (unsigned char *payload, const u16 mess_len);
/**
 * Look for the IRC protocol's signature in payload message from TCP/UDP segments.
 * @param *payload		Message string.
 * @param *mess_len		Message string length.
 */
u_short isIRC (unsigned char *payload, const u16 mess_len);
/**
 * Look for the MSN Messenger protocol's signature in payload message from TCP/UDP segments.
 * @param *payload		Message string.
 * @param *mess_len		Message string length.
 */
u_short isMSN (unsigned char *payload, const u16 mess_len);
/**
 * Look for the Yahoo Messenger protocol's signature in payload message from TCP/UDP segments.
 * @param *payload		Message string.
 * @param *mess_len		Message string length.
 */
u_short isYahooMess (unsigned char *payload, const u16 mess_len);
/**
 * Look for the Half Life Counter-Strike game's signature in payload message from TCP/UDP segments.
 * @param *payload		Message string.
 * @param *mess_len		Message string length.
 */
u_short isHLCS (unsigned char *payload, const u16 mess_len);
/**
 * Look for the Half Life 2 Deathmatch game's signature in payload message from TCP/UDP segments.
 * @param *payload		Message string.
 * @param *mess_len		Message string length.
 */
u_short isHL2DEATH (const unsigned char *payload, const u16 mess_len);
/**
 * Look for the Half Life 2 Counter-Strike game's signature in payload message from TCP/UDP segments.
 * @param *payload		Message string.
 * @param *mess_len		Message string length.
 */
u_short isHL2CS (const unsigned char *payload, const u16 mess_len);
/**
 * Look for the Half Life Deathmatch game's signature in payload message from TCP/UDP segments.
 * @param *payload		Message string.
 * @param *mess_len		Message string length.
 */
u_short isHLDEATH (const unsigned char *payload, const u16 mess_len);
/**
 * Look for the Quake 3 game's signature in payload message from TCP/UDP segments.
 * @param *payload		Message string.
 * @param *mess_len		Message string length.
 */
u_short isQUAKE3 (const unsigned char *payload, const u16 mess_len);
/**
 * Look for the DNS protocol's signature in payload message from UDP segments.
 * @param *payload		Message string.
 * @param *mess_len		Message string length.
 */
u_short isDNS (unsigned char *payload, const u16 mess_len);
/**
 * Look for the RTSP protocol's signature in payload message from TCP/UDP segments.
 * @param *payload		Message string.
 * @param *mess_len		Message string length.
 */
u_short isRTSP (unsigned char *payload, const u16 mess_len);
/**
 * Look for the Quicktime under HTTP protocol's signature in payload message from TCP/UDP segments.
 * @param *payload		Message string.
 * @param *mess_len		Message string length.
 */
u_short isHTTPQuicktime (unsigned char *payload, const u16 mess_len);
/**
 * Look for Video under HTTP protocol's signature in payload message from TCP/UDP segments.
 * @param *payload		Message string.
 * @param *mess_len		Message string length.
 */
u_short isHTTPVideo (unsigned char *payload, const u16 mess_len);
/**
 * Look for Audio under HTTP protocol's signature in payload message from TCP/UDP segments.
 * @param *payload		Message string.
 * @param *mess_len		Message string length.
 */
u_short isHTTPAudio (unsigned char *payload, const u16 mess_len);
/**
 * Look for the POP3  protocol's signature in payload message from TCP/UDP segments.
 * @param *payload		Message string.
 * @param *mess_len		Message string length.
 */
u_short isPOP3 (unsigned char *payload, const u16 mess_len);
/**
 * Look for the SMTP protocol's signature in payload message from TCP/UDP segments.
 * @param *payload		Message string.
 * @param *mess_len		Message string length.
 */
u_short isSMTP (unsigned char *payload, const u16 mess_len);
/**
 * Look for the FTP protocol's signature in payload message from TCP/UDP segments.
 * @param *payload		Message string.
 * @param *mess_len		Message string length.
 */
u_short isFTP (unsigned char *payload, const u16 mess_len);
/**
 * Look for Skype (VOIP) application's signature in payload message from UDP segments.
 * @param *payload		Message string.
 * @param *mess_len		Message string length.
 */
u_short isSkypeOut (unsigned char *payload, const u16 mess_len);
/**
 * Look for Skype (CHAT) application's signature in payload message from UDP segments.
 * @param *payload		Message string.
 * @param *mess_len		Message string length.
 */
u_short isSkypeToSkype (unsigned char *payload, const u16 mess_len);
/**
 * Look for the SSL protocol's signature in payload message from TCP/UDP segments.
 * @param *payload		Message string.
 * @param *mess_len		Message string length.
 */
u_short isSSL (unsigned char *payload, const u16 mess_len);
/**
 * Look for the VALIDCERTSSL (SSL subset) protocol's signature in payload message from TCP/UDP segments.
 * @param *payload		Message string.
 * @param *mess_len		Message string length.
 */
u_short isVALIDCERTSSL (unsigned char *payload, const u16 mess_len);
/**
 * Look for the SSH protocol's signature in payload message from TCP/UDP segments.
 * @param *payload		Message string.
 * @param *mess_len		Message string length.
 */
u_short isSSH (unsigned char *payload, const u16 mess_len);
/**
 * Look for the NetBios protocol's signature in payload message from TCP/UDP segments.
 * @param *payload		Message string.
 * @param *mess_len		Message string length.
 */
u_short isNetBios (unsigned char *payload, const u16 mess_len);
/**
 * Look for the Nbns protocol's signature in payload message from TCP/UDP segments.
 * @param *payload		Message string.
 * @param *mess_len		Message string length.
 */
u_short isNbns (unsigned char *payload, const u16 mess_len);
/**
 * Look for the Nbds protocol's signature in payload message from TCP/UDP segments.
 * @param *payload		Message string.
 * @param *mess_len		Message string length.
 */
u_short isNbds (unsigned char *payload, const u16 mess_len);
/**
 * Look for the Bootstrap protocol's signature in payload message from UDP segments.
 * @param *payload		Message string.
 * @param *mess_len		Message string length.
 */
u_short isBootstrap (unsigned char *payload, const u16 mess_len);
/**
 * Look for YouTube's videos from TCP segments.
 * @param *payload		Message string.
 * @param *mess_len		Message string length.
 */
u_short isYouTube (unsigned char *payload, const u16 mess_len);
/**
 * Look for GoogleVideo's videos from TCP segments.
 * @param *payload		Message string.
 * @param *mess_len		Message string length.
 */
u_short isGoogleVideo (unsigned char *payload, const u16 mess_len);
/**
 * Look for ZippyVideo's videos from TCP segments.
 * @param *payload		Message string.
 * @param *mess_len		Message string length.
 */
u_short isZippyVideo (unsigned char *payload, const u16 mess_len);
/**
 * Look for Veoh's videos from TCP segments.
 * @param *payload		Message string.
 * @param *mess_len		Message string length.
 */
u_short isVeoh (unsigned char *payload, const u16 mess_len);
/**
 * Look for Vidilife's videos from TCP segments.
 * @param *payload		Message string.
 * @param *mess_len		Message string length.
 */
u_short isVidilife (unsigned char *payload, const u16 mess_len);
/**
 * Look for ifilm's videos from TCP segments.
 * @param *payload		Message string.
 * @param *mess_len		Message string length.
 */
u_short isIfilm (unsigned char *payload, const u16 mess_len);
/**
 * Look for other Chat applications from TCP segments.
 * @param *payload              Message string.
 * @param *mess_len             Message string length.
 */
u_short isOtherChat (unsigned char *payload, const u16 mess_len);
/**
 * Look for other Video Streaming types from TCP segments.
 * @param *payload              Message string.
 * @param *mess_len             Message string length.
 */
u_short isOtherVideoTCP (unsigned char *payload, const u16 mess_len);
/**
 * Look for other Video Streaming types from UDP segments.
 * @param *payload              Message string.
 * @param *mess_len             Message string length.
 */
u_short isOtherVideoUDP (unsigned char *payload, const u16 mess_len);
/**
 * Look for MMS from TCP segments.
 * @param *payload              Message string.
 * @param *mess_len             Message string length.     
 */
u_short isMMS (unsigned char *payload, const u16 mess_len);

u_short isOtherMail (unsigned char *payload, const u16 mess_len);

u_short isOtherHTTP (unsigned char *payload, const u16 mess_len);

u_short isOtherDNS (unsigned char *payload, const u16 mess_len);

u_short isMySQL (unsigned char *payload, const u16 mess_len);

u_short isAP2PID(u_short id);

u_short verID(u_short old_id, u_short new_id);

u_short isSuperClass(u_short id);

u_short getIdbyPort(u_short port);

extern int STR_MAX_LEN;

#endif
