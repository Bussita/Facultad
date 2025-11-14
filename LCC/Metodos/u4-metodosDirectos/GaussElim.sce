function [x,a] = eliminacionGaussSinPP(A,b)
    
    [nA, mA] = size(A);
    [nB, mB] = size(b);
    
    if nA <> mA then
        error("eliminacionGaussSinPP - La matriz debe ser cuadrada");
        abort;
    end
    
    if mA <> nB then
        error("eliminacionGaussSinPP - Dimensiones incompatibles entre A y b");
        abort;
    end;
    

    a = [A b] // Matriz aumentada del sistema   
     
    n = nA;
    iter = 0;
    // Escalonamos la matriz
    for k = [1 : n - 1]  
    
        for i = k + 1 : n 
            
            a(i,k : n + 1) = a(i, k : n + 1) - (a(k, k : n + 1) * a(i,k) / a(k,k));
            
        end
        iter = iter + 1;
    end
    
    // Realizamos la sustitucion regresiva
    
    b = a(1 : n, n + 1);
    
    x = zeros(n, 1);

    x(n) = b(n) / a(n,n);

    for i = [n - 1 : -1 : 1]
        
        x(i) = (b(i) - a(i, i + 1 : n) * x(i + 1 : n)) / a(i,i);
        
    end         
    disp(iter);
endfunction



// Ejemplos de aplicación
A = [3 -2 -1; 6 -2 2; -9 7 1]
b = [0 6 -1]'

[x,a] = eliminacionGaussSinPP(A,b)
disp(x);
disp(a);
