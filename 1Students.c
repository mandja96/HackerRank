#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_N 60
#define MAX_GRADE 100

int* solve(int grades_size, int* grades, int *result_size){
    int *result = malloc(sizeof(int) * grades_size);

    int i, br = 0;

    for(i = 0; i < grades_size; i++){
    	if(grades[i] < 38){
    		result[br++] = grades[i];	
    	}
    	else if((grades[i] % 5) == 0){
    		result[br++] = grades[i];
    	}
    	else if(grades[i] % 5 > 0){
    		int times = grades[i] / 5;
    		int next = (times + 1) * 5;
    		if(abs(grades[i] - next) < 3){
    			result[br++] = next;
    		}
    		else{
    			result[br++] = grades[i];
    		}
    	}
    }

    *result_size = br;
    return result;
}

int main() {
    int n; 
    scanf("%d", &n);

    int *grades = malloc(sizeof(int) * n);
    
    for(int grades_i = 0; grades_i < n; grades_i++){
       scanf("%d", &grades[grades_i]);
    }

    int result_size;
    int* result = solve(n, grades, &result_size);

    for(int result_i = 0; result_i < result_size; result_i++) {
        if(result_i) {
            printf("\n");
        }
        printf("%d", result[result_i]);
    }

    puts("");
    
    return 0;
}
