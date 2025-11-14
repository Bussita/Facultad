function x = triangularSup(A, b);
    [nA, mA] = size(A);
    [nB, mB] = size(b);
    if (nB > nA || nB < nA)
        mprintf("Sistema sin solución única.\n");
        return %nan;
    end;
    if(mB > 1)
       mprintf("Vector incorrecto.\n")
       return %nan; 
    end;
    n = nB
    x(n,1) = b(nB,mB)/A(nA,mA)
    contador = n -1;
    while(contador >0)
        j = contador + 1;
        suma = 0;
        while(j<=n)
            suma = suma + A(contador, j)*x(j)
            j = j + 1
        end;
        x(contador,1) = (1/A(contador, contador))*(b(contador,mB) - suma)
        contador = contador - 1;
    end;
endfunction

