#include <iostream>
#include <vector>
#include "class.hpp"
#include "Geogebra_conics.hpp"

Conic::Conic(const std::vector<Eigen::Vector3d> &points){
    Eigen::MatrixXd A(5,6);
    for (int i = 0; i <5; i++){
        A(i,0)=points[i](0)*points[i](0);
        A(i,1)=points[i](0)*points[i](1);
        A(i,2)=points[i](1)*points[i](1);
        A(i,3)=points[i](0)*points[i](2);
        A(i,4)=points[i](1)*points[i](2);
        A(i,5)=points[i](2)*points[i](2);
    };
        
    Eigen :: JacobiSVD < Eigen :: MatrixXd > svd(A,
    Eigen :: ComputeThinU | Eigen :: ComputeFullV );
    //Eigen :: VectorXd x = svd. matrixV (). rightCols (1);
    //x matrice des coefficients, x=conic_coef

    //j'ai changé le nom pour que ce soit plus compréhensible
    Eigen :: VectorXd conic_coef = svd. matrixV (). rightCols (1);

    // calculer la matrice conique avec conic_coef
    conic_matrix << conic_coef(0), conic_coef(1) / 2, conic_coef(3) / 2,
                   conic_coef(1) / 2, conic_coef(2), conic_coef(4) / 2,
                   conic_coef(3) / 2, conic_coef(4) / 2, conic_coef(5);

    //affiche conic_coef
    std::cout << "Coefficients Conic : " << conic_coef.transpose() << std::endl;

    //dessine la conique avec conic_coef
    //viewer.push_conic(conic_coef, 0, 0, 200);

}

Eigen::Matrix3d Conic::get_conic_matrix() const {
    return conic_matrix;
}