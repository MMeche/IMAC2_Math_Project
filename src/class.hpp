#pragma once
#include <string>
#include <vector>
#include "class.hpp"
#include "function.hpp"
#include <Eigen/Dense>
//#include "C:/Users/fox20/Downloads/eigen-3.4.0/eigen-3.4.0/Eigen/Dense"

class FormContainer{
    private :
    std::vector<Eigen::Vector3d> _x;
    
    public:
    FormContainer()=default;
    inline std::vector<Eigen::Vector3d> getter()const{return _x;};
    inline void setter(const std::vector<Eigen::Vector3d> &x){_x=x;};

};

//Container de points
class Points : public FormContainer
{   
    private:
    std::vector<Eigen::Vector3d> _points;
    
    public:
    Points()=default;
};
//Container de tangentes
class Tangentes : public FormContainer
{
    private:
    std::vector<Eigen::Vector3d> _tangentes;
    
    public:
    Tangentes()=default;
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

    //From a set of points
    Conic(const Points &points);
    //From a set of tangents
    Conic(const Tangentes &tangents);
    
    //Getter
    Eigen::Matrix3d matrix() const;
    Eigen::VectorXd coef() const;

    //Setter
    void change_matrix(const Eigen::Matrix3d &m);
    void change_coef(const Eigen::VectorXd &c);

    //Methode
    double norm();
    
    //Destructor
    ~Conic() = default;
};


template<typename T>
void handle_exceptions(const T &t);
