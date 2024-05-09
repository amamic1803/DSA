#!/bin/bash

printf "Running tests...\n\n"

declare -i success=0
declare -i fail=0

for algorithm in */;
do
  algorithm=${algorithm%/}
  if [ "$algorithm" != "venv" ]; then
    cd "$algorithm" || exit 1
    for language in */;
    do
      language=${language%/}
      printf "#%d %s (%s) ... " $((success + fail)) "$algorithm" "$language"
      cd "$language" || exit 1
      case "$language" in
        "Python")
          output=$(ruff check . 2>&1)
          exit_code=$?
          if [ "$exit_code" -eq 0 ]; then
            output=$(python -m unittest 2>&1)
            exit_code=$?
          fi
          if [ "$exit_code" -eq 0 ]; then
            printf "\033[32mOK\033[0m\n"
            success+=1
          else
            printf "\033[31mFAIL\033[0m\n"
            printf "%s\n" "$output"
            fail+=1
          fi
          ;;
        "Rust")
          output=$(cargo clippy -- -D warnings 2>&1)
          exit_code=$?
          if [ "$exit_code" -eq 0 ]; then
            output=$(cargo fmt --all -- --check 2>&1)
            exit_code=$?
          fi
          if [ "$exit_code" -eq 0 ]; then
            output=$(cargo build 2>&1)
            exit_code=$?
          fi
          if [ "$exit_code" -eq 0 ]; then
            output=$(cargo test 2>&1)
            exit_code=$?
          fi
          if [ "$exit_code" -eq 0 ]; then
            printf "\033[32mOK\033[0m\n"
            success+=1
          else
            printf "\033[31mFAIL\033[0m\n"
            printf "%s\n" "$output"
            fail+=1
          fi
          ;;
        *)
          printf "\033[31mUnknown language!\033[0m\n"
          exit 1
          ;;
      esac
      cd ..
    done
    cd ..
  fi
done

printf "\nTest results:\n"
printf "\033[32mOK\033[0m: %d\n" "$success"
printf "\033[31mFAIL\033[0m: %d\n" "$fail"
if [ "$fail" -gt 0 ]; then
  exit 1
fi
