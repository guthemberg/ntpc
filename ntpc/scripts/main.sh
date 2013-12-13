#!/bin/csh
if ($#argv == 6) then
  set output = $argv[1]
  set opcao = $argv[2]
  set root = $argv[3]
  set obj = $argv[4]
  set sense = $argv[5]
  set libexec = $argv[6]
else
  echo "[MAIN]Numero de parametros invalido. tente: apps.exe arg1 arg2 arg3"
  exit
endif
set scripts_dir = ${libexec}
set temp_dir = ${root}/tmp
if ( ! -d ${temp_dir} ) then
  echo "Nao existe o diretorio ${temp_dir} ."
endif
if ( ( ( ${sense} != 1 ) && ( ${sense} != 0 ) )  )  then
  echo "O quinto parametro deve ter o valo 1 ou 0. "
  exit
endif
if ( ( ( ${obj} != 1 ) && ( ${obj} != 0 ) )  )  then
  echo "O quarto parametro deve ter o valo 1 ou 0. "
  exit
endif
csh ${scripts_dir}/mind.sh $output $opcao $root $obj $sense $scripts_dir
