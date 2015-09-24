stem(cpus)
par(mfrow=c(1,2), pty="s") # deux graphs
hist(cpus, xlab="performance relative", ylab="fréquence", main="", col="darkslategray4")
boxplot(cpus, xlab="performance relative", col="darkslategray4", horizontal=T)
rug(cpus)
par(mfrow=c(1,1))

median(cpus)
mean(cpus)

summary(cpus)
summary(c(cpus, 40)) # Ajout d'un proc à 40
summary(cpus - 10)
summary(cpus / 5)

sd(cpus[cpus<=185])
