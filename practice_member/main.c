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
#include "genetic_algorithm.h"
#include "test.h"


int main(int argc, const char * argv[]) {
    srand((unsigned)time(NULL));
    //make_testfile(30);
    //make_testfile2(10);
     if(argc>1){
        genetic_algorithm(argv[1],0);
    }
    return 0;
}

/*整備記録
    #今後の課題,!解決済み,・作業内容
 !ごく稀にmember_listでerrorがでる->3/24に対処.根本原因はmallocとfreeにありそう.
 !入力から可能日程と2限抜け日程リストを作る
 1/6:settingにてscoringのパラ設定を整理.
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
*/
/*作業予定

    #scoringの仕組みの簡略化(使用するデータ構造の簡略化)
    #性能比較用の関数の用意
    #出力ファイルの設定
    #学年バランスによる評価の追加(court_score)
    #3回練習に対応
 */
