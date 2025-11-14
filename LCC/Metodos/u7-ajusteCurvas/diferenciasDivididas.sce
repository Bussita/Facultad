function [pol, div] = interpolacionDiferenciasDivididas(x,y)

  div = calcularDiferenciasDivididas(x,y); // Calculamos las diferencias divididas

  n = length(x); // Cantidad de puntos que tenemos

  xvar = poly([0 1], "x","coeff"); 

  productos = ones(1,n);

  for i = [2:n] 

    productos(i) = productos(i-1) * (xvar - x(i - 1));
  
  end

  pol = div(1, 1:n) * productos';
  
  div = div(1, 1:n); // Nos interesa la primer fila para poder evaluar el polinomio 

endfunction


// Calcula el polinomio interpolador ya de manera encajada
function pol = interpolacionDiferenciasDivididasEncajado(x,y)

  div = calcularDiferenciasDivididas(x,y); // Calculamos las diferencias divididas

  n = length(x); // Cantidad de puntos que tenemos
  
  div = div(1,1:n); // Nos quedamos solamente con la primera fila

  xvar = poly([0 1], "x","coeff"); 
  
  pol = div(n);

  for i = [n - 1: -1: 1]
    
    pol = div(i) + (xvar - x(i)) * pol;

  end
endfunction





// Funcion que calcula la table de diferencias divididas.
function div = calcularDiferenciasDivididas(x,y)

  n = length(x); // Cantidad de puntos que tenemos

  calculado = eye(n,n); // Matriz que determina si calculamos la diferencia dividida ij
  div = diag(y); // Matriz con los valores base de la recursion

  [div,calc] = calcularDiferenciasDivididasRecursiva(div,calculado,1,n,x);

endfunction


function [div,calc] = calcularDiferenciasDivididasRecursiva(div,calc,i,k,x)

  if (calc(i,k) == 1) // Si ya calculamos dicha diferencia dividida ik, no hacemos nada
    return 
  
  else // En caso de que no hayamos calculado la diferencia dividia ik

    [div, calc] = calcularDiferenciasDivididasRecursiva(div, calc, i, k-1,x); // Calculamos la primer parte
    [div, calc] = calcularDiferenciasDivididasRecursiva(div, calc, i+1, k,x); // Calculamos la segunda parte

    div(i,k) = (div(i+1,k) - div(i,k-1)) / (x(k) - x(i)); // Calculamos la diferencia dividida ik
    calc(i,k) = 1; // Marcamos que calculamos dicha diferencia
  end

endfunction
