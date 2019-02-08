#include "knn.h"
#include <Eigen/Dense> //matrix library, does dynamic memory allocation 
#include <iostream>

int knn (
    const double *train_inputs_ptr, //n oservations x n_features
    const double *train_label_ptr, //n_observations 
    const double *test_input_ptr, //n_features
    const int n_observations, const int n_features, const int max_neighbors, 
    //inputs above, outputs below
    double *test_predictions_ptr //max_neighbors
){
  Eigen::Map< Eigen::MatrixXd > train_inputs_mat(
      (double*)train_inputs_ptr, n_observations, n_features);
  
  Eigen::Map< Eigen::VectorXd > test_input_vec(
      (double*)test_input_ptr, n_features);
  
  Eigen::VectorXd dist_vec(n_observations);
  
  Eigen::VectorXi sorted_index_vec(n_observations); 
  
  for(int i=0; i<n_observations; i++){
    dist_vec(i) = (
      train_inputs_mat.row(i).transpose() - test_input_vec
    ).norm(); 
    sorted_index_vec(i) = i; 
  }
  std::sort(
    sorted_index_vec.data(), 
    sorted_index_vec.data()+sorted_index_vec.size(), 
    [& dist_vec](int left, int right){
      return dist_vec(left) < dist_vec(right); 
    }
  ); 
  double total = 0.0;
  int model_i, neighbors, row_i; 
  for(model_i = 0; model_i< max_neighbors; model_i++){
    neighbors = model_i + 1; 
    row_i = sorted_index_vec(model_i);
    total += train_label_ptr[row_i]; 
    test_predictions_ptr[model_i] = total / neighbors; 
  }
  return 0;
}