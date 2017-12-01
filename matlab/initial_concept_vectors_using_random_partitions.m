function [M] = initial_concept_vectors_using_random_partitions (A, k)

  [n,m]=size(A);
  
  % calculate starting partition
  x = randperm(m);
  %x
  for i=1:m
    x(i) = mod(x(i)-1,k) + 1;
  end
  x
  
  % calculate initial concept vector
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

    % dividing by norm (to put them on a sphere)
    M(:,j) /= sqrt(sum (abs (M(:,j)) .^ 2));
  end
  
endfunction