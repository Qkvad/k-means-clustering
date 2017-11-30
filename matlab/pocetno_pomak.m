function [matr] = pocetno_pomak (A, k, dev)
  
  [n,m]=size(A);
  
  %raèunanje centroida svega
  M=zeros(n,1);
  br=0;
  for i=1:m
    M=M+A;
    br=br+1;
  end
  M=(1/br)*M;
 
  % normiranje (kako bi centar ostao na sferi)
  M(:,j) /= sqrt(sum (abs (M(:,j)) .^ 2))
  
  matr = zeros(n,k);
  for i=1:k
    matr(:,i)=normrnd(M,dev/sqrt(n*k),n,1);
  end
  
  % traženje najbližih centroida i stvaranje poèetnih klastera
  %y=9999*ones(m);
  %for i=1:m
  %  for j=1:k
  %    if(norm(A(:,i)-matr(:,j),2)<y(i))
  %      y(i)=norm(A(:,i)-matr(:,j),2);
  %      x(i)=j;
  %    end
  %  end
  %end

endfunction