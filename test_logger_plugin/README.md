# Test Logger Plugin for AviUtl2

簡単な汎用プラグイン (.aux2) で、ロード時とプロジェクト読み込み時にログウィンドウへメッセージを出すだけの動作確認用です。

## ビルド方法

1. 任意のビルドディレクトリを作成して移動  
   例: `mkdir build && cd build`
2. CMake で 64bit 向けプロジェクトを生成  
   `cmake -G "Visual Studio 17 2022" -A x64 ..`
3. ビルド  
   `cmake --build . --config Release`
4. 出力物 `test_logger.aux2` を AviUtl2 の `Plugin` フォルダへコピー

## 期待されるログ

- AviUtl2 起動時: `[test_logger] プラグインを読み込みました`
- プロジェクトを開く／新規作成時: `[test_logger] プロジェクトを読み込みました`
