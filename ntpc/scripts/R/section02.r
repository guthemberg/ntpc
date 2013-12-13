###P2P####
tabsrcip<-read.table("./tmp/p2p_SRC_IP_kartei.txt", header=T,sep=",")
x<-tabsrcip$bc
y<-tabsrcip$freq
brk<-c(-0.5,0.5,1.5,2.5,3.5,4.5,5.5,6.5,7.5,8.5,9.5,10.5,11.5,12.5,13.5,14.5,15.5,16.5,17.5,18.5,19.5,20.5,21.5,22.5,23.5,24.5,25.5,26.5)
bc<-rep(x,y)
png(filename="./resultados/graficos/histograma_p2p.png")
hist(bc,breaks=brk,freq=T,main="Histograma de BC para P2P")
dev.off()
###EDK####
tabsrcip<-read.table("./tmp/edk_SRC_IP_kartei.txt", header=T,sep=",")
x<-tabsrcip$bc
y<-tabsrcip$freq
brk<-c(-0.5,0.5,1.5,2.5,3.5,4.5,5.5,6.5,7.5,8.5,9.5,10.5,11.5,12.5,13.5,14.5,15.5,16.5,17.5,18.5,19.5,20.5,21.5,22.5,23.5,24.5,25.5,26.5)
bc<-rep(x,y)
png(filename="./resultados/graficos/histograma_edk.png")
hist(bc,breaks=brk,freq=T,main="Histograma de BC para EDK")
dev.off()
###BIT####
tabsrcip<-read.table("./tmp/bit_SRC_IP_kartei.txt", header=T,sep=",")
x<-tabsrcip$bc
y<-tabsrcip$freq
brk<-c(-0.5,0.5,1.5,2.5,3.5,4.5,5.5,6.5,7.5,8.5,9.5,10.5,11.5,12.5,13.5,14.5,15.5,16.5,17.5,18.5,19.5,20.5,21.5,22.5,23.5,24.5,25.5,26.5)
bc<-rep(x,y)
png(filename="./resultados/graficos/histograma_bit.png")
hist(bc,breaks=brk,freq=T,main="Histograma de BC para BIT")
dev.off()
###KAZ####
tabsrcip<-read.table("./tmp/kaz_SRC_IP_kartei.txt", header=T,sep=",")
x<-tabsrcip$bc
y<-tabsrcip$freq
brk<-c(-0.5,0.5,1.5,2.5,3.5,4.5,5.5,6.5,7.5,8.5,9.5,10.5,11.5,12.5,13.5,14.5,15.5,16.5,17.5,18.5,19.5,20.5,21.5,22.5,23.5,24.5,25.5,26.5)
bc<-rep(x,y)
png(filename="./resultados/graficos/histograma_kaz.png")
hist(bc,breaks=brk,freq=T,main="Histograma de BC para KAZ")
dev.off()
###AUT####
tabsrcip<-read.table("./tmp/aut_SRC_IP_kartei.txt", header=T,sep=",")
x<-tabsrcip$bc
y<-tabsrcip$freq
brk<-c(-0.5,0.5,1.5,2.5,3.5,4.5,5.5,6.5,7.5,8.5,9.5,10.5,11.5,12.5,13.5,14.5,15.5,16.5,17.5,18.5,19.5,20.5,21.5,22.5,23.5,24.5,25.5,26.5)
bc<-rep(x,y)
png(filename="./resultados/graficos/histograma_aut.png")
hist(bc,breaks=brk,freq=T,main="Histograma de BC para AUT")
dev.off()
###ALL####
tabsrcip<-read.table("./tmp/all_SRC_IP_kartei.txt", header=T,sep=",")
x<-tabsrcip$bc
y<-tabsrcip$freq
brk<-c(-0.5,0.5,1.5,2.5,3.5,4.5,5.5,6.5,7.5,8.5,9.5,10.5,11.5,12.5,13.5,14.5,15.5,16.5,17.5,18.5,19.5,20.5,21.5,22.5,23.5,24.5,25.5,26.5)
bc<-rep(x,y)
png(filename="./resultados/graficos/histograma_all.png")
hist(bc,breaks=brk,freq=T,main="Histograma de BC para ALL")
dev.off()
