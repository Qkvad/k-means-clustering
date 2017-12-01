function [dobr] = objective_function (A, M, x)
  
  if x(1)==0
    dobr = 0;
    return;
  end
  
  [d,n] = size(A);
  [d,k] = size(M);
  
  v = zeros(1,k);
  
  for i=1:n
    v(x(i)) += transpose(A(:,i))*M(:,x(i));
  end
  
  dobr = norm(v,2);
  
endfunction