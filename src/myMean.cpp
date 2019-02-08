#include "myMean.h"

/*
 * return int - status code. 
 */
int my_mean_C(int *data_ptr, int data_count, double *output_ptr) {
  double total = 0.0; 
  int data_i;
  if(data_count == 0) {
    return MY_MEAN_ERROR_NO_DATA;
  }
  
  for(data_i = 0; data_i < data_count; data_i++) {
    total += data_ptr[data_i]; 
  }
  
  *output_ptr = total/data_count; 
  
  return 0; 
}
  