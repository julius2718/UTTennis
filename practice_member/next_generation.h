//
//  next_generation.h
//  practice_member
//
//  Created by 長澤達也 on 2019/11/05.
//  Copyright © 2019 長澤達也. All rights reserved.
//

#ifndef next_generation_h
#define next_generation_h

#include <stdio.h>
#include "selection.h"
#include "scoring.h"

individual selection(info f,generation g);
individual crossover(info f,generation g);
individual mutation(info f,generation g);
generation next_generation(info f,generation g);
generation next_generation_random(info f,generation g);

#endif /* next_generation_h */
