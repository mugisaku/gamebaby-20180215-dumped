#ifndef ScriptManager_HPP
#define ScriptManager_HPP


#include"gamn.hpp"
#include"Messembly.hpp"


namespace gmbb{


bool  reset_machine(messembly::Machine&  m, const char*  entry_name) noexcept;

gamn::Value const*  find_script(char const*  module_name                         ) noexcept;
gamn::Value const*  find_script(char const*  module_name, char const*  value_name) noexcept;

void  load_script_file(char const*  filepath) noexcept;

}




#endif




