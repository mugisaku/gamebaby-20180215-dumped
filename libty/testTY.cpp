#include"ty.hpp"


using namespace ty;


struct
type_manager
{
  std::vector<type_decl>  type_decl_list;

  type_manager()
  {
    type_decl_list.emplace_back(type_info::make_i8(),"int8_t");
    type_decl_list.emplace_back(type_info::make_u8(),"uint8_t");
    type_decl_list.emplace_back(type_info::make_i16(),"int16_t");
    type_decl_list.emplace_back(type_info::make_u16(),"uint16_t");
    type_decl_list.emplace_back(type_info::make_i32(),"int32_t");
    type_decl_list.emplace_back(type_info::make_u32(),"uint32_t");
  }

  void  read(const char*  s)
  {
  }

};


type_manager
type_mgr;


int
main(int  argc, char**  argv)
{

  return 0;
}




