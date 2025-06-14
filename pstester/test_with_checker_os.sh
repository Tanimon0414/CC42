

#!/bin/bash

# テスト回数と引数の個数を設定
NUM_TESTS=50
ARG_COUNT=500
  # smallから始めたいなら 5〜10 がおすすめ

for i in $(seq 1 $NUM_TESTS); do
  echo "===== テスト $i ====="
  ARGS=$(seq 1 $ARG_COUNT | shuf | tr '\n' ' ')
  echo "引数: $ARGS"

  # 手順出力
  STEPS=$(./push_swap $ARGS | tee ops.txt | wc -l)
  RESULT=$(cat ops.txt | ./checker_linux $ARGS)

  echo "checker_OS結果: $RESULT"
  echo "ステップ数: $STEPS"

  # メモリリークチェック
  valgrind --leak-check=full --quiet --error-exitcode=1 ./push_swap $ARGS > /dev/null
  if [ $? -eq 0 ]; then
    echo "✅ メモリリークなし"
  else
    echo "❌ メモリリーク検出！"
  fi

  echo ""
done

# 一時ファイル削除
rm -f ops.txt
