function [x]=spherical_k_means(A,M,k,iter_num)
  [n,m]=size(A);
  x = zeros(m,1);

  d = -1;
  for z=1:iter_num
  
    % searching of the closest concept vectors and creating new partition
    y=9999*ones(m);
    for i=1:m
        for j=1:k
            if(norm(A(:,i)-M(:,j),2)<y(i))
              y(i)=norm(A(:,i)-M(:,j),2);
              x(i)=j;
            end
        end
    end
    
    %x
  
    % calculating new concept vectors
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
    d = objective_function(A, M, x);
    %d
    if(d<=d_stara)
      break;
    end

  end
 
endfunction