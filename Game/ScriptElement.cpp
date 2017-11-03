#include"ScriptElement.hpp"
#include"Script.hpp"
#include<new>


namespace gmbb{




ScriptElement::
ScriptElement(gamn::Value const&  v) noexcept
{
    if(v.is_string("text"))
    {
      kind = ScriptElementKind::text;

      new(&data) std::string(v.get_string());
    }

  else
    if(v.is_string("call_shop"))
    {
      kind = ScriptElementKind::call_shop;

      new(&data) std::string(v.get_string());
    }

  else
    if(v.is_string("command"))
    {
      kind = ScriptElementKind::command;

      new(&data) std::string(v.get_string());
    }

  else
    if(v.is_list("choosing"))
    {
      kind = ScriptElementKind::choosing;

      new(&data) std::vector<ChoosingEntry>();

        for(auto&  vv: v.get_list())
        {
            if(vv.is_value("entry"))
            {
              auto&  vvv = vv.get_value();

                if(vvv.is_list())
                {
                  data.choosing.emplace_back(vvv.get_name(),new Script(vvv.get_list()));
                }
            }
        }
    }

  else
    if(v)
    {
      printf("[scriptelement error] unprocessable value...");

      v.print();

      printf("\n");

      fflush(stdout);
    }
}





ScriptElement&
ScriptElement::
operator=(ScriptElement&&  rhs) noexcept
{
  clear();

  std::swap(kind,rhs.kind);

    switch(kind)
    {
  case(ScriptElementKind::null):
      break;
  case(ScriptElementKind::script):
      data.script = rhs.data.script;
      break;
  case(ScriptElementKind::text):
  case(ScriptElementKind::command):
  case(ScriptElementKind::call_shop):
      new(&data) std::string(std::move(rhs.data.string));
      break;
  case(ScriptElementKind::choosing):
      new(&data) std::vector<ChoosingEntry>(std::move(rhs.data.choosing));
      break;
    }
}


void
ScriptElement::
clear() noexcept
{
    switch(kind)
    {
  case(ScriptElementKind::null):
      break;
  case(ScriptElementKind::script):
      delete data.script;
      break;
  case(ScriptElementKind::text):
  case(ScriptElementKind::command):
  case(ScriptElementKind::call_shop):
      data.string.~basic_string();
      break;
  case(ScriptElementKind::choosing):
      data.choosing.~vector();
      break;
    }


  kind = ScriptElementKind::null;
}


void
ScriptElement::
print() const noexcept
{
    switch(kind)
    {
  case(ScriptElementKind::null):
      printf("(null script element)");
      break;
  case(ScriptElementKind::script):
      data.script->print();
      break;
  case(ScriptElementKind::text):
      printf("text:\"%s\"",data.string.data());
      break;
  case(ScriptElementKind::command):
      printf("command:\"%s\"",data.string.data());
      break;
  case(ScriptElementKind::call_shop):
      printf("call_shop:\"%s\"",data.string.data());
      break;
  case(ScriptElementKind::choosing):
      printf("choosing:{\n");

        for(auto&  ent: data.choosing)
        {
          printf("entry:\"%s\":",ent.text.data());

          ent.script->print();
        }


      printf("}\n");
      break;
    }
}


}




