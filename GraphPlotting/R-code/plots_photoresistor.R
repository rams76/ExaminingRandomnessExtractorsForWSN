library(plyr)
library(ggplot2)
setwd ("G:/MU Second Semester/PROJECT/CODE/GraphPlotting")
rawdata <- read.table("RES_measured2.txt", header=FALSE)
data1 <- as.numeric(rawdata$V1)
data <- data1[1:1000]
str(rawdata)
data.len <- length(data)
data.len
x <- seq(1,1000)
options(scipen=5)
avg<- mean(data)
std.dev <- sd(data)
plot(x,data,xlab = 'Time in msec',ylab = 'Resistance value', 
     main = 'Time domain represenation of resistance value of photoresistor')
#abline(h=avg, col="blue", lwd=1.8)
#legend('bottomright', c('Mean'),col=c('blue'),lty=1,bty='n')

h<-hist(data, breaks=10, xlab='Resistance value',main='Histogram of resistance value of photoresistor',
     probability = FALSE,ylim =c(0, 700))
#plot(x=h$mids, y=h$density*1200, type="l")

xx <- seq(min(data), max(data), length.out=100)
normdens <- dnorm(xx, avg, std.dev)*4000
lines(xx, normdens, col ='red',lwd=1.8)
abline(v=avg, col="blue", lwd=1.8)
#empdens <- density(data)
#lines(empdens, col = 'blue')
#plot(x=h$mids, y=h$density*1200, type="l")
rug (data)
legend('topleft', c('Normal distribution','Mean'),col=c('red', 'blue'),lty=1,bty='n')




