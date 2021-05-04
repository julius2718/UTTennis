//
//  test.c
//  practice_member
//
//  Created by 長澤達也 on 2020/03/23.
//  Copyright © 2020 長澤達也. All rights reserved.
//

#include "test.h"

int random_year(double rate){
    //ランダムに学年を決定する.rate=ランク/全体人数.ランクが高いほど学年が高くなりやすい
    int year;
    int b;
    double a;
    a = (rand()+1.0)/(RAND_MAX+2.0);
    b = rand()%4;
    a = (a*b*2+1-rate)/(b*2+1);
    year = (int)(a*4)+1;
    return year;
}

int random_dayprint(int* list,FILE *fp,int day){
    int j,c,d;
    while(1){
        c = 0;
        for(j=0;j<day;j++){
            d = rand()%(rand()%6+2);
            if(d==1){
                list[j]=1;
                c++;
            }else if(d==2 && j%2==0){
                list[j]=2;
            }else{
                list[j] = 0;
            }
        }
    if(c>=2)break;
    }
    return 0;
}

int make_testfile(int people,int d){
    //グローバル変数DAYは用いず個別に設定->d
    printf("****** start making test csv file *****\n");
    FILE *fp;
    char filename[] = "TestData.csv";
    int i,j,year;
    int* daylist;
    NEW(daylist,d);
    fp = fopen(filename,"w");
    if(d==10){
    fprintf(fp,"氏名,学年,ランク,月朝,月夜,火朝,火夜,水朝,水夜,木朝,木夜,金朝,金夜\n");
    printf("氏名,学年,ランク,月朝,月夜,火朝,火夜,水朝,水夜,木朝,木夜,金朝,金夜\n");
    }else if(d==15){
        fprintf(fp,"氏名,学年,ランク,月朝,月昼,月夜,火朝,火昼,火夜,水朝,水昼,水夜,木朝,木昼,木夜,金朝,金昼,金夜\n");
        printf("氏名,学年,ランク,月朝,月昼,月夜,火朝,火昼,火夜,水朝,水昼,水夜,木朝,木昼,木夜,金朝,金昼,金夜\n");
    }else{
        printf("練習回数が不適です\n");
        fclose(fp);
        return -1;
    }
    for(i=1;i<=people;i++){
        fprintf(fp,"test%d",i);printf("test%d",i);
        year = random_year((double)i/people);
        fprintf(fp,",%d",year);printf(",%d",year);
        fprintf(fp,",%d",i);printf(",%d",i);
        random_dayprint(daylist,fp,d);
        for(j=0;j<d;j++){
            fprintf(fp,",%d",daylist[j]);printf(",%d",daylist[j]);
        }
        fprintf(fp,"\n");printf("\n");
    }
    SAFE_FREE(daylist);
    fclose(fp);
    printf("****** finish making test csv file *****\n");
    return 0;
}

int make_testfile2(int people,int d){
    //ランクの重複や飛びのあるテストファイルを作成
    //ランクを1-max_peopleの中からランダムに選択
    //グローバル変数DAYは用いず個別に設定->d
    printf("****** start making test csv file *****\n");
    FILE *fp;
    char filename[] = "TestData2.csv";
    int i,j,year,rank;
    int* daylist;
    NEW(daylist,d);
    fp = fopen(filename,"w");
    if(d==10){
    fprintf(fp,"氏名,学年,ランク,月朝,月夜,火朝,火夜,水朝,水夜,木朝,木夜,金朝,金夜\n");
    printf("氏名,学年,ランク,月朝,月夜,火朝,火夜,水朝,水夜,木朝,木夜,金朝,金夜\n");
    }else if(d==15){
        fprintf(fp,"氏名,学年,ランク,月朝,月昼,月夜,火朝,火昼,火夜,水朝,水昼,水夜,木朝,木昼,木夜,金朝,金昼,金夜\n");
        printf("氏名,学年,ランク,月朝,月昼,月夜,火朝,火昼,火夜,水朝,水昼,水夜,木朝,木昼,木夜,金朝,金昼,金夜\n");
    }else{
        printf("練習回数が不適です\n");
        fclose(fp);
        return -1;
    }
    for(i=1;i<=people;i++){
        fprintf(fp,"test%d",i);printf("test%d",i);
        year = random_year((double)i/people);
        rank = rand()%max_people+1;
        fprintf(fp,",%d",year);printf(",%d",year);
        fprintf(fp,",%d",rank);printf(",%d",rank);
        random_dayprint(daylist,fp,d);
        for(j=0;j<d;j++){
            fprintf(fp,",%d",daylist[j]);printf(",%d",daylist[j]);
        }
        fprintf(fp,"\n");printf("\n");
    }
    SAFE_FREE(daylist);
    fclose(fp);
    printf("****** finish making test csv file *****\n");
    return 0;
}

void test_rand_year(void){
    //random_yearの性能確認用
    int i,j;
    int a,b,c,d;
    for(j=0;j<100;j++){
    a=0;b=0;c=0;d=0;
    for(i=0;i<10000;i++){
        switch(random_year(1-j*0.01)){
            case 1:
                a++;break;
            case 2:
                b++;break;
            case 3:
                c++;break;
            case 4:
                d++;break;
            default:
                printf("erorr\n");break;
        }
    }
    printf("rate=%.2fの時,1=%d,2=%d,3=%d,4=%d\n",1-j*0.01,a,b,c,d);
    }
}
