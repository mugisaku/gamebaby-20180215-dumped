#include"CharacterData.hpp"
#include"gmbb_unicode.hpp"


namespace gmbb{




void
CharacterData::
set_name(const char*  new_name) noexcept
{
  snprintf(name,sizeof(name),"%s",new_name);
}


void
CharacterData::
set_name(const NameBuffer&  nambuf) noexcept
{
  char*  dst = name;

  auto  src = nambuf.get_data();

    while(*src)
    {
      auto  p = UTF8Chunk(*src++).codes;

        while(*p)
        {
          *dst++ = *p++;
        }
    }


  *dst = 0;
}


}




