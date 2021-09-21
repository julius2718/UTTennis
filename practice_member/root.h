//
//  root.h
//  practice_member
//
//  Created by 長澤達也 on 2020/03/25.
//  Copyright © 2020 長澤達也. All rights reserved.
//

#ifndef root_h
#define root_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define NEW(p,n){p=malloc((n)*sizeof(p[0]));};
#define RENEW(p,n){p=realloc(p,(n)*sizeof(p[0]));};
#define SAFE_FREE(ptr){\
    free(ptr);\
    ptr=NULL;\
    }
#define N 256
#define max_people 100 //最大人数
#define MAX_PEOPLEinCOURT 4 //1面の最大人数:変更時はselect_groupのコード改変が必要
extern int DAY; //練習数(月~金の朝夜で10回):変更時は諸々のコード改変が必要
extern char** DAY_LIST;  //練習設定日の文字列.load_file.cで代入

extern int MAX_GENE; //遺伝アルゴリズムの最大世代数.初代を0とする
extern int N_GENE; //1世代の個体数
extern double MUTATION;  //突然変異による個体生成率
extern double SELECTION;  //選択による個体生成率
extern double CROSSOVER;  //交叉による個体生成時の部分突然変異率

#endif /* root_h */
