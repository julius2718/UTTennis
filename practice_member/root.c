//
//  root.c
//  practice_member
//
//  Created by 長澤達也 on 2020/03/25.
//  Copyright © 2020 長澤達也. All rights reserved.

/*
 **練習日程組担当者へ**
 これは希望日程を元に,練習日程を組むプログラムです。簡単に仕組みを説明します。読める人はプログラムを読んで理解してください。
 プログラムの主な役割は以下の通りです。
    (1)希望日程をcsvファイルから入力として受け取る。(フォーマットは引き継ぎファイル参照)
    (2)希望日程の元で組まれた練習日程の"良さ"に点数をつけて評価する。
    (3)評価関数をもちいて遺伝的アルゴリズムで,"良い"練習日程を生成する。(遺伝的アルゴリズムはググってください)
    (4)出来た練習日程をいくつかの形式で出力する。
 プログラムを分からなくても,csvファイルのフォーマットさえ守れていれば,練習日程を組むことができます。
 分かる人は以下をいじることで,より適したプログラムに改良できます。
    <1>評価関数に新要素を追加して,複雑な条件を考慮する(難)
    <2>評価関数のパラメータを変更して,"良い練習"の基準を変える(易)
    <3>遺伝的アルゴリズムのパラメータを変更して,計算速度や性能を向上させる。(普通)
 */

//******遺伝アルゴリズムのパラメータはroot.hで変更可能******
//******評価関数のパラメータはsetting.cで変更可能******
/*
プログラム構造
 (1)入力,データの構成
 load_file
    |__test
    |__setting
        |__make_list
            |__print
                |_group_court__(2)

 (2)評価関数
-group_court
    |__free
        |__court_score____
        |__personal_score_|
                          |__scoring__(3)
 (3)遺伝的アルゴリズム,結果出力
 -scoring
          |__result_scoring__result__
          |__first_generation________|
          |__next_generation_________|
                                       |_genetic_algorithm

 */

/*
構造体一覧
 personal:選手の入力情報(load_file.h)
    info_buildでinfoに情報を引き継いだらfree.
 info:入力情報と評価関数のパラメタ(setting.h)
    -score_data:評価関数のパラメタ(setting.h)
        -court_rank         :面ごと>ランク差の評価パラメタ(setting.h)
        -court_sum          :面ごと>人数による評価パラメタ(setting.h)
        -personal_interval  :人ごと>練習間隔による評価パラメタ(setting.h)
        -personal_equality  :人ごと>練習メンバによる評価パラメタ(setting.h)
        -personal_short_prac:人ごと>2限抜けによる評価パラメタ(setting.h)
 generation:世代情報(make_list.h)
    -individual:個体情報(練習日程と評価値)(make_list.h)
 detail:individualを評価しやすいように変換した構造体.以下の2つの配列からなる(group_court.h)
    -court:ある個体でのある日の練習情報(group_court.h)
    -player:ある個体でのある人の練習情報(group_court.h)

 */
/*
 genetic_algorithmの流れ
    (1)ファイルの読み込み,初期設定(load_file,setting)
    (2)0代の作成(first_generation)
    (3)1-MAX_GENE代の作成(next_generation)
    (4)結果の出力(result)
*/
/*
 first_generationの流れ
    (1)各個体をランダムに作成,評価計算(make_list(random_individual),scoring)
    (2)scoreに基づく相対順位rankを計算(scoring)
 next_generationの流れ
    (1)前世代の最高個体を1番目にcopy
    (2)各個体を選択/交叉/突然変異のいずれかで作成(評価値計算scoringはそれぞれのメソッド内に組み込まれている)
    (3)scoreに基づく相対順位rankを計算(scoring)
*/
/*
 遺伝のアルゴリズム(next_generationの(2))
 選択の流れ(selection(in next_generaion))
    (1)rankに基づいて親を選ぶ(selection)
    (2)親をそのままコピーする(make_list(copy_individual))(評価値もcopyされてる)
 交叉の流れ(crossover(in next_generation))
    (1)rankに基づいて異なる親2つを選ぶ(selection)
    (2)親のrankと交叉内突然変異率に応じて,人ごとに,一方の親の練習日程をcopy or ランダム生成で作成(make_list(random_list,copy_list))
    (3)評価計算(scoring)
 突然変異の流れ（mutation(in next_generation))
    (1)個体をランダムに作成
    (2)評価値計算(scoring)
 */
/*

 評価値計算の流れ(scoring)
    (1)個体データを日程別データ(detail->courts)と選手別データ(detail->players)に変換(group_court)
    (2)面分けによる日程ごとの点数計算(court_score)
    (3)人ごとの練習日程,メンバによる点数計算(personal_score)
    (4)日程別データの解放
 court_scoreの計算の流れ(court_score)
    (1)日程ごとに評価値を計算
 personal_scoreの計算の流れ
    (1)個人スコアを計算
 */

#include "root.h"

int DAY = 10;
char** DAY_LIST;
