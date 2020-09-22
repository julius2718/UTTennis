//
//  result.h
//  practice_member
//
//  Created by 長澤達也 on 2019/11/15.
//  Copyright © 2019 長澤達也. All rights reserved.
//
/*役割
   結果を様々なテキストで出力する
   print_result...メーリスに流す形式での出力
   print_score...評価値に関する情報を出力
   print_csv...csv形式での出力.結果が視覚的に見やすい.
*/

#ifndef result_h
#define result_h

#include <stdio.h>
#include "scoring.h"

void print_generation(info f,generation g);
void print_result(info f,individual a);
void print_score(info f,individual a);
void print_csv(info f,individual a);

#endif /* result_h */
