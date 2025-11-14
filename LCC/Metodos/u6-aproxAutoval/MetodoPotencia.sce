function [valor, zn] = mpotencia(A,z0,eps,maxIter)
    valor = 0;
    iter = 1;
    w = A*z0;
    zn = w / norm(w,%inf);
    [m,j] = max(abs(w));
    //m = w(j)
    valor = w(j) / zn(j);
    zn = w/valor;
    while( (iter <= maxIter) &&  (norm(z0 - zn, %inf)>eps) )
        z0 = zn;
        w = A*z0;
        zn = w / norm(w,%inf);
        [m,j] = max(abs(w));
        //m = w(j)
        valor = w(j) / zn(j);
        zn = w/valor;        
        iter = iter + 1;
    end
    printf("Num Iteraciones: %d\n",iter);
endfunction
