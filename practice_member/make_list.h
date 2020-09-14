//
//  random_member.h
//  practice_member
//
//  Created by 長澤達也 on 2019/11/05.
//  Copyright © 2019 長澤達也. All rights reserved.
//

#ifndef make_list_h
#define make_list_h

#include <stdio.h>
#include <time.h>
#include "setting.h"

/*役割
    各人の練習日程を表すlistと練習日程を表すindividualと,遺伝的アルゴリズムにおける各世代generation(individualの集合)の管理
    list<<individual<<generation
    new_individual...individualの初期化
    new_generation...generationの初期化
    random_list...最低条件を満たすlistをランダムに作成
    random_individual...最低条件を満たすindividualをランダムに作成
    copy_individual...individualを値渡しで作成
 */

typedef struct{ //個体.初期値はnew_individualで入力
    int gene; //世代数.g->indiに入力時に設定.初期値は-1
    int number; //個体の識別番号.g->indiに入力時に設定.初期値は-1
    double score; //評価関数値.初期値は-1
    int **list; //メインの練習日程.random_listで設定
}*individual;

typedef struct{ //世代
    int gene;
    individual *indi;   //個体の配列
    double *rank;   //適応度に応じた選択率.合計で1
    int max_indi; //rank最高の個体番号
}*generation;

individual new_individual(info f);
generation new_generation(info f);
void random_list(info f,int* list,int people);
individual random_individual(info f);
individual copy_individual(info f,individual a);

#endif /* make_list_h */
