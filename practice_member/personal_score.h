//
//  personal_score.h
//  practice_member
//
//  Created by 長澤達也 on 2019/11/08.
//  Copyright © 2019 長澤達也. All rights reserved.
//
/*役割
    評価に用いる要素のうち,各個人に関するスコアをつける関数群
    personal_score...全ての部員についてのpersonal_scoreの合計値を求める
    personal_score_interval...練習間隔によるスコア.同日練習や夜->朝は大幅減点
    personal_score_equality...上位の人と練習できるかによるスコア.できないと減点
    personal_score_2period...2限抜けの練習があると減点
*/

#ifndef personal_score_h
#define personal_score_h

#include <stdio.h>
#include "free.h"

double personal_score(info f,individual a,detail det);
double personal_score_interval(info f,player me);
double personal_score_equality(info f,player me);
double personal_score_2period(info f,individual a);


#endif /* personal_score_h */
