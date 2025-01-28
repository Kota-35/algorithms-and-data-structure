# 赤黒木（Red-Black Tree）の実装

このプロジェクトはC++で実装された赤黒木のデータ構造を提供します。

## 機能
- 挿入操作（insert）
- 削除操作（delete）
- 木構造の表示（print_tree）

## 実装詳細
- 赤黒木の基本的な性質を満たす実装
- 左回転（left_rotate）と右回転（right_rotate）による木の再構築
- 挿入後の修正（insert_fixup）と削除後の修正（delete_fixup）による木の性質の維持

## コンパイル方法
```bash
g++ -std=c++11 -o ./target/out red_black_tree.cpp
```

## 使用方法
コンパイル後、生成された実行ファイルを実行することで、サンプルの操作を確認できます。
```bash
./target/out
```

## 要件
- C++11以上
- g++コンパイラ