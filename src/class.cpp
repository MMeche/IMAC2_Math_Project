#include <iostream>
#include <vector>
#include "class.hpp"

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