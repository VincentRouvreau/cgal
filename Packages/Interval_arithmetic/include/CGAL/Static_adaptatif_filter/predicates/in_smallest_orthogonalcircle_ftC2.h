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
// file          : include/CGAL/Arithmetic_filter/predicates/in_smallest_orthogonalcircle_ftC2.h
// package       : Interval_arithmetic
// author(s)     : Sylvain Pion <Sylvain.Pion@sophia.inria.fr>
//
// coordinator   : INRIA Sophia-Antipolis (<Mariette.Yvinec@sophia.inria.fr>)
// ======================================================================

// This file is automatically generated by the script
// examples/Interval_arithmetic/filtered_predicate_converter.

#ifndef CGAL_ARITHMETIC_FILTER_IN_SMALLEST_ORTHOGONALCIRCLE_FTC2_H
#define CGAL_ARITHMETIC_FILTER_IN_SMALLEST_ORTHOGONALCIRCLE_FTC2_H

CGAL_BEGIN_NAMESPACE

inline
Oriented_side
in_smallest_orthogonalcircleC2_SAF(
    const Static_filter_error &px,
    const Static_filter_error &py,
    const Static_filter_error &pw,
    const Static_filter_error &qx,
    const Static_filter_error &qy,
    const Static_filter_error &qw,
    const Static_filter_error &tx,
    const Static_filter_error &ty,
    const Static_filter_error &tw,
    double & epsilon_0)
{
  Static_filter_error dpx = px-qx;
  Static_filter_error dpy = py-qy;
  Static_filter_error dtx = tx-qx;
  Static_filter_error dty = ty-qy;
  Static_filter_error dpz = square(dpx)+square(dpy);
 
  return Oriented_side (sign_SAF((square(dtx)+square(dty)-tw+qw)*dpz
			     -(dpz-pw+qw)*(dpx*dtx+dpy*dty), epsilon_0));
}

inline
Oriented_side
in_smallest_orthogonalcircleC2_SAF(
    const Restricted_double &px,
    const Restricted_double &py,
    const Restricted_double &pw,
    const Restricted_double &qx,
    const Restricted_double &qy,
    const Restricted_double &qw,
    const Restricted_double &tx,
    const Restricted_double &ty,
    const Restricted_double &tw,
    const double & epsilon_0)
{
  Restricted_double dpx = px-qx;
  Restricted_double dpy = py-qy;
  Restricted_double dtx = tx-qx;
  Restricted_double dty = ty-qy;
  Restricted_double dpz = square(dpx)+square(dpy);
 
  return Oriented_side (sign_SAF((square(dtx)+square(dty)-tw+qw)*dpz
			     -(dpz-pw+qw)*(dpx*dtx+dpy*dty), epsilon_0));
}

inline
Oriented_side
in_smallest_orthogonalcircleC2(
    const Static_adaptatif_filter &px,
    const Static_adaptatif_filter &py,
    const Static_adaptatif_filter &pw,
    const Static_adaptatif_filter &qx,
    const Static_adaptatif_filter &qy,
    const Static_adaptatif_filter &qw,
    const Static_adaptatif_filter &tx,
    const Static_adaptatif_filter &ty,
    const Static_adaptatif_filter &tw)
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
        fabs(pw.value()) > SAF_bound ||
        fabs(qx.value()) > SAF_bound ||
        fabs(qy.value()) > SAF_bound ||
        fabs(qw.value()) > SAF_bound ||
        fabs(tx.value()) > SAF_bound ||
        fabs(ty.value()) > SAF_bound ||
        fabs(tw.value()) > SAF_bound)
      throw Restricted_double::unsafe_comparison();
    // Try the epsilon variant of the predicate.
    return in_smallest_orthogonalcircleC2_SAF(
		Restricted_double(px.value()),
		Restricted_double(py.value()),
		Restricted_double(pw.value()),
		Restricted_double(qx.value()),
		Restricted_double(qy.value()),
		Restricted_double(qw.value()),
		Restricted_double(tx.value()),
		Restricted_double(ty.value()),
		Restricted_double(tw.value()),
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
      SAF_bound = std::max(SAF_bound, fabs(pw.value()));
      SAF_bound = std::max(SAF_bound, fabs(qx.value()));
      SAF_bound = std::max(SAF_bound, fabs(qy.value()));
      SAF_bound = std::max(SAF_bound, fabs(qw.value()));
      SAF_bound = std::max(SAF_bound, fabs(tx.value()));
      SAF_bound = std::max(SAF_bound, fabs(ty.value()));
      SAF_bound = std::max(SAF_bound, fabs(tw.value()));

      // recompute epsilons: "just" call it over Static_filter_error.
      // That's the tricky part that might not work for everything.
      (void) in_smallest_orthogonalcircleC2_SAF(
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
    return in_smallest_orthogonalcircleC2(
		px.exact(),
		py.exact(),
		pw.exact(),
		qx.exact(),
		qy.exact(),
		qw.exact(),
		tx.exact(),
		ty.exact(),
		tw.exact());
  }
}

CGAL_END_NAMESPACE

#endif // CGAL_ARITHMETIC_FILTER_IN_SMALLEST_ORTHOGONALCIRCLE_FTC2_H
