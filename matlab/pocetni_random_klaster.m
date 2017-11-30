function [M] = pocetni_random_klaster (A, k)

  [n,m]=size(A);
  
  x = randperm(m);
  %x
  for i=1:m
    x(i) = mod(x(i)-1,k) + 1;
  end
  %x
  
  % raèunanje poèetnih centroida
  M=zeros(n,k);
  for j=1:k
    br=0;
    for i=1:m
      if(x(i)==j)
        M(:,j)=M(:,j)+A(:,i);
        br=br+1;
      end
    end
    M(:,j)=(1/br)*M(:,j);

    % normiranje (kako bi centar ostao na sferi)
    M(:,j) /= sqrt(sum (abs (M(:,j)) .^ 2));
  end
  
endfunction