# UTTennis
東大庭球部管理コード集

# Python ファイルの使い方

Google Spreadsheet のデータにアクセスするための設定が必要。`gspread`ライブラリを利用する。

設定の方法はこれ( https://tanuhack.com/library-gspread/#i-5 )を参照のこと。

## 仕様

- 時間割ベースで集める
- Google Forms からpythonの `gspread`ライブラリを使って中身を取ってくる。それをpandasなどを用いて整形。
- 多分、文字列で出力されるので、その中にある数字が入っているかどうかで練習の可不可を判定。
    - e.g.) 駒場生で`2, 3, 4`なら，朝練: 2限抜け，ナイター可。
- 出力時に，ランク表に従って，ランク順にソートされる。

# GAS コードの使い方

## `copy_ranking.gs`
ランク表をコピーして，練習日程処理用のランク表を新たに作る。

参考: https://yokochan-y2.com/google-apps-scriptgas-copy-paste-spread-sheet/

ファイルをどこに置くかとか，書くのが面倒なので，自分で調べてなんとかしてほしい。

おそらく，スクリプトの管理者を変更し，自分のアカウントでコピー先のシートを作成するだけで問題ないはず。
