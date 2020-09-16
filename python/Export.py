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


class Export():

    SPREADSHEET_KEY = 'YOUR_SHEETID_HERE'

    def get_worksheet(self, worksheet_name):
        gc = ga.gauth()
        worksheet = gc.open_by_key(
            self.SPREADSHEET_KEY).worksheet(worksheet_name)

        return worksheet

    def toAlpha(self, num):
        if num <= 26:
            return chr(64+num)
        elif num % 26 == 0:
            return toAlpha(num//26-1)+chr(90)
        else:
            return toAlpha(num//26)+chr(64+num % 26)

    def export(self, df, worksheet):
        col_lastnum = len(df.columns)
        row_lastnum = len(df.rows)
        cell_list = worksheet.range('A1:'+toAlpha(col_lastnum)+str(row_lastnum))

        for cell in cell_list:
            val = df.iloc[cell.row-1][cell.col-1]
            cell.value = val

        worksheet.update_cells(cell_list)
