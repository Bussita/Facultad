
function integral = metodoTrapecioCompuesto(fun, a, b, n)

  // Verificamos que el intervalo sea correcto
  if (b < a) then
    error("metodoTrapecioCompuesto: intervalo incorrecto");
    abort;
  end

  // Verificamos que el n sea correcto
  if (n <= 0) then
    error("metodoTrapecioCompuesto: Valor de n incorrecto");
    abort;
  end

  deff("y=f(x)","y=" + fun); // Definimos nuestra funcion

  h = (b - a) / n;

  integral = 0;

  xj = a;

  for j = [0 : n]

    if j == 0 || j == n then

      integral = integral + 1/2 * f(xj);
    
    else

      integral = integral + f(xj);
    
    end
    
    xj = xj + h; // Actualizamos el punto
  
  end

  integral = h * integral;

endfunction


// Ejercicio 3 P8 complementaria

function integral = integralSi(b,n)
    if(b<=1) then
        printf("El intervalo es incorrecto\n")
        abort
        end
    integral = metodoTrapecioCompuesto("sin(x)/x",1,b,n);
endfunction
