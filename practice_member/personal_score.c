//
//  personal_score.c
//  practice_member
//
//  Created by 長澤達也 on 2019/11/08.
//  Copyright © 2019 長澤達也. All rights reserved.
//

#include "personal_score.h"

double calc_interval(int d1,int d2,personal_interval data);
double personal_score_interval(info f,player me);
double personal_score_equality(info f,player me);
double personal_score_2period(info f,individual a);


double personal_score(info f,individual a,detail det){
     player p;
     int i;
    double score = 0;
     for(i=0;i<f->people;i++){
         p = det->players[i];
         p->score = 0;
         p->score += personal_score_interval(f,p);
         p->score += personal_score_equality(f,p);
         score += p->score;
     }
     score += personal_score_2period(f,a);
     return score;
}

//2回の練習日程の間隔によるスコア
//練習が2回以外を実装する場合は要変更
double personal_score_interval(info f,player me){
    personal_interval data = f->score_data->p_inter;
    double score = 0;
    int i;
    if(me->count<2)return score;    //練習間隔が存在しない部員
    for(i=0;i<me->count-1;i++){
        score += calc_interval(me->day_list[i],me->day_list[i+1],data);
    }
    /*
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
     */
     return score;
 }
//自分より上の人と練習できるかによるスコア
//一緒に練習する最高位の人で判断
double personal_score_equality(info f,player me){
    personal_equality data = f->score_data->p_equ;
    double score = 0;
    int i,best_rank;
    if(me->number < data->not_consider)return score; //'not_consider'位までの人は考慮しない
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
double personal_score_2period(info f,individual a){
    personal_short_prac data = f->score_data->p_short;
    double score = 0;
    int i,j,c;
    for(i=0;i<f->people;i++){
        c = 0;
        for(j=0;j<DAY;j++){
            c += a->list[i][j]*f->short_list[i][j]; //練習箇所が2限抜けだったらカウント
        }
        if(c==1){
            score += data->single_short;
        }else if(c>1){
            score += (c-1)*data->double_short;
        }
    }
    return score;
}


double calc_interval(int d1,int d2,personal_interval data){
    double ans = 0;
    int x1,x2,y1,y2;//x:曜日,y:朝昼夜
    if(DAY == 10){
        x1 = d1/2;x2 = d2/2;
        y1 = d1%2;y2 = d2%2;
    }else if(DAY == 15){
        x1 = d1/3;x2 = d2/3;
        y1 = d1%3;y2 = d2%3;
    }else{
        return 0; //朝夜or朝昼夜練以外でのスコアは未定義
    }
    if(x1==x2){
        ans = data->same_day;  //同一日の練習
    }else if(x2-x1 == 1){
        if(d2-d1 == 1){
            ans = data->night_to_morning;  //連続夜->朝練習
        }else{
            ans = data->row_day;   //連日の練習(夜->朝を除く)
        }
    }
    if(y1==0 && y2==0){
        ans += data->two_morning;   //朝練2回
    }else if(y1==1 && y2==1){
        if(DAY==15) ans += data->two_noon;  //昼練2回
        if(DAY==10) ans += data->two_night; //夜練2回
    }else if(y1==2 && y2==2){
        ans += data->two_night; //夜練2回
    }
    if(d1 == 0) ans += data->mon_morning; //月朝練習による追加減点
    if(d1 == DAY-1) ans += data->fri_night; //金夜練習による追加減点
    return ans;
}
