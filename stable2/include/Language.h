// interface definition for module Language
#ifndef CLAIREH_Language
#define CLAIREH_Language

  
class CL_EXPORT Instruction;
class CL_EXPORT Basic_instruction;
class CL_EXPORT Variable;
class CL_EXPORT Vardef;
class CL_EXPORT Complex_instruction;
class CL_EXPORT Instruction_with_var;
class CL_EXPORT Control_structure;
class CL_EXPORT Call;
class CL_EXPORT Call_star;
class CL_EXPORT Call_plus;
class CL_EXPORT Call_wcl;
class CL_EXPORT Princ_wcl;
class CL_EXPORT Assign;
class CL_EXPORT Gassign;
class CL_EXPORT And;
class CL_EXPORT Or;
class CL_EXPORT Quote;
class CL_EXPORT Optimized_instruction;
class CL_EXPORT Call_method;
class CL_EXPORT Call_method1;
class CL_EXPORT Call_method2;
class CL_EXPORT Call_slot;
class CL_EXPORT Call_array;
class CL_EXPORT Call_table;
class CL_EXPORT Update;
class CL_EXPORT Super;
class CL_EXPORT Cast;
class CL_EXPORT Return;
class CL_EXPORT If;
class CL_EXPORT Do;
class CL_EXPORT Let;
class CL_EXPORT When;
class CL_EXPORT Let_plus;
class CL_EXPORT Let_star;
class CL_EXPORT Iteration;
class CL_EXPORT For;
class CL_EXPORT iClaire_Ffor;
class CL_EXPORT Collect;
class CL_EXPORT Image;
class CL_EXPORT Select;
class CL_EXPORT Lselect;
class CL_EXPORT Exists;
class CL_EXPORT Case;
class CL_EXPORT While;
class CL_EXPORT ClaireHandle;
class CL_EXPORT Construct;
class CL_EXPORT List;
class CL_EXPORT Tuple;
class CL_EXPORT Set;
class CL_EXPORT Array;
class CL_EXPORT Printf;
class CL_EXPORT Error;
class CL_EXPORT Branch;
class CL_EXPORT Macro;
class CL_EXPORT Trace;
class CL_EXPORT Assert;
class CL_EXPORT Defclaire;
class CL_EXPORT Definition;
class CL_EXPORT Defobj;
class CL_EXPORT Defclass;
class CL_EXPORT Defmethod;
class CL_EXPORT Defarray;
class CL_EXPORT Defrule;
class CL_EXPORT Defvar;
class CL_EXPORT Language_demon;
class CL_EXPORT Language_rule_object;

class CL_EXPORT Instruction: public SystemObject{ 
    public:}
  ;

class CL_EXPORT Basic_instruction: public Instruction{ 
    public:}
  ;

class CL_EXPORT Variable: public Basic_instruction{ 
    public:
       symbol *pname;
       ClaireType *range;
       CL_INT index;
       CL_INT dindex;}
  ;

class CL_EXPORT Vardef: public Variable{ 
    public:}
  ;

class CL_EXPORT Complex_instruction: public Instruction{ 
    public:}
  ;

class CL_EXPORT Instruction_with_var: public Complex_instruction{ 
    public:
       Variable *var;}
  ;

class CL_EXPORT Control_structure: public Complex_instruction{ 
    public:}
  ;

class CL_EXPORT Call: public Control_structure{ 
    public:
       property *selector;
       list *args;}
  ;

class CL_EXPORT Call_star: public Call{ 
    public:}
  ;

class CL_EXPORT Call_plus: public Call{ 
    public:}
  ;

class CL_EXPORT Call_wcl: public Call{ 
    public:}
  ;

class CL_EXPORT Princ_wcl: public Call{ 
    public:}
  ;

class CL_EXPORT Assign: public Basic_instruction{ 
    public:
       OID var;
       OID arg;}
  ;

class CL_EXPORT Gassign: public Basic_instruction{ 
    public:
       global_variable *var;
       OID arg;}
  ;

class CL_EXPORT And: public Control_structure{ 
    public:
       list *args;}
  ;

class CL_EXPORT Or: public Control_structure{ 
    public:
       list *args;}
  ;

class CL_EXPORT Quote: public Basic_instruction{ 
    public:
       OID arg;}
  ;

class CL_EXPORT Optimized_instruction: public Complex_instruction{ 
    public:}
  ;

class CL_EXPORT Call_method: public Optimized_instruction{ 
    public:
       method *arg;
       list *args;}
  ;

class CL_EXPORT Call_method1: public Call_method{ 
    public:}
  ;

class CL_EXPORT Call_method2: public Call_method{ 
    public:}
  ;

class CL_EXPORT Call_slot: public Optimized_instruction{ 
    public:
       slot *selector;
       OID arg;
       ClaireBoolean *test;}
  ;

class CL_EXPORT Call_array: public Optimized_instruction{ 
    public:
       OID selector;
       OID arg;
       OID test;}
  ;

class CL_EXPORT Call_table: public Optimized_instruction{ 
    public:
       table *selector;
       OID arg;
       ClaireBoolean *test;}
  ;

class CL_EXPORT Update: public Optimized_instruction{ 
    public:
       OID selector;
       OID arg;
       OID value;
       OID var;}
  ;

class CL_EXPORT Super: public Control_structure{ 
    public:
       property *selector;
       ClaireType *cast_to;
       list *args;}
  ;

class CL_EXPORT Cast: public Basic_instruction{ 
    public:
       OID arg;
       ClaireType *set_arg;}
  ;

class CL_EXPORT Return: public Basic_instruction{ 
    public:
       OID arg;}
  ;

class CL_EXPORT If: public Control_structure{ 
    public:
       OID test;
       OID arg;
       OID other;}
  ;

class CL_EXPORT Do: public Control_structure{ 
    public:
       list *args;}
  ;

class CL_EXPORT Let: public Instruction_with_var{ 
    public:
       OID value;
       OID arg;}
  ;

class CL_EXPORT When: public Let{ 
    public:
       OID other;}
  ;

class CL_EXPORT Let_plus: public Let{ 
    public:}
  ;

class CL_EXPORT Let_star: public Let{ 
    public:}
  ;

class CL_EXPORT Iteration: public Instruction_with_var{ 
    public:
       OID set_arg;
       OID arg;}
  ;

class CL_EXPORT For: public Iteration{ 
    public:}
  ;

class CL_EXPORT iClaire_Ffor: public Instruction_with_var{ 
    public:
       OID set_arg;
       OID arg;
       OID forkedby;}
  ;

class CL_EXPORT Collect: public Iteration{ 
    public:
       ClaireType *of;}
  ;

class CL_EXPORT Image: public Iteration{ 
    public:
       ClaireType *of;}
  ;

class CL_EXPORT Select: public Iteration{ 
    public:
       ClaireType *of;}
  ;

class CL_EXPORT Lselect: public Iteration{ 
    public:
       ClaireType *of;}
  ;

class CL_EXPORT Exists: public Iteration{ 
    public:
       OID other;}
  ;

class CL_EXPORT Case: public Control_structure{ 
    public:
       OID var;
       list *args;}
  ;

class CL_EXPORT While: public Control_structure{ 
    public:
       OID test;
       OID arg;
       ClaireBoolean *other;}
  ;

class CL_EXPORT ClaireHandle: public Control_structure{ 
    public:
       OID test;
       OID arg;
       OID other;}
  ;

class CL_EXPORT Construct: public Complex_instruction{ 
    public:
       list *args;}
  ;

class CL_EXPORT List: public Construct{ 
    public:
       ClaireType *of;}
  ;

class CL_EXPORT Tuple: public Construct{ 
    public:}
  ;

class CL_EXPORT Set: public Construct{ 
    public:
       ClaireType *of;}
  ;

class CL_EXPORT Array: public Construct{ 
    public:
       ClaireType *of;}
  ;

class CL_EXPORT Printf: public Construct{ 
    public:}
  ;

class CL_EXPORT Error: public Construct{ 
    public:}
  ;

class CL_EXPORT Branch: public Construct{ 
    public:}
  ;

class CL_EXPORT Macro: public Construct{ 
    public:}
  ;

class CL_EXPORT Trace: public Construct{ 
    public:}
  ;

class CL_EXPORT Assert: public Construct{ 
    public:
       CL_INT index;
       char *external;}
  ;

class CL_EXPORT Defclaire: public Complex_instruction{ 
    public:}
  ;

class CL_EXPORT Definition: public Defclaire{ 
    public:
       ClaireClass *arg;
       list *args;}
  ;

class CL_EXPORT Defobj: public Definition{ 
    public:
       symbol *ident;}
  ;

class CL_EXPORT Defclass: public Defobj{ 
    public:
       list *params;
       ClaireBoolean *forward_ask;}
  ;

class CL_EXPORT Defmethod: public Defclaire{ 
    public:
       Call *arg;
       OID set_arg;
       OID body;
       OID inline_ask;}
  ;

class CL_EXPORT Defarray: public Defmethod{ 
    public:}
  ;

class CL_EXPORT Defrule: public Defclaire{ 
    public:
       symbol *ident;
       list *args;
       OID arg;
       OID body;}
  ;

class CL_EXPORT Defvar: public Defclaire{ 
    public:
       Variable *ident;
       OID arg;}
  ;

class CL_EXPORT Language_demon: public lambda{ 
    public:
       symbol *pname;
       CL_INT priority;
       lambda *formula;}
  ;

class CL_EXPORT Language_rule_object: public property{ 
    public:}
  ;
extern CL_EXPORT Instruction * close_Instruction1(Instruction *self);
extern CL_EXPORT void  option_respond_string50_Language(char *opt,list *l);
extern CL_EXPORT tuple * option_usage_string34_Language(char *self);
extern CL_EXPORT tuple * option_usage_string34_Language_(char *g0332);
extern CL_EXPORT OID  no_eval_Instruction(Instruction *self);
extern CL_EXPORT void  self_print_unbound_symbol_Language(unbound_symbol *self);
extern CL_EXPORT OID  self_eval_unbound_symbol(unbound_symbol *self);
extern CL_EXPORT void  self_print_Variable_Language(Variable *self);
extern CL_EXPORT void  ppvariable_Variable(Variable *self);
extern CL_EXPORT void  ppvariable_list(list *self);
extern CL_EXPORT OID  self_eval_Variable(Variable *self);
extern CL_EXPORT OID  write_value_Variable(Variable *self,OID val);
extern CL_EXPORT OID  self_eval_Vardef(Vardef *self);
extern CL_EXPORT OID  self_eval_global_variable(global_variable *self);
extern CL_EXPORT OID  write_value_global_variable(global_variable *self,OID val);
extern CL_EXPORT OID  apply_lambda(lambda *self,list *_Zl);
extern CL_EXPORT OID  call_lambda2(lambda *self,listargs *l);
extern CL_EXPORT OID  self_print_lambda_Language(lambda *self);
extern CL_EXPORT lambda * lambda_I_list(list *lvar,OID self);
extern CL_EXPORT OID  lexical_build_any(OID self,list *lvar,int n);
extern CL_EXPORT OID  lexical_build_imp_any1(OID self,list *lvar,int n);
extern CL_EXPORT OID  lexical_change_any(OID self,list *lvar);
extern CL_EXPORT ClaireClass * close_class(ClaireClass *self);
extern CL_EXPORT symbol * extract_symbol_any(OID self);
extern CL_EXPORT property * make_a_property_any(OID self);
extern CL_EXPORT OID  lbreak_void();
extern CL_EXPORT OID  put_buffer_void();
extern CL_EXPORT OID  checkfar_void();
extern CL_EXPORT OID  lbreak_integer(CL_INT n);
extern CL_EXPORT OID  indent_integer(CL_INT limit);
extern CL_EXPORT void  set_level_void();
extern CL_EXPORT void  set_level_integer(CL_INT n);
extern CL_EXPORT OID  printbox_bag1(bag *self,int start,int finish,char *s);
extern CL_EXPORT OID  printbox_bag2(bag *self);
extern CL_EXPORT OID  printbox_bag3(bag *self,char *s);
extern CL_EXPORT void  printl_bag(bag *self,char *s);
extern CL_EXPORT void  printexp_any(OID self,ClaireBoolean *comp);
extern CL_EXPORT void  pretty_print_any(OID self);
extern CL_EXPORT void  self_print_list_Language(list *self);
extern CL_EXPORT void  self_print_set_Language(set *self);
extern CL_EXPORT void  self_print_tuple_Language(tuple *self);
extern CL_EXPORT void  self_print_Princ_wcl1_Language(Princ_wcl *self);
extern CL_EXPORT void  self_print_Call_wcl1_Language(Call_wcl *self);
extern CL_EXPORT void  self_print_Call_Language(Call *self);
extern CL_EXPORT OID  self_print_Call_plus_Language(Call_plus *self);
extern CL_EXPORT OID  self_eval_Call(Call *self);
extern CL_EXPORT OID  self_eval_Call_plus(Call_plus *self);
extern CL_EXPORT void  printe_any(OID self,property *s);
extern CL_EXPORT ClaireBoolean * sugar_ask_any(OID x,OID x2,OID o,OID a);
extern CL_EXPORT void  self_print_Assign_Language(Assign *self);
extern CL_EXPORT OID  self_eval_Assign(Assign *self);
extern CL_EXPORT void  self_print_Gassign_Language(Gassign *self);
extern CL_EXPORT OID  self_eval_Gassign(Gassign *self);
extern CL_EXPORT void  self_print_And_Language(And *self);
extern CL_EXPORT OID  self_eval_And(And *self);
extern CL_EXPORT void  self_print_Or_Language(Or *self);
extern CL_EXPORT OID  self_eval_Or(Or *self);
extern CL_EXPORT void  self_print_Quote_Language(Quote *self);
extern CL_EXPORT OID  self_eval_Quote(Quote *self);
extern CL_EXPORT void  self_print_Call_method_Language(Call_method *self);
extern CL_EXPORT OID  self_eval_Call_method(Call_method *self);
extern CL_EXPORT OID  self_eval_Call_method1(Call_method1 *self);
extern CL_EXPORT OID  self_eval_Call_method2(Call_method2 *self);
extern CL_EXPORT void  self_print_Call_slot_Language(Call_slot *self);
extern CL_EXPORT OID  self_eval_Call_slot(Call_slot *self);
extern CL_EXPORT void  self_print_Call_array_Language(Call_array *self);
extern CL_EXPORT OID  self_eval_Call_array(Call_array *self);
extern CL_EXPORT void  self_print_Call_table_Language(Call_table *self);
extern CL_EXPORT OID  self_eval_Call_table(Call_table *self);
extern CL_EXPORT void  self_print_Update_Language(Update *self);
extern CL_EXPORT OID  self_eval_Update(Update *self);
extern CL_EXPORT void  self_print_Super_Language(Super *self);
extern CL_EXPORT OID  self_eval_Super(Super *self);
extern CL_EXPORT void  self_print_Cast_Language(Cast *x);
extern CL_EXPORT OID  self_eval_Cast(Cast *self);
extern CL_EXPORT void  self_print_Return_Language(Return *self);
extern CL_EXPORT OID  self_eval_Return(Return *self);
extern CL_EXPORT OID  substitution_any(OID self,Variable *x,OID val);
extern CL_EXPORT CL_INT  occurrence_any(OID self,Variable *x);
extern CL_EXPORT OID  instruction_copy_any(OID self);
extern CL_EXPORT void  self_print_If_Language(If *self);
extern CL_EXPORT void  printstat_If(If *self);
extern CL_EXPORT void  printif_any(OID self);
extern CL_EXPORT void  printelse_If(If *self);
extern CL_EXPORT OID  self_eval_If(If *self);
extern CL_EXPORT void  self_print_Do_Language(Do *self);
extern CL_EXPORT void  printdo_list(list *l,ClaireBoolean *clo);
extern CL_EXPORT void  printblock_any(OID x);
extern CL_EXPORT OID  self_eval_Do(Do *self);
extern CL_EXPORT void  self_print_Let_Language(Let *self);
extern CL_EXPORT void  printbody_Let(Let *self);
extern CL_EXPORT OID  self_eval_Let(Let *self);
extern CL_EXPORT void  self_print_When_Language(When *self);
extern CL_EXPORT OID  self_eval_When(When *self);
extern CL_EXPORT void  self_print_Let_plus_Language(Let_plus *self);
extern CL_EXPORT void  self_print_Let_star_Language(Let_star *self);
extern CL_EXPORT void  self_print_For_Language(For *self);
extern CL_EXPORT OID  self_eval_For(For *self);
extern CL_EXPORT void  self_print_Ffor1_Language(iClaire_Ffor *self);
extern CL_EXPORT OID  self_eval_Ffor1(iClaire_Ffor *self);
extern CL_EXPORT void  self_print_Collect_Language(Collect *self);
extern CL_EXPORT OID  self_eval_Collect(Collect *self);
extern CL_EXPORT void  self_print_Image_Language(Image *self);
extern CL_EXPORT OID  self_eval_Image(Image *self);
extern CL_EXPORT void  self_print_Select_Language(Select *self);
extern CL_EXPORT OID  self_eval_Select(Select *self);
extern CL_EXPORT void  self_print_Lselect_Language(Lselect *self);
extern CL_EXPORT OID  self_eval_Lselect(Lselect *self);
extern CL_EXPORT void  self_print_Exists_Language(Exists *self);
extern CL_EXPORT OID  self_eval_Exists(Exists *self);
extern CL_EXPORT void  self_print_Case_Language(Case *self);
extern CL_EXPORT OID  self_eval_Case(Case *self);
extern CL_EXPORT void  self_print_While_Language(While *self);
extern CL_EXPORT OID  self_eval_While(While *self);
extern CL_EXPORT void  self_print_Handle_Language(ClaireHandle *self);
extern CL_EXPORT OID  self_eval_Handle(ClaireHandle *self);
extern CL_EXPORT void  self_print_Construct_Language(Construct *self);
extern CL_EXPORT OID  self_eval_List(List *self);
extern CL_EXPORT OID  self_eval_Set(Set *self);
extern CL_EXPORT OID  self_eval_Tuple(Tuple *self);
extern CL_EXPORT OID  self_eval_Array2(Array *self);
extern CL_EXPORT OID  self_eval_Macro2(Macro *self);
extern CL_EXPORT void  self_eval_Error(Error *self);
extern CL_EXPORT OID  self_eval_Printf(Printf *self);
extern CL_EXPORT OID  self_eval_Trace(Trace *self);
extern CL_EXPORT OID  self_eval_Assert(Assert *self);
extern CL_EXPORT OID  self_eval_Branch(Branch *self);
extern CL_EXPORT OID  self_print_Definition_Language(Definition *self);
extern CL_EXPORT void  self_print_Defobj_Language(Defobj *self);
extern CL_EXPORT void  self_print_Defclass_Language(Defclass *self);
extern CL_EXPORT void  self_print_Defmethod_Language(Defmethod *self);
extern CL_EXPORT void  self_print_Defarray_Language(Defarray *self);
extern CL_EXPORT void  self_print_Defrule_Language(Defrule *self);
extern CL_EXPORT void  self_print_Defvar_Language(Defvar *self);
extern CL_EXPORT OID  self_eval_Definition(Definition *self);
extern CL_EXPORT OID  complete_object(ClaireObject *self,list *_Zl);
extern CL_EXPORT OID  self_eval_Defobj(Defobj *self);
extern CL_EXPORT ClaireBoolean * reified_ask_type1_Language(ClaireType *self);
extern CL_EXPORT OID  self_eval_Defclass(Defclass *self);
extern CL_EXPORT OID  self_eval_Defmethod(Defmethod *self);
extern CL_EXPORT void  fill_debug_placeholder_any1(OID x,OID m);
extern CL_EXPORT void  attach_comment_any(OID x);
extern CL_EXPORT list * extract_signature_list(list *l);
extern CL_EXPORT OID  extract_pattern_any(OID x,list *path);
extern CL_EXPORT ClaireType * extract_type_any(OID x);
extern CL_EXPORT OID  extract_item_any(OID x,OID y);
extern CL_EXPORT OID  extract_pattern_nth_list(list *l,list *path);
extern CL_EXPORT ClaireObject * extract_class_call_class(ClaireClass *self,list *l);
extern CL_EXPORT list * extract_range_any(OID x,list *lvar,list *ldef);
extern CL_EXPORT CL_INT  bit_vector_listargs2(listargs *l);
extern CL_EXPORT list * extract_status_any(OID x);
extern CL_EXPORT ClaireType * type_I_any(OID x);
extern CL_EXPORT OID  self_eval_Defarray(Defarray *self);
extern CL_EXPORT void  self_print_demon(Language_demon *self);
extern CL_EXPORT OID  funcall_demon1(Language_demon *self,OID x,OID y);
extern CL_EXPORT OID  funcall_demon2(Language_demon *self,OID x,OID y,OID z);
extern CL_EXPORT OID  self_eval_Defrule(Defrule *self);
extern CL_EXPORT ClaireBoolean * eventMethod_ask_relation2(ClaireRelation *r);
extern CL_EXPORT tuple * make_filter_any(OID cond);
extern CL_EXPORT tuple * make_filter_any_(OID g0596);
extern CL_EXPORT Language_demon * make_demon_relation(ClaireRelation *R,symbol *n,list *lvar,OID cond,OID conc);
extern CL_EXPORT Call * readCall_relation(ClaireRelation *R,OID x);
extern CL_EXPORT Call * putCall_relation2(ClaireRelation *R,OID x,OID y);
extern CL_EXPORT ClaireType * safeRange_relation(ClaireRelation *x);
extern CL_EXPORT void  eval_if_write_relation(ClaireRelation *R);
extern CL_EXPORT void  eventMethod_property(property *p);
extern CL_EXPORT void  interface_property(property *p);
extern CL_EXPORT void  interface_class(ClaireClass *c,listargs *l);

// namespace class for Language 
class CL_EXPORT LanguageClass: public NameSpace {
public:

  ClaireClass * _Instruction;
  ClaireClass * _Basic_instruction;
  global_variable * DEBUG_ask;
  global_variable * CAN_INIT_LOCATION_ask;
  table * CODE_LOCS;
  property * equip;
  property * init_location;
  global_variable * typing;
  global_variable * index;
  ClaireClass * _Variable;
  ClaireClass * _Vardef;
  ClaireClass * _Complex_instruction;
  ClaireClass * _Instruction_with_var;
  ClaireClass * _Control_structure;
  global_variable * MAX_INTEGER;
  global_variable * _starvariable_index_star;
  property * printl;
  global_variable * LastCall;
  ClaireClass * _Call;
  ClaireClass * _Call_star;
  ClaireClass * _Call_plus;
  ClaireClass * _Call_wcl;
  ClaireClass * _Princ_wcl;
  property * echo;
  property * self_html;
  property * breakpoint;
  ClaireClass * _Assign;
  ClaireClass * _Gassign;
  ClaireClass * _And;
  ClaireClass * _Or;
  ClaireClass * _Quote;
  ClaireClass * _Optimized_instruction;
  ClaireClass * _Call_method;
  ClaireClass * _Call_method1;
  ClaireClass * _Call_method2;
  ClaireClass * _Call_slot;
  ClaireClass * _Call_array;
  ClaireClass * _Call_table;
  ClaireClass * _Update;
  ClaireClass * _Super;
  ClaireClass * _Cast;
  ClaireClass * _Return;
  ClaireClass * _If;
  ClaireClass * _Do;
  ClaireClass * _Let;
  ClaireClass * _When;
  ClaireClass * _Let_plus;
  ClaireClass * _Let_star;
  ClaireClass * _Iteration;
  property * iterate;
  property * Iterate;
  ClaireClass * _For;
  ClaireClass * _Ffor;
  ClaireClass * _Collect;
  ClaireClass * _Image;
  ClaireClass * _Select;
  ClaireClass * _Lselect;
  ClaireClass * _Exists;
  ClaireClass * _Case;
  ClaireClass * _While;
  ClaireClass * _Handle;
  ClaireClass * _Construct;
  ClaireClass * _List;
  ClaireClass * _Tuple;
  ClaireClass * _Set;
  ClaireClass * _Array;
  ClaireClass * _Printf;
  ClaireClass * _Error;
  ClaireClass * _Branch;
  ClaireClass * _Macro;
  property * macroexpand;
  ClaireClass * _Trace;
  ClaireClass * _Assert;
  property * extract_item;
  property * function_I;
  global_variable * LastComment;
  global_variable * NeedComment;
  ClaireClass * _Defclaire;
  ClaireClass * _Definition;
  ClaireClass * _Defobj;
  ClaireClass * _Defclass;
  ClaireClass * _Defmethod;
  ClaireClass * _Defarray;
  ClaireClass * _Defrule;
  ClaireClass * _Defvar;
  property * complete;
  property * reified_ask;
  global_variable * LDEF;
  global_variable * _NEW_ALLOC;
  global_variable * _BAG_UPDATE;
  global_variable * _SLOT_UPDATE;
  global_variable * _RETURN_ARG;
  global_variable * _SAFE_RESULT;
  global_variable * _SAFE_GC;
  property * bit_vector;
  ClaireClass * _demon;
  table * demons;
  operation * _inf_dash;
  ClaireClass * _rule_object;
  table * relations;
  table * last_rule;
  property * eval_rule;
  table * InterfaceList;
  property * ClaireInterface;
property * type_I;// iClaire/"type!"
property * forward_ask;// iClaire/"forward?"
property * no_eval;// Language/"no_eval"
property * ppvariable;// Language/"ppvariable"
property * write_value;// Language/"write_value"
property * var;// claire/"var"
property * lambda_I;// iClaire/"lambda!"
property * lexical_build;// iClaire/"lexical_build"
property * lexical_change;// iClaire/"lexical_change"
property * extract_symbol;// iClaire/"extract_symbol"
property * make_a_property;// iClaire/"make_a_property"
property * lbreak;// Language/"lbreak"
property * put_buffer;// Language/"put_buffer"
property * checkfar;// Language/"checkfar"
property * indent;// Language/"indent"
property * make_filter;// Language/"make_filter"
property * set_level;// Language/"set_level"
property * printbox;// Language/"printbox"
property * printexp;// Language/"printexp"
property * pretty_print;// claire/"pretty_print"
property * assign;// Language/"assign"
property * printe;// Language/"printe"
property * sugar_ask;// Language/"sugar?"
property * cast_to;// iClaire/"cast_to"
property * set_arg;// iClaire/"set_arg"
property * substitution;// claire/"substitution"
property * instruction_copy;// Language/"instruction_copy"
property * other;// iClaire/"other"
property * test;// iClaire/"test"
property * printstat;// Language/"printstat"
property * pname;// Language/"pname"
property * priority;// Language/"priority"
property * extract_type;// iClaire/"extract_type"
property * extract_pattern_nth;// Language/"extract_pattern_nth"
property * extract_class_call;// iClaire/"extract_class_call"
property * extract_range;// iClaire/"extract_range"
property * extract_status;// iClaire/"extract_status"
property * make_demon;// Language/"make_demon"
property * eval_if_write;// Language/"eval_if_write"
property * readCall;// Language/"readCall"
property * eventMethod;// Language/"eventMethod"
property * eventMethod_ask;// Language/"eventMethod?"
property * putCall;// Language/"putCall"
property * safeRange;// Language/"safeRange"
property * forkedby;// iClaire/"forkedby"
property * printif;// Language/"printif"
property * printelse;// Language/"printelse"
property * printdo;// Language/"printdo"
property * printblock;// Language/"printblock"
property * printbody;// Language/"printbody"
property * ident;// iClaire/"ident"
property * attach_comment;// Language/"attach_comment"
property * extract_signature;// iClaire/"extract_signature"
property * extract_pattern;// iClaire/"extract_pattern"
property * dindex;// iClaire/"dindex"
property * fill_debug_placeholder;// Language/"fill_debug_placeholder"
property * lexical_build_imp;// Language/"lexical_build_imp"

// module definition 
 void metaLoad();};

extern CL_EXPORT LanguageClass Language;

#endif

