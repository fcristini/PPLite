m4_define(`dnl', `m4_dnl')`'dnl
dnl This file is to generate CLASS.java.
dnl
dnl Include files defining macros that generate the non-fixed part.
m4_include(`ppl_interface_generator_java_classes_java_code.m4')dnl
m4_include(`ppl_interface_generator_common.m4')dnl
m4_include(`ppl_interface_generator_common_dat.m4')dnl
m4_include(`ppl_interface_generator_java_dat.m4')dnl
dnl
m4_divert(-1)dnl

dnl m4_pre_extra_class_code(Class, CPP_Class, Class_Kind)
dnl Prefix extra code for each class.
m4_define(`m4_pre_extra_class_code', `dnl
m4_define(`m4_this_class', `m4_interface_class$1')`'dnl
%<--%<--%<-- m4_this_class`'.java
package ppl_java;

public class m4_cplusplus_class$1 extends PPL_Object {`'dnl
m4_ifelse(m4_this_class, Polyhedron,
`

%<--%<--%<-- C_`'m4_this_class`'.java
package ppl_java;

public class C_`'m4_cplusplus_class$1 extends Polyhedron {

%<--%<--%<-- NNC_`'m4_this_class`'.java
package ppl_java;

public class NNC_`'m4_cplusplus_class$1 extends Polyhedron {
')`'dnl
m4_undefine(`m4_this_class')
')

%<--%<--%<-- m4_interface_class$1`'.java
public class m4_cplusplus_class$1 extends PPL_Object {

dnl m4_post_extra_class_code(Class, CPP_Class, Class_Kind)
dnl Postfix extra code for each class.
m4_define(`m4_post_extra_class_code', `dnl
m4_replace_all_patterns_in_string($1,
  m4_class_build_cpp_object1_code,
  m4_pattern_list)`'dnl
m4_replace_all_patterns_in_string($1,
  m4_class_build_cpp_object2_code,
  m4_pattern_list)`'dnl
m4_replace_all_patterns_in_string($1,
  m4_class_build_cpp_object3_code,
  m4_pattern_list)`'dnl
m4_define(`m4_this_class', `m4_interface_class$1')`'dnl
%<--%<--%<-- m4_this_class`'.java
}`'dnl
m4_ifelse(m4_this_class, Polyhedron,
`

%<--%<--%<-- C_`'m4_this_class`'.java
}

%<--%<--%<-- NNC_`'m4_this_class`'.java
}
')`'dnl
m4_undefine(`m4_this_class')
')

m4_divert`'dnl
dnl
dnl Generate the non-fixed part of the file.
m4_all_code`'dnl
dnl
dnl End of file generation.
