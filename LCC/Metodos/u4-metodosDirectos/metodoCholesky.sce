function U = metodoCholesky(A)
    
    eps = 1.0e-30;
    
    n = size(A,1)
    U = zeros(n,n);
    
    for k = 1 : n
        
        // Calculamos el valor de t
        if k == 1 then 
           t = A(k,k);
        else
            t = A(k,k) - U(1:k-1, k)' * U(1:k-1, k);
        end
        
        // Chequeamos que el autovalor sea definido positivo
        if t <= eps then
            error("metodoCholesky - La matriz debe ser definida positiva");
            abort;   
        end
        
        U(k,k) = sqrt(t);
        
        for j = k + 1 : n
            
            if k == 1 then
                U(k,j) = A(k,j)/U(k,k)
            else
                U(k,j) = (A(k,j) - U(1:k-1,k)' * U(1:k-1,j)) / U(k,k);
            end
        end        
    end
    
endfunction

A = [4 1 1; 8 2 2; 1 2 3]
U = metodoCholesky(A)
disp(U)


B = [5 2 1 0; 2 5 2 0; 1 2 5 2; 0 0 2 5]
U = metodoCholesky(B)
disp(U)


C = [5 2 1 0; 2 -4 2 0; 1 2 2 2; 0 0 2 5]
U = metodoCholesky(C)
disp(U)
