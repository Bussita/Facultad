#Vector de edades
edades <- c(22,22,23,24,25,25,26,27,28,29,29,29,29,29,31,31,32,33,34,35,35,35,36,38,39,39,42,42,44,44,45,45,45,47,48,52,59,66,67,69,69)
#Tamanio de la muestra
tamanioMuestra <- length(edades);
#Media, mediana, moda y cuartiles

media <- mean(edades)
mediana<- median(edades)
moda <- function(x) {
  ux <- unique(x)
  ux[which.max(tabulate(match(x, ux)))]
}

modaEdades <- moda(edades)

cuartiles <- function(x){
  cuartil <- quantile(x, prob=c(0.25,0.5,0.75))
  return (cuartil)
}

cuartilesEdades <- cuartiles(edades)

rango <- (max(edades) - min(edades))

Q1indice <- (length(edades) + 1)/4
Q3indice <- Q1indice*3
if(Q1indice != round(Q1indice)){
  Q1 <- (edades[round(Q1indice)] + edades[round(Q1indice)+1])/2
}else{
  Q1 <- edades[Q1indice]
}
if(Q3indice != round(Q3indice)){
  Q3 <- (edades[round(Q3indice)] + edades[round(Q3indice)+1])/2
}else{
  Q3 <- edades[Q1indice]
}

RangoIntercuartil <- Q3 - Q1

desvioEstandar <- round(sd(edades), 3)
variancia <- round(var(edades),3)

percentiles <- function(x, division){
  perc <- quantile(x, prob = division / 100)
  return (perc)
}

P10 <- percentiles(edades, 10)
P50 <- percentiles(edades, 50)


boxplot(edades, main="Boxplot de las edades", xlab="Mediciones", ylab = "Edad", col= "skyblue")
stem(edades, scale = 0.8)
hist(edades, col = "skyblue")
plot(edades, xlab="medidas")

