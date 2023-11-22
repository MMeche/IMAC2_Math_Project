#include <iostream>
#include <vector>
#include "class.hpp"
#include "Geogebra_conics.hpp"
#include "function.hpp"
#include <Eigen/Dense>
//#include "C:/Users/fox20/Downloads/eigen-3.4.0/eigen-3.4.0/Eigen/Dense"

//Interface utilisateur pour rentrer un set de points.
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

//Retourne des set de points prédéfinis. Leur coniques sont respectivement : un cercle, une parabole, une hyperbole et une ellipse.
std::vector<Eigen::Vector3d> load_points(Viewer_conic &viewer,const std::string &ui){
    std::vector<Eigen::Vector3d> points;
    if(ui=="c"){
        //conique cercle
        Eigen::VectorXd pt1(3), pt2(3), pt3(3), pt4(3), pt5(3);
        pt1 << 0.0, 2.0, 1.0;
        pt2 << 2.0, 0.0, 1.0;
        pt3 << -2.0, 0.0, 1.0;
        pt4 << 0.0, -2.0, 1.0;
        pt5 << sqrt(2), sqrt(2), 1.0;
        points.push_back(pt1);
        points.push_back(pt2);
        points.push_back(pt3);
        points.push_back(pt4);
        points.push_back(pt5);
        viewer.push_point(pt1, "p1", 200,0,0);
        viewer.push_point(pt2, "p2", 200,0,0);
        viewer.push_point(pt3, "p3", 200,0,0);
        viewer.push_point(pt4, "p4", 200,0,0);
        viewer.push_point(pt5, "p5", 200,0,0);
    }
    if(ui=="p"){
        //conique parabole
        Eigen::VectorXd pt1(3), pt2(3), pt3(3), pt4(3), pt5(3);
        pt1 << 0.0, 2.0, 1.0;
        pt2 << 2.0, 0.0, 0.0;
        pt3 << -2.0, 0.0, 0.0;
        pt4 << 0.0, -2.0, 1.0;
        pt5 << sqrt(2), sqrt(2), 1.0;
        points.push_back(pt1);
        points.push_back(pt2);
        points.push_back(pt3);
        points.push_back(pt4);
        points.push_back(pt5);
        viewer.push_point(pt1, "p1", 200,0,0);
        viewer.push_point(pt2, "p2", 200,0,0);
        viewer.push_point(pt3, "p3", 200,0,0);
        viewer.push_point(pt4, "p4", 200,0,0);
        viewer.push_point(pt5, "p5", 200,0,0);
    }
    if(ui=="h"){
        //conique hyperbole
        Eigen::VectorXd pt1(3), pt2(3), pt3(3), pt4(3), pt5(3);
        pt1 << 4.0, 5.0, 1.0;
        pt2 << 7.0, 3.0, 1.0;
        pt3 << 6.0, 4.0, 1.0;
        pt4 << 1.0, 6.0, 1.0;
        pt5 << 9.0, 5.0, 1.0;
        points.push_back(pt1);
        points.push_back(pt2);
        points.push_back(pt3);
        points.push_back(pt4);
        points.push_back(pt5);        
        viewer.push_point(pt1, "p1", 200,0,0);
        viewer.push_point(pt2, "p2", 200,0,0);
        viewer.push_point(pt3, "p3", 200,0,0);
        viewer.push_point(pt4, "p4", 200,0,0);
        viewer.push_point(pt5, "p5", 200,0,0);
    }
    if(ui=="e"){
        //conique ellipse
        Eigen::VectorXd pt1(3), pt2(3), pt3(3), pt4(3), pt5(3);
        pt1 <<  1.5,  2.0, 1.0;
        pt2 <<  3.0,  1.0, 1.0;
        pt3 << -2.0, -1.0, 1.0;
        pt4 <<  0.5, -2.0, 1.0;
        pt5 << -1.0,  3.0, 1.0;
        points.push_back(pt1);
        points.push_back(pt2);
        points.push_back(pt3);
        points.push_back(pt4);
        points.push_back(pt5);         
        viewer.push_point(pt1, "p1", 200,0,0);
        viewer.push_point(pt2, "p2", 200,0,0);
        viewer.push_point(pt3, "p3", 200,0,0);
        viewer.push_point(pt4, "p4", 200,0,0);
        viewer.push_point(pt5, "p5", 200,0,0);
    }
    return points;
}

//Prend en entrée les paramètres des tangentes pour ajouter au viewer les droites correspondantes.
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

//Interface utilisateur pour rentrer un set de tangentes.
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

//Retourne un set de tangentes prédéfini.
std::vector<Eigen::Vector3d> load_tangents(Viewer_conic &viewer){
    std::vector<Eigen::Vector3d> tangents;
    Eigen::VectorXd t1(3), t2(3), t3(3), t4(3), t5(3);
    t1<< 2.0, -3.0, 4.0;
    t2<< 5.0, 2.0, -8.0;
    t3<< 1.0, 2.0, -2.0;
    t4<< 3.0, -4.0, 7.0;
    t5<< 2.0, 2.0, -5.0;
    tangents.push_back(t1);
    tangents.push_back(t2);
    tangents.push_back(t3);
    tangents.push_back(t4);
    tangents.push_back(t5);
    add_lines(tangents,viewer);
    return tangents;
}
