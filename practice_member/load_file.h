//
//  load_file.h
//  practice_member
//
//  Created by 長澤達也 on 2019/11/14.
//  Copyright © 2019 長澤達也. All rights reserved.
//
/*役割
    指定したcsvファイルを読み込み,構造体の配列personal[]として保持する.
    配列の要素数はmax_rank.[rank-1]に対応選手のデータが入っている.
    読み込んだ人数を返す.エラー時は-1.
 */

#ifndef load_file_h
#define load_file_h

#include <stdio.h>
#include "root.h"


typedef struct{ //各選手の情報
    int rank; //ランク
    int year;
    char *name; //名前
    int *list; //メインの練習日程
}*personal;

int load_file(personal* plist,const char* fname); 

#endif /* load_file_h */
