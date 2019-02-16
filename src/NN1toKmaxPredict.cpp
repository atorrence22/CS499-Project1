#include "NN1toKmaxPredict.h"
#include <Eigen/Dense> //matrix library, does dynamic memory allocation 
#include <iostream>

int NN1toKmaxPredict ( 
    const double *train_inputs_ptr, //n oservations x n_features
    const double *train_label_ptr, //n_observations 
    const double *test_input_ptr, //n_features
    const int n_observations, const int n_features, const int max_neighbors, 
    //inputs above, outputs below
    double *test_predictions_ptr //max_neighbors
){
  //ERROR STUFF HERE? 
  
  //////COMPUTE VECTOR OF DISTANCES: 
  
  int index;
  
  Eigen::Map< Eigen::MatrixXd > train_inputs_mat(
      (double*)train_inputs_ptr, n_observations, n_features);
  
  Eigen::Map< Eigen::VectorXd > test_input_vec(
      (double*)test_input_ptr, n_features);
  
  Eigen::VectorXd dist_vec(n_observations);
  
  Eigen::VectorXi sorted_index_vec(n_observations); 
  
  //loop of data points to compute distance
    //l1 manhattan distance
  for(index = 0; index < n_observations; index++){
    dist_vec(index) = (
      train_inputs_mat.row(index).transpose() - test_input_vec
    ).norm(); 
    sorted_index_vec(index) = index; 
  }
  std::sort(
    sorted_index_vec.data(), //get vector of indices back 
    sorted_index_vec.data() + sorted_index_vec.size(), 
    [&dist_vec](int left, int right) {
      return dist_vec(left) < dist_vec(right); 
      }
  );
  
  double total = 0.0;
  int k, neighbors, row_i; 
  for(k = 0; k < max_neighbors; k++){
    neighbors = k + 1; 
    //i <- t_k
    row_i = sorted_index_vec(k);
    //totalY += y_i
    total += train_label_ptr[row_i]; 
    //totalY / kmax
    test_predictions_ptr[k] = total / neighbors; 
  }
  
  return 0;
}
