
#include <math.h>

void txn(double** X, int d, int n){
	double s=0.0;
	for(int i=0;i<n;i++){
		for(int j=0;j<d;j++){
			s=(X[j][i]*X[j][i])+s;	
		}
		s=1/sqrt(s);
		for(int j=0;j<d;j++){
			X[j][i]=X[j][i]*s;					
		}	
	}
}
