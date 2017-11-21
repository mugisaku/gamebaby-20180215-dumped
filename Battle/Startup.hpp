#ifndef Startup_HPP
#define Startup_HPP


#include"TemporaryData.hpp"
#include"gmbb_Standard.hpp"


namespace gmbb{


void  terminate_party_making() noexcept;

void  start_party_making(coreturn_t  ret) noexcept;




void  terminate_class_choosing() noexcept;

void  start_class_choosing(coreturn_t  ret) noexcept;




void  terminate_character_making() noexcept;

void  start_character_making(coreturn_t  ret, int  number) noexcept;




void  terminate_name_making() noexcept;

void  start_name_making(coreturn_t  ret) noexcept;
}




#endif




