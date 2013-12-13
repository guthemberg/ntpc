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
set script_bc = ${scripts_dir}/bc.sh
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

echo "tempo,bc,nr_fluxos,volume,tempo,nr_pacotes" > ${result_file}
@ i = 1
if ( ${apps} == all ) then
	while ( $i < 299 )
     	  grep ^"p2p${i}," ${resultados_dir}/p2p_TS_${ou}_${qui}.txt |cut -f3,8-11 -d, > $temp_file
     	  #exemplo do comando a seguir csh por_aplicacao.sh ./teste.txt 20 aut
    	  csh ${script_bc} ${root} ${i} ${temp_file} ${libexec} >> ${result_file} 
 	  @ i++
	end
else
	while ( $i < 299 )
     	  grep ^"${apps}${i}," ${resultados_dir}/${apps}_TS_${ou}_${qui}.txt |cut -f3-7 -d, > $temp_file
     	  #exemplo do comando a seguir csh por_aplicacao.sh ./teste.txt 20 aut
    	  csh ${script_bc} ${root} ${i} ${temp_file} ${libexec} >> ${result_file} 
 	  @ i++
	end
endif 
rm -rf ${temp_file}
echo "Arquivo final de resultados em ${result_file}."
