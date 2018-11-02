//#pragma once
//#include "igl/igl_inline.h"
//#include <Eigen/Core>
//
//namespace igl
//{
//	template <typename DerivedV, typename DerivedF, typename DerivedN>
//	IGL_INLINE void per_face_areas(
//		const Eigen::MatrixBase<DerivedV>& V,
//		const Eigen::MatrixBase<DerivedF>& F,
//		Eigen::PlainObjectBase<DerivedN> & A);
//}
//
//namespace Eigen
//{
//	Eigen::Quaterniond AddQuat(Eigen::Quaterniond& Q1, Eigen::Quaterniond& Q2)
//	{
//		Eigen::Quaterniond R;
//		R.w() = Q1.w() + Q2.w();
//		R.x() = Q1.x() + Q2.x();
//		R.y() = Q1.y() + Q2.y();
//		R.z() = Q1.z() + Q2.z();
//
//		return R;
//	}
//
//	Eigen::Quaterniond SubQuat(Eigen::Quaterniond& Q1, Eigen::Quaterniond& Q2)
//	{
//		Eigen::Quaterniond R;
//		R.w() = Q1.w() - Q2.w();
//		R.x() = Q1.x() - Q2.x();
//		R.y() = Q1.y() - Q2.y();
//		R.z() = Q1.z() - Q2.z();
//
//		return R;
//	}
//
//	void MultiplyScalar(Eigen::Quaterniond& Q, double& c)
//	{
//		Q.w() *= c;
//		Q.x() *= c;
//		Q.y() *= c;
//		Q.z() *= c;
//	}
//
//	void AddScalar(Eigen::Quaterniond& Q, double& c)
//	{
//		Q.w() += c;
//		Q.x() += c;
//		Q.y() += c;
//		Q.z() += c;
//	}
//}