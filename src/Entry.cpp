// Copyright (c) 2018 by University Paris-Est Marne-la-Vallee
// Entry.cpp
// This file is part of the Garamon Generator.
// Authors: Vincent Nozick and Stephane Breuils
// Contact: vincent.nozick@u-pem.fr
//
// Licence MIT
// A a copy of the MIT License is given along with this program


#include "Entry.hpp"


//constructeur class Entry
Entry::Entry(const std::string &equation,//chaine de caractères équation
             const std::string &objectName, //nom de l'objet
             const int &red, 
             const int &green, 
             const int &blue, 
             bool show_label, //indique s'il faut afficher une étique à l'objet
             bool show_value)//indique s'il faut afficher valeur objet
   : m_equation(equation), _objectName(objectName), m_show_label(show_label), m_show_value(show_value)
   {//initialise paramêtre
      m_color = std::vector<int>(3);
      m_color[0] = red;
      m_color[1] = green;
      m_color[2] = blue;
   }

//méthode display, pour afficher information objet
void Entry::display() const
{
    std::cout << "Entry " << std::endl;
    std::cout << "  object  : " << _objectName << std::endl;
    std::cout << "  equation: " << m_equation << std::endl;
    std::cout << "  color   : (";
    for(int i=0; i<(int)m_color.size()-1; ++i)//affiche composantes couleur stocké dans m_color
        std::cout << std::to_string(m_color[i]) << ", ";
    std::cout << std::to_string(m_color[m_color.size()-1]) << ")" << std::endl;
    std::cout << std::endl;
}


