#include <iostream>
#include <vector>
#include "class.hpp"
#include "Geogebra_conics.hpp"
#include "function.hpp"
#include <Eigen/Dense>
//#include "C:/Users/fox20/Downloads/eigen-3.4.0/eigen-3.4.0/Eigen/Dense"

std::vector<Eigen::Vector3d> input_points(Viewer_conic &viewer){
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

