#!/bin/csh
# esse script faz o seguinte: processa um arquivo de entrada(argumento 1) e gera uma linha para um determinado bc(argumento 2), o resultado serah jogado no arquivo de saida (terceiro argumento), o ultimo parametro (parametro quatro) eh o local onde serao armazenados os resultados, (quarto parametro desabilitado)
# Construcao do relatorio de totais de bytes com flow-report
#if(!((nr_fluxos==0)&&(volume==0)&&(tempo==0)&&(nr_pacotes==0)) )
awk -F, -v bc=$2 -v freq=0 -v flag=$3 ' { \
        if($3 == bc) { \
          if(flag) { \
            freq++ \
          } else { \
            if((($4!=0)||($5!=0)||($6!=0)||($7!=0)) ) \
              freq++ \
          } \
        } \
}  END { \
          printf("%d,%.0f\n",bc,freq) }' $1
