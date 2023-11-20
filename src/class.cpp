#include <iostream>
#include <vector>
#include "class.hpp"
#include "Geogebra_conics.hpp"

Conic::Conic(const Points &points){
    //Eigen::MatrixXd A(5,6);
    
    //méthode moindre carrés
    std::vector<Eigen::Vector3d> x = points.getter();
    int nb_points = x.size();
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
    
    //exception
    //nombre points
    try{
        std::vector<double> points;

        //fonction entrée points
        double nb_points = points.size();

        if(nb_points != 5){
        //throw std::runtime_error("Le nombre de points entrés doit être égal à 5.");
        throw std::logic_error("Le nombre de points entrés doit être égal à 5.");////je ne sais pas laquelle il faut privilégier
        }
    }catch (const std::exception &e) {
        std::cout << e.what() << std::endl;
    }

    //points similaires
    try{
        std::vector<std::vector<double>> points;
        for (int i = 0; i < 5; ++i) {
            Eigen::Vector3d point;
            std::cout << "\nPoint " << i + 1 << " :\n";
            std::cout << "x : ";
            std::cin >> point(0); 
            std::cout << "y : " ;
            std::cin >> point(1);
            std::cout << "w : ";
            std::cin >> point(2);

            if (std::find(points.begin(), points.end(), point) != points.end()) {
                throw std::runtime_error("Au moins deux points ont les mêmes coordonnées. Saisissez des points uniques.");
            }
            //points.push_back(point);//je ne sais pas pourquoi ça ne marche pas
        }
    }catch (const std::exception &e) {
        std::cout << e.what() << std::endl;
    }
}


Conic::Conic(const Tangentes &tangents){
    std::vector<Eigen::Vector3d> l = tangents.getter();
    int nb_tangents = l.size();
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