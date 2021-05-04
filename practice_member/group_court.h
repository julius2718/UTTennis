//
//  group_court.h
//  practice_member
//
//  Created by 長澤達也 on 2019/11/05.
//  Copyright © 2019 長澤達也. All rights reserved.
//
/*役割
    練習日程を評価するために,individualから各日程の練習情報courtと各個人の練習情報mycourtを生成する
    court_individual...individualに対応するcourt配列を生成
    input_mycourt...個人の参加する練習のcourt配列を生成(scoringで使用)
    member_list...個人の参加する面のメンバー配列を生成(scoringで使用)
 */

#ifndef group_court_h
#define group_court_h

#include <stdio.h>
#include "print.h"

typedef struct{
    int day; //どの練習か.0<=j<DAY
    int time;   //朝=0,昼=1,夜=2;
    int sum_num; //練習参加人数
    int *number; //info->listでの個人の番号.参加者のランクに相当
    int *year; //参加者の学年
    int *num_of_court; //面の人数.3か4.面わけ不可の時は[0]=0.末尾に-1
    double score; //練習スコア
}*court;

typedef struct{
    int number; //info->listでの個人の番号.ランクに相当
    int count; //練習回数
    int* day_list;  //練習参加日.0~DAY-1
    int** members;  //参加練習の同じ面のリスト
    double score;   //個人スコア
}*player;

typedef struct{
    court*  courts;//courtの配列
    player*   players;//各選手の参加情報
}*detail;

//面情報と個人の情報を一括に管理
detail detail_of_individual(info f,individual a);
int* member_list(info f,court x,int number);


#endif /* group_court_h */
