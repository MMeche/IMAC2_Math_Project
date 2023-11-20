#include <iostream>
#include <vector>
#include "class.hpp"
#include "Geogebra_conics.hpp"
#include "function.hpp"
//#include <Eigen/Dense>
#include "C:/Users/fox20/Downloads/eigen-3.4.0/eigen-3.4.0/Eigen/Dense"

std::vector<Eigen::Vector3d> input_points(){
    Viewer_conic viewer;
    std::vector<Eigen::Vector3d> points;
    std::cout << "Entrer les coordonnées de cinq points :\n";
    for (int i = 0; i < 5; ++i){
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

std::vector<Eigen::Vector3d> input_tangents(){
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
    return tangents;
}