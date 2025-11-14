function A = crearC(c)
    A = zeros(5,5);
   // A = A*(1+2*c)
    for i=1:5
        A(i,i) = 1+2*c;
        if i <> 5 then
        A(i+1,i) = -c;
        A(i,i+1) = -c;
        end
       
    end
endfunction

