# -*- coding: utf-8 -*-

import gspread
import json

# ServiceAccountCredentials：Googleの各サービスへアクセスできるservice変数を生成します。
from oauth2client.service_account import ServiceAccountCredentials

import numpy as np
import pandas as pd
from pandas import Series, DataFrame

import google_auth as ga
import ranking

gc = ga.gauth()

# Spreadsheetを取得
SPREADSHEET_KEY = 'YOUR_SHEETID_HERE' # Google Formsの出力先シートのID
worksheet = gc.open_by_key(SPREADSHEET_KEY).sheet1

# ---ここからデータ処理---
df = DataFrame(worksheet.get_all_values())
initial_columns_list = list(df.iloc[0, :])
df.columns = initial_columns_list
df.drop(0, inplace=True)
df.reset_index(inplace=True)
df.drop('index', axis=1, inplace=True)
df['学年'] = df['学年'].astype(int)
df['練習回数'] = df['希望する練習回数'].astype(int)

days = ['月', '火', '水', '木', '金']
times = ['朝', '夜']
daytime_list = []

for day in days:
    for time in times:
        daytime_list.append(day+time)

for daytime in daytime_list:
    df[daytime] = 0

for day in days:
    df['{}朝'.format(day)].where((df['{}曜日'.format(day)].str.contains('1')), 1, inplace=True)
    df['{}朝'.format(day)].mask((df['キャンパス'] == '駒場')
                               & ~(df['{}曜日'.format(day)].str.contains('1'))
                               & (df['{}曜日'.format(day)].str.contains('2')), 2, inplace=True)
    df['{}夜'.format(day)].where((df['{}曜日'.format(day)].str.contains('5'))
                                | (df['{}曜日'.format(day)].str.contains('6')), 1, inplace=True)

boys_df = df[df['所属']=='男子部']
boys_df = ranking.sort_by_ranking(boys_df, '男子部')
girls_df = df[df['所属']=='女子部']
girls_df = ranking.sort_by_ranking(girls_df, '女子部')


unnecessary_columns_list = initial_columns_list
unnecessary_columns_list.remove('名前')
unnecessary_columns_list.remove('学年')

boys_results_df = boys_df.drop(unnecessary_columns_list, axis=1)
boys_results_df.to_csv('../results/boys_input.csv', header=True, index=False)

girls_results_df = girls_df.drop(unnecessary_columns_list, axis=1)
girls_results_df.to_csv('../results/girls_input.csv', header=True, index=False)

df.to_csv('../results/results.csv', header=True, index=False)
