#!/usr/bin/env bash
set -u

ROOT_DIR="$(cd "$(dirname "$0")/.." && pwd)"
APP="$ROOT_DIR/miniRT"
SCENES="$ROOT_DIR/scenes/correction_mandatory"

ok=0
ng=0

printf '[build] make\n'
if ! make -C "$ROOT_DIR" >/tmp/minirt_correction_make.log 2>&1; then
  printf '[FAIL] build failed\n'
  sed -n '1,80p' /tmp/minirt_correction_make.log
  exit 1
fi

run_case() {
  local file out ec
  file="$1"
  out="/tmp/minirt_corr_$(basename "$file").log"
  timeout 1 "$APP" "$file" >"$out" 2>&1
  ec=$?
  if grep -q '^Error$' "$out"; then
    printf '[FAIL] %s -> Error\n' "$(basename "$file")"
    sed -n '1,6p' "$out"
    ng=$((ng + 1))
    return
  fi
  if [ "$ec" -ne 0 ] && [ "$ec" -ne 124 ]; then
    printf '[FAIL] %s -> bad exit(%s)\n' "$(basename "$file")" "$ec"
    sed -n '1,6p' "$out"
    ng=$((ng + 1))
    return
  fi
  printf '[PASS] %s\n' "$(basename "$file")"
  ok=$((ok + 1))
}

printf '[run] correction mandatory scenes\n'
for f in "$SCENES"/*.rt; do
  run_case "$f"
done

printf '[result] pass=%s fail=%s\n' "$ok" "$ng"
if [ "$ng" -ne 0 ]; then
  exit 1
fi
exit 0
