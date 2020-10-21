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
#define SAFE_FREE(ptr){\
    free(ptr);\
    ptr=NULL;\
    }
#define N 256
#define max_people 100 //最大人数
#define MAX_PEOPLEinCOURT 4 //1面の最大人数:変更時はselect_groupのコード改変が必要
#define DAY 10 //練習数(月~金の朝夜で10回):変更時は諸々のコード改変が必要

#define MAX_GENE 1000 //遺伝アルゴリズムの最大世代数.初代を0とする
#define N_GENE 1000 //1世代の個体数
#define MUTATION 0.01   //突然変異による個体生成率
#define SELECTION 0.7   //選択による個体生成率
#define CROSSOVER 0.1   //交叉による個体生成時の部分突然変異率

#endif /* root_h */
