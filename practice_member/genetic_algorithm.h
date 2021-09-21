//
//  genetic_algorithm.h
//  practice_member
//
//  Created by 長澤達也 on 2019/11/06.
//  Copyright © 2019 長澤達也. All rights reserved.
//

#ifndef genetic_algorithm_h
#define genetic_algorithm_h

#include <stdio.h>
#include "first_generation.h"
#include "next_generation.h"
#include "result.h"

void genetic_algorithm(const char* fname,int opt);
info preprocessing(const char* fname);


#endif /* genetic_algorithm_h */
