
// Realiza la aproximacion por minimos cuadrados, utilizando un conjunto de funciones pasados por parametro como strings
function [coeficientes, err] = minimosCuadrados(x, y, funciones);

  m = length(x);

  p = size(funciones)(2);

  A = zeros(m,p);

  // Definimos nuestra familia de funciones
  for j = [1 : p] 
  
    deff("y = f(x)", "y = " + funciones(j));

    // Construimos la primera columna de nuestra matriz
    for i = [1 : m] 
      A(i,j) = f(x(i));
    end
    
  end

  [coeficientes, P, L, U] = eliminacionGaussCompleta(A'*A, A'*y') // Vemos la solucion del sistema At*A*x = At*b

  err = norm(A*coeficientes-y', 2);

endfunction


function stringFuncion = construirFuncion(funciones, coeficientes)

  p = size(funciones)(2);

  stringFuncion = "";

  for i = [1 : p - 1]

    stringFuncion = stringFuncion + string(coeficientes(i)) + "*" + funciones(i) + "+";

  end

  stringFuncion = stringFuncion + string(coeficientes(p)) + "*" + funciones(p);

endfunction
