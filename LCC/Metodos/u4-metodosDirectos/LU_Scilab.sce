function [P,L,U] = factorizacionLU(A)
    
    [nA,mA] = size(A)

    if nA<>mA then
        error('factorizacionLU - La matriz A debe ser cuadrada');
        abort;
    end;

    n = nA;    // Tamaño de la matriz
    
    // Inicializamos las matrices de la factorizacion
    U = A;
    L = eye(n,n);
    P = eye(n,n);

    // Escalonamos la matriz U
    for k = [1 : n - 1]  
        
        kpivot = k; // Primero consideramos como el mayor pivot al actual
        maxpivot = abs(U(k,k)); // Valor absoluto del actual pivote
    
        for i = k + 1 : n // Encontramos el mayor pivot
            if abs(U(i,k)) > maxpivot then
                kpivot = i;
                maxpivot = abs(U(i,k));
            end
        end
        
        // Intercambiamos las filas de U
        temp = U(k, k:n);
        U(k, k:n) = U(kpivot, k:n);
        U(kpivot, k:n) = temp;
        
        // Intercambiamos las filas de L
        temp = L(k, 1:k-1);
        L(k, 1:k-1) = L(kpivot, 1:k-1);
        L(kpivot, 1:k-1) = temp;
                
        // Intercambiamos las filas de P
        temp = P(k,:);
        P(k,:) = P(kpivot,:);
        P(kpivot,:) = temp;
    
        for i = k + 1 : n // Eliminamos los elementos inferiores en la columna
            
            L(i,k) = U(i,k) / U(k,k)
            
            U(i,k : n) = U(i, k : n) - U(k, k : n) * L(i,k);
        end
    end

endfunction


// Ejemplo de aplicación
//A = [2 1 1 0; 4 3 3 1; 8 7 9 5 ; 6 7 9 8]

//[P,L,U] = factorizacionLU(A)
//disp(P)
//disp(L)
//disp(U)
