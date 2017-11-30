function trunc_norm=k_trunc_svd(X,k)
  [U,S,V]=svd(X);
  r=rank(X);
  u=size(U);
  v=size(V);
  U_k=U(:,1:u-k);
  V_k=V(:,1:v-k);
  S_k=S(1:u-k,1:v-k);
  X_k=U_k*S_k*V_k';
  trunc_norm=norm(X_k,'fro');
  