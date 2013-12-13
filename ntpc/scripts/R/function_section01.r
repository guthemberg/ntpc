section1.function <- function (id, root)
{
  ####SRC_IP####
  ##dimension
  #Determina o arquivo de onde serah lido o conjunto de dados, exemplo: ./resultados/p2p_SRC_IP.txt,
  #onde resultados p2p_SRC_IP eh a chave, ou seja o id
  #e ./resultados/ o root 
  file1 <- paste(root,"/",id,".txt",sep="")
  tabsrcip<-read.table(file1, header=T,sep=",")
  y<-tabsrcip$nA
  x<-1:length(y)
  k<-tabsrcip$nS
  #Semelhante a descricao do paste acima, a diferenca eh a adicao do caminho de resultados graficos
  #Lembre-se esses caminhos deverao ser testados pelo script que chamar esta funcao
  img1 <- paste(root,"/graficos/",id,"_dimension.png",sep="")
  png(filename=img1)
  par(lty=2)
  plot(x,log10(y),type="l",ylim=c(0,6),axes=T,main="srcIP dimension",ylab="srcIP clusters(log base 10)",xlab="tempo")
  par(lty=1)
  lines(x,log10(k),type="l")
  dev.off()
  ##alfa
  y<-tabsrcip$alpha
  img <- paste(root,"/graficos/",id,"_srcIP_alfa.png",sep="")
  png(filename=img)
  par(lty=1)
  plot(x,(y*100),type="l",ylim=c(0,(max(y)+0.001)*100),axes=T,main="limite para srcIP",ylab="alfa(%)",xlab="tempo")
  dev.off()
  ##entropia H(x)
  y<-tabsrcip$Ha
  img <- paste(root,"/graficos/",id,"_srcIP_entropia.png",sep="")
  png(filename=img)
  par(lty=1)
  #plot(x,y,type="l",ylim=c(min(y)-2,max(y)+2),axes=T,main="entropia de srcIP",ylab="H(x)",xlab="tempo")
  plot(x,y,type="l",ylim=c(min(y)-(0.05),max(y)+(0.05)),axes=T,main="entropia de srcIP",ylab="H(x)",xlab="tempo")
  dev.off()
  ##entropia RU
  y<-tabsrcip$RUa
  img <- paste(root,"/graficos/",id,"_srcIP_ru.png",sep="")
  png(filename=img)
  par(lty=1)
  #plot(x,y,type="l",ylim=c(min(y)-(0.05),max(y)+(0.05)),axes=T,main="RU de srcIP",ylab="RU",xlab="tempo")
  plot(x,y,type="l",ylim=c(min(y)-(0.02),max(y)+(0.02)),axes=T,main="RU de srcIP",ylab="RU",xlab="tempo")
  dev.off()
}
