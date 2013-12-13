#! /bin/csh

#este script eh responsavel pela preparacao so diretorio para o processamento dos arquivos
#como primeiro argumento, este script recebe o diretorio para ser preparado, em seguida,
#ele recebe o nome da parta a ser criada

if ( ( $#argv == 2 ) ) then
  set root = ${1}
  set dir_version = ${2}
else
  echo "[PREPARE_PROF ERROR] Vc errou, tente:  #./apps.exe raiz dir_version"
  exit
endif
cd $root
if ( ( -f ./result.txt.gz ) ) then
	echo "[PREPARE_PROF]DesCompactando o arquivo ${root}/result.txt.gz ..."
	gunzip result.txt.gz
	echo "[PREPARE_PROF]O arquivo ${root}/result.txt.gz foi descompactado com sucesso."
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
else
	if ( ( -f ./result.txt ) ) then
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
	endif
endif
