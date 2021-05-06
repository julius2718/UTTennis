//
//  result.c
//  practice_member
//
//  Created by 長澤達也 on 2019/11/15.
//  Copyright © 2019 長澤達也. All rights reserved.
//

#include "result.h"

void print_result(info f,individual a);
void print_csv(info f,individual a);

void print_generation(info f,generation g){
    //各世代の最高評価値を出力
    printf("第%d世代が作成されました.最高評価個体を出力します.\n\n",g->gene);
    //print_individual(f,g->indi[g->max_indi]);
    printf("****** start printing result *****\n");
    print_csv(f,g->indi[g->max_indi]);sleep(1);
    printf("\nこの個体の点数の詳細です.\n");
    print_score(f,g->indi[g->max_indi]);sleep(1);
    printf("\nメーリス形式の出力です.\n");
    print_result(f,g->indi[g->max_indi]);
    printf("****** finish printing result *****\n");sleep(1);
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
    int day,time=0;   //day:曜日0~4,time:0~9or0~14
    char week[5][10] = {"月","火","水","木","金"};
    detail det = detail_of_individual(f,a);
    char** name = f->name;
    switch (DAY) {
        case 10:
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
            break;
        case 15:
            for(day=0;day<5;day++){
                printf("%s曜日\n",week[day]);
                if(det->courts[time]->sum_num != 0){
                    printf("07:00~10:00\n");
                    print_member(f,det->courts[time],name);
                }
                time++;
                if(det->courts[time]->sum_num != 0){
                    printf("10:00~13:00\n");
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
            break;
        default:
            printf("*****メーリス形式の出力が未対応の練習回数です*****\n");
            break;
    }
    free_detail(f,det);
}


void print_csv(info f,individual a){
    int i,j,x,y,z;
    FILE *fp;
    char filename[] = "practice_daylist.csv";fp = fopen(filename,"w");
    fprintf(fp,"ランク,氏名,学年");printf("ランク,氏名,学年");
    for(i=0;i<DAY;i++){
        fprintf(fp,",%s",DAY_LIST[i]);printf(",%s",DAY_LIST[i]);
    }
    fprintf(fp,"\n");printf("\n");
    for(i=0;i<f->people;i++){
        printf("%d,",f->rank[i]);fprintf(fp,"%d,",f->rank[i]);
        printf("%s,",f->name[i]);fprintf(fp,"%s,",f->name[i]);
        printf("%d",f->year[i]);fprintf(fp,"%d",f->year[i]);
        for(j=0;j<DAY;j++){
            x = f->list[i][j];  //練習できるか
            y = f->short_list[i][j] * 10;  //2限抜けか
            z = a->list[i][j] * 100;       //練習に入っているか
            switch (x+y+z) {
                case 0:
                    printf(",");fprintf(fp,",");
                    break;
                case 1:
                    printf(",◯");fprintf(fp,",◯");
                    break;
                case 11:
                    printf(",△");fprintf(fp,",△");
                    break;
                case 101:
                    printf(",●");fprintf(fp,",●");
                    break;
                case 111:
                    printf(",▲");fprintf(fp,",▲");
                    break;
                default:
                    printf("\nerror in [%d][%d]. x+y+z = %dです.\n",i,j,x+y+z);
                    break;
            }
        }
        printf("\n");fprintf(fp,"\n");
    }
    fclose(fp);
    printf("%s に結果を保存しました\n",filename);
}

