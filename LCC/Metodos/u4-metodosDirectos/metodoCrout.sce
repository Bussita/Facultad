function [L,U]=crount(A)
    n=size(A,1)
    U=eye(n,n)
    L=zeros(n,n)
    for j=1:n
        for i=1:n
            aux=0
            for k=1:j-1
                aux=aux+(L(i,k)*U(k,j))
            end
            if i>=j then
                L(i,j)=A(i,j)-aux
            elseif i<=j then
                U(i,j)=(1/L(i,i))*(A(i,j)-aux)
            end
            
                
        end
        
    end
endfunction
