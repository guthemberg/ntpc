#!/bin/csh
if ($#argv == 6) then
  set output = $argv[1]
  set apps = $argv[2]
  set root = $argv[3]
  set obj = $argv[4]
  set sense = $argv[5]
  set libexec = $argv[6]
else
  echo "[MIND]Numero de parametros invalido. tente: apps.exe arg1 arg2 arg3"
  exit
endif
set resultados_dir = ${root}/resultados
set scripts_dir = ${libexec}
set temp_dir = ${root}/tmp
set script_bc = ${scripts_dir}/barras3.sh
set temp_file = ${temp_dir}/fool1.txt
set qui=""
set ou=""

if( $obj == 1 ) then
  set qui=PRT
  if( $sense == 1 ) then
    set ou=DST
  else
    set ou=SRC
  endif
else
  set qui=IP
  if( $sense == 1 ) then
    set ou=DST
  else
    set ou=SRC
  endif
endif

set result_file = ${temp_dir}/${apps}_${ou}_${qui}_${output}
#echo "chegou em barra2"
echo "bc,app,nr_fluxos,volume,tempo,nr_pacotes" > ${result_file}
@ i = 0 
while ( $i < 27 )
  csh ${script_bc} ${temp_dir}/${apps}_bc${i}_${ou}_${qui}_fichier.txt ${i} ${apps} >> ${result_file} 
  @ i++
end
echo "Arquivo final de resultados em ${result_file}."
exit
