//
//  personal_score.c
//  practice_member
//
//  Created by 長澤達也 on 2019/11/08.
//  Copyright © 2019 長澤達也. All rights reserved.
//

#include "personal_score.h"

double interval_score(info f,player me);
double equality_score(info f,player me);
double short_prac_score(info f,individual a);

double personal_score(info f,individual a,detail det){
     double score = 0;
     int i;
     for(i=0;i<f->people;i++){
         score += interval_score(f,det->players[i]);
         score += equality_score(f,det->players[i]);
     }
     score += short_prac_score(f,a);
     return score;
}

//2回の練習日程の間隔によるスコア
//練習が2回以外を実装する場合は要変更
double interval_score(info f,player me){
     personal_interval data = f->score_data->p_inter;
     double score = 0;
     int d1,d2;
     if(me->count!=2)printf("warning!練習回数が2回でない部員がいます.score計算を変更してください.\n");
     d1 = me->day_list[0];
     d2 = me->day_list[1];
     if(d1%2 == 0){
         switch (d2-d1) {
             case 1:
                 score = data->same_day; //同一日の練習
                 break;
             case 2:
                 score = data->row_morning;   //2日連続の朝練
                 break;
             case 3:
                 score = data->morning_to_night;    //朝-夜の連日練
                 break;
             case 5:case 7:case 9: //朝と夜1回ずつ
                 score = data->balance;
                 break;
             case 4:case 6: case 8: //朝練2回
                 score = data->two_morning;
                 break;
             default:
                 printf("error in interbal_score.\n 想定外の練習日程です: d1=%d,d2=%dです\n",d1,d2);
                 break;
         }
     }else{
         switch (d2-d1) {
             case 1:
                 score = data->night_to_morning; //夜-朝の連日連
                 break;
             case 2:
                 score = data->two_night;   //2日連続の夜練
                 break;
             case 3:case 5:case 7:   //朝と夜1回ずつ
                 score = data->balance;
                 break;
             case 4:case 6: case 8:  //夜練2回
                 score = data->two_night;
                 break;
             default:
                 printf("error in interbal_score.\n 想定外の練習日程です: \nd1=%d,d2=%dです\n",d1,d2);
                 break;
         }
     }
     return score;
 }
//自分より上の人と練習できるかによるスコア
//一緒に練習する最高位の人で判断
double equality_score(info f,player me){
    personal_equality data = f->score_data->p_equ;
    double score = 0;
    int i,best_rank;
    if(me->number < data->not_consider)return score; //'not_consider'位までの人は考慮しないbest_rank=max_people;
    best_rank = max_people;
    //全ての練習の中での最高ランクbest_rankを求める
    for(i=0;i<me->count;i++){
        if(me->members[i][0]<best_rank && me->members[i][0]!=-1)best_rank = me->members[i][0];
    }
    //最高位と自分のランクを比較して加減点
    if(me->number - best_rank  >=  data->up_rank){    //'up_rank'以上と練習できる場合加点
         score = data->up_point;
    }else if(best_rank == me->number ){
         score = data->down_point;   //上とできない場合減点
    }else{
         score = 0; //全ての練習が成立していない時は考慮しない
    }
    return score;
 }

//2限抜けの回数による減点
double short_prac_score(info f,individual a){
    personal_short_prac data = f->score_data->p_short;
    double score = 0;
    int i,j,c;
    for(i=0;i<f->people;i++){
        c = 0;
        for(j=0;j<DAY;j++){
            c += a->list[i][j]*f->short_list[i][j]; //練習箇所が2限抜けだったらカウント
        }
        switch (c) {
            //2限抜けが1回なら-100点,2回なら-300点
            case 2:
                score += data->double_short;
            case 1:
                score += data->single_short;
            case 0:
                break;
            default:
                printf("error in short_prac_score.c=%dに計算異常があります\n",c);
                break;
        }
    }
    return score;
}


