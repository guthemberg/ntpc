#!/bin/csh
# esse script faz o seguinte: processa um arquivo de entrada(argumento 1) e gera uma linha para um determinado bc(argumento 2), o resultado serah jogado no arquivo de saida (terceiro argumento), o ultimo parametro (parametro quatro) eh o local onde serao armazenados os resultados, (quarto parametro desabilitado)
# Construcao do relatorio de totais de bytes com flow-report
awk -F, -v ind=$3 -v bc=$2 -v tempo=0 -v nr_fluxos=0 -v volume=0 -v nr_pacotes=0 ' { \
        if($1 == bc) { \
          nr_fluxos+=$2 \
          volume+=$3 \
          tempo+=$4 \
          nr_pacotes+=$5 \
        } \
}  END { \
        if(!((nr_fluxos==0)&&(volume==0)&&(tempo==0)&&(nr_pacotes==0)) ) \
          printf("%s,%d,%.0f,%.0f,%.6f,%.0f\n",ind,bc,nr_fluxos,volume,tempo,nr_pacotes) }' $1
