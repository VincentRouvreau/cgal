// ======================================================================
//
// Copyright (c) 1999 The CGAL Consortium
//
// This software and related documentation is part of an INTERNAL release
// of the Computational Geometry Algorithms Library (CGAL). It is not
// intended for general use.
//
// ----------------------------------------------------------------------
// 
// release       :
// release_date  :
// 
// file          : include/CGAL/Arithmetic_filter/predicates/Regular_triangulation_ftC2.h
// package       : Interval_arithmetic
// author(s)     : Sylvain Pion <Sylvain.Pion@sophia.inria.fr>
//
// coordinator   : INRIA Sophia-Antipolis (<Mariette.Yvinec@sophia.inria.fr>)
// ======================================================================

// This file is automatically generated by the script
// examples/Interval_arithmetic/filtered_predicate_converter.

#ifndef CGAL_ARITHMETIC_FILTER_REGULAR_TRIANGULATION_FTC2_H
#define CGAL_ARITHMETIC_FILTER_REGULAR_TRIANGULATION_FTC2_H

CGAL_BEGIN_NAMESPACE

inline
Oriented_side
power_testC2_SAF(
    const Static_filter_error &px,
    const Static_filter_error &py,
    const Static_filter_error &pwt,
    const Static_filter_error &qx,
    const Static_filter_error &qy,
    const Static_filter_error &qwt,
    const Static_filter_error &rx,
    const Static_filter_error &ry,
    const Static_filter_error &rwt,
    const Static_filter_error &tx,
    const Static_filter_error &ty,
    const Static_filter_error &twt,
    double & epsilon_0)
{
    

    
    Static_filter_error dpx = px - tx;
    Static_filter_error dpy = py - ty;
    Static_filter_error dpz = square(dpx) + square(dpy) - pwt + twt;
    Static_filter_error dqx = qx - tx;
    Static_filter_error dqy = qy - ty;
    Static_filter_error dqz = square(dqx) + square(dqy) - qwt + twt;
    Static_filter_error drx = rx - tx;
    Static_filter_error dry = ry - ty;
    Static_filter_error drz = square(drx) + square(dry) - rwt + twt;

    return Oriented_side(sign_of_determinant3x3_SAF(dpx, dpy, dpz,
                                                dqx, dqy, dqz,
                                                drx, dry, drz, epsilon_0));
}

inline
Oriented_side
power_testC2_SAF(
    const Restricted_double &px,
    const Restricted_double &py,
    const Restricted_double &pwt,
    const Restricted_double &qx,
    const Restricted_double &qy,
    const Restricted_double &qwt,
    const Restricted_double &rx,
    const Restricted_double &ry,
    const Restricted_double &rwt,
    const Restricted_double &tx,
    const Restricted_double &ty,
    const Restricted_double &twt,
    const double & epsilon_0)
{
    

    
    Restricted_double dpx = px - tx;
    Restricted_double dpy = py - ty;
    Restricted_double dpz = square(dpx) + square(dpy) - pwt + twt;
    Restricted_double dqx = qx - tx;
    Restricted_double dqy = qy - ty;
    Restricted_double dqz = square(dqx) + square(dqy) - qwt + twt;
    Restricted_double drx = rx - tx;
    Restricted_double dry = ry - ty;
    Restricted_double drz = square(drx) + square(dry) - rwt + twt;

    return Oriented_side(sign_of_determinant3x3_SAF(dpx, dpy, dpz,
                                                dqx, dqy, dqz,
                                                drx, dry, drz, epsilon_0));
}

inline
Oriented_side
power_testC2(
    const Static_adaptatif_filter &px,
    const Static_adaptatif_filter &py,
    const Static_adaptatif_filter &pwt,
    const Static_adaptatif_filter &qx,
    const Static_adaptatif_filter &qy,
    const Static_adaptatif_filter &qwt,
    const Static_adaptatif_filter &rx,
    const Static_adaptatif_filter &ry,
    const Static_adaptatif_filter &rwt,
    const Static_adaptatif_filter &tx,
    const Static_adaptatif_filter &ty,
    const Static_adaptatif_filter &twt)
{
  bool tried = false;
  static double SAF_bound = -1.0;
  static double SAF_epsilon_0;

letstry:
  try
  {
    // Check the bounds.  All arguments must be <= SAF_bound.
    // The throw mecanism is not useful here, it should be before the try{}.
    if (
        fabs(px.value()) > SAF_bound ||
        fabs(py.value()) > SAF_bound ||
        fabs(pwt.value()) > SAF_bound ||
        fabs(qx.value()) > SAF_bound ||
        fabs(qy.value()) > SAF_bound ||
        fabs(qwt.value()) > SAF_bound ||
        fabs(rx.value()) > SAF_bound ||
        fabs(ry.value()) > SAF_bound ||
        fabs(rwt.value()) > SAF_bound ||
        fabs(tx.value()) > SAF_bound ||
        fabs(ty.value()) > SAF_bound ||
        fabs(twt.value()) > SAF_bound)
      throw Restricted_double::unsafe_comparison();
    // Try the epsilon variant of the predicate.
    return power_testC2_SAF(
		Restricted_double(px.value()),
		Restricted_double(py.value()),
		Restricted_double(pwt.value()),
		Restricted_double(qx.value()),
		Restricted_double(qy.value()),
		Restricted_double(qwt.value()),
		Restricted_double(rx.value()),
		Restricted_double(ry.value()),
		Restricted_double(rwt.value()),
		Restricted_double(tx.value()),
		Restricted_double(ty.value()),
		Restricted_double(twt.value()),
		SAF_epsilon_0);
  }
  catch (Restricted_double::unsafe_comparison)
  {
    // It failed once, we re-adjust (bound, epsilons).
    if (!tried)
    {
      tried = true;
      // Recompute SAF_bound (tighter or larger).
      SAF_bound = 0;
      SAF_bound = std::max(SAF_bound, fabs(px.value()));
      SAF_bound = std::max(SAF_bound, fabs(py.value()));
      SAF_bound = std::max(SAF_bound, fabs(pwt.value()));
      SAF_bound = std::max(SAF_bound, fabs(qx.value()));
      SAF_bound = std::max(SAF_bound, fabs(qy.value()));
      SAF_bound = std::max(SAF_bound, fabs(qwt.value()));
      SAF_bound = std::max(SAF_bound, fabs(rx.value()));
      SAF_bound = std::max(SAF_bound, fabs(ry.value()));
      SAF_bound = std::max(SAF_bound, fabs(rwt.value()));
      SAF_bound = std::max(SAF_bound, fabs(tx.value()));
      SAF_bound = std::max(SAF_bound, fabs(ty.value()));
      SAF_bound = std::max(SAF_bound, fabs(twt.value()));

      // recompute epsilons: "just" call it over Static_filter_error.
      // That's the tricky part that might not work for everything.
      (void) power_testC2_SAF(
		Static_filter_error(SAF_bound,0,1),
		Static_filter_error(SAF_bound,0,1),
		Static_filter_error(SAF_bound,0,1),
		Static_filter_error(SAF_bound,0,1),
		Static_filter_error(SAF_bound,0,1),
		Static_filter_error(SAF_bound,0,1),
		Static_filter_error(SAF_bound,0,1),
		Static_filter_error(SAF_bound,0,1),
		Static_filter_error(SAF_bound,0,1),
		Static_filter_error(SAF_bound,0,1),
		Static_filter_error(SAF_bound,0,1),
		Static_filter_error(SAF_bound,0,1),
		SAF_epsilon_0);

      // We should verify that all epsilons have really been updated.

      // Try again with the updated (SAF_bound, epsilon)
      goto letstry;
    }
    // This scheme definitely fails => exact computation (filtered_exact<> ?).
    return power_testC2(
		px.exact(),
		py.exact(),
		pwt.exact(),
		qx.exact(),
		qy.exact(),
		qwt.exact(),
		rx.exact(),
		ry.exact(),
		rwt.exact(),
		tx.exact(),
		ty.exact(),
		twt.exact());
  }
}

inline
Oriented_side
power_testC2_SAF(
    const Static_filter_error &px,
    const Static_filter_error &py,
    const Static_filter_error &pwt,
    const Static_filter_error &qx,
    const Static_filter_error &qy,
    const Static_filter_error &qwt,
    const Static_filter_error &tx,
    const Static_filter_error &ty,
    const Static_filter_error &twt,
    double & epsilon_0,
    double & epsilon_1,
    double & epsilon_2,
    double & epsilon_3)
{
    
    Static_filter_error dpx = px - tx;
    Static_filter_error dpy = py - ty;
    Static_filter_error dpz = square(dpx) + square(dpy) - pwt + twt;
    Static_filter_error dqx = qx - tx;
    Static_filter_error dqy = qy - ty;
    Static_filter_error dqz = square(dqx) + square(dqy) - qwt + twt;

    
    Comparison_result cmpx = CGAL::compare_SAF(px, qx, epsilon_0);
    if (cmpx != EQUAL)
	return Oriented_side(cmpx * sign_of_determinant2x2_SAF(dpx, dpz, dqx, dqz, epsilon_1));

    
    Comparison_result cmpy = CGAL::compare_SAF(py, qy, epsilon_2);
    return Oriented_side(cmpy * sign_of_determinant2x2_SAF(dpy, dpz, dqy, dqz, epsilon_3));
}

inline
Oriented_side
power_testC2_SAF(
    const Restricted_double &px,
    const Restricted_double &py,
    const Restricted_double &pwt,
    const Restricted_double &qx,
    const Restricted_double &qy,
    const Restricted_double &qwt,
    const Restricted_double &tx,
    const Restricted_double &ty,
    const Restricted_double &twt,
    const double & epsilon_0,
    const double & epsilon_1,
    const double & epsilon_2,
    const double & epsilon_3)
{
    
    Restricted_double dpx = px - tx;
    Restricted_double dpy = py - ty;
    Restricted_double dpz = square(dpx) + square(dpy) - pwt + twt;
    Restricted_double dqx = qx - tx;
    Restricted_double dqy = qy - ty;
    Restricted_double dqz = square(dqx) + square(dqy) - qwt + twt;

    
    Comparison_result cmpx = CGAL::compare_SAF(px, qx, epsilon_0);
    if (cmpx != EQUAL)
	return Oriented_side(cmpx * sign_of_determinant2x2_SAF(dpx, dpz, dqx, dqz, epsilon_1));

    
    Comparison_result cmpy = CGAL::compare_SAF(py, qy, epsilon_2);
    return Oriented_side(cmpy * sign_of_determinant2x2_SAF(dpy, dpz, dqy, dqz, epsilon_3));
}

inline
Oriented_side
power_testC2(
    const Static_adaptatif_filter &px,
    const Static_adaptatif_filter &py,
    const Static_adaptatif_filter &pwt,
    const Static_adaptatif_filter &qx,
    const Static_adaptatif_filter &qy,
    const Static_adaptatif_filter &qwt,
    const Static_adaptatif_filter &tx,
    const Static_adaptatif_filter &ty,
    const Static_adaptatif_filter &twt)
{
  bool tried = false;
  static double SAF_bound = -1.0;
  static double SAF_epsilon_0;
  static double SAF_epsilon_1;
  static double SAF_epsilon_2;
  static double SAF_epsilon_3;

letstry:
  try
  {
    // Check the bounds.  All arguments must be <= SAF_bound.
    // The throw mecanism is not useful here, it should be before the try{}.
    if (
        fabs(px.value()) > SAF_bound ||
        fabs(py.value()) > SAF_bound ||
        fabs(pwt.value()) > SAF_bound ||
        fabs(qx.value()) > SAF_bound ||
        fabs(qy.value()) > SAF_bound ||
        fabs(qwt.value()) > SAF_bound ||
        fabs(tx.value()) > SAF_bound ||
        fabs(ty.value()) > SAF_bound ||
        fabs(twt.value()) > SAF_bound)
      throw Restricted_double::unsafe_comparison();
    // Try the epsilon variant of the predicate.
    return power_testC2_SAF(
		Restricted_double(px.value()),
		Restricted_double(py.value()),
		Restricted_double(pwt.value()),
		Restricted_double(qx.value()),
		Restricted_double(qy.value()),
		Restricted_double(qwt.value()),
		Restricted_double(tx.value()),
		Restricted_double(ty.value()),
		Restricted_double(twt.value()),
		SAF_epsilon_0,
		SAF_epsilon_1,
		SAF_epsilon_2,
		SAF_epsilon_3);
  }
  catch (Restricted_double::unsafe_comparison)
  {
    // It failed once, we re-adjust (bound, epsilons).
    if (!tried)
    {
      tried = true;
      // Recompute SAF_bound (tighter or larger).
      SAF_bound = 0;
      SAF_bound = std::max(SAF_bound, fabs(px.value()));
      SAF_bound = std::max(SAF_bound, fabs(py.value()));
      SAF_bound = std::max(SAF_bound, fabs(pwt.value()));
      SAF_bound = std::max(SAF_bound, fabs(qx.value()));
      SAF_bound = std::max(SAF_bound, fabs(qy.value()));
      SAF_bound = std::max(SAF_bound, fabs(qwt.value()));
      SAF_bound = std::max(SAF_bound, fabs(tx.value()));
      SAF_bound = std::max(SAF_bound, fabs(ty.value()));
      SAF_bound = std::max(SAF_bound, fabs(twt.value()));

      // recompute epsilons: "just" call it over Static_filter_error.
      // That's the tricky part that might not work for everything.
      (void) power_testC2_SAF(
		Static_filter_error(SAF_bound,0,1),
		Static_filter_error(SAF_bound,0,1),
		Static_filter_error(SAF_bound,0,1),
		Static_filter_error(SAF_bound,0,1),
		Static_filter_error(SAF_bound,0,1),
		Static_filter_error(SAF_bound,0,1),
		Static_filter_error(SAF_bound,0,1),
		Static_filter_error(SAF_bound,0,1),
		Static_filter_error(SAF_bound,0,1),
		SAF_epsilon_0,
		SAF_epsilon_1,
		SAF_epsilon_2,
		SAF_epsilon_3);

      // We should verify that all epsilons have really been updated.

      // Try again with the updated (SAF_bound, epsilon)
      goto letstry;
    }
    // This scheme definitely fails => exact computation (filtered_exact<> ?).
    return power_testC2(
		px.exact(),
		py.exact(),
		pwt.exact(),
		qx.exact(),
		qy.exact(),
		qwt.exact(),
		tx.exact(),
		ty.exact(),
		twt.exact());
  }
}

CGAL_END_NAMESPACE

#endif // CGAL_ARITHMETIC_FILTER_REGULAR_TRIANGULATION_FTC2_H
