
function [klaster,norma_aproksimacije,norma_SVD]=mainMatLab(k,iteracije)
  X=mmread('../extractor-output/matlab_data.mtx');
  [d,n]=size(X);
  %%umjesto iducih 5 linija stavi svoj algoritam
  %%m1,m5,m8 su izabrane centroide za testiranje
  m1=X(:,1);
  m5=X(:,5);
  m8=X(:,8);
  M=[m1 m5 m8];
  klaster=ksredine(X,M,k,iteracije);
  %%kmeans
  %%u funkciji ispod promijeni klaster i M ovisno o tvom algoritmu
  %%M je matrica centroida koje vraca tvoj algoritam
  %%klaster je vektor indeksa klastera koji vraca tvoj algoritam
  %% i-ti dokument spada u klaster broj klaster(i)
  norma_aproksimacije=decomposition_norm(X,M,klaster,k,d,n);
  norma_SVD=k_trunc_svd(X,k);
