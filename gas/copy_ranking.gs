
//練習日程作成のため，ランク表をコピー。

function copy() {
  var origin_sheets = SpreadsheetApp.openById("YOUR_ORIGIN_SHEETID_HERE").getSheets(); //コピー元のSheetIDを取得すること
  var destination = SpreadsheetApp.openById("YOUR_DESTINATION_SHEETID_HERE").getSheets(); //コピー先の…
  
  var copiedValues = undefined;
  
  for (n in origin_sheets) {
    destination[n].clear();
    copiedValues = origin_sheets[n].getRange("A1:B100").getValues();
    destination[n].getRange("A1:B100").setValues(copiedValues);
  }
}
