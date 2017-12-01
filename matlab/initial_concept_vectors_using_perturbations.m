function [matr] = initial_concept_vectors_using_perturbations (A, k, dev)
  
  [n,m]=size(A);
  
  %calculating concept vector
  M=zeros(n,1);
  br=0;
  for i=1:m
    M(:,1)=M(:,1)+A(:,i);
    br=br+1;
  end
  M=(1/br)*M;
 
  % dividing by norm
  M(:,1) /= sqrt(sum (abs (M(:,1)) .^ 2));
  
  matr = zeros(n,k);
  for i=1:k
    matr(:,i)=normrnd(M,dev/sqrt(n*k),n,1);
  end

endfunction