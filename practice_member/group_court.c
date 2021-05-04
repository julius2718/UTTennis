//
//  group_court.c
//  practice_member
//
//  Created by 長澤達也 on 2019/11/05.
//  Copyright © 2019 長澤達也. All rights reserved.
//


#include "group_court.h"


void select_group(court x);
court new_court(info f,individual a,int day);
player new_player(info f,individual a,court* courts,int number);


detail detail_of_individual(info f,individual a){
    //個体のデータを各日の練習面データに変換
    int i;
    detail det;
    NEW(det,1);NEW(det->courts,DAY);NEW(det->players,f->people);
    for(i=0;i<DAY;i++)det->courts[i] = new_court(f,a,i);
    for(i=0;i<f->people;i++)det->players[i] = new_player(f,a,det->courts,i);
    return det;
}
//各個体の日程別の面わけ情報を作成
court new_court(info f,individual a,int day){
    court x;
    NEW(x,1);
    int i,c = 0;
    for(i=0;i<f->people;i++){
        if(a->list[i][day]==1)c++;
    }
    NEW(x->number,c);
    NEW(x->year,c);
    NEW(x->num_of_court,5);
    x->day = day;//練習日程
    x->sum_num = c;//練習参加人数
    if((DAY==10 && day%2==0)||(DAY==15 && day%3==0)){
        x->time = 0;
    }else if(DAY==15 && day%3 ==1){
        x->time = 1;
    }else{
        x->time = 2;
    }
    c = 0;
    for(i=0;i<f->people;i++){
        if(a->list[i][day]==1){
            x->number[c] = i;
            x->year[c] = f->year[i];
            c++;
        }
    }
    if(c != x->sum_num){
        printf("error in new_court.\n 練習参加人数が一致しません.コードを確認してください\n");
    }
    select_group(x);//練習面の人数割りを決定
    x->score = -1;
    return x;
}

//各個体の選手別の練習情報を取得
player new_player(info f,individual a,court* courts,int number){
    player play;
    int i;
    int count = 0;
    NEW(play,1);
    play->number = number;
    play->count = f->count_prac[number];
    NEW(play->day_list,play->count);NEW(play->members,play->count);
    for(i=0;i<DAY;i++){
        if(a->list[number][i]==1){
            play->day_list[count] = i;
            play->members[count] = member_list(f,courts[i],number);
            count++;
        }
    }
    if(count != play->count){
        printf("error in new_player.\n 世代%d,個体番号%d,選手No.%dの練習登録数が一致しません.\n",a->gene,a->number,number);
    }
    play->score = -1;
    return play;
}

//numberが含まれる面のnumberを昇順に抽出.配列の最後尾は-1.
int* member_list(info f,court x,int number){
    int* member_list;
    NEW(member_list,MAX_PEOPLEinCOURT+1);
    int i,j,n,rank_in_member;
    if(x->num_of_court[0] == 0){
        member_list[0] = -1;    //練習面が作れない時は-1にする
        /*test用出力
        printf("rank=%dのday%dで参加する練習は成立しません\n",number,x->day);
        */
        return member_list;
    }
    i = 0;
    rank_in_member = -1;
    //numberのその練習内でのランクを取得
    while(i<x->sum_num){
        if(x->number[i] == number){
            rank_in_member = i;
            break;
        }
        i++;
    }
    if(rank_in_member == -1)printf("error in member_list.該当メンバ-%dがday%dで見つかりません.総人数は%dです\n",number,x->day,x->sum_num);
    i = 0;n = 0;
    //numberを含む3or4人面のランクをランク順に出力,末尾に-1を加える
    while(1){
        if(rank_in_member < n + x->num_of_court[i]){
            for(j=0;j<x->num_of_court[i];j++){
                member_list[j] = x->number[n+j];
            }
            member_list[x->num_of_court[i]] = -1;
            break;
        }
        n += x->num_of_court[i];
        i++;
    }
    /*test用出力
    i=0;
    printf("rank=%dのday%dで参加する練習のランク一覧:",number,x->day);
    while(member_list[i]!=-1){
        printf("%d ",member_list[i]);
        i++;
    }
    printf("\n");
     */
    //ここまでテスト用
    return member_list;
}

    
//参加メンバーに対する最適な面わけを探索.(x->num_of_courtの代入)
//面内の練習差が少なくなる様に面わけする
void select_group(court x){
    int i;
    int *score;NEW(score,N);
    int *num = x->number;
    if(x->time==2 && x->sum_num>8){
        x->num_of_court[0] = 0;
    }else{
    switch (x->sum_num) {
        //全体の人数ごとに面わけのパターンを考えランク差が少なくなるパターンを採用
        case 0: case 1: case 2: case 5:
            //面わけが不可能
            x->num_of_court[0] = 0;
            break;
        case 4: case 8: case 12: case 16:
            //4人面のみ
            for(i=0;i<x->sum_num/4;i++){
                x->num_of_court[i] = 4;
            }
            x->num_of_court[x->sum_num/4+1] = -1;
            break;
        case 3: case 6: case 9:
            //3人面のみ
            for(i=0;i<x->sum_num/3;i++){
                x->num_of_court[i] = 3;
            }
            x->num_of_court[x->sum_num/3+1] = -1;
            break;
        case 7:
            score[0] = num[4]-num[3]; //4-3で分けた場合
            score[1] = num[3]-num[2]; //3-4で分けた場合
            switch (list_max(score,2)) {
                case 0:
                    x->num_of_court[0] = 4;
                    x->num_of_court[1] = 3;
                    break;
                case 1:
                    x->num_of_court[0] = 3;
                    x->num_of_court[1] = 4;
                    break;
                default:
                    printf("error in switch case 7\n");
                    break;
            }
            x->num_of_court[2] = -1;
            break;
        case 10:
            score[0] = num[4]+num[7]-num[3]-num[6]; //4-3-3
            score[1] = num[3]+num[7]-num[2]-num[6]; //3-4-3
            score[2] = num[3]+num[6]-num[2]-num[5]; //3-3-4
            switch (list_max(score,3)) {
                case 0:
                    x->num_of_court[0] = 4;
                    x->num_of_court[1] = 3;
                    x->num_of_court[2] = 3;
                    break;
                case 1:
                    x->num_of_court[0] = 3;
                    x->num_of_court[1] = 4;
                    x->num_of_court[2] = 3;
                    break;
                case 2:
                    x->num_of_court[0] = 3;
                    x->num_of_court[1] = 3;
                    x->num_of_court[2] = 4;
                    break;
                default:
                    printf("error in switch case 10\n");
                    break;
            }
            x->num_of_court[3] = -1;
            break;
        case 11:
            score[0] = num[4]+num[8]-num[3]-num[7]; //4-4-3
            score[1] = num[4]+num[7]-num[3]-num[6]; //4-3-4
            score[2] = num[3]+num[7]-num[2]-num[6]; //3-4-4
            switch (list_max(score,3)) {
                case 0:
                    x->num_of_court[0] = 4;
                    x->num_of_court[1] = 4;
                    x->num_of_court[2] = 3;
                    break;
                case 1:
                    x->num_of_court[0] = 4;
                    x->num_of_court[1] = 3;
                    x->num_of_court[2] = 4;
                    break;
                case 2:
                    x->num_of_court[0] = 3;
                    x->num_of_court[1] = 4;
                    x->num_of_court[2] = 4;
                    break;
                default:
                    printf("error in switch case 11\n");
                    break;
            }
            x->num_of_court[3] = -1;
            break;
        case 13:
            score[0] = num[4]+num[7]+num[10]-num[3]-num[6]-num[9]; //4-3-3-3
            score[1] = num[3]+num[7]+num[10]-num[2]-num[6]-num[9]; //3-4-3-3
            score[2] = num[3]+num[6]+num[10]-num[2]-num[5]-num[9]; //3-3-4-3
            score[3] = num[3]+num[6]+num[9]-num[2]-num[5]-num[8]; //3-3-3-4
            switch (list_max(score,4)) {
                case 0:
                    x->num_of_court[0] = 4;
                    x->num_of_court[1] = 3;
                    x->num_of_court[2] = 3;
                    x->num_of_court[3] = 3;
                    break;
                case 1:
                    x->num_of_court[0] = 3;
                    x->num_of_court[1] = 4;
                    x->num_of_court[2] = 3;
                    x->num_of_court[3] = 3;
                    break;
                case 2:
                    x->num_of_court[0] = 3;
                    x->num_of_court[1] = 3;
                    x->num_of_court[2] = 4;
                    x->num_of_court[3] = 3;
                    break;
                case 3:
                    x->num_of_court[0] = 3;
                    x->num_of_court[1] = 3;
                    x->num_of_court[2] = 3;
                    x->num_of_court[3] = 4;
                    break;
                default:
                    printf("error in switch case 13\n");
                    break;
            }
            x->num_of_court[4] = -1;
            break;
        case 14:
            score[0] = num[4]+num[8]+num[11]-num[3]-num[7]-num[10]; //4-4-3-3
            score[1] = num[4]+num[7]+num[11]-num[3]-num[6]-num[10]; //4-3-4-3
            score[2] = num[4]+num[7]+num[10]-num[3]-num[6]-num[9]; //4-3-3-4
            score[3] = num[3]+num[7]+num[11]-num[2]-num[6]-num[10]; //3-4-4-3
            score[4] = num[3]+num[7]+num[10]-num[2]-num[6]-num[9]; //3-4-3-4
            score[5] = num[3]+num[6]+num[10]-num[2]-num[5]-num[9]; //3-3-4-4
            switch (list_max(score,6)) {
                case 0:
                    x->num_of_court[0] = 4;
                    x->num_of_court[1] = 4;
                    x->num_of_court[2] = 3;
                    x->num_of_court[3] = 3;
                    break;
                case 1:
                    x->num_of_court[0] = 4;
                    x->num_of_court[1] = 3;
                    x->num_of_court[2] = 4;
                    x->num_of_court[3] = 3;
                    break;
                case 2:
                    x->num_of_court[0] = 4;
                    x->num_of_court[1] = 3;
                    x->num_of_court[2] = 3;
                    x->num_of_court[3] = 4;
                    break;
                case 3:
                    x->num_of_court[0] = 3;
                    x->num_of_court[1] = 4;
                    x->num_of_court[2] = 4;
                    x->num_of_court[3] = 3;
                    break;
                case 4:
                    x->num_of_court[0] = 3;
                    x->num_of_court[1] = 4;
                    x->num_of_court[2] = 3;
                    x->num_of_court[3] = 4;
                    break;
                case 5:
                    x->num_of_court[0] = 3;
                    x->num_of_court[1] = 3;
                    x->num_of_court[2] = 4;
                    x->num_of_court[3] = 4;
                    break;
                default:
                    printf("error in switch case 14\n");
                    break;
            }
            x->num_of_court[4] = -1;
            break;
        case 15:
            score[0] = num[4]+num[8]+num[12]-num[3]-num[7]-num[11]; //4-4-4-3
            score[1] = num[4]+num[8]+num[11]-num[3]-num[7]-num[10]; //4-4-3-4
            score[2] = num[4]+num[7]+num[11]-num[3]-num[6]-num[10]; //4-3-4-4
            score[3] = num[3]+num[7]+num[11]-num[2]-num[6]-num[10]; //3-4-4-4
            switch (list_max(score,4)) {
                case 0:
                    x->num_of_court[0] = 4;
                    x->num_of_court[1] = 4;
                    x->num_of_court[2] = 4;
                    x->num_of_court[3] = 3;
                    break;
                case 1:
                    x->num_of_court[0] = 4;
                    x->num_of_court[1] = 4;
                    x->num_of_court[2] = 3;
                    x->num_of_court[3] = 4;
                    break;
                case 2:
                    x->num_of_court[0] = 4;
                    x->num_of_court[1] = 3;
                    x->num_of_court[2] = 4;
                    x->num_of_court[3] = 4;
                    break;
                case 3:
                    x->num_of_court[0] = 3;
                    x->num_of_court[1] = 4;
                    x->num_of_court[2] = 4;
                    x->num_of_court[3] = 4;
                    break;
                default:
                    printf("error in switch case 14\n");
                break;
            }
            x->num_of_court[4] = -1;
        default:
            x->num_of_court[0] = 0;
            break;
    }
    }
    SAFE_FREE(score);
}




