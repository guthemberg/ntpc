#include "expressions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void allocateMemory() {
	http = (regex_t*) malloc(sizeof(regex_t));
	http2 = (regex_t*) malloc(sizeof(regex_t));
	dns = (regex_t*) malloc(sizeof(regex_t));
	irc = (regex_t*) malloc(sizeof(regex_t));
	msn = (regex_t*) malloc(sizeof(regex_t));
	aim = (regex_t*) malloc(sizeof(regex_t));
	yahooMess = (regex_t*) malloc(sizeof(regex_t));
	rtsp = (regex_t*) malloc(sizeof(regex_t));
	httpQuicktime = (regex_t*) malloc(sizeof(regex_t));
	httpVideo = (regex_t*) malloc(sizeof(regex_t));
	httpAudio = (regex_t*) malloc(sizeof(regex_t));
	pop3 = (regex_t*) malloc(sizeof(regex_t));
	smtp = (regex_t*) malloc(sizeof(regex_t));
	ftp = (regex_t*) malloc(sizeof(regex_t));
	hlcs = (regex_t*) malloc(sizeof(regex_t));
	skypeToSkype = (regex_t*) malloc(sizeof(regex_t));
	skypeOut = (regex_t*) malloc(sizeof(regex_t));
	ssh = (regex_t*) malloc(sizeof(regex_t));
	ssl = (regex_t*) malloc(sizeof(regex_t));
	validcertssl = (regex_t*) malloc(sizeof(regex_t));
	netbios = (regex_t*) malloc(sizeof(regex_t));
	nbns = (regex_t*) malloc(sizeof(regex_t));
	nbds = (regex_t*) malloc(sizeof(regex_t));
	bootstrap = (regex_t*) malloc(sizeof(regex_t));
	googlevideo = (regex_t*) malloc(sizeof(regex_t));
	youtube = (regex_t*) malloc(sizeof(regex_t));
	zippyvideo = (regex_t*) malloc(sizeof(regex_t));
	veoh = (regex_t*) malloc(sizeof(regex_t));
	vidilife = (regex_t*) malloc(sizeof(regex_t));
	napster = (regex_t*) malloc(sizeof(regex_t));
	otherChat = (regex_t*) malloc(sizeof(regex_t));
	otherVideoTCP = (regex_t*) malloc(sizeof(regex_t));
	otherVideoUDP = (regex_t*) malloc(sizeof(regex_t));
	otherMail = (regex_t*) malloc(sizeof(regex_t));
	mySQL = (regex_t*) malloc(sizeof(regex_t));
	otherDNS = (regex_t*) malloc(sizeof(regex_t));
	otherHTTP = (regex_t*) malloc(sizeof(regex_t));
	goBoogy = (regex_t*) malloc(sizeof(regex_t));
	soribada = (regex_t*) malloc(sizeof(regex_t));
	mms = (regex_t*) malloc(sizeof(regex_t));
	//ifilm = (regex_t*) malloc(sizeof(regex_t));
}

void loadExpressions() {
	allocateMemory();
	if (regcomp(msn, "ver [0-9]+ msnp[1-9][0-9]? [\x09-\x0d -~]* cvr0|usr [0-9] [!-~]+ *@*|ans 1 [!-~]+ [0-9. ]+\x0d\x0a$|cal [0-9] *@*|cal [0-9] ringing *|^(msg) *@*",REG_EXTENDED | REG_NOSUB| REG_ICASE)!=0)
                printf("Error. Couldn't load MSN regular expression\n");
	if (regcomp(aim, "^(\\*[\x01\x02].*\x03\x0b|\\*\x01.?.?.?.?\x01)|flapon|toc_signon.*0x",REG_EXTENDED | REG_NOSUB | REG_ICASE)!=0)
		  printf("Error. Couldn't load AIM regular expression\n");
	if (regcomp(irc,"^(nick[\x09-\x0d -~]*user[\x09-\x0d -~]*|user[\x09-\x0d -~]*|[\x02-\x0d -~]*nick[\x09-\x0d -~]*\x0d\x0a|:* notice *)|pong |join |:irc|ping |privmsg |watch |userhost ",REG_EXTENDED | REG_NOSUB | REG_ICASE)!=0)
		//^(nick[\x09-\x0d -~]*user[\x09-\x0d -~]*|user[\x09-\x0d -~]*|[\x02-\x0d -~]*nick[\x09-\x0d -~]*\x0d\x0a) antiga
		printf("Error. Couldn't load IRC regular expression\n");
	if (regcomp(yahooMess, "^(ymsg|ypns|yhoo).?.?.?.?.?.?.?[lwt].*\xc0\x80",REG_EXTENDED | REG_NOSUB | REG_ICASE)!=0)
		printf("Error. Couldn't load Yahoo Messenger regular expression\n");
	if (regcomp(http,"http/(0\\.9|1\\.0|1\\.1) [1-5][0-9][0-9] [\x09-\x0d -~]*|post [\x09-\x0d -~]* http/[01]\\.[019]"/*|get */,REG_EXTENDED | REG_NOSUB | REG_ICASE)!=0)
		printf("Error. Couldn't load HTTP regular expression\n");
	if (regcomp(httpVideo,"http/(0\\.9|1\\.0|1\\.1)[\x09-\x0d ][1-5][0-9][0-9][\x09-\x0d -~]*(content-type: video)",REG_EXTENDED | REG_NOSUB | REG_ICASE)!=0)
		printf("Error. Couldn't load HTTP Video regular expression\n");
	if (regcomp(httpQuicktime,"user-agent: quicktime \\(qtver=[0-9].[0-9].[0-9];os=[\x09-\x0d -~]+\\)\x0d\x0a|http/(0\\.9|1\\.0|1\\.1)[\x09-\x0d ][1-5][0-9][0-9][\x09-\x0d -~]*(content-type: video/quicktime)",REG_EXTENDED | REG_NOSUB | REG_ICASE)!=0)
		printf("Error. Couldn't load HTTP Quicktime regular expression\n");
	if (regcomp(httpAudio,"http/(0\\.9|1\\.0|1\\.1)[\x09-\x0d ][1-5][0-9][0-9][\x09-\x0d -~]*(content-type: audio)",REG_EXTENDED | REG_NOSUB | REG_ICASE)!=0)
		printf("Error. Couldn't load HTTP Audio regular expression\n");
	if (regcomp(http2,"get /[\x09-\x0d -~]+(http/[01]\\.[019])*",REG_EXTENDED | REG_NOSUB | REG_ICASE)!=0)
		printf("Error. Couldn't load HTTP2 regular expression\n");
	if (regcomp(dns, "^.?.?.?.?[\x01\x02].?.?.?.?.?.?[\x01-?][a-z0-9][\x01-?a-z]*[\x02-\x06][a-z][a-z][fglmoprstuvz]?[aeop]?(um)?[\x01-\x10\x1c][\x01\x03\x04\xFF]",REG_EXTENDED | REG_NOSUB | REG_ICASE)!=0)
		printf("Error. Couldn't load DNS regular expression\n");
	if (regcomp(smtp, "^220[\x09-\x0d -~]* (e?smtp|simple mail)",REG_EXTENDED | REG_NOSUB | REG_ICASE)!=0)
		printf("Error. Couldn't load SMTP regular expression\n");
	if (regcomp(pop3, "^(\\+ok |-err )",REG_EXTENDED | REG_NOSUB | REG_ICASE)!=0)
		printf("Error. Couldn't load POP3 regular expression\n");
	if (regcomp(otherMail, "^354 Enter mail|^250 (ok|sender|recipient)|^mail |^data\x0d\x0a|^rset\x0d\x0a|^ehlo|^Received:|^\\+ok |^rcpt to|stat\x0d\x0a|^\\* (ok|status|flags)|^done\x0d\x0a|^inbox\x0d\x0a|ompleted\x0d\x0a",REG_EXTENDED | REG_NOSUB | REG_ICASE)!=0)
                printf("Error. Couldn't load OtherMail regular expression\n");
	if (regcomp(ftp, "^220[\x09-\x0d -~]*ftp|^(331|pass)[\x09-\x0d -~]*passwor|^(230|syst)[\x09-\x0d -~]*user logged in|^user[\x09-\x0d -~]|^421 *",REG_EXTENDED | REG_NOSUB | REG_ICASE)!=0)
		printf("Error. Couldn't load FTP regular expression\n");
	if (regcomp(skypeToSkype, "^..\x02...............",REG_EXTENDED | REG_NOSUB | REG_ICASE)!=0)
		printf("Error. Couldn't load Skype To Skype regular expression\n");
	if (regcomp(skypeOut, "^(\x01.?.?.?.?.?.?.?.?\x01|\x02.?.?.?.?.?.?.?.?\x02|\x03.?.?.?.?.?.?.?.?\x03|\x04.?.?.?.?.?.?.?.?\x04|\x05.?.?.?.?.?.?.?.?\x05|\x06.?.?.?.?.?.?.?.?\x06|\x07.?.?.?.?.?.?.?.?\x07|\x08.?.?.?.?.?.?.?.?\x08|\x09.?.?.?.?.?.?.?.?\x09|\x0a.?.?.?.?.?.?.?.?\x0a|\x0b.?.?.?.?.?.?.?.?\x0b|\x0c.?.?.?.?.?.?.?.?\x0c|\x0d.?.?.?.?.?.?.?.?\x0d|\x0e.?.?.?.?.?.?.?.?\x0e|\x0f.?.?.?.?.?.?.?.?\x0f|\x10.?.?.?.?.?.?.?.?\x10|\x11.?.?.?.?.?.?.?.?\x11|\x12.?.?.?.?.?.?.?.?\x12|\x13.?.?.?.?.?.?.?.?\x13|\x14.?.?.?.?.?.?.?.?\x14|\x15.?.?.?.?.?.?.?.?\x15|\x16.?.?.?.?.?.?.?.?\x16|\x17.?.?.?.?.?.?.?.?\x17|\x18.?.?.?.?.?.?.?.?\x18|\x19.?.?.?.?.?.?.?.?\x19|\x1a.?.?.?.?.?.?.?.?\x1a|\x1b.?.?.?.?.?.?.?.?\x1b|\x1c.?.?.?.?.?.?.?.?\x1c|\x1d.?.?.?.?.?.?.?.?\x1d|\x1e.?.?.?.?.?.?.?.?\x1e|\x1f.?.?.?.?.?.?.?.?\x1f|\x20.?.?.?.?.?.?.?.?\x20|\x21.?.?.?.?.?.?.?.?\x21|\x22.?.?.?.?.?.?.?.?\x22|\x23.?.?.?.?.?.?.?.?\x23|\\$.?.?.?.?.?.?.?.?\\$|\x25.?.?.?.?.?.?.?.?\x25|\x26.?.?.?.?.?.?.?.?\x26|\x27.?.?.?.?.?.?.?.?\x27|\\(.?.?.?.?.?.?.?.?\\(|\\).?.?.?.?.?.?.?.?\\)|\\*.?.?.?.?.?.?.?.?\\*|\\+.?.?.?.?.?.?.?.?\\+|\x2c.?.?.?.?.?.?.?.?\x2c|\x2d.?.?.?.?.?.?.?.?\x2d|\\..?.?.?.?.?.?.?.?\\.|\x2f.?.?.?.?.?.?.?.?\x2f|\x30.?.?.?.?.?.?.?.?\x30|\x31.?.?.?.?.?.?.?.?\x31|\x32.?.?.?.?.?.?.?.?\x32|\x33.?.?.?.?.?.?.?.?\x33|\x34.?.?.?.?.?.?.?.?\x34|\x35.?.?.?.?.?.?.?.?\x35|\x36.?.?.?.?.?.?.?.?\x36|\x37.?.?.?.?.?.?.?.?\x37|\x38.?.?.?.?.?.?.?.?\x38|\x39.?.?.?.?.?.?.?.?\x39|\x3a.?.?.?.?.?.?.?.?\x3a|\x3b.?.?.?.?.?.?.?.?\x3b|\x3c.?.?.?.?.?.?.?.?\x3c|\x3d.?.?.?.?.?.?.?.?\x3d|\x3e.?.?.?.?.?.?.?.?\x3e|\\?.?.?.?.?.?.?.?.?\\?|\x40.?.?.?.?.?.?.?.?\x40|\x41.?.?.?.?.?.?.?.?\x41|\x42.?.?.?.?.?.?.?.?\x42|\x43.?.?.?.?.?.?.?.?\x43|\x44.?.?.?.?.?.?.?.?\x44|\x45.?.?.?.?.?.?.?.?\x45|\x46.?.?.?.?.?.?.?.?\x46|\x47.?.?.?.?.?.?.?.?\x47|\x48.?.?.?.?.?.?.?.?\x48|\x49.?.?.?.?.?.?.?.?\x49|\x4a.?.?.?.?.?.?.?.?\x4a|\x4b.?.?.?.?.?.?.?.?\x4b|\x4c.?.?.?.?.?.?.?.?\x4c|\x4d.?.?.?.?.?.?.?.?\x4d|\x4e.?.?.?.?.?.?.?.?\x4e|\x4f.?.?.?.?.?.?.?.?\x4f|\x50.?.?.?.?.?.?.?.?\x50|\x51.?.?.?.?.?.?.?.?\x51|\x52.?.?.?.?.?.?.?.?\x52|\x53.?.?.?.?.?.?.?.?\x53|\x54.?.?.?.?.?.?.?.?\x54|\x55.?.?.?.?.?.?.?.?\x55|\x56.?.?.?.?.?.?.?.?\x56|\x57.?.?.?.?.?.?.?.?\x57|\x58.?.?.?.?.?.?.?.?\x58|\x59.?.?.?.?.?.?.?.?\x59|\x5a.?.?.?.?.?.?.?.?\x5a|\\[.?.?.?.?.?.?.?.?\\[|\\].?.?.?.?.?.?.?.?\\]|\x5d.?.?.?.?.?.?.?.?\x5d|\\^.?.?.?.?.?.?.?.?\\^|\x5f.?.?.?.?.?.?.?.?\x5f|\x60.?.?.?.?.?.?.?.?\x60|\x61.?.?.?.?.?.?.?.?\x61|\x62.?.?.?.?.?.?.?.?\x62|\x63.?.?.?.?.?.?.?.?\x63|\x64.?.?.?.?.?.?.?.?\x64|\x65.?.?.?.?.?.?.?.?\x65|\x66.?.?.?.?.?.?.?.?\x66|\x67.?.?.?.?.?.?.?.?\x67|\x68.?.?.?.?.?.?.?.?\x68|\x69.?.?.?.?.?.?.?.?\x69|\x6a.?.?.?.?.?.?.?.?\x6a|\x6b.?.?.?.?.?.?.?.?\x6b|\x6c.?.?.?.?.?.?.?.?\x6c|\x6d.?.?.?.?.?.?.?.?\x6d|\x6e.?.?.?.?.?.?.?.?\x6e|\x6f.?.?.?.?.?.?.?.?\x6f|\x70.?.?.?.?.?.?.?.?\x70|\x71.?.?.?.?.?.?.?.?\x71|\x72.?.?.?.?.?.?.?.?\x72|\x73.?.?.?.?.?.?.?.?\x73|\x74.?.?.?.?.?.?.?.?\x74|\x75.?.?.?.?.?.?.?.?\x75|\x76.?.?.?.?.?.?.?.?\x76|\x77.?.?.?.?.?.?.?.?\x77|\x78.?.?.?.?.?.?.?.?\x78|\x79.?.?.?.?.?.?.?.?\x79|\x7a.?.?.?.?.?.?.?.?\x7a|\\|.?.?.?.?.?.?.?.?\\|)",REG_EXTENDED | REG_NOSUB | REG_ICASE)!=0)
		printf("Error. Couldn't load Skype Out regular expression\n");
	/*if (regcomp(hl2death, "^(..(\x08\x08\x10\x10)..(\x08\x10)|..(\x09\x08\x10\x10)..(\x09\x08))",REG_EXTENDED | REG_NOSUB | REG_ICASE)!=0)
	printf("Erro ao carregar a expressao regular Half Life 2\n");*/
	if (regcomp(rtsp, "rtsp/1\\.0 200 ok|^(play|pause) rtsp",REG_EXTENDED | REG_NOSUB | REG_ICASE)!=0)
		printf("Error. Couldn't load RTSP regular expression\n");
	if (regcomp(hlcs, "^\xff\xff\xff\xff(get(info|challenge)|infostring|infostringresponse|ping|details|players|connect|a00000000|rules|status)",REG_EXTENDED | REG_NOSUB | REG_ICASE)!=0)
		printf("Erro ao carregar a expressao regular HalfLife Counter-Strike\n");
	if (regcomp(ssl, "^(.?.?\x16\x03.*\x16\x03|.?.?\x01\x03\x01?.*\x0b)",REG_EXTENDED | REG_NOSUB | REG_ICASE)!=0)
		printf("Error. Couldn't load SSL regular expression\n");
	if (regcomp(validcertssl, "^.?.?\x01\x03\x01?.*\x0b.*(thawte|equifax secure certificate authority|rsa data security, inc|verisign, inc|gte cybertrust root|entrust\\.net limited)",REG_EXTENDED | REG_NOSUB | REG_ICASE)!=0)
		printf("Error. Couldn't load VALIDCERTSSL regular expression\n");	
	if (regcomp(ssh, "^ssh-[12]\\.[0-9]",REG_EXTENDED | REG_NOSUB | REG_ICASE)!=0)
		printf("Error. Couldn't load SSH regular expression\n");
	if (regcomp(netbios, "\x81.?.?.[A-P][A-P][A-P][A-P][A-P][A-P][A-P][A-P][A-P][A-P][A-P][A-P][A-P][A-P][A-P][A-P][A-P][A-P][A-P][A-P][A-P][A-P][A-P][A-P][A-P][A-P][A-P][A-P][A-P][A-P][A-P][A-P][A-P][A-P][A-P][A-P][A-P][A-P][A-P][A-P]",REG_EXTENDED | REG_NOSUB | REG_ICASE)!=0)
		printf("Error. Couldn't load NetBios regular expression\n");
	if (regcomp(nbns, "\x01\x10\x01|\\)\x10\x01\x01|0\x10\x01",REG_EXTENDED | REG_NOSUB | REG_ICASE)!=0)
		printf("Error. Couldn't load Nbns regular expression\n");
	if (regcomp(nbds, "^(\x10|\x11|\x12|\x13|\x14|\x15|\x16)(\x02|\x0a|\x0e)............*",REG_EXTENDED | REG_NOSUB | REG_ICASE)!=0)
		printf("Error. Couldn't load Nbds regular expression\n");
	if (regcomp(bootstrap, "^(\x02|\x01)(\x01|\x06|\x07|\x15|\x16|\x17|\x18|\x19|\x20)..............................*",REG_EXTENDED | REG_NOSUB | REG_ICASE)!=0)
		printf("Error. Couldn't load Bootstrap regular expression\n");
	if (regcomp(googlevideo, "^get /googleplayer\\.swf\\?&videoUrl=http[!-~]+",REG_EXTENDED | REG_NOSUB | REG_ICASE)!=0)
		printf("Error. Couldn't load GoogleVideo regular expression\n");
	if (regcomp(youtube, "^get /player2\\.swf\\?video_id=.*&l=[!-~]",REG_EXTENDED | REG_NOSUB | REG_ICASE)!=0)
		printf("Error. Couldn't load YouTube regular expression\n");
	if (regcomp(zippyvideo, "^get /images/player\\.swf\\?storageId=[0-9]&userNam[!-~].*", REG_EXTENDED | REG_NOSUB |REG_ICASE) != 0)
		printf("Error. Couldn't load ZippyVideo regular expression\n");
	if (regcomp(veoh, "^get /multiplayer\\.swf\\?inVeoh=(tr..|fa...)", REG_EXTENDED | REG_NOSUB |REG_ICASE) != 0)
		printf("Error. Couldn't load Veoh regular expression\n");
	if (regcomp(vidilife, "^get /flash/flvplayer\\.swf\\?video[!-~]*", REG_EXTENDED | REG_NOSUB |REG_ICASE) != 0)
		printf("Error. Couldn't load Vidilife regular expression\n");
	if (regcomp(napster, "^(.[\x02\x06][!-~]+ [!-~]+ [0-9][0-9]?[0-9]?[0-9]?[0-9]? \"[\x09-\x0d -~]+\" ([0-9]|10)|1(send|get)[!-~]+ \"[\x09-\x0d -~]+\")", REG_EXTENDED | REG_NOSUB |REG_ICASE) != 0)
		printf("Error. Couldn't load Napster regular expression\n");
	if (regcomp(otherChat, "^png\x0d\x0a|^usr |^(cvr|qng|chg).[0-9]|nln (idl|nln)|^ymsg..\x00|^\x2a\x05..\x00\x00$|^\x50\x4e\x41\x00\x01|^msg |^joi |^\x2a\x02....update_bud|^\x2a\x02..\x00.\x00.\x00.\x00\x00", REG_EXTENDED | REG_NOSUB |REG_ICASE) != 0)
        	printf("Error. Couldn't load outrosChat regular expression\n");
	if (regcomp(otherVideoTCP, "^..._parame|icy |^connected\x0d\x0a\x0d\x0a|^..........\x00\x00ml20", REG_EXTENDED | REG_NOSUB |REG_ICASE) != 0)
        	printf("Error. Couldn't load outrosVideoTCP regular expression\n");
	if (regcomp(otherVideoUDP, "^........applicat", REG_EXTENDED | REG_NOSUB |REG_ICASE) != 0)
	        printf("Error. Couldn't load outrosVideoUDP regular expression\n");
	if (regcomp(mySQL, "^....\x03(select|insert|show|update)", REG_EXTENDED | REG_NOSUB |REG_ICASE) != 0)
                printf("Error. Couldn't load MySQL regular expression\n");
	if (regcomp(otherDNS, "^....\x00\x01\x00(\x00|\x01)\x00.\x00|^\x01\x02\x00\x07\xd1\x86\x3f\xc3", REG_EXTENDED | REG_NOSUB |REG_ICASE) != 0)
                printf("Error. Couldn't load otherDNS regular expression\n");
	if (regcomp(otherHTTP, "^(head|search|propfind)", REG_EXTENDED | REG_NOSUB |REG_ICASE) != 0)
                printf("Error. Couldn't load otherHTTP regular expression\n");
	if (regcomp(otherHTTP, "^\xc2\x00...$|^.\x00..\x00\x00..\x02\x00(users_|.(creat|play))", REG_EXTENDED | REG_NOSUB |REG_ICASE) != 0)
                printf("Error. Couldn't load gamesTCP regular expression\n");
	if (regcomp(goBoogy, "<peerplat>|^get /getfilebyhash\\.cgi\\?|^get /queue_register\\.cgi\\?|^get /getupdowninfo\\.cgi\\?", REG_EXTENDED | REG_NOSUB |REG_ICASE) != 0)
                printf("Error. Couldn't load GoBoogy regular expression\n");
	if (regcomp(soribada, "^GETMP3\x0d\x0aFilename|^\x01.?.?.?(\x51\x3a\\+|\x51\x32\x3a)|^\x10[\x14-\x16]\x10[\x15-\x17].?.?.?.?$", REG_EXTENDED | REG_NOSUB |REG_ICASE) != 0)
                printf("Error. Couldn't load Soribada regular expression\n");
	if (regcomp(mms, "^............mms ", REG_EXTENDED | REG_NOSUB |REG_ICASE) != 0)
		printf("Error. Couldn't load MMS regular expression\n");
}

void freeExpressions() {
	free(http);
	free(http2);
	free(dns);
	free(irc);
	free(msn);
	free(aim);
	free(yahooMess);
	free(rtsp);
	free(httpQuicktime);
	free(httpVideo);
	free(httpAudio);
	free(pop3);
	free(smtp);
	free(ftp);
	free(hlcs);
	free(skypeToSkype);
	free(skypeOut);
	free(ssh);
	free(ssl);
	free(validcertssl);
	free(netbios);
	free(nbns);
	free(nbds);
	free(bootstrap);
	free(googlevideo);
	free(youtube);
	free(zippyvideo);
	free(veoh);
	free(vidilife);
	free(napster);
	free(otherChat);
	free(otherVideoTCP);
	free(otherVideoUDP);
	free(otherMail);
	free(mySQL);
        free(otherDNS);
        free(otherHTTP);
        free(goBoogy);
	free(soribada);
	free(mms);
}
