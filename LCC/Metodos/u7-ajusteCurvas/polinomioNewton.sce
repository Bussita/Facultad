function w = difdiv(x,y)

  n = length(y);

  if n == 1 then

    w = y(1);

  else
    
    w = (difdiv(x(2:n), y(2:n)) - difdiv(x(1:n-1), y(1:n-1))) / (x(n) - x(1));
    end
endfunction

// Polinomio interpolante mediante el metodo de Newton
function p = interpolNewton(x,y)

  n = length(x);
  r = poly(0, "x");

  p = 0;

  for i = n:-1:2
    p = (p + difdiv(x(1:i), y(1:i))) * (r - x(i-1));
  end

  p = p + y(1);

endfunction
