#!/bin/csh
if ($#argv == 7) then
  set output = $argv[1]
  set bc = $argv[2]
  set root = $argv[3]
  set obj = $argv[4]
  set sense = $argv[5]
  set libexec = $argv[6]
  set opt = $argv[7]
else
  echo "[MIND]Numero de parametros invalido. tente: apps.exe arg1 arg2 arg3"
  exit
endif
set resultados_dir = ${root}/tmp
set temp_dir = ${root}/tmp
set scripts_dir = ${libexec}
set script_bc = ${scripts_dir}/cbc.sh
set temp_file = ${temp_dir}/fool10.txt
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

set result_file = ${temp_dir}/${opt}_bc${bc}_${ou}_${qui}_${output}
echo "tempo,apps,nr_fluxos,volume,tempo,nr_pacotes" > ${result_file}
@ i = 1 
while ( $i < 299 )
  set table = ( $opt )
  foreach tipo ( $table[*] )
      grep ^"${i},${bc}," ${resultados_dir}/${tipo}_${ou}_${qui}_file.txt |cut -f3-6 -d, > $temp_file
      @ linhas = `cat ${temp_file} | wc -l `
      if ( $linhas > 0 ) then 
        csh ${script_bc} ${i} ${tipo} $temp_file >> ${result_file}
      endif
  end
  @ i++
end
rm -rf ${temp_file}
echo "Arquivo final de resultados em ${result_file}."
