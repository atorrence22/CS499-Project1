int knn (
    const double *train_inputs_ptr, //n oservations x n_features
    const double *train_label_ptr, //n_observations 
    const double *test_input_ptr, //n_features
    const int n_observations, const int n_features, const int max_neighbors, 
    double *test_predictions_ptr //max_neighbors
);
