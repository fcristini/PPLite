#include "ppl_install.hh"
#include <iostream>
#include <stdexcept>

using namespace std;
using namespace Parma_Polyhedra_Library;

#define NOISY 0

int main() {
  Variable x(0);
  Variable y(1);
  Polyhedron p1;
  Polyhedron p2(2);
  p2.insert(vertex(x + y));
  try {
    p2.convex_hull_assign(p1);
  }
  catch (std::invalid_argument& e) {
#if NOISY
    cout << "invalid_argument: " << e.what() << endl;
#endif
    exit(0);
  }
  catch (...) {
    exit(1);
  }

  // Should not get here.
  return 1;
}

