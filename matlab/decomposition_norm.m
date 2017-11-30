function norm_err_apr=decomposition_norm(X,M,A,k,d,n)
  for i=1:n
    X_apr(:,i) = M(:,A(i));
  end
  norm_err_apr=norm(X-X_apr,'fro');
