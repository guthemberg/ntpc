#!/bin/csh
#Este objetivo tem como objetivo construir os graficos que possibilitarao dar uma visao geral da 
#implementacao. Eles exibirao valores relacionados as dimenssoes e a entropia.Os parametros neces
#sarios sao:
#$1 - Caminho para os arquivos que contem os resultados. Ex. : /caminho/completo/resultados
#$2 - caminho para um diretorio onde seja possivel escrever arquivos temporarios. Ex.: /any/tmp
#$3 - caminho pata o diretorio de scripts
if ( ( $#argv ) == 3 ) then
  if ( (!( -d $1 )) || (!( -d $2 )) || (!( -d $3 )) ) then
    echo "Ao menos Um dos argumentos fornecidos nao corresponde a um diretorio valido."
    exit
  endif
else
  echo "Execute :  csh apps.sh  /caminho/completo/resultados /any/tmp /caminho/para/scripts"
  exit
endif
set result_dir = $1
set tmp_dir = $2
set scripts_dir = $3
# O script abaixo eh o pondo principal de geracao de graficos
set scripts_but = ${scripts_dir}/R/function_section01.r
set tmp_script = ${tmp_dir}/tmp.r
printf "source(\042%s\042)\n" ${scripts_but} > ${tmp_script}
#echo "source(\"${scripts_but}\")" > ${tmp_script}
#Processamento para p2p_SRC_IP
printf "section1.function(\042p2p_SRC_IP\042,\042%s\042)\n" ${result_dir} >> ${tmp_script}
#Processamento para p2p_DST_IP
printf "section1.function(\042p2p_DST_IP\042,\042%s\042)\n" ${result_dir} >> ${tmp_script}
#Processamento para p2p_SRC_PRT
printf "section1.function(\042p2p_SRC_PRT\042,\042%s\042)\n" ${result_dir} >> ${tmp_script}
#Processamento para p2p_DST_PRT
printf "section1.function(\042p2p_DST_PRT\042,\042%s\042)\n" ${result_dir} >> ${tmp_script}
#processamento do arquivo R cpnstruido
R --no-save < ${tmp_script}
rm -rf ${tmp_script}
