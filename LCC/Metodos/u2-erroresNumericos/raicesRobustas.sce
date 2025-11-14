function r = raicesRobustas(p);
    c = coeff(p,3);
    b = coeff(p,2);
    a = coeff(p,1);
    discriminante = b**2 - 4*a*c;
    if b >= 0 then
        r(1) = (-b - sqrt(discriminante))/(2*a);
        r(2) = (2*c)/(-b - sqrt(discriminante));
    else
        r(2) = (-b + sqrt(discriminante))/(2*a);
        r(1) = (2*c)/(-b + sqrt(discriminante)); 
    end
endfunction

clc // limpia la consola
clear // borra el contenido de la memoria
xdel(winsid()) // cierra ventanas gr´aficas
// Definici´on de la funci´on
function y = f(x)
y = x.*x;
endfunction
// C´alculo de la derivada utilizando diferencias finitas
function y = dfa(f,x,h)
y = (f(x+h) - f(x))./h;
endfunction
x = 1; // Punto donde vamos a evaluar la derivada
ih = (0:16)';
h = (10.^-ih); // Vector con los valores de h
df approx = dfa(f,x,h); // Evaluaci´on de la derivada por diferencias finitas
df scilab = numderivative(f,x,[],order=1); // Derivada obtenida por numderivative
df true = 2; // Valor verdadero de la derivada en x = 1
// Errores absolutos y relativos
err abs = abs(df approx - df true);
err rel = err abs./abs(df true);
err abs sci = abs(df scilab - df true);
err rel sci = err abs sci/abs(df true);
// Gr´afica
plot(ih,log10(err rel),’b*-’); // Gr´afica en escala logar´ıtmica en el eje y
title(’Error relativo utilizando diferencias finitas’);
xlabel(’i’);
ylabel(’$log {10} (Err Rel)$’);
plot(ih,log10(err rel sci*ones(length(ih),1)),’r-’);
// Impresi´on de resultados en pantalla
tablevalue = [ih,h,df true*ones(length(h),1),df approx,err abs,err rel];
mprintf(’ %s\n’,strcat(repmat(’-’,1,80)));
mprintf(’ %4s %8s %12s %18s %14s %14s\n’,...
’i’, ’h’,’Der. exact’,’Der approx’,’Abs. error’,’Rel. error’);
mprintf(’ %s\n’,strcat(repmat(’-’,1,80)));
mprintf(’ %4d %8.1e %9.6e %18.10e %14.5e %14.5e\n’,tablevalue);
mprintf(’ %s\n’,strcat(repmat(’-’,1,80)));
mprintf(’ %4.1s %8s %9.6e %18.10e %14.5e %14.5e\n’,...
’ ’, ’Scilab’,[df true,df scilab,err abs sci,err rel sci]);
mprintf(’ %s\n’,strcat(repmat(’-’,1,80)));
