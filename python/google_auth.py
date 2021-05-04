# -*- coding: utf-8 -*-

import gspread
import json

# ServiceAccountCredentials：Googleの各サービスへアクセスできるservice変数を生成します。
from oauth2client.service_account import ServiceAccountCredentials

def gauth():
    # Google認証情報
    scope = ['https://spreadsheets.google.com/feeds',
            'https://www.googleapis.com/auth/drive']
    credentials = ServiceAccountCredentials.from_json_keyfile_name(
        'divine-position-290308-a36964268f51.json', scope
    ) # ダウンロードしたjsonファイル名をクレデンシャル変数に設定（秘密鍵、Pythonファイルから読み込みしやすい位置に置く）
    # OAuth2の資格情報を使用してGoogle APIにログイン
    gc = gspread.authorize(credentials)

    return gc
