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
if ( !(-f ${temp_dir}/all_${ou}_${qui}_barras.txt) ) then
	echo "[PARAM ERRROR] o arquivo ${temp_dir}/all_${ou}_${qui}_barras.txt nao existe ou nao pode ser lido."
	exit
endif
if ( !(-f ${temp_dir}/${apps}_${ou}_${qui}_barras.txt) ) then
	echo "[PARAM ERRROR] o arquivo ${temp_dir}/${apps}_${ou}_${qui}_barras.txt nao existe ou nao pode ser lido."
	exit
endif
set result_file = ${temp_dir}/${apps}_${ou}_${qui}_${output}
#echo "chegou em barra2"
echo "bc,precisao" > ${result_file}
awk -F, -v tb1=0 -v tb2=0 -v flag=0 -v input=${temp_dir}/all_${ou}_${qui}_barras.txt -v output=${result_file} ' { \
        if (flag) { \
                tb1=$4 \
                getline < input \
                tb2=$4 \
		if(tb2==0) { \
                	printf("%s,%.6f\n",$1,0) >> output \
		} else { \
                	printf("%s,%.6f\n",$1,tb1/tb2) >> output \
		} \
		close(output) \
        } else { \
                getline < input \
                flag = 1 \
        } \
}' ${temp_dir}/${apps}_${ou}_${qui}_barras.txt

echo "Arquivo final de resultados em ${result_file}."
exit
