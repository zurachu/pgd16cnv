pgd16cnv

8bit or 4bit の Windows BMP を、
LDirect_DrawObject() で描画できる16階調拡張 P/ECE BMP に変換します。


■ 8bit or 4bit Windoes BMP の作成

グレースケールで、パレットの0番～15番を白～黒にして作成して下さい。
8bit の場合は、それ以外の色は透過色として扱われます。
幅は、8の倍数（通常の P/ECEBMP と同様）


■ コンバータ実行方法

pgd16cnv [option] bmpfile ...

option -t テキスト出力 (.c) デフォルト
       -b バイナリ出力 (.pgx)
bmpfile Windows BMP ファイル名
        複数指定可能、ワイルドカードも使えます

