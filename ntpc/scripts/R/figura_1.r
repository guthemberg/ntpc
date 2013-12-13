#Este constroi graficos em barras
# Os parametros de ntrada sao as porcentagens
#O objetivo eh criar um comparativo entre a eficiencia da utilizacao da solucao com fluxos m relacao a com bytes
#Para ver um exemplo deste grafico, verifique ./exemplos/figura_1.png
alturas<-read.table("./tmp/resultados.txt", header=T,sep=",")
#alturas<-c(0.571403,0.943153)
png(filename="./tmp/figura_1.png")
barplot(ylab='Porcentagem de Octetos P2P',alturas,col=c('gray','black'),xlim=c(0,5),ylim = c(0,1),width=1,space=1,offset=0,names.arg=c('I1','I2'))
dev.off()
