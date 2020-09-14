//
//  result.h
//  practice_member
//
//  Created by 長澤達也 on 2019/11/15.
//  Copyright © 2019 長澤達也. All rights reserved.
//

#ifndef result_h
#define result_h

#include <stdio.h>
#include "scoring.h"

void print_generation(info f,generation g);
void print_result(info f,individual a);
void print_score(info f,individual a);
void print_csv(info f,individual a);

#endif /* result_h */
