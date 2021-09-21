//
//  main.c
//  practice_member
//
//  Created by 長澤達也 on 2019/11/05.
//  Copyright © 2019 長澤達也. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "options.h"
#include "test_algorithm.h"
#include "test.h"


int main(int argc, char * argv[]) {
    srand((unsigned)time(NULL));
    //------------------------------------------
    //入力の確認
    //------------------------------------------
    
    int geneopt,scoreopt,opt;
    const char* optstring = "gs";
    geneopt=0;scoreopt=0;
    while((opt = getopt(argc,argv,optstring))!=-1){
        switch (opt){
            case 'g':
                geneopt = 1;
                break;
            case 's':
                scoreopt = 1;
                break;
            default:
                printf("error! \'%c\' \'%c\'\n", opt, optopt);
                return 1;
        }
    }
    //------------------------------------------
    //オプション操作の実行
    //------------------------------------------
    if(geneopt == 1){
        change_gene_parameter();
    }
    //------------------------------------------
    //テストファイルの作成
    //------------------------------------------
    //if(make_testfile(50,15)<0)return EXIT_FAILURE;
    //if(make_testfile2(30,10)<0)return EXIT_FAILURE;
    
    //------------------------------------------
    //遺伝アルゴリズムによる練習日程の作成
    //------------------------------------------
     if(argc>1){
        genetic_algorithm(argv[argc-1],0);
     }else{
         printf("入力が不正です.入力を確認してください.\n");
     }
    //------------------------------------------
    //性能評価用の繰り返し関数
    //------------------------------------------
    //simple_genetic(argv[argc-1],0,5);
    return 0;
}

/*整備記録
    #今後の課題,!解決済み,・作業内容
 !ごく稀にmember_listでerrorがでる->3/24に対処.根本原因はmallocとfreeにありそう.
 !入力から可能日程と2限抜け日程リストを作る
  2020/1/6:settingにてscoringのパラ設定を整理.
    #c_sumの4人加点が面ごとではなくに日ごとのアンバランスになってる
    !点数の計算タイミングを考えてデータ構造を変更することで高速化できるかも.
     逐一計算になってる可能性
    #p_equは複数の計算方法を用意してもいいかもしれない
    !一部面を固定した状態での運営をできるようにもしたい->固定場所の日程を1以外にすれば行けそう
    ・info_buildをsettingに移行した
    ・test用データを整備.日程の決め方は変えた方がいいかも
 1/7:settingとmake_listの整理
    ・info_buildをsettingに移行
    #一部の人が3回練習に入れるようにしたり,固定練習日をつくる.
    ・settingとmake_listで固定練習日を-1で実装.また希望練習回数をinfoに追加
    !make_listをgenerationの作成系とprint系でセパレートする
 3/23:入力とテストデータ整理
    ・CSVファイルからの読み取りをpersonal_listの格納するload_fileを作成
    ・それにともない,info_buildをpersonal_listで作成,genetic_algoにinfo_buildなどをまとめる
    ・test用のランダムデータのcsvファイル作成メソッドを作成.学年はランク依存
 3/24
    ・以前からのmember_listでのエラーの原因箇所を特定.原因は以前不明だが,me->numberの代入位置をずらしてエラー回避.
    !構造体ポインタ系の管理がズタボロなので,遺伝によるデータ引き継ぎを見直して,適宜freeできるようにする.
    #学年要素の実装,infoへの組み込み.学年によるスコアの考案
    !グローバル変数や定数を取り入れて,コードを簡素化する.
 3/25
    !group_courtのnew_courtでaが初期化されててBAD_ACCESSになる不具合あり.突然変異によるランダム生成時に発生か.->どこかでfreeされてる?
    ・infoの一部定数をroot内でマクロ化.infoは希望日程と遺伝のパラメタ情報だけに.
    ・root.c内に各ファイルの接続図を作成.
    !root.cに？設計書スペースを作る.
    ・make_listからprintを分離
 3/26
    ・make_listの各関数の見直し
    #scoringに学年による評価の追加
    ・root.cに構造体一覧と各プログラムの流れを記載
    ・評価関数系統の全体的な見直し.構造体court,mycourtを改善.処理速度が5倍程度に向上.
    ・mycourtのfreeを追加.メモリバグ減った?
 8/30
    ・各ヘッダーファイルにファイルの役割を追記
    ・データ構造系のコードの説明文などを整理
    ・csvの入力をコマンドラインから受け付ける.
 8/31
    ・エラー確認用にrankの飛びや重複のあるテストデータ"TestData2.csv"作成メソッドを作成
    ・settingのコード整理.構造体personalからの参照渡しをなくして早めにfree化.
    ・make_listのコード整理.配列のコピーをmemcpyに変更
    ・group_courtのコード整理
    ・generationを配列にせず世代ごとにfreeしてく関数を実装.
    !free_mycourtでエラー大量発生->scoring系の引き継ぎに問題?
    ・ダブルフリー問題を解決するためSAFE_FREEにfreeを置き換え->mycourtの問題以外解決
    ・mycourtにcourtの情報を持たせない様に変更->次でさらにいじる
  9/12
    ・scoringに使用するデータ構造をdetailに統一(作業中)
  9/13
    ・detailへの統一作業の完了
    !?まれにfree_courtとfree_playerの最初の工程でエラー発生.何らかの形で二重フリーが発生している?
    ->new_court付属のselect_group内で使用しているNEW(score)のミスを直したら消えた.直接関係ないのに...
  9/26
    ・学年バランスによる評価の追加
    ・csv形式の結果をファイルとして保存
  10/21
    ・1行目の形式エラーを警告に変更し処理を続行
    ・一部のprint後に一時停止を挿入
  2021/4/29
    ・設定日時を可変に(昼練なども可能に)
        ・DAYをグローバル変数化(load_fileで取得)
        ・入力形式の変更
        ・testファイルを対応
  5/3
    ・設定日時を可変に(昼練なども可能に)
        ・DAY_LISTをグローバル変数化(load_fileで取得)
    ・練習間隔による評価計算を修正(3回練や朝昼夜練に対応)
  5/4
    ・二限抜けによる評価計算を修正(3回以上の練習に対応)
    ・練習人数による評価計算を修正(朝昼夜練に対応)
    ・スコア詳細のresultを大幅刷新(result_scoring.cに移行)
    ・resultを朝昼夜練に対応
  5/7
    ・改行コード\r\cに対応
    ・練習可能回数が1回以下に対応
    ・練習がない回を減点していた仕様を修正
  5/25
    ・court_rankの評価計算式を変更
  5/26
    ・性能評価用のメソッドをtest_algorithmに追加
    ・各個体の選出確率を定めるrankの計算方式を0にならないように修正.(scoring.c)
  5/27
    ・遺伝アルゴリズムのパラメータを定数(#define)からグローバル変数(extern)に変更
  9/21
    ・遺伝アルゴリズムのパラメータを入力で変更できるオプションを追加(options.c)
    (試作につきrootへの記載は後日)
*/
/*作業予定
    #入力でパラメータを変更できるようにする
        #rootへの仕様の記載
        #遺伝アルゴリズム・評価関数のパラメータ変更モードの追加
        #性能比較モードの追加
        #コードの整理
    #3回練習に対応
    #rankが小数や重複あっても許せるようにする
    #二限抜による評価を個人スコアから練習スコアに移行(同じ面で多いと減点?)
    #昼練に割り振られた場合の減点
 */
