function pol = polinomioLagrange(x, y)
    pol = poly([0], "x", "coeff");
    if (length(x)<>length(y)) then
        printf("Tabla de valores incorrecta.");
        abort
    end
    n = length(x);
    for i = [0 : n-1]
        pol = pol + Lk(x,i)*y(i+1)
    end
endfunction

function pol = Lk(x,k)
    xk = x(k+1)
    n = length(x)
    pol = poly([1], "x", "coeff");
    variableX = poly([0 1],"x", "coeff");
    
    for i = 1 : n
        if(i <> k+1) then
            pol = pol*(variableX-x(i))/(xk-x(i));
            end
    end
endfunction

