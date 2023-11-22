#include <iostream>
#include <vector>
#include "class.hpp"
#include "Geogebra_conics.hpp"

//fonction pour gérer les possibles erreurs de dimension (n<5)
template<typename T>
void handle_exceptions(const T &t){
    std::vector<Eigen::Vector3d> x = t.getter();
    int nb_elmts = x.size();
    if(nb_elmts < 5){
        throw std::logic_error("\nUne conique necessite au moins 5 points/tangentes.\n le système est sous-dimensionne");
    }
    for(int i = 0 ; i < nb_elmts ; i++){
        Eigen::Vector3d p = x[i];
        if((std::find(x.begin(),x.begin()+i,p)!= x.begin()+i) | (std::find(x.begin()+i+1,x.end(),p)!= x.end())){
            throw std::logic_error("\nAu moins deux points/tangentes ont les mêmes coordonnées.\n Saisissez des points/tangentes uniques.\nLe systeme est sous-dimensionne\nLa conique ne sera pas tracee.");
        }
    }
}

//Constructeur à partir d'un set de Points
Conic::Conic(const Points &points){
    std::vector<Eigen::Vector3d> x = points.getter();
    int nb_points = x.size();
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
    //Méthode des moindres carrés
    Eigen :: JacobiSVD < Eigen :: MatrixXd > svd(A, Eigen :: ComputeThinU | Eigen :: ComputeFullV );
    change_coef(svd. matrixV (). rightCols (1));
}

//Constructeur à partir d'un set de tangentes
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
    //Idem, méthode des moindres carrés mais pour trouver l'inverse de C, cette fois-ci.
    Eigen :: JacobiSVD < Eigen :: MatrixXd >svd(A, Eigen :: ComputeThinU | Eigen :: ComputeFullV);
    Eigen::VectorXd inverse_coef = svd. matrixV (). rightCols (1);
    Eigen::Matrix3d inverse_C;
    inverse_C << inverse_coef(0) , inverse_coef(1) , inverse_coef(2),
                 inverse_coef(1) , inverse_coef(3) , inverse_coef(4),
                 inverse_coef(2) , inverse_coef(4) , inverse_coef(5);
    //Il faut donc inverser la matrice.
    conic_matrix = inverse_C.inverse();
    Eigen::VectorXd tmp(6);
    tmp << conic_matrix(0,0) , 2*conic_matrix(0,1) , conic_matrix(1,1) , 2*conic_matrix(0,2) , 2*conic_matrix(1,2) , conic_matrix(2,2);
    conic_coef = tmp;
}

//Simple Getter
Eigen::Matrix3d Conic::matrix() const {
    return conic_matrix;
}

//Simple Getter
Eigen::VectorXd Conic::coef() const {
    return conic_coef;
}

//Update de la Matrice C et des coefficients qui lui sont liés
void Conic::change_matrix(const Eigen::Matrix3d &m){
    conic_matrix = m;
    Eigen::VectorXd tmp(6);
    tmp[0] = conic_matrix(0,0);
    tmp[1] = 2*conic_matrix(0,1);
    tmp[2] = conic_matrix(1,1);
    tmp[3] = conic_matrix(0,2);
    tmp[4] = 2*conic_matrix(1,2);
    tmp[5] = conic_matrix(2,2);
    conic_coef = tmp;
}

//Update des coefficients de la conique et de la Matrice C qui leur est liée
void Conic::change_coef(const Eigen::VectorXd &c){
    conic_coef = c;
    Eigen::Matrix3d tmp;
    tmp<< conic_coef[0],conic_coef[1]/2,conic_coef[3]/2,
        conic_coef[1]/2,conic_coef[2], conic_coef[4]/2,
        conic_coef[3]/2,conic_coef[4]/2,conic_coef[5];
    conic_matrix = tmp;
}

//Calcul de la norme de vecteur des coefficients
double Conic::norm(){
    return sqrt(pow(conic_coef[0],2)+pow(conic_coef[1],2)+pow(conic_coef[2],2)+pow(conic_coef[3],2)+pow(conic_coef[4],2)+pow(conic_coef[5],2));
}
