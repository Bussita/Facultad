//Gauss-Seidel
// xi^{k+1} =
// 1/aii (bi - sum_{j=1}^{i-1} aij xj^{k} - sum_{j=i+1,n}^{n} aij xj^{k} )


function x = gauss_seidel(A,b,x0, eps)
    n = size(A,1); //Cantidad de filas
    x = x0;
    xk = x;
    cont = 0;
    for i=1:n
        suma = 0;
        for j=1:n
           if (j<>i)
               suma = suma + A(i,j)* x(j); // USO LA ITER ACTUAL
           end 
        end
        x(i) = 1/A(i,i) * (b(i) - suma);    
    end
    cont = cont + 1;
    while(norm(x-xk)>eps)
     xk = x;
     for i=1:n
        suma = 0;
        for j=1:n
           if (j<>i)
               suma = suma + A(i,j)* x(j);
           end 
        end
        x(i) = 1/A(i,i) * (b(i) - suma);    
     end
     cont = cont + 1;        
    end
    disp(cont);
endfunction
