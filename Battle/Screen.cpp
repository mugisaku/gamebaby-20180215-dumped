#include"Screen.hpp"


namespace screen{


namespace{
gbstd::image
image(width,height);


gbstd::point
offset;


bool  add;
bool  render;
bool  reverse;

int  add_r;
int  add_g;
int  add_b;

gbstd::color_index
fill_color;

Subtitle*  first;
Subtitle*   last;


}


void                set_fill_color(gbstd::color_index  i) noexcept{fill_color = i;}
gbstd::color_index  get_fill_color(                     ) noexcept{return fill_color;}


void   enable_reverse_color() noexcept{reverse =  true;}
void  disable_reverse_color() noexcept{reverse = false;}

void   enable_render() noexcept{render =  true;}
void  disable_render() noexcept{render = false;}

void   enable_add_color() noexcept{add =  true;}
void  disable_add_color() noexcept{add = false;}

void  set_add_r(int  v) noexcept{add_r = v;}
void  set_add_g(int  v) noexcept{add_g = v;}
void  set_add_b(int  v) noexcept{add_b = v;}

int  get_add_r() noexcept{return add_r;}
int  get_add_g() noexcept{return add_g;}
int  get_add_b() noexcept{return add_b;}


gbstd::image&  get_image() noexcept{return image;}


const gbstd::image&
update(const gbstd::task&  root_task) noexcept
{
    if(fill_color)
    {
      gbstd::pixel  pix;

      pix.index = fill_color;
      pix.z     =          0;

      image.fill(pix);
    }


    if(render)
    {
      root_task.render(image,offset);
    }


    if(add)
    {
      image.add(add_r,
                add_g,
                add_b);
    }


    if(reverse)
    {
      image.reverse_color();
    }


  auto  cur = first;

    while(cur)
    {
      image.print(cur->string,cur->point,*cur->font);

      cur = cur->next;
    }


  return image;
}


void
insert_subtitle(Subtitle&  subt) noexcept
{
    if(last)
    {
      last->next = &subt;
    }

  else
    {
      first = &subt;
    }


  last = &subt;
}


}




