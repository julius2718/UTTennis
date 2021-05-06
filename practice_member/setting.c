//
//  setting.c
//  practice_member
//
//  Created by 長澤達也 on 2019/11/16.
//  Copyright © 2019 長澤達也. All rights reserved.
//

#include "setting.h"

//*******ここから:scoringのパラメータ設定********

court_rank set_court_rank(void){
    //各面内のランク差による評価.ランクの最大値-最小値が小さいほど高評価.
    //比率を大きくするとランク差が小さい組み分けが出やすくなる.
    //計算式はcourt_score.c参照.
    court_rank c_rank;
    NEW(c_rank,1);
    c_rank->accept_number = 5;  //最大加点を与えるランク範囲n1
    c_rank->add_point = 600;    //ランク差が規定内の時の最大加点max
    c_rank->deduce_point1 = -200;   //ランク差がある時の減点比率d1
    c_rank->deduce_point2 = -1000;   //ランク差がより大きい時の減点比率d2
    c_rank->limit_number = 10;   //減点比率の境界点n2
    return c_rank;
}

court_sum set_court_sum(void){
    //各練習の人数による評価.面わけ不能時の点数はマイナスに振り切った点数.4人面が多いと高評価
    //3人面の減点比率が大きいと,4人面が多い組み分けが出やすくなる
    court_sum c_sum;
    NEW(c_sum,1);
    c_sum->impossible = -10000; //面分け不能時の減点係数
    c_sum->three = -200;    //3人面での加減点
    c_sum->four = 100;  //4人面での加点
    return c_sum;
}

court_year set_court_year(void){
    //各練習の学年による評価.
    //各面で同学年のみだと低評価。特に最低学年のみの時は大幅減点
    //4面全体の中に最高学年がいないと減点
    court_year c_year;
    NEW(c_year,1);
    c_year->same_grade = -200; //全員同じ学年の練習での減点
    c_year->first_grade = -5000;    //最低学年のみの練習での追加減点
    c_year->final_grade = -300;  //全体で最高学年不在時の減点
    return c_year;
}

personal_interval set_personal_interval(void){
    //各人の練習間隔による評価.
    //同日の練習や夜->朝は振り切った減点.
    //連日の練習も多少減点.重要度は低い
    //朝練連続or夜練連続で減点.重要度は低い
    personal_interval p_interval;
    NEW(p_interval,1);
    p_interval->same_day = -10000;  //同一日の練習による減点
    p_interval->row_day = -100; //連日の練習による減点(夜->朝を除く)
    p_interval->night_to_morning = -5000;   //連続夜->朝での減点
    p_interval->two_morning = 0;    //2回朝練
    p_interval->two_noon = 0;   //2回昼練
    p_interval->two_night = 0;  //2回夜練
    p_interval->mon_morning = -50;  //月朝練習による追加減点
    p_interval->fri_night = -50;  //金夜練習による追加減点
    return p_interval;
}

personal_equality set_personal_equality(void){
    //各人が上の人とできるかによる評価.
    //比率を大きくすると,下の人としか練習できない人が減る.
    personal_equality p_equal;
    NEW(p_equal,1);
    p_equal->up_rank = 5;   //ボーナスが入るランク差
    p_equal->up_point = 100;    //up_rank以上上とできるときのボーナス
    p_equal->down_point = -300; //上の人とできない場合の減点
    p_equal->not_consider = 1;  //考慮しない最大ランク
    return p_equal;
}

personal_short_prac set_personal_short_prac(void){
    //各人が2限抜けをするかによる評価.
    //比率を大きくすると,2限抜けの日程には入りづらくなる
    personal_short_prac p_short;
    NEW(p_short,1);
    p_short->single_short = -100;   //1回二限抜けする場合
    p_short->double_short = -300;   //2回二限抜けする場合
    return p_short;
}

//*******ここまで:scoringのパラメータ設定********





score_data set_score(void);
void separate_list(info f,personal* plist);
int** make_daylist(int people,personal* plist);
char** make_namelist(int people,personal* plist);
int print_info(info f);

info info_build(int people,personal* plist){
    //初期値や入力データを保持するinfoの設定
    //f->count_pracは未使用
    int i,j,p,c,cf;p=0;
    int min_year,max_year;min_year=100;max_year=0;
    info f;
    NEW(f,1);
    f->people = people;
    separate_list(f,plist);
    f->name = make_namelist(people,plist);
    f->score_data = set_score();
    NEW(f->count_prac,f->people);
    NEW(f->count_can,f->people);
    NEW(f->count_fix,f->people);
    NEW(f->year,f->people);
    NEW(f->rank,f->people);
    for(i=0;i<f->people;i++){
        c = 0;
        cf= 0;
        for(j=0;j<DAY;j++){
            if(f->list[i][j] == 1)c++;
            if(f->list[i][j] == -1)cf++;
        }
        f->count_prac[i] = 2;   //今後3回練にも対応予定.
        f->count_can[i] = c;
        f->count_fix[i] = cf;
        while(plist[p]==NULL)p++;
        f->year[i] = plist[p]->year;
        if(f->year[i] < min_year)min_year = f->year[i];
        if(f->year[i] > max_year)max_year = f->year[i];
        f->rank[i] = plist[p]->rank;

        p++;
    }
    f->min_year = min_year;
    f->max_year = max_year;
    //print_info(f);    //test用出力
    return f;
}

score_data set_score(void){
    score_data data;
    NEW(data,1);
    data->c_rank = set_court_rank();
    data->c_sum = set_court_sum();
    data->c_year = set_court_year();
    data->p_inter = set_personal_interval();
    data->p_equ = set_personal_equality();
    data->p_short = set_personal_short_prac();
    return data;
}

void separate_list(info f,personal* plist){
    //入力データを分解してinfoに格納する
    //f->listは練習に入れない/入れる/固定で入るの3通り
    //f->short_listは練習に入るが2限抜けの時.
    int i,j,p;p=0;
    NEW(f->list,f->people);NEW(f->short_list,f->people);
    for(i=0;i<f->people;i++){
        while(plist[p]==NULL){
            p++;    //ランクの飛びを考慮
        }
        NEW(f->list[i],DAY);NEW(f->short_list[i],DAY);
        for(j=0;j<DAY;j++){
            switch (plist[p]->list[j]) {
                case 0://練習に入れない
                    f->list[i][j] = 0;
                    f->short_list[i][j] = 0;
                    break;
                case 1://練習に入れる
                    f->list[i][j] = 1;
                    f->short_list[i][j] = 0;
                    break;
                case 2://練習に入れるが2限抜け
                    f->list[i][j] = 1;
                    f->short_list[i][j] = 1;
                    break;
                case -1://固定で入る練習
                    f->list[i][j] = -1;
                    f->short_list[i][j] = 0;
                    break;
                default://エラーは練習に入れない扱いで処理
                    printf("error in separate_list.\n");
                    printf(" 想定されない値がlistにあります.入力データを確認してください.\n");
                    f->list[i][j] = 0;
                    f->short_list[i][j] = 0;
                    break;
            }
        }
        p++;
    }
}

char** make_namelist(int people,personal* plist){
    //名前情報をplistからinfoへ値渡し
    char** list;
    int i,p;
    NEW(list,people);
    i=0;p=0;
    while(i<people){
        if(plist[p]!=NULL){
            NEW(list[i],N)
            strcpy(list[i],plist[p]->name);
            i++;
        }
        p++;
    }
    return list;
}

int list_max(int* a,int n){
    //最大値をあたえる要素番号を返す.n:要素数
    int ans = 0;
    int i;
    for(i=1;i<n;i++){
        if(a[ans]<a[i])ans = i;
    }
    return ans;
}

