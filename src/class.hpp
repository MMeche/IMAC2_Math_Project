#pragma once
#include <string>
#include <vector>
#include "class.hpp"
#include <Eigen/Dense>
//#include "C:/Users/fox20/Downloads/eigen-3.4.0/eigen-3.4.0/Eigen/Dense"

//Container de points
class Points
{
    private:
    std::vector<Eigen::Vector3d> _points;
    
    public:
    Points()=default;
    inline std::vector<Eigen::Vector3d> getter()const{return _points;};
    inline void setter(const std::vector<Eigen::Vector3d> &points){_points=points;};
};
//Container de tangentes
class Tangentes
{
    private:
    std::vector<Eigen::Vector3d> _tangentes;
    
    public:
    Tangentes()=default;
    inline std::vector<Eigen::Vector3d> getter()const{return _tangentes;};
    inline void setter(const std::vector<Eigen::Vector3d> &tangentes){_tangentes=tangentes;};
};

class Conic
{
    private : 
    Eigen::VectorXd conic_coef; //a,b,c,d,e,f
    Eigen::Matrix3d conic_matrix; //matrix C

    bool sizeTest(){return conic_coef.size()==6;};
    
    public :
    //Constructor
    Conic() = default;
    //From a pre-existing list of conic coefficients
    Conic(const Eigen::VectorXd &coef) : conic_coef(coef){};
    //From a set of points
    Conic(const Points &points);
    //From a set of tangents
    Conic(const Tangentes &tangents);
    
    //Getter
    Eigen::Matrix3d matrix() const;
    Eigen::VectorXd coef() const;
    
    
    void display() const;
    void tangent(const std::vector<Eigen::Vector3d> &tangents);
    
    //Destructor
    ~Conic() = default;
};


