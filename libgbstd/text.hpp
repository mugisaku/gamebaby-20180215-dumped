#ifndef GMBB_text_HPP
#define GMBB_text_HPP


#include<string>
#include<cstdarg>


namespace gbstd{
namespace texts{


std::string_view  make_text(const char*  fmt, ...) noexcept;


}


using texts::make_text;


}




#endif




