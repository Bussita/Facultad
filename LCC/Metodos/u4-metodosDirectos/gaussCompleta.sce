function [S,P,L,U] = eliminacionGaussCompleta(A, B)
    
    [nA,mA] = size(A);
    [nB, mB] = size(B);

    if nA<>mA then
        error('eliminacionGaussCompleta - La matriz A debe ser cuadrada');
        abort;
    end;

     if mA <> nB then
        error("eliminacionGaussCompleta - Dimensiones incompatibles entre A y b");
        abort;
    end;
    
    n = nA;    // Tamaño de la matriz
    a = [A B]; // Matriz del sistema aumentada
    
    // Inicializamos las matrices de la factorizacion
    L = eye(n,n);
    P = eye(n,n);

    // Escalonamos la matriz a (matriz del sistema aumentada)
    for k = [1 : n - 1]  
        
        kpivot = k; // Primero consideramos como el mayor pivot al actual
        maxpivot = abs(a(k,k)); // Valor absoluto del actual pivote
    
        for i = k + 1 : n // Encontramos el mayor pivot en la columna
            if abs(a(i,k)) > maxpivot then
                kpivot = i;
                maxpivot = abs(a(i,k));
            end
        end
        
        // Intercambiamos las filas de a
        temp = a(k, k: n + mB);
        a(k, k: n + mB) = a(kpivot, k: n + mB);
        a(kpivot, k:n + mB) = temp;
        
        // Intercambiamos las filas de L
        temp = L(k, 1:k-1);
        L(k, 1:k-1) = L(kpivot, 1:k-1);
        L(kpivot, 1:k-1) = temp;
                
        // Intercambiamos las filas de P
        temp = P(k,:);
        P(k,:) = P(kpivot,:);
        P(kpivot,:) = temp;
    
        for i = k + 1 : n // Eliminamos los elementos inferiores en la columna
            
            L(i,k) = a(i,k) / a(k,k);
            
            a(i,k : n + mB) = a(i, k : n + mB) - a(k, k : n + mB) * L(i,k);
        end
    end

    // Seteamos la matriz U luego de haber escalonado el sistema
    U = a(1:n , 1:n)

    B = a(1 : n, n + 1 : n + mB);
    
    S = zeros(n, mB);

    S(n , 1 : mB) = B(n, 1 : mB ) / U(n,n);

    for i = [n - 1 : -1 : 1]
        
        S(i, 1 : mB) = (B(i, 1 : mB) - U(i, i + 1 : n) * S(i + 1 : n, 1 : mB)) / U(i,i);
        
    end        


endfunction
