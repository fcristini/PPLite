m4_define(`dnl', `m4_dnl')`'dnl
m4_divert(-1)

dnl This m4 file generates the file Prolog_configured_interface.dox
dnl and Prolog_interface.dox

dnl Copyright (C) 2001-2008 Roberto Bagnara <bagnara@cs.unipr.it>
dnl
dnl This file is part of the Parma Polyhedra Library (PPL).
dnl
dnl The PPL is free software; you can redistribute it and/or modify it
dnl under the terms of the GNU General Public License as published by the
dnl Free Software Foundation; either version 3 of the License, or (at your
dnl option) any later version.
dnl
dnl The PPL is distributed in the hope that it will be useful, but WITHOUT
dnl ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
dnl FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
dnl for more details.
dnl
dnl You should have received a copy of the GNU General Public License
dnl along with this program; if not, write to the Free Software Foundation,
dnl Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02111-1307, USA.
dnl
dnl For the most up-to-date information see the Parma Polyhedra Library
dnl site: http://www.cs.unipr.it/ppl/ .

dnl FIXME: This should be in the main m4 generator file.

dnl -----------------------------------------------------------------
dnl Include the needed m4 files.
dnl -----------------------------------------------------------------
m4_include(`ppl_interface_generator_prolog_procedure_generators.m4')
m4_include(`ppl_interface_generator_prolog_dox_code.m4')

dnl Redefine m4_extension to allow for endings for the code which
dnl were defined to have a default value "_code" to change according to the
dnl category of predicates.
m4_define(`m4_extension',
  `m4_ifdef($1_`'m4_procedure_schema_ext,
            `m4_indir($1_`'m4_procedure_schema_ext)', `')
')

dnl The classes are fixed for the configuration independent manual.
m4_ifdef(`m4_configuration_independent', `dnl
m4_define(`m4_interface_classes_names',
 `Polyhedron@Pointset_Powerset_C_Polyhedron@Pointset_Powerset_NNC_Polyhedron')
m4_define(`m4_cplusplus_classes_names',
 `Polyhedron@Pointset_Powerset<C_Polyhedron>@Pointset_Powerset<NNC_Polyhedron>')')


dnl =================================================================
dnl The Preamble.
dnl =================================================================
dnl -----------------------------------------------------------------
dnl The preamble has a list of contents and needs a section name
dnl for each generated class.
dnl -----------------------------------------------------------------
dnl m4_one_class_code(Class)
m4_pushdef(`m4_one_class_code', `dnl
m4_define(`m4_current_ppl_domain', m4_interface_class`'$1)`'dnl
        - \ref m4_current_ppl_domain`'_predicates "Predicates for the m4_interface_class`'$1 Domain"
')

dnl -----------------------------------------------------------------
dnl Description of file and copyright notice
dnl -----------------------------------------------------------------
m4_divert`'dnl
/* m4_ifdef(`m4_configuration_independent',
  Configuration Independent Documentation for Prolog.,
  Configuration Dependent Documentation for Prolog.)
m4_include(`ppl_interface_generator_copyright')*/

dnl -----------------------------------------------------------------
dnl General Introduction
dnl -----------------------------------------------------------------
/*!
  \defgroup PPL_Prolog_interface Prolog Language Interface
  \brief
  The Parma Polyhedra Library comes equipped with an interface
  for the Prolog language.
*/

/*! \mainpage Prolog Language Interface

The Parma Polyhedra Library comes equipped with a Prolog interface.
Despite the lack of standardization of Prolog's foreign language interfaces,
the PPL Prolog interface supports several Prolog systems and, to the
extent this is possible, provides a uniform view of the library from
each such system.

The system-independent features of the library are described in
Section \ref PI_SI_Features "System-Independent Features".
Section \ref PI_Compilation "Compilation and Installation"
explains how the Prolog interface is compiled and installed.
Section \ref PI_SD_Features "System-Dependent Features"
illustrates the system-dependent features of the interface
for all the supported systems.

The structure of this section is as follows:
- \ref PI_SI_Features "System-Independent Features"
    - \ref Prolog_Interface_Overview "Overview"
    - \ref Predicate_Specifications "Predicate Specifications"
    - \ref predicate_descriptions "Predicate Descriptions"
        - \ref di_predicates "Domain Independent Predicates"
        - \ref mip_predicates "MIP Predicates"
m4_ifdef(`m4_configuration_independent', `dnl
        - \ref Polyhedron_predicates "Predicates for C Polyhedra"
        - \ref other_domains "Ad hoc Predicates for Other Domains"',
  `m4_all_code')
- \ref PI_Compilation "Compilation and Installation"
- \ref PI_SD_Features "System-Dependent Features"
    - \ref GNU_Prolog "GNU Prolog"
    - \ref CIAO_Prolog "CIAO Prolog"
    - \ref SICStus_Prolog "SICStus Prolog"
    - \ref SWI_Prolog "SWI Prolog"
    - \ref XSB_Prolog "XSB"
    - \ref YAP_Prolog "YAP"

In the sequel, <CODE>prefix</CODE> is the prefix under which
you have installed the library (typically <CODE>/usr</CODE>
or <CODE>/usr/local</CODE>).
m4_divert(-1)
m4_popdef(`m4_one_class_code')

dnl =================================================================
dnl SYSTEM and DOMAIN INDEPENDENT DOCUMENTATION.
dnl =================================================================
m4_divert`'dnl
m4_include(`ppl_prolog_sysindep_dox')
m4_divert(-1)

dnl =================================================================
dnl DOMAIN DEPENDENT DOCUMENTATION.
dnl =================================================================

dnl -----------------------------------------------------------------
dnl Initialize the class definitions
dnl as we do not use m4_all_code to generate the documentation,
dnl this must be done here.
dnl -----------------------------------------------------------------
m4_init_class_definitions


dnl -----------------------------------------------------------------
dnl For the documentation, the predicates for a single class are
dnl divinided into categories and then into subcategories.
dnl Each category and subcategory can have its own introduction.
dnl -----------------------------------------------------------------

dnl -----------------------------------------------------------------
dnl Define documentation for one subcategory.
dnl -----------------------------------------------------------------
m4_define(`m4_one_subcategory', `dnl
m4_define(`m4_procedure_schema_ext', m4_ext`'_doc)`'dnl
m4_echo_unquoted(m4_subcategory_`'m4_ext)
m4_ifdef(m4_interface_class`'$1,
`m4_patsubst(m4_one_class_code($1), @COMMA@, `,')`'dnl
')`'dnl
')

dnl -----------------------------------------------------------------
dnl Define the documentation for all categories for simple domains;
dnl -----------------------------------------------------------------
m4_define(`m4_all_simple_categories', `dnl
m4_category_constr_destr
m4_define(`m4_ext', build)`'dnl
m4_one_subcategory($1)`'dnl
m4_define(`m4_ext', convert)`'dnl
m4_one_subcategory($1)`'dnl
m4_define(`m4_ext', destruct)`'dnl
m4_one_subcategory($1)`'dnl
m4_category_const
m4_define(`m4_ext', testpoly)`'dnl
m4_one_subcategory($1)`'dnl
m4_define(`m4_ext', constpoly)`'dnl
m4_one_subcategory($1)`'dnl
m4_define(`m4_ext', dump)`'dnl
m4_one_subcategory($1)`'dnl
m4_category_nonconst
m4_define(`m4_ext', addto)`'dnl
m4_one_subcategory($1)`'dnl
m4_define(`m4_ext', trans)`'dnl
m4_one_subcategory($1)`'dnl
m4_define(`m4_ext', binop)`'dnl
m4_one_subcategory($1)`'dnl
m4_define(`m4_ext', widen)`'dnl
m4_one_subcategory($1)`'dnl
m4_category_varspace
m4_define(`m4_ext', concat)`'dnl
m4_one_subcategory($1)`'dnl
m4_define(`m4_ext', spacemod)`'dnl
m4_one_subcategory($1)`'dnl
')

dnl -----------------------------------------------------------------
dnl Define the documentation for extra categories for powerset domains;
dnl -----------------------------------------------------------------
m4_define(`m4_adhoc_pps_categories', `dnl
m4_category_pps
m4_define(`m4_ext', pps_iter)`'dnl
m4_one_subcategory($1)`'dnl
m4_define(`m4_ext', pps_other)`'dnl
m4_one_subcategory($1)`'dnl
')

dnl -----------------------------------------------------------------
dnl Documentation for one simple class.
dnl -----------------------------------------------------------------
m4_define(`m4_pre_extra_simple_class_code', `dnl
m4_define(`m4_current_ppl_domain', m4_interface_class`'$1)`'dnl
\anchor m4_current_ppl_domain`'_predicates
<H1>Predicates for the m4_current_topology m4_current_ppl_domain Domain</H1>
Here we provide a short description for each of the predicates
available for the domain of m4_current_topology m4_current_ppl_objects.
m4_ifdef(`m4_configuration_independent',
  `Note that predicates for other domains will follow a similar pattern.')

')
m4_define(`m4_post_extra_simple_class_code', `')

m4_define(`m4_one_simple_class_code', `dnl
m4_pre_extra_simple_class_code($1)`'dnl
m4_all_simple_categories($1)`'dnl
m4_post_extra_simple_class_code($1)`'dnl
')

dnl -----------------------------------------------------------------
dnl Additional documentation for a powerset class.
dnl -----------------------------------------------------------------
m4_define(`m4_pre_extra_adhoc_class_code', `dnl
m4_define(`m4_current_ppl_domain', m4_interface_class`'$1)`'dnl
\anchor other_domains
<H1>Ad hoc Predicates for Other Domains</H1>`'dnl
')
m4_define(`m4_post_extra_adhoc_class_code', `')

m4_define(`m4_one_adhoc_class_code', `dnl
m4_pre_extra_adhoc_class_code($1)`'dnl
m4_adhoc_pps_categories($1)`'dnl
m4_pushdef(`m4_subcategory_widen', `')`'dnl
m4_define(`m4_ext', widen)`'dnl
m4_one_subcategory($1)`'dnl
m4_popdef(`m4_subcategory_widen')`'dnl
m4_post_extra_adhoc_class_code($1)`'dnl
')

dnl m4_underscore_to_space(String)
dnl
dnl Changes an underscore to space and change to lowercase.
dnl Example: m4_underscore_to_space(`xyz_abc') ==> xyz abc
m4_define(`m4_underscore_to_space', `m4_translit(`$1', `_', ` ')')
m4_define(`m4_PPL_domain2text', `dnl
  m4_patsubst(m4_patsubst(m4_downcase(m4_underscore_to_space($1)),
                           ` c ', ` C '),
              ` nnc ', ` NNC ')')

dnl m4_plural(String)
dnl
dnl Very simple macro for making domains (lowercase) plural.
m4_define(`m4_plural', `dnl
m4_patsubst(m4_patsubst(m4_patsubst(m4_patsubst(m4_patsubst(m4_patsubst($1,
  polyhedron, polyhedra),
  grid, grids),
  shape, shapes),
  box, boxes),
  powerset, powersets),
  product, products)`'dnl
')

dnl =================================================================
dnl Now the generation of the documentation.
dnl =================================================================

dnl -----------------------------------------------------------------
dnl CONFIGURATION INDEPENDENT
dnl -----------------------------------------------------------------
m4_divert`'dnl
m4_ifdef(`m4_configuration_independent', `dnl
m4_define(`m4_current_ppl_domain', Polyhedron)`'dnl
m4_pushdef(`m4_class_alt_replacement', `polyhedron')`'dnl
m4_pushdef(`m4_Polyhedron_topology_replacement', `C_')`'dnl
m4_pushdef(`m4_Polyhedron_topology_alt_replacement', `C ')`'dnl
m4_pushdef(`m4_current_ppl_one_object', `polyhedron')`'dnl
m4_pushdef(`m4_current_ppl_objects', `polyhedra')`'dnl
m4_pushdef(`m4_current_ppl_group', `polyhedra')`'dnl
m4_pushdef(`m4_current_topology', `C')`'dnl
m4_patsubst(`m4_one_simple_class_code(1)', @COMMA@, `,')`'dnl
m4_popdef(`m4_Polyhedron_topology_replacement')`'dnl
m4_popdef(`m4_Polyhedron_topology_alt_replacement')`'dnl
m4_popdef(`m4_current_ppl_objects')`'dnl
m4_popdef(`m4_current_topology')`'dnl
m4_patsubst(`m4_one_adhoc_class_code(2)', @COMMA@, `,')`'dnl
')`'dnl
m4_divert(-1)

dnl -----------------------------------------------------------------
dnl CONFIGURATION DEPENDENT
dnl -----------------------------------------------------------------

dnl m4_all_classes_code(Class_Counter)
dnl
dnl Class_Counter   - The index for the current class;
dnl This iterates through the classes to generate the documentation.
m4_define(`m4_all_classes_doc', `dnl
dnl
dnl Check for class counter in range. If so, generate the documentation
dnl for the current class. If not finish.
dnl
m4_ifdef(m4_interface_class`'$1, `dnl
dnl
dnl First some temporary definitions.
dnl
m4_define(`m4_current_ppl_domain', m4_interface_class`'$1)`'dnl
m4_pushdef(`m4_class_alt_replacement', `dnl
m4_PPL_domain2text(m4_current_ppl_domain)')
m4_pushdef(`m4_current_topology', `')`'dnl
m4_pushdef(`m4_current_ppl_group', m4_class_group`'$1)`'dnl
m4_pushdef(`m4_current_ppl_kind', m4_class_kind`'$1)`'dnl
m4_pushdef(`m4_current_ppl_disjunct_kind', m4_class_body_kind`'$1)`'dnl
m4_define(`m4_disjunct_topology', `dnl
m4_upcase(m4_get_class_topology(m4_cplusplus_class_body$1))')`'dnl
m4_pushdef(`m4_current_ppl_one_object', `dnl
m4_PPL_domain2text(m4_current_ppl_kind)')
m4_pushdef(`m4_current_ppl_objects', `dnl
m4_ifelse(m4_current_ppl_group, box,
   m4_plural(m4_PPL_domain2text(m4_current_ppl_domain)),
          m4_current_ppl_group, pointset_powerset,
   pointset powersets of m4_plural(m4_PPL_domain2text(m4_disjunct_topology m4_current_ppl_disjunct_kind)),
  m4_plural(m4_PPL_domain2text(m4_current_ppl_kind)))')`'dnl
m4_pre_extra_simple_class_code($1)`'dnl
dnl
dnl Generate documentation for current class.
dnl
m4_all_simple_categories($1)`'dnl
m4_ifelse(m4_current_ppl_group,
  pointset_powerset, `m4_adhoc_pps_categories($1)')`'dnl
dnl
dnl Remove temporary definition.
dnl
m4_popdef(`m4_current_ppl_objects')`'dnl
m4_popdef(`m4_current_topology')`'dnl
m4_popdef(`m4_current_ppl_group')`'dnl
m4_popdef(`m4_current_ppl_kind')`'dnl
m4_popdef(`m4_current_ppl_disjunct_kind')`'dnl
m4_popdef(`m4_disjunct_topology')`'dnl
dnl
dnl Increment class counter and repeat.
dnl
m4_all_classes_doc(m4_incr($1))')`'dnl
')

dnl -----------------------------------------------------------------
dnl Generate the configuration dependent documentation
dnl -----------------------------------------------------------------
m4_divert`'dnl
m4_ifdef(`m4_configuration_independent', `',
  `m4_patsubst(`m4_all_classes_doc(1)', @COMMA@, `,')`'dnl
')`'dnl
m4_divert(-1)

dnl =================================================================
dnl SYSTEM DEPENDENT DOCUMENTATION.
dnl =================================================================
m4_divert`'dnl
m4_include(ppl_prolog_sysdep_dox)
dnl
dnl End of file generation.
