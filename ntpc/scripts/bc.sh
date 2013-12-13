#!/bin/csh
if ($#argv == 4) then
  set root = $argv[1]
  set tempo = $argv[2]
  set input = $argv[3]
  set libexec = $argv[4]
else
  echo "[BC]Numero de parametros invalido. tente: apps.exe arg1 arg2 arg3"
endif
set scripts_dir = ${libexec}
set temp_dir = ${root}/tmp
set temp_file = ${temp_dir}/fool.txt
set script_apps = ${scripts_dir}/por_aplicacao.sh
@ i = 0 
while ( $i < 27 )
  grep ^"${i}," ${input} > $temp_file
  #exemplo do comando a seguir csh por_aplicacao.sh ./teste.txt 20 [1-288]
  csh ${script_apps} ${temp_file} ${i} ${tempo}
  @ i++
end
rm -rf ${temp_file}
