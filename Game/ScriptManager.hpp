#ifndef ScriptManager_HPP
#define ScriptManager_HPP


#include"gamn.hpp"


namespace gmbb{


gamn::Value const*  find_script(char const*  module_name                         ) noexcept;
gamn::Value const*  find_script(char const*  module_name, char const*  value_name) noexcept;

void  load_script_file(char const*  filepath) noexcept;

}




#endif




