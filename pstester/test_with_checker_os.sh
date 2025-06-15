#!/bin/bash

# テスト回数と引数数の設定
NUM_TESTS=10
ARG_COUNT=500

for i in $(seq 1 $NUM_TESTS); do
  echo "===== テスト $i ====="

  # ランダムな引数生成
  ARGS=$(seq 1 $ARG_COUNT | shuf | tr '\n' ' ')
  echo "引数: $ARGS"

  # push_swap 実行 → 手順を一時ファイルに保存
  ./push_swap $ARGS > ops.txt
  STEPS=$(wc -l < ops.txt)

  # checker_linux で正当性確認
  RESULT=$(cat ops.txt | ./checker_linux $ARGS)

  # 色付き出力（OK:緑、KO:赤、Error:黄色）
  if [ "$RESULT" = "OK" ]; then
    echo -e "✅ \033[32mchecker_linux結果: OK\033[0m"
  elif [ "$RESULT" = "KO" ]; then
    echo -e "❌ \033[31mchecker_linux結果: KO（ソート失敗）\033[0m"
  else
    echo -e "⚠️  \033[33mchecker_linux結果: $RESULT（異常な出力）\033[0m"
  fi

  echo "ステップ数: $STEPS"

  # valgrind でメモリリークチェック
  valgrind --leak-check=full --quiet --error-exitcode=1 ./push_swap $ARGS > /dev/null
  if [ $? -eq 0 ]; then
    echo -e "✅ \033[32mメモリリークなし\033[0m"
  else
    echo -e "❌ \033[31mメモリリーク検出！\033[0m"
  fi

  echo ""
done

# 後始末
rm -f ops.txt
