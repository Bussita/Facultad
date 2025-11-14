// Ejercicio 10 practica 7
//clc()
//clear()

// Aproximacion polinomial de minimos cuadrados para matrices con rango completo
function [valores, err] = minCuad_pol(A,b)
    [valores, A_amp] = eliminacionGaussConPP(A' * A, A'*b)
    err = norm(A*valores - b);
    
endfunction

// Matriz del metodo de minimos cuadrados polinomial

function A = A_mc(x,grado) // Vector de los puntos x medidos y grado es el grado del polinomio resultante
    // p = grado + 1
    m = length(x)
    A = ones(m,1)
    for j=2:(grado + 1)
        A = [A, (x).^(j-1)]
    end
endfunction

