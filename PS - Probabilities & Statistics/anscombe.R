#Proiect anscombe
#grupa 234
#Butu Anda Irina
#Cercel Ana Maria
#Ciobanu Andrei Ovidiu

#install.packages("fBasics")
library(fBasics)
library(ggplot2)
library(grid)
library(gridExtra)


datasets::anscombe
fBasics::basicStats(anscombe)
results1<-lm(x1 ~ y1, data=anscombe)
coef(results1)

#Medie
sapply(1:8, function(x) mean(anscombe[ , x]))

#Variatie
sapply(1:8, function(x) var(anscombe[ , x]))

#Corelatie
sapply(1:4, function(x) cor(anscombe[ , x], anscombe[ , x+4]))

#Boxplot
ggplot(anscombe, aes(x2, y2)) + 
  geom_boxplot(outlier.colour="red", outlier.shape=8,
               outlier.size=4)

p1 <- ggplot(anscombe) +
  geom_point(aes(x1, y1), color = "darkorange", size = 1.5) +
  scale_x_continuous(breaks = seq(0,20,2)) +
  scale_y_continuous(breaks = seq(0,12,2)) +
  expand_limits(x = 0, y = 0) +
  labs(x = "x1", y = "y1",
       title = "Dataset 1" ) +
  theme_bw()
p1

p2 <- ggplot(anscombe) +
  geom_point(aes(x2, y2), color = "darkorange", size = 1.5) +
  scale_x_continuous(breaks = seq(0,20,2)) +
  scale_y_continuous(breaks = seq(0,12,2)) +
  expand_limits(x = 0, y = 0) +
  labs(x = "x2", y = "y2",
       title = "Dataset 2" ) +
  theme_bw()
p2

p3 <- ggplot(anscombe) +
  geom_point(aes(x3, y3), color = "darkorange", size = 1.5) +
  scale_x_continuous(breaks = seq(0,20,2)) +
  scale_y_continuous(breaks = seq(0,12,2)) +
  expand_limits(x = 0, y = 0) +
  labs(x = "x3", y = "y3",
       title = "Dataset 3" ) +
  theme_bw()
p3

p4 <- ggplot(anscombe) +
  geom_point(aes(x4, y4), color = "darkorange", size = 1.5) +
  scale_x_continuous(breaks = seq(0,20,2)) +
  scale_y_continuous(breaks = seq(0,12,2)) +
  expand_limits(x = 0, y = 0) +
  labs(x = "x4", y = "y4",
       title = "Dataset 4" ) +
  theme_bw()
p4

#Quantile
grid.arrange(grobs = list(p1, p2, p3, p4), 
             ncol = 2, 
             top = "Anscombe's Quartet")

#Regresie Simpla
lm1 <- lm(y1 ~ x1, data = anscombe)
lm1

lm2 <- lm(y2 ~ x2, data = anscombe)
lm2

lm3 <- lm(y3 ~ x3, data = anscombe)
lm3

lm4 <- lm(y4 ~ x4, data = anscombe)
lm4

#plot cu datele de intrare si regresia
p1_fitted <- p1 + geom_abline(intercept = 3.0001, slope = 0.5001, color = "blue")
p2_fitted <- p2 + geom_abline(intercept = 3.001, slope = 0.500, color = "blue")
p3_fitted <- p3 + geom_abline(intercept = 3.0025, slope = 0.4997, color = "blue")
p4_fitted <- p4 + geom_abline(intercept = 3.0017, slope = 0.499, color = "blue")

grid.arrange(grobs = list(p1_fitted, p2_fitted,
                          p3_fitted, p4_fitted), 
             ncol = 2, 
             top = "Anscombe's Quartet")

require(stats); require(graphics)
summary(anscombe)

#Regresie multipla
ff <- y ~ x
mods <- setNames(as.list(1:4), paste0("lm", 1:4))
for(i in 1:4) {
  ff[2:3] <- lapply(paste0(c("y","x"), i), as.name)
  mods[[i]] <- lmi <- lm(ff, data = anscombe)
  print(anova(lmi))
}

sapply(mods, coef)
lapply(mods, function(fm) coef(summary(fm)))

#Plots
op <- par(mfrow = c(2, 2), mar = 0.1+c(4,4,1,1), oma =  c(0, 0, 2, 0))
for(i in 1:4) {
  ff[2:3] <- lapply(paste0(c("y","x"), i), as.name)
  plot(ff, data = anscombe, col = "red", pch = 21, bg = "orange", cex = 1.2,
       xlim = c(3, 19), ylim = c(3, 13))
  abline(mods[[i]], col = "blue")
}

mtext("Anscombe's 4 Regression data sets", outer = TRUE, cex = 1.5)
par(op)

anscombe.1 <- data.frame(x = anscombe[["x1"]], y = anscombe[["y1"]], Set = "Anscombe Set 1")
anscombe.2 <- data.frame(x = anscombe[["x2"]], y = anscombe[["y2"]], Set = "Anscombe Set 2")
anscombe.3 <- data.frame(x = anscombe[["x3"]], y = anscombe[["y3"]], Set = "Anscombe Set 3")
anscombe.4 <- data.frame(x = anscombe[["x4"]], y = anscombe[["y4"]], Set = "Anscombe Set 4")

anscombe.data <- rbind(anscombe.1, anscombe.2, anscombe.3, anscombe.4)
aggregate(cbind(x, y) ~ Set, anscombe.data, mean)


correlation <- function(data) {
  x <- data.frame(r = cor(data$x, data$y))
  return(x)
}

ddply(.data = anscombe.data, .variables = "Set", .fun = correlation)

model1 <- lm(y ~ x, subset(anscombe.data, Set == "Anscombe Set 1"))
model2 <- lm(y ~ x, subset(anscombe.data, Set == "Anscombe Set 2"))
model3 <- lm(y ~ x, subset(anscombe.data, Set == "Anscombe Set 3"))
model4 <- lm(y ~ x, subset(anscombe.data, Set == "Anscombe Set 4"))

summary(model1)


#Repartitie Fisher
x = seq(0, 5, length = 100)

par(mfrow = c(2, 1))
curve(df(x, 5, 2), from = 0, to = 5, col = "orange", 
      xlab = "quantile", ylab = "density", lwd = 2, main = "fisher repartition")
curve(df(x, 5, 1), from = 0, to = 5, col = "dark green", add = TRUE, lwd = 2)
curve(df(x, 4, 3), from = 0, to = 5, col = "sky blue", add = TRUE, lwd = 2)
curve(df(x, 6, 4), from = 0, to = 5, col = "grey40", add = TRUE, lwd = 2)

curve(pf(x, 5, 2), from = 0, to = 5, col = "orange", lwd = 2)
curve(pf(x, 5, 1), from = 0, to = 5, col = "dark green", add = TRUE, lwd = 2)
curve(pf(x, 4, 3), from = 0, to = 5, col = "sky blue", add = TRUE, lwd = 2)
curve(pf(x, 6, 4), from = 0, to = 5, col = "grey40", add = TRUE, lwd = 2)

pareto.MLE <- function(X)
{
  n <- length(X)
  m <- min(X)
  a <- n/sum(log(X)-log(m))
  return( c(m,a) ) 
}

#exemplu
library(VGAM)
set.seed(1)
z = rpareto(1000, 1, 5) 
pareto.MLE(z)

#Pareto Repartitie
#Densitate Pareto
dpareto(2:4, 1, 1) 

#Distributie Pareto
ppareto(3:5, 2, 1) 

qpareto(0.25, 1, 1) 
