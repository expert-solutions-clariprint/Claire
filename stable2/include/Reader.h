// interface definition for module Reader
#ifndef CLAIREH_Reader
#define CLAIREH_Reader

  
class CL_EXPORT delimiter;
class CL_EXPORT reserved_keyword;
class CL_EXPORT meta_reader;
class CL_EXPORT Reader_syntax_error;
class CL_EXPORT PRcount;
class CL_EXPORT Reader_stdin_line_reader;
class CL_EXPORT Reader_execution_context;
class CL_EXPORT Reader_abort_debug;
class CL_EXPORT Reader_debug_fatal_error;
class CL_EXPORT Reader_command_line_error;
class CL_EXPORT Reader_DebugVariable;
class CL_EXPORT Reader_self_html_converter;
class CL_EXPORT Reader_hash_table;
class CL_EXPORT Reader_map_node;
class CL_EXPORT Reader_doc_context;
class CL_EXPORT Reader_doc_item;
class CL_EXPORT Reader_doc_link;
class CL_EXPORT Reader_doc_copyright;
class CL_EXPORT Reader_doc_preamble;
class CL_EXPORT Reader_doc_author;
class CL_EXPORT Reader_doc_category;
class CL_EXPORT Reader_doc_entity;
class CL_EXPORT Reader_doc_section;
class CL_EXPORT Reader_doc_option;
class CL_EXPORT Reader_doc_method;
class CL_EXPORT Reader_doc_class;
class CL_EXPORT Reader_doc_global;
class CL_EXPORT Reader_doc_interface;
class CL_EXPORT Reader_doc_table;
class CL_EXPORT Reader_bad_eval;

class CL_EXPORT delimiter: public global_variable{ 
    public:}
  ;

class CL_EXPORT reserved_keyword: public keyword{ 
    public:}
  ;

class CL_EXPORT meta_reader: public thing{ 
    public:
       char *source;
       CL_INT s_index;
       PortObject *fromp;
       CL_INT nb_line;
       char *external;
       CL_INT index;
       OID last_form;
       CL_INT maxstack;
       ClaireBoolean *toplevel;
       CL_INT eof;
       CL_INT space;
       CL_INT tab;
       OID bracket;
       OID paren;
       OID comma;
       OID curly;
       ClaireBoolean *last_arrow;
       set *s_properties;
       ClaireBoolean *cascade_ask;
       ClaireBoolean *wcl_ask;}
  ;

class CL_EXPORT Reader_syntax_error: public ClaireException{ 
    public:
       CL_INT code;
       char *cause;
       list *args;}
  ;

class CL_EXPORT PRcount: public ClaireObject{ 
    public:
       CL_INT rtime;
       CL_INT rdepth;
       CL_INT rnum;
       CL_INT rloop;
       CL_INT rstart;}
  ;

class CL_EXPORT Reader_stdin_line_reader: public device{ 
    public:
       blob *line;}
  ;

class CL_EXPORT Reader_execution_context: public ephemeral_object{ 
    public:
       list *module_stack;
       ClaireEnvironment *saved_system;
       meta_reader *saved_reader;
       ClaireBoolean *debug_context_ask;}
  ;

class CL_EXPORT Reader_abort_debug: public ClaireException{ 
    public:}
  ;

class CL_EXPORT Reader_debug_fatal_error: public Reader_abort_debug{ 
    public:
       ClaireException *src;}
  ;

class CL_EXPORT Reader_command_line_error: public ClaireException{ 
    public:
       OID src;}
  ;

class CL_EXPORT Reader_DebugVariable: public ephemeral_object{ 
    public:
       OID value;}
  ;

class CL_EXPORT Reader_self_html_converter: public device{ 
    public:
       blob *src;}
  ;

class CL_EXPORT Reader_hash_table: public ephemeral_object{ 
    public:
       CL_INT hash_max;
       list *content;}
  ;

class CL_EXPORT Reader_map_node: public ephemeral_object{ 
    public:
       OID nkey;
       OID nval;
       Reader_map_node *next;}
  ;

class CL_EXPORT Reader_doc_context: public ephemeral_object{ 
    public:
       CL_INT generation_mode;
       ClaireBoolean *add_source_links_ask;
       module *source;
       char *index;
       char *directory;
       char *color;
       ClaireBoolean *bold_ask;
       ClaireBoolean *in_code_ask;
       ClaireBoolean *in_a_ask;}
  ;

class CL_EXPORT Reader_doc_item: public ClaireObject{ 
    public:
       OID src_location;
       char *documentation;
       ClaireBoolean *xl_ask;
       char *name;}
  ;

class CL_EXPORT Reader_doc_link: public Reader_doc_item{ 
    public:
       char *oid;
       char *src;}
  ;

class CL_EXPORT Reader_doc_copyright: public Reader_doc_item{ 
    public:}
  ;

class CL_EXPORT Reader_doc_preamble: public Reader_doc_item{ 
    public:}
  ;

class CL_EXPORT Reader_doc_author: public Reader_doc_item{ 
    public:}
  ;

class CL_EXPORT Reader_doc_category: public Reader_doc_item{ 
    public:
       Reader_doc_section *section;
       ClaireBoolean *exploit_ask;
       list *items;
       list *entity_names;
       list *aliases;
       char *aname;}
  ;

class CL_EXPORT Reader_doc_entity: public Reader_doc_item{ 
    public:
       OID source;
       symbol *ident;
       Reader_doc_category *category;}
  ;

class CL_EXPORT Reader_doc_section: public Reader_doc_item{ 
    public:
       ClaireBoolean *exploit_ask;
       list *categories;}
  ;

class CL_EXPORT Reader_doc_option: public Reader_doc_item{ 
    public:
       char *usage;
       module *from_module;
       list *opts;
       list *vars;
       list *ranges;}
  ;

class CL_EXPORT Reader_doc_method: public Reader_doc_entity{ 
    public:
       list *vars;
       OID mrange;
       ClaireBoolean *inline_ask;
       list *var_ranges;}
  ;

class CL_EXPORT Reader_doc_class: public Reader_doc_entity{ 
    public:
       OID superclass;}
  ;

class CL_EXPORT Reader_doc_global: public Reader_doc_entity{ 
    public:
       ClaireBoolean *constant_ask;
       OID grange;
       OID value;}
  ;

class CL_EXPORT Reader_doc_interface: public Reader_doc_entity{ 
    public:
       OID arg;
       list *args;}
  ;

class CL_EXPORT Reader_doc_table: public Reader_doc_entity{ 
    public:
       OID trange;
       OID tbody;}
  ;

class CL_EXPORT Reader_bad_eval: public ClaireException{ 
    public:
       ClaireException *src;}
  ;
extern CL_EXPORT ClaireBoolean * keyword_ask_any(OID x);
extern CL_EXPORT CL_INT  get_lines_meta_reader(meta_reader *r);
extern CL_EXPORT CL_INT  next_meta_reader(meta_reader *r);
extern CL_EXPORT CL_INT  firstc_meta_reader(meta_reader *r);
extern CL_EXPORT OID  stop_ask_integer(CL_INT n);
extern CL_EXPORT OID  nextunit_meta_reader(meta_reader *r);
extern CL_EXPORT OID  nexts_meta_reader(meta_reader *r,keyword *e);
extern CL_EXPORT ClaireBoolean * leaf_wcl_intruction_ask_any1(OID self);
extern CL_EXPORT ClaireBoolean * head_wcl_intruction_ask_any1(OID self);
extern CL_EXPORT OID  loopexp_meta_reader(meta_reader *r,OID x,keyword *e,ClaireBoolean *loop);
extern CL_EXPORT OID  extended_operator_property1(property *p,OID x,OID y);
extern CL_EXPORT OID  nexte_meta_reader(meta_reader *r);
extern CL_EXPORT void  add_ident_string1(char *s);
extern CL_EXPORT OID  read_ident_meta_reader1(meta_reader *r);
extern CL_EXPORT OID  nextexp_meta_reader(meta_reader *r,ClaireBoolean *str);
extern CL_EXPORT OID  nexti_meta_reader(meta_reader *r,OID val);
extern CL_EXPORT OID  read_escape_meta_reader(meta_reader *r);
extern CL_EXPORT OID  nextvariable_meta_reader(meta_reader *r,OID val);
extern CL_EXPORT OID  nexts_I_meta_reader1(meta_reader *r,keyword *e);
extern CL_EXPORT OID  nexte_I_meta_reader(meta_reader *r,keyword *e);
extern CL_EXPORT OID  nexts_I_meta_reader2(meta_reader *r,int e);
extern CL_EXPORT OID  nexts_I_meta_reader3(meta_reader *r,keyword *e,int n);
extern CL_EXPORT ClaireBoolean * extended_comment_ask_meta_reader(meta_reader *r,char *s);
extern CL_EXPORT OID  extended_comment_I_meta_reader(meta_reader *r,char *s);
extern CL_EXPORT Call * Call_I_property(property *p,list *l);
extern CL_EXPORT ClaireBoolean * operation_ask_any(OID y);
extern CL_EXPORT OID  combine_any(OID x,OID y,OID z);
extern CL_EXPORT OID  combine_I_any(OID x,OID y,OID z);
extern CL_EXPORT OID  operation_I_any(OID x);
extern CL_EXPORT OID  operand_I_any(OID x,int n);
extern CL_EXPORT CL_INT  precedence_I_any(OID y);
extern CL_EXPORT OID  nextstruct_meta_reader(meta_reader *r,keyword *_Zfirst,keyword *e);
extern CL_EXPORT OID  readlet_meta_reader(meta_reader *r,keyword *e);
extern CL_EXPORT OID  readlet_star_meta_reader(meta_reader *r,list *l,int n,keyword *e);
extern CL_EXPORT OID  readwhen_meta_reader(meta_reader *r,keyword *e);
extern CL_EXPORT OID  readif_meta_reader(meta_reader *r,int e);
extern CL_EXPORT OID  readcase_meta_reader(meta_reader *r,keyword *e);
extern CL_EXPORT OID  readset_meta_reader(meta_reader *r,OID _Za1);
extern CL_EXPORT OID  dereference_any(OID x);
extern CL_EXPORT OID  nextseq_meta_reader(meta_reader *r,int e);
extern CL_EXPORT OID  readblock_meta_reader(meta_reader *r,OID x,int e);
extern CL_EXPORT OID  Do_I_any(OID x,OID y);
extern CL_EXPORT ClaireType * extract_of_type_Call(Call *x);
extern CL_EXPORT OID  readcall_meta_reader(meta_reader *r,OID x,OID t);
extern CL_EXPORT OID  nextdefinition_meta_reader(meta_reader *r,OID x,OID y,ClaireBoolean *old_ask);
extern CL_EXPORT OID  nextmethod_meta_reader(meta_reader *r,OID x,OID y,ClaireBoolean *table_ask,ClaireBoolean *old_ask,ClaireBoolean *inl_ask);
extern CL_EXPORT OID  nextinst_meta_reader(meta_reader *r,OID x);
extern CL_EXPORT Defclass * nextDefclass_meta_reader(meta_reader *r,OID x,ClaireBoolean *old_ask);
extern CL_EXPORT OID  self_eval_delimiter(delimiter *self);
extern CL_EXPORT ClaireBoolean * useless_c_integer(CL_INT r);
extern CL_EXPORT OID  skipc_meta_reader(meta_reader *self);
extern CL_EXPORT OID  skipc_I_meta_reader(meta_reader *r);
extern CL_EXPORT meta_reader * cnext_meta_reader(meta_reader *self);
extern CL_EXPORT ClaireBoolean * findeol_meta_reader(meta_reader *self);
extern CL_EXPORT OID  checkno_meta_reader(meta_reader *r,int n,OID y);
extern CL_EXPORT OID  verify_any(OID t,OID x,OID y);
extern CL_EXPORT void  self_print_syntax_error1_Reader(Reader_syntax_error *self);
extern CL_EXPORT void  Serror_integer1(CL_INT c,char *s,list *la);
extern CL_EXPORT void  reader_push_void1();
extern CL_EXPORT void  reader_pop_void1();
extern CL_EXPORT void  reader_reset_void1();
extern CL_EXPORT Variable * extract_variable_any(OID self);
extern CL_EXPORT list * bind_I_meta_reader(meta_reader *self,Variable *_Zv);
extern CL_EXPORT OID  unbind_I_meta_reader(meta_reader *self,list *_Zfirst);
extern CL_EXPORT void  restore_state_meta_reader(meta_reader *self);
extern CL_EXPORT OID  load_file_string(char *self,ClaireBoolean *b);
extern CL_EXPORT OID  load_string(char *self);
extern CL_EXPORT OID  sload_string(char *self);
extern CL_EXPORT void  load_file_module(module *self,ClaireBoolean *b);
extern CL_EXPORT void  set_load_module_boolean(ClaireBoolean *b);
extern CL_EXPORT void  set_eval_module_boolean1(ClaireBoolean *b);
extern CL_EXPORT OID  load_module(module *self);
extern CL_EXPORT OID  sload_module(module *self);
extern CL_EXPORT list * add_modules_module(module *self,set *l,list *result);
extern CL_EXPORT void  add_parts_module(module *self,set *result);
extern CL_EXPORT void  add_subparts_module(module *self,set *result);
extern CL_EXPORT void  add_uses_module(module *self,set *result);
extern CL_EXPORT void  add_modules_module2(module *self,set *result);
extern CL_EXPORT list * add_modules_list(list *self);
extern CL_EXPORT OID  eload_string(char *self);
extern CL_EXPORT OID  readblock_port(PortObject *p);
extern CL_EXPORT OID  read_port(PortObject *p);
extern CL_EXPORT OID  read_string(char *self);
extern CL_EXPORT OID  print_exception_void();
extern CL_EXPORT OID  show_any(OID self);
extern CL_EXPORT OID  min_any(OID x,OID y);
extern CL_EXPORT OID  max_any(OID x,OID y);
extern CL_EXPORT ClaireBoolean * known_ask_table(table *a,OID x);
extern CL_EXPORT ClaireBoolean * unknown_ask_table(table *a,OID x);
extern CL_EXPORT ClaireBoolean * _sup_equal_any(OID self,OID x);
extern CL_EXPORT list * hashgrow_list(list *l,property *hi);
extern CL_EXPORT void  use_module_string(char *m);
extern CL_EXPORT tuple * option_usage_string13_Reader(char *opt);
extern CL_EXPORT tuple * option_usage_string13_Reader_(char *g0716);
extern CL_EXPORT void  option_respond_string10_Reader(char *opt,list *l);
extern CL_EXPORT tuple * option_usage_string14_Reader(char *opt);
extern CL_EXPORT tuple * option_usage_string14_Reader_(char *g0717);
extern CL_EXPORT void  option_respond_string11_Reader(char *opt,list *l);
extern CL_EXPORT tuple * option_usage_string15_Reader(char *opt);
extern CL_EXPORT tuple * option_usage_string15_Reader_(char *g0718);
extern CL_EXPORT void  option_respond_string12_Reader(char *opt,list *l);
extern CL_EXPORT OID  inspect_any(OID self);
extern CL_EXPORT OID  inspect_loop_any(OID _Zread,list *old);
extern CL_EXPORT OID  get_from_integer_any(OID self,int n);
extern CL_EXPORT void  trace_rule_relation(ClaireRelation *R,char *s,OID x,OID y,OID u,OID v);
extern CL_EXPORT CL_INT  mem_class(ClaireClass *c);
extern CL_EXPORT PRcount * PRget_property(property *p);
extern CL_EXPORT OID  PRlook_property2(property *p);
extern CL_EXPORT void  PRshow_property(property *p);
extern CL_EXPORT CL_INT  PRtime_property(property *p);
extern CL_EXPORT CL_INT  PRcounter_property(property *p);
extern CL_EXPORT void  PRshow_void();
extern CL_EXPORT set * dependents_method(method *self);
extern CL_EXPORT OID  dependents_any(OID self);
extern CL_EXPORT void  PRdepends_property(property *p,property *p2);
extern CL_EXPORT void  dump_stack_void1();
extern CL_EXPORT void  init_location_any1_Reader(OID self);
extern CL_EXPORT OID  update_location_I_list1(list *loc);
extern CL_EXPORT OID  update_location_I_any1(OID self,list *loc);
extern CL_EXPORT OID  pop_frame_I_any1(OID self);
extern CL_EXPORT OID  pop_handle_I_any1(OID self,Variable *hid);
extern CL_EXPORT OID  equip_any1_Reader(OID self,list *poploc);
extern CL_EXPORT OID  equip_Instruction1_Reader(Instruction *self,list *poploc);
extern CL_EXPORT list * equip_list_list1(list *self,list *poploc,int indexstart);
extern CL_EXPORT OID  equip_unbound_symbol1_Reader(unbound_symbol *self,list *poploc);
extern CL_EXPORT OID  equip_Variable1_Reader(Variable *self,list *poploc);
extern CL_EXPORT OID  equip_While1_Reader(While *self,list *poploc);
extern CL_EXPORT OID  equip_Error1_Reader(Error *self,list *poploc);
extern CL_EXPORT OID  equip_Construct1_Reader(Construct *self,list *poploc);
extern CL_EXPORT OID  equip_Call1_Reader(Call *self,list *poploc);
extern CL_EXPORT OID  equip_Do1_Reader(Do *self,list *poploc);
extern CL_EXPORT OID  equip_Case1_Reader(Case *self,list *poploc);
extern CL_EXPORT OID  equip_If1_Reader(If *self,list *poploc);
extern CL_EXPORT OID  equip_Let1_Reader(Let *self,list *poploc);
extern CL_EXPORT OID  equip_When1_Reader(When *self,list *poploc);
extern CL_EXPORT OID  equip_Iteration1_Reader(Iteration *self,list *poploc);
extern CL_EXPORT OID  equip_For1_Reader(For *self,list *poploc);
extern CL_EXPORT OID  equip_Handle1_Reader(ClaireHandle *self,list *poploc);
extern CL_EXPORT OID  equip_Assign1_Reader(Assign *self,list *poploc);
extern CL_EXPORT OID  equip_Defclaire1_Reader(Defclaire *self,list *poploc);
extern CL_EXPORT OID  equip_Definition1_Reader(Definition *self,list *poploc);
extern CL_EXPORT OID  equip_Defobj1_Reader(Defobj *self,list *poploc);
extern CL_EXPORT OID  equip_Defrule1_Reader(Defrule *self,list *poploc);
extern CL_EXPORT OID  equip_any2_Reader(OID self);
extern CL_EXPORT OID  equip_lambda1_Reader(lambda *self);
extern CL_EXPORT void  lexical_build_equip_any1(OID self,int n);
extern CL_EXPORT void  completion_reset_void();
extern CL_EXPORT void  explode_separators_string(char *s);
extern CL_EXPORT ClaireBoolean * same_tree_ask_module(module *a);
extern CL_EXPORT void  complete_named_object_string(char *o,list *l);
extern CL_EXPORT void  complete_slot_string(char *o,list *l);
extern CL_EXPORT void  complete_class_string(char *o,list *l);
extern CL_EXPORT void  nodup_list(list *l);
extern CL_EXPORT void  fill_claire_matches_string(char *buf,int end);
extern CL_EXPORT char * match_prefix_void();
extern CL_EXPORT char * method_description_method(method *m);
extern CL_EXPORT char * class_description_class(ClaireClass *self);
extern CL_EXPORT void  claire_complete_void();
extern CL_EXPORT void  bin_init_void();
extern CL_EXPORT void  fill_binaries_string(char *buf);
extern CL_EXPORT void  fill_files_string(char *buf);
extern CL_EXPORT void  shell_complete_void();
extern CL_EXPORT void  close_port_stdin_line_reader1_Reader(Reader_stdin_line_reader *self);
extern CL_EXPORT ClaireBoolean * eof_port_ask_stdin_line_reader1_Reader(Reader_stdin_line_reader *self);
extern CL_EXPORT void  flush_port_stdin_line_reader1_Reader(Reader_stdin_line_reader *self);
extern CL_EXPORT void  unget_port_stdin_line_reader1_Reader(Reader_stdin_line_reader *self,char*buf,int len);
extern CL_EXPORT CL_INT  read_port_stdin_line_reader1_Reader(Reader_stdin_line_reader *self,char*buf,int len);
extern CL_EXPORT Reader_execution_context * save_context_boolean1(ClaireBoolean *debug_ask);
extern CL_EXPORT void  restore_context_execution_context1(Reader_execution_context *self);
extern CL_EXPORT char * get_prompt_void2();
extern CL_EXPORT void  self_print_abort_debug1_Reader(Reader_abort_debug *self);
extern CL_EXPORT void  self_print_debug_fatal_error1_Reader(Reader_debug_fatal_error *self);
extern CL_EXPORT void  inspect_system_list2(list *self);
extern CL_EXPORT void  inspect_toplevel_any1(OID self);
extern CL_EXPORT OID  read_command_string1(char *prompt);
extern CL_EXPORT void  eval_command_any2(OID x,int nb_eval,ClaireBoolean *check_break_ask);
extern CL_EXPORT void  close_toplevel_exception_exception1(ClaireException *self);
extern CL_EXPORT void  self_print_command_line_error1_Reader(Reader_command_line_error *self);
extern CL_EXPORT void  toplevel_void2_Reader();
extern CL_EXPORT void  debug_loop_void1();
extern CL_EXPORT void  on_break_program_void1_Reader();
extern CL_EXPORT void  show_frame_dbg_frame1(Core_dbg_frame *self,Core_dbg_frame *frame);
extern CL_EXPORT void  show_source_lines_dbg_frame1(Core_dbg_frame *self,int n);
extern CL_EXPORT void  show_frame_info_dbg_frame1(Core_dbg_frame *self);
extern CL_EXPORT void  show_frame_info_dbg_frame2(Core_dbg_frame *self,Core_dbg_frame *frame);
extern CL_EXPORT void  where_dbg_frame1(Core_dbg_frame *frame);
extern CL_EXPORT OID  self_eval_DebugVariable1(Reader_DebugVariable *self);
extern CL_EXPORT list * bind_frame_dbg_frame1(Core_dbg_frame *self);
extern CL_EXPORT void  unbind_frame_list1(list *bindings);
extern CL_EXPORT void  print_oid_any1(OID x);
extern CL_EXPORT void  echo_any1_Reader(OID self);
extern CL_EXPORT void  echo_string1_Reader(char *self);
extern CL_EXPORT void  echo_integer1_Reader(CL_INT self);
extern CL_EXPORT void  echo_float1_Reader(double self);
extern CL_EXPORT void  echo_float1_Reader_(OID g0911);
extern CL_EXPORT void  echo_char1_Reader(ClaireChar *self);
extern CL_EXPORT void  echo_property1_Reader(property *p,ClaireObject *self);
extern CL_EXPORT void  self_html_string1_Reader(char *src);
extern CL_EXPORT char * nl2br_string1(char *self);
extern CL_EXPORT CL_INT  write_port_self_html_converter1_Reader(Reader_self_html_converter *self,char*buf,int len);
extern CL_EXPORT void  self_html_any1_Reader(OID self);
extern CL_EXPORT void  self_html_property1_Reader(property *p,ClaireObject *self);
extern CL_EXPORT ClaireBoolean * wcl_start_ask_meta_reader1(meta_reader *r,int p);
extern CL_EXPORT OID  nextswcl_meta_reader1(meta_reader *r);
extern CL_EXPORT Call_wcl * Call_wcl_I_property1(property *self,list *l,tuple *loc);
extern CL_EXPORT OID  build_call_wcl_meta_reader2(meta_reader *r,property *prop);
extern CL_EXPORT OID  build_top_call_wcl_meta_reader1(meta_reader *r,property *prop);
extern CL_EXPORT OID  read_top_wcl_meta_reader1(meta_reader *r);
extern CL_EXPORT OID  read_wcl_meta_reader1(meta_reader *r);
extern CL_EXPORT PortObject * fopen_source_string1(char *self);
extern CL_EXPORT list * load_wcl_I_string1(char *self);
extern CL_EXPORT void  add_wcl_module1(module *self,char *wcl_path,char *wild,char *pathinfo);
extern CL_EXPORT void  add_wcl_module2(module *self,char *wcl_path,ClaireType *wild,char *pathinfo);
extern CL_EXPORT Reader_hash_table * hash_table_I_integer1(CL_INT n);
extern CL_EXPORT void  reset_hash_table1(Reader_hash_table *self);
extern CL_EXPORT CL_INT  hash_value_oid_hash_table1(Reader_hash_table *self,OID value);
extern CL_EXPORT CL_INT  hash_value_string_hash_table1(Reader_hash_table *self,char *value);
extern CL_EXPORT void  nth_equal_hash_table1(Reader_hash_table *self,OID key,OID val);
extern CL_EXPORT OID  nth_hash_table1(Reader_hash_table *self,OID key);
extern CL_EXPORT void  add_ref_to_item_doc_item1(Reader_doc_item *self,char *nm);
extern CL_EXPORT OID  string2item_doc_context1(Reader_doc_context *ctx,char *s);
extern CL_EXPORT void  save_doc_links_doc_context1(Reader_doc_context *ctx);
extern CL_EXPORT void  load_doc_links_void1();
extern CL_EXPORT ClaireBoolean * compare_items_doc_entity1(Reader_doc_entity *e1,Reader_doc_entity *e2);
extern CL_EXPORT list * ordered_categories_void1();
extern CL_EXPORT void  print_module_doc_entity1(Reader_doc_entity *self);
extern CL_EXPORT void  make_alias_doc_category1(Reader_doc_category *cat,char *salias);
extern CL_EXPORT Reader_doc_category * make_category_string1(char *scat);
extern CL_EXPORT Reader_doc_category * make_section_doc_category1(Reader_doc_category *cat,char *ssec);
extern CL_EXPORT Reader_doc_section * make_section_string1(char *ssec);
extern CL_EXPORT void  make_doc_item_any1(OID x,char *sdoc,char *cat,ClaireBoolean *xl);
extern CL_EXPORT void  make_doc_item_Defmethod1(Defmethod *x,char *sdoc,char *cat,ClaireBoolean *xl);
extern CL_EXPORT void  make_doc_item_Defarray1(Defarray *x,char *sdoc,char *cat,ClaireBoolean *xl);
extern CL_EXPORT void  make_doc_item_Defclass1(Defclass *x,char *sdoc,char *cat,ClaireBoolean *xl);
extern CL_EXPORT void  make_doc_item_Defobj1(Defobj *x,char *sdoc,char *cat,ClaireBoolean *xl);
extern CL_EXPORT list * load_items_string1(char *self);
extern CL_EXPORT void  self_print_bad_eval1_Reader(Reader_bad_eval *self);
extern CL_EXPORT void  load_file_items_string1(char *self);
extern CL_EXPORT void  option_respond_string51_Reader(char *opt,list *l);
extern CL_EXPORT void  option_respond_string52_Reader(char *opt,list *l);
extern CL_EXPORT void  option_respond_string53_Reader(char *opt,list *l);
extern CL_EXPORT void  option_respond_string54_Reader(char *opt,list *l);
extern CL_EXPORT void  option_respond_string55_Reader(char *opt,list *l);
extern CL_EXPORT tuple * option_usage_string35_Reader(char *self);
extern CL_EXPORT tuple * option_usage_string35_Reader_(char *g0942);
extern CL_EXPORT void  load_module_doc_module1(module *self);
extern CL_EXPORT void  generate_module_doc_module1(module *self);
extern CL_EXPORT void  generate_index_doc_context1(Reader_doc_context *self);
extern CL_EXPORT void  generate_index_doc_context2(Reader_doc_context *ctx,Reader_doc_entity *e);
extern CL_EXPORT void  generate_index_doc_context3(Reader_doc_context *ctx,Reader_doc_entity *e,ClaireBoolean *catindex_ask);
extern CL_EXPORT void  generate_category_index_doc_context1(Reader_doc_context *self);
extern CL_EXPORT void  generate_option_index_doc_context1(Reader_doc_context *self);
extern CL_EXPORT void  generate_entity_index_doc_context1(Reader_doc_context *self,ClaireClass *c,char *cn,char *si);
extern CL_EXPORT void  generate_doc_doc_context1(Reader_doc_context *self);
extern CL_EXPORT void  generate_doc_doc_context2(Reader_doc_context *self,char *str,ClaireClass *c);
extern CL_EXPORT void  generate_doc_doc_category1(Reader_doc_category *self,Reader_doc_context *ctx);
extern CL_EXPORT void  generate_doc_doc_option1(Reader_doc_option *self,Reader_doc_context *ctx);
extern CL_EXPORT void  start_entity_doc_doc_entity1(Reader_doc_entity *self,Reader_doc_context *ctx);
extern CL_EXPORT void  generate_doc_doc_entity1(Reader_doc_entity *self,Reader_doc_context *ctx);
extern CL_EXPORT void  generate_doc_doc_method1(Reader_doc_method *self,Reader_doc_context *ctx);
extern CL_EXPORT void  generate_doc_doc_class1(Reader_doc_class *self,Reader_doc_context *ctx);
extern CL_EXPORT void  start_item_header_doc_entity1(Reader_doc_entity *self,Reader_doc_context *ctx,int n_Z);
extern CL_EXPORT void  end_item_header_doc_entity1(Reader_doc_entity *self,Reader_doc_context *ctx,int n_Z,char *kind);
extern CL_EXPORT void  item_header_doc_global1(Reader_doc_global *self,Reader_doc_context *ctx);
extern CL_EXPORT void  item_header_doc_table1(Reader_doc_table *self,Reader_doc_context *ctx);
extern CL_EXPORT void  item_header_doc_method1(Reader_doc_method *self,Reader_doc_context *ctx);
extern CL_EXPORT void  item_header_doc_class1(Reader_doc_class *self,Reader_doc_context *ctx);
extern CL_EXPORT void  item_header_doc_interface1(Reader_doc_interface *self,Reader_doc_context *ctx);
extern CL_EXPORT void  file_inline_css_style_void1();
extern CL_EXPORT void  html_file_header_doc_context1(Reader_doc_context *self);
extern CL_EXPORT void  html_file_header_doc_context2(Reader_doc_context *self,char *kind);
extern CL_EXPORT void  html_file_header_doc_context3(Reader_doc_context *self,Reader_doc_item *x);
extern CL_EXPORT void  html_file_footer_void1();
extern CL_EXPORT void  category_index_href_doc_context1(Reader_doc_context *self);
extern CL_EXPORT void  option_index_href_doc_context1(Reader_doc_context *self);
extern CL_EXPORT void  section_index_href_doc_context1(Reader_doc_context *self,Reader_doc_section *sec);
extern CL_EXPORT void  item_href_doc_context1(Reader_doc_context *self,Reader_doc_link *x);
extern CL_EXPORT void  item_href_doc_context2(Reader_doc_context *self,Reader_doc_item *x);
extern CL_EXPORT void  item_href_doc_context3(Reader_doc_context *self,Reader_doc_link *x,char *w);
extern CL_EXPORT void  item_href_doc_context4(Reader_doc_context *self,Reader_doc_item *x,char *w);
extern CL_EXPORT void  item_href_doc_context5(Reader_doc_context *self,Reader_doc_section *x,char *w);
extern CL_EXPORT void  item_file_doc_context1(Reader_doc_context *self,Reader_doc_category *x);
extern CL_EXPORT void  item_file_doc_context2(Reader_doc_context *self,Reader_doc_option *x);
extern CL_EXPORT void  item_file_doc_context3(Reader_doc_context *self,Reader_doc_entity *x);
extern CL_EXPORT void  set_item_module_doc_entity1(Reader_doc_entity *x);
extern CL_EXPORT void  restore_module_void1();
extern CL_EXPORT void  entity_print_doc_entity1(Reader_doc_entity *x,Reader_doc_context *ctx,OID e);
extern CL_EXPORT void  item_prototype_doc_global1(Reader_doc_global *x,Reader_doc_context *ctx);
extern CL_EXPORT void  item_prototype_doc_table1(Reader_doc_table *x,Reader_doc_context *ctx);
extern CL_EXPORT void  item_prototype_doc_interface1(Reader_doc_interface *x,Reader_doc_context *ctx);
extern CL_EXPORT void  item_prototype_doc_class1(Reader_doc_class *x,Reader_doc_context *ctx);
extern CL_EXPORT void  item_prototype_doc_method1(Reader_doc_method *x,Reader_doc_context *ctx);
extern CL_EXPORT void  princ_doc_word_doc_context1(Reader_doc_context *self,char *w,list *vnames);
extern CL_EXPORT void  print_doc_word_doc_context1(Reader_doc_context *self,char *w,list *vnames,list *exclude);
extern CL_EXPORT ClaireBoolean * isnext_ask_port1(PortObject *self,char *s);
extern CL_EXPORT ClaireBoolean * checknext_ask_port1(PortObject *self,char *s);
extern CL_EXPORT void  print_doc_doc_context1(Reader_doc_context *self,char *doc,list *vnames,list *exclude);

// namespace class for Reader 
class CL_EXPORT ReaderClass: public NameSpace {
public:

  ClaireClass * _delimiter;
  global_variable * arrow;
  global_variable * triangle;
  ClaireClass * _reserved_keyword;
  reserved_keyword * _cl_else;
  reserved_keyword * _cl_for;
  reserved_keyword * _cl_ffor;
  reserved_keyword * _cl_case;
  reserved_keyword * _cl_while;
  reserved_keyword * _cl_until;
  reserved_keyword * _cl_let;
  reserved_keyword * _cl_when;
  reserved_keyword * _cl_try;
  reserved_keyword * _cl_if;
  reserved_keyword * _cl_Zif;
  reserved_keyword * _cl_branch;
  keyword * forall;
  keyword * None;
  keyword * L__equal;
  keyword * L_;
  keyword * CATCH;
  keyword * in;
  keyword * by;
  keyword * as;
  keyword * L_L_;
  keyword * PRINTF;
  keyword * assert;
  keyword * RETURN;
  keyword * BREAK;
  keyword * trace;
  keyword * exists;
  keyword * some;
  keyword * _equal_sup;
  keyword * _ask;
  keyword * rule;
  keyword * quote;
  property * inspect;
  property * known_I;
  ClaireClass * _meta_reader;
  global_variable * IDENTS;
  global_variable * AND;
  global_variable * OR;
  property * REGISTER;
  ClaireClass * _syntax_error;
  meta_reader * reader;
  global_variable * READER_STACK;
  global_variable * PROCESS_LOAD_MODULE_ask;
  global_variable * PROCESS_EVAL_INSTRUCTIONS_ask;
  keyword * q;
  property * pretty_show;
  global_variable * WCL_STOP;
  global_variable * used_modules;
  global_variable * NO_DEBUG_METHOD;
  global_variable * _starshowall_star;
  ClaireClass * _PRcount;
  table * PRdependent;
  table * PRdependentOf;
  global_variable * MATCHES;
  global_variable * LAST_EXPLODED;
  global_variable * LAST_MODULE;
  global_variable * LAST_LINE;
  global_variable * LAST_POSITION;
  global_variable * MATCH_INDEX;
  global_variable * COMPLETE_START_POSITION;
  global_variable * BINS;
  global_variable * BINS_INIT_ask;
  ClaireClass * _stdin_line_reader;
  ClaireClass * _execution_context;
  global_variable * PROMPT;
  ClaireClass * _abort_debug;
  ClaireClass * _debug_fatal_error;
  global_variable * _stardebug_fatal_error_star;
  global_variable * INSPECT_STACK;
  global_variable * IN_INSPECT_LOOP_ask;
  global_variable * NB_EVAL;
  global_variable * TOP_CHANDLE;
  ClaireClass * _command_line_error;
  global_variable * NB_DEBUG_EVAL;
  ClaireClass * _DebugVariable;
  ClaireClass * _self_html_converter;
  global_variable * SELF_HTML_CONVERTER;
  property * load_wcl;
  ClaireClass * _hash_table;
  ClaireClass * _map_node;
  global_variable * MODULE_NAME;
  global_variable * NAME_TO_ITEM_TABLE;
  global_variable * ITEM_LOCATION;
  global_variable * SHORT_PRESENTATION;
  global_variable * DOC_TITLE;
  global_variable * _starexpl_doc_star;
  global_variable * _starcode_doc_star;
  global_variable * _stardoc_links_star;
  global_variable * _starone_file_star;
  global_variable * _starper_cat_file_star;
  global_variable * _stardirectory_star;
  global_variable * _staronly_doc_links_star;
  global_variable * DEPOPTIONS;
  ClaireClass * _doc_context;
  ClaireClass * _doc_item;
  ClaireClass * _doc_link;
  ClaireClass * _doc_copyright;
  ClaireClass * _doc_preamble;
  ClaireClass * _doc_author;
  ClaireClass * _doc_category;
  ClaireClass * _doc_entity;
  ClaireClass * _doc_section;
  ClaireClass * _doc_option;
  ClaireClass * _doc_method;
  ClaireClass * _doc_class;
  ClaireClass * _doc_global;
  ClaireClass * _doc_interface;
  ClaireClass * _doc_table;
  ClaireClass * _bad_eval;
  global_variable * ONE_FILE;
  global_variable * PER_CATEGORY_FILE;
  global_variable * DOC_CLASS_ROOTS;
  global_variable * RESTORE_MODULE;
  global_variable * IGNORE_WORDS;
  global_variable * TAG_STOP;
  global_variable * DOC_STOP;
property * s_index;// Reader/"s_index"
property * fromp;// Reader/"fromp"
property * nb_line;// Reader/"nb_line"
property * firstc;// Reader/"firstc"
property * last_form;// Reader/"last_form"
property * maxstack;// Reader/"maxstack"
property * toplevel;// Reader/"toplevel"
property * eof;// Reader/"eof"
property * space;// Reader/"space"
property * tab;// Reader/"tab"
property * bracket;// Reader/"bracket"
property * paren;// Reader/"paren"
property * comma;// Reader/"comma"
property * curly;// Reader/"curly"
property * next;// Reader/"next"
property * keyword_ask;// Reader/"keyword?"
property * stop_ask;// Reader/"stop?"
property * nextunit;// Reader/"nextunit"
property * nexts;// Reader/"nexts"
property * loopexp;// Reader/"loopexp"
property * nexte;// Reader/"nexte"
property * nextexp;// Reader/"nextexp"
property * nexti;// Reader/"nexti"
property * read_escape;// Reader/"read_escape"
property * nextvariable;// Reader/"nextvariable"
property * nexts_I;// Reader/"nexts!"
property * nexte_I;// Reader/"nexte!"
property * extended_comment_ask;// Reader/"extended_comment?"
property * extended_comment_I;// Reader/"extended_comment!"
property * Call_I;// Reader/"Call!"
property * operation_ask;// Reader/"operation?"
property * combine;// Reader/"combine"
property * combine_I;// Reader/"combine!"
property * operation_I;// Reader/"operation!"
property * operand_I;// Reader/"operand!"
property * precedence_I;// Reader/"precedence!"
property * nextstruct;// Reader/"nextstruct"
property * readlet;// Reader/"readlet"
property * readlet_star;// Reader/"readlet*"
property * readwhen;// Reader/"readwhen"
property * show;// claire/"show"
property * readif;// Reader/"readif"
property * readcase;// Reader/"readcase"
property * readset;// Reader/"readset"
property * dereference;// Reader/"dereference"
property * nextseq;// Reader/"nextseq"
property * readblock;// claire/"readblock"
property * Do_I;// Reader/"Do!"
property * readcall;// Reader/"readcall"
property * nextdefinition;// Reader/"nextdefinition"
property * nextmethod;// Reader/"nextmethod"
property * nextinst;// Reader/"nextinst"
property * nextDefclass;// Reader/"nextDefclass"
property * useless_c;// Reader/"useless_c"
property * skipc;// Reader/"skipc"
property * skipc_I;// Reader/"skipc!"
property * cnext;// Reader/"cnext"
property * findeol;// Reader/"findeol"
property * checkno;// Reader/"checkno"
property * verify;// Reader/"verify"
property * Serror;// Reader/"Serror"
property * extract_variable;// Reader/"extract_variable"
property * bind_I;// Reader/"bind!"
property * unbind_I;// Reader/"unbind!"
property * load_file;// Reader/"load_file"
property * load;// claire/"load"
property * sload;// claire/"sload"
property * add_modules;// Reader/"add_modules"
property * eload;// claire/"eload"
property * print_exception;// Reader/"print_exception"
property * hashgrow;// mClaire/"hashgrow"
property * inspect_system;// Reader/"inspect_system"
property * trace_rule;// Reader/"trace_rule"
property * rtime;// Reader/"rtime"
property * rdepth;// Reader/"rdepth"
property * rnum;// Reader/"rnum"
property * rloop;// Reader/"rloop"
property * rstart;// Reader/"rstart"
property * PRget;// claire/"PRget"
property * PRlook;// claire/"PRlook"
property * dependents;// Reader/"dependents"
property * extract_of_type;// Reader/"extract_of_type"
property * PRdepends;// claire/"PRdepends"
property * PRshow;// claire/"PRshow"
property * PRtime;// claire/"PRtime"
property * PRcounter;// claire/"PRcounter"
property * last_arrow;// Reader/"last_arrow"
property * s_properties;// Reader/"s_properties"
property * wcl_ask;// Reader/"wcl?"
property * cascade_ask;// Reader/"cascade?"
property * set_load_module;// Reader/"set_load_module"
property * get_lines;// Reader/"get_lines"
property * use_module;// claire/"use_module"
property * add_parts;// Reader/"add_parts"
property * add_subparts;// Reader/"add_subparts"
property * add_uses;// Reader/"add_uses"
property * insert_text;// Reader/"insert_text"
property * delete_text;// Reader/"delete_text"
property * reset_state;// Reader/"reset_state"
property * get_cursor_position;// Reader/"get_cursor_position"
property * get_text;// Reader/"get_text"
property * display_list;// Reader/"display_list"
property * completion_reset;// Reader/"completion_reset"
property * explode_separators;// Reader/"explode_separators"
property * same_tree_ask;// Reader/"same_tree?"
property * complete_named_object;// Reader/"complete_named_object"
property * complete_slot;// Reader/"complete_slot"
property * complete_class;// Reader/"complete_class"
property * nodup;// Reader/"nodup"
property * fill_claire_matches;// Reader/"fill_claire_matches"
property * match_prefix;// Reader/"match_prefix"
property * method_description;// Reader/"method_description"
property * class_description;// Reader/"class_description"
property * claire_complete;// Reader/"claire_complete"
property * bin_init;// Reader/"bin_init"
property * fill_binaries;// Reader/"fill_binaries"
property * fill_files;// Reader/"fill_files"
property * shell_complete;// Reader/"shell_complete"
property * extended_operator;// Reader/"extended_operator"
property * inspect_loop;// claire/"inspect_loop"
property * get_from_integer;// claire/"get_from_integer"
property * reader_push;// Reader/"reader_push"
property * reader_pop;// Reader/"reader_pop"
property * cause;// Reader/"cause"
property * reader_reset;// Reader/"reader_reset"
property * dump_stack;// claire/"dump_stack"
property * module_stack;// Reader/"module_stack"
property * get_prompt;// Reader/"get_prompt"
property * eval_command;// Reader/"eval_command"
property * print_oid;// Reader/"print_oid"
property * nl2br;// claire/"nl2br"
property * wcl_start_ask;// Reader/"wcl_start?"
property * read_wcl;// Reader/"read_wcl"
property * read_top_wcl;// Reader/"read_top_wcl"
property * fopen_source;// claire/"fopen_source"
property * load_wcl_I;// Reader/"load_wcl!"
property * add_wcl;// claire/"add_wcl"
property * saved_system;// Reader/"saved_system"
property * saved_reader;// Reader/"saved_reader"
property * save_context;// Reader/"save_context"
property * restore_context;// Reader/"restore_context"
property * inspect_toplevel;// Reader/"inspect_toplevel"
property * read_command;// Reader/"read_command"
property * debug_loop;// Reader/"debug_loop"
property * nextswcl;// Reader/"nextswcl"
property * head_wcl_intruction_ask;// Reader/"head_wcl_intruction?"
property * Call_wcl_I;// Reader/"Call_wcl!"
property * build_call_wcl;// Reader/"build_call_wcl"
property * build_top_call_wcl;// Reader/"build_top_call_wcl"
property * debug_context_ask;// Reader/"debug_context?"
property * src;// Reader/"src"
property * line;// Reader/"line"
property * leaf_wcl_intruction_ask;// Reader/"leaf_wcl_intruction?"
property * close_toplevel_exception;// Reader/"close_toplevel_exception"
property * show_source_lines;// Reader/"show_source_lines"
property * show_frame;// Reader/"show_frame"
property * show_frame_info;// Reader/"show_frame_info"
property * add_ident;// Reader/"add_ident"
property * set_eval_module;// Reader/"set_eval_module"
property * hash_max;// Reader/"hash_max"
property * content;// Reader/"content"
property * hash_table_I;// Reader/"hash_table!"
property * nkey;// Reader/"nkey"
property * nval;// Reader/"nval"
property * reset;// Reader/"reset"
property * hash_value_oid;// Reader/"hash_value_oid"
property * hash_value_string;// Reader/"hash_value_string"
property * print_module;// Reader/"print_module"
property * category_index_href;// Reader/"category_index_href"
property * src_location;// Reader/"src_location"
property * documentation;// Reader/"documentation"
property * xl_ask;// Reader/"xl?"
property * oid;// Reader/"oid"
property * exploit_ask;// Reader/"exploit?"
property * categories;// Reader/"categories"
property * section;// Reader/"section"
property * items;// Reader/"items"
property * entity_names;// Reader/"entity_names"
property * aliases;// Reader/"aliases"
property * aname;// Reader/"aname"
property * usage;// Reader/"usage"
property * from_module;// Reader/"from_module"
property * opts;// Reader/"opts"
property * ranges;// Reader/"ranges"
property * category;// Reader/"category"
property * mrange;// Reader/"mrange"
property * var_ranges;// Reader/"var_ranges"
property * constant_ask;// Reader/"constant?"
property * grange;// Reader/"grange"
property * trange;// Reader/"trange"
property * tbody;// Reader/"tbody"
property * add_ref_to_item;// Reader/"add_ref_to_item"
property * string2item;// Reader/"string2item"
property * in_code_ask;// Reader/"in_code?"
property * save_doc_links;// Reader/"save_doc_links"
property * directory;// Reader/"directory"
property * load_doc_links;// Reader/"load_doc_links"
property * compare_items;// Reader/"compare_items"
property * ordered_categories;// Reader/"ordered_categories"
property * make_alias;// Reader/"make_alias"
property * make_category;// Reader/"make_category"
property * make_section;// Reader/"make_section"
property * make_doc_item;// Reader/"make_doc_item"
property * load_items;// Reader/"load_items"
property * load_file_items;// Reader/"load_file_items"
property * update_location_I;// Reader/"update_location!"
property * pop_frame_I;// Reader/"pop_frame!"
property * load_module_doc;// Reader/"load_module_doc"
property * generate_module_doc;// Reader/"generate_module_doc"
property * generation_mode;// Reader/"generation_mode"
property * add_source_links_ask;// Reader/"add_source_links?"
property * bold_ask;// Reader/"bold?"
property * in_a_ask;// Reader/"in_a?"
property * html_file_header;// Reader/"html_file_header"
property * print_doc;// Reader/"print_doc"
property * generate_index;// Reader/"generate_index"
property * generate_doc;// Reader/"generate_doc"
property * html_file_footer;// Reader/"html_file_footer"
property * generate_category_index;// Reader/"generate_category_index"
property * generate_option_index;// Reader/"generate_option_index"
property * generate_entity_index;// Reader/"generate_entity_index"
property * item_href;// Reader/"item_href"
property * item_prototype;// Reader/"item_prototype"
property * item_file;// Reader/"item_file"
property * section_index_href;// Reader/"section_index_href"
property * option_index_href;// Reader/"option_index_href"
property * start_entity_doc;// Reader/"start_entity_doc"
property * item_header;// Reader/"item_header"
property * entity_print;// Reader/"entity_print"
property * start_item_header;// Reader/"start_item_header"
property * end_item_header;// Reader/"end_item_header"
property * file_inline_css_style;// Reader/"file_inline_css_style"
property * set_item_module;// Reader/"set_item_module"
property * restore_module;// Reader/"restore_module"
property * princ_doc_word;// Reader/"princ_doc_word"
property * print_doc_word;// Reader/"print_doc_word"
property * isnext_ask;// Reader/"isnext?"
property * checknext_ask;// Reader/"checknext?"
property * pop_handle_I;// Reader/"pop_handle!"
property * equip_list;// Reader/"equip_list"
property * lexical_build_equip;// Reader/"lexical_build_equip"
property * where;// Reader/"where"
property * bind_frame;// Reader/"bind_frame"
property * unbind_frame;// Reader/"unbind_frame"

// module definition 
 void metaLoad();};

extern CL_EXPORT ReaderClass Reader;

#endif

