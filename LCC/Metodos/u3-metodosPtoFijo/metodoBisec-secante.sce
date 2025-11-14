function raiz = metodo_biseccion(fun, a, b, tolerancia, maxIteraciones)

  deff("y = f(x)", "y=" + fun);  // Definimos la funcion


  if (a >= b) then // Es un intervalo incorrecto
    
    raiz = %nan;

    disp("Intervalo incorrecto");
    
    return;

  end


  if f(a) * f(b) > 0 then // No es posible aplicar el metodo
    
    raiz = %nan;

    disp("f(a)f(b) > 0, no podemos aplicar Bolzano");

    return;

  
  elseif f(a) * f(b) == 0 // Algunas de los extremo es raiz
    
    if f(a) == 0 then raiz = a;
    
    else raiz = b; end


  else // f(a) * f(b) < 0

    raiz = (a + b) / 2; // Definimos el valor intermedio

    numIter = 0; // Numero de iteraciones

    while b - raiz > tolerancia && numIter < maxIteraciones
      
      numIter = numIter + 1;

      // Comparamos el f(c) con f(a) y f(b)

      if f(raiz) == 0 then // Calculamos justo la raiz

        return;
        
      else if f(b) * f(raiz) < 0
        
        a = raiz;
      
      else b = raiz;

      end


      raiz = (a + b) / 2; 

    end
end
mprintf("Iteraciones: %d Raiz: %f", numIter, raiz);
end
endfunction

function raiz = metodo_secante(fun, x0,x1, tol,maxIter);
    deff("y=f(x)","y="+fun);
    raiz = x1 - f(x1) * (x1-x0)/(f(x1)-f(x0))
    numIter = 0;
    while abs(raiz - x1) > tol && numIter <= maxIter
        x0 = x1
        x1 = raiz
        raiz = x1 - f(x1) * (x1-x0) / (f(x1)-f(x0))
        numIter = numIter + 1;
    end
    mprintf("Iteraciones: %d Raiz: %f",numIter,raiz)
endfunction
