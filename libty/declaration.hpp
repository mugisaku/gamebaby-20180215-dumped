#ifndef declaration_HPP
#define declaration_HPP


#include<string>
#include<memory>



namespace ty{
namespace ty_types{




template<typename  T>
class
declaration
{
public:
  using pointer = std::unique_ptr<T>;

private:
  std::string  m_name;

  pointer  m_definition;

public:
  declaration() noexcept: m_definition(nullptr){}

  declaration(std::string_view  name) noexcept:
  m_name(name){}

  declaration(std::string_view  name, pointer&&  def) noexcept:
  m_name(name),
  m_definition(std::move(def)){}


  std::string&  get_name() const noexcept{return m_name;}

  void      set_definition(pointer&&  def)       noexcept{       m_definition = std::move(def);}
  const T*  get_definition(              ) const noexcept{return m_definition.get()           ;}

  void print(FILE*  f) const noexcept
  {
    fprintf(f,"%s{\n",m_name.data());

      if(m_definition)
      {
        m_definition->print(f);
      }

    else
      {
        fprintf(f,"**have no definition**");
      }


    fprintf(f,"\n}");
  }

};


}


using ty_types::declaration;


}


#endif




