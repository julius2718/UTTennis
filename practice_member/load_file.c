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

int first_line_check(char* str);
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
    personal personal_data;
    NEW(DAY_LIST,N);
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
    if(fgets(data,N,fp)==NULL){//一行目の読み込み
        printf("error in load_file.\n");
        printf(" 1行目が正常に読み込まれませんでした.ファイルを確認してください.\n");
        fclose(fp);return -1;
    }else{
        DAY = first_line_check(data);
        RENEW(DAY_LIST,DAY);
        if(DAY==-1){
            printf("error in load_file.\n");
            printf(" 1行目が正常に読み込まれませんでした.書式を確認してください.\n");
            fclose(fp);return -1;
        }
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
    sleep(2);
    //入力データの表示
    print_person_data(plist,people);
    return people;
}

int first_line_check(char* str){
    char name[N],rank[N],year[N],emp[N],tmp[N];
    char _name[] = "氏名";
    char _year[] = "学年";
    char _rank[] = "ランク";
    int i,k,num,ret;
    i = 0;
    num = -1;
    ret = 2;
    if(sscanf(str,"%[^,],%[^,],%[^,],",name,year,rank)!= 3)return -1;
    if(strncmp(_name,name,strlen(_name))!=0||strncmp(_year,year,strlen(_year))!=0||strncmp(_rank,rank,strlen(_rank))!=0){
        printf("caution in first_line_check.\n");
        printf(" 1行目の書式に誤りがあり,正しく読み込めない可能性があります.\n");
    }
    for(k=0;k<2;k++){
        while(i<strlen(str)&&str[i]!=','){str[i]=' ';i++;}
        if(i<strlen(str))str[i]=' ';
    }
    printf("練習設定日時は");
    while(ret == 2){
        while(i<strlen(str)&&str[i]!=','){str[i]=' ';i++;}
        num++;
        ret = sscanf(str,"%[^,],%[^,\r\n]",emp,tmp);
        if(i<strlen(str))str[i]=' ';
        if(ret==2){
            printf(",%s",tmp);
            NEW(DAY_LIST[num],N);
            memcpy(DAY_LIST[num],tmp,strlen(tmp));
        }
    }
    printf(" の%d回です.\n",num);
    return num;
}


personal make_person_data(char* str){
    //入力データの各行から各選手の情報をpersonalに格納する
    //書式が一致しない場合NULLを返す->呼び出し元でメソッド終了
    personal data;
    NEW(data,1);
    NEW(data->name,N);
    int tmp_list[N];
    int ret,i,j;
    i=0;j=-1;
    ret = sscanf(str,"%[^,],",data->name);
    if(ret != 1){
        printf("error in make_person_data.\n");
        printf(" 入力データの読み込みに失敗しました.書式を確認してください.\n");
        return NULL;
    }
    while(ret == 1){
        j++;
        while(i<strlen(str)&&str[i]!=','){str[i]=' ';i++;}
        if(i<strlen(str))str[i]=' ';
        ret = sscanf(str,"%d",&tmp_list[j]);
    }
    if(j != DAY+2){
        printf("error in make_person_data.\n");
        printf(" データ数の異なる行があります.入力を確認してください.\n");
        return NULL;
    }
    NEW(data->list,DAY);
    data->year = tmp_list[0];
    data->rank = tmp_list[1];
    for(i=0;i<DAY;i++)data->list[i]=tmp_list[i+2];
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
    i=0;p=0;
    while(p<people){
        if(plist[i]!=NULL){
            printf("%s(%d年,%d位)の練習可能日程は",plist[i]->name,plist[i]->year,plist[i]->rank);
            for(d=0;d<DAY;d++){
                if(plist[i]->list[d]!=0)printf(" %s",DAY_LIST[d]);
            }
            printf("です.\n");
            p++;
        }else{
            printf("rank%dは登録されていません.\n",i+1);
        }
        i++;
    }
    printf("***** check input deta *****\n");
    sleep(1);
    return 0;
}

