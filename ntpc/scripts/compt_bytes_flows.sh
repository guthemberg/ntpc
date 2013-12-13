#! /bin/csh
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
	printf("%s,%.0f,%.0f,%.0f,%.0f,%.0f,%.0f,%.0f,%.0f,%.0f,%.0f\n",ident,bytes,flows,p2p_bytes,p2p_flows,edk_b,edk_f,bit_b,bit_f,aut_b,aut_f) \
	}' $1
