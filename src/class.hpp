#pragma once
#include <string>
#include <vector>
#include "class.hpp"
//#include <Eigen/Dense>
#include "C:/Users/fox20/Downloads/eigen-3.4.0/eigen-3.4.0/Eigen/Dense"

class Conic
{
    private : 
    Eigen::VectorXd conic_coef;

    bool sizeTest(){return conic_coef.size()==6;};
    
    public :
    //Constructor
    Conic() = default;
    //From a pre-existing list of conic coefficients
    Conic(const Eigen::VectorXd &coef) : conic_coef(coef){};
    //From a set of points
    Conic(const std::vector<Eigen::Vector2d> points);
    
    //Destructor
    ~Conic() = default;
};

