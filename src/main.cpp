#include <iostream>
#include <vector>

//#include <Eigen/Dense>
#include "C:/Users/fox20/Downloads/eigen-3.4.0/eigen-3.4.0/Eigen/Dense"

#include "Geogebra_conics.hpp"
#include "class.hpp"



int main()
{
  // the viewer will open a file whose path is writen in hard (bad!!). 
  // So you should either launch your program from the fine directory or change the path to this file.
  Viewer_conic viewer;

  // viewer options
  viewer.set_background_color(250, 250, 255);
  viewer.show_axis(true);
  viewer.show_grid(false);
  viewer.show_value(false);
  viewer.show_label(true);

  // draw points
  Eigen::VectorXd pt1(2), pt2(2), pt3(2), pt4(2), pt5(2);
  pt1 <<  1.5,  2.0;
  pt2 <<  3.0,  1.0;
  pt3 << -2.0, -1.0;
  pt4 <<  0.5, -2.0;
  pt5 << -1.0,  3.0;

  viewer.push_point(pt1, "p1", 200,0,0);
  viewer.push_point(pt2, "p2", 200,0,0);
  viewer.push_point(pt3, "p3", 200,0,0);
  viewer.push_point(pt4, "p4", 200,0,0);
  viewer.push_point(pt5, "p5", 200,0,0);

  // draw line
  viewer.push_line(pt1, pt2-pt1,  200,200,0);

  // draw conic
  Eigen::VectorXd conic(6);
  conic << -1.4, -0.3, -1, -0.6, 0.0, 0.8; //vecteur qui contient (a, b, c, d, e, f)
  viewer.push_conic(conic, 0,0,200);

  //draw points
  std::vector<Eigen::Vector3d> points;
  points.push_back(Eigen::Vector3d(pt1(0), pt1(1), 1.0));
  points.push_back(Eigen::Vector3d(pt2(0), pt2(1), 1.0));
  points.push_back(Eigen::Vector3d(pt3(0), pt3(1), 1.0));
  points.push_back(Eigen::Vector3d(pt4(0), pt4(1), 1.0));
  points.push_back(Eigen::Vector3d(pt5(0), pt5(1), 1.0));

  // matrice
  // Eigen::MatrixXd matrice_c(3);
  // matrice_c << ; //vecteur qui contient (a, b, c, d, e, f)
  // viewer.push_conic(conic, 0,0,200);


    // Entrer les coordonnées des cinq points
    std::cout << "Entrer les coordonnées des cinq points :\n";
    for (int i = 0; i < 5; ++i) {
        Eigen::Vector3d point;
        std::cout << "Point " << i + 1 << " : ";
        std::cin >> point(0) >> point(1) ; //normalement c'est 2 coordonnées qu'on demande non ?
        points.push_back(point);
    }
    //pour ajouter points dans Conic
    //Conic Conic(points);

  // render
  viewer.display(); // on terminal
  viewer.render("output.html");  // generate the output file (to open with your web browser)

  return 0;
}

