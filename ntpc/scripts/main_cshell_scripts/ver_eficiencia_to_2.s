#!/bin/csh
#Este script tem como finalidade comparar a completude dos bytes caracterizados como p2p pela implementacao do profiling
#No final ele compara duas implementacoes e gera um grafico
# Os argumentos sao so seguintes:
# $1 - variavel comparadora de implementacoes, se possuir um valor diferente de zero as implementacoes serao comparadas
# caso contrario, sera cnsiderada apenas a primeira implementacao, o resultado serah impresso na tela e serao ignoradas as
# variaveis 4 e 5
# $2 - arquivos de traces. Ex.: /caminho/para/o/arquivo/result.txt
# $3 - implementacao 1 (implementacao padrao do profiling)
# $4 - Option para o arquivo de resultados. Os valores possiveis sao: p2p, edk, bit, kaz, aut, all
# $5 - implementacao 2 (implementacao com melhoramentos para o trafego p2p)
# $6 - diretorip raiz dos dos scrpts R
# O resultado deste script eh o valor percentual entre o total P2P presente e o que havia no trace
if ( ( $#argv < 4 ) || ( $#argv > 6 ) ) then
  echo "quantidade de parametros inadequada. Use csh this_script.sh flag_compara_implementacoes traces_file path_to_implementation1 option [path_to_implementation2] [path_R_scripts]"
  exit
endif
@ compara = $1
set opt = $4
if ( !( -d ./tmp ) ) then
  echo -n " O diretorio ./tmp nao existe ou nao pode ser lido. Deseja cria-lo(s/n): "
#  set resp=($<)
  set resp=s
  if ( (${resp} == s)  ) then
    mkdir ./tmp
  else
    echo "Goodbye\!"
    exit
  endif
endif
echo "aqui 1"
if ( !( -f $2 ) ) then
  echo " O arquivo $2 nao existe ou nao pode ser lido"
  exit
endif
echo "aqui 2"
if($compara) then
  if ( (!( -d $3 ))||(!( -d $5 )) ) then
    echo " Uma das pastas das implementacoes nao existe ou nao pode ser lida"
    exit
  endif
else
  if ( (!( -d $3 ))) then
    echo " Uma das pastas das implementacoes nao existe ou nao pode ser lida"
    exit
  endif
endif
set implementacoes = ( $3 )
if($compara) then
  set implementacoes = ( $3 $5 )
else
  set implementacoes = ( $3 )
endif
echo "aqui 3"
set r_scripts = $6
set dir = ./tmp/total.txt
set resultados = ./tmp/resultados.txt
rm -rf ${resultados}
awk -F, -v total=0 -v path=${dir} ' { \
        sorte=$11 \
        if( ((sorte)>=1)&&((sorte)<=11) ) total+=$9 \
        if( ((sorte)>=21)&&((sorte)<=23) ) total+=$9 \
        if( ((sorte)>=27)&&((sorte)<=28) ) total+=$9 \
        if( ((sorte)==30)) total+=$9 \
}  END { \
          printf("Veja: %.0f\n",total); printf("%.0f\n",total) > path }' $2
cat ${dir}
@ total = `cat ${dir}`
echo $total
@ i = 1
@ max = 3
#echo "indice,eficiencia"
echo "aqui 4"
if($compara) then
  echo "indice,eficiencia" > ${resultados}
  while ( $i < ${max} )
    awk -F, -v ind=${i} -v geral=${total} -v total=0 -v input=${dir} -v output=${resultados} ' { \
          total+=$5 \
    }  END { \
            getline <input; total=total/$0;printf("I%i,%.6f,%.2f%%\n",ind,total,total*100);printf("%i,%.6f\n",ind,total) >> output;close(output) }' $implementacoes[${i}]/resultados/${opt}_TS_SRC_IP.txt
    @ i++
  end
  #O conjunto de comandos a seguir serve apenas para a comparaco de dois resultados
  echo "A figura 1 soh poderah ser gerada com sucesso se houver apenas dois resuldados gerados acima"
  echo -n "Deseja continuar (s/n):"
  set resp=($<)
  if ( (${resp} == s) && ( ${max} == 3 ) ) then
    if ( !( -f ${r_scripts}/figura_1.r ) ) then
      echo " O arquivo /figura_1.r nao existe ou nao pode ser lido."
      exit
    endif
    R --no-save < ${r_scripts}/figura_1.r
    echo "Grafico gerado em ./tmp/figura_1.png"
  endif
else
  @ max = 2
  echo "aqui 5"
  echo "indice,eficiencia" > ${resultados}
  echo "aqui 5.1"
  echo "aqui 5.2 $implementacoes[${i}]/resultados/${opt}_TS_SRC_IP.txt"
  if ( -f $implementacoes[${i}]/resultados/${opt}_TS_SRC_IP.txt ) then
    while ( $i < ${max} )
	echo "variaveis ${i} ${total} ${dir} ${resultados} "
      awk -F, -v ind=${i} -v geral=${total} -v total=0 -v input=${dir} -v output=${resultados} ' { \
            total+=$5 \
      }  END { \
              getline <input; total=total/$0;printf("I%i,%.6f,%.2f%%\n",ind,total,total*100);printf("%i,%.6f\n",ind,total) >> output;close(output) }' $implementacoes[${i}]/resultados/${opt}_TS_SRC_IP.txt
      @ i++
    end
  else
    echo "O arquivo  $implementacoes[${i}]/resultados/${opt}_TS_SRC_IP.txt nao existe ou nao pode ser lido"
    exit
  endif
  echo "aqui 5.5"
endif
#Deletar arquivos temporarios
rm -rf ${dir}
#Deletando arquivos de resultados
  echo "aqui 6"
echo "exibindo resultados de $2 :"
cat ${resultados}
rm -rf ${resultados}
