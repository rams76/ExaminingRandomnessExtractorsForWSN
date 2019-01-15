#pragma once
#include "../shared/utils.h"

#define D_LAG 128

// Section 6.3.8 - Lag Prediction Estimate
double lag_test(byte *data, long len, int alph_size){
	int winner; 
	long i, d, N, C, run_len, max_run_len;
	long scoreboard[D_LAG] = {0};
	double p_global, p_local;
	
	if(len < 2){	
		printf("\t*** Warning: not enough samples to run lag test (need more than %d) ***\n", 2);
		return -1.0;
	}

	N = len-1;
	winner = 0;
	C = 0;
	run_len = 0;
	max_run_len = 0;

	// perform predictions
	for (i = 1; i < len; i++){
		// test prediction of winner
		if(data[i-winner-1] == data[i]){
			C++;
			if(++run_len > max_run_len) max_run_len = run_len;
		}
		else run_len = 0;

		// update scoreboard and select new winner
		for(d = 0; d < D_LAG; d++){
			if((i > d) && (data[i-d-1] == data[i])){
				if(++scoreboard[d] >= scoreboard[winner]) winner = d;
			}
		}
	}

	p_global = calc_p_global(C, N);
	p_local = calc_p_local(max_run_len, N);

	return -log2(max(max(p_global, p_local), 1/(double)alph_size));
}
