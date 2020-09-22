//
//  scoring.h
//  practice_member
//
//  Created by 長澤達也 on 2019/11/05.
//  Copyright © 2019 長澤達也. All rights reserved.
//
/*役割
    "良い練習日程"を評価するscoringと,その評価値に基づいて遺伝的アルゴリズムでの優先度を決めるrankを決定する。
    scoring...練習日程の評価値を決める.練習スコアと個人スコアの合計値
    rank_build...遺伝アルゴリズムの各場面で世代の中から各個体が選ばれる確率を決める.scoreが高いほど高く,合計が1になる様にする
*/


#ifndef scoring_h
#define scoring_h

#include <stdio.h>
#include "court_score.h"
#include "personal_score.h"

void scoring(info f,individual a);
void rank_build(info f,generation g);


#endif /* scoring_h */
