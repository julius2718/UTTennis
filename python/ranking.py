# -*- coding: utf-8 -*-

import gspread
import json

# ServiceAccountCredentials：Googleの各サービスへアクセスできるservice変数を生成します。
from oauth2client.service_account import ServiceAccountCredentials

import numpy as np
import pandas as pd
from pandas import Series, DataFrame

import google_auth as ga

def get_first_names(splitted_names):
    first_names = [name[0] for name in splitted_names]
    given_names = [name[1] for name in splitted_names]

    duplicates = [first_name for first_name in first_names if first_names.count(first_name)>1]

    for i, value in enumerate(first_names):
        if value in duplicates:
            first_names[i] = value + given_names[i][0]
    
    return first_names

def process_ranking(group):
    gc = ga.gauth()
    SPREADSHEET_KEY = '14bvDWMdB8sK0UkoCZ6qtt0dBdw6qeD8cORO0VhFtbbM' # コピーしたランク表のシートID
    worksheet = gc.open_by_key(SPREADSHEET_KEY).worksheet(group)

    df = DataFrame(worksheet.get_all_values())
    initial_columns_list = list(df.iloc[0, :])
    initial_columns_list[1] = '名前'
    df.columns = initial_columns_list
    df.drop(0, inplace=True)
    df.reset_index(inplace=True)
    df.drop('index', axis=1, inplace=True)
    df = df[df['名前']!='']
    df['ランク'] = df['ランク'].astype(int)

    names = list(df.iloc[:, 1])
    splitted_names = []

    for name in names:
        splitted_names.append(name.split(' '))
    
    first_names = get_first_names(splitted_names)
    first_names = Series(first_names)

    df = pd.concat([df, first_names], axis=1)
    df.drop('名前', axis=1, inplace=True)
    df.columns = initial_columns_list

    return df

def sort_by_ranking(df, group):
    df = pd.merge(df, process_ranking(group), on='名前')
    df.sort_values(inplace=True, by='ランク')
    df.reset_index(drop=True, inplace=True)

    return df

if __name__ == '__main__':
    print(process_ranking())
