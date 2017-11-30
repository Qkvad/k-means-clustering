function [x]=sferneksredine(A,M,k,iteracije)
  [n,m]=size(A);
  x = zeros(m,1);

  d = -1;
  for z=1:iteracije
  
    % traženje najbližih centroida i stvaranje novih klastera
    y=9999*ones(m);
    for i=1:m
        for j=1:k
            if(norm(A(:,i)-M(:,j),2)<y(i))
              y(i)=norm(A(:,i)-M(:,j),2);
              x(i)=j;
            end
        end
    end
    
    x
  
    % raèunanje novih centroida
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
    
    d_stara = d;
    d = dobrota(A, M, x);
    d
    if(d<=d_stara)
      break;
    end

  end
 
endfunction