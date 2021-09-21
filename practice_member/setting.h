//
//  setting.h
//  practice_member
//
//  Created by 長澤達也 on 2019/11/16.
//  Copyright © 2019 長澤達也. All rights reserved.
/*役割(set_score)
 scoringでの評価値関数のパラメータ設定
 */
/*役割(info_build)
 入力データを利用可能な形infoに再形成
*/

#ifndef setting_h
#define setting_h

#include <stdio.h>
#include <stdlib.h>
#include "load_file.h"

typedef struct{
    //court_score_rankでの点数決定係数
    int add_point;  //ランク差が規定内の時の最大加点
    int deduce_point;  //ランク差がより大きい時の減点比率
    int accept_number;  //最大加点を与えるランク範囲
    int limit_number;   //減点比率の臨界点
}*court_rank;

typedef struct{
    //court_score_sumでの点数決定係数
    int impossible; //面分け不能時の減点係数
    int three;  //3人面での加減点
    int four;   //4人面での加点
}*court_sum;

typedef struct{
    //court_score_yearでの点数決定係数
    int same_grade; //全員同じ学年の練習での減点
    int first_grade;  //最低学年のみの練習での追加減点
    int final_grade;   //全体で最高学年不在時の減点
}*court_year;

typedef struct{
    int same_day;   //同一日の練習での減点
    int row_day;    //連日の練習での減点(夜->朝を除く)
    int night_to_morning;   //連続夜->朝での減点
    int two_morning;    //2回朝練
    int two_noon;   //2回昼練
    int two_night;  //2回夜練
    int mon_morning;    //月朝による減点
    int fri_night;  //金夜による追加減点
}*personal_interval;

typedef struct{
    int not_consider;   //考慮しない最大ランク
    int up_rank; //ボーナスが入るランク差
    int up_point;   //up_rank以上上とできるときのボーナス
    int down_point; //上の人とできない場合の減点
}*personal_equality;

typedef struct{
    int single_short;   //1回二限抜けする場合
    int double_short;   //2回二限抜けする場合
}*personal_short_prac;


typedef struct{
    court_rank c_rank;
    court_sum c_sum;
    court_year c_year;
    personal_interval p_inter;
    personal_equality p_equ;
    personal_short_prac p_short;
}*score_data;   //scoringにおける評価値関数のパラメータ

typedef struct{
    //一覧データはランクの昇順に格納される
    int people; //対象人数
    int **list; //参加可能な練習日程.0で不可,1で可能,-1で固定で入る
    int **short_list;   //参加可能なうち2限抜けする練習日程
    int *count_prac;    //練習希望回数.基本は2.(今後入力形式に合わせて変化させる)
    int *count_can; //各人の固定以外の練習可能回数
    int *count_fix; //各人の固定で入る練習回数
    int *year; //各人の学年
    int min_year;   //全体の最低学年
    int max_year;   //全体の最高学年
    int *rank; //各人のランク
    char **name; //各人の氏名
    score_data score_data;
}*info;

info info_build(int people,personal* plist);
int list_max(int* a,int n);

#endif /* setting_h */
