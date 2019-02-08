//put this in src

#include "knn.h"
#include <Eigen/Dense> //matrix library, does dynamic memory allocation 
#include <iostream>

int Predict1toMaxNeighbors(double *train_inputs_ptr, double *train_label_ptr, 
                int nrow, int ncol, int max_neighbors_ptr, 
                double *test_input_ptr, //ncols
                //inputs above, outputs below
                double *test_prediction_ptr // max_neighbors
                )
{
    if(nrow < 1) {
        return ERROR_NO_TRAIN_DATA;
    }
    //COMPUTE VECTOR OF DISTANCES: 

    Eigen::VectorXd distance_vec(nrow)  //initializes vector
    Eigen::Map< Eigen::MatrixXd > train_inputs_mat(train_inputs_ptr, nrow, ncol); //eigen map - 
    Eigen::Map< Eigen::VectorXd > test_input_vec(test_input_ptr, ncol); //will let us access data..
    Eigen::VectorXd diff_vec(ncol);
    Eigen::VectorXi sorted_index_vec(nrow);


    //loop of data points to compute distance
    for(int i = 0; i < nrow; i++){
        
        diff_vec = train_inputs_mat.row(i).transpose() - test_input_vec; //vector of distances
            //transpose - takes row vector and will give back col vector (linear)
        distance(i) = diff_vec.norm(); 
        sorted_index_vec(i) = i; 
    }

    //std::cout << sorted_index_vec << std::endl << std::endl; 

    //std::sort => void sort( RandomIt first, RandomIt last, Compare comp );
    std::sort
        (sorted_index_vec.data(), //get vecotr of indices back 
        sorted_index_vec.data()+sorted_index_vec.size(), 
        [&distance_vec](int left, int right) {     //cpp lambda func?
            return distance_vec(left) < distance_vec(right)  //return whether or not left item < right item 
        }
        ); 
    //std::cout << sorted_index_vec << std::endl << std::endl; 

    //compute totalY
    int k; 
    double total_labels = 0.0; 
    for (k = 0; k < max_neighbors; k++) {
        int neighbors = k+1; 
        //i <- t_k
        int t = sorted_index_vec(k);
        //totalY += y_i
        total _labels += train_label_ptr[row];
        //totalY / kmax
        test_prediction_ptr[k] = total_labels/neighbors; 
    }

    return 0;
}



//do error checking in code
    //check for negative numbers