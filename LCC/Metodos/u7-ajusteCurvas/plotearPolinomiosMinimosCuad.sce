// Generar puntos para graficar las curvas
function graficar_polinomiosMC(x,y,p1,p2,p3)
x_curve = 0:0.1:13;

y_curve1 = horner(p1, x_curve'); // Evaluar el polinomio lineal
y_curve2 = horner(p2, x_curve'); // Evaluar el polinomio cuadrático
y_curve3 = horner(p3, x_curve'); // Evaluar el polinomio cúbico

// Graficar los datos originales
plot2d(x, y, style=-4, leg="Datos originales"); // Puntos, estilo -4 para marcadores
clf(); // Limpiar el gráfico
plot2d(x_curve,[y_curve1, y_curve2, y_curve3], leg="Poli1@Poli2@Poli3")// Puntos de datos originales

endfunction
