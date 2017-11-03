

response:{
  on_enter:{
    text:"ここは　こなや　だよ"
    text:"なにを　かうんだい？"
  }
  on_buy:{
    text:""
  }
  on_exit:{
    text:"また　きてくれよな"
  }
}


shop:{
  test:{
    commodity:{
      name:"さとう" price:10 number:-1
    }
    commodity:{
      name:"しお" price:10 number:-1
    }
    commodity:{
      name:"こしょう" price:30 number:-1
    }
    commodity:{
      name:"しあわせのこな" price:30000 number:-1
    }
  }
}


message:{
  no_data_for_talk:{
    text:"かいわデータがありません"
  }

  there_is_no_one_on_its_direction:{
    text:"その　ほうこうには　だれも　いない"
  }

  whether_hero_picks_up_item:{
    text:"${item_on_square}が　おちている"
    choosing:{
      entry:"ひろう":{
        trigger_event:"pick_up_item"
      }
      entry:"ひろわない":{
      }
    }
  }


  advice:{
    text:"ぶきや　ぼうぐは　ちゃんと　そうびしないと"
    text:"いみが　ないんだぜ"
    text:"でも　まだ　しょりが　じっそう　されていないから"
    text:"ちゃんと　そうびしても"
    text:"いみが　ないんだぜ"
  }

  shopping_please:{
    text:"ちょっと　おじかん　いいですか？"
    choosing:{
      entry:"はい":{
        text:"かいもの　していって　ください"
        choosing:{
          entry:"はい":{
            text:"うれしいです"
            call_shop:"test"
            command:exit
          }
          entry:"いいえ":{
            text:"かなしいです"
          }
        }
      }
      entry:"いいえ":{
        text:"そうですか・・・"
      }
    }


    text:"さようなら"
  }

  needing_happiness_powder:{
    if:"has_happiness_powder"{
      text:"あ　あんたが　もっているのは"
      text:"「しあわせのこな」じゃねえか？"
      text:"それを　おれに　くれるのかい？"
      choosing:{
        entry:"おう　やるよ":{
          text:"ありがてえ"
          erase:""
        }
        entry:"ぜったいに　やらん":{
          text:"ちっ　なんでえ"
          text:"だったら　あっちへ　いきやがれ"
        }
      }
    }
    else:{
      text:"ああ　ほしい"
      text:"「しあわせのこな」が　ほしいぜ"
    }
  }
}

role:{
  hero:{
  }
  friend:{
    talk_action:{
         with:"hero"
      content:"shopping_please"
    }
  }
}


routine: test:{
           new_piece:(
             name:"hero"
             role:"hero"
             initial_position:(x:1 y:1)
           )
           new_piece:(
             name:"friend"
             role:"friend"
             initial_position:(x:3 y:3)
           )
         }




