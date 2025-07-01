mk() { local F="$1" ; shift ; g++ "$F.cpp" -o "$F" "$@"; }
hash() {
cpp -fpreprocessed -P "$1" | python3 -c '
import hashlib, re, sys
for i in sys.stdin.readlines():
    print(hashlib.md5(re.sub(r"\s", "", i).encode()).hexdigest()[:4], i[:-1])
'
}
ulimit -s 1048576
ulimit -v 1048576
export CXXFLAGS='-g -Wall -Wextra -fsanitize=address,undefined -std=c++20'
