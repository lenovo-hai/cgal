// Copyright (c) 2005-2006  INRIA Sophia-Antipolis (France).
// All rights reserved.
//
// This file is part of CGAL (www.cgal.org); you may redistribute it under
// the terms of the Q Public License version 1.0.
// See the file LICENSE.QPL distributed with CGAL.
//
// Licensees holding a valid commercial license may use this file in
// accordance with the commercial license agreement provided with the software.
//
// This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
// WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
//
// Partially supported by the IST Programme of the EU as a Shared-cost
// RTD (FET Open) Project under Contract No  IST-2000-26473 
// (ECG - Effective Computational Geometry for Curves and Surfaces) 
// and a STREP (FET Open) Project under Contract No  IST-006413 
// (ACS -- Algorithms for Complex Shapes)
//
// $URL: $
// $Id: $
//
// Author(s) : Monique Teillaud <Monique.Teillaud@sophia.inria.fr>
//             Sylvain Pion     <Sylvain.Pion@sophia.inria.fr>
//             Pedro Machado    <tashimir@gmail.com>
//             Julien Hazebrouck
//             Damien Leroy


#ifndef CGAL_CIRCULAR_ARC_POINT_3_H
#define CGAL_CIRCULAR_ARC_POINT_3_H
namespace CGAL {

template < typename SphericalKernel >
class Circular_arc_point_3
  : public SphericalKernel::Kernel_base::Circular_arc_point_3
{
  typedef typename SphericalKernel::Kernel_base::Circular_arc_point_3 
                                           RCircular_arc_point_3;

  typedef typename SphericalKernel::Root_of_2             Root_of_2;
  typedef typename SphericalKernel::Point_3               Point_3;
  typedef typename SphericalKernel::Plane_3               Plane_3;
  typedef typename SphericalKernel::Line_3                Line_3;
  typedef typename SphericalKernel::Circle_3              Circle_3;
  typedef typename SphericalKernel::Sphere_3              Sphere_3;

public:
  typedef typename SphericalKernel::Root_for_spheres_2_3 
    Root_for_spheres_2_3;
  typedef SphericalKernel   R; 
  typedef RCircular_arc_point_3 Rep;

  const Rep& rep() const
  {
    return *this;
  }

  Rep& rep()
  {
    return *this;
  }

  Circular_arc_point_3()
  : RCircular_arc_point_3(
    typename R::Construct_circular_arc_point_3()())
  {}

  Circular_arc_point_3(const Root_of_2 & x,
		       const Root_of_2 & y,
		       const Root_of_2 & z)
  : RCircular_arc_point_3(
    typename R::Construct_circular_arc_point_3()(x,y,z))
  {}
    

  Circular_arc_point_3(const Root_for_spheres_2_3 & np)
  : RCircular_arc_point_3(
    typename R::Construct_circular_arc_point_3()(np))
  {}

  Circular_arc_point_3(const RCircular_arc_point_3 & p)
  : RCircular_arc_point_3(p)
  {}

  Circular_arc_point_3(const Point_3 & p)
  : RCircular_arc_point_3(
    typename R::Construct_circular_arc_point_3()(p))
  {}

  Circular_arc_point_3(const Sphere_3 & s1,
                       const Sphere_3 & s2,
                       const Sphere_3 & s3,
                       const bool less_xyz = true)
  : RCircular_arc_point_3(
    typename R::Construct_circular_arc_point_3()(s1,s2,s3,less_xyz))
  {}

  Circular_arc_point_3(const Plane_3 & p,
                       const Sphere_3 & s1,
                       const Sphere_3 & s2,
                       const bool less_xyz = true)
  : RCircular_arc_point_3(
    typename R::Construct_circular_arc_point_3()(p,s1,s2,less_xyz))
  {}

  Circular_arc_point_3(const Sphere_3 & s1,
                       const Plane_3 & p,
                       const Sphere_3 & s2,
                       const bool less_xyz = true)
  : RCircular_arc_point_3(
    typename R::Construct_circular_arc_point_3()(s1,p,s2,less_xyz))
  {}

  Circular_arc_point_3(const Sphere_3 & s1,
                       const Sphere_3 & s2,
                       const Plane_3 & p,
                       const bool less_xyz = true)
  : RCircular_arc_point_3(
    typename R::Construct_circular_arc_point_3()(s1,s2,p,less_xyz))
  {}

  Circular_arc_point_3(const Plane_3 & p1,
                       const Plane_3 & p2,
                       const Sphere_3 & s,
                       const bool less_xyz = true)
  : RCircular_arc_point_3(
    typename R::Construct_circular_arc_point_3()(p1,p2,s,less_xyz))
  {}

  Circular_arc_point_3(const Plane_3 & p1,
                       const Sphere_3 & s,
                       const Plane_3 & p2,
                       const bool less_xyz = true)
  : RCircular_arc_point_3(
    typename R::Construct_circular_arc_point_3()(p1,s,p2,less_xyz))
  {}

  Circular_arc_point_3(const Sphere_3 & s,
                       const Plane_3 & p1,
                       const Plane_3 & p2,
                       const bool less_xyz = true)
  : RCircular_arc_point_3(
    typename R::Construct_circular_arc_point_3()(s,p1,p2,less_xyz))
  {}

  Circular_arc_point_3(const Line_3 & l,
                       const Sphere_3 & s,
                       const bool less_xyz = true)
  : RCircular_arc_point_3(
    typename R::Construct_circular_arc_point_3()(l,s,less_xyz))
  {}

  Circular_arc_point_3(const Sphere_3 & s,
                       const Line_3 & l,
                       const bool less_xyz = true)
  : RCircular_arc_point_3(
    typename R::Construct_circular_arc_point_3()(s,l,less_xyz))
  {}

  Circular_arc_point_3(const Circle_3 & c,
                       const Sphere_3 & s,
                       const bool less_xyz = true)
  : RCircular_arc_point_3(
    typename R::Construct_circular_arc_point_3()(c,s,less_xyz))
  {}

  Circular_arc_point_3(const Sphere_3 & s,
                       const Circle_3 & c,
                       const bool less_xyz = true)
  : RCircular_arc_point_3(
    typename R::Construct_circular_arc_point_3()(s,c,less_xyz))
  {}

  Circular_arc_point_3(const Circle_3 & c,
                       const Plane_3 & p,
                       const bool less_xyz = true)
  : RCircular_arc_point_3(
    typename R::Construct_circular_arc_point_3()(c,p,less_xyz))
  {}

  Circular_arc_point_3(const Sphere_3 & s,
                       const Plane_3 & p,
                       const bool less_xyz = true)
  : RCircular_arc_point_3(
    typename R::Construct_circular_arc_point_3()(s,p,less_xyz))
  {}

      
      
  typename Qualified_result_of<typename R::Compute_circular_x_3,Circular_arc_point_3>::type
  //const Root_of_2 &
  x() const
  { return typename R::Compute_circular_x_3()(*this);}

  typename Qualified_result_of<typename R::Compute_circular_y_3,Circular_arc_point_3>::type
  //const Root_of_2 &
  y() const
  { return typename R::Compute_circular_y_3()(*this);}

  typename Qualified_result_of<typename R::Compute_circular_z_3,Circular_arc_point_3>::type
  //const Root_of_2 &
  z() const
  { return typename R::Compute_circular_z_3()(*this);}

  Bbox_3 bbox() const
  { return typename R::Construct_bbox_3()(*this); }

};

  template < class SK >
std::ostream&
operator<<(std::ostream &os, const Circular_arc_point_3<SK> &p)
{
  //I can make it because I know the output format of Root_for_circle
  return os << p.x() << " " << p.y() << " " << p.z() << " " ;
}




}
#endif
