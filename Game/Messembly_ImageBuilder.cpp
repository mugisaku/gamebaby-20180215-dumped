#include"Messembly_ImageBuilder.hpp"
#include<new>




namespace gmbb{
namespace messembly{


struct
Source
{
  Opcode  opcode;

  Symbol*  symbol=nullptr;

  uint32_t  imm;

  Source(){}
  Source(Opcode  op, uint32_t  imm_): opcode(op), imm(imm_){}
  Source(Opcode  op, Symbol&  sym): opcode(op), symbol(&sym){}

  void  update() noexcept
  {
      if(symbol)
      {
        imm = symbol->index;
      }
  }

};


enum class
ElementKind
{
  null,
  entry,
  label,
  source,

};


union
ElementData
{
  Symbol*  symbol;
  Source   source;

   ElementData(){}
  ~ElementData(){}
};


struct
ImageBuilder::
Element
{
  ElementKind  kind=ElementKind::null;
  ElementData  data;

  Element*  next=nullptr;


  Element(){}
  Element(Symbol&  sym, bool  isent) noexcept: kind(isent? ElementKind::entry:ElementKind::label){data.symbol = &sym;}
  Element(Opcode  op, uint32_t  imm) noexcept: kind(ElementKind::source){new(&data) Source(op,imm);}
  Element(Opcode  op, Symbol&  sym) noexcept: kind(ElementKind::source){new(&data) Source(op,sym);}

        ElementData*  operator->()       noexcept{return &data;}
  const ElementData*  operator->() const noexcept{return &data;}

  bool  is_source() const noexcept{return kind == ElementKind::source;}
  bool  is_entry() const noexcept{return kind == ElementKind::entry;}
  bool  is_label() const noexcept{return kind == ElementKind::label;}

};


struct
ImageBuilder::
Status
{
  const std::string&  entry_name;

  uint32_t  count_of_condition=0;
  uint32_t  count_of_choosing=0;

  Status(const std::string&  s): entry_name(s){}

};




void
ImageBuilder::
clear() noexcept
{
    while(first)
    {
      auto  next = first->next;

      delete first       ;
             first = next;
    }


  first = nullptr;
   last = nullptr;

        string_list.clear();
  entry_symbol_list.clear();
  label_symbol_list.clear();
}




void
ImageBuilder::
push_element(Element*  e) noexcept
{
    if(!first)
    {
      first = e;
    }

  else
    {
      last->next = e;
    }


  last = e;
}


uint32_t
ImageBuilder::
append_string(const std::string&  s) noexcept
{
  auto  n = string_list.size();

  string_list.emplace_back(s);


  return n;
}


void
ImageBuilder::
append_label_symbol(const std::string&  s) noexcept
{
  push_element(new Element(get_label_symbol(s),false));
}


void
ImageBuilder::
append_entry_symbol(const std::string&  s) noexcept
{
  push_element(new Element(get_entry_symbol(s),true));
}




Symbol&
ImageBuilder::
get_label_symbol(const std::string&  s) noexcept
{
    for(auto&  sym: label_symbol_list)
    {
        if(sym.name == s)
        {
          return sym;
        }
    }


  auto  i = label_symbol_list.size();

  label_symbol_list.emplace_back(s,i);

  return label_symbol_list.back();
}


Symbol&
ImageBuilder::
get_entry_symbol(const std::string&  s) noexcept
{
    for(auto&  sym: entry_symbol_list)
    {
        if(sym.name == s)
        {
          return sym;
        }
    }


  auto  i = entry_symbol_list.size();

  entry_symbol_list.emplace_back(s,i);

  return entry_symbol_list.back();
}




void
ImageBuilder::
push_choosing(const gamn::List&  ls, Status&  st) noexcept
{
  char  buf[256];

  snprintf(buf,sizeof(buf),"%s_choosing%03d",st.entry_name.data(),st.count_of_choosing++);

  const std::string  base_s(buf);

  const std::string  begin_s(base_s+"_begin");
  const std::string    end_s(base_s+"_end");

  append_label_symbol(begin_s);

  std::vector<const gamn::Value*>  entries;

    for(auto&  v: ls)
    {
        if(v.is_value("entry"))
        {
          auto&  vv = v.get_value();

          push_element(new Element(Opcode::adb,append_string(vv.get_name())));

          entries.emplace_back(&vv);
        }
    }


  push_element(new Element(Opcode::xch,0));

  int  n = 0;

    for(auto&  v: entries)
    {
      snprintf(buf,sizeof(buf),"%s_entry%03d_begin",base_s.data(),n+1);

      const std::string  next_ent_begin_s(buf);


      push_element(new Element(Opcode::neq,n));
      push_element(new Element(Opcode::bra,get_label_symbol(next_ent_begin_s)));

      push_value(*v,st);

      push_element(new Element(Opcode::jmp,get_label_symbol(end_s)));

      append_label_symbol(next_ent_begin_s);


      ++n;
    }


  append_label_symbol(end_s);
}


void
ImageBuilder::
push_value(const gamn::Value&  v, Status&  st) noexcept
{
    if(v.is_list())
    {
      auto&  name = v.get_name();
      auto&    ls = v.get_list();

        if(name == "choosing")
        {
          push_choosing(ls,st);
        }

      else
        {
            for(auto&  vv: ls)
            {
              push_value(vv,st);
            }
        }
    }

  else
    if(v.is_string())
    {
      auto&  name = v.get_name();
      auto&     s = v.get_string();

           if(name == "text"      ){push_element(new Element(Opcode::ttx,append_string(s)));}
      else if(name == "set_flag"  ){push_element(new Element(Opcode::sfl,append_string(s)));}
      else if(name == "unset_flag"){push_element(new Element(Opcode::ufl,append_string(s)));}
      else if(name == "reference" ){push_element(new Element(Opcode::cal,get_entry_symbol(s)));}
      else if(name == "function"  ){push_element(new Element(Opcode::xfn,append_string(s)));}
      else
        {
          push_element(new Element(Opcode::cal,get_entry_symbol(s)));
        }
    }

  else
    if(v.is_pair())
    {
      char  buf[256];

      snprintf(buf,sizeof(buf),"%s_cond%03d",st.entry_name.data(),st.count_of_condition++);

      const std::string  base_s(buf);

      const std::string   cond_begin_s(base_s+"_begin");
      const std::string     cond_end_s(base_s+"_end");
      const std::string   left_begin_s(base_s+"_left_begin");
      const std::string  right_begin_s(base_s+"_right_begin");

      append_label_symbol(cond_begin_s);


      push_element(new Element(Opcode::tfl,string_list.size()));

      string_list.emplace_back(v.get_name());


      push_element(new Element(Opcode::bra,get_label_symbol(left_begin_s)));


      auto&  p = v.get_pair();

      append_label_symbol(right_begin_s);

      push_value(p.right,st);

      push_element(new Element(Opcode::jmp,get_label_symbol(cond_end_s)));

      append_label_symbol(left_begin_s);

      push_value(p.left,st);

      append_label_symbol(cond_end_s);
    }
}


void
ImageBuilder::
push_entry(const std::string&  name, const gamn::List&  ls) noexcept
{
  append_entry_symbol(name);

  Status  st(name);

    for(auto&  v: ls)
    {
      push_value(v,st);
    }


  push_element(new Element(Opcode::ret,0));
}


void
ImageBuilder::
push_entry_list(const gamn::List&  ls) noexcept
{
    for(auto&  v: ls)
    {
        if(v.is_list())
        {
          push_entry(v.get_name(),v.get_list());
        }
    }
}




void
ImageBuilder::
finalize() noexcept
{
  uint32_t  index = 0;

  auto  cur = first;

    while(cur)
    {
      auto&  e = *cur            ;
                  cur = cur->next;

        if(e.is_source())
        {
          ++index;
        }

      else
        if(e.is_entry() ||
           e.is_label())
        {
          e->symbol->index = index;
        }
    }


  cur = first;

    while(cur)
    {
      auto&  e = *cur            ;
                  cur = cur->next;

        if(e.is_source())
        {
          e->source.update();
        }
    }
}


namespace{
template<typename  SRC, typename  DST>
void
transfer(const SRC&  src, DST&  dst) noexcept
{
  auto  n = src.size();

  dst.resize(n);

  auto  src_it = src.cbegin();
  auto  dst_it = dst.begin();

    while(n--)
    {
      *dst_it++ = *src_it++;
    }
}
}


Image
ImageBuilder::
build() const noexcept
{
  std::vector<Symbol>  entry_symbol_table;
  std::vector<Symbol>  label_symbol_table;
  std::vector<std::string>   string_table;
  std::vector<Instruction>  binary;

  transfer(      string_list,      string_table);
  transfer(entry_symbol_list,entry_symbol_table);
  transfer(label_symbol_list,label_symbol_table);

  auto  cur = first;

    while(cur)
    {
      auto&  e = *cur            ;
                  cur = cur->next;

        if(e.is_source())
        {
          auto&  src = e->source;

          binary.emplace_back(src.opcode,src.imm);
        }
    }


  return Image(std::move(entry_symbol_table),
               std::move(label_symbol_table),
               std::move(string_table),
               std::move(binary));
}




void
ImageBuilder::
print() const noexcept
{
  auto  cur = first;

  uint32_t  i = 0;

    while(cur)
    {
      auto&  e = *cur            ;
                  cur = cur->next;

        if(e.is_source())
        {
          auto&  src = e->source;

          printf("%4d  ",i++);

            switch(src.opcode)
            {
          case(Opcode::nop): printf("nop");break;
          case(Opcode::sfl): printf("sfl \"%s\"",string_list[src.imm].data());break;
          case(Opcode::ufl): printf("ufl \"%s\"",string_list[src.imm].data());break;
          case(Opcode::tfl): printf("tfl \"%s\"",string_list[src.imm].data());break;
          case(Opcode::ttx): printf("ttx \"%s\"",string_list[src.imm].data());break;
          case(Opcode::adb): printf("adb \"%s\"",string_list[src.imm].data());break;
          case(Opcode::eq ): printf("eq  %4d",src.imm);break;
          case(Opcode::neq): printf("neq %4d",src.imm);break;
          case(Opcode::jmp): printf("jmp %s(%4d)",src.symbol->name.data(),src.symbol->index);break;
          case(Opcode::bra): printf("bra %s(%4d)",src.symbol->name.data(),src.symbol->index);break;
          case(Opcode::xch): printf("xch");break;
          case(Opcode::xfn): printf("xfn %s",string_list[src.imm].data());break;
          case(Opcode::cal): printf("cal %s(%4d)",src.symbol->name.data(),src.symbol->index);break;
          case(Opcode::ret): printf("ret");break;
            }


          printf("\n");
        }

      else
        if(e.is_label() ||
           e.is_entry())
        {
          printf("%s:\n",e->symbol->name.data());
        }
    }
}




}}




