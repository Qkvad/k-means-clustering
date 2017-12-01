function norm_err_apr=decomposition_norm(X,M,A,k,d,n)
  X_apr=M*inverse(M'*M)*M'*X;
  norm_err_apr=norm(X-X_apr,'fro');
