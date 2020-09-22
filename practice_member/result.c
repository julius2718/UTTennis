//
//  result.c
//  practice_member
//
//  Created by 長澤達也 on 2019/11/15.
//  Copyright © 2019 長澤達也. All rights reserved.
//

#include "result.h"

void print_result(info f,individual a);
void print_score(info f,individual a);
void print_csv(info f,individual a);

void print_generation(info f,generation g){
    //各世代の最高評価値を出力
    printf("第%d世代が作成されました.最高評価個体を出力します.\n\n",g->gene);
    //print_individual(f,g->indi[g->max_indi]);
    print_csv(f,g->indi[g->max_indi]);
    printf("\nこの個体の点数の詳細です.\n");
    print_score(f,g->indi[g->max_indi]);
    printf("\nメーリス形式の出力です.\n");
    print_result(f,g->indi[g->max_indi]);
}

void print_member(info f,court x,char** name){
    int i,c_num,c_num_;
    c_num = 0;  //コート番号
    c_num_ = 1;  //コート人数の一時変数
    for(i=0;i<x->sum_num;i++){
        if(c_num_ == 1)printf("[");
        printf("%s",name[x->number[i]]);
        if(f->short_list[x->number[i]][x->day]==1)printf("!");//iがdayで二限抜けなら!をつける
        if(c_num_ == x->num_of_court[c_num]){
            //iがその面の最後の人の場合
            printf("]\n");
            c_num++;
            c_num_ =1;
        }else{
            //iがその面の最後でない場合
            printf(",");
            c_num_++;
        }
    }
}

void print_result(info f,individual a){
    //メーリスに流す形式で出力
    int day,time=0;   //day:曜日0~4,time:0~9
    char week[5][10] = {"月","火","水","木","金"};
    detail det = detail_of_individual(f,a);
    char** name = f->name;
    for(day=0;day<5;day++){
        printf("%s曜日\n",week[day]);
        if(det->courts[time]->sum_num != 0){
            printf("07:00~10:00\n");
            print_member(f,det->courts[time],name);
        }
        time++;
        if(det->courts[time]->sum_num != 0){
            printf("18:00~21:00\n");
            print_member(f,det->courts[time],name);
        }
        printf("\n");
        time++;
    }
    free_detail(f,det);
}


void print_csv(info f,individual a){
    int i,j,x,y,z;
    printf("ランク,名前,月朝,月夜,火朝,火夜,水朝,水夜,木朝,木夜,金朝,金夜\n");
    for(i=0;i<f->people;i++){
        printf("%d,",f->rank[i]);
        printf("%s,",f->name[i]);
        for(j=0;j<DAY;j++){
            x = f->list[i][j];  //練習できるか
            y = f->short_list[i][j] * 10;  //2限抜けか
            z = a->list[i][j] * 100;       //練習に入っているか
            switch (x+y+z) {
                case 0:
                    printf(",");
                    break;
                case 1:
                    printf("◯,");
                    break;
                case 11:
                    printf("△,");
                    break;
                case 101:
                    printf("●,");
                    break;
                case 111:
                    printf("▲,");
                    break;
                default:
                    printf("\nerror in [%d][%d]. x+y+z = %dです.\n",i,j,x+y+z);
                    break;
            }
        }
        printf("\n");
    }
}



void print_score(info f,individual a){
    //点数の詳細を出力
    score_data data = f->score_data;
    detail det = detail_of_individual(f,a);
    int i,three,four,impo;
    double r_s; //rank_scoreの一時変数
    double rank_score = 0;
    double min_rank_score = 100000;
    int min_r_s_day = -1; //rankscoreの最も低い日
    double *personal_score_interval_list,*personal_score_equality_list;
    double s_prac_score;
    int *n,*m,*l;
    char day[10][10] = {"月朝","月夜","火朝","火夜","水朝","水夜","木朝","木夜","金朝","金夜"};
    three = 0;  //3人面の数
    four = 0;   //４人面の数
    impo = 0;   //コート不成立の数
    NEW(n,f->people+1);NEW(m,f->people+1);NEW(l,f->people+1)    //n:1日2回練習の人.m:夜->朝の連続の人.[0]が人数,[1]以降がそのrank
    NEW(personal_score_interval_list,f->people+1);   //[f->people+1]は合計点
    NEW(personal_score_equality_list,f->people+1);
    //面の人数による点数
    for(i=0;i<DAY;i++){
        if(det->courts[i]->num_of_court[0]==0 &&det->courts[i]->sum_num != 0){
            impo++;
        }else{
            switch (det->courts[i]->sum_num) {
                case 9:case 13:
                    three++;
                case 6:case 10:case 14:
                    three++;
                case 3:case 7:case 11:case 15:
                    three++;
                case 0:case 4:case 8:case 12:case 16:
                    break;
                default:
                    printf("error in print_score of court_score_sum 3");
                    break;
            }
            switch (det->courts[i]->sum_num) {
                case 16:
                    four++;
                case 12:case 15:
                    four++;
                case 8:case 11:case 14:
                    four++;
                case 4:case 7:case 10:case 13:
                    four++;
                case 0:case 3:case 6:case 9:
                break;
                default:
                    printf("error in print_score of court_score_sum 4");
                    break;
            }
        }
    }
    //面内のランク差による点数
    for(i=0;i<DAY;i++){
        r_s = court_score_rank(f,det->courts[i]);
        rank_score += r_s;
        if(r_s < min_rank_score){
            min_rank_score = r_s;
            min_r_s_day = i;
        }
    }
    //personal_scoreの点数リスト
    n[0]=0;m[0]=0;l[0]=0;personal_score_interval_list[f->people]=0;personal_score_equality_list[f->people]=0;
    for(i=0;i<f->people;i++){
        personal_score_interval_list[i] = personal_score_interval(f,det->players[i]);
        if(personal_score_interval_list[i] == data->p_inter->same_day){
            n[0]++;
            n[n[0]] = i;
        }else if(personal_score_interval_list[i] == data->p_inter->night_to_morning){
            m[0]++;
            m[m[0]] = i;
        }else{
            personal_score_interval_list[f->people] += personal_score_interval_list[i];
        }
        personal_score_equality_list[i] = personal_score_equality(f,det->players[i]);
        if(personal_score_equality_list[i]< 0){
            l[0] ++;
            l[l[0]] = i;
        }
        personal_score_equality_list[f->people] += personal_score_equality_list[i];
    }
    s_prac_score = personal_score_2period(f,a);
    /*求める内容
     練習スコア->court_score(f,court*)
     *組み分け不能数impo->court*[i]のnum_of_courtで確認
     *面数three,four->court*[i]のsum_numで確認
     *ランク差による点数rank_score->court*[i]のcourt_score_rank(f,court)の合計
     *上記の最低点min_rank_score->上記と同時に計算
     個人スコア->parsonal_score(f,a,det)
     *練習時間による点数n,m,l,personal_score_interval_list->inteval_score(f,det)による計算
     *練習面による点数->equality scoreによる計算
    */
    
    //出力内容
    //全体のスコア
    printf("この個体の評価値は%.1fです\n",a->score);
    //練習スコア
    printf("練習スコア: %.1f\n",court_score(f,det));
    printf("練習スコアの詳細\n");
    printf("    練習面が組み分け不可能な日数: %d * %d点\n",impo,data->c_sum->impossible);
    printf("        3人面の数: %d * %d点\n",three,data->c_sum->three);
    printf("        4人面の数: %d * %d点\n",four,data->c_sum->four);
    printf("    面内のランク差による点数: %.1f点\n",rank_score);
    printf("        最低点は %.1f点でその練習は%s\n",min_rank_score,day[min_r_s_day]);
    //個人スコア
    printf("個人スコア: %.1f\n",personal_score(f,a,det));
    printf("個人スコアの詳細\n");
    printf("    1日2回の練習の人数: %d人 * %d点\n",n[0],data->p_inter->same_day);
    if(n[0] > 0){
        printf("        その人の名前は:");
        for(i=1;i<=n[0];i++)printf("%s ",f->name[n[i]]);
        printf("\n");
    }
    printf("    夜->朝の連日練習の人数: %d人 * %d点\n",m[0],data->p_inter->night_to_morning);
    if(m[0] > 0){
        printf("        その人の名前は:");
        for(i=1;i<=m[0];i++)printf("%s ",f->name[m[i]]);
        printf("\n");
    }
    printf("    それ以外の人の練習間隔による点数は, %.1f点\n",personal_score_interval_list[f->people]);
    printf("    上のランクと練習できるかによる点数は, %.1f点\n",personal_score_equality_list[f->people]);
    printf("        上の人と練習できない人数は%d人\n",l[0]);
    if(l[0] > 0){
        printf("            その人の名前は:");
        for(i=1;i<=l[0];i++)printf("%s ",f->name[l[i]]);
        printf("\n");
    }
    printf("    2限抜けする人数による点数は, %.1f点\n",s_prac_score);
    SAFE_FREE(n);SAFE_FREE(m);SAFE_FREE(l);
    SAFE_FREE(personal_score_interval_list);SAFE_FREE(personal_score_equality_list);
    free_detail(f,det);
}
