#pragma once
#include <string>
#include <vector>

//#include <Eigen/Dense>
#include "C:/Users/fox20/Downloads/eigen-3.4.0/eigen-3.4.0/Eigen/Dense"

std::vector<Eigen::Vector3d> input_points(Viewer_conic &viewer);

void add_lines(const std::vector<Eigen::Vector3d> &tangents , Viewer_conic &viewer);

std::vector<Eigen::Vector3d> input_tangents(Viewer_conic &viewer);

Eigen::VectorXd moindre_carre(const Eigen::MatrixXd &A, const Eigen::VectorXd &points);