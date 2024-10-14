import os
import sys
import subprocess


def main():
    ignored_dirs = get_ignored_dirs()

    print("Running tests...\n")

    succeeded = 0
    failed = 0

    for (i, algorithm) in enumerate(filter(lambda x: os.path.isdir(x) and x not in ignored_dirs, os.listdir())):
        print(f"#{i + 1:02d} {algorithm}")
        for (j, language) in enumerate(filter(lambda x: os.path.isdir(os.path.join(algorithm, x)) and x not in ignored_dirs, os.listdir(algorithm))):
            print(f"    {chr(ord('a') + j)}) {language.ljust(10)} ... ", end="")

            match language:
                case "Python":
                    if not run_test(algorithm, language, ["ruff", "check", "."]):
                        failed += 1
                        continue
                    if not run_test(algorithm, language, ["python", "-m", "unittest"]):
                        failed += 1
                        continue
                    print("OK")
                    succeeded += 1
                case "Rust":
                    if not run_test(algorithm, language, ["cargo", "clippy", "--", "-D", "warnings"]):
                        failed += 1
                        continue
                    if not run_test(algorithm, language, ["cargo", "fmt", "--all", "--", "--check"]):
                        failed += 1
                        continue
                    if not run_test(algorithm, language, ["cargo", "build"]):
                        failed += 1
                        continue
                    if not run_test(algorithm, language, ["cargo", "test"]):
                        failed += 1
                        continue
                    print("OK")
                    succeeded += 1
                case _:
                    failed += 1
                    print("Unsupported language!")

    print("\nResults:")
    print("  OK:   ", succeeded)
    print("  FAIL: ", failed)

    if failed > 0:
        sys.exit(1)

def run_test(algorithm, language, args) -> bool:
    ret = subprocess.run(
        args,
        cwd=os.path.join(algorithm, language),
        capture_output=True,
    )
    if ret.returncode != 0:
        print("FAIL")
        print(f"       COMMAND: {" ".join(ret.args)}")
        print("       STDOUT:")
        for line in ret.stdout.decode("utf-8").replace("\r", "").split("\n"):
            print(f"           {line}")
        print("       STDERR:")
        for line in ret.stderr.decode("utf-8").replace("\r", "").split("\n"):
            print(f"           {line}")
    return ret.returncode == 0

def get_ignored_dirs() -> list[str]:
    ignored_dirs = [".github"]
    with open(".gitignore", "r") as file:
        ignored_dirs.extend(
            map(
                lambda line: line.rstrip("/"),
                filter(
                    lambda line: line.endswith("/"),
                    map(
                        lambda line: line.rstrip("\r\n"),
                        file.readlines()
                    )
                )
            )
        )
    return ignored_dirs


if __name__ == '__main__':
    main()
