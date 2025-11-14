function v = DobleTn(f,a,b,c,d,n,m) // n ab m cd
    h = (b-a)/n;
    deff('z=fxa(y)',"z=f(" + string(a)+",y)");
        deff('z=fxa(y)',"z=f("+ string(b) + ",y)");
        v = Tn(fxa, c(a), d(a), m)/2 + Tn(fxb,  c(b), d(b), m)/2;
        for i = 1:n-1
            xi = a + i * h;
            deff("z=fxi(y)","f(" + string(xi) + ",y)");
            v = v + Tn(fxi, c(xi), d(xi), m);
        end
        v = v * h;
endfunction

// Ejemplo de aplicación 

function y = cx(x)
    y = -sqrt(2*x - x^2);
endfunction

function y = dx(x)
    y = sqrt(2*x - x^2);
endfunction
function y = uno(x)
    y = 1;
endfunction

DobleTn(uno, 0, 2, cx, dx, 10000, 10000)
