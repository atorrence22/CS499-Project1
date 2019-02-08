
#ifndef KNN_H
#define KNN_H

//global constants
extern const int ERROR_NO_TRAIN_DATA; 


int knn (
    const double *train_inputs_ptr, //n oservations x n_features
    const double *train_label_ptr, //n_observations 
    int nrow, int ncol, int max_neighbors_ptr, 
    const double *test_input_ptr, //n_features
    const int n_observations, const int n_features, const int max_neighbors, 
    double *test_predictions_ptr //max_neighbors
);


#endif //KNN_H
