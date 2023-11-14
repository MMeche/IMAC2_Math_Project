#include <iostream>
#include <vector>
#include "class.hpp"

Conic::Conic(const std::vector<Eigen::Vector3d> &points){
    Eigen::MatrixXd A(0,6);
    int n;
    for (int i = 0; i <4; i++){
        points[i](0)*points[i](0), points[i](0)*points[i](1), points[i](1)*points[i](1), points[i](0)*points[i](2), points[i](1)*points[i](2), points[i](2)*points[i](2);
    };
        
    Eigen :: JacobiSVD < Eigen :: MatrixXd > svd(A,
    Eigen :: ComputeThinU | Eigen :: ComputeFullV );
    Eigen :: VectorXd x = svd. matrixV (). rightCols (1);
}