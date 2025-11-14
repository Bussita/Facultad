function [L,U] = metodoDoolittle(A)
    
    [n,m] = size(A);
    
    if n <> m then
        error("metodoDoolittle - la matriz A debe ser cuadrada");
        abort;
    end
    
    L = zeros(n,n);
    U = zeros(n,n);
    
    for s = 1 : n 
        
        // Calculamos la siguiente fila de U
       for j = s : n
            
            suma = 0;
            
            for k = 1 : s - 1 
                suma = suma + L(s,k) * U(k,j);
            end
            
            U(s,j) = A(s,j) - suma
       end
        
        // Calculamos la siguiente columna de L
        for i = s : n
            
            suma = 0;
            
            for k = 1 : s - 1 
                suma = suma + L(i,k) * U(k,s);
            end
            
            L(i,s) = (A(i,s) - suma) / U(s,s);
       end 
    end
    
endfunction
