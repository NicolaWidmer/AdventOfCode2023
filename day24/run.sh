g++ -std=c++20 main.cpp -o main -lz3 -L /Users/Nicola/git/z3/build
cat in.txt | ./main
rm ./main