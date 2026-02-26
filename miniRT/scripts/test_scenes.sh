#!/usr/bin/env bash
set -u

ROOT_DIR="$(cd "$(dirname "$0")/.." && pwd)"
APP="$ROOT_DIR/miniRT"
VALID_DIR="$ROOT_DIR/scenes/tests_valid"
INVALID_DIR="$ROOT_DIR/scenes/tests_invalid"

ok=0
ng=0

echo "[build] make"
if ! make -C "$ROOT_DIR" >/tmp/minirt_test_make.log 2>&1; then
  echo "[FAIL] build failed"
  sed -n '1,60p' /tmp/minirt_test_make.log
  exit 1
fi

run_valid() {
  local file out ec
  file="$1"
  out="/tmp/minirt_valid_$(basename "$file").log"
  timeout 1 "$APP" "$file" >"$out" 2>&1
  ec=$?
  if grep -q '^Error$' "$out"; then
    echo "[FAIL] valid -> error: $(basename "$file")"
    sed -n '1,6p' "$out"
    ng=$((ng + 1))
    return
  fi
  if [ "$ec" -ne 0 ] && [ "$ec" -ne 124 ]; then
    echo "[FAIL] valid -> bad exit($ec): $(basename "$file")"
    sed -n '1,6p' "$out"
    ng=$((ng + 1))
    return
  fi
  echo "[PASS] valid: $(basename "$file")"
  ok=$((ok + 1))
}

run_invalid() {
  local file out
  file="$1"
  out="/tmp/minirt_invalid_$(basename "$file").log"
  "$APP" "$file" >"$out" 2>&1
  if grep -q '^Error$' "$out"; then
    echo "[PASS] invalid: $(basename "$file")"
    ok=$((ok + 1))
  else
    echo "[FAIL] invalid -> no error: $(basename "$file")"
    sed -n '1,6p' "$out"
    ng=$((ng + 1))
  fi
}

echo "[test] valid scenes"
for f in "$VALID_DIR"/*.rt; do
  run_valid "$f"
done

echo "[test] invalid scenes"
for f in "$INVALID_DIR"/*.rt "$INVALID_DIR"/*.txt; do
  run_invalid "$f"
done

echo "[result] pass=$ok fail=$ng"
if [ "$ng" -ne 0 ]; then
  exit 1
fi
exit 0
