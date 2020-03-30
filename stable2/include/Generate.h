// interface definition for module Generate
#ifndef CLAIREH_Generate
#define CLAIREH_Generate

  
class CL_EXPORT Generate_producer;
class CL_EXPORT Generate_c_producer;

class CL_EXPORT Generate_producer: public thing{ 
    public:
       list *open_comparators;
       list *open_operators;
       OID body;
       char *extension;
       char *comment;
       list *interfaces;
       CL_INT stat;}
  ;

class CL_EXPORT Generate_c_producer: public Generate_producer{ 
    public:
       list *bad_names;
       list *good_names;}
  ;
extern CL_EXPORT void  ident_symbol(symbol *v46356);
extern CL_EXPORT void  ident_thing(thing *v46356);
extern CL_EXPORT void  ident_class(ClaireClass *v46356);
extern CL_EXPORT void  interface_I_class(ClaireClass *v12187);
extern CL_EXPORT void  class_princ_class(ClaireClass *v12187);
extern CL_EXPORT OID  indent_c_void();
extern CL_EXPORT OID  breakline_void();
extern CL_EXPORT void  new_block_void();
extern CL_EXPORT void  close_block_void();
extern CL_EXPORT void  c_test_any(OID v12208);
extern CL_EXPORT void  c_test_method(method *v12197);
extern CL_EXPORT void  compile_module(module *v46356);
extern CL_EXPORT void  generate_files_module(module *v46356);
extern CL_EXPORT void  generate_f2f_module(module *v12197);
extern CL_EXPORT void  generate_file_string1(char *v12203,module *v12197);
extern CL_EXPORT void  generate_classes_module(module *v46356);
extern CL_EXPORT void  generate_c2f_module(module *v46356);
extern CL_EXPORT void  generate_interface_module(module *v46356,bag *v12196);
extern CL_EXPORT void  generate_objects_module(module *v46356);
extern CL_EXPORT void  generate_meta_load_module(module *v46356);
extern CL_EXPORT ClaireBoolean * global_var_def_ask_any(OID v12208);
extern CL_EXPORT ClaireClass * getRange_global_variable(global_variable *v12208);
extern CL_EXPORT void  generate_functions_module(module *v46356);
extern CL_EXPORT list * parents_module(module *v46356,list *v12196);
extern CL_EXPORT list * parents_list(list *v46356);
extern CL_EXPORT void  get_module2(module *v12197);
extern CL_EXPORT void  generate_file_string2(char *v46356,char *v50260);
extern CL_EXPORT void  generate_wcl_file_string(char *v46356,char *v59452,char *v50260);
extern CL_EXPORT OID  make_c_function_lambda_Generate(lambda *v46356,char *v25167,OID v12197);
extern CL_EXPORT OID  print_c_function_lambda2(lambda *v46356,char *v25167,OID v12197);
extern CL_EXPORT void  print_body_If(If *v29311,char *v16478,ClaireClass *v12203,If *v3118,ClaireBoolean *v40159);
extern CL_EXPORT void  print_body_any(OID v29311,char *v16478,ClaireClass *v12203,OID v3118,ClaireBoolean *v40159);
extern CL_EXPORT OID  print_body_Do(Do *v29311,char *v16478,ClaireClass *v12203,OID v3118,ClaireBoolean *v40159);
extern CL_EXPORT void  outer_statement_any(OID v29311,char *v16478,ClaireClass *v12203,ClaireBoolean *v40159);
extern CL_EXPORT ClaireBoolean * c_safe_any(OID v12208);
extern CL_EXPORT ClaireClass * check_sort_method(method *v46356);
extern CL_EXPORT OID  typed_args_list_list(list *v46356);
extern CL_EXPORT void  get_dependents_method(method *v12197);
extern CL_EXPORT void  c_princ_function(ClaireFunction *v46356);
extern CL_EXPORT void  set_outfile_lambda(lambda *v46356);
extern CL_EXPORT ClaireBoolean * c_func_any(OID v46356);
extern CL_EXPORT void  expression_thing(thing *v46356,OID v44140);
extern CL_EXPORT void  expression_integer(CL_INT v46356,OID v44140);
extern CL_EXPORT void  expression_any(OID v46356,OID v44140);
extern CL_EXPORT void  expression_string(char *v46356,OID v44140);
extern CL_EXPORT void  expression_float(double v46356,OID v44140);
extern CL_EXPORT void  expression_float_(OID v22632,OID v22633);
extern CL_EXPORT void  expression_boolean(ClaireBoolean *v46356,OID v44140);
extern CL_EXPORT void  expression_environment(ClaireEnvironment *v46356,OID v44140);
extern CL_EXPORT void  expression_Variable(Variable *v46356,OID v44140);
extern CL_EXPORT void  expression_global_variable(global_variable *v46356,OID v44140);
extern CL_EXPORT void  expression_Set(Set *v46356,OID v44140);
extern CL_EXPORT void  expression_set2(set *v46356,OID v44140);
extern CL_EXPORT void  expression_Tuple(Tuple *v46356,OID v44140);
extern CL_EXPORT void  expression_tuple(tuple *v46356,OID v44140);
extern CL_EXPORT void  expression_List(List *v46356,OID v44140);
extern CL_EXPORT void  expression_list(list *v46356,OID v44140);
extern CL_EXPORT void  expression_Call2(Call *v46356,OID v44140);
extern CL_EXPORT void  expression_Call_method12(Call_method1 *v46356,OID v44140);
extern CL_EXPORT void  expression_Call_method22(Call_method2 *v46356,OID v44140);
extern CL_EXPORT void  expression_Call_method2(Call_method *v46356,OID v44140);
extern CL_EXPORT void  bexpression_any(OID v46356,OID v44140);
extern CL_EXPORT void  expression_If(If *v46356,OID v44140);
extern CL_EXPORT void  expression_Assign(Assign *v46356,OID v44140);
extern CL_EXPORT void  expression_to_protect(Compile_to_protect *v46356,OID v44140);
extern CL_EXPORT char * gc_protect_class(ClaireClass *v12187);
extern CL_EXPORT void  expression_Gassign(Gassign *v46356,OID v44140);
extern CL_EXPORT void  expression_And(And *v46356,OID v44140);
extern CL_EXPORT void  expression_Or(Or *v46356,OID v44140);
extern CL_EXPORT void  expression_to_CL(Compile_to_CL *v46356,OID v44140);
extern CL_EXPORT void  expression_to_C(Compile_to_C *v46356,OID v44140);
extern CL_EXPORT void  expression_C_cast(Compile_C_cast *v46356,OID v44140);
extern CL_EXPORT void  expression_Call_slot(Call_slot *v46356,OID v44140);
extern CL_EXPORT void  expression_Call_table(Call_table *v46356,OID v44140);
extern CL_EXPORT void  expression_Call_array(Call_array *v46356,OID v44140);
extern CL_EXPORT void  expression_Update(Update *v46356,OID v44140);
extern CL_EXPORT void  sign_equal_boolean(ClaireBoolean *v46356);
extern CL_EXPORT void  sign_or_boolean(ClaireBoolean *v46356);
extern CL_EXPORT void  bool_exp_any_Generate(OID v46356,ClaireBoolean *v32308,OID v44140);
extern CL_EXPORT void  any_bool_exp_any(OID v46356,ClaireBoolean *v32308,OID v44140,ClaireBoolean *v24838);
extern CL_EXPORT void  bool_exp_to_CL_Generate(Compile_to_CL *v46356,ClaireBoolean *v32308,OID v44140);
extern CL_EXPORT void  bool_exp_If_Generate(If *v46356,ClaireBoolean *v32308,OID v44140);
extern CL_EXPORT void  bool_exp_And_Generate(And *v46356,ClaireBoolean *v32308,OID v44140);
extern CL_EXPORT void  bool_exp_Or_Generate(Or *v46356,ClaireBoolean *v32308,OID v44140);
extern CL_EXPORT void  bool_exp_Call_method1_Generate(Call_method1 *v46356,ClaireBoolean *v32308,OID v44140);
extern CL_EXPORT void  bool_exp_Call_method2_Generate(Call_method2 *v46356,ClaireBoolean *v32308,OID v44140);
extern CL_EXPORT ClaireBoolean * bool_exp_ask_any(OID v12208);
extern CL_EXPORT void  args_list_bag(bag *v46356,OID v44140,ClaireBoolean *v48718);
extern CL_EXPORT char * check_var_string(char *v46356,OID v12203,OID v44140);
extern CL_EXPORT Variable * build_Variable_string(char *v12203,OID v12204);
extern CL_EXPORT list * unfold_args_list(list *v12196);
extern CL_EXPORT ClaireType * c_type_sort_any(OID v12208);
extern CL_EXPORT OID  unfold_arg_list(list *v12196,list *v50496,OID v12208);
extern CL_EXPORT void  unfold_use_list(list *v33249,OID v12208,OID v12203,OID v44140);
extern CL_EXPORT void  statement_any(OID v46356,OID v12203,OID v44140);
extern CL_EXPORT void  self_statement_Construct(Construct *v46356,OID v12203,OID v44140);
extern CL_EXPORT void  self_statement_If(If *v46356,OID v12203,OID v44140);
extern CL_EXPORT void  self_statement_Do(Do *v46356,OID v12203,OID v44140);
extern CL_EXPORT void  inner_statement_any(OID v46356,OID v12203,OID v44140);
extern CL_EXPORT void  self_statement_Let(Let *v46356,OID v12203,OID v44140);
extern CL_EXPORT void  self_statement_And(And *v46356,OID v12203,OID v44140);
extern CL_EXPORT void  self_statement_Or(Or *v46356,OID v12203,OID v44140);
extern CL_EXPORT void  self_statement_While(While *v46356,OID v12203,OID v44140);
extern CL_EXPORT void  self_statement_Assign(Assign *v46356,OID v12203,OID v44140);
extern CL_EXPORT void  self_statement_Gassign(Gassign *v46356,OID v12203,OID v44140);
extern CL_EXPORT void  self_statement_to_protect(Compile_to_protect *v46356,OID v12203,OID v44140);
extern CL_EXPORT void  self_statement_For(For *v46356,OID v12203,OID v44140);
extern CL_EXPORT void  self_statement_Iteration(Iteration *v46356,OID v12203,OID v44140);
extern CL_EXPORT void  self_statement_Return(Return *v46356,OID v12203,OID v44140);
extern CL_EXPORT void  self_statement_Call(Call *v46356,OID v12203,OID v44140);
extern CL_EXPORT void  self_statement_Call_method(Call_method *v46356,OID v12203,OID v44140);
extern CL_EXPORT void  self_statement_Call_method1(Call_method1 *v46356,OID v12203,OID v44140);
extern CL_EXPORT void  self_statement_Call_method2(Call_method2 *v46356,OID v12203,OID v44140);
extern CL_EXPORT void  self_statement_Super(Super *v46356,OID v12203,OID v44140);
extern CL_EXPORT void  self_statement_Cast(Cast *v46356,OID v12203,OID v44140);
extern CL_EXPORT void  self_statement_Handle(ClaireHandle *v46356,OID v12203,OID v44140);
extern CL_EXPORT void  self_statement_to_CL(Compile_to_CL *v46356,OID v12203,OID v44140);
extern CL_EXPORT void  self_statement_to_C(Compile_to_C *v46356,OID v12203,OID v44140);
extern CL_EXPORT void  self_statement_C_cast(Compile_C_cast *v46356,OID v12203,OID v44140);
extern CL_EXPORT void  self_statement_Call_slot(Call_slot *v46356,OID v12203,OID v44140);
extern CL_EXPORT void  self_statement_Call_table(Call_table *v46356,OID v12203,OID v44140);
extern CL_EXPORT void  self_statement_Call_array(Call_array *v46356,OID v12203,OID v44140);
extern CL_EXPORT void  self_statement_Update(Update *v46356,OID v12203,OID v44140);
extern CL_EXPORT char * c_string_c_producer1(Generate_c_producer *v12187,Variable *v46356);
extern CL_EXPORT char * c_string_c_producer2(Generate_c_producer *v12187,symbol *v46356);
extern CL_EXPORT char * string_I_c_producer1(Generate_c_producer *v12187,Variable *v46356);
extern CL_EXPORT char * string_I_c_producer2(Generate_c_producer *v12187,symbol *v46356);
extern CL_EXPORT void  ident_c_producer3(Generate_c_producer *v12187,Variable *v12206);
extern CL_EXPORT void  ident_c_producer(Generate_c_producer *v12187,symbol *v12203);
extern CL_EXPORT void  class_princ_c_producer(Generate_c_producer *v12187,ClaireClass *v46356);
extern CL_EXPORT void  produce_c_producer2(Generate_c_producer *v12187,OID v12208);
extern CL_EXPORT void  globalVar_c_producer(Generate_c_producer *v12187,global_variable *v12208);
extern CL_EXPORT void  stat_exp_c_producer(Generate_c_producer *v12187,OID v46356,OID v44140);
extern CL_EXPORT void  namespace_I_c_producer(Generate_c_producer *v12187,module *v12197);
extern CL_EXPORT void  module_I_c_producer(Generate_c_producer *v12187,module *v12197);
extern CL_EXPORT void  declare_c_producer(Generate_c_producer *v12187,property *v12200);
extern CL_EXPORT void  start_module_interface_c_producer(Generate_c_producer *v12187,module *v46356);
extern CL_EXPORT void  end_module_interface_c_producer(Generate_c_producer *v12187,module *v46356);
extern CL_EXPORT void  generate_end_file_c_producer(Generate_c_producer *v12194,module *v12197);
extern CL_EXPORT void  generate_classes_c_producer(Generate_c_producer *v12194,char *v12203,module *v12197);
extern CL_EXPORT void  generate_start_file_c_producer(Generate_c_producer *v12187,module *v12197);
extern CL_EXPORT void  generate_meta_load_c_producer(Generate_c_producer *v12187,module *v12197);
extern CL_EXPORT OID  start_file_string(char *v12203,module *v12197);
extern CL_EXPORT void  define_variable_c_producer2(Generate_c_producer *v12187,ClaireClass *v12204,char *v12206);
extern CL_EXPORT void  generate_profile_c_producer(Generate_c_producer *v12187,OID v12197);
extern CL_EXPORT void  generate_interface_c_producer(Generate_c_producer *v12187,module *v46356);
extern CL_EXPORT void  global_var_def_I_c_producer(Generate_c_producer *v12187,module *v46356,Let *v12208);
extern CL_EXPORT OID  gc_usage_any(OID v46356,ClaireBoolean *v44140);
extern CL_EXPORT OID  gc_or_any(OID v12208,OID v12209);
extern CL_EXPORT OID  gc_usage_star_list(list *v12196,ClaireBoolean *v44140);
extern CL_EXPORT char * protect_result_c_producer(Generate_c_producer *v12187,ClaireClass *v12203,ClaireBoolean *v32348,OID v12208);
extern CL_EXPORT void  generate_function_start_c_producer(Generate_c_producer *v12187,lambda *v46356,ClaireClass *v12203,OID v12197,char *v25167);
extern CL_EXPORT void  generate_regular_function_c_producer(Generate_c_producer *v12187,lambda *v46356,ClaireFunction *v48297,ClaireClass *v12203,OID v12197,list *v50514);
extern CL_EXPORT void  generate_float_function_c_producer(Generate_c_producer *v12187,method *v12197,char *v25167);
extern CL_EXPORT void  at_c_producer(Generate_c_producer *v12187);
extern CL_EXPORT void  generate_tuple_function_c_producer(Generate_c_producer *v12187,method *v12197,char *v25167);
extern CL_EXPORT OID  create_function_entry_c_producer(Generate_c_producer *v12187,lambda *v50494,char *v48297,OID v12197);
extern CL_EXPORT OID  update_function_entry_c_producer(Generate_c_producer *v12187,ClaireFunction *v48297,list *v50514,ClaireClass *v12203);
extern CL_EXPORT char * c_interface_class1_Generate(ClaireClass *v46356);
extern CL_EXPORT void  c_interface_class2_Generate(ClaireClass *v46356,char *v12203);
extern CL_EXPORT void  c_interface_method_Generate(method *v46356);
extern CL_EXPORT void  interface_I_c_producer(Generate_c_producer *v12187,ClaireClass *v46356);
extern CL_EXPORT void  to_cl_c_producer(Generate_c_producer *v12187,OID v12208,ClaireClass *v12203,OID v44140);
extern CL_EXPORT void  to_c_c_producer1(Generate_c_producer *v12187,OID v12208,ClaireClass *v12203,OID v44140);
extern CL_EXPORT void  to_c_c_producer2(Generate_c_producer *v12187,ClaireClass *v12203);
extern CL_EXPORT void  public_static_c_producer(Generate_c_producer *v12187);
extern CL_EXPORT void  bool_exp_I_c_producer(Generate_c_producer *v12187,OID v46356,OID v44140);
extern CL_EXPORT void  inherit_exp_c_producer(Generate_c_producer *v12187,OID v50104,OID v50105,OID v44140);
extern CL_EXPORT void  bitvector_exp_c_producer(Generate_c_producer *v12187,OID v50104,OID v50105,OID v44140);
extern CL_EXPORT void  equal_exp_c_producer(Generate_c_producer *v12187,OID v50104,ClaireBoolean *v32308,OID v50105,OID v55228);
extern CL_EXPORT ClaireBoolean * char_exp_ask_c_producer2(Generate_c_producer *v12187,OID v12208);
extern CL_EXPORT void  char_exp_c_producer2(Generate_c_producer *v12187,OID v12208,OID v44140);
extern CL_EXPORT void  c_member_c_producer(Generate_c_producer *v12187,OID v46356,ClaireClass *v12203,property *v12208,OID v44140);
extern CL_EXPORT void  addFast_c_producer(Generate_c_producer *v12187);
extern CL_EXPORT void  cast_I_c_producer(Generate_c_producer *v12187,Compile_C_cast *v46356,OID v44140);
extern CL_EXPORT void  gc_protection_exp_c_producer(Generate_c_producer *v12187,Variable *v12206,ClaireBoolean *v40842,OID v12205,OID v44140);
extern CL_EXPORT void  bag_expression_c_producer(Generate_c_producer *v50237,ClaireClass *v12187,bag *v12196,ClaireType *v12204,OID v44140);
extern CL_EXPORT void  generate_s_file_string(char *v46356,list *v12196,OID v12197);
extern CL_EXPORT void  create_load_modules_string(char *v46356,PortObject *v12200,list *v1140,OID v12197);
extern CL_EXPORT void  create_dynload_module_module1(module *v12208);
extern CL_EXPORT void  methods_interface_c_producer(Generate_c_producer *v12187,ClaireClass *v12208);
extern CL_EXPORT void  methods_bodies_c_producer(Generate_c_producer *v12187,ClaireClass *v12208);
extern CL_EXPORT void  inline_exp_c_producer1(Generate_c_producer *v12187,Call_method1 *v46356,OID v44140);
extern CL_EXPORT void  inline_exp_c_producer2(Generate_c_producer *v12187,Call_method2 *v46356,OID v44140);
extern CL_EXPORT void  inline_exp_c_producer3(Generate_c_producer *v12187,Call_method *v46356,OID v44140);
extern CL_EXPORT void  print_external_call_c_producer(Generate_c_producer *v12187,Call_method *v46356,OID v44140);
extern CL_EXPORT void  inline_exp_c_producer5(Generate_c_producer *v12187,Call *v46356,OID v44140);
extern CL_EXPORT ClaireBoolean * fcall_ask_Call2_Generate(Call *v12208);
extern CL_EXPORT list * get_restrictions_Call2(Call *v12208,list *v50512);
extern CL_EXPORT void  fcall_exp_Call2_Generate(Call *v12208,OID v44140);
extern CL_EXPORT void  c_sorted_arg_any(OID v12208,ClaireClass *v12203,OID v44140,ClaireBoolean *v46108);
extern CL_EXPORT void  c_sorted_args_Call(Call *v12208,list *v50511,OID v44140,ClaireBoolean *v46108);
extern CL_EXPORT void  bitvector_I_c_producer(Generate_c_producer *v12187,OID v12208);
extern CL_EXPORT void  bitvectorSum_integer(CL_INT v12208);
extern CL_EXPORT void  signature_I_c_producer(Generate_c_producer *v12187,OID v12208);
extern CL_EXPORT OID  getC_any(OID v12208);
extern CL_EXPORT void  gassign_c_producer(Generate_c_producer *v12187,Gassign *v46356,OID v44140);
extern CL_EXPORT void  call_slot_c_producer(Generate_c_producer *v12187,Call_slot *v46356,OID v44140);
extern CL_EXPORT void  call_table_c_producer(Generate_c_producer *v12187,Call_table *v46356,OID v44140);
extern CL_EXPORT void  call_array_c_producer(Generate_c_producer *v12187,Call_array *v46356,OID v44140);
extern CL_EXPORT void  update_c_producer(Generate_c_producer *v12187,Update *v46356,OID v44140);
extern CL_EXPORT void  object_test_c_producer(Generate_c_producer *v12187,OID v50104,ClaireBoolean *v32308,OID v44140);
extern CL_EXPORT void  exp_to_protect_c_producer(Generate_c_producer *v12187,Compile_to_protect *v46356,OID v44140);
extern CL_EXPORT void  macro_c_producer(Generate_c_producer *v12187);
extern CL_EXPORT void  init_var_c_producer(Generate_c_producer *v12187,ClaireClass *v12203);
extern CL_EXPORT void  any_interface_c_producer(Generate_c_producer *v12187);
extern CL_EXPORT void  pointer_cast_c_producer(Generate_c_producer *v12187,ClaireClass *v12203);
extern CL_EXPORT void  exp_Assign_c_producer(Generate_c_producer *v12187,Assign *v46356,OID v44140);
extern CL_EXPORT void  stat_handle_c_producer(Generate_c_producer *v12187,ClaireHandle *v46356,OID v12203,OID v44140);
extern CL_EXPORT void  stat_construct_c_producer(Generate_c_producer *v12187,Construct *v46356,OID v12203,OID v44140);
extern CL_EXPORT void  stat_while_c_producer(Generate_c_producer *v12187,While *v46356,OID v12203,OID v44140);
extern CL_EXPORT void  stat_gassign_c_producer(Generate_c_producer *v12187,Gassign *v46356,OID v12203,OID v44140);
extern CL_EXPORT void  stat_for_c_producer(Generate_c_producer *v12187,For *v46356,OID v12203,OID v44140);
extern CL_EXPORT void  stat_iteration_c_producer(Generate_c_producer *v12187,Iteration *v46356,OID v12203,OID v44140);
extern CL_EXPORT void  stat_super_c_producer(Generate_c_producer *v12187,Super *v46356,OID v12203,OID v44140);
extern CL_EXPORT void  stat_let_c_producer(Generate_c_producer *v12187,Let *v46356,OID v12203,OID v44140);
extern CL_EXPORT char * external_I_module1(module *v12197);
extern CL_EXPORT module * string2module_string1(char *v12203);
extern CL_EXPORT char * home_path_void1();
extern CL_EXPORT void  function_compile_string1(char *v46356,char *v32610);
extern CL_EXPORT char * libpath_void1();
extern CL_EXPORT void  libpath_I_module1(module *v12197);
extern CL_EXPORT void  headers_I_void1();
extern CL_EXPORT void  lib_I_any1(OID v12197,list *v12196);
extern CL_EXPORT void  importlib_I_any1(OID v12197,list *v12196);
extern CL_EXPORT void  files_I_any1(OID v12197,ClaireBoolean *v8893,char *v26321);
extern CL_EXPORT char * job_option_void1();
extern CL_EXPORT void  cmakefile_any1(OID v12197,char *v61574);
extern CL_EXPORT void  create_makefile_nt_any1(OID v12197,char *v61574,list *v12196);
extern CL_EXPORT void  create_makefile_unix_any1(OID v12197,char *v61574,list *v12196);
extern CL_EXPORT void  ensure_module_directories_exist_void1();
extern CL_EXPORT void  new_module_list1(list *v12196);
extern CL_EXPORT void  rcopy_string1(char *v50324,char *v50760);
extern CL_EXPORT void  export_module_boolean1(ClaireBoolean *v40842);
extern CL_EXPORT char * relayed_params_void1();
extern CL_EXPORT void  compile_module_libs_void1();
extern CL_EXPORT void  compile_all_module_libs_void1();
extern CL_EXPORT void  module_list_list1(list *v12196);
extern CL_EXPORT void  module_info_list1(list *v12196);
extern CL_EXPORT void  list_fcall_void1();
extern CL_EXPORT tuple * option_usage_string16_Generate(char *v61419);
extern CL_EXPORT tuple * option_usage_string16_Generate_(char *v23624);
extern CL_EXPORT void  option_respond_string15_Generate(char *v61419,list *v12196);
extern CL_EXPORT tuple * option_usage_string17_Generate(char *v61419);
extern CL_EXPORT tuple * option_usage_string17_Generate_(char *v23625);
extern CL_EXPORT void  option_respond_string16_Generate(char *v61419,list *v12196);
extern CL_EXPORT tuple * option_usage_string18_Generate(char *v61419);
extern CL_EXPORT tuple * option_usage_string18_Generate_(char *v23627);
extern CL_EXPORT void  option_respond_string17_Generate(char *v61419,list *v12196);
extern CL_EXPORT tuple * option_usage_string19_Generate(char *v61419);
extern CL_EXPORT tuple * option_usage_string19_Generate_(char *v23628);
extern CL_EXPORT void  option_respond_string18_Generate(char *v61419,list *v12196);
extern CL_EXPORT void  option_respond_string19_Generate(char *v61419,list *v12196);
extern CL_EXPORT tuple * option_usage_string20_Generate(char *v61419);
extern CL_EXPORT tuple * option_usage_string20_Generate_(char *v23629);
extern CL_EXPORT void  option_respond_string20_Generate(char *v61419,list *v12196);
extern CL_EXPORT tuple * option_usage_string21_Generate(char *v61419);
extern CL_EXPORT tuple * option_usage_string21_Generate_(char *v23630);
extern CL_EXPORT void  option_respond_string21_Generate(char *v61419,list *v12196);
extern CL_EXPORT void  option_respond_string22_Generate(char *v61419,list *v12196);
extern CL_EXPORT tuple * option_usage_string22_Generate(char *v61419);
extern CL_EXPORT tuple * option_usage_string22_Generate_(char *v23652);
extern CL_EXPORT void  option_respond_string24_Generate(char *v61419,list *v12196);
extern CL_EXPORT tuple * option_usage_string23_Generate(char *v61419);
extern CL_EXPORT tuple * option_usage_string23_Generate_(char *v23653);
extern CL_EXPORT void  option_respond_string25_Generate(char *v61419,list *v12196);
extern CL_EXPORT void  option_respond_string43_Generate(char *v61419,list *v12196);
extern CL_EXPORT void  option_respond_string26_Generate(char *v61419,list *v12196);
extern CL_EXPORT tuple * option_usage_string24_Generate(char *v61419);
extern CL_EXPORT tuple * option_usage_string24_Generate_(char *v23654);
extern CL_EXPORT void  option_respond_string27_Generate(char *v61419,list *v12196);
extern CL_EXPORT tuple * option_usage_string33_Generate(char *v61419);
extern CL_EXPORT tuple * option_usage_string33_Generate_(char *v23655);
extern CL_EXPORT void  option_respond_string28_Generate(char *v61419,list *v12196);
extern CL_EXPORT void  option_respond_string29_Generate(char *v61419,list *v12196);
extern CL_EXPORT void  option_respond_string30_Generate(char *v61419,list *v12196);
extern CL_EXPORT tuple * option_usage_string26_Generate(char *v61419);
extern CL_EXPORT tuple * option_usage_string26_Generate_(char *v23656);
extern CL_EXPORT void  option_respond_string31_Generate(char *v61419,list *v12196);
extern CL_EXPORT void  option_respond_string32_Generate(char *v61419,list *v12196);
extern CL_EXPORT void  option_respond_string33_Generate(char *v61419,list *v12196);
extern CL_EXPORT void  option_respond_string42_Generate(char *v61419,list *v12196);
extern CL_EXPORT void  option_respond_string44_Generate(char *v61419,list *v12196);
extern CL_EXPORT void  option_respond_string34_Generate(char *v61419,list *v12196);
extern CL_EXPORT tuple * option_usage_string27_Generate(char *v61419);
extern CL_EXPORT tuple * option_usage_string27_Generate_(char *v23657);
extern CL_EXPORT void  option_respond_string35_Generate(char *v61419,list *v12196);
extern CL_EXPORT tuple * option_usage_string28_Generate(char *v61419);
extern CL_EXPORT tuple * option_usage_string28_Generate_(char *v23658);
extern CL_EXPORT void  option_respond_string36_Generate(char *v61419,list *v12196);
extern CL_EXPORT void  option_respond_string37_Generate(char *v61419,list *v12196);
extern CL_EXPORT tuple * option_usage_string29_Generate(char *v61419);
extern CL_EXPORT tuple * option_usage_string29_Generate_(char *v23659);
extern CL_EXPORT void  option_respond_string38_Generate(char *v61419,list *v12196);
extern CL_EXPORT tuple * option_usage_string30_Generate(char *v61419);
extern CL_EXPORT tuple * option_usage_string30_Generate_(char *v23660);
extern CL_EXPORT void  option_respond_string39_Generate(char *v61419,list *v12196);
extern CL_EXPORT tuple * option_usage_string31_Generate(char *v61419);
extern CL_EXPORT tuple * option_usage_string31_Generate_(char *v23661);
extern CL_EXPORT void  option_respond_string40_Generate(char *v61419,list *v12196);
extern CL_EXPORT tuple * option_usage_string32_Generate(char *v61419);
extern CL_EXPORT tuple * option_usage_string32_Generate_(char *v23683);
extern CL_EXPORT void  option_respond_string41_Generate(char *v61419,list *v12196);
extern CL_EXPORT void  option_parsed_void2_Generate();
extern CL_EXPORT void  option_respond_string57_Generate(char *v61419,list *v12196);
extern CL_EXPORT tuple * option_usage_string37_Generate(char *v46356);
extern CL_EXPORT tuple * option_usage_string37_Generate_(char *v23692);

// namespace class for Generate 
class CL_EXPORT GenerateClass: public NameSpace {
public:

  global_variable * _star_ask_interval_star;
  global_variable * _star_dash_dash_integer_star;
  global_variable * _star_plus_integer_star;
  global_variable * _starnth_integer_star;
  global_variable * _starnth_list_star;
  global_variable * _starnth_1_bag_star;
  global_variable * _starnth_string_star;
  global_variable * _starnth_1_string_star;
  global_variable * _starnth_equal_list_star;
  global_variable * _starnot_star;
  global_variable * _starknown_star;
  global_variable * _starunknown_star;
  global_variable * _starnot_equal_star;
  global_variable * _starcontain_star;
  global_variable * _starmin_integer_star;
  global_variable * _starmax_integer_star;
  global_variable * _starlength_array_star;
  global_variable * _starlength_bag_star;
  global_variable * _starlength_string_star;
  global_variable * _star_plus_char_star_star;
  global_variable * _starnth_char_star_star;
  global_variable * _starclose_exception_star;
  ClaireClass * _producer;
  global_variable * PRODUCER;
  table * classFile;
  global_variable * WrongMethod;
  ClaireClass * _c_producer;
  Generate_c_producer * C_plus_plusPRODUCER;
  property * fcall_ask;
  property * fcall_exp;
  global_variable * FCLimit;
  global_variable * FCALLSTINKS;
  global_variable * bitvectorList;
  global_variable * _starin_store_star;
  global_variable * so_options;
  global_variable * cxx_options;
  global_variable * ld_options;
  global_variable * rCode;
  global_variable * _Zcm;
  global_variable * _Zcf;
  global_variable * _Zcxf;
  global_variable * dblevel;
  global_variable * _Zout;
  global_variable * _Zcj;
  global_variable * _Zsudo;
  global_variable * _Zov;
  global_variable * _Zcls;
  global_variable * _Zcall;
  global_variable * _Zexport;
  global_variable * _Zboth;
  global_variable * _Zpublish;
  global_variable * _Zsm;
  global_variable * _Zem;
  global_variable * cppopts;
  global_variable * linkopts;
  global_variable * clevel;
  global_variable * _Zinit_ask;
  global_variable * vlevel;
  global_variable * slevel;
  global_variable * clcc_ask;
property * equal_exp;// Generate/"equal_exp"
property * object_test;// Generate/"object_test"
property * bitvector_exp;// Generate/"bitvector_exp"
property * inherit_exp;// Generate/"inherit_exp"
property * args_list;// Generate/"args_list"
property * check_var;// Generate/"check_var"
property * build_Variable;// Generate/"build_Variable"
property * unfold_args;// Generate/"unfold_args"
property * c_type_sort;// Generate/"c_type_sort"
property * unfold_arg;// Generate/"unfold_arg"
property * unfold_use;// Generate/"unfold_use"
property * self_statement;// Generate/"self_statement"
property * stat_construct;// Generate/"stat_construct"
property * init_var;// Generate/"init_var"
property * stat_while;// Generate/"stat_while"
property * stat_gassign;// Generate/"stat_gassign"
property * stat_for;// Generate/"stat_for"
property * stat_iteration;// Generate/"stat_iteration"
property * stat_super;// Generate/"stat_super"
property * stat_handle;// Generate/"stat_handle"
property * any_interface;// Generate/"any_interface"
property * pointer_cast;// Generate/"pointer_cast"
property * bad_names;// Generate/"bad_names"
property * good_names;// Generate/"good_names"
property * generate_float_function;// Generate/"generate_float_function"
property * generate_regular_function;// Generate/"generate_regular_function"
property * bitvectorSum;// Generate/"bitvectorSum"
property * signature_I;// Generate/"signature!"
property * bitvector_I;// Generate/"bitvector!"
property * get_restrictions;// Generate/"get_restrictions"
property * public_static;// Generate/"public_static"
property * c_sorted_arg;// Generate/"c_sorted_arg"
property * c_sorted_args;// Generate/"c_sorted_args"
property * open_comparators;// Generate/"open_comparators"
property * open_operators;// Generate/"open_operators"
property * extension;// Generate/"extension"
property * interfaces;// Generate/"interfaces"
property * interface_I;// Generate/"interface!"
property * indent_c;// Generate/"indent_c"
property * breakline;// Generate/"breakline"
property * new_block;// Generate/"new_block"
property * close_block;// Generate/"close_block"
property * c_test;// claire/"c_test"
property * c_func;// Compile/"c_func"
property * expression;// Generate/"expression"
property * statement;// Generate/"statement"
property * compile;// claire/"compile"
property * parents;// Generate/"parents"
property * outmodule;// Generate/"outmodule"
property * generate_files;// Generate/"generate_files"
property * generate_classes;// Generate/"generate_classes"
property * generate_c2f;// Generate/"generate_c2f"
property * generate_f2f;// Generate/"generate_f2f"
property * generate_interface;// Generate/"generate_interface"
property * start_module_interface;// Generate/"start_module_interface"
property * generate_file;// Generate/"generate_file"
property * start_file;// Generate/"start_file"
property * generate_meta_load;// Generate/"generate_meta_load"
property * generate_start_file;// Generate/"generate_start_file"
property * generate_functions;// Generate/"generate_functions"
property * generate_objects;// Generate/"generate_objects"
property * generate_end_file;// Generate/"generate_end_file"
property * typed_args_list;// Generate/"typed_args_list"
property * namespace_I;// Generate/"namespace!"
property * c_member;// Generate/"c_member"
property * addFast;// Generate/"addFast"
property * print_external_call;// Generate/"print_external_call"
property * getC;// Generate/"getC"
property * declare;// Generate/"declare"
property * print_c_function;// Generate/"print_c_function"
property * create_function_entry;// Generate/"create_function_entry"
property * check_sort;// Generate/"check_sort"
property * protect_result;// Generate/"protect_result"
property * set_outfile;// Generate/"set_outfile"
property * generate_profile;// Generate/"generate_profile"
property * inner_statement;// Generate/"inner_statement"
property * update_function_entry;// Generate/"update_function_entry"
property * get_dependents;// Generate/"get_dependents"
property * produce;// Generate/"produce"
property * at;// Generate/"at"
property * bag_expression;// Generate/"bag_expression"
property * inline_exp;// Generate/"inline_exp"
property * gc_protection_exp;// Generate/"gc_protection_exp"
property * exp_to_protect;// Generate/"exp_to_protect"
property * gc_protect;// Generate/"gc_protect"
property * gassign;// Generate/"gassign"
property * to_cl;// Generate/"to_cl"
property * to_c;// Generate/"to_c"
property * call_slot;// Generate/"call_slot"
property * call_table;// Generate/"call_table"
property * call_array;// Generate/"call_array"
property * update;// Generate/"update"
property * sign_equal;// Generate/"sign_equal"
property * sign_or;// Generate/"sign_or"
property * macro;// Generate/"macro"
property * generate_function_start;// Generate/"generate_function_start"
property * print_body;// Generate/"print_body"
property * c_safe;// Generate/"c_safe"
property * outer_statement;// Generate/"outer_statement"
property * methods_interface;// Generate/"methods_interface"
property * methods_bodies;// Generate/"methods_bodies"
property * gc_usage;// Generate/"gc_usage"
property * gc_usage_star;// Generate/"gc_usage*"
property * gc_or;// Generate/"gc_or"
property * stat_exp;// Generate/"stat_exp"
property * define_variable;// Generate/"define_variable"
property * char_exp_ask;// Generate/"char_exp?"
property * char_exp;// Generate/"char_exp"
property * bool_exp_ask;// Generate/"bool_exp?"
property * bool_exp_I;// Generate/"bool_exp!"
property * bexpression;// Generate/"bexpression"
property * end_module_interface;// Generate/"end_module_interface"
property * stat_let;// Generate/"stat_let"
property * exp_Assign;// Generate/"exp_Assign"
property * generate_tuple_function;// Generate/"generate_tuple_function"
property * generate_s_file;// Generate/"generate_s_file"
property * create_load_modules;// Generate/"create_load_modules"
property * global_var_def_ask;// Generate/"global_var_def?"
property * global_var_def_I;// Generate/"global_var_def!"
property * getRange;// Generate/"getRange"
property * globalVar;// Generate/"globalVar"
property * c_string;// Generate/"c_string"
property * class_princ;// Generate/"class_princ"
property * any_bool_exp;// Generate/"any_bool_exp"
property * generate_wcl_file;// Generate/"generate_wcl_file"
property * headers_I;// Generate/"headers!"
property * new_module;// Generate/"new_module"
property * external_I;// Generate/"external!"
property * string2module;// Generate/"string2module"
property * home_path;// Generate/"home_path"
property * function_compile;// Generate/"function_compile"
property * libpath;// Generate/"libpath"
property * libpath_I;// Generate/"libpath!"
property * lib_I;// Generate/"lib!"
property * files_I;// Generate/"files!"
property * job_option;// Generate/"job_option"
property * cmakefile;// Generate/"cmakefile"
property * create_makefile_nt;// Generate/"create_makefile_nt"
property * create_makefile_unix;// Generate/"create_makefile_unix"
property * ensure_module_directories_exist;// Generate/"ensure_module_directories_exist"
property * rcopy;// Generate/"rcopy"
property * export_module;// Generate/"export_module"
property * relayed_params;// Generate/"relayed_params"
property * compile_module_libs;// Generate/"compile_module_libs"
property * compile_all_module_libs;// Generate/"compile_all_module_libs"
property * module_list;// Generate/"module_list"
property * module_info;// Generate/"module_info"
property * list_fcall;// Generate/"list_fcall"
property * create_dynload_module;// Generate/"create_dynload_module"
property * importlib_I;// Generate/"importlib!"

// module definition 
 void metaLoad();};

extern CL_EXPORT GenerateClass Generate;

#endif

