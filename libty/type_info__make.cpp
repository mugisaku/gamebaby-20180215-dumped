#include"type_info_PRIVATE.hpp"



namespace ty{
namespace ty_types{


type_info  type_info::make_i8()  noexcept{return type_info("i8",type_kind::integral         , 1);}
type_info  type_info::make_u8()  noexcept{return type_info("u8",type_kind::unsigned_integral,1);}
type_info  type_info::make_i16() noexcept{return type_info("i16",type_kind::integral         ,2);}
type_info  type_info::make_u16() noexcept{return type_info("u16",type_kind::unsigned_integral,2);}
type_info  type_info::make_i32() noexcept{return type_info("i32",type_kind::integral         ,4);}
type_info  type_info::make_u32() noexcept{return type_info("u32",type_kind::unsigned_integral,4);}

type_info  type_info::make_boolean()         noexcept{return type_info("b",type_kind::boolean,1);}
type_info  type_info::make_void()            noexcept{return type_info("v",type_kind::void_,0);}
type_info  type_info::make_null_pointer()    noexcept{return type_info("np",type_kind::null_pointer,pointer_type_size);}
type_info  type_info::make_generic_pointer() noexcept{return type_info("gp",type_kind::generic_pointer,pointer_type_size);}

type_info  type_info::make_array(const type_info&  ti, size_t  n)  noexcept{return type_info(array_def(ti,n));}
type_info  type_info::make_empty_enum()   noexcept{return type_info(  enum_def());}
type_info  type_info::make_empty_struct() noexcept{return type_info(struct_def());}
type_info  type_info::make_empty_union()  noexcept{return type_info( union_def());}


}}




