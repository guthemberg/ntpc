#! /bin/csh
#Este executa uma versao do profiling por um intervalo de tempo determinado
# a versao deve ser especificada em libexec, onde jah deve haver uma versao do profiling no formato binario "libexec" 
# aguardado pelo script run.sh (deste mesmo diretorio de scripts ). Ainda em relacao do script ru.sh, devem ser informados
# o valor da variavel "beta" para o algoritmo profiling, a opcao "opt" (valores possiveis, p2p, kaz, edk, bit, aut, all).
# Alem disso, a variavel "root" deve receber o ponto ond estao os diretorios de cada dia de coleta.
# Detro deste diretorio deve haver pastas cujos nomes devem obedecer o seguinte formato: ./ddmmaaaa
# O intervalo de dias a serem processados eh especificado com o conjunto de variaveis: "ini_day", "last_day", "ini_mes"
# , "last_mes" e "ano"
# O penultimo argumento diz respeito a pasta na qual serao gravadas as informacoes resultates da implementacao profiling
# O ultimo argumento eh a variavel que indica que tipo de "mix" haverah, valores possiveis sao 0 ou diferente de 0
#//mix determina se as tabelas devem ser adicionadas (0) ou s edeve ser feita a interseccao delas (1)
if ( ( $#argv == 8 ) ) then
  set root = ${1}
  set day = ${2}
  set month = ${3}
  set year = ${4}
  set period = ${5}
  set libexec = ${6}
  set opt = ${7}
  set beta = ${8}
else
#Valores possiveis para option: p2p, edk, bit, kaz, aut
  echo "[RUN_TRAINNING ERROR] Vc errou, tente:  #./apps.exe raiz day mes ano periodo dir_libexec option beta_value"
  exit
endif
set casa = $root
cd $casa

if ( !( -d ${libexec}/scripts ) ) then
	echo "O diretorio ${libexec}/scripts nao existe, verifique a variavel dir_libexec."
	exit
endif


#csh ${libexec}/scripts/main_cshell_scripts/run.sh ${libexec} .. ${opt} ${beta} ${mix}
#${libexec}/main.exe ${repo}/result.txt $opt $beta $mix
${libexec}/main.exe $root $opt $beta $day $month $year $period $libexec
exit
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
					if ( ! ( -d ./${dir_version} ) ) then
						mkdir ./${dir_version}
						mkdir ./${dir_version}/resultados
						mkdir ./${dir_version}/tmp
					else
						rm -rf ./${dir_version}
						mkdir ./${dir_version}
						mkdir ./${dir_version}/resultados
						mkdir ./${dir_version}/tmp
					endif
					cd ./${dir_version}
					echo "[RUN_PROF]Processando arquivo com run.sh..."
					csh ${libexec}/scripts/main_cshell_scripts/run.sh ${libexec} .. ${opt} ${beta} ${mix}
					echo "[RUN_PROF]Arquivo processado com run.sh."
					cd ..
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
                                        echo "[RUN_PROF]O arquivo ${pasta}/result.txt.gz foi descompactado com sucesso."
					if ( ! ( -d ./${dir_version} ) ) then
                                                mkdir ./${dir_version}
                                                mkdir ./${dir_version}/resultados
                                                mkdir ./${dir_version}/tmp
					else
						rm -rf ./${dir_version}
						mkdir ./${dir_version}
						mkdir ./${dir_version}/resultados
						mkdir ./${dir_version}/tmp
                                        endif
                                        cd ./${dir_version}
                                        echo "[RUN_PROF]Processando arquivo com run.sh..."
                                        csh ${libexec}/scripts/main_cshell_scripts/run.sh ${libexec} .. ${opt} ${beta} ${mix}
                                        echo "[RUN_PROF]Arquivo processado com run.sh."
					cd ..
                                        echo "[RUN_PROF]Compactando o arquivo ${pasta}/result.txt ..."
                                        gzip result.txt
                                        echo "[RUN_PROF]O arquivo ${pasta}/result.txt foi descompactado com sucesso."
                                endif
                        endif
                endif
                cd $casa
                @ dia ++
        end
        @ mes ++
end

