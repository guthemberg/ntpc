(-1)run_training.sh: The most important script of this folder. Start here.
0) run_prof.sh: Este eh o script que chama o run.sh abaixo para ser excutando em uma serie continua de dias
1) o script run.sh a implementacao do profiling
2) HA dois scripts que devem ser executados em conjunto, sao eles:
roda.sh, roule.sh (obedecer esta ordem)
Os scripts descritos acima processam os arquivos gerados pela implementacao do profiling e gera os seus respectivos relatorios
3) O script rollt.sh pode ser executado de maneira independente
4) Jah o o script corte_em_horas.sh trada da fragmentacao d eum arquivo d etraces em pedacos menores, ele pode ser executado separadamente.
5) - ver_eficiencia.sh - Este script verifica a eficiencia da implementacao. Ele executa o script em R que produz a Figura 1 do relatorio 
6)overview_img.sh - mostra um conjunto de quatro grafivos para cada arquivo processado, esetes graficos sao em relacao as dimensoes e entropia. Este script execura o script R chamado function_section01.r
7) ver_eficiencia_to_2.sh: verifica a eficiencia para apenas duas implementacoe. Ele inicialmente processa o arquivo d etraces, em seguida, compara com duas implementacaoes. Por fim, ele gera um grafico atraves do R.
8) separador.sh este script seleciona um conjunto de fluxos de um arquivo de traces. Atraves do tempo final dos traces ele verifica ele localiza a hora inicial passada e escreve em um arquivo o conjunto de fluxos de um intervalo de tempo determinado
9) run_ver_to_2.sh: executa o script ver_eficiencia_to_2.sh em um conjutno de varios dias em um mes
10) run_bytes.sh: Conta byes para um sequencia de dias determinados. sta contagem permite saber a quantidade total de trafego e a quantidade total de bytes p2p. Ele utiliza o script compt_bytes.sh localizado no diretorio scripts
