//
//  genetic_algorithm.c
//  practice_member
//
//  Created by 長澤達也 on 2019/11/06.
//  Copyright © 2019 長澤達也. All rights reserved.
//

#include "genetic_algorithm.h"

//メインの関数.ファイルの読み込みから結果の出力まで
//opt=0:通常仕様
//opt=1:常にランダム生成の遺伝アルゴリズム.テスト比較用
void genetic_algorithm(const char* fname,int opt){
    int i,people;
    personal* personal_list;
    info f;
    generation g,g_old;
    NEW(personal_list,max_people);NEW(g,MAX_GENE+1);
    for(i=0;i<max_people;i++)personal_list[i]=NULL;
    //ファイルの読み込み,入力の設定
    people = load_file(personal_list,fname);
    if(people==-1)exit(1);//エラー終了
    f = info_build(people,personal_list);
    free_personal(people,personal_list);    //personal_listはinfo_buildで用済み
    //初代の作成
    g = first_generation(f);
    //print_generation(f,g[0]);
    //1~MAX_GENE世代の作成
    for(i=0;i<MAX_GENE;i++){
        g_old = g;
        if(opt==0){
            g = next_generation(f,g_old);
        }else if (opt==1){
            g = next_generation_random(f,g_old);
        }
        if(i%100==0)printf("第%d世代が作成されました.最高評価値は%.1fです\n",i+1,g->indi[g->max_indi]->score);
        free_generation_(f,g_old);
    }
    //最終結果の出力
    print_generation(f,g);
    free_generation_(f,g);
    free_info(f);
}



