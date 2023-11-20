#include <iostream>
#include <vector>
#include "class.hpp"
#include "Geogebra_conics.hpp"

template<typename T>
void handle_exceptions(const T &t){
    std::vector<Eigen::Vector3d> x = t.getter();
    int nb_elmts = x.size();
    if(nb_elmts < 5){
        throw std::logic_error("\nUne conique necessite au moins 5 points/tangentes, le système est sous-dimensionne");
    }
    for(int i = 0 ; i < nb_elmts ; i++){
        Eigen::Vector3d p = x[i];
        if((std::find(x.begin(),x.begin()+i,p)!= x.begin()+i) | (std::find(x.begin()+i+1,x.end(),p)!= x.end())){
            throw std::logic_error("\nAu moins deux points/tangentes ont les mêmes coordonnées.\n Saisissez des points/tangentes uniques.\nLe systeme est sous-dimensionne\nLa conique ne sera pas tracee.");
        }
    }
}

Conic::Conic(const Points &points){
    //Eigen::MatrixXd A(5,6);
    
    //méthode moindre carrés
    std::vector<Eigen::Vector3d> x = points.getter();
    int nb_points = x.size();
    //Exception
    handle_exceptions(points);
    Eigen::MatrixXd A(nb_points, 6);
    for (int i = 0; i <nb_points; i++){
        A(i,0)=x[i](0)*x[i](0);
        A(i,1)=x[i](0)*x[i](1);
        A(i,2)=x[i](1)*x[i](1);
        A(i,3)=x[i](0)*x[i](2);
        A(i,4)=x[i](1)*x[i](2);
        A(i,5)=x[i](2)*x[i](2);
    };
        
    Eigen :: JacobiSVD < Eigen :: MatrixXd > svd(A, Eigen :: ComputeThinU | Eigen :: ComputeFullV );
    conic_coef = svd. matrixV (). rightCols (1);

    // calculer la matrice conique avec conic_coef
    conic_matrix << conic_coef(0), conic_coef(1) / 2, conic_coef(3) / 2,
                   conic_coef(1) / 2, conic_coef(2), conic_coef(4) / 2,
                   conic_coef(3) / 2, conic_coef(4) / 2, conic_coef(5);
}


Conic::Conic(const Tangentes &tangents){
    std::vector<Eigen::Vector3d> l = tangents.getter();
    int nb_tangents = l.size();
    handle_exceptions(tangents);
    Eigen::MatrixXd A(nb_tangents, 6);
    for(int i = 0; i<nb_tangents; i++){
        A(i,0)=l[i](0)*l[i](0);
        A(i,1)=2*l[i](0)*l[i](1);
        A(i,2)=2*l[i](0)*l[i](2);
        A(i,3)=l[i](1)*l[i](1);
        A(i,4)=2*l[i](1)*l[i](2);
        A(i,5)=l[i](2)*l[i](2);        
    }
    Eigen :: JacobiSVD < Eigen :: MatrixXd >svd(A, Eigen :: ComputeThinU | Eigen :: ComputeFullV);
    Eigen::VectorXd inverse_coef = svd. matrixV (). rightCols (1);
    Eigen::Matrix3d inverse_C;
    inverse_C << inverse_coef(0) , inverse_coef(1) , inverse_coef(2),
                 inverse_coef(1) , inverse_coef(3) , inverse_coef(4),
                 inverse_coef(2) , inverse_coef(4) , inverse_coef(5);
    
    conic_matrix = inverse_C.inverse();
    Eigen::VectorXd tmp(6);
    tmp << conic_matrix(0,0) , 2*conic_matrix(0,1) , conic_matrix(1,1) , 2*conic_matrix(0,2) , 2*conic_matrix(1,2) , conic_matrix(2,2);
    conic_coef = tmp;
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

void Conic::tangent(const std::vector<Eigen::Vector3d> &tangents) {
    int nb_points = tangents.size();
    Eigen::MatrixXd T(nb_points, 6);

    for (int i = 0; i < nb_points; i++) {
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