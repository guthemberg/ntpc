#! /bin/csh
awk -F, -v output=$2 -v l4id="" -v proto="" -v sorte=0 -v class=0 -v flag=0 ' { \
	if(flag) { \
		class=$11 \
		if(class==1) { \
			sorte=107 \
			l4id="6" \
		} else if(class==2) { \
			sorte=106 \
			l4id="6" \
		} else if(class==3) { \
			sorte=110 \
			l4id="6" \
		} else if(class==4) { \
			sorte=104 \
			l4id="6" \
                } else if(class==5) { \
			sorte=120 \
			l4id="6" \
                } else if(class==6) { \
			sorte=102 \
			l4id="6" \
                } else if(class==7) { \
			sorte=105 \
			l4id="6" \
                } else if(class==8) { \
			sorte=124 \
			l4id="6" \
                } else if(class==9) { \
			sorte=103 \
			l4id="6" \
                } else if(class==10) { \
			sorte=125 \
			l4id="6" \
                } else if(class==11) { \
			sorte=116 \
			l4id="6" \
                } else if(class==12) { \
			sorte=306 \
			l4id="6" \
                } else if(class==15) { \
			sorte=0 \
			l4id="6" \
                } else if(class==22) { \
			sorte=106 \
			l4id="17" \
                } else if(class==21) { \
			sorte=107 \
			l4id="17" \
                } else if(class==23) { \
			sorte=110 \
			l4id="17" \
                } else if(class==30) { \
			sorte=125 \
			l4id="17" \
                } else if(class==28) { \
			sorte=124 \
			l4id="17" \
                } else if(class==29) { \
			sorte=1002 \
			l4id="17" \
                } else if(class==31) { \
			sorte=306 \
			l4id="17" \
                } else if(class==32) { \
			sorte=0 \
			l4id="17" \
                } else if(class==33) { \
			sorte=0 \
			l4id="17" \
                } else if(class==17) { \
			sorte=0 \
			l4id="17" \
                } else if(class==18) { \
			sorte=0 \
			l4id="18" \
                } else { \
			sorte=0 \
			l4id="19" \
                } \
		if(sorte<10) { \
			proto="000"sorte \
		} else if(sorte<100) { \
			proto="00"sorte \
		} else if(sorte<1000) { \
			proto="0"sorte \
		} else { \
			proto=sorte \
		} \
		printf("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n",$1,$2,$3,$4,$5,$6,$7,$8,$9,$10,proto,l4id) >> output \
		close(output) \
	} \
	flag=1 \
}' $1
exit
set id = $2
awk -F, -v ident="${id}#->#" -v isP2P=0 -v flag=0 -v marca=0 -v intervalos=1 -v bytes=0 -v flows=0 -v p2p_bytes=0 -v p2p_flows=0 -v edk_b -v edk_f=0 -v bit_b=0 -v bit_f=0 -v aut_b=0 -v aut_f=0 ' { \
        if(flag) { \
	        ts = $3 \
       		tm = $4 \
        	tf = ts + tm/1000000 \
		if(marca==0) { \
			marca=tf \
		} \
		inter = (tf-marca)/60 \
		if(inter>=(5*intervalos)) { \
			printf("%s,%d,%.0f,%.0f,%.0f,%.0f,%.0f,%.0f,%.0f,%.0f,%.0f,%.0f\n",ident,intervalos,bytes,flows,p2p_bytes,p2p_flows,edk_b,edk_f,bit_b,bit_f,aut_b,aut_f) \
			bytes=0 \
			flows=0 \
			p2p_bytes=0 \
			p2p_flows=0 \
			edk_b=0 \
			edk_f=0 \
			bit_b=0 \
			bit_f=0 \
			aut_b=0 \
			aut_f=0 \
			intervalos++ \
		} \
		sorte=$11 \
        	if( ((sorte)>=1)&&((sorte)<=11) ) { \
			p2p_bytes+=$9 \
			p2p_flows++ \
			isP2P=1 \
		} \
        	if( ((sorte)>=21)&&((sorte)<=23) ) { \
                        p2p_bytes+=$9 \
                        p2p_flows++ \
			isP2P=1 \
                } \
        	if( ((sorte)>=27)&&((sorte)<=28) ) { \
                        p2p_bytes+=$9 \
                        p2p_flows++ \
			isP2P=1 \
                } \
        	if( ((sorte)==30)) { \
                        p2p_bytes+=$9 \
                        p2p_flows++ \
			isP2P=1 \
                } \
		if( ((sorte)==2)||((sorte)==22) ) { \
                        edk_b+=$9 \
                        edk_f++ \
			isP2P=0 \
                } \
		if( ((sorte)==4) ) { \
                        bit_b+=$9 \
                        bit_f++ \
			isP2P=0 \
                } \
		if( ((isP2P)) ) { \
                        aut_b+=$9 \
                        aut_f++ \
                } \
		bytes+=$9 \
		flows++ \
		isP2P=0 \
	} \
	flag=1 \
}  END { \
	printf("%s,%d,%.0f,%.0f,%.0f,%.0f,%.0f,%.0f,%.0f,%.0f,%.0f,%.0f\n",ident,intervalos,bytes,flows,p2p_bytes,p2p_flows,edk_b,edk_f,bit_b,bit_f,aut_b,aut_f) \
	}' $1
