function [X]=txn(F,n,d)
  s=0
   for i=1:n-1
      for j=1:d
         s=F(j,i)^2 +s;
      end
      s=s^(-1/2);
      for j=1:d
         X(j,i)=F(j,i)*s;
      end
   end