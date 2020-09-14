//
//  load_file.c
//  practice_member
//
//  Created by 長澤達也 on 2019/11/14.
//  Copyright © 2019 長澤達也. All rights reserved.
//
//fscanfだと数値も文字列扱いでめんどくさい...->fgetsで一行ずつ取得,sscanfで読み込み
//sscanfのところ,strtokを使えば分割+forで記述できそうだが保留
//name[],year[],rank[],list[][]の作成
//

#include "load_file.h"

personal make_person_data(char* str);
int insert_personal(personal* plist,personal new);
int print_person_data(personal* plist,int people);


int load_file(personal* plist,const char* fname){
    //入力データを読み込みplistに格納する.
    //ファイルを読み込めない場合は-1を返す->呼び出し元でメソッドを終了
    printf("***** start loading csv file *****\n");
    FILE *fp;
    int people = 0;
    char data[N];
    char f_line[] = "氏名,学年,月朝,月夜,火朝,火夜,水朝,水夜,木朝,木夜,金朝,金夜,ランク\n";
    personal personal_data;
    //ファイルの読み込み
    fp = fopen(fname,"r");  //fnameを読み込みモードで開く.返り値はFILE構造体のアドレス
    if(fp == NULL){ //ファイルが開けないとNULLを返す
        printf("error in load_file.\n");
        printf(" %sが開けませんでした.ファイル名を確認してください.\n",fname);
        fclose(fp);return -1;
    }else{
        printf("succeed in file open! file name is %s\n",fname);
    }
    //1行目の形式の確認
    if(fgets(data,N,fp)==NULL){ //一行目の読み込み
        printf("error in load_file.\n");
        printf(" 1行目が正常に読み込まれませんでした.ファイルを確認してください.\n");
        fclose(fp);return -1;
    }else if(strcmp(data,f_line)!=0){
        printf("error in load_file.\n");
        printf(" 1行目が正しくありません.書式を確認してください.\n");
        fclose(fp);return -1;
    }
    //2行目以降の確認&plistへの格納
    while(fgets(data,N,fp)!=NULL){  //一行ずつ読み込み,persondataに格納
        personal_data = make_person_data(data);
        if(personal_data==NULL){fclose(fp);return -1;}
        if(insert_personal(plist, personal_data)==-1){fclose(fp);return -1;};
        people++;
    }
    fclose(fp);
    printf("***** finish loading csv file *****\n");
    //入力データの表示
    print_person_data(plist,people);
    return people;
}


personal make_person_data(char* str){
    //入力データの各行から各選手の情報をpersonalに格納する
    //書式が一致しない場合NULLを返す->呼び出し元でメソッド終了
    personal data;
    NEW(data,1);
    NEW(data->name,N);
    NEW(data->list,10);
    int year,rank;
    if(sscanf(str,"%[^,],%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",data->name,&year,&data->list[0],&data->list[1],&data->list[2],&data->list[3],&data->list[4],&data->list[5],&data->list[6],&data->list[7],&data->list[8],&data->list[9],&rank)!=13){
        printf("error in make_person_data.\n");
        printf(" 入力データの読み込みに失敗しました.書式を確認してください.\n");
        return NULL;
    }
    data->rank = rank;
    data->year = year;
    //printf("%sのデータ読み込みが完了\n",data->name);
    return data;
}

int insert_personal(personal* plist,personal new){
    //personalデータをplistの該当ランクの位置に格納する
    //ランクが想定外の場合-1を返す->呼び出し元でメソッド終了
    if(new->rank>max_people){
        printf("error in insert_personal.\n ランク%dが想定外です.\n",new->rank);
        return -1;
    }
    if(plist[new->rank-1]==NULL){
        plist[new->rank-1] = new;
    }else{
        printf("error in insert_personal.\n ランク%dが重複しています.\n",new->rank);
        return -1;
    }
    return 0;
}

int print_person_data(personal* plist,int people){
    printf("***** check input deta *****\n");
    int i,p;
    int d;
    char day[10][N] = {"月朝","月夜","火朝","火夜","水朝","水夜","木朝","木夜","金朝","金夜"};
    i=0;p=0;
    while(p<people){
        if(plist[i]!=NULL){
            printf("名前:%s,学年:%d,ランク:%dの練習可能日程は",plist[i]->name,plist[i]->year,plist[i]->rank);
            for(d=0;d<10;d++){
                if(plist[i]->list[d]!=0)printf(" %s",day[d]);
            }
            printf("です.\n");
            p++;
        }else{
            printf("rank%dは登録されていません.\n",i+1);
        }
        i++;
    }
    printf("***** check input deta *****\n");
    return 0;
}

