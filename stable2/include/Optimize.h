// interface definition for module Optimize
#ifndef CLAIREH_Optimize
#define CLAIREH_Optimize

  
class CL_EXPORT Optimize_meta_OPT;
class CL_EXPORT Optimize_meta_compiler;
class CL_EXPORT Compile_to_protect;
class CL_EXPORT Compile_to_CL;
class CL_EXPORT Compile_to_C;
class CL_EXPORT Compile_C_cast;
class CL_EXPORT Optimize_ClairePattern;
class CL_EXPORT Optimize_optUnion;
class CL_EXPORT Optimize_Call_function2;

class CL_EXPORT Optimize_meta_OPT: public thing{ 
    public:
       list *instructions;
       list *objects;
       set *properties;
       list *functions;
       set *need_to_close;
       set *need_modules;
       set *legal_modules;
       ClaireBoolean *allocation;
       ClaireBoolean *protection;
       ClaireBoolean *alloc_stack;
       set *ignore;
       set *to_remove;
       PortObject *cinterface;
       PortObject *outfile;
       CL_INT max_vars;
       ClaireBoolean *loop_gc;
       CL_INT loop_index;
       CL_INT level;
       OID in_method;
       ClaireBoolean *profile_ask;
       OID cfile;
       ClaireBoolean *use_update;
       ClaireBoolean *use_nth_equal;
       ClaireBoolean *online_ask;
       ClaireBoolean *recompute;
       list *unsure;
       set *knowns;
       set *simple_operations;
       set *non_identifiable_set;}
  ;

class CL_EXPORT Optimize_meta_compiler: public thing{ 
    public:
       char *external;
       list *headers;
       char *source;
       list *debug_ask;
       OID version;
       ClaireBoolean *active_ask;
       CL_INT safety;
       char *env;
       CL_INT naming;
       list *libraries;
       ClaireBoolean *inline_ask;
       ClaireBoolean *loading_ask;
       ClaireBoolean *class2file_ask;
       ClaireBoolean *greedy_ask;
       list *libraries_dir;
       char *headers_dir;
       list *options;
       ClaireBoolean *overflow_ask;
       ClaireBoolean *diet_ask;
       ClaireBoolean *optimize_ask;}
  ;

class CL_EXPORT Compile_to_protect: public Optimized_instruction{ 
    public:
       OID arg;}
  ;

class CL_EXPORT Compile_to_CL: public Optimized_instruction{ 
    public:
       OID arg;
       ClaireClass *set_arg;}
  ;

class CL_EXPORT Compile_to_C: public Optimized_instruction{ 
    public:
       OID arg;
       ClaireClass *set_arg;}
  ;

class CL_EXPORT Compile_C_cast: public Compile_to_C{ 
    public:}
  ;

class CL_EXPORT Optimize_ClairePattern: public Type{ 
    public:
       property *selector;
       list *arg;}
  ;

class CL_EXPORT Optimize_optUnion: public Union{ 
    public:}
  ;

class CL_EXPORT Optimize_Call_function2: public Optimized_instruction{ 
    public:
       ClaireFunction *arg;
       list *args;}
  ;
extern CL_EXPORT char * home_void();
extern CL_EXPORT OID  safe_any2(OID v8240);
extern CL_EXPORT ClaireType * safe_any2_type(ClaireType *v8240);
extern CL_EXPORT ClaireType * c_type_any_Optimize(OID v62612);
extern CL_EXPORT OID  c_strict_code_any(OID v8240,ClaireClass *v8235);
extern CL_EXPORT OID  c_strict_check_any_Optimize(OID v8240,ClaireClass *v8235);
extern CL_EXPORT OID  c_code_any1_Optimize(OID v8240,ClaireClass *v8235);
extern CL_EXPORT OID  c_code_any2_Optimize(OID v62612);
extern CL_EXPORT ClaireBoolean * c_gc_ask_any(OID v62612);
extern CL_EXPORT ClaireClass * c_sort_any_Optimize(OID v62612);
extern CL_EXPORT ClaireClass * selector_psort_Call(Call *v62612);
extern CL_EXPORT CL_INT  c_status_any(OID v62612,list *v8228);
extern CL_EXPORT CL_INT  c_or_integer(CL_INT v8240,CL_INT v8241);
extern CL_EXPORT CL_INT  c_or_list(list *v8228);
extern CL_EXPORT CL_INT  status_I_restriction(restriction *v62612);
extern CL_EXPORT CL_INT  c_return_integer(CL_INT v8240,CL_INT v8241);
extern CL_EXPORT CL_INT  c_status_property(property *v62612);
extern CL_EXPORT OID  showstatus_method2(method *v8229);
extern CL_EXPORT void  s_test_method2(method *v8229);
extern CL_EXPORT ClaireBoolean * legal_ask_module(module *v62612,OID v8240);
extern CL_EXPORT OID  legal_ask_environment(ClaireEnvironment *v62612,OID v8240);
extern CL_EXPORT OID  c_register_object(ClaireObject *v62612);
extern CL_EXPORT OID  c_register_property(property *v62612);
extern CL_EXPORT OID  selector_register_property(property *v62612);
extern CL_EXPORT OID  allocate_ask_property(property *v62612);
extern CL_EXPORT ClaireBoolean * stable_ask_relation(ClaireRelation *v62612);
extern CL_EXPORT OID  get_module_object(ClaireObject *v62612);
extern CL_EXPORT OID  known_I_listargs(listargs *v8228);
extern CL_EXPORT OID  oload_module(module *v8229);
extern CL_EXPORT OID  oload_string(char *v8222);
extern CL_EXPORT OID  turbo_module(module *v8229);
extern CL_EXPORT void  stats_meta_OPT(Optimize_meta_OPT *v8240);
extern CL_EXPORT void  self_print_to_protect(Compile_to_protect *v8240);
extern CL_EXPORT OID  self_eval_to_protect(Compile_to_protect *v8240);
extern CL_EXPORT void  self_print_to_CL(Compile_to_CL *v62612);
extern CL_EXPORT ClaireType * c_type_to_CL_Optimize(Compile_to_CL *v62612);
extern CL_EXPORT ClaireBoolean * c_gc_ask_to_CL(Compile_to_CL *v62612);
extern CL_EXPORT void  self_print_to_C(Compile_to_C *v62612);
extern CL_EXPORT ClaireBoolean * c_gc_ask_to_C(Compile_to_C *v62612);
extern CL_EXPORT ClaireType * c_type_to_C_Optimize(Compile_to_C *v62612);
extern CL_EXPORT void  self_print_C_cast(Compile_C_cast *v62612);
extern CL_EXPORT ClaireBoolean * c_gc_ask_C_cast(Compile_C_cast *v62612);
extern CL_EXPORT ClaireType * c_type_C_cast_Optimize(Compile_C_cast *v62612);
extern CL_EXPORT OID  c_code_C_cast_Optimize(Compile_C_cast *v62612,ClaireClass *v8235);
extern CL_EXPORT void  self_print_Pattern(Optimize_ClairePattern *v62612);
extern CL_EXPORT ClaireBoolean * _Z_any3(OID v8240,Optimize_ClairePattern *v8241);
extern CL_EXPORT ClaireType * glb_Pattern(Optimize_ClairePattern *v8240,ClaireType *v8241);
extern CL_EXPORT ClaireBoolean * less_ask_Pattern(Optimize_ClairePattern *v8240,OID v8241);
extern CL_EXPORT ClaireBoolean * less_ask_any(OID v8240,Optimize_ClairePattern *v8241);
extern CL_EXPORT Optimize_ClairePattern * nth_property(property *v8232,tuple *v8240);
extern CL_EXPORT void  show_opportunist_integer1(CL_INT v8230);
extern CL_EXPORT void  warn_void();
extern CL_EXPORT void  Cerror_string(char *v8235,listargs *v8228);
extern CL_EXPORT void  notice_void();
extern CL_EXPORT OID  c_warn_Call(Call *v62612,OID v30871);
extern CL_EXPORT OID  c_warn_Super(Super *v62612,OID v30871);
extern CL_EXPORT OID  c_warn_property(property *v62612,list *v8228,list *v30871);
extern CL_EXPORT OID  c_warn_Variable(Variable *v62612,OID v8240,ClaireType *v8241);
extern CL_EXPORT OID  sort_equal_class(ClaireClass *v8219,ClaireClass *v58231);
extern CL_EXPORT ClaireClass * psort_any(OID v8240);
extern CL_EXPORT ClaireClass * osort_any(OID v8240);
extern CL_EXPORT ClaireClass * sort_Variable(Variable *v8240);
extern CL_EXPORT ClaireClass * stupid_t_any1(OID v62612);
extern CL_EXPORT ClaireBoolean * stupid_t_any2(OID v62612,OID v8240);
extern CL_EXPORT ClaireBoolean * extended_ask_type(ClaireType *v62612);
extern CL_EXPORT ClaireType * extends_type(ClaireType *v8240);
extern CL_EXPORT ClaireType * sort_abstract_I_type(ClaireType *v8240);
extern CL_EXPORT ClaireBoolean * sort_abstract_ask_type(ClaireType *v8240);
extern CL_EXPORT ClaireType * ptype_type(ClaireType *v8240);
extern CL_EXPORT ClaireType * pmember_type(ClaireType *v8240);
extern CL_EXPORT OID  enumerate_code_any(OID v62612,ClaireType *v56375);
extern CL_EXPORT OID  range_infers_for_Variable(Variable *v62612,ClaireType *v8241,ClaireType *v58823);
extern CL_EXPORT OID  range_infers_Variable(Variable *v62612,ClaireType *v8241);
extern CL_EXPORT void  range_infer_case_any(OID v62612,ClaireType *v8241);
extern CL_EXPORT OID  c_check_any(OID v8240,OID v8241);
extern CL_EXPORT void  range_sets_any(OID v62612,ClaireType *v8241);
extern CL_EXPORT ClaireClass * c_srange_method(method *v8229);
extern CL_EXPORT ClaireBoolean * nativeVar_ask_global_variable(global_variable *v8240);
extern CL_EXPORT ClaireType * return_type_any(OID v62612);
extern CL_EXPORT OID  c_code_Type_Optimize(Type *v62612,ClaireClass *v8235);
extern CL_EXPORT OID  self_code_subtype(subtype *v62612);
extern CL_EXPORT OID  self_code_Param(Param *v62612);
extern CL_EXPORT OID  self_code_Union(Union *v62612);
extern CL_EXPORT OID  self_code_Interval(Interval *v62612);
extern CL_EXPORT OID  self_code_Reference(Reference *v62612);
extern CL_EXPORT OID  self_code_Pattern(Optimize_ClairePattern *v62612);
extern CL_EXPORT OID  member_code_class2(ClaireClass *v62612,OID v8240);
extern CL_EXPORT OID  member_code_Type(Type *v62612,OID v8240);
extern CL_EXPORT OID  member_code_Union(Union *v62612,OID v8240);
extern CL_EXPORT OID  member_code_Interval(Interval *v62612,OID v8240);
extern CL_EXPORT OID  member_code_Param(Param *v62612,OID v8240);
extern CL_EXPORT OID  member_code_tuple(tuple *v62612,OID v8240);
extern CL_EXPORT OID  member_code_any(OID v62612,OID v8240);
extern CL_EXPORT ClaireBoolean * _Z_any4(OID v8240,OID v8241);
extern CL_EXPORT ClaireBoolean * _Z_any5(OID v8240,OID v8241);
extern CL_EXPORT ClaireBoolean * gcsafe_ask_class(ClaireClass *v62612);
extern CL_EXPORT ClaireBoolean * gcsafe_ask_type(ClaireType *v62612);
extern CL_EXPORT ClaireBoolean * gcsafe_ask_property(property *v62612);
extern CL_EXPORT OID  c_gc_I_any1(OID v62612);
extern CL_EXPORT OID  c_gc_I_any2(OID v62612,ClaireType *v8236);
extern CL_EXPORT ClaireBoolean * need_protect_any(OID v8240);
extern CL_EXPORT Variable * Variable_I_symbol(symbol *v8235,int v8230,ClaireType *v8236);
extern CL_EXPORT list * get_indexed_class_Optimize(ClaireClass *v8219);
extern CL_EXPORT ClaireBoolean * designated_ask_any(OID v62612);
extern CL_EXPORT OID  gc_register_Variable(Variable *v62612);
extern CL_EXPORT OID  gc_register_Variable2(Variable *v62612,OID v7502);
extern CL_EXPORT ClaireBoolean * inner2outer_ask_any(OID v8240);
extern CL_EXPORT ClaireBoolean * identifiable_ask_any(OID v62612);
extern CL_EXPORT OID  c_inline_method1(method *v62612,list *v8228,ClaireClass *v8235);
extern CL_EXPORT OID  c_inline_method2(method *v62612,list *v8228);
extern CL_EXPORT OID  c_inline_arg_ask_any(OID v62612);
extern CL_EXPORT OID  c_substitution_any(OID v62612,list *v58580,list *v55513,ClaireBoolean *v59099);
extern CL_EXPORT OID  eval_any2(OID v8240,ClaireClass *v8241);
extern CL_EXPORT list * bound_variables_any(OID v62612);
extern CL_EXPORT OID  c_boolean_any(OID v8240);
extern CL_EXPORT OID  restriction_I_property(property *v62612,list *v8228,ClaireBoolean *v24299);
extern CL_EXPORT OID  restriction_I_list(list *v58574,list *v8228,ClaireBoolean *v24299);
extern CL_EXPORT OID  restriction_I_class(ClaireClass *v8219,list *v58574,list *v8228);
extern CL_EXPORT ClaireType * use_range_method(method *v62612,list *v56367);
extern CL_EXPORT ClaireType * c_type_Call2_Optimize(Call *v62612);
extern CL_EXPORT OID  c_code_Call_Optimize(Call *v62612);
extern CL_EXPORT OID  c_code_call_Call(Call *v62612,ClaireClass *v58797);
extern CL_EXPORT Call * open_message_property(property *v62612,list *v8228);
extern CL_EXPORT ClaireBoolean * c_gc_ask_Call(Call *v62612);
extern CL_EXPORT OID  daccess_any(OID v62612,ClaireBoolean *v8218);
extern CL_EXPORT ClaireBoolean * c_gc_ask_Call_slot(Call_slot *v62612);
extern CL_EXPORT ClaireType * c_type_Call_slot_Optimize(Call_slot *v62612);
extern CL_EXPORT ClaireType * c_type_Call_table_Optimize(Call_table *v62612);
extern CL_EXPORT ClaireType * c_type_Call_array_Optimize(Call_array *v62612);
extern CL_EXPORT OID  c_code_write_Call(Call *v62612);
extern CL_EXPORT OID  c_code_hold_property(property *v8232,OID v8240,OID v8241,ClaireBoolean *v8218);
extern CL_EXPORT OID  c_code_add_Call(Call *v62612);
extern CL_EXPORT OID  c_code_add_bag_Call(Call *v62612);
extern CL_EXPORT OID  c_code_delete_Call(Call *v62612);
extern CL_EXPORT OID  c_code_not_Select(Select *v8240);
extern CL_EXPORT OID  c_code_belong_Call(Call *v62612);
extern CL_EXPORT OID  c_code_nth_Call(Call *v62612);
extern CL_EXPORT OID  c_code_table_Call(Call *v62612);
extern CL_EXPORT OID  c_code_array_Call(Call *v62612);
extern CL_EXPORT ClaireBoolean * Update_ask_relation(ClaireRelation *v8232,OID v8240,OID v8241);
extern CL_EXPORT ClaireBoolean * Update_ask_relation2(ClaireRelation *v8232,ClaireRelation *v8235);
extern CL_EXPORT ClaireType * c_type_Update_Optimize(Update *v62612);
extern CL_EXPORT OID  c_code_method_method1(method *v62612,list *v8228,list *v30871);
extern CL_EXPORT OID  c_code_method_method2(method *v62612,list *v8228,list *v30871,ClaireClass *v58797);
extern CL_EXPORT OID  Call_method_I_method(method *v62612,list *v38730);
extern CL_EXPORT ClaireType * c_type_Call_method_Optimize(Call_method *v62612);
extern CL_EXPORT OID  c_code_Call_method_Optimize(Call_method *v62612);
extern CL_EXPORT ClaireBoolean * c_gc_ask_Call_method(Call_method *v62612);
extern CL_EXPORT ClaireFunction * functional_I_method_Optimize(method *v62612);
extern CL_EXPORT OID  nth_type_check_type(ClaireType *v58816,ClaireType *v58813,ClaireType *v58828);
extern CL_EXPORT ClaireBoolean * c_inline_ask_method(method *v62612,list *v8228);
extern CL_EXPORT OID  inline_optimize_ask_Call(Call *v62612);
extern CL_EXPORT ClaireType * c_type_Assign_Optimize(Assign *v62612);
extern CL_EXPORT OID  c_code_Assign_Optimize(Assign *v62612);
extern CL_EXPORT ClaireBoolean * c_gc_ask_Assign(Assign *v62612);
extern CL_EXPORT ClaireType * c_type_Gassign_Optimize(Gassign *v62612);
extern CL_EXPORT OID  c_code_Gassign_Optimize(Gassign *v62612);
extern CL_EXPORT ClaireBoolean * c_gc_ask_Gassign(Gassign *v62612);
extern CL_EXPORT ClaireType * c_type_And_Optimize(And *v62612);
extern CL_EXPORT OID  c_code_And_Optimize(And *v62612);
extern CL_EXPORT ClaireType * c_type_Or_Optimize(Or *v62612);
extern CL_EXPORT OID  c_code_Or_Optimize(Or *v62612);
extern CL_EXPORT ClaireType * c_type_Quote_Optimize(Quote *v62612);
extern CL_EXPORT void  c_code_Quote_Optimize(Quote *v62612);
extern CL_EXPORT ClaireType * c_type_to_protect_Optimize(Compile_to_protect *v62612);
extern CL_EXPORT OID  c_code_to_protect_Optimize(Compile_to_protect *v62612);
extern CL_EXPORT ClaireBoolean * c_gc_ask_to_protect(Compile_to_protect *v62612);
extern CL_EXPORT ClaireType * c_type_Return_Optimize(Return *v62612);
extern CL_EXPORT OID  c_code_Return_Optimize(Return *v62612);
extern CL_EXPORT ClaireType * c_type_Handle_Optimize(ClaireHandle *v62612);
extern CL_EXPORT OID  c_code_Handle_Optimize(ClaireHandle *v62612,ClaireClass *v8235);
extern CL_EXPORT ClaireBoolean * c_gc_ask_Handle(ClaireHandle *v62612);
extern CL_EXPORT ClaireType * c_type_Cast_Optimize(Cast *v62612);
extern CL_EXPORT OID  c_code_Cast2_Optimize(Cast *v62612);
extern CL_EXPORT ClaireType * c_type_Super_Optimize(Super *v62612);
extern CL_EXPORT OID  c_code_Super_Optimize(Super *v62612);
extern CL_EXPORT void  self_print_Call_function2(Optimize_Call_function2 *v62612);
extern CL_EXPORT ClaireType * c_type_Call_function2_Optimize(Optimize_Call_function2 *v62612);
extern CL_EXPORT OID  c_code_Call_function2_Optimize(Optimize_Call_function2 *v62612);
extern CL_EXPORT OID  c_code_Assert_Optimize(Assert *v62612);
extern CL_EXPORT OID  c_code_Trace_Optimize(Trace *v62612);
extern CL_EXPORT ClaireType * c_type_Assert_Optimize(Assert *v62612);
extern CL_EXPORT ClaireType * c_type_Trace_Optimize(Trace *v62612);
extern CL_EXPORT ClaireType * c_type_Branch_Optimize(Branch *v62612);
extern CL_EXPORT OID  c_code_Branch_Optimize(Branch *v62612);
extern CL_EXPORT OID  c_code_Macro_Optimize(Macro *v62612,ClaireClass *v8235);
extern CL_EXPORT ClaireType * c_type_Macro_Optimize(Macro *v62612);
extern CL_EXPORT ClaireType * c_type_Printf_Optimize(Printf *v62612);
extern CL_EXPORT OID  c_code_Printf_Optimize(Printf *v62612);
extern CL_EXPORT ClaireType * c_type_Error_Optimize(Error *v62612);
extern CL_EXPORT OID  c_code_Error_Optimize(Error *v62612);
extern CL_EXPORT ClaireType * extendedTest_ask_If(If *v62612);
extern CL_EXPORT ClaireType * c_type_If_Optimize(If *v62612);
extern CL_EXPORT OID  c_code_If_Optimize(If *v62612,ClaireClass *v8235);
extern CL_EXPORT ClaireBoolean * c_gc_ask_If(If *v62612);
extern CL_EXPORT ClaireType * c_type_Case_Optimize(Case *v62612);
extern CL_EXPORT OID  c_code_Case_Optimize(Case *v62612,ClaireClass *v8235);
extern CL_EXPORT ClaireType * c_type_Do_Optimize(Do *v62612);
extern CL_EXPORT OID  c_code_Do_Optimize(Do *v62612,ClaireClass *v8235);
extern CL_EXPORT ClaireBoolean * c_gc_ask_Do(Do *v62612);
extern CL_EXPORT ClaireType * c_type_Let_Optimize(Let *v62612);
extern CL_EXPORT OID  c_code_Let_Optimize(Let *v62612,ClaireClass *v8235);
extern CL_EXPORT ClaireType * c_type_When_Optimize(When *v62612);
extern CL_EXPORT OID  c_code_When_Optimize(When *v62612,ClaireClass *v8235);
extern CL_EXPORT ClaireBoolean * c_gc_ask_Let(Let *v62612);
extern CL_EXPORT ClaireType * c_type_For_Optimize(For *v62612);
extern CL_EXPORT ClaireType * infers_from_type2(ClaireType *v8236,OID v62612);
extern CL_EXPORT OID  c_code_For_Optimize(For *v62612,ClaireClass *v8235);
extern CL_EXPORT OID  c_code_multiple_For(For *v62612,ClaireType *v56375,ClaireClass *v8235);
extern CL_EXPORT ClaireBoolean * c_gc_ask_Iteration(Iteration *v62612);
extern CL_EXPORT ClaireBoolean * c_gc_ask_Ffor1(iClaire_Ffor *v62612);
extern CL_EXPORT ClaireType * c_type_Iteration_Optimize(Iteration *v62612);
extern CL_EXPORT OID  c_code_Iteration_Optimize(Iteration *v62612);
extern CL_EXPORT OID  c_code_Select_Optimize(Select *v62612);
extern CL_EXPORT OID  c_code_Lselect_Optimize(Lselect *v62612);
extern CL_EXPORT OID  c_code_select_Iteration(Iteration *v62612,ClaireClass *v8240);
extern CL_EXPORT OID  inner_select_Iteration(Iteration *v62612,OID v58820,OID v58797,OID v55513);
extern CL_EXPORT ClaireType * c_type_Exists_Optimize(Exists *v62612);
extern CL_EXPORT OID  c_code_Exists_Optimize(Exists *v62612,ClaireClass *v8235);
extern CL_EXPORT ClaireType * c_type_Image_Optimize(Image *v62612);
extern CL_EXPORT ClaireType * c_type_Select_Optimize(Select *v62612);
extern CL_EXPORT ClaireType * c_type_Lselect_Optimize(Lselect *v62612);
extern CL_EXPORT ClaireType * c_type_While_Optimize(While *v62612);
extern CL_EXPORT OID  c_code_While_Optimize(While *v62612,ClaireClass *v8235);
extern CL_EXPORT void  option_respond_string58_Optimize(char *v49259,list *v8228);
extern CL_EXPORT tuple * option_usage_string38_Optimize(char *v62612);
extern CL_EXPORT tuple * option_usage_string38_Optimize_(char *v17858);
extern CL_EXPORT OID  c_type_Ffor1_Optimize(iClaire_Ffor *v62612);
extern CL_EXPORT OID  c_code_Ffor1_Optimize(iClaire_Ffor *v62612,ClaireClass *v58792);
extern CL_EXPORT OID  Iterate_I_Iteration(Iteration *v62612);
extern CL_EXPORT OID  iterate_Interval(Interval *v8240,Variable *v8238,OID v8221);
extern CL_EXPORT OID  iterate_array(OID *v8240,Variable *v8238,OID v8221);
extern CL_EXPORT OID  Iterate_class(ClaireClass *v8240,Variable *v8238,OID v8221);
extern CL_EXPORT OID  Iterate_any1(OID v8240,Variable *v8238,OID v8221);
extern CL_EXPORT OID  Iterate_Lselect(Lselect *v8240,Variable *v8238,OID v8221);
extern CL_EXPORT OID  Iterate_Select(Select *v8240,Variable *v8238,OID v8221);
extern CL_EXPORT OID  Iterate_Collect(Collect *v8240,Variable *v8238,OID v8221);
extern CL_EXPORT OID  Iterate_any2(OID v8240,Variable *v8238,OID v8221);
extern CL_EXPORT OID  Iterate_any3(OID v8240,Variable *v8238,OID v8221);
extern CL_EXPORT ClaireType * c_type_List_Optimize(List *v62612);
extern CL_EXPORT OID  c_code_List_Optimize(List *v62612);
extern CL_EXPORT ClaireType * c_type_Set_Optimize(Set *v62612);
extern CL_EXPORT OID  c_code_Set_Optimize(Set *v62612);
extern CL_EXPORT ClaireType * c_type_Tuple_Optimize(Tuple *v62612);
extern CL_EXPORT OID  c_code_Tuple_Optimize(Tuple *v62612);
extern CL_EXPORT ClaireType * c_type_Definition_Optimize(Definition *v62612);
extern CL_EXPORT OID  c_code_Definition_Optimize(Definition *v62612,ClaireClass *v8235);
extern CL_EXPORT OID  total_ask_class(ClaireClass *v62612,list *v8228);
extern CL_EXPORT OID  analyze_I_class(ClaireClass *v8219,OID v62612,list *v56367,list *v58572);
extern CL_EXPORT OID  c_code_Defobj_Optimize(Defobj *v62612,ClaireClass *v8235);
extern CL_EXPORT OID  c_code_Defclass_Optimize(Defclass *v62612,ClaireClass *v8235);
extern CL_EXPORT ClaireType * c_type_Defmethod_Optimize(Defmethod *v62612);
extern CL_EXPORT OID  c_code_Defmethod_Optimize(Defmethod *v62612);
extern CL_EXPORT ClaireBoolean * sort_pattern_ask_list(list *v58578,OID v8959);
extern CL_EXPORT OID  sort_code_Defmethod(Defmethod *v62612,list *v58578);
extern CL_EXPORT method * add_method_property2(property *v8232,list *v58575,ClaireType *v58750,int v58793,ClaireFunction *v58323,ClaireFunction *v58324);
extern CL_EXPORT OID  add_method_I_method(method *v8229,list *v58575,OID v58750,OID v49756,ClaireFunction *v58391);
extern CL_EXPORT list * extract_status_new_any(OID v8240);
extern CL_EXPORT list * extract_signature_I_list(list *v8228);
extern CL_EXPORT ClaireBoolean * _equalsig_ask_list(list *v8240,list *v8241);
extern CL_EXPORT char * function_name_property_Optimize(property *v8232,list *v8228,OID v8240);
extern CL_EXPORT OID  compile_lambda_string(char *v62612,lambda *v8228,OID v8229);
extern CL_EXPORT OID  c_code_Defarray_Optimize(Defarray *v62612);
extern CL_EXPORT void  compute_if_write_inverse_relation2(ClaireRelation *v8203);
extern CL_EXPORT OID  compute_set_write_relation2(ClaireRelation *v8203);
extern CL_EXPORT OID  Produce_put_property2(property *v8234,Variable *v8240,OID v8241);
extern CL_EXPORT OID  Produce_erase_property2(property *v8234,Variable *v8240);
extern CL_EXPORT OID  Produce_put_table2(table *v8234,Variable *v8240,OID v8241);
extern CL_EXPORT OID  Produce_get_relation2(ClaireRelation *v8234,Variable *v8240);
extern CL_EXPORT OID  Produce_remove_property2(property *v8234,Variable *v8240,OID v8241);
extern CL_EXPORT OID  Produce_remove_table2(table *v8234,Variable *v8240,OID v8241);
extern CL_EXPORT void  Tighten_relation2(ClaireRelation *v8234);
extern CL_EXPORT void  lexical_num_any2(OID v62612,int v8230);
extern CL_EXPORT ClaireType * c_type_Defrule2_Optimize(Defrule *v62612);
extern CL_EXPORT OID  c_code_Defrule_Optimize(Defrule *v62612,ClaireClass *v8235);
extern CL_EXPORT void  compile_if_write_relation(ClaireRelation *v8203);
extern CL_EXPORT OID  compileEventMethod_property(property *v8232);

// namespace class for Optimize 
class CL_EXPORT OptimizeClass: public NameSpace {
public:

  global_variable * srange;
  global_variable * typing;
  global_variable * status;
  global_variable * tmatch_ask;
  global_variable * pname;
  global_variable * if_write;
  ClaireClass * _meta_OPT;
  ClaireClass * _meta_compiler;
  global_variable * claire_options;
  global_variable * claire_lib;
  global_variable * claire_modules;
  global_variable * claire_prefix;
  global_variable * have_prefix_ask;
  Optimize_meta_compiler * compiler;
  property * c_type;
  property * c_code;
  property * c_gc;
  property * get_index;
  property * get_indexed;
  property * make_c_function;
  property * make_float_function;
  property * c_expression;
  property * bool_exp;
  property * c_statement;
  property * c_interface;
  property * c_sort;
  property * designated_ask;
  property * sort_equal;
  property * psort;
  property * osort;
  property * compile_lambda;
  property * c_check;
  property * need_protect;
  property * member_code;
  property * c_strict_code;
  property * c_strict_check;
  property * stupid_t;
  property * object_I;
  property * anyObject_I;
  property * Cerror;
  property * self_code;
  property * get_module;
  property * main;
  ClaireClass * _to_protect;
  ClaireClass * _to_CL;
  ClaireClass * _to_C;
  ClaireClass * _C_cast;
  ClaireClass * _Pattern;
  Optimize_meta_OPT * OPT;
  ClaireClass * _optUnion;
  global_variable * _staroportunist_method_star;
  keyword * ambiguous;
  global_variable * _stardebug_local_file_star;
  property * functional_I;
  ClaireClass * _Call_function2;
  global_variable * PENIBLE;
  global_variable * NO_FFOR_ask;
  global_variable * _starname_star;
  global_variable * SHIT;
  operation * _equalsig_ask;
  property * function_name;
property * sort_abstract_I;// Optimize/"sort_abstract!"
property * warn;// Compile/"warn"
property * c_warn;// Optimize/"c_warn"
property * open_message;// Optimize/"open_message"
property * sort_abstract_ask;// Optimize/"sort_abstract?"
property * extended_ask;// Optimize/"extended?"
property * extends;// Optimize/"extends"
property * enumerate_code;// Optimize/"enumerate_code"
property * c_code_method;// Optimize/"c_code_method"
property * range_infers_for;// Optimize/"range_infers_for"
property * range_infers;// Optimize/"range_infers"
property * gc_register;// Optimize/"gc_register"
property * range_infer_case;// Optimize/"range_infer_case"
property * c_gc_I;// Optimize/"c_gc!"
property * range_sets;// Optimize/"range_sets"
property * Variable_I;// Compile/"Variable!"
property * identifiable_ask;// Compile/"identifiable?"
property * c_inline;// Optimize/"c_inline"
property * bound_variables;// Optimize/"bound_variables"
property * c_substitution;// Optimize/"c_substitution"
property * c_inline_arg_ask;// Optimize/"c_inline_arg?"
property * restriction_I;// Optimize/"restriction!"
property * c_inline_ask;// Optimize/"c_inline?"
property * c_boolean;// Optimize/"c_boolean"
property * use_range;// Optimize/"use_range"
property * inline_optimize_ask;// Optimize/"inline_optimize?"
property * daccess;// Optimize/"daccess"
property * c_code_write;// Optimize/"c_code_write"
property * c_code_hold;// Optimize/"c_code_hold"
property * c_code_add;// Optimize/"c_code_add"
property * c_code_delete;// Optimize/"c_code_delete"
property * c_code_table;// Optimize/"c_code_table"
property * c_code_array;// Optimize/"c_code_array"
property * c_code_nth;// Optimize/"c_code_nth"
property * c_code_belong;// Optimize/"c_code_belong"
property * c_code_not;// Optimize/"c_code_not"
property * Update_ask;// Optimize/"Update?"
property * Call_method_I;// Optimize/"Call_method!"
property * nth_type_check;// Optimize/"nth_type_check"
property * extendedTest_ask;// Optimize/"extendedTest?"
property * Iterate_I;// Optimize/"Iterate!"
property * total_ask;// Optimize/"total?"
property * analyze_I;// Optimize/"analyze!"
property * extract_signature_I;// Optimize/"extract_signature!"
property * extract_status_new;// Optimize/"extract_status_new"
property * add_method_I;// Optimize/"add_method!"
property * showstatus;// claire/"showstatus"
property * safe;// claire/"safe"
property * overflow_ask;// claire/"overflow?"
property * c_code_multiple;// Optimize/"c_code_multiple"
property * Produce_put;// Compile/"Produce_put"
property * Produce_get;// Compile/"Produce_get"
property * Produce_remove;// Compile/"Produce_remove"
property * compute_if_write_inverse;// Compile/"compute_if_write_inverse"
property * compute_set_write;// Compile/"compute_set_write"
property * Tighten;// Compile/"Tighten"
property * c_code_add_bag;// Optimize/"c_code_add_bag"
property * diet_ask;// claire/"diet?"
property * Produce_erase;// Compile/"Produce_erase"
property * lexical_num;// Compile/"lexical_num"
property * inner2outer_ask;// Compile/"inner2outer?"
property * pmember;// Optimize/"pmember"
property * c_code_select;// Optimize/"c_code_select"
property * inner_select;// Optimize/"inner_select"
property * compile_if_write;// Optimize/"compile_if_write"
property * compileEventMethod;// Optimize/"compileEventMethod"
property * s_test;// claire/"s_test"
property * c_srange;// Compile/"c_srange"
property * optimize_ask;// claire/"optimize?"
property * nativeVar_ask;// Compile/"nativeVar?"
property * simple_operations;// Compile/"simple_operations"
property * non_identifiable_set;// Compile/"non_identifiable_set"
property * sort_pattern_ask;// Optimize/"sort_pattern?"
property * sort_code;// Optimize/"sort_code"
property * return_type;// Compile/"return_type"
property * notice;// Compile/"notice"
property * infers_from;// Optimize/"infers_from"
property * show_opportunist;// Optimize/"show_opportunist"
property * home;// claire/"home"
property * instructions;// Compile/"instructions"
property * objects;// Compile/"objects"
property * properties;// Compile/"properties"
property * functions;// Compile/"functions"
property * need_to_close;// Compile/"need_to_close"
property * need_modules;// Compile/"need_modules"
property * legal_modules;// Compile/"legal_modules"
property * allocation;// Compile/"allocation"
property * protection;// Compile/"protection"
property * alloc_stack;// Compile/"alloc_stack"
property * ignore;// Compile/"ignore"
property * to_remove;// Compile/"to_remove"
property * cinterface;// Compile/"cinterface"
property * outfile;// Compile/"outfile"
property * max_vars;// Compile/"max_vars"
property * loop_gc;// Compile/"loop_gc"
property * loop_index;// Compile/"loop_index"
property * level;// Compile/"level"
property * in_method;// Compile/"in_method"
property * profile_ask;// Compile/"profile?"
property * cfile;// Compile/"cfile"
property * use_update;// Optimize/"use_update"
property * use_nth_equal;// Optimize/"use_nth="
property * online_ask;// Optimize/"online?"
property * recompute;// Optimize/"recompute"
property * unsure;// Optimize/"unsure"
property * knowns;// Optimize/"knowns"
property * headers;// claire/"headers"
property * debug_ask;// claire/"debug?"
property * active_ask;// claire/"active?"
property * safety;// claire/"safety"
property * env;// claire/"env"
property * naming;// claire/"naming"
property * libraries;// claire/"libraries"
property * loading_ask;// claire/"loading?"
property * class2file_ask;// claire/"class2file?"
property * greedy_ask;// claire/"greedy?"
property * libraries_dir;// claire/"libraries_dir"
property * headers_dir;// claire/"headers_dir"
property * options;// claire/"options"
property * ptype;// Optimize/"ptype"
property * c_code_call;// Optimize/"c_code_call"
property * c_register;// Optimize/"c_register"
property * c_gc_ask;// Compile/"c_gc?"
property * gcsafe_ask;// Optimize/"gcsafe?"
property * selector_psort;// Optimize/"selector_psort"
property * c_status;// Optimize/"c_status"
property * c_or;// Optimize/"c_or"
property * c_return;// Optimize/"c_return"
property * status_I;// Compile/"status!"
property * stable_ask;// Optimize/"stable?"
property * legal_ask;// Optimize/"legal?"
property * selector_register;// Optimize/"selector_register"
property * allocate_ask;// Optimize/"allocate?"
property * oload;// Optimize/"oload"
property * turbo;// Optimize/"turbo"
property * stats;// Optimize/"stats"

// module definition 
 void metaLoad();};

extern CL_EXPORT OptimizeClass Optimize;
extern CL_EXPORT NameSpace Compile;

#endif

