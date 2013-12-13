#! /bin/csh
# Este script executa o script ver_eficiencia_to_2.sh para um intervado de dias determinado. Abaixo segue uma breve 
#decricao do script ver_eficiencia_to_2.sh:
#%csh ~/ver_eficiencia_to_2.sh
#quantidade de parametros inadequada. Use csh this_script.sh flag_compara_implementacoes traces_file path_to_implementation1 option [path_to_implementation2] [path_R_scripts]
#
#Descricao detalhada do script:
# o valor da variavel "opt" (valores possiveis, p2p, kaz, edk, bit, aut, all).
# Alem disso, a variavel "root" deve receber o ponto ond estao os diretorios de cada dia de coleta.
# Detro deste diretorio deve haver pastas cujos nomes devem obedecer o seguinte formato: ./ddmmaaaa
# O intervalo de dias a serem processados eh especificado com o conjunto de variaveis: "ini_day"(dd), "last_day"(dd), 
# "ini_mes"(mm), "last_mes"(mm) e "ano"(aaaa). O penultimo argumento diz respeito a pasta na qual serao gravadas as 
# informacoes resultates da implementacao profiling
# a variavel libeexec eh o local (caminho completo) onde estah armazenado o arquivo ver_eficiencia_to_2.sh
# O argumento numero 10 indica se serah feita uma comparacao (valor diferente de zero) ou se nao (valor igual a zero)
# Os ultimos dois argumentos dizem respeito as implementacoes que serao comparadas. Eles indicam os caminhos relativos as
# implementacoes
if ( ( $#argv > 9 ) && ( $#argv < 13 )   ) then
  set root = ${1}
  set ini_day = ${2}
  set last_day = ${3}
  set ini_mes = ${4}
  set last_mes = ${5}
  set ano = ${6}
  set libexec = ${7}
  set opt = ${8}
  set implementacao1 = ${9}
  set compara = ${10}
else
#Valores possiveis para option: p2p, edk, bit, kaz, aut
  echo "[RUN_PROF ERROR] Vc errou, tente:  #./apps.exe raiz ini_day last_day ini_mes last_mes ano dir_libexec option dir_implementacao_1 var_compara [dir_implentacao_2] [dir_R_scripts]"
  exit
endif
set casa = $root
cd $casa
if ( ! (-f ${libexec}/ver_eficiencia_to_2.sh) ) then
  echo "[RUN_PROF ERROR] O arquivo ${libexec}/ver_eficiencia_to_2.sh nao existe ou nao pode ser lido."
  exit
endif
set implementacao_2 = prof_master
set dir_R_scripts = ""

if ( $#argv > 11 ) then
  set implementacao_2 = ${11}
  set dir_R_scripts = ${12}
endif

@ mes = $ini_mes

set pasta="" 

while ( $mes <= ${last_mes} )
        @ dia = $ini_day 
        while ( $dia <= $last_day )
                if ( $dia < 10 ) then
			if ( $mes < 10 ) then
				set pasta = ./0${dia}0${mes}${ano}
			else
				set pasta = ./0${dia}${mes}${ano}
			endif
                        if ( -d ${pasta} ) then
                                cd ${pasta}
                                if ( -f ./result.txt.gz ) then
                                        echo "[RUN_PROF]DesCompactando o arquivo ${pasta}/result.txt.gz ..."
                                        gunzip result.txt.gz
                                        echo "[RUN_PROF]O arquivo ${pasta}/result.txt foi descompactado com sucesso."
					if(${compara}) then
					  echo "[RUN_PROF]Processando arquivo com ver_eficiencia_to_2.sh..."
					  csh ${libexec}/ver_eficiencia_to_2.sh ${compara} `pwd`/result.txt `pwd`/${implementacao1} ${opt} `pwd`/${implementacao2} ${dir_R_scripts}
					else
					  csh ${libexec}/ver_eficiencia_to_2.sh ${compara} `pwd`/result.txt `pwd`/${implementacao1} ${opt}
					endif
					echo "[RUN_PROF]Processando arquivo com run.sh..."
					echo "[RUN_PROF]Arquivo processado com ver_eficiencia_to_2.sh."
                                        echo "[RUN_PROF]Compactando o arquivo ${pasta}/result.txt ..."
                                        gzip result.txt
                                        echo "[RUN_PROF]O arquivo ${pasta}/result.txt foi compactado com sucesso."
                                endif
                        endif
                else
			if ( $mes < 10 ) then
				set pasta = ./${dia}0${mes}${ano}
			else
				set pasta = ./${dia}${mes}${ano}
			endif
                        if ( -d ${pasta} ) then
                                cd ${pasta}
                                if ( -f ./result.txt.gz ) then
                                        echo "[RUN_PROF]DesCompactando o arquivo ${pasta}/result.txt.gz ..."
                                        gunzip result.txt.gz
                                        echo "[RUN_PROF]O arquivo ${pasta}/result.txt foi descompactado com sucesso."
					if(${compara}) then
					  echo "[RUN_PROF]Processando arquivo com ver_eficiencia_to_2.sh..."
					  csh ${libexec}/ver_eficiencia_to_2.sh ${compara} `pwd`/result.txt `pwd`/${implementacao1} ${opt} `pwd`/${implementacao2} ${dir_R_scripts}
					else
					  csh ${libexec}/ver_eficiencia_to_2.sh ${compara} `pwd`/result.txt `pwd`/${implementacao1} ${opt}
					endif
					echo "[RUN_PROF]Processando arquivo com run.sh..."
					echo "[RUN_PROF]Arquivo processado com ver_eficiencia_to_2.sh."
                                        echo "[RUN_PROF]Compactando o arquivo ${pasta}/result.txt ..."
                                        gzip result.txt
                                        echo "[RUN_PROF]O arquivo ${pasta}/result.txt foi compactado com sucesso."
                                endif
                        endif
                endif
                cd $casa
                @ dia ++
        end
        @ mes ++
end
