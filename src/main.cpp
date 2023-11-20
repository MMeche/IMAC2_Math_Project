#include <iostream>
#include <vector>

#include <Eigen/Dense>
//#include "C:/Users/fox20/Downloads/eigen-3.4.0/eigen-3.4.0/Eigen/Dense"

#include "Geogebra_conics.hpp"
#include "class.hpp"
#include "function.hpp"


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

  /*// draw points anciennement le template du prof
  Eigen::VectorXd pt1(3), pt2(3), pt3(3), pt4(3), pt5(3);
  pt1 <<  1.5,  2.0, 1.0;
  pt2 <<  3.0,  1.0, 1.0;
  pt3 << -2.0, -1.0, 1.0;
  pt4 <<  0.5, -2.0, 1.0;
  pt5 << -1.0,  3.0, 1.0;

  viewer.push_point(pt1, "p1", 200,0,0);
  viewer.push_point(pt2, "p2", 200,0,0);
  viewer.push_point(pt3, "p3", 200,0,0);
  viewer.push_point(pt4, "p4", 200,0,0);
  viewer.push_point(pt5, "p5", 200,0,0);*/ 

  //points
  std::vector<Eigen::Vector3d> points = input_points(viewer);
  Points P;
  P.setter(points);

  //tangentes
  std::vector<Eigen::Vector3d> tangents = input_tangents(viewer);
  Tangentes T;
  T.setter(tangents);

  /*// draw line anciennement le template du prof
  viewer.push_line(pt1, pt2-pt1,  200,200,0);*/

  // conic object
  try{
    Conic conic(P);
    //vecteur qui contient (a, b, c, d, e, f)
    Eigen::VectorXd coef = conic.coef();
    viewer.push_conic(coef,"", 0,0,200);
    //conic.display();
  }
  catch(const std::exception &e){
    std::cerr<< e.what() <<"\n";
  }
 


  Conic conic2(T);
  //conic2.display();

  Eigen::VectorXd coef = conic2.coef();
  viewer.push_conic(coef,"",0,0,200);


  //pour ajouter points dans Conic
  //Conic Conic(points);

  // render
  //viewer.display(); // on terminal
  viewer.render("output.html");  // generate the output file (to open with your web browser)

  return 0;
}

