#include <stdio.h>
#include <math.h>

int main(void){

double w0 = 9534.625892455922;
double w;
double beta = 1545.4545454545453;


for(w = 0.0; w <= w0*2; w += 0.1*w0){
	printf("%lf\n", (0.3*w)/( 0.55*1e-3 * sqrt( pow(w0*w0 - w*w , 2) + 4*beta*beta*w*w )));
	
	//printf("%lf\n", w);


} 
printf("\n\n\n");

for(w = 0.0; w <= w0*2; w += 0.1*w0){
	printf("%lf\n", w);
}

return 0;
}
