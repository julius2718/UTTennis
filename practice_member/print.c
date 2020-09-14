
//
//  print.c
//  practice_member
//
//  Created by 長澤達也 on 2020/03/25.
//  Copyright © 2020 長澤達也. All rights reserved.
//

#include "print.h"

void print_list(int **list,int n,int m){
    //n*m行列の出力
    int i,j;
    for(i=0;i<n;i++){
        printf("rank=%d -> ",i+1);
        for(j=0;j<m;j++){
            printf("%d ",list[i][j]);
        }
        printf("\n");
    }
}

void print_individual(info f,individual a){
    print_list(a->list,f->people,DAY);
}


void print_rank(info f,generation g){
    int i;
    printf("この世代の評価値一覧です\n");
    for(i=0;i<N_GENE-1;i++){
        printf("%d ",(int)g->indi[i]->score);
    }
    printf("%d \n",(int)g->indi[i]->score);
}

void print_rank2(info f,generation g){
    int i;
    printf("この世代の評価値rank一覧です\n");
    for(i=0;i<N_GENE-1;i++){
        printf("%3f ",g->rank[i]);
    }
    printf("%3f \n",g->rank[i]);
}
