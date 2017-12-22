#ifndef print_HPP
#define print_HPP


#include<cstdio>



namespace ty{
namespace ty_types{


inline void
print_indent(FILE*  f, size_t  indent=1) noexcept
{
    while(indent--)
    {
      fprintf(f,"  ");
    }
}


}}


#endif




