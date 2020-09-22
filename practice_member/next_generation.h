//
//  next_generation.h
//  practice_member
//
//  Created by 長澤達也 on 2019/11/05.
//  Copyright © 2019 長澤達也. All rights reserved.
//
/*役割
    "選択","交叉","突然変異"の3通りで前世代から次世代の個体(練習日程候補)を作り出す.
    selection..."選択"による個体生成.前世代の個体をそのまま次世代に引き継ぐ
    crossover..."交叉"による個体生成.各個人の練習日程を2つの親からランダムに選んで練習日程を構成.(個人レベルで)稀に突然変異させる.
    mutation..."突然変異"による個体生成.初代と同じ様に,希望日程のもとでランダムに練習日程を組む
    next_generation..."選択","交叉","突然変異"の3通りで前世代から次世代の個体(練習日程候補)を作り出す
    next_generation_random..."突然変異"のみで前世代から次世代の個体(練習日程候補)を作り出す.test検証用
*/

#ifndef next_generation_h
#define next_generation_h

#include <stdio.h>
#include "scoring.h"

individual selection(info f,generation g);
individual crossover(info f,generation g);
individual mutation(info f,generation g);
generation next_generation(info f,generation g);
generation next_generation_random(info f,generation g);

#endif /* next_generation_h */
