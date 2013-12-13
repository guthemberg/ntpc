#! /bin/csh
#Este script serve para contar a quantidade de trafego p2p e de trafego total de um conjutno de arquivos de traces
#Os parametros sao os seguintes:
#->root: raiz da busta por diretorio do formato ddmmaaaa
#->ini_day: dia inicial da contagem
#-> last_day: dia final da contagem de bytes
#->mes: mes da sequencia de dias
#->ano: ano para a contagem de bytes
#->libeexec: local onde estah armazenado o script compt_bytes_flows.sh
if ( ( $#argv == 7 ) ) then
  set root = ${1}
  set ini_day = ${2}
  set last_day = ${3}
  set mes = ${4}
  set ano = ${5}
  set libexec = ${6}
  set output_dir = ${7}
else
#Valores possiveis para option: p2p, edk, bit, kaz, aut
  echo "[RUN_BYTES_FLOWS ERROR] Vc errou, tente:  #./apps.exe raiz ini_day last_day mes ano dir_libexec output_dir"
  exit
endif
if( ! ( -d $output_dir ) ) then
  echo "[RUN_BYTES_FLOWS ERROR] Invalid output_dir: ${output_dir}"
  exit
endif
set casa = $root
cd $casa
set id=""
set pasta="" 

        @ dia = $ini_day 
        while ( $dia <= $last_day )
                if ( $dia < 10 ) then
			if ( $mes < 10 ) then
				set pasta = ./0${dia}0${mes}${ano}
				set id=0${dia}0${mes}
			else
				set pasta = ./0${dia}${mes}${ano}
				set id=0${dia}${mes}
			endif
                        if ( -d ${pasta} ) then
                                cd ${pasta}
                                if ( ( -f ./result.txt.gz ) || ( -f ./result.txt ) ) then
                                        if( -f ./result.txt.gz ) then
						echo "[RUN_BYTES_FLOWS]DesCompactando o arquivo ${pasta}/result.txt.gz ..."
                                        	gunzip result.txt.gz
					endif
                                        echo "[RUN_BYTES_FLOWS]O arquivo ${pasta}/result.txt foi descompactado com sucesso."
					echo "[RUN_BYTES_FLOWS]Processando arquivo com compt_bytes_flows.sh..."
					csh ${libexec}/scripts/compt_bytes_flows.sh ./result.txt $id > ${output_dir}/${id}.txt
					echo "[RUN_BYTES_FLOWS]Arquivo processado com compt_bytes_flows.sh."
                                        echo "[RUN_BYTES_FLOWS]Compactando o arquivo ${pasta}/result.txt ..."
                                        gzip result.txt
                                        echo "[RUN_BYTES_FLOWS]O arquivo ${pasta}/result.txt foi compactado com sucesso."
                                endif
                        endif
                else
			if ( $mes < 10 ) then
				set pasta = ./${dia}0${mes}${ano}
				set id = ${dia}0${mes}
			else
				set pasta = ./${dia}${mes}${ano}
				set id = ${dia}${mes}
			endif
                        if ( -d ${pasta} ) then
                                cd ${pasta}
                                if ( ( -f ./result.txt.gz ) || ( -f ./result.txt ) ) then
                                        if( -f ./result.txt.gz ) then
						echo "[RUN_BYTES_FLOWS]DesCompactando o arquivo ${pasta}/result.txt.gz ..."
                                        	gunzip result.txt.gz
					endif
                                        echo "[RUN_BYTES_FLOWS]O arquivo ${pasta}/result.txt foi descompactado com sucesso."
					echo "[RUN_BYTES_FLOWS]Processando arquivo com compt_bytes_flows.sh..."
					csh ${libexec}/scripts/compt_bytes_flows.sh ./result.txt $id > ${output_dir}/${id}.txt
					echo "[RUN_BYTES_FLOWS]Arquivo processado com compt_bytes_flows.sh."
                                        echo "[RUN_BYTES_FLOWS]Compactando o arquivo ${pasta}/result.txt ..."
                                        gzip result.txt
                                        echo "[RUN_BYTES_FLOWS]O arquivo ${pasta}/result.txt foi compactado com sucesso."
                                endif
                        endif
                endif
                cd $casa
                @ dia ++
        end
