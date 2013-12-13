#!/bin/csh
if ( !( $#argv == 3 ) ) then
  echo "[RODA]Numero de parametros invalido. tente: apps.exe dir_local libexec opt"
  echo "onde:"
  echo "apps.exe: csh barras.sh"
  echo "dir_local: diretorio onde estao os resultados. Ex.: <path>/traces_poppe/012005/11012005/prof_master_bytes_secao5/ "
  echo "libexec: diretorio onde estao os scripts secundarios. Ex: <path>/versao_<tipo>/scripts"
  echo "opt: indica a opcao de processamento: p2p, bit, edk, kaz, aut,all. Eh importante lembrar que all refere-se as colunas 8-11 dos arquivos p2p_TS*"
  exit
endif
set root = ${1}
if ( -d $root ) then
        if ( ( !( -d $root/resultados) ) || ( !( -d $root/tmp) ) ) then
                echo "[ROULE ERROR] o diretorio $root nao eh validos, pq ao mesnos um dos diretorios interrnos ./tmp ou ./resultados  nao exiete ou nao pode ser lido"
                exit
        endif
else
        echo "[ROULE ERROR] o diretorio $root nao existe ou nao pode ser lido"
        exit
endif

#local onde estao armazenados os scripts secundarios localizados em ./versao_<tipo>/scripts
set libexec = ${2}
if ( ! ( -d $libexec ) ) then
        echo "[ROULE ERROR] o diretorio $libexec nao existe ou nao pode ser lido"
        exit
endif

set opt = ${3}
if ( !( ( $opt == p2p) || ( $opt == edk) || ( $opt == aut)|| ( $opt == all) || ( $opt == kaz) || ( $opt == bit))  ) then
        echo "[ROULE ERROR] a optcao $opt nao eh valida. Tente: p2p, bit, edk, kaz, aut"
        exit
endif
 
set table = ( $opt )
foreach tipo ( $table[*] )
# os ultimos dois argumentos do scripts a seguir distiguem src, dst, prt e ip, exemplo, o primeiro eh IP src
  csh ${libexec}/barras1.sh barras.txt $tipo ${root} 0 0 $libexec
  csh ${libexec}/barras1.sh barras.txt $tipo ${root} 0 1 $libexec
  csh ${libexec}/barras1.sh barras.txt $tipo ${root} 1 0 $libexec
  csh ${libexec}/barras1.sh barras.txt $tipo ${root} 1 1 $libexec
end 
