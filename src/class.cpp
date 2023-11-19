#include <iostream>
#include <vector>
#include "class.hpp"
#include "Geogebra_conics.hpp"

Conic::Conic(const std::vector<Eigen::Vector3d> &points){
    //Eigen::MatrixXd A(5,6);
    //méthode moindre carrés
    int nb_points = points.size();
    Eigen::MatrixXd A(nb_points, 6);
    for (int i = 0; i <nb_points; i++){
        A(i,0)=points[i](0)*points[i](0);
        A(i,1)=points[i](0)*points[i](1);
        A(i,2)=points[i](1)*points[i](1);
        A(i,3)=points[i](0)*points[i](2);
        A(i,4)=points[i](1)*points[i](2);
        A(i,5)=points[i](2)*points[i](2);
    };
        
    Eigen :: JacobiSVD < Eigen :: MatrixXd > svd(A, 
        Eigen :: ComputeThinU | Eigen :: ComputeFullV );
    conic_coef = svd. matrixV (). rightCols (1);

    // calculer la matrice conique avec conic_coef
    conic_matrix << conic_coef(0), conic_coef(1) / 2, conic_coef(3) / 2,
                   conic_coef(1) / 2, conic_coef(2), conic_coef(4) / 2,
                   conic_coef(3) / 2, conic_coef(4) / 2, conic_coef(5);
}

Eigen::Matrix3d Conic::matrix() const {
    return conic_matrix;
}

Eigen::VectorXd Conic::coef() const {
    return conic_coef;
}

void Conic::display() const {
    std::cout<<"Coefficients : \n"<<conic_coef;
    std::cout<<"\nMatrice associee : \n"<<conic_matrix<<std::endl; 
}

void Conic::tangent(const std::vector<Eigen::Vector2d> &tangents) {
    int nb_points = tangents.size();
    Eigen::MatrixXd T(nb_points, 6);

    for (int i = 0; i < nb_points; i++) {
        // T(i, 0) = 0;
        // T(i, 1) = 0;
        // T(i, 2) = 1;
        T(i, 0) = tangents[i](0);//remplit 4ème colonne avec tangents(x)
        T(i, 1) = tangents[i](1);//remplit 5ème colonne avec tangents(y)
        T(i, 2) = tangents[i](0) * tangents[i](0) + tangents[i](1) * tangents[i](1);//somme des carrés, pour que tangents orthogonal
    }
    Eigen :: JacobiSVD < Eigen :: MatrixXd > svd(T, Eigen :: ComputeThinU | Eigen :: ComputeFullV );
    conic_coef = svd.matrixV().rightCols (1);

    // calculer la matrice conique avec conic_coef
    conic_matrix << conic_coef(0), conic_coef(1) / 2, conic_coef(3) / 2,
                   conic_coef(1) / 2, conic_coef(2), conic_coef(4) / 2,
                   conic_coef(3) / 2, conic_coef(4) / 2, conic_coef(5);
}