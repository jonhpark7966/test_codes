echo " ---------------------------------------"
echo " ------------ basic tests --------------"
echo " ---------------------------------------"
echo ""

# build/basic library a
gcc -c -Wall -Werror -fpic src/basic/a.c -o build/basic/a.o
gcc -shared -o build/basic/liba.so build/basic/a.o
echo " --- liba.so is built."

# build/basic library b
gcc -c -Wall -Werror -fpic src/basic/b.c -o build/basic/b.o
gcc -shared -o build/basic/libb.so build/basic/b.o
echo " --- libb.so is built."

# build/basic test1 
gcc -Wall -o build/basic/test1 src/basic/test1.c -lb -la -L./build/basic
echo " --- test1 is built."

# run test1
LD_LIBRARY_PATH=./build/basic ./build/basic/test1
echo " --- test1 tested."

# build/basic library c
gcc -c -Wall -Werror -fpic src/basic/c.c -o build/basic/c.o
gcc -shared -la -lb -L./build/basic -o build/basic/libC.so build/basic/c.o
echo " --- libC.so is built."

# build/basic test2
gcc -Wall -o build/basic/test2 src/basic/test2.c -lC -la -L./build/basic
echo " --- test2 is built."

# run test
LD_LIBRARY_PATH=./build/basic ./build/basic/test2
echo " --- test2 tested."

# build/basic test3
gcc -Wall -o build/basic/test3 src/basic/test3.c -ldl
echo " --- test3 is built."

# run test
LD_LIBRARY_PATH=./build/basic ./build/basic/test3
echo " --- test3 tested."





echo ""
echo " ---------------------------------------"
echo " ---------- circular tests -------------"
echo " ---------------------------------------"
echo ""

# build/circular library a
gcc -g -c -Wall -Werror -fpic src/circular/a.c -o build/circular/a.o
gcc -shared -o build/circular/liba.so build/circular/a.o
echo " --- liba.so is built."

# build/circular library b
gcc -g -c -Wall -Werror -fpic src/circular/b.c -o build/circular/b.o
gcc -shared -o build/circular/libb.so build/circular/b.o
echo " --- libb.so is built."

# build/circular test1 
gcc -g -Wall -o build/circular/test1 src/circular/test1.c -la -lb -L./build/circular
echo " --- test1 is built."

# run test1
LD_LIBRARY_PATH=./build/circular ./build/circular/test1
echo " --- test1 tested."
