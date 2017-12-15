#ifndef Startup_HPP
#define Startup_HPP


#include"TemporaryData.hpp"
#include"gmbb_Standard.hpp"


namespace gmbb{


void  terminate_party_making() noexcept;

extern const coprocess  coprocess_of_party_making;




void  terminate_class_choosing() noexcept;

extern const coprocess  coprocess_of_class_choosing;




void  terminate_character_making() noexcept;

extern const coprocess  coprocess_of_character_making;




void  terminate_name_making() noexcept;

extern const coprocess  coprocess_of_name_making;


}




#endif




