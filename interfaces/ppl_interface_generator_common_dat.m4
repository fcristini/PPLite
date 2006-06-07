dnl Classes to be implemented and C++ versions of these classes.
dnl These lines will be replaced by defintions
dnl generated by the configuration file.
define(`m4_interface_class_names', `Polyhedron@Grid@BD_Shape_int8_t')
define(`m4_cplusplus_class_names', `Polyhedron@Grid@BD_Shape<int8_t>')

dnl m4_class_group
dnl
dnl There are two class groups:
dnl GRID for all the grid-like classes,
dnl SHAPE for classes denoting subsets of a vector space that have some shape.
define(`m4_class_group',
  `ifelse($1, Grid, GRID, SHAPE)')

dnl class_super_group
dnl
dnl There is one class super_group:
dnl POINTS for classes defining some Domain based on sets of Points
dnl (ie grid and shape classes)
define(`m4_class_super_group', `POINTS')

dnl m4_pattern_list
dnl
dnl Returns a list of patterns (in lowercase) used for the generation
dnl of procedure names and code schemas.
define(`m4_pattern_list', `dnl
intopology,
topology,
represent,
dimension,
generator,
point,
constrainer,
state,
abovebelow,
maxmin,
embedproject,
affimage,
comparison,
binop,
binminop,
widenexp,
box,
describe')

dnl num_class_widenexps
dnl class_widenexp
dnl
dnl The widening and extrapolation operators.
define(`num_Polyhedron_widenexps', 2)
define(`Polyhedron_widenexp1', `BHRZ03')
define(`Polyhedron_widenexp2', `H79')
define(`num_Grid_widenexps', 2)
define(`Grid_widenexp1', `congruence')
define(`Grid_widenexp2', `generator')
dnl define(`Grid_widenexp3', `BDHMZ06')
define(`Grid_widenexp3', `')
define(`num_BD_Shape_widenexps',2)
define(`BD_Shape_widenexp1',`BHMZ05')
define(`BD_Shape_widenexp2',`H79')
dnl define(`BD_Shape_widenexp3',`CC76')
define(`num_Octagonal_Shape_widenexps',1)
define(`Octagonal_Shape_widenexp1',CH78)

dnl num_class_topologys
dnl class_topology
dnl
dnl Some classes can have a topology.
dnl The "_" only needed when topology exists.
define(`num_topologys', 1)
define(`topology1', `')
define(`num_Polyhedron_topologys', 2)
define(`Polyhedron_topology1', `C_')
define(`Polyhedron_topology2', `NNC_')
define(`num_intopologys', 1)
define(`intopology1', `')
define(`num_Polyhedron_intopologys', 2)
define(`Polyhedron_intopology1', `C_')
define(`Polyhedron_intopology2', `NNC_')

dnl num_class_boxs
dnl class_box
dnl
dnl The shape classes have bounding boxes while the grid classes also
dnl have covering boxes.
define(`num_boxs', 1)
define(`box1', `bounding_box')
define(`num_Grid_boxs', 2)
define(`Grid_box2', `covering_box')
define(`alt_Grid_box1', `shrink_bounding_box')
define(`alt_Grid_box2', `get_covering_box')

dnl num_class_dimensions
dnl class_dimension
dnl
dnl  space or affine dimensions
define(`num_dimensions', 2)
define(`dimension1', `space_dimension')
define(`dimension2', `affine_dimension')

dnl num_class_generators
dnl class_generator
dnl
dnl The different kinds of objects use to generate a class.
define(`num_generators', 1)
define(`generator1', `generator')
define(`Grid_generator1', `grid_generator')

dnl num_class_points
dnl class_point
dnl
dnl  The different kinds of points.
define(`num_points', 1)
define(`point1', `point')
define(`Grid_point1', `grid_point')

dnl num_class_constrainers
dnl class_constrainer
dnl
dnl  The constrainer objects used to define a class.
define(`num_constrainers', 1)
define(`constrainer1', `constraint')
define(`Grid_constrainer1', `congruence')

dnl num_class_represents
dnl class_represent?
dnl
dnl  The different kinds of objects use to construct a class.
define(`num_represents', 2)
define(`represent1', `constraint')
define(`represent2', `generator')
define(`num_Grid_represents', 3)
define(`Grid_represent2', `grid_generator')
define(`alt_Grid_represent2', `generator')
define(`Grid_represent3', `congruence')
define(`num_BD_Shape_represents', 1)
define(`num_Octagonal_Shape_represents', 1)


dnl num_class_describes
dnl class_describe
dnl
dnl  The different kinds of objects use to describe a class.
define(`num_describes', 2)
define(`describe1', `constraint')
define(`describe2', `generator')
define(`num_Grid_describe', 2)
define(`Grid_describe1', `congruence')
define(`Grid_describe2', `grid_generator')
define(`alt_Grid_describe2', `generator')
define(`num_BD_Shape_describes', 1)
define(`num_Octagonal_Shape_describes', 1)

dnl num_class_states
dnl class_State
dnl
dnl  the "is" predicates
define(`num_states', 4)
define(`state1', `empty')
define(`state2', `universe')
define(`state3', `bounded')
define(`state4', `topologically_closed')
define(`num_BD_Shape_states', 3)
define(`num_Grid_states', 5)
define(`Grid_state5', `discrete')

dnl num_class_bounds
dnl class_bounds
dnl
dnl  above or below
define(`num_abovebelows', 2)
define(`abovebelow1', `above')
define(`abovebelow2', `below')

dnl num_class_maxmins
dnl class_maxmin
dnl
dnl  Maximize or Minimize
define(`num_maxmins', 2)
define(`maxmin1', `maximize')
define(`maxmin2', `minimize')

dnl num_class_embedprojects
dnl class_embedproject
dnl
dnl  Embed or project
define(`num_embedprojects', 2)
define(`embedproject1', `and_embed')
define(`embedproject2', `and_project')

dnl num_class_affimages
dnl class_affimage
dnl
dnl  affine_image or affine_preimage
define(`num_affimages', 2)
define(`affimage1', `affine_image')
define(`affimage2', `affine_preimage')

dnl num_class_comparisons
dnl class_comparison
dnl
dnl  One object can be contained, strictly contained or disjoint in the other.
define(`num_comparisons', 3)
define(`comparison1', `contains')
define(`comparison2', `strictly_contains')
define(`comparison3', `is_disjoint_from')

dnl num_class_binops
dnl class_binop
dnl
dnl  The different kinds of binary operators.
define(`num_binops', 5)
define(`binop1', `intersection_assign')
define(`binop2', `upper_bound_assign')
define(`binop3', `difference_assign')
define(`binop4', `concatenate_assign')
define(`binop5', `time_elapse_assign')
define(`num_Polyhedron_binops', 7)
define(`Polyhedron_binop6', `poly_hull_assign')
define(`Polyhedron_binop7', `poly_difference_assign')
define(`num_BD_Shape_binops', 6)
define(`BD_Shape_binop6', `bds_hull_assign')
define(`num_Octagonal_Shape_binops', 6)
define(`Octagonal_Shape_binop6', `oct_hull_assign')
define(`num_Grid_binops', 6)
define(`Grid_binop6', `join_assign')

dnl num_class_binminops
dnl class_binminop
dnl
dnl  The different kinds of "and_minimize" binary operators.
define(`num_binminops', 1)
define(`binminop1', `intersection_assign_and_minimize')
define(`num_Polyhedron_binminops', 2)
define(`Polyhedron_binminop2', `poly_hull_assign_and_minimize')
define(`num_Grid_binminops', 2)
define(`Grid_binminop2', `join_assign_and_minimize')
