#!/bin/csh
if ( ( $#argv > 4 ) && ( $#argv < 6 )   ) then
  set libexec = ${1}
  set repo = ${2}
  set opt = ${3}
  set beta = ${4}
else
#Valores possiveis para option: p2p, edk, bit, kaz, aut
  echo "[RUN ERROR] Vc errou, tente:  #./apps.exe dir_libexec result.txt_dir option beta_value"
  echo -n "[RUN ERROR] Vc informou apenas $#argv parametros: "
  @ i=0
  @ var=0
  while ( $i < $#argv )
        @ var = $i + 1
        echo -n "$argv[$var] "
        @ i++
  end
  echo "."
  exit
endif
set mix = ""

if ( $#argv == 5 ) then
  set mix = ${5}
endif
if ( !( -d ./resultados ) ) then
	echo -n "[RUN ERROR] Nao existe o diretorio ./resultados em "
	pwd
  	exit
endif
if ( !( -d ./tmp ) ) then
	echo -n "[RUN ERROR] Nao existe o diretorio ./tmp em "
	pwd
  	exit
endif
echo "[RUN]Processando main.exe com a opcao $opt em "
pwd
${libexec}/main.exe ${repo}/result.txt $opt $beta $mix
echo "[RUN]Fim do Processando main.exe com a opcao $opt em "
pwd
#${libexec}/main.exe ${repo}/result.txt edk $beta
#${libexec}/main.exe ${repo}/result.txt bit $beta
#${libexec}/main.exe ${repo}/result.txt kaz $beta
#${libexec}/main.exe ${repo}/result.txt aut $beta
#${libexec}/main.exe ${repo}/result.txt all $beta
#./main.exe ./result.txt all
