#!/bin/csh
# esse script faz o seguinte: processa um arquivo de entrada(argumento 1) e gera uma linha para um determinado bc(argumento 2), o resultado serah jogado no arquivo de saida (terceiro argumento), o ultimo parametro (parametro quatro) eh o local onde serao armazenados os resultados, (quarto parametro desabilitado)
# Construcao do relatorio de totais de bytes com flow-report
#if(!((nr_fluxos==0)&&(volume==0)&&(tempo==0)&&(nr_pacotes==0)) )
#Arquivo fonte em $1:
#tempo,apps,nr_fluxos,volume,tempo,nr_pacotes
#1,all,60,97661584,49638.340039,175633
#echo "chegou em barra1"
awk -F, -v bc=$2 -v apps=$3 -v flag=0 -v nr_fluxos=0 -v volume=0 -v tempo=0 -v nr_pacotes=0 -v input=$4 ' { \
	if (flag) { \
		print "begin" \
		print $0 \
		getline < input \
		print $0 \
		print "end" \
#		nr_fluxos+=$3 \
#		volume+=$4 \
#		tempo+=$5 \
#		nr_pacotes+=$6 \
	} else { \
		getline < input \
		flag = 1 \
	} \
}' $1
exit
  END { \
          printf("%d,%s,%.0f,%.0f,%.6f,%.0f\n",bc,apps,nr_fluxos,volume,tempo,nr_pacotes) }' $1
