####SRC_IP####
##dimension
tabsrcip<-read.table("./resultados/SRC_IP.txt", header=T,sep=",")
y<-tabsrcip$nA
x<-1:length(y)
k<-tabsrcip$nS
png(filename="./resultados/graficos/srcIP_dimension.png")
par(lty=2)
plot(x,log10(y),type="l",ylim=c(0,6),axes=T,main="srcIP dimension",ylab="srcIP clusters(log base 10)",xlab="tempo")
par(lty=1)
lines(x,log10(k),type="l")
dev.off()
##alfa
y<-tabsrcip$alpha
png(filename="./resultados/graficos/srcIP_alfa.png")
par(lty=1)
plot(x,(y*100),type="l",ylim=c(0,(max(y)+0.001)*100),axes=T,main="limite para srcIP",ylab="alfa(%)",xlab="tempo")
dev.off()
##entropia H(x)
y<-tabsrcip$Ha
png(filename="./resultados/graficos/srcIP_entropia.png")
par(lty=1)
#plot(x,y,type="l",ylim=c(min(y)-2,max(y)+2),axes=T,main="entropia de srcIP",ylab="H(x)",xlab="tempo")
plot(x,y,type="l",ylim=c(min(y)-(0.05),max(y)+(0.05)),axes=T,main="entropia de srcIP",ylab="H(x)",xlab="tempo")
dev.off()
##entropia RU
y<-tabsrcip$RUa
png(filename="./resultados/graficos/srcIP_ru.png")
par(lty=1)
#plot(x,y,type="l",ylim=c(min(y)-(0.05),max(y)+(0.05)),axes=T,main="RU de srcIP",ylab="RU",xlab="tempo")
plot(x,y,type="l",ylim=c(min(y)-(0.02),max(y)+(0.02)),axes=T,main="RU de srcIP",ylab="RU",xlab="tempo")
dev.off()
####DST_IP####
##dimension
tabsrcip<-read.table("./resultados/DST_IP.txt", header=T,sep=",")
y<-tabsrcip$nA
k<-tabsrcip$nS
png(filename="./resultados/graficos/dstIP_dimension.png")
par(lty=2)
plot(x,log10(y),type="l",ylim=c(0,6),axes=T,main="dstIP dimension",ylab="dstIP clusters(log base 10)",xlab="tempo")
par(lty=1)
lines(x,log10(k),type="l")
dev.off()
##alfa
y<-tabsrcip$alpha
png(filename="./resultados/graficos/dstIP_alfa.png")
par(lty=1)
plot(x,(y*100),type="l",ylim=c(0,(max(y)+0.001)*100),axes=T,main="limite para dstIP",ylab="alfa(%)",xlab="tempo")
dev.off()
##entropia H(x)
y<-tabsrcip$Ha
png(filename="./resultados/graficos/dstIP_entropia.png")
par(lty=1)
plot(x,y,type="l",ylim=c(min(y)-(0.05),max(y)+(0.05)),axes=T,main="entropia de dstIP",ylab="H(x)",xlab="tempo")
dev.off()
##RU
y<-tabsrcip$RUa
png(filename="./resultados/graficos/dstIP_ru.png")
par(lty=1)
plot(x,y,type="l",ylim=c(min(y)-(0.02),max(y)+(0.02)),axes=T,main="RU de dstIP",ylab="RU",xlab="tempo")
dev.off()
####DST_PRT####
##dimension
tabsrcip<-read.table("./resultados/DST_PRT.txt", header=T,sep=",")
y<-tabsrcip$nA
k<-tabsrcip$nS
png(filename="./resultados/graficos/dstPrt_dimension.png")
par(lty=2)
plot(x,log10(y),type="l",ylim=c(0,max(log10(y))+1),axes=T,main="dstPrt dimension",ylab="dstPrt clusters(log base 10)",xlab="tempo")
par(lty=1)
lines(x,log10(k),type="l")
dev.off()
##alfa
y<-tabsrcip$alpha
png(filename="./resultados/graficos/dstPrt_alfa.png")
par(lty=1)
plot(x,(y*100),type="l",ylim=c(0,(max(y)+0.001)*100),axes=T,main="limite para dstPrt",ylab="alfa(%)",xlab="tempo")
dev.off()
##entropia H(x)
y<-tabsrcip$Ha
png(filename="./resultados/graficos/dstPrt_entropia.png")
par(lty=1)
plot(x,y,type="l",ylim=c(min(y)-(0.05),max(y)+(0.05)),axes=T,main="entropia de dstPrt",ylab="H(x)",xlab="tempo")
dev.off()
##RU
y<-tabsrcip$RUa
png(filename="./resultados/graficos/dstPrt_ru.png")
par(lty=1)
plot(x,y,type="l",ylim=c(min(y)-(0.02),max(y)+(0.02)),axes=T,main="RU de dstPrt",ylab="RU",xlab="tempo")
dev.off()
####SRC_PRT####
##dimension
tabsrcip<-read.table("./resultados/SRC_PRT.txt", header=T,sep=",")
y<-tabsrcip$nA
k<-tabsrcip$nS
png(filename="./resultados/graficos/srcPrt_dimension.png")
par(lty=2)
plot(x,log10(y),type="l",ylim=c(0,max(log10(y))+1),axes=T,main="srcPrt dimension",ylab="srcPrt clusters(log base 10)",xlab="tempo")
par(lty=1)
lines(x,log10(k),type="l")
dev.off()
##alfa
y<-tabsrcip$alpha
png(filename="./resultados/graficos/srcPrt_alfa.png")
par(lty=1)
plot(x,(y*100),type="l",ylim=c(0,(max(y)+0.001)*100),axes=T,main="limite para srcPrt",ylab="alfa(%)",xlab="tempo")
dev.off()
##entropia H(x)
y<-tabsrcip$Ha
png(filename="./resultados/graficos/srcPrt_entropia.png")
par(lty=1)
plot(x,y,type="l",ylim=c(min(y)-(0.05),max(y)+(0.05)),axes=T,main="entropia de srcPrt",ylab="H(x)",xlab="tempo")
dev.off()
##RU
y<-tabsrcip$RUa
png(filename="./resultados/graficos/srcPrt_ru.png")
par(lty=1)
plot(x,y,type="l",ylim=c(min(y)-(0.02),max(y)+(0.02)),axes=T,main="RU de srcPrt",ylab="RU",xlab="tempo")
dev.off()
