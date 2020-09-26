//
//  court_score.h
//  practice_member
//
//  Created by 長澤達也 on 2019/11/06.
//  Copyright © 2019 長澤達也. All rights reserved.
//
/*役割
    評価に用いる要素のうち,各練習面に関するスコアをつける関数群
    court_score...全ての面でのcourt_scoreの合計値を求める
    court_score_rank...面内での最大ランク差による点数.ランク差が大きいほど減点
    court_score_sum...3人面と4人面で構成できるか,全体の人数による評価.構成できない場合は大幅減点.4人面が多いと高評価
    court_score_year...学年構成による評価.同学年のみだと減点(特に最低学年のみ).全体に最高学年がいないと減点
*/

#ifndef court_score_h
#define court_score_h

#include <stdio.h>
#include "free.h"

double court_score(info f,detail det);
double court_score_rank(info f,court x);
double court_score_sum(info f,court x);
double court_score_year(info f,court x);


#endif /* court_score_h */
