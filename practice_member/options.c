//
//  options.c
//  practice_member
//
//  Created by 長澤達也 on 2021/09/21.
//  Copyright © 2021 長澤達也. All rights reserved.
//

#include "options.h"

int input_int(void);
int input_check(void);

int change_gene_parameter(void){
    int tmp_ngene,tmp_maxgene,checker;
    tmp_ngene = N_GENE;
    tmp_maxgene = MAX_GENE;
    checker = -1;
    printf("*****遺伝アルゴリズムのパラメータ変更モード*****\n");
    printf("☆計算時間はおおよそ2つの積で決まります.\n");
    printf("現在のパラメータは,\n");
    printf("    1世代の個体数: %dつ\n", N_GENE);
    printf("    最大世代数: %d世代\n", MAX_GENE);
    while(checker !=0){
        printf("+++1世代あたりの個体数を入力してください+++\n");
        while((tmp_ngene = input_int()) == -1){
            printf("+++もう一度入力してください+++\n");
        }
        printf("+++最大世代数を入力してください+++\n");
        while((tmp_maxgene = input_int()) == -1){
            printf("+++もう一度入力してください+++\n");
        }
        printf("パラメータを変更しました.\n");
        printf("    1世代の個体数: %dつ\n", tmp_ngene);
        printf("    最大世代数: %d世代\n", tmp_maxgene);
        checker = input_check();
    }
    N_GENE = tmp_ngene;
    MAX_GENE = tmp_maxgene;
    printf("*****遺伝アルゴリズムのパラメータ変更モード終了*****\n");
    sleep(1);
    return 0;
}

//正の整数を出力. エラー時は-1を出力
int input_int(void){
    char buffer[32] = "";
    char *endptr;
    long num;
    if (scanf("%31[^\n]%*[^\n]", buffer) == EOF) {
        return -1;
    }
    scanf("%*c");
    num = strtol(buffer, &endptr, 10);
    if (*endptr != '\0' || errno == ERANGE || num < 1) {
        return -1;
    }
    return (int)num;
}

//問題なければ0. やり直し要求時は-1を出力
int input_check(void){
    char buffer[256] = "";
    printf("問題がなければEnterキーを, やり直す場合は適当なキーを入力してください\n");
    if (scanf("%255[^\n]%*[^\n]", buffer) == EOF) {
        return -1;
    }
    scanf("%*c");
    if(strlen(buffer) != 0){
        return -1;
    }
    return 0;
}
