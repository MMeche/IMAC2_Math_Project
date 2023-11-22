#include <iostream>
#include <vector>
#include "class.hpp"
#include "Geogebra_conics.hpp"
#include "function.hpp"
#include <Eigen/Dense>
//#include "C:/Users/fox20/Downloads/eigen-3.4.0/eigen-3.4.0/Eigen/Dense"

std::vector<Eigen::Vector3d> input_points(Viewer_conic &viewer){
    std::vector<Eigen::Vector3d> points;
    int nb_points;
    std::cout<< "Entrer le nombre de point que vous voulez pour définir la conique :\n";
    std::cin>>nb_points;
    std::cout << "Entrer les coordonnées de(s) "<<nb_points<<  " point(s) :\n";
    for (int i = 0; i < nb_points; ++i){
      Eigen::Vector3d point;
      std::cout << "\nPoint " << i + 1 << " :\n";
      std::cout << "x : ";
      std::cin >> point(0);
      std::cout << "y : ";
      std::cin >> point(1);
      std::cout << "w : ";
      std::cin >> point(2);
      points.push_back(point);
      viewer.push_point(point,"" ,200,0,0);
    };
    return points;
}
void add_lines(const std::vector<Eigen::Vector3d> &tangents , Viewer_conic &viewer){
    int nb_lines = tangents.size();
    Eigen::Vector3d pt1,pt2;
    for(int i= 0;i<nb_lines;i++){
        if(tangents[i](0) != 0){
            pt1 << -(tangents[i](1)+tangents[i](2))/tangents[i](0) , 1 , 1;
            pt2 << -(2*tangents[i](1)+tangents[i](2))/tangents[i](0) , 2 , 1;
        }else
            if(tangents[i](1) != 0){
                pt1 << 1 , -(tangents[i](2)/tangents[i](1)) , 1;
                pt2 << 1 , -2*(tangents[i](2)/tangents[i](1)) , 2;
            }
            else
                if(tangents[i](2) != 0){
                    pt1 << 1 , 1 , 0;
                    pt2 << 1 , 2 , 0;
                }
                else throw std::logic_error("Tangente nulle detectee");
        viewer.push_line(pt1,pt2-pt1,200,200,0);
    }
}

std::vector<Eigen::Vector3d> input_tangents(Viewer_conic &viewer){
    std::vector<Eigen::Vector3d> tangents;
    std::cout << "Entrer les équations de tangentes pour cinq points :\n";
    for (int i = 0; i < 5; ++i) {
        Eigen::Vector3d tangent;
        std::cout << "\nTangente " << i + 1 << " :\n";
        std::cout << "tx : ";
        std::cin >> tangent(0);
        std::cout << "ty : ";
        std::cin >> tangent(1);
        std::cout << "tw : ";
        std::cin >> tangent(2);
        tangents.push_back(tangent);
    };
    add_lines(tangents,viewer);
    return tangents;
}

Eigen::VectorXd moindre_carres(const Eigen::MatrixXd &A){
    std::cout<<A<<"\n";
    Eigen :: JacobiSVD < Eigen :: MatrixXd > svd(A, Eigen :: ComputeThinU | Eigen :: ComputeFullV );
    std::cout<<svd. matrixV (). rightCols (1);
    return svd. matrixV (). rightCols (1);
};

/*    Eigen::VectorXd conic_coef(6);
    conic_coef <<10,10,10,10,10,10;
    for(int i = 0 ; i<6 ; i++){
        Eigen::MatrixXd diminued_A(A.rows(),5);
        diminued_A.leftCols(i)=A.leftCols(i);
        diminued_A.rightCols(5-i)=A.rightCols(5-i);
        Eigen::VectorXd tmp = diminued_A.colPivHouseholderQr().solve(-1*A.col(i));
        Eigen::VectorXd sol(6);
        sol[i]=1;
        sol.head(i) = tmp.head(i);
        sol.tail(5-i) = tmp.tail(5-i);
        std::cout<<(A*conic_coef).norm()<<"\n\n";
        if((A*sol).norm()<(A*conic_coef).norm()){
            conic_coef = sol;
        }

        std::cout<<conic_coef<<"\n\n";
        
    }
    std::cout<<conic_coef;*/