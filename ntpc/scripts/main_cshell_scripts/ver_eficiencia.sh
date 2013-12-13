#!/bin/csh
#Este script tem como finalidade comparar a completure dos bytes caracterizados como p2p pela implementacao do profiling
# Os argumentos sao so seguintes:
# $1 - arquivos de traces. Ex.: /caminho/para/o/arquivo/result.txt
# $2 - padrao das pastas experimentais. Ex.: experimento_
# $3 - quantidade de pastas. Ex.: 3. Isso quer dizer: experimento_1, experimento_2 e experimento_3
# $4 - diretorip pai das pastas experimento. Ex.: /path/to/directories_experimento_/
# $5 - Diretorio para a raiz onde estao os scripts. Ex.: /path/to/scripts_directories/
# O resultado deste script eh o valor percentual entre o total P2P presente e o que havia no trace
if ( !( -d ./tmp ) ) then
  echo " O diretorio ./tmp nao existe ou nao pode ser lido"
  exit
endif
cd $4
set dir = ./tmp/total.txt
set resultados = ./tmp/resultados.txt
awk -F, -v total=0 -v path=${dir} ' { \
        sorte=$11 \
        if( ((sorte)>=1)&&((sorte)<=11) ) total+=$9 \
        if( ((sorte)>=21)&&((sorte)<=23) ) total+=$9 \
        if( ((sorte)>=27)&&((sorte)<=28) ) total+=$9 \
        if( ((sorte)==30)) total+=$9 \
}  END { \
          printf("Veja: %.0f\n",total); printf("%.0f\n",total) > path }' $1
cat ${dir}
@ total = `cat ${dir}`
echo $total
@ i = 1
@ max = $3
@ max++
echo "indice,eficiencia"
echo "indice,eficiencia" > ${resultados}
while ( $i < ${max} )
  awk -F, -v ind=${i} -v geral=${total} -v total=0 -v input=${dir} -v output=${resultados} ' { \
        total+=$5 \
  }  END { \
          getline <input; total=total/$0;printf("%i,%.6f\n",ind,total);printf("%i,%.6f\n",ind,total) >> output;close(output) }' ./experimento_${i}/resultados/p2p_TS_SRC_IP.txt
  @ i++
end
#O conjunto de comandos a seguir serve apenas para a comparaco de dois resultados
echo "A figura 1 soh poderah ser gerada com sucesso se houver apenas dois resuldados gerados acima"
echo -n "Deseja continuar (s/n):"
set resp=($<)
if ( (resp == s) && ( ${max} == 3 ) ) then
  R --no-save < ./experimento_1/scripts/R/figura_1.r
  echo "Grafico gerado em ./tmp/figura_1.png"
endif
#Deletar arquivos temporarios
rm -rf ${dir}
rm -rf ${resultados}
