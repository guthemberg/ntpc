#! /bin/csh
awk -F, -v total=0 -v marca=0 -v geral=0 -v fluxos=0 -v intervalos=1 ' { \
        if(fluxos>0) { \
	        ts = $3 \
       		tm = $4 \
        	tsi = $1 \
        	tmi = $2 \
        	tf = ts + tm/1000000 \
        	ti = tsi + tmi/1000000 \
		if(marca==0) { \
			marca=tf \
		} \
		inter = (tf-marca)/60 \
		if(inter>=5) { \
			intervalos++ \
			marca=0 \
		} \
		geral+=$9 \
		sorte=$11 \
        	if( ((sorte)>=1)&&((sorte)<=11) ) total+=$9 \
        	if( ((sorte)>=21)&&((sorte)<=23) ) total+=$9 \
        	if( ((sorte)>=27)&&((sorte)<=28) ) total+=$9 \
        	if( ((sorte)==30)) total+=$9 \
	} \
	fluxos++ \
}  END { \
          printf("Totais para bytes:\nTotal de bytes p2p: %.0f\nTotal geral: %.0f\nTaxa de p2p: %.6f\n",total,geral,(total/geral)); printf("Totais para fluxos:\nTotal geral de fluxos: %.0f\n",fluxos); printf("Quantidade de intervalos: %.0f\n",intervalos) }' $1
