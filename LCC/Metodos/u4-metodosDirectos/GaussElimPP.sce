function [x, a] = eliminacionGaussConPP(A, b)
    
    [nA,mA] = size(A) 
    [nb,mb] = size(b)

    if nA<>mA then
        error('gausselim - La matriz A debe ser cuadrada');
        abort;
        
    elseif mA<>nb then
        error('gausselim - dimensiones incompatibles entre A y b');
        abort;
    end;

    a = [A b]; // Matriz aumentada
    n = nA;    // Tamaño de la matriz

    // Escalonamos la matriz
    for k = [1 : n - 1]
        
        kpivot = k; // Primero consideramos como el mayor pivot al actual
        maxpivot = abs(a(k,k)); // Valor absoluto del actual pivote
    
        for i = k + 1 : n // Encontramos el mayor pivot
            if abs(a(i,k)) > maxpivot then
                kpivot = i;
                maxpivot = abs(a(i,k));
            end
        end
        
        // Intercambiamos las filas
        temp = a(k, k:n+1);
        a(k, k:n+1) = a(kpivot, k:n+1);
        a(kpivot, k:n+1) = temp;
    
        for i = k + 1 : n // Eliminamos los elementos inferiores en la columna
            
            a(i,k : n + 1) = a(i, k : n + 1) - (a(k, k : n + 1) * a(i,k) / a(k,k));
            
        end

    end
    
    // Realizamos la sustitucion regresiva
    
    b = a(1 : n, n + 1);
    
    x = zeros(n, 1);

    x(n) = b(n) / a(n,n);

    for i = [n - 1 : -1 : 1]
        
        x(i) = (b(i) - a(i, i + 1 : n) * x(i + 1 : n)) / a(i,i);
        
    end             
endfunction


// Ejemplo de aplicación
//A = [0 2 3; 2 0 3; 8 16 -1]
//b = [7 13 -3]'

//[x,a] = eliminacionGaussConPP(A,b)
//disp(x)
//disp(a)
