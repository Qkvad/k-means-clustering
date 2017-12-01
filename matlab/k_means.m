function [x]=k_means(A,M,k,iter_num)
[n,m]=size(A);


for z=1:iter_num
    y=9999*ones(m);
    for i=1:m
        for j=1:k
            if(norm(A(:,i)-M(:,j),2)<y(i))
              y(i)=norm(A(:,i)-M(:,j),2);
              x(i)=j;
            end
        end
    end
  
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
    end
    M;
end