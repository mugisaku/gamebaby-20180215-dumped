#include"libgbsnd/stmt.hpp"


namespace gbsnd{
namespace devices{


const stmt*  block::begin() const noexcept{return m_stmt_list.data();}
const stmt*    block::end() const noexcept{return m_stmt_list.data()+m_stmt_list.size();}


}}




