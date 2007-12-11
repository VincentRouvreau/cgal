// Copyright (c) 1997  Tel-Aviv University (Israel).
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
// $URL$
// $Id$
// 
//
// Author(s)     : Baruch Zukerman <baruchzu@post.tau.ac.il>
//                 Ron Wein <wein@post.tau.ac.il>

#ifndef CGAL_ARR_BASIC_INSERTION_TRAITS_2_H
#define CGAL_ARR_BASIC_INSERTION_TRAITS_2_H

/*!
 * Defintion of the Arr_basic_insertion_traits_2<Traits,Arrangement> class.
 */

#include <CGAL/Object.h>
#include <CGAL/Arr_tags.h>

#include <list>
#include <iterator>

CGAL_BEGIN_NAMESPACE

/*! 
 * A basic meta-traits class that stores a halfedge handle with every
 * x-monotone curve, and a vertex handle with each point. This information is 
 * used to speed up the aggregated insertion process.
 */
template <typename Traits_, typename Arrangement_>
class Arr_basic_insertion_traits_2 
{
public:

  typedef Traits_                                   Traits_2;
  typedef Arrangement_                              Arrangement_2;

  typedef typename Arrangement_2::Halfedge_handle   Halfedge_handle;
  typedef typename Arrangement_2::Vertex_handle     Vertex_handle;
  typedef typename Traits_2::X_monotone_curve_2     Base_x_monotone_curve_2;
  typedef typename Traits_2::Point_2                Base_point_2;
  typedef typename Traits_2::Construct_min_vertex_2 Base_construct_min_vertex_2;
  typedef typename Traits_2::Construct_max_vertex_2 Base_construct_max_vertex_2;
  typedef typename Traits_2::Compare_x_2            Base_compare_x_2;
  typedef typename Traits_2::Compare_xy_2           Base_compare_xy_2;
  typedef typename Traits_2::Compare_y_at_x_2       Base_compare_y_at_x_2;
  typedef typename Traits_2::Compare_y_at_x_right_2 Base_compare_y_at_x_right_2;
  typedef typename Traits_2::Equal_2                Base_equal_2;
  typedef typename Traits_2::Is_vertical_2          Base_is_vertical_2;

  typedef typename Traits_2::Boundary_category      Boundary_category;

  /* Insertion is implemented as sweep-line visitor. The sweep-line algorithm
   * never uses Compare_y_at_x_left_2.
   */
  typedef Tag_false                                 Has_left_category;

protected:

  //! The base traits.
  Traits_2*    m_base_traits;

public:

  /*! Constructor. */
  Arr_basic_insertion_traits_2 (Traits_2& tr):
    m_base_traits (&tr)
  {}

  /*! 
   * Nested extension of the x-monotone curve type.
   */
  class Ex_x_monotone_curve_2 
  {
  public:

    typedef  Base_x_monotone_curve_2  Base;

  protected:

    Base                m_base_xcv;    // The base x-monotone curve.
    Halfedge_handle     m_he_handle;   // The corresponding arrangement edge
                                       // (may be invalid).
    bool                m_overlap;     // Does this curve represent and overlap
                                       // of two other curves.

  public:

    Ex_x_monotone_curve_2():
      m_base_xcv(),
      m_he_handle(),
      m_overlap(false)
    {}

    Ex_x_monotone_curve_2(const Base& xcv):
      m_base_xcv (xcv),
      m_he_handle(),
      m_overlap(false)
    {}

    Ex_x_monotone_curve_2(const Base& xcv, Halfedge_handle he) :
      m_base_xcv (xcv),
      m_he_handle (he),
      m_overlap(false)
    {
      CGAL_precondition (he == Halfedge_handle() ||
                         he->direction() == ARR_RIGHT_TO_LEFT);
    }

    const Base& base() const
    {
      return (m_base_xcv);
    }

    Base& base()
    {
      return (m_base_xcv);
    }

    operator const Base& () const
    {
      return (m_base_xcv);
    }

    Ex_x_monotone_curve_2& operator= (const Base& xcv)
    {
      m_base_xcv = xcv;
      m_he_handle = Halfedge_handle();
      return (*this);
    }

    Halfedge_handle halfedge_handle() const
    {
      return (m_he_handle);
    }

    void set_halfedge_handle(Halfedge_handle he)
    {
      CGAL_precondition (he == Halfedge_handle() ||
                         he->direction() == ARR_RIGHT_TO_LEFT);
      m_he_handle = he;
    }

    bool is_overlapping () const
    {
      return (m_overlap);
    }

    void set_overlapping ()
    {
      m_overlap = true;
    }
  };

  typedef Ex_x_monotone_curve_2                     X_monotone_curve_2;

#ifdef VERBOSE
  // For debugging purposes:
  friend std::ostream& operator<< (std::ostream& os,
                                   const X_monotone_curve_2& xcv)
  {
    os << xcv.base();
    return (os);
  }
#endif
 
  /*! 
   * Nested extension of the point type.
   */
  class Ex_point_2 
  {
  public:

    typedef  Base_point_2            Base;

  protected:

    Base             m_base_pt;        // The base point.
    Vertex_handle    m_v;              // The corresponding arrangement vertex
                                       // (may be invalid).

  public:

    Ex_point_2() :
      m_base_pt(),
      m_v()
    {}

    Ex_point_2 (const Base& pt) :
      m_base_pt (pt),
      m_v()
    {}

    Ex_point_2 (const Base& pt, Vertex_handle v) :
      m_base_pt (pt),
      m_v (v)
    {}

    const Base& base() const
    {
      return (m_base_pt);
    }
    
    operator const Base& () const
    {
      return (m_base_pt);
    }

    Vertex_handle vertex_handle() const
    {
      return m_v;
    }

    void set_vertex_handle(Vertex_handle v)
    {
      m_v = v;
    }
  };

  typedef Ex_point_2                                Point_2;

#ifdef VERBOSE
  // For debugging purposes:
  friend std::ostream& operator<< (std::ostream& os,
                                   const Point_2& pt)
  {
    os << pt.base();
    return (os);
  }
#endif

  /*! A functor that obtains the left endpoint of an x-monotone curve. */
  class Construct_min_vertex_2 {
  protected:
    Base_construct_min_vertex_2  m_base_min_v;
    Base_equal_2                 m_base_equal;
    Halfedge_handle              invalid_he;

    /*! Constructor.
     * The constructor is declared private to allow only the functor
     * obtaining function, which is a member of the nesting class,
     * constructing it.
     */
    Construct_min_vertex_2 (const Base_construct_min_vertex_2& base_min_v,
                            const Base_equal_2& base_equal) :
      m_base_min_v (base_min_v),
      m_base_equal (base_equal),
      invalid_he()
    {}

    //! Allow its functor obtaining function calling the private constructor.
    friend class Arr_basic_insertion_traits_2<Traits_, Arrangement_>;
    
  public:
    Point_2 operator() (const X_monotone_curve_2 & xcv) 
    {
      // If there is not halfedge associated with the curve, just return
      // a point with invalid halfedge handle.
      const Base_point_2&  base_p = m_base_min_v(xcv.base());

      if (xcv.halfedge_handle() == invalid_he)
        return (Point_2 (base_p));

      // Note that the halfedge associated with the curve is always directed
      // from right to left, so its target is the leftmost vertex.
      // We probably have to associate the point with the target vertex of
      // the halfedge associated with the curve.
      Vertex_handle        vh = xcv.halfedge_handle()->target();

      if (! xcv.is_overlapping())
        return (Point_2(base_p, vh));

      // In case of an overlapping curve, make sure the curve endpoint equals
      // the point associated with the vertex. If not, we attach an invalid
      // vertex to the extended point.
      if (! vh->is_at_infinity() && m_base_equal (base_p, vh->point()))
        return (Point_2(base_p, vh));
      else
        return (Point_2 (base_p));
    }
  };

  /*! Obtain a Construct_min_vertex_2 function object */
  Construct_min_vertex_2 construct_min_vertex_2_object () const
  {
    return (Construct_min_vertex_2
            (m_base_traits->construct_min_vertex_2_object(),
             m_base_traits->equal_2_object()));
  }

  /*! A functor that obtains the right endpoint of an x-monotone curve. */
  class Construct_max_vertex_2 {
  protected:
    Base_construct_max_vertex_2  m_base_max_v;
    Base_equal_2                 m_base_equal;
    Halfedge_handle              invalid_he;

    /*! Constructor.
     * The constructor is declared private to allow only the functor
     * obtaining function, which is a member of the nesting class,
     * constructing it.
     */
    Construct_max_vertex_2 (const Base_construct_max_vertex_2& base_max_v,
                            const Base_equal_2& base_equal) :
      m_base_max_v (base_max_v),
      m_base_equal (base_equal),
      invalid_he()
    {}


    //! Allow its functor obtaining function calling the private constructor.
    friend class Arr_basic_insertion_traits_2<Traits_, Arrangement_>;

  public:
    Point_2 operator() (const X_monotone_curve_2 & xcv) 
    {
      // If there is not halfedge associated with the curve, just return
      // a point with invalid halfedge handle.
      const Base_point_2&  base_p = m_base_max_v(xcv.base());

      if (xcv.halfedge_handle() == invalid_he)
        return (Point_2 (base_p));

      // Note that the halfedge associated with the curve is always directed
      // from right to left, so its source is the rightmost vertex.
      // We probably have to associate the point with the source vertex of
      // the halfedge associated with the curve.
      Vertex_handle        vh = xcv.halfedge_handle()->source();

      if (! xcv.is_overlapping())
        return (Point_2(base_p, vh));

      // In case of an overlapping curve, make sure the curve endpoint equals
      // the point associated with the vertex. If not, we attach an invalid
      // vertex to the extended point.
      if (! vh->is_at_infinity() && m_base_equal (base_p, vh->point()))
        return (Point_2(base_p, vh));
      else
        return (Point_2 (base_p));
    }
  };

  /*! Obtain a Construct_max_vertex_2 function object */
  Construct_max_vertex_2 construct_max_vertex_2_object () const
  {
    return (Construct_max_vertex_2
            (m_base_traits->construct_max_vertex_2_object(),
             m_base_traits->equal_2_object()));
  }

  /*! A functor that compares two points lexigoraphically: by x, then by y. */
  class Compare_xy_2 {
  protected:
    Base_compare_xy_2 m_base_cmp_xy;

    /*! Constructor.
     * The constructor is declared private to allow only the functor
     * obtaining function, which is a member of the nesting class,
     * constructing it.
     */
    Compare_xy_2(const Base_compare_xy_2 & base) : m_base_cmp_xy(base) {}

    //! Allow its functor obtaining function calling the private constructor.
    friend class Arr_basic_insertion_traits_2<Traits_, Arrangement_>;

  public:
    Comparison_result operator() (const Point_2& p1, const Point_2& p2) const
    {
      if(p1.vertex_handle() == p2.vertex_handle() &&
         p1.vertex_handle() != Vertex_handle())
        return (EQUAL);

      return (m_base_cmp_xy(p1.base(), p2.base()));
    }
  };

  /*! Obtain a Compare_xy_2 function object */
  Compare_xy_2 compare_xy_2_object () const
  {
    return (Compare_xy_2 (m_base_traits->compare_xy_2_object()));
  }

  /*! A functor that compares the y-coordinates of a point and an
   * x-monotone curve at the point x-coordinate.
   */
  class Compare_y_at_x_2 {
  protected:
    Base_compare_y_at_x_2 m_base_cmp_y_at_x;

    /*! Constructor.
     * The constructor is declared private to allow only the functor
     * obtaining function, which is a member of the nesting class,
     * constructing it.
     */
    Compare_y_at_x_2(const Base_compare_y_at_x_2& base) :
        m_base_cmp_y_at_x(base)
    {}

    //! Allow its functor obtaining function calling the private constructor.
    friend class Arr_basic_insertion_traits_2<Traits_, Arrangement_>;

  public:
    Comparison_result operator() (const Point_2& p,
                                  const X_monotone_curve_2& xcv) const
    {
      return (m_base_cmp_y_at_x (p.base(), xcv.base()));
    }
  };

  /*! Obtain a Compare_y_at_x_2 function object */
  Compare_y_at_x_2 compare_y_at_x_2_object () const
  {
    return (Compare_y_at_x_2 (m_base_traits->compare_y_at_x_2_object()));
  }

  /*! A functor that compares compares the y-coordinates of two x-monotone
   * curves immediately to the right of their intersection point.
   */
  class Compare_y_at_x_right_2 {
  protected:
    Base_compare_y_at_x_right_2 m_base_cmp_y_at_x_right;

    /*! Constructor.
     * The constructor is declared private to allow only the functor
     * obtaining function, which is a member of the nesting class,
     * constructing it.
     */
    Compare_y_at_x_right_2(const Base_compare_y_at_x_right_2& base) :
        m_base_cmp_y_at_x_right(base)
    {}

    //! Allow its functor obtaining function calling the private constructor.
    friend class Arr_basic_insertion_traits_2<Traits_, Arrangement_>;

  public:
    Comparison_result operator() (const X_monotone_curve_2& xcv1,
                                  const X_monotone_curve_2& xcv2,
                                  const Point_2& p) const
    {
      return (m_base_cmp_y_at_x_right(xcv1.base(),
                                      xcv2.base(),
                                      p.base()));
    }
  };

  /*! Obtain a Compare_y_at_x_right_2 function object */
  Compare_y_at_x_right_2 compare_y_at_x_right_2_object () const
  {
    return (Compare_y_at_x_right_2
	    (m_base_traits->compare_y_at_x_right_2_object()));
  }

  /*! A functor that checks whether two points and two x-monotone curves are
   * identical.
   */
  class Equal_2 {
  protected:
    Base_equal_2 m_base_eq;

    /*! Constructor.
     * The constructor is declared private to allow only the functor
     * obtaining function, which is a member of the nesting class,
     * constructing it.
     */
    Equal_2(const Base_equal_2& base) : m_base_eq(base) {}

    //! Allow its functor obtaining function calling the private constructor.
    friend class Arr_basic_insertion_traits_2<Traits_, Arrangement_>;

  public:
    /*! Check if two curves are the same. */
    bool operator() (const X_monotone_curve_2& xcv1,
		     const X_monotone_curve_2& xcv2) const
    {
      return (m_base_eq(xcv1.base(), xcv2.base()));
    }

    /*! Check if the two points are the same. */
    bool operator() (const Point_2& p1, const Point_2& p2) const
    {
      return (m_base_eq(p1.base(), p2.base()));
    }
  };

  /*! Obtain a Equal_2 function object */
  Equal_2 equal_2_object () const
  {
    return (Equal_2 (m_base_traits->equal_2_object()));
  }

  /*! A functor that compares the x-coordinates of two points */
  class Compare_x_2 {
  protected:
    Base_compare_x_2 m_base_cmp_x;

    /*! Constructor.
     * The constructor is declared private to allow only the functor
     * obtaining function, which is a member of the nesting class,
     * constructing it.
     */
    Compare_x_2(const Base_compare_x_2& base) : m_base_cmp_x(base) {}

    //! Allow its functor obtaining function calling the private constructor.
    friend class Arr_basic_insertion_traits_2<Traits_, Arrangement_>;

  public:
    Comparison_result operator() (const Point_2& p1, const Point_2& p2) const
    {
      return (m_base_cmp_x(p1.base(), p2.base()));
    }
  };

  /*! Obtain a Compare_x_2 function object */
  Compare_x_2 compare_x_2_object () const
  {
    return (Compare_x_2 (m_base_traits->compare_x_2_object()));
  }

  /*! A functor that checks whether a given x-monotone curve is vertical. */
  class Is_vertical_2 {
  protected:
    Base_is_vertical_2 m_base_is_vert;

    /*! Constructor.
     * The constructor is declared private to allow only the functor
     * obtaining function, which is a member of the nesting class,
     * constructing it.
     */
    Is_vertical_2(const Base_is_vertical_2& base) : m_base_is_vert(base) {}

    //! Allow its functor obtaining function calling the private constructor.
    friend class Arr_basic_insertion_traits_2<Traits_, Arrangement_>;

  public:
     bool operator() (const X_monotone_curve_2& xcv) const
    {
      return (m_base_is_vert(xcv.base()));
    }
  };

  /*! Obtain a Is_vertical_2 function object */
  Is_vertical_2 is_vertical_2_object() const
  {
    return (Is_vertical_2(m_base_traits->is_vertical_2_object()));
  }

  /*! A functor that determines whether an endpoint of an x-monotone curve lies
   * on a boundary of the parameter space along the x axis.
   */
  class Parameter_space_in_x_2 {
  protected:
    //! The base traits.
    const Traits_2 * m_base;

    /*! Constructor.
     * \param tr The base traits class. It must be passed, to handle non
     *           stateless traits objects, (which stores data).
     * The constructor is declared private to allow only the functor
     * obtaining function, which is a member of the nesting class,
     * constructing it.
     */
    Parameter_space_in_x_2 (const Traits_2 * tr) : m_base(tr) {}

    //! Allow its functor obtaining function calling the private constructor.
    friend class Arr_basic_insertion_traits_2<Traits_, Arrangement_>;

  public:
    Arr_parameter_space operator() (const X_monotone_curve_2 & xcv,
                                    Arr_curve_end ce) const
    {
      return parameter_space_in_x (xcv, ce, Boundary_category());
    }

    Arr_parameter_space operator()(const Point_2 & p) const
    {
      return parameter_space_in_x (p, Boundary_category());
    }

  private:
    Arr_parameter_space parameter_space_in_x (const X_monotone_curve_2& xcv,
                                              Arr_curve_end ce,
                                              Arr_has_boundary_tag) const
    {
      return (m_base->parameter_space_in_x_2_object() (xcv.base(), ce));
    }

    Arr_parameter_space parameter_space_in_x (const X_monotone_curve_2 &,
                                              Arr_curve_end,
                                              Arr_no_boundary_tag) const
    {
      return ARR_INTERIOR;
    }

    Arr_parameter_space parameter_space_in_x (const Point_2 & p,
                                              Arr_has_boundary_tag) const
    {
      return m_base->parameter_space_in_x_2_object() (p.base());
    }

    Arr_parameter_space parameter_space_in_x (const Point_2 &,
                                              Arr_no_boundary_tag) const
    {
      return ARR_INTERIOR;
    }
  };

  /*! Obtain a Parameter_space_in_x_2 function object */
  Parameter_space_in_x_2 parameter_space_in_x_2_object () const
  {
    return Parameter_space_in_x_2 (m_base_traits);
  }

  /*! A functor that determines whether an endpoint of an x-monotone arc lies
   * on a boundary of the parameter space along the y axis.
   */
  class Parameter_space_in_y_2 {
  protected:
    //! The base traits.
    const Traits_2 * m_base;

    /*! Constructor.
     * \param tr The base traits class. It must be passed, to handle non
     *           stateless traits objects, (which stores data).
     * The constructor is declared private to allow only the functor
     * obtaining function, which is a member of the nesting class,
     * constructing it.
     */
    Parameter_space_in_y_2(const Traits_2 * tr) : m_base(tr) {}

    //! Allow its functor obtaining function calling the private constructor.
    friend class Arr_basic_insertion_traits_2<Traits_, Arrangement_>;

  public:
    Arr_parameter_space operator() (const X_monotone_curve_2& xcv,
                                    Arr_curve_end ce) const
    {
      return parameter_space_in_y(xcv, ce, Boundary_category());
    }

    Arr_parameter_space operator()(const Point_2 & p) const
    {
      return parameter_space_in_y (p, Boundary_category());
    }

  private:
    Arr_parameter_space parameter_space_in_y (const X_monotone_curve_2& xcv,
                                              Arr_curve_end ce,
                                              Arr_has_boundary_tag) const
    {
      return m_base->parameter_space_in_y_2_object() (xcv.base(), ce);
    }

    Arr_parameter_space parameter_space_in_y (const X_monotone_curve_2&,
                                              Arr_curve_end,
                                              Arr_no_boundary_tag) const
    {
      return ARR_INTERIOR;
    }

    Arr_parameter_space parameter_space_in_y (const Point_2 & p,
                                              Arr_has_boundary_tag) const
    {
      return m_base->parameter_space_in_y_2_object() (p.base());
    }

    Arr_parameter_space parameter_space_in_y (const Point_2 &,
                                              Arr_no_boundary_tag) const
    {
      return ARR_INTERIOR;
    }
  };

  /*! Obtain a Parameter_space_in_y_2 function object */
  Parameter_space_in_y_2 parameter_space_in_y_2_object () const
  {
    return Parameter_space_in_y_2 (m_base_traits);
  }

  /*! A functor that compares the x-coordinates of curve ends near the
   * boundary of the parameter space.
   */
  class Compare_x_near_boundary_2 {
  protected:
    //! The base traits.
    const Traits_2 * m_base;

    Comparison_result compare_point_curve (const Point_2 & p,
                                           const X_monotone_curve_2 & xcv,
                                           Arr_curve_end ce,
                                           Arr_has_boundary_tag) const
    {
      return m_base->compare_x_near_boundary_2_object() (p.base(),
                                                         xcv.base(), ce);
    }

    /*! This function should never be invoked
     */
    Comparison_result compare_point_curve (const Point_2 &,
                                           const X_monotone_curve_2 &,
                                           Arr_curve_end,
                                           Arr_no_boundary_tag) const
    {
      CGAL_error();
      return EQUAL;
    }

    Comparison_result compare_curves (const X_monotone_curve_2 & xcv1, 
                                      Arr_curve_end ce1,
                                      const X_monotone_curve_2 & xcv2,
                                      Arr_curve_end ce2,
                                      Arr_has_boundary_tag) const
    {
      return m_base->compare_x_near_boundary_2_object() (xcv1.base(), ce1,
                                                         xcv2.base(), ce2);
    }

    /*! This function should never be invoiced
     */
    Comparison_result compare_curves (const X_monotone_curve_2 &,
                                      Arr_curve_end,
                                      const X_monotone_curve_2 &,
                                      Arr_curve_end,
                                      Arr_no_boundary_tag) const
    {
      CGAL_error();
      return EQUAL;
    }

    /*! Constructor.
     * \param base The base traits class. It must be passed, to handle non
     *             stateless traits objects, (which stores data).
     * The constructor is declared private to allow only the functor
     * obtaining function, which is a member of the nesting class,
     * constructing it.
     */
    Compare_x_near_boundary_2 (const Traits_2 * base) : m_base(base) {}

    //! Allow its functor obtaining function calling the private constructor.
    friend class Arr_basic_insertion_traits_2<Traits_, Arrangement_>;

  public:
    /*! Use tag dispatching to avoid compilation errors in case the functor
     * is not defined
     */
    Comparison_result operator() (const Point_2 & p,
                                  const X_monotone_curve_2 & xcv,
                                  Arr_curve_end ce) const
    {
      return compare_point_curve(p, xcv, ce, Boundary_category());
    }

    /*! Use tag dispatching to avoid compilation errors in case the functor
     * is not defined
     */
    Comparison_result operator() (const X_monotone_curve_2 & xcv1,
                                  Arr_curve_end ce1,
                                  const X_monotone_curve_2 & xcv2,
                                  Arr_curve_end ce2) const
    {
      return compare_curves (xcv1, ce1, xcv2, ce2, Boundary_category());
    }
  };
  
  /*! Obtain a Compare_x_near_boundary_2 object
   */ 
  Compare_x_near_boundary_2 compare_x_near_boundary_2_object() const
  {
    return Compare_x_near_boundary_2(m_base_traits);
  }

  /*! A functor that compares the y-coordinates of curve ends near the
   * boundary of the parameter space.
   */
  class Compare_y_near_boundary_2 {
  protected:
    //! The base traits.
    const Traits_2 * m_base;

    Comparison_result comp_y_near_bnd (const X_monotone_curve_2 & xcv1,
                                       const X_monotone_curve_2 & xcv2, 
                                       Arr_curve_end ce,
                                       Arr_has_boundary_tag) const
    {
      return m_base->compare_y_near_boundary_2_object() (xcv1.base(),
                                                         xcv2.base(), ce);
    }

    /*! This function should never be invoiced
     */
    Comparison_result comp_y_near_bnd (const X_monotone_curve_2 &,
                                       const X_monotone_curve_2 &, 
                                       Arr_curve_end,
                                       Arr_no_boundary_tag) const
    {
      CGAL_error();
      return EQUAL;
    }

    /*! Constructor.
     * \param base The base traits class. It must be passed, to handle non
     *             stateless traits objects, (which stores data).
     * The constructor is declared private to allow only the functor
     * obtaining function, which is a member of the nesting class,
     * constructing it.
     */
    Compare_y_near_boundary_2(const Traits_2 * base) : m_base(base) {}

    //! Allow its functor obtaining function calling the private constructor.
    friend class Arr_basic_insertion_traits_2<Traits_, Arrangement_>;

  public:
    /*! Use tag dispatching to avoid compilation errors in case the functor
     * is not defined
     */
    Comparison_result operator() (const X_monotone_curve_2 & xcv1,
                                  const X_monotone_curve_2 & xcv2, 
                                  Arr_curve_end ce) const
    {
      return comp_y_near_bnd (xcv1, xcv2, ce, Boundary_category());
    }
  };

  /*! Obtain a Compare_y_near_boundary_2 object
   */ 
  Compare_y_near_boundary_2 compare_y_near_boundary_2_object() const
  {
    return Compare_y_near_boundary_2 (m_base_traits);
  }


  /*! A functor that compares the y-coordinates of two points on the 
   * identification curve.
   */
  class Compare_y_on_identification_2 
  {
  protected:
    //! The base traits.
    const Traits_2 * m_base;
    
    Comparison_result comp_y_on_idnt(const Point_2 & p1,
                                     const Point_2 & p2,
                                     Arr_bounded_boundary_tag) const
    {
      return m_base->compare_y_on_identification_2_object()(p1.base(),
                                                            p2.base());
    }

    /*! This function should never be invoked
     */
    Comparison_result comp_y_on_idnt (const Point_2 & p1,
                                      const Point_2 & p2,
                                      Arr_has_boundary_tag) const
    {
      CGAL_error();
      return EQUAL;
    }
    
    /*! This function should never be invoked
     */
    Comparison_result comp_y_on_idnt (const Point_2 & p1,
                                      const Point_2 & p2,
                                      Arr_no_boundary_tag) const
    {
      CGAL_error();
      return EQUAL;
    }

    /*! Constructor.
     * \param base The base traits class. It must be passed, to handle non
     *             stateless traits objects, (which stores data).
     * The constructor is declared private to allow only the functor
     * obtaining function, which is a member of the nesting class,
     * constructing it.
     */
    Compare_y_on_identification_2 (const Traits_2 * base) : m_base(base) {}

    //! Allow its functor obtaining function calling the private constructor.
    friend class Arr_basic_insertion_traits_2<Traits_, Arrangement_>;

  public:
    /*! Use tag dispatching to avoid compilation errors in case the functor
     * is not defined
     */
    Comparison_result operator() (const Point_2 & p1,
                                  const Point_2 & p2) const
    {
      return comp_y_on_idnt(p1, p2, Boundary_category());
    }
  };

  /*! Obtain a Compare_y_on_identification_2 object
   */ 
  Compare_y_on_identification_2 compare_y_on_identification_2_object() const
  {
    return Compare_y_on_identification_2(m_base_traits);
  }

  /*! A function object that determines whether a curve end is bounded. */
  class Is_bounded_2 {
  protected:
    //! The base traits.
    const Traits_2 * m_base;

    /*! Constructor.
     * \param base The base traits class. It must be passed, to handle non
     *             stateless traits objects, (which stores data).
     * The constructor is declared private to allow only the functor
     * obtaining function, which is a member of the nesting class,
     * constructing it.
     */
    Is_bounded_2(const Traits_2 * base) : m_base(base) {}

    //! Allow its functor obtaining function calling the private constructor.
    friend class Arr_basic_insertion_traits_2<Traits_, Arrangement_>;
    
    bool is_bounded (const X_monotone_curve_2 &, Arr_curve_end,
                     Arr_no_boundary_tag) const
    { return true; }

    bool is_bounded (const X_monotone_curve_2 &, Arr_curve_end,
                     Arr_has_boundary_tag) const
    { return true; }

    bool is_bounded (const X_monotone_curve_2 & xcv, Arr_curve_end ce,
                     Arr_unbounded_boundary_tag) const
    {
      return m_base->is_bounded_2_object()(xcv, ce);
    }
    
  public:
    /*! Is the end of an x-monotone curve bounded?
     * \param xcv The x-monotone curve.
     * \param ce The end of xcv identifier.
     * \return true is the curve end is bounded, and false otherwise
     */
    bool operator() (const X_monotone_curve_2 & xcv, Arr_curve_end ce) const
    {
      return is_bounded(xcv, ce, Boundary_category());
    }
  };

  /*! Obtain a Is_bounded_2 function object. */
  Is_bounded_2 is_bounded_2_object() const
  {
    return Is_bounded_2(m_base_traits);
  }
};

CGAL_END_NAMESPACE

#endif
