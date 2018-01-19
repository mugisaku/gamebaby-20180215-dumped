#ifndef utility_TEMPLATE
#define utility_TEMPLATE


#ifndef report
#define report printf("[report] %s, %s, %d\n",__FILE__,__func__,__LINE__);
#endif


namespace gbstd{


template<typename  T>
inline void
destruct(T&  t) noexcept
{
  t.~T();
}


template<typename  T>
inline T*
duplicate(T*  src) noexcept
{
  return src? new T(*src):nullptr;
}


}


#endif




