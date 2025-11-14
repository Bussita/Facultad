function B = esDiagDominante(A)
    B = 1;
    [n,m] = size(A);
    if n <> m then
        printf("esDiagDominante - La matriz no es cuadrada")
        abort
    end
    for i=1:n
        valorDiag = abs(A(i,i));
        suma = 0;
        for j=1:n
             if i <> j then
             suma = suma + abs(A(i,j));
         end
         if suma >= valorDiag then
             B = 0
         end
    end
    end
endfunction
