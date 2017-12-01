
function [klaster,norma_aproksimacije,norma_SVD]=mainMatLab(k,iter_num)
  X=mmread('../extractor-output/matlab_data.mtx');
  [d,n]=size(X);
  
  %m1=X(:,1);
  %m5=X(:,5);
  %m8=X(:,8);
  %M=[m1 m5 m8];
  M = initial_concept_vectors_using_perturbations(X,k,0.2);
  klaster=spherical_k_means(X,M,k,iter_num);
  
  norma_aproksimacije=decomposition_norm(X,M,klaster,k,d,n);
  norma_SVD=k_trunc_svd(X,k);
