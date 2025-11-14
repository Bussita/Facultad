function circ(r, x, y)
    w = 2 * r
    h = 2 * r
    
    xarc(x - r, y + r, w, h, 0, 360 * 64)
    gce().thickness = 2
endfunction


function Gers(A)
    [n, m] = size(A)
    
    centros = diag(A)
    radios = sum(abs(A), 'c') - abs(centros)

    min_x = min(centros - radios)
    max_x = max(centros + radios)
    min_xr = round(min_x - 1)
    max_xr = round(max_x + 1)
    
    min_y = min(-radios)
    max_y = max(radios)    
    min_yr = round(min_y - 1)
    max_yr = round(max_y + 1)

    rectangulo = [min_xr, min_yr, max_xr, max_yr]

    // Acotamos el radio espectral
    cota = max(abs(min_x), abs(max_x))    
    printf("p(A) <= %3.3f\n", cota)  

    av = spec(A)    
    a = gca()
    a.x_location = "origin"
    a.y_location = "origin"
    plot2d(real(av), imag(av), -1, "031", "", rectangulo);
    xgrid();

    // Imprimir los circulos
    for i = 1 : n
        circ(radios(i), centros(i), 0)
    end

    // Imprimir los centros
    y(1 : n) = 0    
    plot(centros, y, 'O')
    
    // Imprimir los autovalores
    plot(real(av), imag(av), 'X')

endfunction
