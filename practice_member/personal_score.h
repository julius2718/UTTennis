//
//  personal_score.h
//  practice_member
//
//  Created by 長澤達也 on 2019/11/08.
//  Copyright © 2019 長澤達也. All rights reserved.
//
//個人スコアを求める

#ifndef personal_score_h
#define personal_score_h

#include <stdio.h>
#include "free.h"

double personal_score(info f,individual a,detail det);
double interval_score(info f,player me);
double equality_score(info f,player me);
double short_prac_score(info f,individual a);


#endif /* personal_score_h */
