NNLearnCV <- function(X.mat, y.vec, max.neighbors = 30L, fold.vec = NULL, n.folds = 5L){
  
  if (!all(is.matrix(X.mat), is.numeric(X.mat))) {
    stop("X.mat is not numeric")
  }
  
  if (!all(is.vector(y.vec), is.numeric(y.vec), length(y.vec) == nrow(X.mat))) {
    stop("y.vec is not a numeric vector or its length is not equal to nrow(X.mat)")
  }
  print(typeof(max.neighbors))
  if (!all(is.integer(max.neighbors), length(max.neighbors) == 1)) {
    stop("max.neighbors is not an integer")
  }
  
  if (!is.null(fold.vec) && !all(is.vector(fold.vec), is.numeric(fold.vec), length(fold.vec) == length(y.vec))) {
    stop("fold.vec is not a numberic vector or its length is not equal to length(y.vec)")
  }
  
  if (!all(is.integer(n.folds), length(n.folds) == 1)) {
    stop("n.folds is not an integer")
  }
  
  # initialize a fold sequence if fold.vec is null
  if (is.null(fold.vec)) {
    fold.vec <- sample(rep(1:n.folds, l = nrow(X.mat)))
  }
  
  label.is.binary = (y.vec == 0) || (y.vec == 1)
  for (test_fold in seq_len(n.folds)) {
    for (prediction.set.name in c("train", "validation")) {
      if (prediction.set.name == "train") {
        train.index <- which(fold.vec != test_fold)
        validation.index = which(fold.vec != test_fold)
      } 
      if (prediction.set.name == "validation") {
        train.index <- which(fold.vec != test_fold)
        validation.index = which(fold.vec == test_fold)
      } 
      
      CV.result <- matrix(knn(X.mat[train.index,], y.vec[train.index], X.mat[validation.index, ], max.neighbors), ncol = max.neighbors)
      
      loss.mat <- if (label.is.binary) {
        ifelse(CV.result > 0.5, 1, 0) != y.vec[validation.index]
      } else{
        (CV.result - y.vec[validation.index]) ^ 2
      }
      
      if (prediction.set.name == "train") {
        train.loss.mat[, test_fold] <- colMeans(loss.mat)
      } 
      if (prediction.set.name == "validation") {
        validation.loss.mat[, test_fold] <- colMeans(loss.mat)
      }
    }
  }
  
  print(rowMeans(train.loss.mat))
  print(rowMeans(validation.loss.mat))
  print(which.min(validation.loss.vec))
  
}

