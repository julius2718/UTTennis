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
double court_score_year(info f,court x);

double court_score(info f,detail det){
    //個体の練習スコアの総和.
    court c;
    int j;
    double score = 0;
    for(j=0;j<DAY;j++){
        c = det->courts[j];
        c->score = 0;
        c->score += court_score_sum(f,c);
        c->score += court_score_rank(f,c);
        c->score += court_score_year(f, c);
        score += c->score;
    }
    return score;
}

double court_score_rank(info f,court x){
    //各面内のランク差による点数
    court_rank data = f->score_data->c_rank;
    int acp = data->accept_number;int lim = data->limit_number;
    int ded1 = data->deduce_point1;int ded2 = data->deduce_point2;
    if(x->num_of_court[0]==0)return 0; //面が存在しなければ無視
    int i,min_i,max_i,dif;
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
    int i;
    if(x->num_of_court[0]==0){
        if(x->time<2 && x->sum_num>16){
            //-溢れた人数*10000点(朝昼)
            score += (x->sum_num-16) * data->impossible;
        }else if(x->time==2 && x->sum_num>8){
            //-溢れた人数*10000点(夜)
            score += (x->sum_num-8) * data->impossible;
        }else{
            score += data->impossible; //面分け不能時の減点
        }
    }else{
        i=0;
        while(x->num_of_court[i]>0){
            if(x->num_of_court[i]==3){
                score += data->three;
            }else if(x->num_of_court[i]==4){
                score += data->four;
            }
            i++;
        }
    }
    return score;
}

double court_score_year(info f,court x){
    //面内の学年による評価.未設定
    court_year data = f->score_data->c_year;
    double score=0;
    if(x->num_of_court[0]==0)return 0;
    int i,j,min_i,max_i,count;
    min_i=0;max_i=0;i=0;
    while(min_i<x->sum_num){
        max_i = min_i + x->num_of_court[i]-1;
        //ここに評価
        count=0;
        for(j=min_i;j<max_i;j++)count += abs(x->year[j+1]-x->year[j]);
        if(count==0){
            score += data->same_grade;  //全部同学年なら低評価
            if(x->year[min_i]==f->min_year)score += data->first_grade;  //一年生なら大幅減点
        }
        i++;
        min_i = max_i +1;
    }
    //全体に最高学年がいないと減点
    if(x->year[list_max(x->year, x->sum_num)]<f->max_year)score += data->final_grade;
    return score;
}


