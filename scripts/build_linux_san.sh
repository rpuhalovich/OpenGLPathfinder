cd $(dirname $0)
cmake -S .. -B ../build -DCMAKE_CXX_FLAGS="-fsanitize=address -fsanitize=leak -g"
