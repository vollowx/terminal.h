mkdir -p build

demo=$1
main="./demos/$demo/main.cpp"
append=$(cat ./demos/$demo/append.txt | sed 's/^/.\/demos\/'$demo'\//')

succeeded=$(clang++ -std=c++17 -o ./build/$demo $main $append)

if [ $? -eq 0 ]; then
  ./build/$demo
else
  echo 'compilation failed'
fi
