function [x, i] = metodoSOR(matriz_coef, b, x0, w, tolerancia, max_iter)

  // Chequeamos que la matriz sea cuadrada
  [n,m] = size(matriz_coef)

  if n <> m then 
    disp("La matriz no es cuadrada")
    x = %nan
    return
  end

  // Chequeamos que coincidan las dimensiones de la matriz y los valores independientes
  size_b = length(b)

  if size_b <> n then
    disp("No coinciden la dimension de la matriz con la de valores")
    x = %nan
    return
  end

  // Chequeamos que no tenga elementos nulos en la diagonal
  for i = [1 : n]

  if matriz_coef(i,i) == 0 then 

    disp("Hay elementos nulos en la diagonal")
    x = %nan
    return
  
  end
end

x = x0 // Valor inicial de la iteracion

xk = x // Valor que iremos iterando

iter = 1 // Cantidad de iteraciones

// Hacemos una primer iteracion
for i = [1 : n] // Iteramos por fila

  suma = 0

  for j = [1 : n] // Calculamos la suma de la fila sin incluir la diagonal

    if j < i then suma = suma + matriz_coef(i,j) * x(j)

    elseif j > i then suma = suma + matriz_coef(i,j) * xk(j) 
    
    end
  
  end
    
  x(i) = (1 - w) * x(i) + (w / matriz_coef(i,i)) * (b(i) - suma); // Calculamos el valor
      
end

// Seguimos iterando hasta que no se cumpla alguna de las condiciones
while norm(x - xk) > tolerancia  && iter < max_iter 
  
  xk = x

  for i = [1 : n] // Iteramos por fila

    suma = 0
  
    for j = [1 : n] // Calculamos la suma de la fila sin incluir la diagonal
  
      if j < i then suma = suma + matriz_coef(i,j) * x(j)
  
      elseif j > i then suma = suma + matriz_coef(i,j) * xk(j) 
      
      end

    end
      
    x(i) = (1 - w) * x(i)+ (w / matriz_coef(i,i)) * (b(i) - suma); // Calculamos el valor
        
  end
  
  
  iter = iter + 1; // Aumentamos el numero de iteraciones

end

i = iter;

endfunction





function w = omega_optimo(A)

  n = size(A)(1) // Obtenemos el tamanio de la matriz

  // Calculamos la matriz de iteraion del metodo de Jacobi
  Tj = eye(n,n) - diag(1 ./ diag(A)) * A; 

  rho = max(abs(spec(Tj))); // Calculamos el radio espectral

  w = 2 / (1 + sqrt(1 - rho ** 2)) // Calculamos el omega optimo

endfunction
