#!bin/csh
#Este scripts recebe um arquivo de traces e o corta em um pedaco de uam quantidade de horas predefinidas
# salavando o resultado em um arquivo de saida
# O tempo de amostra eh dado em horas, que serao contadas a partir da hora inicial fornecida
#Abaixo segue a descricao dos argumentos:
# O argumento $1 eh o arquivo de entrada
#$2 eh o arquivo de saida
#Intervalo de tempo a ser coletado $3
#hora inicial $4
rm -rf $2
awk -F, -v path=${2} -v ini=$4 -v end=0 -v inter=$3 -v flag=1 'BEGIN { } { \
      if(flag) { \
        printf("%s\n",$0) >> path \
        close(path) \
        getline \
        ini=( (ini*(60)*(60)) + ($3+( ($4)/(1000000) )) ) \
        flag=0 \
      } \
      end=$3+( ($4)/(1000000) ) \
      if( ((end - ini) < (inter*(60)*(60)))&&((end - ini)>=0) ) { \
        printf("%s\n",$0) >> path \
        close(path) \
      } \
      if ( (end - ini) >= ( inter*(60)*(60) ) ) \
        exit 0 \
    } END { }' $1
