//
//  result_scoring.c
//  practice_member
//
//  Created by 長澤達也 on 2021/05/03.
//  Copyright © 2021 長澤達也. All rights reserved.
//

#include "result_scoring.h"

double calc_interval_(int d1,int d2,int people,int* out,personal_interval data);
double calc_2period(info f,individual a,int people);
void print_score_court_sum(court_sum data,detail det);
void print_score_court_rank(info f,detail det);
void print_score_court_year(info f,detail det);
void print_score_court(info f,detail det);
void print_score_personal_interval(info f,detail det);
void print_score_personal_equality(info f,detail det);
void print_score_personal_2period(info f,individual a);
void print_score_personal(info f,detail det,individual a);

void print_score(info f,individual a){
    detail det = detail_of_individual(f,a);
    //全体のスコア
    printf("この個体の評価値は%.1fです\n",a->score);
    print_score_court(f,det);
    print_score_personal(f,det,a);
    free_detail(f,det);
}


void print_score_court(info f,detail det){
    court c;
    double score = 0;
    double min = 100000;
    int i;
    
    for(i=0;i<DAY;i++){
        c = det->courts[i];
        c->score = 0;
        c->score += court_score_sum(f,c);
        c->score += court_score_rank(f,c);
        c->score += court_score_year(f,c);
        if(c->score<min) min = c->score;
        score += c->score;
    }
    printf("練習スコア: %.1f\n",score);
    printf("    最低点は ");
    for(i=0;i<DAY;i++){
        if(det->courts[i]->score == min) printf("%s ",DAY_LIST[i]);
    }
    printf("で %.1f点\n",min);
    printf("練習スコアの詳細\n");
    print_score_court_sum(f->score_data->c_sum,det);
    print_score_court_rank(f,det);
    print_score_court_year(f,det);

}

void print_score_personal(info f,detail det,individual a){
    player me;
    double score = 0;
    double min = 100000;
    int i;
    
    for(i=0;i<f->people;i++){
        me = det->players[i];
        me->score = 0;
        me->score += personal_score_interval(f,me);
        me->score += personal_score_equality(f,me);
        me->score += calc_2period(f,a,i);
        if(me->score<min) min = me->score;
        score += me->score;
    }
    printf("個人スコア: %.1f\n",score);
    printf("    最低点の選手は ");
    for(i=0;i<f->people;i++){
        if(det->players[i]->score == min) printf("%s ",f->name[i]);
    }
    printf("で %.1f点\n",min);
    printf("個人スコアの詳細\n");
    print_score_personal_interval(f,det);
    print_score_personal_equality(f,det);
    print_score_personal_2period(f,a);

}

void print_score_court_sum(court_sum data,detail det){
    double score = 0;
    int i,j,tmp;
    int imp[DAY+1];
    int three = 0;
    int four = 0;
    imp[0] = 0;
    for(i=0;i<DAY;i++){
        j = 0;
        tmp = det->courts[i]->num_of_court[j];
        if(tmp == 0){
            if(det->courts[i]->sum_num==0)continue;
            imp[0]++;
            imp[i+1]=1;
            score += data->impossible;
        }else{
            imp[i+1]=0;
            while(tmp>0){
                if(tmp == 3){
                    three++;
                    score += data->three;
                }else if(tmp == 4){
                    four++;
                    score += data->four;
                }
                j++;
                tmp = det->courts[i]->num_of_court[j];
            }
        }
    }
    printf("    各練習の人数による点数: %.1f点\n",score);
    printf("        組分け不能な練習は");
    if(imp[0]==0){
        printf("ありません\n");
    }else{
        for(i=0;i<DAY;i++){
            if(imp[i+1]==1)printf(" %s",DAY_LIST[i]);
        }
        printf(" の%d回\n",imp[0]);
    }
    printf("        3人面の数: %d回 * %d点\n",three,data->three);
    printf("        4人面の数: %d回 * %d点\n",four,data->four);
}

void print_score_court_rank(info f,detail det){
    double score = 0;
    double min = 100000;
    double scores[DAY];
    int i;
    for(i=0;i<DAY;i++){
        scores[i] = court_score_rank(f, det->courts[i]);
        score += scores[i];
        if(scores[i] < min) min = scores[i];
    }
    printf("    各面のランク差による点数: %.1f点\n",score);
    printf("        最低点は ");
    for(i=0;i<DAY;i++){
        if(scores[i] == min) printf("%s ",DAY_LIST[i]);
    }
    printf("で %.1f点\n",min);
}

void print_score_court_year(info f,detail det){
    double score = 0;
    double min = 100000;
    double scores[DAY];
    int i;
    for(i=0;i<DAY;i++){
        scores[i] = court_score_year(f, det->courts[i]);
        score += scores[i];
        if(scores[i] < min) min = scores[i];
    }
    printf("    各練習の学年構成による点数: %.1f点\n",score);
    printf("        最低点は ");
    for(i=0;i<DAY;i++){
        if(scores[i] == min) printf("%s ",DAY_LIST[i]);
    }
    printf("で %.1f点\n",min);
}


void print_score_personal_interval(info f,detail det){
    player me;
    double score = 0;
    int i,j;
    int c_same = 0;
    int c_ntom = 0;
    int c_row = 0;
    int out[f->people];//1:同日練,2:夜->朝練,3:連日練.
    //3回練で同日練+連日練みたいなレアケースでは正しく表記されないが計算はされている.
    for(i=0;i<f->people;i++){
        me = det->players[i];
        out[i] = 0;
        if(me->count<2)continue;
        for(j=0;j<me->count-1;j++){
            score += calc_interval_(me->day_list[j], me->day_list[j+1], i, out, f->score_data->p_inter);
        }
        switch (out[i]) {
            case 1:
                c_same++;
                break;
            case 2:
                c_ntom++;
                break;
            case 3:
                c_row++;
                break;
            default:
                break;
        }
    }
    printf("    各選手の練習間隔についての点数: %.1f\n",score);
    printf("        同日に複数練習ある人は");
    if(c_same == 0){
        printf("いません\n");
    }else{
        for(i=0;i<f->people;i++){
            if(out[i] == 1) printf(" %s",f->name[i]);
        }
        printf(" です\n");
    }
    printf("        連日夜->朝の練習がある人は");
    if(c_ntom == 0){
        printf("いません\n");
    }else{
        for(i=0;i<f->people;i++){
            if(out[i] == 2) printf(" %s",f->name[i]);
        }
        printf(" です\n");
    }
    printf("        その他連日の練習がある人は");
    if(c_row == 0){
        printf("いません\n");
    }else{
        for(i=0;i<f->people;i++){
            if(out[i] == 3) printf(" %s",f->name[i]);
        }
        printf(" です\n");
    }
}


void print_score_personal_equality(info f,detail det){
    double score = 0;
    double scores[f->people];
    int minus = 0;
    int nc = f->score_data->p_equ->not_consider;
    int i;
    for(i=0;i<f->people;i++){
        scores[i] = personal_score_equality(f,det->players[i]);
        score += scores[i];
        if(scores[i]<0){
            minus++;
        }
    }
    printf("    各選手の練習相手についての点数: %.1f\n",score);
    printf("        %d位以下で上のランクの人と練習できない人は",f->rank[nc]);
    if(minus == 0){
        printf("いません\n");
    }else{
        for(i=0;i<f->people;i++){
            if(scores[i] < 0) printf(" %s",f->name[i]);
        }
        printf(" です\n");
    }
}


void print_score_personal_2period(info f,individual a){
    personal_short_prac data = f->score_data->p_short;
    double score = 0;
    int flag[f->people];
    int i,j,c;
    for(i=0;i<f->people;i++){
        c = 0;
        for(j=0;j<DAY;j++){
            c += a->list[i][j]*f->short_list[i][j];
        }
        if(c==1){
            score += data->single_short;
        }else if(c>1){
            score += (c-1)*data->double_short;
        }
        if(c == f->count_prac[i]){
            flag[i] = 1;
        }else{
            flag[i] = 0;
        }
    }
    printf("    各選手の二限抜けについての点数: %.1f\n",score);
    printf("        全ての練習で二限抜けする人は");
    c=0;
    for(i=0;i<f->people;i++){
        if(flag[i]==1){
            printf(" %s",f->name[i]);
            c++;
        }
    }
    if(c>0){
        printf(" です\n");
    }else{
        printf("いません\n");
    }
    
}

double calc_interval_(int d1,int d2,int people,int* out,personal_interval data){
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
        out[people] = 1;   //同日練フラグを建てる
    }else if(x2-x1 == 1){
        if(d2-d1 == 1){
            ans = data->night_to_morning;  //連続夜->朝練習
            out[people] = 2;  //夜->朝練フラグを建てる
        }else{
            ans = data->row_day;   //連日の練習(夜->朝を除く)
            out[people] = 3;   //連日練フラグを建てる
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

double calc_2period(info f,individual a,int people){
    personal_short_prac data = f->score_data->p_short;
    double score = 0;
    int j,c;
    c = 0;
    for(j=0;j<DAY;j++){
        c += a->list[people][j]*f->short_list[people][j];
        //練習箇所が2限抜けだったらカウント
    }
    if(c==1){
        score += data->single_short;
    }else if(c>1){
        score += (c-1)*data->double_short;
    }
    return score;
}
