#ifndef ReferenceWrapper_TEMPLATE
#define ReferenceWrapper_TEMPLATE


#include<cstddef>
#include<cstdint>


#ifndef report
#define report printf("[report] %s, %s, %d\n",__FILE__,__func__,__LINE__);
#endif


template<typename  T>
class
reference_wrapper
{
  T*  data;

public:
  using value_type = T;

  constexpr reference_wrapper(        ) noexcept: data(std::addressof(T::get_default())){}
  constexpr reference_wrapper(T&   ent) noexcept: data(std::addressof(ent             )){}
  constexpr reference_wrapper(T&&  ent) noexcept=delete;

  reference_wrapper  operator=(T&  ent) noexcept
  {
    data = std::addressof(ent);

    return *this;
  }

  constexpr T&  get() const noexcept{return *data;}
  constexpr operator T&() const noexcept{return *data;}

};


template<typename  T>
inline reference_wrapper<T>
make_ref(T&  t) noexcept
{
  return reference_wrapper<T>(t);
}


#endif




