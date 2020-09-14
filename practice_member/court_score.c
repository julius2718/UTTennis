//
//  court_score.c
//  practice_member
//
//  Created by 長澤達也 on 2019/11/06.
//  Copyright © 2019 長澤達也. All rights reserved.
//

#include "court_score.h"
double court_score_rank(info f,court x);
double court_score_sum(info f,court x);



double court_score(info f,detail det){
    //個体の練習スコアの総和.
    int j;
    double score = 0;
    for(j=0;j<DAY;j++){
        det->courts[j]->score = 0;
        det->courts[j]->score += court_score_sum(f,det->courts[j]);
        det->courts[j]->score += court_score_rank(f,det->courts[j]);
        score += det->courts[j]->score;
    }
    return score;
}

double court_score_rank(info f,court x){
    //各面内のランク差による点数
    court_rank data = f->score_data->c_rank;
    int acp = data->accept_number;int lim = data->limit_number;
    int ded1 = data->deduce_point1;int ded2 = data->deduce_point2;
    if(x->num_of_court[0]==0)return 0; //面が存在しなければ無視
    int i,max_i,min_i,dif;
    double score = 0;
    i = 0;min_i = 0;dif=0;
    while(min_i<x->sum_num){
        max_i = min_i + x->num_of_court[i]-1;
        dif = x->number[max_i]-x->number[min_i];  //面内の最大ランク差
        if(dif<=acp){
            score += data->add_point; //面内の最大ランク差が5以下なら500点
        }else if(dif<=lim){
            score += data->add_point + (dif - acp)*ded1; //ランクが離れるほど減点
        }else{
            score += data->add_point + (lim - acp)*ded1 + (dif - lim)*ded2;
        }
        i++;
        min_i = max_i +1;
    }
    return score;
}

double court_score_sum(info f,court x){
    //全体の練習人数による点数
    court_sum data = f->score_data->c_sum;
    double score = 0;
    double four_court = data->four; //４人面による加点
    double three_court = data->three; //３人面による減点
    double no_court = data->impossible; //面分け不能時の減点
    switch (x->sum_num) {
        case 0: case 4: case 8:
            score = four_court;    //4の倍数の時
            break;
        case 1: case 2: case 5:
            score = no_court; //面分け不能時
            break;
        case 3: case 7:
            score = three_court;   //3人面1つ
            break;
        case 6:
            score = 2*three_court;   //3人面2つ
            break;
        default:
            if(x->day%2 == 0){ //朝練は16人まで許容
                switch(x->sum_num){
                    case 12: case 16:
                        score = four_court;   //4の倍数の時
                    case 11: case 15:
                        score = three_court;   //3人面1つ
                        break;
                    case 10: case 14:
                        score = 2*three_court;   //3人面2つ
                        break;
                    case 9: case 13:
                        score = 3*three_court;   //3人面3つ
                        break;
                    default:
                        score = (x->sum_num-16)*no_court; //-溢れた人数*10000点
                        break;
                }
            }
            score = (x->sum_num-8)*no_court;  //-溢れた人数*10000点(夜)
            break;
    }
    return score;
}

double court_score_year(info f,court x){
    //面内の学年による評価.未設定
    double score=0;
    return score;
}


