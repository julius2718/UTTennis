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

int random_dayprint(int* list,FILE *fp){
    int j,c,d;
    while(1){
        c = 0;
        for(j=0;j<DAY;j++){
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

int make_testfile(int people){
    printf("****** start making test csv file *****\n");
    FILE *fp;
    char filename[] = "TestData.csv";
    int i,j,year;
    int* daylist;
    NEW(daylist,DAY);
    fp = fopen(filename,"w");
    fprintf(fp,"氏名,学年,月朝,月夜,火朝,火夜,水朝,水夜,木朝,木夜,金朝,金夜,ランク\n");
    printf("氏名,学年,月朝,月夜,火朝,火夜,水朝,水夜,木朝,木夜,金朝,金夜,ランク\n");
    for(i=1;i<=people;i++){
        fprintf(fp,"test%d,",i);printf("test%d,",i);
        year = random_year((double)i/people);
        fprintf(fp,"%d,",year);printf("%d,",year);
        random_dayprint(daylist,fp);
        for(j=0;j<DAY;j++){
            fprintf(fp,"%d,",daylist[j]);printf("%d,",daylist[j]);
        }
        fprintf(fp,"%d\n",i);printf("%d\n",i);
    }
    SAFE_FREE(daylist);
    fclose(fp);
    printf("****** finish making test csv file *****\n");
    return 0;
}

int make_testfile2(int people){
    //ランクの重複や飛びのあるテストファイルを作成
    //ランクを1-max_peopleの中からランダムに選択
    printf("****** start making test csv file *****\n");
    FILE *fp;
    char filename[] = "TestData2.csv";
    int i,j,year,rank;
    int* daylist;
    NEW(daylist,DAY);
    fp = fopen(filename,"w");
    fprintf(fp,"氏名,学年,月朝,月夜,火朝,火夜,水朝,水夜,木朝,木夜,金朝,金夜,ランク\n");
    printf("氏名,学年,月朝,月夜,火朝,火夜,水朝,水夜,木朝,木夜,金朝,金夜,ランク\n");
    for(i=1;i<=people;i++){
        fprintf(fp,"test%d,",i);printf("test%d,",i);
        year = random_year((double)i/people);
        fprintf(fp,"%d,",year);printf("%d,",year);
        random_dayprint(daylist,fp);
        for(j=0;j<DAY;j++){
            fprintf(fp,"%d,",daylist[j]);printf("%d,",daylist[j]);
        }
        rank = rand()%max_people+1;
        fprintf(fp,"%d\n",rank);printf("%d\n",rank);
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
