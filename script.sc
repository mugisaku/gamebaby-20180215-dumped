

shop:{
  test:{
    commodity:{
      item:"てつのつるぎ" price:0 number:-1
    }
    commodity:{
      item:"かわのたて" price:0 number:-1
    }
    commodity:{
      item:"やすいおび" price:0 number:-1
    }
    commodity:{
      item:"ただのみず" price:0 number:-1
    }
  }
}


message:{
  test:{
    "ちょっと　おじかん　いいですか？"
    choosing:{
      "はい":{
        "かいもの　していって　ください"
        choosing:{
          "はい":{
            "うれしいです"
            call_shop:shop_name:"test"
         }
          "いいえ":{
            "かなしいです"
          }
        }
      }
      "いいえ":{
        "そうですか・・・"
      }
    }
  }
}

routine: test:{
           new_piece:(
             name:"friend"
             initial_position:(x:3 y:3)
             talk:{
                  with:"hero"
               content:{
                "ぶきや　ぼうぐは　ちゃんと　そうびしないと"
                "いみが　ないんだぜ"
                "でも　まだ　しょりが　じっそう　されていないから"
                "ちゃんと　そうびしても"
                "いみが　ないんだぜ"
               }
             }
           )
         }




