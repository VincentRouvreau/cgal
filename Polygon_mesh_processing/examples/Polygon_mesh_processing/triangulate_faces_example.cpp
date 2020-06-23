#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Surface_mesh.h>

#include <CGAL/Polygon_mesh_processing/triangulate_faces.h>
#include <CGAL/Polygon_mesh_processing/IO/polygon_mesh_io.h>

#include <CGAL/boost/graph/helpers.h>

#include <fstream>
#include <iostream>

typedef CGAL::Exact_predicates_inexact_constructions_kernel Kernel;
typedef Kernel::Point_3                                     Point;
typedef CGAL::Surface_mesh<Point>                           Surface_mesh;

namespace PMP = CGAL::Polygon_mesh_processing;

int main(int argc, char* argv[])
{
  const char* filename = (argc > 1) ? argv[1] : "data/P.off";
  const char* outfilename = (argc > 2) ? argv[2] : "P_tri.off";

  Surface_mesh mesh;
  if(!PMP::read_polygon_mesh(filename, mesh))
  {
    std::cerr << "Invalid input." << std::endl;
    return 1;
  }

  PMP::triangulate_faces(mesh);

  // Confirm that all faces are triangles.
  for(boost::graph_traits<Surface_mesh>::face_descriptor f : faces(mesh))
    if(!CGAL::is_triangle(halfedge(f, mesh), mesh))
      std::cerr << "Error: non-triangular face left in mesh." << std::endl;

  std::ofstream cube_off(outfilename);
  cube_off.precision(17);
  cube_off << mesh;

  return 0;
}
