// ***************** ***************** *****************
// *****************   AUXILIARES QR   *****************
// ***************** ***************** *****************

// Importamos la factorizacion QR
function c = col(A, k)
    c = A(:,k)
endfunction


// Factorizacion QR
// Q = (q1 | q2 | ... | qn)
// R es tal que A = QR
function [Q, R] = factQR(A)
    // Necesitamos calcular la base ortonormal por GS para Q
    // luego R deriva de esta

    [m, n] = size(A)
    Q = zeros(A)
    R = zeros(n, n)
    
    // Defino el primer vector columna de la base, q1 = a1/v1
    v_1 = norm(col(A, 1));
    Q(:, 1) = col(A, 1) / v_1
    R(1, 1) = v_1;
    
    for k = 2 : n
        acum = zeros(1 : m)';
        
        for i = 1 : k - 1
            // Calculo la sumatoria
            q_i = col(Q, i)
            a_k = col(A, k)
            
            // Calculo de paso el coeficiente ik de R
            r_ik = a_k' * q_i;
            acum = acum + r_ik .* q_i;
            
            R(i, k) = r_ik;
        end    
        
        // Calculo v_k
        v_k = norm(a_k - acum)
            
        // Defino la columna k de Q
        q_k = (a_k - acum) / v_k;
        Q(:, k) = q_k;     
        
        // Y colocamos en R el valor de la diagonal
        R(k, k) = v_k;
    end
endfunction


function b = remontesup(A, b)
    [n, m] = size(A)
    
    b(n) = b(n) / A(n, n)
    for i = n - 1 : -1 : 1
        suma = b(i)
        
        for j = i + 1 : n 
            suma = suma - A(i, j) * b(j)
        end
        
        b(i) = suma / A(i, i)        
    end   
endfunction

function res = factQR_sol(A, b)
    [Q, R] = factQR(A);
    
    b_prima = Q' * b;
    res = remontesup(R, b_prima);
endfunction


function coefs = ej1a()
    v = [54.3, 61.8, 72.4, 88.7, 118.6, 194]
    p = [61.2, 48.2, 37.6, 28.4, 19.2, 10.1]
    log_p = log(p)
    log_v = log(v)
    //disp(log_p)
    
    // Definimos la matriz A de funciones phi evaluadas en x
    m = length(v)
    A = ones(m, 1)
    //disp(A)
    A = [A log_v']
    
    // Descomponemos A = QR
    coefs = factQR_sol(A, log_p')
    a0 = exp(coefs(1))
    a1 = coefs(2)
    coefs = [a0 a1]
    mprintf("Los valores de los coeficientes son:\n a0 = C = %f\n a1 = alpha = %f\n\n", a0, a1)
endfunction


function ej1d()
    v = [54.3, 61.8, 72.4, 88.7, 118.6, 194]
    p = [61.2, 48.2, 37.6, 28.4, 19.2, 10.1]
    
    coefs = ej1a()
    plot(v, p, 'O')
    deff("z = f(x)", "z = " + string(coefs(1)) + "* x^" + string(coefs(2)))
    
    x_func = 53:1:195
    y_func = f(x_func)
    plot(x_func, y_func, 'thickness', 1.5, 'color', 'red')
    legend(["Puntos", "f(V)"])
endfunction


function estim = ej1c()
    coefs = ej1a()
    deff("z = f(x)", "z = " + string(coefs(1)) + "* x^" + string(coefs(2)))
   
    v = 100
    estim = f(v)
    mprintf("El valor estimado de f(100) es %f", estim)
endfunction

ej1a()
ej1d()
ej1c()
