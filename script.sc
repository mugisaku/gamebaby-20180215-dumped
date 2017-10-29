

shop:{
  test:{
    commodity:{
      name:"さとう" price:0 number:-1
    }
    commodity:{
      name:"しお" price:0 number:-1
    }
    commodity:{
      name:"こしょう" price:0 number:-1
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

role:{
  hero:{
  }
  friend:{
    talk_action:{
         with:"hero"
      content:{
       "ぶきや　ぼうぐは　ちゃんと　そうびしないと"
       "いみが　ないんだぜ"
       "でも　まだ　しょりが　じっそう　されていないから"
       "ちゃんと　そうびしても"
       "いみが　ないんだぜ"
      }
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




