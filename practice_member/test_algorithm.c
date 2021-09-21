//
//  test_algorithm.c
//  practice_member
//
//  Created by 長澤達也 on 2021/05/26.
//  Copyright © 2021 長澤達也. All rights reserved.
//

#include "test_algorithm.h"


//1つのパラメータで繰り返して評価値の平均等のデータをとる
//同じく,平均的な?推移のデータをとる
//評価値の(MAX_GENE*試行回数)配列

double* tmp_scores(info f,int max_gene,int opt);
void plot_graph(double** scores,int n,int repeat);
double* print_test_result(double** scores,int n,int repeat,long time);

void simple_genetic(const char* fname,int opt,int repeat){
    //性能評価用の簡素版アルゴリズム
    info f;
    int i;
    long t_start,t_finish;
    double** scores;
    double* stats;
    NEW(scores,repeat);
    f = preprocessing(fname);
    t_start = clock();
    for(i=0;i<repeat;i++){
        scores[i] = tmp_scores(f,MAX_GENE,opt);
        printf("%d回目の試行が終了.最終評価値は%.1f\n",i+1,scores[i][MAX_GENE]);
    }
    t_finish = clock();
    plot_graph(scores,MAX_GENE+1,repeat);
    stats = print_test_result(scores,MAX_GENE+1,repeat,t_finish-t_start);
    for(i=0;i<repeat;i++)SAFE_FREE(scores[i]);
    SAFE_FREE(scores);
    SAFE_FREE(stats);
    free_info(f);
    free_global();
}

double* tmp_scores(info f,int max_gene,int opt){
    double* scores;
    int i;
    generation g,g_old;
    NEW(g,MAX_GENE+1);
    NEW(scores,max_gene+1);
    //初代の作成
    g = first_generation(f);
    scores[0] = g->indi[g->max_indi]->score;
    //1~MAX_GENE世代の作成
    for(i=0;i<max_gene;i++){
        g_old = g;
        if(opt==0){
            g = next_generation(f,g_old);
        }else if (opt==1){
            g = next_generation_random(f,g_old);
        }
        scores[i+1] = g->indi[g->max_indi]->score;
        free_generation_(f,g_old);
    }
    free_generation_(f,g);
    return scores;
}


void plot_graph(double** scores,int n,int repeat){
    FILE *gp;
    int i,j;
    
    gp = popen("/usr/local/bin/gnuplot -persist","w");
    fprintf(gp, "plot '-' with lines linetype 1 title \"graph1\"");
    for(i=1;i<repeat;i++)fprintf(gp, ", '-' with lines linetype 1 title \"graph%d\"",i+1);
    fprintf(gp, "\n");
    for(i=0;i<repeat;i++){
        for(j=0;j<n;j++){
            fprintf(gp,"%d\t%f\n",j,scores[i][j]);
        }
        fprintf(gp,"e\n");
    }
    //fprintf(gp, "set logscale y\n");
    fprintf(gp, "replot\n");
    pclose(gp);
}

double* print_test_result(double** scores,int n,int repeat,long time){
    double score,min,max,sum,ave,sum_dev,dev,ave_time;
    double* stats;
    NEW(stats,5);
    int i;
    min=0;max=0;sum=0;sum_dev=0;
    for(i=0;i<repeat;i++){
        score =scores[i][n-1];
        if(i==0){
            min = score;
            max = score;
        }else{
            if(min>score)min=score;
            if(max<score)max=score;
        }
        sum += score;
        sum_dev+= score*score;
    }
    ave_time = (double)time/CLOCKS_PER_SEC/repeat;
    ave = sum/repeat;
    dev = sqrt(sum_dev/repeat - ave*ave);
    stats[0] = ave_time;stats[1] = ave;stats[2] = dev;stats[3] = min;stats[4] = max;
    printf("CPU時間:%fs\n",ave_time);
    printf("平均スコア:%.1f,  標準偏差:%.1f\n",ave,dev);
    printf("最低スコア:%.1f,  最高スコア:%.1f\n",min,max);
    return stats;
}

