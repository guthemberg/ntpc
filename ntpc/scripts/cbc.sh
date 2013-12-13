#!/bin/csh
if ($#argv == 3) then
  set tempo = $argv[1]
  set apps = $argv[2]
  set input = $argv[3]
else
  echo "[BC]Numero de parametros invalido. tente: apps.exe arg1 arg2 arg3 $#argv"
  exit
endif
echo "${tempo},${apps},`cat ${input}`"
