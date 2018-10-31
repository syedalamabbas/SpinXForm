//#include <igl/readOBJ.h>
//#include <igl/readPLY.h>
//#include <igl/opengl/glfw/Viewer.h>
//#include <iostream>
//#include "tutorial_shared_path.h"
//#include <igl/png/readPNG.h>
//#include <igl/cotmatrix.h>
//#include <algorithm>
//
//void clamp(const int& w, const int& h, int& x, int& y)
//// clamps coordinates to range [0,w-1] x [0,h-1]
//{
//	x = std::max(0, std::min(w - 1, x));
//	y = std::max(0, std::min(h - 1, y));
//}
//
//double BilinearFilterSample(Eigen::Matrix<unsigned char, Eigen::Dynamic, Eigen::Dynamic>& Image, double x, double y)
//{
//	double ax = x - floor(x);
//	double ay = y - floor(y);
//	double bx = 1. - ax;
//	double by = 1. - ay;
//	int x0 = (int)floor(x);
//	int y0 = (int)floor(y);
//	int x1 = x0 + 1;
//	int y1 = y0 + 1;
//
//	int w = Image.rows();
//	int h = Image.cols();
//
//	clamp(w, h, x0, y0);
//	clamp(w, h, x1, y1);
//
//	double val1 = Image(x0, y0)/255.f;
//	double val2 = Image(x0, y1)/255.f;
//	double val3 = Image(x1, y0)/255.f;
//	double val4 = Image(x1, y1)/255.f;
//
//	return by * (bx * val1 + ax * val3) +
//		ay * (bx * val2 + ax * val4);
//}
//
//Eigen::MatrixXd& BuildEigenValProblem(const Eigen::MatrixXd& V, const Eigen::MatrixXi& F, const Eigen::MatrixXd& Rho, & A)
//{
//	Eigen::MatrixXd A(V.rows(), V.rows());
//	for (int i = 0; i < F.rows(); i++) // visit each face
//	{
//
//	}
//
//	return A;
//}
//
//int main(int argc, char *argv[])
//{
//  // Step 1:  Load a mesh in PLY format, this is only one that reads the UV with the 3D model
//  Eigen::MatrixXd V;
//  Eigen::MatrixXi F;
//  Eigen::MatrixXd N;
//  Eigen::MatrixXd UV;
//  igl::readPLY(TUTORIAL_SHARED_PATH "/Keenan_sphere.ply", V, F, N, UV);
//  // Print the vertices, faces and UV matrices sizes
//  std::cout << "Vertices: " << V.rows() << " X " << V.cols() << std::endl;
//  std::cout << "Faces:    " << F.rows() << " X " << F.cols() << std::endl;
//  std::cout << "UV:    "    << UV.rows() << " X " << UV.cols() << std::endl;
//
//  // Step 2: Read the image, allocate temporary buffers, using builtin png for now
//  Eigen::Matrix<unsigned char, Eigen::Dynamic, Eigen::Dynamic> R, G, B, A;
//  igl::png::readPNG(TUTORIAL_SHARED_PATH "/bumpy.png", R, G, B, A);
//  std::cout << "Image Size:    " << R.rows() << " X " << R.cols() << std::endl;
//
//  // Step 3 : Scaling the curvature change by a range gating on the image values acquired
//  const double range = 5.;
//  Eigen::MatrixXd Rho(F.rows(),1);
//  for (int i = 0; i < F.rows(); i++)// compute average value over the face
//  {
//	  Rho(i,0) = 0;
//	  // compute average value over the face with 3 vertices, tet mesh would not work 
//	  Eigen::Vector2d curUV_1 = UV.row(F.row(i).x());
//	  Eigen::Vector2d curUV_2 = UV.row(F.row(i).y());
//	  Eigen::Vector2d curUV_3 = UV.row(F.row(i).z());
//
//	  // Debug here it should match : double bilinearinterpVal = BilinearFilterSample(R, curUV_1.x() * R.rows(), curUV_1.y() * R.cols());
//	  Rho(i,0) += BilinearFilterSample(R, curUV_1.x() * R.rows(), curUV_1.y() * R.cols()) / 3.f;
//	  Rho(i,0) += BilinearFilterSample(R, curUV_2.x() * R.rows(), curUV_2.y() * R.cols()) / 3.f;
//	  Rho(i,0) += BilinearFilterSample(R, curUV_3.x() * R.rows(), curUV_3.y() * R.cols()) / 3.f;
//
//	  // map value to [-range,range]
//	  Rho(i,0) = (2.*(Rho(i,0) - .5)) * range;
//  }
//  std::cout << "Rho values per face : " << Rho << std::endl;
//
//  // Step 4 :  Build the DiracOperator - Rho deformation matrix for Eigen value computations
//  Eigen::MatrixXd A;
//  BuildEigenValProblem(V, F, Rho, A);
//
//  // Step N : Create Laplacian i.e. Compute Laplace-Beltrami operator: #V by #V
//  Eigen::SparseMatrix<double> L;
//  igl::cotmatrix(V, F, L);
//  std::cout << "Computed Laplacian:    " << L.rows() << " X " << L.cols() << std::endl;
//
//  // Plot the mesh and register the callback
//  igl::opengl::glfw::Viewer viewer;
//  viewer.data().set_mesh(V, F);
//  viewer.launch();
//}
