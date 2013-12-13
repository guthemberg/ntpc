#! /bin/csh
if ( ( $#argv == 6 ) ) then
	set traces_file=$1
	if ( !(-f $traces_file) ) then
		echo "[SEPARADOR ERROR]O arquivo $traces_file no existe ou no pode ser lido."
		exit
	endif
	set dist_file=$2
	if ( (-f $dist_file) ) then
		rm -rf $dist_file
	endif
	touch $dist_file
	if ( !(-f $dist_file) ) then
		echo "[SEPARADOR ERROR]O arquivo $dist_file no existe ou no pode ser lido."
		exit
	endif
	@ intervalo=$3
        if ( !( ( $intervalo > 0 ) && ( $intervalo < 25 ) ) ) then
        	echo "[SEPARADOR ERROR]O intervalo $intervalo deve estar entre os valores 1 e 24."
                exit
        endif
	@ hora_inicial=$4
	if ( !( ( $hora_inicial >= 0 ) && ( $hora_inicial < 24 ) ) ) then
		echo "[SEPARADOR ERROR]O intervalo $hora_inicial deve estar entre os valores 0 e 23."
		exit
	endif
	set log_file=$5
	if ( (-f $log_file) ) then
		rm -rf $log_file
	endif
	touch $log_file
	if ( !(-f $log_file) ) then
		echo "[SEPARADOR ERROR]O arquivo $log_file no existe ou no pode ser lido."
		exit
	endif
	@ limp = $6
	if ( !( ( $limp == 0 ) || ( $limp == 1 ) ) ) then
		echo "[SEPARADOR ERROR]Os valores para o limpdador tem que ser 0 ou 1 e nao  $limp."
		exit
	endif
else
	if ( ( $#argv == 0 ) ) then
		echo -n "Informe o arquivo de traces:"
		set traces_file = ($<)
		if ( !(-f $traces_file) ) then
			echo "[SEPARADOR ERROR]O arquivo $traces_file no existe ou no pode ser lido."
			exit
		endif
		echo -n "Informe o arquivo destino:"
		set dist_file = ($<)
		if ( (-f $dist_file) ) then
			rm -rf $dist_file
		endif
		touch $dist_file
		if ( !(-f $dist_file) ) then
			echo "[SEPARADOR ERROR]O arquivo $dist_file no existe ou no pode ser lido."
			exit
		endif
		echo -n "Informe o Intervalo de tempo:"
		@ intervalo = ($<)
		if ( !( ( $intervalo > 0 ) && ( $intervalo < 25 ) ) ) then
			echo "[SEPARADOR ERROR]O intervalo $intervalo deve estar entre os valores 1 e 24."
			exit
		endif
		echo -n "Informe  a hora inicial:"
		@ hora_inicial = ($<)
		if ( !( ( $hora_inicial >= 0 ) && ( $hora_inicial < 24 ) ) ) then
			echo "[SEPARADOR ERROR]O intervalo $hora_inicial deve estar entre os valores 0 e 23."
			exit
		endif
		echo -n "Informe o arquivo de log:"
		set log_file = ($<)
		if ( (-f $log_file) ) then
			rm -rf $log_file
		endif
		touch $log_file
		if ( !(-f $log_file) ) then
			echo "[SEPARADOR ERROR]O arquivo $log_file no existe ou no pode ser lido."
			exit
		endif
		echo -n "Habilitar o modo limpeza?(0/1):"
		@ limp = ($<)
		if ( !( ( $limp == 0 ) || ( $limp == 1 ) ) ) then
			echo "[SEPARADOR ERROR]Os valores para o limpdador tem que ser 0 ou 1 e nao  $limp."
			exit
		endif
	else
  		echo "[SEPARADOR ERROR] Vc errou, tente:  #csh separador.sh traces_file dist_file intervalo hora_inicial log_file limp"
  		echo "[SEPARADOR ERROR] Ou:  #csh separador.sh "
  		exit
	endif
endif
awk -F, -v conte=0 -v flag=1 -v marca=1 -v linhas=0 -v ti=0 -v horasi=0 -v conta=0 -v horas=0 -v t0=0 -v tf=0 -v ts=0 -v tm=0 -v path=$dist_file -v intervaloh=$intervalo -v hi=$hora_inicial -v logfile=$log_file -v registrados=0 -v limpar=$limp '{ \
      if( (linhas>0)&&(NF == 12) ) { \
	ts = $3 \
	tm = $4 \
	tsi = $1 \
	tmi = $2 \
	tf = ts + tm/1000000 \
	ti = tsi + tmi/1000000 \
	if(((tf-ti)>=0)&&(ts>=0)&&(tm>=0)&&(tsi>=0)&&(tmi>=0)) { \
 	 	if(t0==0) { \
			t0=tf \
			horas=0 \
		} else { \
			horas=(tf-t0)/(3600) \
		} \
 		if((horas>marca)) { \
			printf("Hora %d\n",marca) >> logfile \
			close(logfile) \
			marca++ \
		} \
		if(limpar) { \
				if((horasi)<intervaloh) printf("%s\n",$0) >> path \
				close(path) \
				registrados++ \
		} else { \
			if((horas)>=hi) { \
				if(flag) { \
					printf("Estamos Gravando registros.\n") >> logfile \
					close(logfile) \
					flag-- \
				} \
				if(conta==0) { \
					conta=tf \
					horasi=0 \
				} else { \
					horasi=(tf-conta)/(3600) \
				} \
				if((horasi)<intervaloh) printf("%s\n",$0) >> path \
				close(path) \
				registrados++ \
			} \
		} \
	} else { \
		printf("tempo:%.2fs, linha: %d, registro: %s\n",tf-ti,linhas,$0) >> logfile \
		close(logfile) \
	} \
      } else { \
	if(NF != 12 ) { \
		printf("Registro Incorreto no. ") >> logfile \
		close(logfile) \
		print FNR >> logfile \
		close(logfile) \
		printf("%s\n"$0) >> logfile \
		close(logfile) \
	} else { \
		printf("%s\n",$0) >> path \
                close(path) \
	} \
      } \
      linhas++ \
  } END { \
	printf("No. de linhas: %.0f\nNo. de linhas registradas: %.0f\n",linhas,registrados) >> logfile \
	close(logfile) \
  }' $traces_file
