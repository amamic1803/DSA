import os
import sys
import subprocess


def main():
    ignored_dirs = get_ignored_dirs()
    verbose = len(sys.argv) > 1 and (sys.argv[1] == "-v" or sys.argv[1] == "--verbose")

    print("Running tests...\n")

    succeeded = 0
    failed = 0

    for (i, algorithm) in enumerate(filter(lambda x: os.path.isdir(x) and x not in ignored_dirs, sorted(os.listdir()))):
        print(f"#{i + 1:02d} {algorithm}")
        for (j, language) in enumerate(filter(lambda x: os.path.isdir(os.path.join(algorithm, x)) and x not in ignored_dirs, sorted(os.listdir(algorithm)))):
            print(f"    {chr(ord('a') + j)}) {language.ljust(10)} ... ", end="")
            sys.stdout.flush()
            path = os.path.join(algorithm, language)

            match language:
                case "C" | "C++":

                    if not run_test(algorithm, language, path, [
                        "cmake",
                        "-DCMAKE_C_COMPILER=gcc",
                        "-DCMAKE_CXX_COMPILER=g++",
                        "-DCMAKE_BUILD_TYPE=Release",
                        "-G", "Ninja",
                        "-S", ".",
                        "-B", "cmake-build-release-gcc"
                    ], verbose):
                        failed += 1
                        continue
                    path_build = os.path.join(path, "cmake-build-release-gcc")
                    if not run_test(algorithm, language, path_build, ["cmake", "--build", "."], verbose):
                        failed += 1
                        continue
                    if not run_test(algorithm, language, path_build, ["ctest"], verbose):
                        failed += 1
                        continue

                    if not run_test(algorithm, language, path, [
                        "cmake",
                        "-DCMAKE_C_COMPILER=clang",
                        "-DCMAKE_CXX_COMPILER=clang++",
                        "-DCMAKE_BUILD_TYPE=Release",
                        "-G", "Ninja",
                        "-S", ".",
                        "-B", "cmake-build-release-clang"
                    ], verbose):
                        failed += 1
                        continue
                    path_build = os.path.join(path, "cmake-build-release-clang")
                    if not run_test(algorithm, language, path_build, ["cmake", "--build", "."], verbose):
                        failed += 1
                        continue
                    if not run_test(algorithm, language, path_build, ["ctest"], verbose):
                        failed += 1
                        continue

                    print("OK")
                    succeeded += 1

                case "Python":
                    if not run_test(algorithm, language, path, ["ruff", "check", "."], verbose):
                        failed += 1
                        continue
                    if not run_test(algorithm, language, path, ["python", "-m", "unittest"], verbose):
                        failed += 1
                        continue
                    print("OK")
                    succeeded += 1

                case "Rust":
                    if not run_test(algorithm, language, path, ["cargo", "clippy", "--all-features", "--", "-D", "warnings"], verbose):
                        failed += 1
                        continue
                    if not run_test(algorithm, language, path, ["cargo", "fmt", "--all", "--check"], verbose):
                        failed += 1
                        continue
                    if not run_test(algorithm, language, path, ["cargo", "build", "--all-features"], verbose):
                        failed += 1
                        continue
                    if not run_test(algorithm, language, path, ["cargo", "test", "--all-features"], verbose):
                        failed += 1
                        continue
                    if not run_test(algorithm, language, path, ["cargo", "doc", "--all-features"], verbose):
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

def run_test(algorithm, language, path, args, verbose) -> bool:
    ret = subprocess.run(
        args,
        cwd=path,
        capture_output=True,
    )
    if ret.returncode != 0:
        print("FAIL")
    if verbose or ret.returncode != 0:
        print(f"### {algorithm}/{language}", file=sys.stderr)
        print(f"COMMAND: {" ".join(ret.args)}", file=sys.stderr)
        print("STDOUT:", file=sys.stderr)
        for line in ret.stdout.decode("utf-8").replace("\r", "").split("\n"):
            print(f"    {line}", file=sys.stderr)
        print("STDERR:", file=sys.stderr)
        for line in ret.stderr.decode("utf-8").replace("\r", "").split("\n"):
            print(f"    {line}", file=sys.stderr)
        print("\n\n", file=sys.stderr)
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
