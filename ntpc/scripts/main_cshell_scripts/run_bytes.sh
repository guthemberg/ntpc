#! /bin/csh
#Este script serve para contar a quantidade de trafego p2p e de trafego total de um conjutno de arquivos de traces
#Os parametros sao os seguintes:
#->root: raiz da busta por diretorio do formato ddmmaaaa
#->ini_day: dia inicial da contagem
#-> last_day: dia final da contagem de bytes
#->mes: mes da sequencia de dias
#->ano: ano para a contagem de bytes
#->libeexec: local onde estah armazenado o script compt_bytes.sh
if ( ( $#argv == 6 ) ) then
  set root = ${1}
  set ini_day = ${2}
  set last_day = ${3}
  set mes = ${4}
  set ano = ${5}
  set libexec = ${6}
else
#Valores possiveis para option: p2p, edk, bit, kaz, aut
  echo "[RUN_BYTES ERROR] Vc errou, tente:  #./apps.exe raiz ini_day last_day mes ano dir_libexec"
  exit
endif
set casa = $root
cd $casa

set pasta="" 

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
                                        echo "[RUN_BYTES]DesCompactando o arquivo ${pasta}/result.txt.gz ..."
                                        gunzip result.txt.gz
                                        echo "[RUN_BYTES]O arquivo ${pasta}/result.txt foi descompactado com sucesso."
					echo "[RUN_BYTES]Processando arquivo com compt_bytes.sh..."
					csh ${libexec}/compt_bytes.sh ./result.txt
					echo "[RUN_BYTES]Arquivo processado com compt_bytes.sh."
                                        echo "[RUN_BYTES]Compactando o arquivo ${pasta}/result.txt ..."
                                        gzip result.txt
                                        echo "[RUN_BYTES]O arquivo ${pasta}/result.txt foi compactado com sucesso."
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
                                        echo "[RUN_BYTES]DesCompactando o arquivo ${pasta}/result.txt.gz ..."
                                        gunzip result.txt.gz
                                        echo "[RUN_BYTES]O arquivo ${pasta}/result.txt foi descompactado com sucesso."
					echo "[RUN_BYTES]Processando arquivo com compt_bytes.sh..."
					csh ${libexec}/compt_bytes.sh ./result.txt
					echo "[RUN_BYTES]Arquivo processado com compt_bytes.sh."
                                        echo "[RUN_BYTES]Compactando o arquivo ${pasta}/result.txt ..."
                                        gzip result.txt
                                        echo "[RUN_BYTES]O arquivo ${pasta}/result.txt foi compactado com sucesso."
                                endif
                        endif
                endif
                cd $casa
                @ dia ++
        end
