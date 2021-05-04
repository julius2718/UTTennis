//
//  test.h
//  practice_member
//
//  Created by 長澤達也 on 2020/03/23.
//  Copyright © 2020 長澤達也. All rights reserved.
//
/*役割
    テスト用の入力データを"TestData.csv"として作成する.
 */

#ifndef test_h
#define test_h

#include <stdio.h>
#include <stdlib.h>
#include "load_file.h"

int make_testfile(int people,int d);
int make_testfile2(int people,int d);
#endif /* test_h */
