#! /bin/csh

#Este script recebe um parametro, dentro dele ele procura se ha um arquivo do tipo
#result.txt e o compacta

if ( ( $#argv == 1 ) ) then
  set root = ${1}
else
  echo "[FINISH_PROF ERROR] Vc errou, tente:  #./apps.exe raiz"
  exit
endif
cd $root
if ( -f ./result.txt ) then
	echo "[FINISH_PROF]Compactando o arquivo ${root}/result.txt ..."
	gzip result.txt
	echo "[FINISH_PROF]O arquivo ${root}}/result.txt foi descompactado com sucesso."
endif
