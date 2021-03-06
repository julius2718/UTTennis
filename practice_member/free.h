//
//  free.h
//  practice_member
//
//  Created by 長澤達也 on 2019/11/06.
//  Copyright © 2019 長澤達也. All rights reserved.
//
/*役割
   各種構造体のメモリ解放を行うfree関数たち.
*/

#ifndef free_h
#define free_h

#include <stdio.h>
#include "group_court.h"

void free_individual_(info f,individual a_);
void free_generation_(info f,generation g);
void free_generation(info f,generation* g);
void free_detail(info f,detail det);
void free_info(info f);
void free_personal(int people,personal* plist);
void free_global(void);


#endif /* free_h */
