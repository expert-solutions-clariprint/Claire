// interface definition for module Core
#ifndef CLAIREH_Core
#define CLAIREH_Core

  
class CL_EXPORT ephemeral_object;
class CL_EXPORT lambda;
class CL_EXPORT general_error;
class CL_EXPORT read_slot_error;
class CL_EXPORT range_error;
class CL_EXPORT selector_error;
class CL_EXPORT return_error;
class CL_EXPORT global_variable;
class CL_EXPORT contradiction;
class CL_EXPORT Core_ffor_error;
class CL_EXPORT pretty_printer;
class CL_EXPORT much_too_far;
class CL_EXPORT Type;
class CL_EXPORT Union;
class CL_EXPORT Interval;
class CL_EXPORT Param;
class CL_EXPORT subtype;
class CL_EXPORT Reference;
class CL_EXPORT Core_dbg_frame;
class CL_EXPORT signal_handler;
class CL_EXPORT Core_itimer;
class CL_EXPORT process_status;
class CL_EXPORT char_star;
class CL_EXPORT device;
class CL_EXPORT filter;
class CL_EXPORT null_port;
class CL_EXPORT blob;
class CL_EXPORT descriptor;
class CL_EXPORT disk_file;
class CL_EXPORT cl_pipe;
class CL_EXPORT cl_socket;
class CL_EXPORT listener;
class CL_EXPORT buffer;
class CL_EXPORT line_buffer;
class CL_EXPORT line_counter;
class CL_EXPORT byte_counter;
class CL_EXPORT clob;
class CL_EXPORT Core_reverser;
class CL_EXPORT Core_FILE_star;
class CL_EXPORT Core_popen_device;
class CL_EXPORT invalid_option_argument;
class CL_EXPORT Core_option_instruction;
class CL_EXPORT Core_option_apply;
class CL_EXPORT Core_option_do;
class CL_EXPORT Core_option_if;
class CL_EXPORT Core_option_while;
class CL_EXPORT Core_option_for;

class CL_EXPORT ephemeral_object: public ClaireObject{ 
    public:}
  ;

class CL_EXPORT lambda: public ClaireObject{ 
    public:
       list *vars;
       OID body;
       CL_INT dimension;}
  ;

class CL_EXPORT general_error: public ClaireError{ 
    public:
       OID cause;
       OID arg;}
  ;

class CL_EXPORT read_slot_error: public ClaireError{ 
    public:
       OID arg;
       OID wrong;}
  ;

class CL_EXPORT range_error: public ClaireError{ 
    public:
       OID cause;
       OID arg;
       OID wrong;}
  ;

class CL_EXPORT selector_error: public ClaireError{ 
    public:
       OID selector;
       OID arg;}
  ;

class CL_EXPORT return_error: public ClaireError{ 
    public:
       OID arg;}
  ;

class CL_EXPORT global_variable: public SystemThing{ 
    public:
       OID value;
       ClaireType *range;
       ClaireBoolean *store_ask;}
  ;

class CL_EXPORT contradiction: public ClaireException{ 
    public:}
  ;

class CL_EXPORT Core_ffor_error: public ClaireException{ 
    public:
       char *childstr;
       CL_INT childpid;}
  ;

class CL_EXPORT pretty_printer: public thing{ 
    public:
       blob *cpretty;
       CL_INT cprevious;
       CL_INT index;
       CL_INT width;
       ClaireBoolean *pprint;
       ClaireBoolean *pbreak;
       list *cpstack;}
  ;

class CL_EXPORT much_too_far: public ClaireError{ 
    public:}
  ;

class CL_EXPORT Type: public ClaireType{ 
    public:}
  ;

class CL_EXPORT Union: public Type{ 
    public:
       ClaireType *t1;
       ClaireType *t2;}
  ;

class CL_EXPORT Interval: public Type{ 
    public:
       CL_INT arg1;
       CL_INT arg2;}
  ;

class CL_EXPORT Param: public Type{ 
    public:
       ClaireClass *arg;
       list *params;
       list *args;}
  ;

class CL_EXPORT subtype: public Type{ 
    public:
       ClaireClass *arg;
       ClaireType *t1;}
  ;

class CL_EXPORT Reference: public Type{ 
    public:
       list *args;
       CL_INT index;
       ClaireBoolean *arg;}
  ;

class CL_EXPORT Core_dbg_frame: public ephemeral_object{ 
    public:
       list *vars;
       CL_INT num;
       ClaireBoolean *step_ask;
       CL_INT dimension;
       OID frame_source;
       ClaireBoolean *compiled_ask;
       char *source;
       CL_INT line;
       CL_INT column;
       CL_INT length;
       ClaireBoolean *catch_ask;
       ClaireBoolean *new_ask;
       Core_dbg_frame *prev;
       Core_dbg_frame *next;}
  ;

class CL_EXPORT signal_handler: public thing{ 
    public:
       CL_INT signo;
       property *handler;}
  ;

class CL_EXPORT Core_itimer: public thing{ 
    public:
       CL_INT timerno;}
  ;

class CL_EXPORT process_status: public thing{ 
    public:}
  ;

class CL_EXPORT char_star: public ClaireImport{ 
    public:}
  ;

class CL_EXPORT device: public PortObject{ 
    public:
       list *filters;}
  ;

class CL_EXPORT filter: public PortObject{ 
    public:
       device *dev;
       PortObject *target;
       ClaireBoolean *close_target_ask;}
  ;

class CL_EXPORT null_port: public device{ 
    public:}
  ;

class CL_EXPORT blob: public device{ 
    public:
       char*data;
       CL_INT alloc_length;
       CL_INT read_index;
       CL_INT write_index;}
  ;

class CL_EXPORT descriptor: public device{ 
    public:
       CL_INT fd;
       ClaireBoolean *eof_reached_ask;}
  ;

class CL_EXPORT disk_file: public descriptor{ 
    public:
       char *file_path;
       ClaireBoolean *locked_ask;
       CL_INT mode;}
  ;

class CL_EXPORT cl_pipe: public descriptor{ 
    public:}
  ;

class CL_EXPORT cl_socket: public descriptor{ 
    public:
       char *address;
       CL_INT tcpport;}
  ;

class CL_EXPORT listener: public cl_socket{ 
    public:}
  ;

class CL_EXPORT buffer: public filter{ 
    public:
       CL_INT buffer_length;
       blob *pending_r;
       blob *pending_w;}
  ;

class CL_EXPORT line_buffer: public filter{ 
    public:
       blob *pending;}
  ;

class CL_EXPORT line_counter: public filter{ 
    public:
       CL_INT written_lines;
       CL_INT line_offset;
       CL_INT prev_line_offset;
       CL_INT read_lines;}
  ;

class CL_EXPORT byte_counter: public filter{ 
    public:
       CL_INT written_bytes;
       CL_INT read_bytes;}
  ;

class CL_EXPORT clob: public blob{ 
    public:}
  ;

class CL_EXPORT Core_reverser: public filter{ 
    public:
       CL_INT left_to_read;}
  ;

class CL_EXPORT Core_FILE_star: public ClaireImport{ 
    public:}
  ;

class CL_EXPORT Core_popen_device: public device{ 
    public:
       FILE*child_comm;
       CL_INT exitcode;}
  ;

class CL_EXPORT invalid_option_argument: public ClaireException{ 
    public:}
  ;

class CL_EXPORT Core_option_instruction: public ephemeral_object{ 
    public:
       char *filename;
       CL_INT line;}
  ;

class CL_EXPORT Core_option_apply: public Core_option_instruction{ 
    public:
       list *args;}
  ;

class CL_EXPORT Core_option_do: public Core_option_instruction{ 
    public:
       list *args;}
  ;

class CL_EXPORT Core_option_if: public Core_option_do{ 
    public:
       char *test;
       Core_option_instruction *other;}
  ;

class CL_EXPORT Core_option_while: public Core_option_do{ 
    public:
       char *test;}
  ;

class CL_EXPORT Core_option_for: public Core_option_do{ 
    public:
       char *forvar;
       char *forsetarg;
       char *such;}
  ;
extern CL_EXPORT void  index_jump_integer1(CL_INT n);
extern CL_EXPORT OID  eval_message_property(property *self,ClaireObject *r,CL_INT start,ClaireBoolean *int_ask);
extern CL_EXPORT OID  noeval_message_property2(property *self,CL_INT start);
extern CL_EXPORT OID  execute_method(method *self,CL_INT start,ClaireBoolean *int_ask);
extern CL_EXPORT OID  eval_any(OID self);
extern CL_EXPORT OID  self_eval_ClaireObject(ClaireObject *self);
extern CL_EXPORT method * inlineok_ask_method(method *self,char *s);
extern CL_EXPORT OID  get_slot(slot *s,ClaireObject *x);
extern CL_EXPORT OID  put_slot(slot *s,ClaireObject *x,OID y);
extern CL_EXPORT OID  get_property(property *self,ClaireObject *x);
extern CL_EXPORT OID  funcall_property(property *self,OID x);
extern CL_EXPORT OID  read_property(property *self,ClaireObject *x);
extern CL_EXPORT ClaireBoolean * hold_ask_property(property *self,ClaireObject *x,OID y);
extern CL_EXPORT void  write_property(property *self,ClaireObject *x,OID y);
extern CL_EXPORT OID  range_is_wrong_slot(slot *self,OID y);
extern CL_EXPORT void  put_property1(property *p,ClaireObject *x,CL_INT n,ClaireClass *s,OID y);
extern CL_EXPORT void  update_property(property *p,ClaireObject *x,CL_INT n,ClaireClass *s,OID y);
extern CL_EXPORT void  update_plus_relation(ClaireRelation *self,OID x,OID y);
extern CL_EXPORT void  update_dash_relation(ClaireRelation *r,OID x,OID y);
extern CL_EXPORT void  add_I_property(property *self,ClaireObject *x,CL_INT n,OID y);
extern CL_EXPORT ClaireBoolean * add_value_property(property *self,ClaireObject *x,CL_INT n,bag *l,OID y);
extern CL_EXPORT void  add_property(property *self,ClaireObject *x,OID y);
extern CL_EXPORT ClaireBoolean * known_ask_property(property *self,ClaireObject *x);
extern CL_EXPORT ClaireBoolean * unknown_ask_property(property *self,ClaireObject *x);
extern CL_EXPORT OID  delete_property(property *self,ClaireObject *x,OID y);
extern CL_EXPORT OID  erase_property(property *self,ClaireObject *x);
extern CL_EXPORT void  set_range_property(property *p,ClaireClass *c,ClaireType *r);
extern CL_EXPORT void  put_store_property2(property *self,ClaireObject *x,OID y,ClaireBoolean *b);
extern CL_EXPORT ClaireBoolean * multi_ask_any(OID x);
extern CL_EXPORT void  fastcall_relation2(ClaireRelation *r,OID x,OID y);
extern CL_EXPORT void  insert_definition_property(property *p,restriction *r);
extern CL_EXPORT list * initialize_restriction1(restriction *x,ClaireClass *d,list *l);
extern CL_EXPORT ClaireBoolean * uniform_restriction(restriction *x);
extern CL_EXPORT ClaireBoolean * uniform_property(property *p);
extern CL_EXPORT list * initialize_restriction2(restriction *x,list *l);
extern CL_EXPORT OID  hashinsert_restriction(restriction *m);
extern CL_EXPORT OID  hashinsert_class(ClaireClass *c,method *x);
extern CL_EXPORT OID  hashinsert_list(list *l,method *x);
extern CL_EXPORT ClaireObject * hashget_class(ClaireClass *c,property *p);
extern CL_EXPORT ClaireBoolean * join_list(list *x,list *y);
extern CL_EXPORT ClaireObject * _at_property1(property *self,ClaireClass *x);
extern CL_EXPORT ClaireObject * _at_property2(property *self,list *lt);
extern CL_EXPORT ClaireBoolean * matching_ask_list(list *l,CL_INT n,CL_INT m);
extern CL_EXPORT ClaireBoolean * vmatch_ask_any(OID t,OID x,CL_INT n);
extern CL_EXPORT ClaireBoolean * tmatch_ask_list(list *l,list *l2);
extern CL_EXPORT ClaireBoolean * tmatch_ask_any(OID t,OID t2,list *l);
extern CL_EXPORT ClaireObject * find_which_list1(list *l,ClaireClass *c,CL_INT n,CL_INT m);
extern CL_EXPORT ClaireObject * find_which_class1(ClaireClass *c,list *l,CL_INT n,CL_INT m);
extern CL_EXPORT char * release_void();
extern CL_EXPORT list * get_args_integer(CL_INT i);
extern CL_EXPORT OID  funcall_method1(method *self,OID x);
extern CL_EXPORT OID  funcall_method2(method *self,OID x,OID y);
extern CL_EXPORT OID  funcall_method3(method *self,OID x,OID y,OID z);
extern CL_EXPORT OID  apply_function(ClaireFunction *self,list *ls,list *l);
extern CL_EXPORT OID  call_property(property *p,listargs *l);
extern CL_EXPORT OID  apply_property(property *p,list *l);
extern CL_EXPORT OID  apply_method(method *m,list *l);
extern CL_EXPORT ClaireBoolean * identified_ask_class(ClaireClass *self);
extern CL_EXPORT ClaireBoolean * identical_ask_any(OID x,OID y);
extern CL_EXPORT OID  put_property2(property *self,ClaireObject *x,OID y);
extern CL_EXPORT void  add_value_property3(property *self,ClaireObject *x,OID y);
extern CL_EXPORT OID  nth_table1(table *a,OID x);
extern CL_EXPORT ClaireType * nth_table1_type(ClaireType *a,ClaireType *x);
extern CL_EXPORT OID  get_table(table *a,OID x);
extern CL_EXPORT ClaireType * get_table_type(ClaireType *a,ClaireType *x);
extern CL_EXPORT void  nth_equal_table1(table *a,OID x,OID y);
extern CL_EXPORT void  nth_put_table(table *a,OID x,OID y);
extern CL_EXPORT void  put_table(table *a,OID x,OID y);
extern CL_EXPORT void  add_table(table *a,OID x,OID y);
extern CL_EXPORT void  add_I_table(table *a,OID x,OID y);
extern CL_EXPORT ClaireBoolean * add_value_array(table *self,CL_INT n,bag *l,OID y);
extern CL_EXPORT void  add_value_table3(table *self,OID x,OID y);
extern CL_EXPORT OID  delete_table(table *a,OID x,OID y);
extern CL_EXPORT OID  nth_table2(table *a,OID x,OID y);
extern CL_EXPORT ClaireType * nth_table2_type(ClaireType *a,ClaireType *x,ClaireType *y);
extern CL_EXPORT void  nth_equal_table2(table *a,OID x,OID y,OID z);
extern CL_EXPORT CL_INT  get_index_table1(table *a,OID x);
extern CL_EXPORT CL_INT  get_index_table2(table *a,CL_INT x,CL_INT y);
extern CL_EXPORT void  erase_table(table *a);
extern CL_EXPORT void  self_print_table1_Core(table *self);
extern CL_EXPORT OID  funcall_lambda1(lambda *self,OID x);
extern CL_EXPORT OID  funcall_lambda2(lambda *self,OID x,OID y);
extern CL_EXPORT OID  funcall_lambda3(lambda *self,OID x,OID y,OID z);
extern CL_EXPORT void  check_inverse_any(OID _Zr1,OID _Zr2);
extern CL_EXPORT bag * invert_relation(ClaireRelation *r,OID x);
extern CL_EXPORT ClaireClass * domain_I_restriction(restriction *x);
extern CL_EXPORT set * methods_class(ClaireClass *d,ClaireClass *r);
extern CL_EXPORT void  reify_listargs(listargs *l);
extern CL_EXPORT void  self_print_general_error_Core(general_error *self);
extern CL_EXPORT void  self_print_read_slot_error_Core(read_slot_error *self);
extern CL_EXPORT void  self_print_range_error_Core(range_error *self);
extern CL_EXPORT void  self_print_selector_error_Core(selector_error *self);
extern CL_EXPORT void  self_print_return_error_Core(return_error *self);
extern CL_EXPORT global_variable * close_global_variable(global_variable *self);
extern CL_EXPORT void  self_print_system_error_Core(system_error *self);
extern CL_EXPORT void  self_print_contradiction_Core(contradiction *x);
extern CL_EXPORT void  format_string(char *self,list *larg);
extern CL_EXPORT OID  tformat_string(char *self,CL_INT i,list *l);
extern CL_EXPORT ClaireBoolean * should_trace_ask_module1(module *m,CL_INT i);
extern CL_EXPORT OID  mtformat_module1(module *m,char *self,CL_INT i,list *l);
extern CL_EXPORT void  princ_bag(bag *s);
extern CL_EXPORT void  contradiction_I_void();
extern CL_EXPORT char * _7_string(char *s,char *s2);
extern CL_EXPORT char * _7_dash_string(char *s1,char *s2);
extern CL_EXPORT void  self_print_ffor_error1_Core(Core_ffor_error *self);
extern CL_EXPORT CL_INT  min_integer1(CL_INT x,CL_INT y);
extern CL_EXPORT CL_INT  max_integer1(CL_INT x,CL_INT y);
extern CL_EXPORT double  min_float1(double x,double y);
extern CL_EXPORT OID  min_float1_(OID g0056,OID g0057);
extern CL_EXPORT double  max_float1(double x,double y);
extern CL_EXPORT OID  max_float1_(OID g0058,OID g0059);
extern CL_EXPORT void  print_in_string_void();
extern CL_EXPORT char * end_of_string_void();
extern CL_EXPORT CL_INT  buffer_length_void();
extern CL_EXPORT void  buffer_set_length_integer(CL_INT i);
extern CL_EXPORT void  apply_self_print_any(OID self);
extern CL_EXPORT void  self_print_any_Core(OID self);
extern CL_EXPORT void  self_print_exception1_Core(ClaireException *self);
extern CL_EXPORT void  self_print_boolean_Core(ClaireBoolean *self);
extern CL_EXPORT void  self_print_function_Core(ClaireFunction *self);
extern CL_EXPORT void  self_print_restriction_Core(restriction *self);
extern CL_EXPORT void  print_any(OID x);
extern CL_EXPORT ClaireBoolean * short_enough_integer(CL_INT self);
extern CL_EXPORT ClaireObject * complete_I_object(ClaireObject *self);
extern CL_EXPORT ClaireBoolean * not_any(OID self);
extern CL_EXPORT ClaireBoolean * _I_equal_any(OID x,OID y);
extern CL_EXPORT ClaireClass * owner_any(OID self);
extern CL_EXPORT ClaireBoolean * known_ask_any(OID self);
extern CL_EXPORT ClaireBoolean * unknown_ask_any(OID self);
extern CL_EXPORT OID  check_in_any(OID self,ClaireType *y);
extern CL_EXPORT bag * check_in_bag(bag *self,ClaireClass *c,ClaireType *y);
extern CL_EXPORT ClaireBoolean * _inf_any(OID self,OID x);
extern CL_EXPORT ClaireBoolean * _sup_any(OID self,OID x);
extern CL_EXPORT OID  ephemeral_class(ClaireClass *self);
extern CL_EXPORT OID  abstract_class(ClaireClass *c);
extern CL_EXPORT OID  final_class(ClaireClass *c);
extern CL_EXPORT ClaireObject * new_class1(ClaireClass *self);
extern CL_EXPORT ClaireType * new_class1_type(ClaireType *self);
extern CL_EXPORT thing * new_class2(ClaireClass *self,symbol *_Znom);
extern CL_EXPORT ClaireType * new_class2_type(ClaireType *self,ClaireType *_Znom);
extern CL_EXPORT ClaireType * new_object_class_type(ClaireType *self);
extern CL_EXPORT ClaireType * new_thing_class_type(ClaireType *self,ClaireType *_Znom);
extern CL_EXPORT ClaireClass * meet_class(ClaireClass *self,ClaireClass *ens);
extern CL_EXPORT ClaireBoolean * inherit_ask_class(ClaireClass *self,ClaireClass *ens);
extern CL_EXPORT OID  abstract_property(property *p);
extern CL_EXPORT void  final_relation(ClaireRelation *r);
extern CL_EXPORT module * close_module(module *self);
extern CL_EXPORT OID  get_symbol_string(char *self);
extern CL_EXPORT symbol * gensym_void();
extern CL_EXPORT OID  store_list4(list *l,CL_INT n,OID y);
extern CL_EXPORT OID  store_array1(OID *l,CL_INT n,OID y);
extern CL_EXPORT void  commit_integer(CL_INT n);
extern CL_EXPORT void  backtrack_integer(CL_INT n);
extern CL_EXPORT OID  store_listargs(listargs *l);
extern CL_EXPORT void  preread_property1_Core(property *p,OID o);
extern CL_EXPORT symbol * symbol_I_string2(char *self);
extern CL_EXPORT void  externC_string(char *s);
extern CL_EXPORT OID  externC_string2(char *s,ClaireClass *c);
extern CL_EXPORT ClaireType * externC_string2_type(ClaireType *s,ClaireType *c);
extern CL_EXPORT ClaireChar * nth_get_string(char *s,CL_INT n,CL_INT max);
extern CL_EXPORT void  nth_put_string(char *s,CL_INT n,ClaireChar *c,CL_INT max);
extern CL_EXPORT char * make_string_symbol(symbol *self);
extern CL_EXPORT void  self_print_symbol_Core(symbol *self);
extern CL_EXPORT CL_INT  _plus_integer(CL_INT self,CL_INT x);
extern CL_EXPORT ClaireType * _plus_integer_type(ClaireType *self,ClaireType *x);
extern CL_EXPORT CL_INT  _dash_integer1(CL_INT self,CL_INT x);
extern CL_EXPORT ClaireType * _dash_integer1_type(ClaireType *self,ClaireType *x);
extern CL_EXPORT CL_INT  _inf_inf_integer(CL_INT x,CL_INT n);
extern CL_EXPORT CL_INT  _sup_sup_integer(CL_INT x,CL_INT n);
extern CL_EXPORT CL_INT  and_integer(CL_INT x,CL_INT y);
extern CL_EXPORT CL_INT  or_integer(CL_INT x,CL_INT y);
extern CL_EXPORT ClaireBoolean * _inf_integer(CL_INT x,CL_INT y);
extern CL_EXPORT ClaireBoolean * _inf_equal_integer(CL_INT x,CL_INT y);
extern CL_EXPORT ClaireBoolean * _sup_integer(CL_INT x,CL_INT y);
extern CL_EXPORT ClaireBoolean * nth_integer(CL_INT self,CL_INT y);
extern CL_EXPORT ClaireBoolean * factor_ask_integer(CL_INT x,CL_INT y);
extern CL_EXPORT ClaireBoolean * divide_ask_integer(CL_INT x,CL_INT y);
extern CL_EXPORT OID  Id_any(OID x);
extern CL_EXPORT ClaireType * Id_any_type(ClaireType *x);
extern CL_EXPORT list * pair_any(OID x,OID y);
extern CL_EXPORT OID  pair_1_list(list *x);
extern CL_EXPORT ClaireType * pair_1_list_type(ClaireType *x);
extern CL_EXPORT OID  pair_2_list(list *x);
extern CL_EXPORT ClaireType * pair_2_list_type(ClaireType *x);
extern CL_EXPORT double  _plus_float(double self,double x);
extern CL_EXPORT OID  _plus_float_(OID g0076,OID g0077);
extern CL_EXPORT double  _dash_float(double self,double x);
extern CL_EXPORT OID  _dash_float_(OID g0078,OID g0079);
extern CL_EXPORT double  _star_float(double self,double x);
extern CL_EXPORT OID  _star_float_(OID g0080,OID g0081);
extern CL_EXPORT double  _7_float(double self,double x);
extern CL_EXPORT OID  _7_float_(OID g0082,OID g0083);
extern CL_EXPORT double  _dash_float2(double x);
extern CL_EXPORT OID  _dash_float2_(OID g0084);
extern CL_EXPORT double  sqrt_float(double self);
extern CL_EXPORT OID  sqrt_float_(OID g0085);
extern CL_EXPORT double  _exp_float(double self,double x);
extern CL_EXPORT OID  _exp_float_(OID g0086,OID g0087);
extern CL_EXPORT double  log_float(double x);
extern CL_EXPORT OID  log_float_(OID g0088);
extern CL_EXPORT double  tan_float1(double self);
extern CL_EXPORT OID  tan_float1_(OID g0089);
extern CL_EXPORT double  cos_float1(double self);
extern CL_EXPORT OID  cos_float1_(OID g0090);
extern CL_EXPORT double  sin_float1(double self);
extern CL_EXPORT OID  sin_float1_(OID g0091);
extern CL_EXPORT double  acos_float1(double self);
extern CL_EXPORT OID  acos_float1_(OID g0092);
extern CL_EXPORT double  asin_float1(double self);
extern CL_EXPORT OID  asin_float1_(OID g0093);
extern CL_EXPORT double  atan_float1(double self);
extern CL_EXPORT OID  atan_float1_(OID g0094);
extern CL_EXPORT double  tanh_float1(double self);
extern CL_EXPORT OID  tanh_float1_(OID g0095);
extern CL_EXPORT double  cosh_float1(double self);
extern CL_EXPORT OID  cosh_float1_(OID g0096);
extern CL_EXPORT double  sinh_float1(double self);
extern CL_EXPORT OID  sinh_float1_(OID g0097);
extern CL_EXPORT char * string_I_float(double self);
extern CL_EXPORT char * string_I_float_(OID g0098);
extern CL_EXPORT char * string_I_char1(ClaireChar *self);
extern CL_EXPORT CL_INT  length_bag(bag *self);
extern CL_EXPORT OID  nth_bag(bag *self,CL_INT x);
extern CL_EXPORT ClaireType * nth_bag_type(ClaireType *self,ClaireType *x);
extern CL_EXPORT OID  nth_get_bag(bag *self,CL_INT x);
extern CL_EXPORT OID  min_method(method *f,bag *self);
extern CL_EXPORT ClaireType * min_method_type(ClaireType *f,ClaireType *self);
extern CL_EXPORT OID  max_method(method *f,bag *self);
extern CL_EXPORT ClaireType * max_method_type(ClaireType *f,ClaireType *self);
extern CL_EXPORT list * _7_plus_bag(bag *x,bag *y);
extern CL_EXPORT OID  last_list(list *self);
extern CL_EXPORT ClaireType * last_list_type(ClaireType *self);
extern CL_EXPORT list * rmlast_list(list *self);
extern CL_EXPORT OID  nth_set_list(list *self,CL_INT x,OID y);
extern CL_EXPORT OID  car_list(list *self);
extern CL_EXPORT list * hashlist_integer(CL_INT n);
extern CL_EXPORT CL_INT  hashsize_list(list *l);
extern CL_EXPORT list * sort_method(method *f,list *self);
extern CL_EXPORT void  quicksort_list(list *self,method *f,CL_INT n,CL_INT m);
extern CL_EXPORT set * build_powerset_list(list *self);
extern CL_EXPORT list * make_copy_list_integer(CL_INT n,OID d);
extern CL_EXPORT set * difference_set(set *self,set *x);
extern CL_EXPORT void  nth_equal_array(OID *self,CL_INT x,OID y);
extern CL_EXPORT void  self_print_array_Core(OID *self);
extern CL_EXPORT ClaireBoolean * _inf_equal_char(ClaireChar *c1,ClaireChar *c2);
extern CL_EXPORT OID  kill_object(ClaireObject *self);
extern CL_EXPORT OID  kill_class(ClaireClass *self);
extern CL_EXPORT double  float_I_string(char *self);
extern CL_EXPORT OID  float_I_string_(char *g0109);
extern CL_EXPORT ClaireBoolean * unix_ask_void1();
extern CL_EXPORT char * strffloat_string1(char *f,double d);
extern CL_EXPORT char * strffloat_string1_(char *g0110,OID g0111);
extern CL_EXPORT void  chroot_string1(char *dir);
extern CL_EXPORT CL_INT  fork_void1();
extern CL_EXPORT ClaireBoolean * forker_ask_void1();
extern CL_EXPORT ClaireBoolean * forked_ask_void1();
extern CL_EXPORT ClaireBoolean * finite_ask_type(ClaireType *self);
extern CL_EXPORT bag * enumerate_any(OID self);
extern CL_EXPORT ClaireBoolean * _equaltype_ask_any(ClaireType *self,ClaireType *ens);
extern CL_EXPORT ClaireClass * sort_I_type(ClaireType *x);
extern CL_EXPORT ClaireBoolean * _Z_any1(OID self,ClaireClass *ens);
extern CL_EXPORT ClaireBoolean * Ztype_any(OID x,OID y);
extern CL_EXPORT void  self_print_Union_Core(Union *self);
extern CL_EXPORT ClaireBoolean * finite_ask_Union(Union *self);
extern CL_EXPORT void  self_print_Interval_Core(Interval *self);
extern CL_EXPORT ClaireBoolean * finite_ask_Interval(Interval *self);
extern CL_EXPORT Interval * _dash_dash_integer(CL_INT x,CL_INT y);
extern CL_EXPORT void  self_print_Param_Core(Param *self);
extern CL_EXPORT ClaireBoolean * finite_ask_Param(Param *self);
extern CL_EXPORT void  self_print_subtype_Core(subtype *self);
extern CL_EXPORT ClaireBoolean * finite_ask_subtype(subtype *self);
extern CL_EXPORT ClaireType * nth_class1(ClaireClass *self,ClaireType *x);
extern CL_EXPORT ClaireType * nth_class2(ClaireClass *self,list *l1,list *l2);
extern CL_EXPORT ClaireType * param_I_class(ClaireClass *self,ClaireType *tx);
extern CL_EXPORT ClaireType * nth_type(ClaireType *self);
extern CL_EXPORT ClaireBoolean * finite_ask_tuple(tuple *self);
extern CL_EXPORT void  self_print_Reference_Core(Reference *self);
extern CL_EXPORT OID  get_Reference(Reference *self,OID y);
extern CL_EXPORT OID  _at_Reference(Reference *self,list *l,OID y);
extern CL_EXPORT set * set_I_collection(ClaireCollection *x);
extern CL_EXPORT CL_INT  size_collection(ClaireCollection *x);
extern CL_EXPORT set * set_I_set(set *x);
extern CL_EXPORT CL_INT  size_set(set *x);
extern CL_EXPORT CL_INT  size_list2_Core(list *x);
extern CL_EXPORT set * set_I_class(ClaireClass *x);
extern CL_EXPORT CL_INT  size_class(ClaireClass *self);
extern CL_EXPORT set * set_I_Union(Union *x);
extern CL_EXPORT CL_INT  size_Union(Union *x);
extern CL_EXPORT set * set_I_Interval(Interval *x);
extern CL_EXPORT CL_INT  size_Interval(Interval *self);
extern CL_EXPORT set * set_I_Param(Param *x);
extern CL_EXPORT CL_INT  size_Param(Param *x);
extern CL_EXPORT set * set_I_subtype(subtype *x);
extern CL_EXPORT CL_INT  size_subtype(subtype *x);
extern CL_EXPORT set * set_I_tuple(tuple *x);
extern CL_EXPORT CL_INT  size_tuple(tuple *l);
extern CL_EXPORT ClaireBoolean * member_ask_any(OID x,ClaireType *y);
extern CL_EXPORT ClaireClass * class_I_type(ClaireType *x);
extern CL_EXPORT ClaireType * U_type(ClaireType *x,ClaireType *y);
extern CL_EXPORT ClaireType * _dot_dot_integer(CL_INT x,CL_INT y);
extern CL_EXPORT ClaireType * _dot_dot_integer_type(ClaireType *x,ClaireType *y);
extern CL_EXPORT bag * but_any(OID s,OID x);
extern CL_EXPORT ClaireType * but_any_type(ClaireType *s,ClaireType *x);
extern CL_EXPORT set * _backslash_type(ClaireType *x,ClaireType *y);
extern CL_EXPORT set * glb_set(set *x,ClaireType *y);
extern CL_EXPORT ClaireType * glb_Union(Union *x,ClaireType *y);
extern CL_EXPORT ClaireType * glb_Interval(Interval *x,ClaireType *y);
extern CL_EXPORT ClaireType * glb_class(ClaireClass *x,ClaireType *y);
extern CL_EXPORT ClaireType * glb_Param(Param *x,ClaireType *y);
extern CL_EXPORT ClaireType * glb_subtype(subtype *x,ClaireType *y);
extern CL_EXPORT ClaireType * glb_tuple(tuple *x,ClaireType *y);
extern CL_EXPORT ClaireType * glb_Reference(Reference *x,ClaireType *y);
extern CL_EXPORT ClaireType * _exp_type(ClaireType *x,ClaireType *y);
extern CL_EXPORT ClaireType * join_class(ClaireClass *x,ClaireClass *y);
extern CL_EXPORT list * _exp_list(list *x,list *y);
extern CL_EXPORT ClaireType * Uall_list(list *l);
extern CL_EXPORT ClaireBoolean * _inf_equalt_bag2(bag *s,ClaireType *y);
extern CL_EXPORT ClaireBoolean * _inf_equalt_class(ClaireClass *x,ClaireType *y);
extern CL_EXPORT ClaireBoolean * _inf_equalt_Union(Union *x,ClaireType *y);
extern CL_EXPORT ClaireBoolean * _inf_equalt_Interval(Interval *x,ClaireType *y);
extern CL_EXPORT ClaireBoolean * _inf_equalt_subtype(subtype *x,ClaireType *y);
extern CL_EXPORT ClaireBoolean * _inf_equalt_Param(Param *x,ClaireType *y);
extern CL_EXPORT ClaireBoolean * _inf_equalt_Reference(Reference *x,ClaireType *y);
extern CL_EXPORT ClaireBoolean * _inf_equalt_tuple(tuple *x,ClaireType *y);
extern CL_EXPORT ClaireBoolean * _inf_equalt_type(ClaireType *x,ClaireType *y);
extern CL_EXPORT ClaireBoolean * _inf_equal_type(ClaireType *x,ClaireType *y);
extern CL_EXPORT ClaireType * member_type(ClaireType *x);
extern CL_EXPORT ClaireType * of_extract_type(ClaireType *x);
extern CL_EXPORT ClaireType * _at_type(ClaireType *x,property *p);
extern CL_EXPORT ClaireBoolean * unique_ask_type(ClaireType *x);
extern CL_EXPORT OID  the_type(ClaireType *x);
extern CL_EXPORT CL_INT  integer_I_set(set *s);
extern CL_EXPORT set * make_set_integer(CL_INT x);
extern CL_EXPORT ClaireType * abstract_type_set(set *xt1);
extern CL_EXPORT ClaireType * abstract_type_operation(operation *p,ClaireType *xt1,ClaireType *xt2);
extern CL_EXPORT ClaireType * first_arg_type_type(ClaireType *x,ClaireType *y);
extern CL_EXPORT ClaireType * first_arg_type_type2(ClaireType *x,ClaireType *y,ClaireType *z);
extern CL_EXPORT ClaireType * second_arg_type_type(ClaireType *x,ClaireType *y);
extern CL_EXPORT ClaireType * meet_arg_types_type(ClaireType *x,ClaireType *y);
extern CL_EXPORT ClaireType * first_member_type_type(ClaireType *x,ClaireType *y);
extern CL_EXPORT ClaireType * append_type_type1(ClaireType *x,ClaireType *y);
extern CL_EXPORT ClaireType * cast_I_type_type1(ClaireType *x,ClaireType *y);
extern CL_EXPORT ClaireType * prealloc_set_type_type1(ClaireType *x,ClaireType *y);
extern CL_EXPORT ClaireType * prealloc_list_type_type1(ClaireType *x,ClaireType *y);
extern CL_EXPORT OID  nth_array(OID *self,CL_INT x);
extern CL_EXPORT ClaireType * nth_array_type(ClaireType *self,ClaireType *x);
extern CL_EXPORT ClaireType * make_array_integer_type(ClaireType *i,ClaireType *t,ClaireType *v);
extern CL_EXPORT list * make_list_integer2(CL_INT n,ClaireType *t,OID x);
extern CL_EXPORT ClaireType * make_list_integer2_type(ClaireType *n,ClaireType *t,ClaireType *x);
extern CL_EXPORT ClaireType * make_list_type_type1(ClaireType *x,ClaireType *y);
extern CL_EXPORT set * make_set_array(OID *self);
extern CL_EXPORT ClaireType * make_set_array_type(ClaireType *self);
extern CL_EXPORT ClaireType * list_I_array_type(ClaireType *a);
extern CL_EXPORT ClaireType * array_I_list_type(ClaireType *a);
extern CL_EXPORT ClaireType * set_I_bag_type(ClaireType *l);
extern CL_EXPORT ClaireType * list_I_set_type(ClaireType *l);
extern CL_EXPORT void  refine_append_of_bag1(bag *self,bag *x,bag *y);
extern CL_EXPORT void  set_user_string1(char *username);
extern CL_EXPORT tuple * sizeof_any1(OID x);
extern CL_EXPORT tuple * sizeof_any1_(OID g0138);
extern CL_EXPORT tuple * sizeof_class1(ClaireClass *c);
extern CL_EXPORT tuple * sizeof_class1_(ClaireClass *g0139);
extern CL_EXPORT void  reset_frame_stack_void1();
extern CL_EXPORT void  push_frame_any1(OID self);
extern CL_EXPORT void  pop_frame_void1();
extern CL_EXPORT void  push_arg_string1(char *nam,OID val);
extern CL_EXPORT void  push_var_string1(char *nam,OID val);
extern CL_EXPORT void  pop_var_void1();
extern CL_EXPORT void  update_var_string1(char *nam,OID val);
extern CL_EXPORT void  update_location_string1(char *f,CL_INT l,CL_INT c,CL_INT n);
extern CL_EXPORT void  break_if_needed_dbg_frame1(Core_dbg_frame *fr,CL_INT st);
extern CL_EXPORT void  push_handle_string1(char *oid);
extern CL_EXPORT void  pop_handle_string1(char *oid);
extern CL_EXPORT void  push_handle_frame_string1(char *f,CL_INT l,CL_INT c,CL_INT n,char *oid);
extern CL_EXPORT void  dload_string1(char *m,char *path);
extern CL_EXPORT property * signal_signal_handler(signal_handler *sig,property *p);
extern CL_EXPORT ClaireBoolean * meta_sighandler_integer(CL_INT sigv);
extern CL_EXPORT void  raise_signal_handler(signal_handler *sig);
extern CL_EXPORT void  kill_integer(CL_INT p,signal_handler *sig);
extern CL_EXPORT set * sigprocmask_void();
extern CL_EXPORT set * sigsetmask_type(ClaireType *self);
extern CL_EXPORT set * sigpending_void();
extern CL_EXPORT set * sigblock_type(ClaireType *self);
extern CL_EXPORT set * sigunblock_type(ClaireType *self);
extern CL_EXPORT void  sigsuspend_type(ClaireType *self);
extern CL_EXPORT tuple * setitimer_itimer(Core_itimer *it,CL_INT interval,CL_INT value);
extern CL_EXPORT tuple * setitimer_itimer_(Core_itimer *g0156,CL_INT g0157,CL_INT g0158);
extern CL_EXPORT tuple * getitimer_itimer(Core_itimer *it);
extern CL_EXPORT tuple * getitimer_itimer_(Core_itimer *g0159);
extern CL_EXPORT tuple * waitpid_integer1(CL_INT p,ClaireBoolean *block_ask);
extern CL_EXPORT tuple * waitpid_integer1_(CL_INT g0163,ClaireBoolean *g0164);
extern CL_EXPORT tuple * waitpid_integer2(CL_INT p);
extern CL_EXPORT tuple * waitpid_integer2_(CL_INT g0165);
extern CL_EXPORT char* _plus_char_star1(char*self,CL_INT n);
extern CL_EXPORT ClaireChar * nth_char_star1(char*self,CL_INT n);
extern CL_EXPORT void  nth_equal_char_star1(char*self,CL_INT n,ClaireChar *c);
extern CL_EXPORT char * string_I_char_star1(char*self,CL_INT len);
extern CL_EXPORT char* char_star_I_string1(char *self);
extern CL_EXPORT PortObject * get_top_most_port1(PortObject *self);
extern CL_EXPORT device * get_device_port1(PortObject *self);
extern CL_EXPORT filter * filter_I_filter1(filter *self,PortObject *p);
extern CL_EXPORT ClaireType * filter_I_filter1_type(ClaireType *self,ClaireType *p);
extern CL_EXPORT filter * close_target_I_filter1(filter *self);
extern CL_EXPORT ClaireType * close_target_I_filter1_type(ClaireType *self);
extern CL_EXPORT void  inner_print_device1(device *self);
extern CL_EXPORT void  inner_print_filter1(filter *self);
extern CL_EXPORT void  self_print_filter1_Core(filter *self);
extern CL_EXPORT void  self_print_device1_Core(device *self);
extern CL_EXPORT void  princ_port1(PortObject *self);
extern CL_EXPORT CL_INT  write_port_port1_Core(PortObject *self,char*buf,CL_INT len);
extern CL_EXPORT CL_INT  read_port_port1_Core(PortObject *self,char*buf,CL_INT len);
extern CL_EXPORT void  unget_port_port1_Core(PortObject *self,char*buf,CL_INT len);
extern CL_EXPORT ClaireBoolean * eof_port_ask_port1_Core(PortObject *self);
extern CL_EXPORT void  flush_port_port1_Core(PortObject *self);
extern CL_EXPORT void  close_port_port1_Core(PortObject *self);
extern CL_EXPORT ClaireBoolean * eof_ask_port1(PortObject *self);
extern CL_EXPORT char * fread_port4(PortObject *self,CL_INT n);
extern CL_EXPORT CL_INT  fread_port5(PortObject *self,char *s);
extern CL_EXPORT char * fread_port6(PortObject *self);
extern CL_EXPORT ClaireChar * getc_port1(PortObject *self);
extern CL_EXPORT void  unget_port1(PortObject *self,char *s);
extern CL_EXPORT void  unget_port2(PortObject *self,ClaireChar *c);
extern CL_EXPORT void  flush_port1(PortObject *self);
extern CL_EXPORT void  flush_port2(PortObject *self,CL_INT n);
extern CL_EXPORT CL_INT  fwrite_string2(char *self,PortObject *p);
extern CL_EXPORT void  putc_char1(ClaireChar *self,PortObject *p);
extern CL_EXPORT CL_INT  freadwrite_port3(PortObject *src,PortObject *trgt);
extern CL_EXPORT CL_INT  freadwrite_port4(PortObject *src,PortObject *trgt,CL_INT len);
extern CL_EXPORT CL_INT  fskip_port1(PortObject *self,CL_INT len);
extern CL_EXPORT void  fclose_port1(PortObject *self);
extern CL_EXPORT PortObject * get_filter_port1(PortObject *self,ClaireClass *c);
extern CL_EXPORT void  prefree_I_filter1(filter *self);
extern CL_EXPORT void  free_I_port2_Core(device *self);
extern CL_EXPORT null_port * null_I_void1();
extern CL_EXPORT CL_INT  read_port_null_port1_Core(null_port *self,char*buf,CL_INT len);
extern CL_EXPORT ClaireBoolean * eof_port_ask_null_port1_Core(null_port *self);
extern CL_EXPORT CL_INT  write_port_null_port1_Core(null_port *self,char*buf,CL_INT len);
extern CL_EXPORT void  flush_port_null_port1_Core(null_port *self);
extern CL_EXPORT void  close_port_null_port1_Core(null_port *self);
extern CL_EXPORT void  princ_blob1(blob *self);
extern CL_EXPORT void  write_attempt_blob1(blob *self,CL_INT n);
extern CL_EXPORT void  unget_port_blob1_Core(blob *self,char*buf,CL_INT len);
extern CL_EXPORT blob * blob_I_void1();
extern CL_EXPORT blob * blob_I_blob1(blob *p);
extern CL_EXPORT blob * blob_I_port1(PortObject *p);
extern CL_EXPORT blob * blob_I_string1(char *self);
extern CL_EXPORT blob * blob_I_integer1(CL_INT n);
extern CL_EXPORT clob * clob_I_void1();
extern CL_EXPORT clob * clob_I_string1(char *self);
extern CL_EXPORT clob * clob_I_port1(PortObject *self);
extern CL_EXPORT clob * clob_I_integer1(CL_INT n);
extern CL_EXPORT CL_INT  remain_for_write_blob1(blob *self);
extern CL_EXPORT CL_INT  remain_to_read_blob1(blob *self);
extern CL_EXPORT ClaireBoolean * eof_port_ask_blob1_Core(blob *self);
extern CL_EXPORT CL_INT  read_port_blob1_Core(blob *self,char*buf,CL_INT len);
extern CL_EXPORT CL_INT  write_port_blob1_Core(blob *self,char*buf,CL_INT len);
extern CL_EXPORT void  close_port_blob1_Core(blob *self);
extern CL_EXPORT char * string_I_blob1(blob *self);
extern CL_EXPORT ClaireChar * nth_blob1(blob *self,CL_INT n);
extern CL_EXPORT void  nth_equal_blob1(blob *self,CL_INT n,ClaireChar *c);
extern CL_EXPORT CL_INT  length_blob1(blob *self);
extern CL_EXPORT void  set_length_blob1(blob *self,CL_INT n);
extern CL_EXPORT char * substring_blob1(blob *self,CL_INT i,CL_INT j);
extern CL_EXPORT CL_INT  get_index_blob1(blob *self);
extern CL_EXPORT void  set_index_blob1(blob *self,CL_INT n);
extern CL_EXPORT Core_reverser * reverser_I_blob1(blob *self);
extern CL_EXPORT ClaireBoolean * eof_port_ask_reverser1_Core(Core_reverser *self);
extern CL_EXPORT CL_INT  read_port_reverser1_Core(Core_reverser *self,char*buf,CL_INT len);
extern CL_EXPORT buffer * buffer_I_port1(PortObject *self,CL_INT bufsize);
extern CL_EXPORT buffer * buffer_I_buffer1(buffer *self,PortObject *p);
extern CL_EXPORT void  princ_buffer1(buffer *self);
extern CL_EXPORT void  reset_buffer_port1(PortObject *self);
extern CL_EXPORT void  fill_read_buffer_buffer1(buffer *self);
extern CL_EXPORT ClaireBoolean * eof_port_ask_buffer1_Core(buffer *self);
extern CL_EXPORT CL_INT  read_port_buffer1_Core(buffer *self,char*buf,CL_INT len);
extern CL_EXPORT void  unget_port_buffer1_Core(buffer *self,char*buf,CL_INT len);
extern CL_EXPORT void  flush_port_buffer1_Core(buffer *self);
extern CL_EXPORT CL_INT  write_port_buffer1_Core(buffer *self,char*buf,CL_INT len);
extern CL_EXPORT void  close_port_buffer1_Core(buffer *self);
extern CL_EXPORT line_buffer * line_buffer_I_port1(PortObject *self);
extern CL_EXPORT void  flush_port_line_buffer1_Core(line_buffer *self);
extern CL_EXPORT void  close_port_line_buffer1_Core(line_buffer *self);
extern CL_EXPORT CL_INT  write_port_line_buffer1_Core(line_buffer *self,char*buf,CL_INT len);
extern CL_EXPORT byte_counter * byte_counter_I_port1(PortObject *self);
extern CL_EXPORT byte_counter * byte_counter_I_byte_counter1(byte_counter *self,PortObject *p);
extern CL_EXPORT CL_INT  write_port_byte_counter1_Core(byte_counter *self,char*buf,CL_INT len);
extern CL_EXPORT CL_INT  read_port_byte_counter1_Core(byte_counter *self,char*buf,CL_INT len);
extern CL_EXPORT ClaireBoolean * eof_port_ask_byte_counter1_Core(byte_counter *self);
extern CL_EXPORT void  princ_line_counter1(line_counter *self);
extern CL_EXPORT line_counter * line_counter_I_port1(PortObject *self);
extern CL_EXPORT line_counter * line_counter_I_line_counter1(line_counter *self,PortObject *p);
extern CL_EXPORT CL_INT  write_port_line_counter1_Core(line_counter *self,char*buf,CL_INT len);
extern CL_EXPORT CL_INT  read_port_line_counter1_Core(line_counter *self,char*buf,CL_INT len);
extern CL_EXPORT void  unget_port_line_counter1_Core(line_counter *self,char*buf,CL_INT len);
extern CL_EXPORT ClaireBoolean * eof_port_ask_line_counter1_Core(line_counter *self);
extern CL_EXPORT void  princ_descriptor1(descriptor *self);
extern CL_EXPORT void  close_port_descriptor1_Core(descriptor *self);
extern CL_EXPORT ClaireBoolean * eof_port_ask_descriptor1_Core(descriptor *self);
extern CL_EXPORT CL_INT  read_port_descriptor1_Core(descriptor *self,char*buf,CL_INT len);
extern CL_EXPORT CL_INT  write_port_descriptor1_Core(descriptor *self,char*buf,CL_INT len);
extern CL_EXPORT ClaireBoolean * terminal_ask_port1(PortObject *p);
extern CL_EXPORT descriptor * duplicate_descriptor1(descriptor *anfd);
extern CL_EXPORT descriptor * close_descriptor1(descriptor *self);
extern CL_EXPORT ClaireBoolean * select_ask_void1();
extern CL_EXPORT ClaireBoolean * select_ask_integer1(CL_INT ms);
extern CL_EXPORT descriptor * get_descriptor_port1(PortObject *self);
extern CL_EXPORT ClaireBoolean * readable_ask_port1(PortObject *self);
extern CL_EXPORT ClaireBoolean * readable_ask_descriptor1(descriptor *p);
extern CL_EXPORT ClaireBoolean * writable_ask_port1(PortObject *self);
extern CL_EXPORT ClaireBoolean * writable_ask_descriptor1(descriptor *p);
extern CL_EXPORT void  read_I_port1(PortObject *self);
extern CL_EXPORT void  read_I_descriptor1(descriptor *p);
extern CL_EXPORT void  write_I_port1(PortObject *self);
extern CL_EXPORT void  write_I_descriptor1(descriptor *p);
extern CL_EXPORT void  princ_disk_file1(disk_file *self);
extern CL_EXPORT disk_file * disk_file_I_string1(char *self,char *mod);
extern CL_EXPORT PortObject * reopen_port1(PortObject *self);
extern CL_EXPORT CL_INT  filepos_disk_file1(disk_file *self);
extern CL_EXPORT void  setfilepos_disk_file1(disk_file *self,CL_INT pos);
extern CL_EXPORT void  setfileend_disk_file1(disk_file *self);
extern CL_EXPORT buffer * fopen_string1(char *self,char *mode);
extern CL_EXPORT disk_file * get_disk_file_port1(PortObject *self);
extern CL_EXPORT void  flock_port1(PortObject *self);
extern CL_EXPORT void  funlock_port1(PortObject *self);
extern CL_EXPORT ClaireBoolean * islocked_ask_port1(PortObject *self);
extern CL_EXPORT tuple * pipe_I_void1();
extern CL_EXPORT tuple * pipe_I_void1_();
extern CL_EXPORT void  princ_pipe1(cl_pipe *self);
extern CL_EXPORT void  princ_socket1(cl_socket *self);
extern CL_EXPORT void  close_port_socket1_Core(cl_socket *self);
extern CL_EXPORT void  unlink_listener1(listener *self);
extern CL_EXPORT char * gethostname_void1();
extern CL_EXPORT cl_socket * client_I_string1(char *addr,CL_INT p);
extern CL_EXPORT cl_socket * client_I_string2(char *addr);
extern CL_EXPORT CL_INT  connect_string1(char *addr,CL_INT p);
extern CL_EXPORT listener * server_I_string2(char *addr);
extern CL_EXPORT listener * server_I_integer1(CL_INT p);
extern CL_EXPORT listener * server_I_string1(char *addr,CL_INT p,CL_INT qlen);
extern CL_EXPORT void  shutdown_socket1(cl_socket *self,char *mod);
extern CL_EXPORT void  linger_socket1(cl_socket *self);
extern CL_EXPORT cl_socket * accept_listener1(listener *self);
extern CL_EXPORT tuple * socketpair_void1();
extern CL_EXPORT tuple * socketpair_void1_();
extern CL_EXPORT CL_INT  read_port_socket1_Core(cl_socket *self,char*buf,CL_INT len);
extern CL_EXPORT CL_INT  write_port_socket1_Core(cl_socket *self,char*buf,CL_INT len);
extern CL_EXPORT void  print_source_location_port1(PortObject *self);
extern CL_EXPORT tuple * get_location_port1(PortObject *self);
extern CL_EXPORT tuple * get_location_port1_(PortObject *g0209);
extern CL_EXPORT ClaireBoolean * eof_port_ask_popen_device1_Core(Core_popen_device *self);
extern CL_EXPORT void  close_port_popen_device1_Core(Core_popen_device *self);
extern CL_EXPORT CL_INT  read_port_popen_device1_Core(Core_popen_device *self,char*buf,CL_INT len);
extern CL_EXPORT void  flush_port_popen_device1_Core(Core_popen_device *self);
extern CL_EXPORT CL_INT  write_port_popen_device1_Core(Core_popen_device *self,char*buf,CL_INT len);
extern CL_EXPORT Core_popen_device * popen_string1(char *file,char *mod);
extern CL_EXPORT char * bqexpand_string1(char *s);
extern CL_EXPORT tuple * option_usage_string1_Core(char *opt);
extern CL_EXPORT tuple * option_usage_string1_Core_(char *g0210);
extern CL_EXPORT tuple * option_usage_string3_Core(char *opt);
extern CL_EXPORT tuple * option_usage_string3_Core_(char *g0211);
extern CL_EXPORT tuple * option_usage_string4_Core(char *opt);
extern CL_EXPORT tuple * option_usage_string4_Core_(char *g0212);
extern CL_EXPORT tuple * option_usage_string5_Core(char *opt);
extern CL_EXPORT tuple * option_usage_string5_Core_(char *g0213);
extern CL_EXPORT tuple * option_usage_string6_Core(char *opt);
extern CL_EXPORT tuple * option_usage_string6_Core_(char *g0214);
extern CL_EXPORT tuple * option_usage_string8_Core(char *opt);
extern CL_EXPORT tuple * option_usage_string8_Core_(char *g0215);
extern CL_EXPORT tuple * option_usage_string9_Core(char *opt);
extern CL_EXPORT tuple * option_usage_string9_Core_(char *g0216);
extern CL_EXPORT tuple * option_usage_string10_Core(char *opt);
extern CL_EXPORT tuple * option_usage_string10_Core_(char *g0217);
extern CL_EXPORT tuple * option_usage_string11_Core(char *opt);
extern CL_EXPORT tuple * option_usage_string11_Core_(char *g0218);
extern CL_EXPORT tuple * option_usage_string12_Core(char *opt);
extern CL_EXPORT tuple * option_usage_string12_Core_(char *g0219);
extern CL_EXPORT tuple * option_usage_string32_Core(char *opt);
extern CL_EXPORT tuple * option_usage_string32_Core_(char *g0220);
extern CL_EXPORT void  print_var_string1(char *self);
extern CL_EXPORT void  print_option_string1(char *self);
extern CL_EXPORT void  print_module_module1(module *self);
extern CL_EXPORT char * parse_var_port1(PortObject *p,list *opts,list *vars,list *rngs);
extern CL_EXPORT void  parse_option_port1(PortObject *p,list *opts,list *vars,list *rngs);
extern CL_EXPORT list * print_back_option_usage_string1(char *self);
extern CL_EXPORT list * print_back_option_usage_port1(PortObject *p);
extern CL_EXPORT void  print_back_option_help_string1(char *self,list *l);
extern CL_EXPORT void  print_back_option_help_port1(PortObject *p,list *l);
extern CL_EXPORT OID  find_option_usage_integer1(CL_INT self);
extern CL_EXPORT OID  find_option_usage_string1(char *self);
extern CL_EXPORT void  print_option_usage_method1(method *r,module *m);
extern CL_EXPORT void  print_option_usage_method2(method *r);
extern CL_EXPORT void  print_option_usage_string1(char *opt);
extern CL_EXPORT void  print_option_usage_module1(module *m);
extern CL_EXPORT void  print_option_usage_void1();
extern CL_EXPORT void  print_option_index_method1(method *r,CL_INT i);
extern CL_EXPORT void  print_option_index_void1();
extern CL_EXPORT void  apply_option_begin_parse_void1();
extern CL_EXPORT void  apply_option_parsed_void1();
extern CL_EXPORT void  option_respond_string1_Core(char *opt,list *l);
extern CL_EXPORT void  option_respond_string2_Core(char *opt,list *l);
extern CL_EXPORT void  option_respond_string48_Core(char *opt,list *l);
extern CL_EXPORT void  option_respond_string4_Core(char *opt,list *l);
extern CL_EXPORT void  option_respond_string5_Core(char *opt,list *l);
extern CL_EXPORT ClaireBoolean * number_ask_string1(char *s);
extern CL_EXPORT void  option_respond_string7_Core(char *opt,list *l);
extern CL_EXPORT void  option_respond_string8_Core(char *opt,list *l);
extern CL_EXPORT void  option_respond_string9_Core(char *opt,list *l);
extern CL_EXPORT void  option_respond_string41_Core(char *opt,list *l);
extern CL_EXPORT void  option_respond_string40_Core(char *opt,list *l);
extern CL_EXPORT void  option_respond_string49_Core(char *opt,list *l);
extern CL_EXPORT tuple * option_usage_string33_Core(char *self);
extern CL_EXPORT tuple * option_usage_string33_Core_(char *g0272);
extern CL_EXPORT void  print_cmline_exception_void1();
extern CL_EXPORT void  parse_command_line_void1();
extern CL_EXPORT void  apply_command_line_list1(list *argv,ClaireBoolean *exit_ask);
extern CL_EXPORT void  option_respond_string45_Core(char *opt,list *l);
extern CL_EXPORT void  option_respond_string46_Core(char *opt,list *l);
extern CL_EXPORT char * read_cmd_string_port1(PortObject *b,char *eos);
extern CL_EXPORT char * shell_expand_string1(char *s);
extern CL_EXPORT void  read_option_line_port1(PortObject *f,list *opts);
extern CL_EXPORT Core_option_instruction * close_option_instruction1(Core_option_instruction *self);
extern CL_EXPORT void  read_option_file_port1(PortObject *b,Core_option_do *ado);
extern CL_EXPORT Core_option_if * read_option_if_port1(PortObject *b,list *opts);
extern CL_EXPORT Core_option_while * read_option_while_port1(PortObject *b,list *opts);
extern CL_EXPORT Core_option_for * read_option_for_port1(PortObject *b,list *opts);
extern CL_EXPORT void  eval_options_option_apply1(Core_option_apply *self);
extern CL_EXPORT void  eval_options_option_do1(Core_option_do *self);
extern CL_EXPORT void  eval_options_option_if1(Core_option_if *self);
extern CL_EXPORT void  eval_options_option_while1(Core_option_while *self);
extern CL_EXPORT void  eval_options_option_for1(Core_option_for *self);
extern CL_EXPORT void  option_respond_string47_Core(char *opt,list *l);
extern CL_EXPORT void  open_link_string1(char *url);
extern CL_EXPORT void  edit_link_bag1(bag *b);
extern CL_EXPORT void  edit_link_string1(char *src,CL_INT l,char *s);

// namespace class for Core 
class CL_EXPORT CoreClass: public NameSpace {
public:

  property * vars;
  property * dimension;
  property * version;
  ClaireClass * _ephemeral_object;
  ClaireClass * _lambda;
  property * execute;
  property * debug;
  property * eval_message;
  property * noeval_message;
  property * eval;
  property * call;
  property * self_eval;
  property * read;
  property * inlineok_ask;
  property * restore_state;
  property * hold_ask;
  property * write;
  property * range_is_wrong;
  property * update_plus;
  property * update_dash;
  property * add_value;
  property * known_ask;
  property * unknown_ask;
  property * erase;
  property * set_range;
  property * put_store;
  property * matching_ask;
  property * vmatch_ask;
  property * tmatch_ask;
  property * main;
  property * undefined_debug;
  property * multi_ask;
  operation * join;
  table * StopProperty;
  property * pname;
  property * reify;
  property * _star_stararg;
  property * args;
  property * value;
  ClaireClass * _general_error;
  ClaireClass * _read_slot_error;
  ClaireClass * _range_error;
  ClaireClass * _selector_error;
  ClaireClass * _return_error;
  ClaireClass * _global_variable;
  global_variable * err_l;
  ClaireClass * _contradiction;
  property * on_trace;
  operation * _inf_equal2;
  global_variable * contradiction_occurs;
  global_variable * nil;
  global_variable * claire_date;
  global_variable * _eof;
  global_variable * EOS;
  global_variable * _starfs_star;
  global_variable * _starps_star;
  operation * _7_dash;
  ClaireClass * _ffor_error;
  operation * _I_equal;
  operation * _inf_inf;
  operation * _sup_sup;
  operation * ClaireAnd;
  operation * ClaireOr;
  operation * U;
  operation * less_ask;
  operation * _and;
  operation * min;
  operation * max;
  operation * meet;
  operation * inherit_ask;
  property * cpstack;
  ClaireClass * _pretty_printer;
  pretty_printer * pretty;
  property * apply_self_print;
  property * short_enough;
  property * print;
  ClaireClass * _much_too_far;
  property * kill_I;
  global_variable * world_plus;
  global_variable * world_dash;
  global_variable * world_dash_I;
  property * preread;
  operation * pair;
  property * on_fork;
  property * on_forked;
  property * arg1;
  property * arg2;
  operation * _dash_dash;
  operation * _equaltype_ask;
  ClaireClass * _Type;
  ClaireClass * _Union;
  ClaireClass * _Interval;
  ClaireClass * _Param;
  ClaireClass * _subtype;
  ClaireClass * _Reference;
  operation * but;
  operation * _backslash;
  operation * glb;
  operation * _inf_equalt;
  keyword * none;
  ClaireClass * _dbg_frame;
  global_variable * top_frame;
  global_variable * current_frame;
  global_variable * STEP;
  global_variable * BREAKPOINTS;
  property * on_break_program;
  table * HANDLE_FRAMES;
  ClaireClass * _signal_handler;
  signal_handler * CL_SIGHUP;
  signal_handler * CL_SIGQUIT;
  signal_handler * CL_SIGILL;
  signal_handler * CL_SIGTRAP;
  signal_handler * CL_SIGABRT;
  signal_handler * CL_SIGEMT;
  signal_handler * CL_SIGFPE;
  signal_handler * CL_SIGKILL;
  signal_handler * CL_SIGBUS;
  signal_handler * CL_SIGSEGV;
  signal_handler * CL_SIGSYS;
  signal_handler * CL_SIGPIPE;
  signal_handler * CL_SIGALRM;
  signal_handler * CL_SIGTERM;
  signal_handler * CL_SIGURG;
  signal_handler * CL_SIGSTOP;
  signal_handler * CL_SIGTSTP;
  signal_handler * CL_SIGCONT;
  signal_handler * CL_SIGCHLD;
  signal_handler * CL_SIGTTIN;
  signal_handler * CL_SIGTTOU;
  signal_handler * CL_SIGIO;
  signal_handler * CL_SIGXCPU;
  signal_handler * CL_SIGXFSZ;
  signal_handler * CL_SIGVTALRM;
  signal_handler * CL_SIGPROF;
  signal_handler * CL_SIGWINCH;
  signal_handler * CL_SIGINFO;
  signal_handler * CL_SIGUSR1;
  signal_handler * CL_SIGUSR2;
  signal_handler * CL_SIGINT;
  property * CL_SIG_DFL;
  property * CL_SIG_IGN;
  property * SIG_EXT;
  table * SIG_MAP;
  global_variable * SHOULD_BREAK_ask;
  ClaireClass * _itimer;
  Core_itimer * CL_ITIMER_REAL;
  Core_itimer * CL_ITIMER_VIRTUAL;
  Core_itimer * CL_ITIMER_PROF;
  ClaireClass * _process_status;
  process_status * CL_WRUNNING;
  process_status * CL_WEXITED;
  process_status * CL_WSIGNALED;
  process_status * CL_WSTOPPED;
  ClaireClass * _char_star;
  ClaireClass * _device;
  ClaireClass * _filter;
  ClaireClass * _null_port;
  ClaireClass * _blob;
  ClaireClass * _descriptor;
  ClaireClass * _disk_file;
  ClaireClass * _pipe;
  ClaireClass * _socket;
  ClaireClass * _listener;
  ClaireClass * _buffer;
  ClaireClass * _line_buffer;
  ClaireClass * _line_counter;
  ClaireClass * _byte_counter;
  property * eof_port_ask;
  property * read_port;
  property * unget_port;
  property * write_port;
  property * flush_port;
  property * close_port;
  global_variable * null;
  ClaireClass * _clob;
  global_variable * port_I;
  ClaireClass * _reverser;
  global_variable * Clib_stdin;
  global_variable * Clib_stdout;
  global_variable * Clib_stderr;
  global_variable * cl_stdin;
  global_variable * cl_stdout;
  global_variable * cl_stderr;
  global_variable * OPEN_MODE;
  ClaireClass * _FILE_star;
  ClaireClass * _popen_device;
  property * option_respond;
  property * option_parsed;
  property * option_begin_parse;
  property * option_usage;
  global_variable * CMD_SEPS;
  global_variable * VAR_END;
  global_variable * OPT_END;
  ClaireClass * _invalid_option_argument;
  global_variable * _Zqonerror;
  global_variable * _Zerrassegv;
  global_variable * DYNLOADS;
  property * toplevel;
  property * on_option_error;
  global_variable * OPTION_LINE;
  global_variable * OPTION_PATH;
  ClaireClass * _option_instruction;
  ClaireClass * _option_apply;
  ClaireClass * _option_do;
  ClaireClass * _option_if;
  ClaireClass * _option_while;
  ClaireClass * _option_for;
  property * option_push;
  property * option_test;
  property * option_pop;
  property * option_continue_ask;
  property * option_start_loop;
property * initialize;// Core/"initialize"
property * uniform;// Core/"uniform"
property * hashinsert;// Core/"hashinsert"
property * hashget;// Core/"hashget"
property * param_I;// Core/"param!"
property * size;// claire/"size"
property * end_of_string;// claire/"end_of_string"
property * apply;// claire/"apply"
property * finite_ask;// claire/"finite?"
property * release;// claire/"release"
operation * _at;// claire/"@"
property * methods;// claire/"methods"
property * get_args;// mClaire/"get_args"
operation * _plus;// claire/"+"
property * identified_ask;// Core/"identified?"
property * identical_ask;// claire/"identical?"
property * factor_ask;// claire/"factor?"
property * divide_ask;// claire/"divide?"
property * Id;// claire/"Id"
property * pair_1;// claire/"pair_1"
property * pair_2;// claire/"pair_2"
property * check_inverse;// Core/"check_inverse"
property * invert;// claire/"invert"
property * cause;// mClaire/"cause"
property * domain_I;// claire/"domain!"
property * class_I;// claire/"class!"
property * owner;// claire/"owner"
property * check_in;// claire/"check_in"
property * wrong;// Core/"wrong"
property * format;// claire/"format"
property * tformat;// Core/"tformat"
property * contradiction_I;// claire/"contradiction!"
property * get_stack;// mClaire/"get_stack"
property * put_stack;// mClaire/"put_stack"
property * push_I;// mClaire/"push!"
property * gc;// claire/"gc"
property * read_option_line;// Core/"read_option_line"
property * filename;// Core/"filename"
property * test;// Core/"test"
property * other;// Core/"other"
property * forvar;// Core/"forvar"
property * forsetarg;// Core/"forsetarg"
property * such;// Core/"such"
property * read_option_file;// Core/"read_option_file"
property * read_option_if;// Core/"read_option_if"
property * read_option_while;// Core/"read_option_while"
property * read_option_for;// Core/"read_option_for"
property * eval_options;// Core/"eval_options"
property * time_get;// claire/"time_get"
property * time_set;// claire/"time_set"
property * time_show;// claire/"time_show"
property * print_in_string;// claire/"print_in_string"
property * buffer_length;// mClaire/"buffer_length"
property * buffer_set_length;// mClaire/"buffer_set_length"
property * NOT;// claire/"not"
property * make_function;// claire/"make_function"
property * externC;// claire/"externC"
property * shell;// claire/"shell"
property * getenv;// claire/"getenv"
property * _dash_dash_ask;// Core/"--?"
property * exit;// claire/"exit"
property * last;// claire/"last"
property * rmlast;// claire/"rmlast"
property * car;// claire/"car"
property * hashlist;// Core/"hashlist"
property * hashsize;// Core/"hashsize"
property * sort;// claire/"sort"
property * quicksort;// Core/"quicksort"
property * build_powerset;// Core/"build_powerset"
property * difference;// claire/"difference"
property * of_extract;// Core/"of_extract"
property * member;// claire/"member"
property * Address;// Core/"Address"
property * Oid;// Core/"Oid"
property * Oid_tilda;// Core/"Oid~"
property * get_value;// claire/"get_value"
property * enumerate;// Core/"enumerate"
property * t1;// mClaire/"t1"
property * t2;// mClaire/"t2"
property * tuple_I;// claire/"tuple!"
property * Uall;// claire/"Uall"
property * unique_ask;// claire/"unique?"
property * the;// claire/"the"
property * abstract_type;// Core/"abstract_type"
property * NEW;// claire/"new"
property * sqrt;// claire/"sqrt"
property * insert_definition;// Core/"insert_definition"
property * make_array;// claire/"make_array"
property * cpretty;// mClaire/"cpretty"
property * cprevious;// mClaire/"cprevious"
property * width;// mClaire/"width"
property * pprint;// mClaire/"pprint"
property * pbreak;// mClaire/"pbreak"
property * base_I;// mClaire/"base!"
property * set_base;// mClaire/"set_base"
property * index_I;// mClaire/"index!"
property * complete_I;// mClaire/"complete!"
property * _Ztype;// mClaire/"%type"
property * update;// mClaire/"update"
property * make_set;// claire/"make_set"
property * get_symbol;// claire/"get_symbol"
property * time_read;// claire/"time_read"
property * first_arg_type;// Core/"first_arg_type"
property * second_arg_type;// Core/"second_arg_type"
property * meet_arg_types;// Core/"meet_arg_types"
property * make_copy_list;// claire/"make_copy_list"
property * log;// claire/"log"
property * new_I;// mClaire/"new!"
property * first_member_type;// Core/"first_member_type"
property * signo;// Core/"signo"
property * handler;// Core/"handler"
property * signal;// claire/"signal"
property * meta_sighandler;// Core/"meta_sighandler"
property * raise;// claire/"raise"
property * sigprocmask;// claire/"sigprocmask"
property * sigsetmask;// claire/"sigsetmask"
property * sigpending;// claire/"sigpending"
property * sigblock;// claire/"sigblock"
property * sigunblock;// claire/"sigunblock"
property * sigsuspend;// claire/"sigsuspend"
property * timerno;// Core/"timerno"
property * setitimer;// claire/"setitimer"
property * getitimer;// claire/"getitimer"
property * waitpid;// claire/"waitpid"
property * childstr;// Core/"childstr"
property * childpid;// Core/"childpid"
property * set_color;// claire/"set_color"
property * mtformat;// claire/"mtformat"
property * unix_ask;// Core/"unix?"
property * refine_append_of;// Core/"refine_append_of"
property * append_type;// Core/"append_type"
property * cast_I_type;// Core/"cast!_type"
property * prealloc_set_type;// Core/"prealloc_set_type"
property * prealloc_list_type;// Core/"prealloc_list_type"
property * make_list_type;// Core/"make_list_type"
property * strffloat;// claire/"strffloat"
property * print_option_index;// Core/"print_option_index"
property * print_var;// Core/"print_var"
property * print_option;// Core/"print_option"
property * print_module;// Core/"print_module"
property * parse_var;// Core/"parse_var"
property * parse_option;// Core/"parse_option"
property * print_back_option_usage;// Core/"print_back_option_usage"
property * print_back_option_help;// Core/"print_back_option_help"
property * find_option_usage;// Core/"find_option_usage"
property * print_option_usage;// Core/"print_option_usage"
property * apply_option_parsed;// Core/"apply_option_parsed"
property * number_ask;// Core/"number?"
property * print_cmline_exception;// Core/"print_cmline_exception"
property * parse_command_line;// Core/"parse_command_line"
property * set_user;// claire/"set_user"
property * putc;// claire/"putc"
property * flush;// claire/"flush"
property * eof_ask;// claire/"eof?"
property * fopen;// claire/"fopen"
property * firstc;// Core/"firstc"
property * closed_ask;// Core/"closed?"
property * filters;// Core/"filters"
property * dev;// Core/"dev"
property * target;// claire/"target"
property * close_target_ask;// Core/"close_target?"
property * get_top_most;// Core/"get_top_most"
property * get_device;// Core/"get_device"
property * filter_I;// claire/"filter!"
property * close_target_I;// claire/"close_target!"
property * remain_to_read;// claire/"remain_to_read"
property * getc;// claire/"getc"
property * unget;// claire/"unget"
property * pending;// Core/"pending"
property * line_buffer_I;// claire/"line_buffer!"
property * duplicate;// Core/"duplicate"
property * fskip;// claire/"fskip"
property * get_filter;// claire/"get_filter"
property * null_I;// claire/"null!"
property * data;// Core/"data"
property * alloc_length;// Core/"alloc_length"
property * read_index;// Core/"read_index"
property * write_index;// Core/"write_index"
property * write_attempt;// Core/"write_attempt"
property * remain_for_write;// Core/"remain_for_write"
property * blob_I;// claire/"blob!"
property * shutdown;// claire/"shutdown"
property * set_length;// claire/"set_length"
property * left_to_read;// Core/"left_to_read"
property * reverser_I;// claire/"reverser!"
property * pending_r;// Core/"pending_r"
property * pending_w;// Core/"pending_w"
property * buffer_I;// claire/"buffer!"
property * reset_buffer;// claire/"reset_buffer"
property * fill_read_buffer;// Core/"fill_read_buffer"
property * written_bytes;// claire/"written_bytes"
property * read_bytes;// claire/"read_bytes"
property * byte_counter_I;// claire/"byte_counter!"
property * written_lines;// claire/"written_lines"
property * read_lines;// claire/"read_lines"
property * line_counter_I;// claire/"line_counter!"
property * fd;// Core/"fd"
property * eof_reached_ask;// Core/"eof_reached?"
property * terminal_ask;// Core/"terminal?"
property * select_ask;// claire/"select?"
property * get_descriptor;// Core/"get_descriptor"
property * file_path;// Core/"file_path"
property * locked_ask;// Core/"locked?"
property * mode;// Core/"mode"
property * disk_file_I;// Core/"disk_file!"
property * get_disk_file;// Core/"get_disk_file"
property * pipe_I;// Core/"pipe!"
property * address;// Core/"address"
property * tcpport;// Core/"tcpport"
property * gethostname;// claire/"gethostname"
property * client_I;// claire/"client!"
property * connect;// Core/"connect"
property * server_I;// claire/"server!"
property * linger;// claire/"linger"
property * accept;// claire/"accept"
property * socketpair;// claire/"socketpair"
property * print_source_location;// Core/"print_source_location"
property * get_location;// Core/"get_location"
property * line_offset;// claire/"line_offset"
property * prev_line_offset;// claire/"prev_line_offset"
property * fork;// claire/"fork"
property * forker_ask;// claire/"forker?"
property * forked_ask;// claire/"forked?"
property * reopen;// claire/"reopen"
property * should_trace_ask;// Core/"should_trace?"
property * child_comm;// Core/"child_comm"
property * popen;// claire/"popen"
property * bqexpand;// claire/"bqexpand"
property * tan;// claire/"tan"
property * edit_link;// Core/"edit_link"
property * cos;// claire/"cos"
property * sin;// claire/"sin"
property * acos;// claire/"acos"
property * asin;// claire/"asin"
property * atan;// claire/"atan"
property * tanh;// claire/"tanh"
property * cosh;// claire/"cosh"
property * sinh;// claire/"sinh"
property * fclose;// claire/"fclose"
property * chroot;// claire/"chroot"
property * inner_print;// Core/"inner_print"
property * exitcode;// Core/"exitcode"
property * clob_I;// claire/"clob!"
property * cl_sizeof;// claire/"sizeof"
property * filepos;// claire/"filepos"
property * setfilepos;// claire/"setfilepos"
property * setfileend;// claire/"setfileend"
property * readable_ask;// claire/"readable?"
property * writable_ask;// claire/"writable?"
property * read_I;// claire/"read!"
property * write_I;// claire/"write!"
property * char_star_I;// claire/"char*!"
property * shell_expand;// claire/"shell_expand"
property * open_link;// Core/"open_link"
property * apply_command_line;// Core/"apply_command_line"
property * read_cmd_string;// Core/"read_cmd_string"
property * apply_option_begin_parse;// Core/"apply_option_begin_parse"
property * num;// Core/"num"
property * step_ask;// Core/"step?"
property * frame_source;// Core/"frame_source"
property * compiled_ask;// Core/"compiled?"
property * line;// Core/"line"
property * column;// Core/"column"
property * catch_ask;// Core/"catch?"
property * new_ask;// Core/"new?"
property * prev;// Core/"prev"
property * next;// Core/"next"
property * reset_frame_stack;// Core/"reset_frame_stack"
property * push_frame;// Core/"push_frame"
property * pop_frame;// Core/"pop_frame"
property * push_arg;// Core/"push_arg"
property * push_var;// Core/"push_var"
property * pop_var;// Core/"pop_var"
property * update_var;// Core/"update_var"
property * update_location;// Core/"update_location"
property * break_if_needed;// Core/"break_if_needed"
property * push_handle;// Core/"push_handle"
property * pop_handle;// Core/"pop_handle"
property * push_handle_frame;// Core/"push_handle_frame"
property * dload;// claire/"dload"

// module definition 
 void metaLoad();};

extern CL_EXPORT CoreClass Core;

#endif

