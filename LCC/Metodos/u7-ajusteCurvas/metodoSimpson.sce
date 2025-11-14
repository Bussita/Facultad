function integral = reglaSimpson(fun, a, b)
  
  // Verificamos que el intervalo sea correcto
  if (b < a) then
    error("metodoTrapecio: intervalo incorrecto");
    abort;
  end
  
  deff("y=f(x)","y=" + fun); // Definimos nuestra funcion

  h = (b - a) / 2;

  integral = (h / 3) * (f(a) + 4 * f(a + h) + f(b));
endfunction




function integral = reglaSimpsonCompuesta(fun, a, b, n)

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

  if (modulo(n,2) == 1) then
    error("metodoTrapecioCompuesto: el valor n tiene que ser par");
    abort;
  end

  deff("y=f(x)","y=" + fun); // Definimos nuestra funcion

  h = (b - a) / n;

  integral = 0;

  xj = a;

  for j = [0 : n]

    if j == 0 || j == n then

      integral = integral + f(xj);
    
    elseif (modulo(j,2) == 1) then

      integral = integral + 4 * f(xj);
    
    else

      integral = integral + 2 * f(xj);

    end

    xj = xj + h;

  end

  integral = (h / 3) * integral;

endfunction
