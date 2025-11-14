// Grafica la integral definida desde 0 a b de f, tomando un paso para los puntos de los intervalos.
// * f es la funcion pasada como string
// * b es el extremo superior del intervalo a evaluar
// * paso es un numero suficientemente chiquito para evaluar las integrales desde 2 puntos que tengan la distancia de paso
// Ej: para f = sin(x), b = 1, paso= 0.1, grafica: 
// sin(x) en rojo
// integral de 0 a x, para cada x = 0 + (i * paso), i natural 
function grafica_integral(f, b, paso)
    deff("z = g(x)", "z = " + f)

    x = 0 : paso : b
    n = length(x)
    y_f = g(x)
    y_int = zeros(1, n)
    
    xi = 0              // xi inicial
    xk = paso           // xk = xi + paso 
    temp_int = 0        // guarda la integral de 0 a xi (es decir, al de la anterior iteracion)

    for i=1:n
        y_int(i) = temp_int + trapecio(f, xi, xk, 1);
        temp_int = y_int(i);
        xi = xk
        xk = xk + paso
    end
    
    yy = zeros(1, n); // Vector de ceros con el tamaño de x. Sirve como eje x = 0.
    
    plot(x, y_f, 'thickness', 2, 'color', 'red')        // Funcion
    plot(x, y_int, 'thickness', 2, 'color', 'blue')     // Integral definida de 0 a b
    plot(x, yy, 'color', 'black') // Eje x
    // plot(yy, x, 'color', 'black') // Eje y

    legend(['f(x)', 'Integral de f(x)'])
    xgrid();
    a = gca();
    a.auto_scale = "off"; 
endfunction
