// Devuelve las raices del polinomio de chebyshev de orden n
// en el intervalo [-1,1]
function r = chebyshev(n)
    coef = %pi / (2 * n);
    for k = 0 : n - 1
        k_odd = 2 * k + 1;
        
        r(k + 1) = cos(coef * k_odd);
    end
endfunction

// Devuelve las raices del polinomio de chebyshev de orden n
// en un intervalo generico [a,b]
function r_ab = chebyshev_ab(n, a, b)
    r = chebyshev(n);
    
    for k = 1 : n
        r_ab(k) = ((b + a) + r(k) * (b - a)) / 2
    end
endfunction
