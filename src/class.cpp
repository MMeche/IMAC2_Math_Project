#include <iostream>
#include <vector>
#include "class.hpp"

Conic::Conic(const std::vector<Eigen::Vector3d> &points){
    Eigen::MatrixXd A(5,6);
    for (int i = 0; i <4; i++){
        A(i,0)=points[i](0)*points[i](0);
        A(i,1)=points[i](0)*points[i](1);
        A(i,2)=points[i](1)*points[i](1);
        A(i,3)=points[i](0)*points[i](2);
        A(i,4)=points[i](1)*points[i](2);
        A(i,5)=points[i](2)*points[i](2);
    };
        
    Eigen :: JacobiSVD < Eigen :: MatrixXd > svd(A,
    Eigen :: ComputeThinU | Eigen :: ComputeFullV );
    Eigen :: VectorXd x = svd. matrixV (). rightCols (1);
    //x matrice des coefficients, x=conic_coef
}