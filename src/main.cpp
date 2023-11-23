#include <iostream>
#include <vector>

#include <Eigen/Dense>
//#include "C:/Users/fox20/Downloads/eigen-3.4.0/eigen-3.4.0/Eigen/Dense"

#include "Geogebra_conics.hpp"
#include "class.hpp"
#include "function.hpp"


int main()
{
  Viewer_conic viewer;

  // viewer options
  viewer.set_background_color(250, 250, 255);
  viewer.show_axis(true);
  viewer.show_grid(false);
  viewer.show_value(false);
  viewer.show_label(true);

  std::string ui;
  std::cout<<"Création par points, par tangentes ou faisceaux? (p/t/f)\n";
  std::cin>>ui;
  while((ui!="p")&(ui!="t")&(ui!="f")){
    std::cerr<<"Entree invalide. Recommencez\n";
    std::cin>>ui;
  }
  if(ui=="p"){
    //Entree de Points
    std::vector<Eigen::Vector3d> points;
    //Soit on créé notre propre set de point soit on prend ceux donnés par le programme
    std::cout<<"Voulez vous creer votre propre conique ? (o/n)\n";
    std::cin>>ui;
    while((ui!="o")&(ui!="n")){
      std::cerr<<"Entree invalide. Recommencez\n";
      std::cin>>ui;
    }
    if(ui=="o"){
      points = input_points(viewer);
    }
    if(ui=="n"){
      std::cout<<"Que voulez-vous ?\nUn cercle (c)\nUne parabole (p)\nUne hyperbole (h)\nUne ellipse (e)\n";
      std::cin>>ui;
      points = load_points(viewer,ui);
      ui="n";
    }
    Points P;
    P.setter(points);
    //Creation de la Conique, possibles erreurs de dimensions
    try{
      Conic conic(P);
      //vecteur qui contient (a, b, c, d, e, f)
      Eigen::VectorXd coef = conic.coef();
      std::cout<<coef<<std::endl;
      viewer.push_conic(coef,"", 0,0,200);
    }
    catch(const std::exception &e){
      std::cerr<< e.what() <<"\n";
    }
  }
  if(ui=="t"){
    //Entree de Tangentes
    std::vector<Eigen::Vector3d> tangents;
    //Soit on créer notre propre set de tangentes soit on prend celui donné par le programme
    std::cout<<"Voulez vous creer votre propre conique ? (o/n)\n";
    std::cin>>ui;
    while((ui!="o")&(ui!="n")){
      std::cerr<<"Entree invalide. Recommencez\n";
      std::cin>>ui;
    }
    if(ui=="o"){
      tangents = input_tangents(viewer);
    }
    else{
      tangents = load_tangents(viewer);
    }
    Tangentes T;
    T.setter(tangents);
    //Creation de la Conique, possibles erreurs de dimensions
    try{
      Conic conic2(T);
      Eigen::VectorXd coef = conic2.coef();
      viewer.push_conic(coef,"",0,0,200);
    }
    catch(const std::exception &e){
      std::cerr<<e.what() <<"\n";
    }
  }
  if(ui=="f"){
    //On cree des listes de points et on en fait des coniques.
    Points P;
    P.setter(load_points(viewer,"c"));
    Conic conicA(P);
    P.setter(load_points(viewer,"e"));
    Conic conicB(P);

    //On normalise les coniques.
    conicA.change_coef((1/conicA.norm())*conicA.coef());
    conicB.change_coef((1/conicB.norm())*conicB.coef());

    //On les affiche.
    viewer.push_conic(conicA.coef(),"",0,0,200);
    viewer.push_conic(conicB.coef(),"",0,200,0);
    
    for(int i = 0 ; i<15;i++){
      Conic somme;
      somme.change_matrix(cos(i*M_PI/14)*conicA.matrix()+sin(i*M_PI/14)*conicB.matrix());
      somme.change_coef((1/somme.norm())*somme.coef());
      viewer.push_conic(somme.coef(),"",200,0,0);
    }
  }

  // render
  viewer.render("output.html");  // generate the output file (to open with your web browser)

  return 0;
}

