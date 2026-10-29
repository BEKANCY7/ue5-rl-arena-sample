#!/usr/bin/env bash
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
BUILD="$ROOT/Harness/build"

if ! command -v cmake >/dev/null 2>&1; then
  if [[ -x "$HOME/.local/cmake/bin/cmake" ]]; then
    export PATH="$HOME/.local/cmake/bin:$PATH"
  else
    echo "cmake not found on PATH" >&2
    exit 127
  fi
fi

cmake -S "$ROOT/Harness" -B "$BUILD"
cmake --build "$BUILD"
ctest --test-dir "$BUILD" --output-on-failure
echo "VERIFY_OK"
