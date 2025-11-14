function v = TnExt(f,a,b,c,d)
    h = (b-a)*(d-c)/4;
    v = h * (f(c,a) + f(c,b) + f(d,a) + f(d,b));
endfunction

// Ejemplo de aplicación 

deff("z =g(x,y)","z = sin(x+y)");

TnExt(g,0,2,0,1)
