import os

# Compile all of our tests
os.system('clang tests/test1.c -o tests/test1')
os.system('clang tests/test2.c -o tests/test2')
os.system('clang tests/test3.c -o tests/test3')

# (Optional)
# Make sure my tests do not have memory leaks
# Valgrind also has helpful information
# about how many allocs and frees took place
# os.system('valgrind ./tests/test1')
# os.system('valgrind ./tests/test2')
# os.system('valgrind ./tests/test3')

# Compile our malloc program
os.system('clang -c mymalloc.c')


# Compile our tests with our custom allocator
os.system('clang -I. -o ./tests/test1_mymalloc ./tests/test1.c mymalloc.o')
os.system('clang -I. -o ./tests/test2_mymalloc ./tests/test2.c mymalloc.o')
os.system('clang -I. -o ./tests/test3_mymalloc ./tests/test3.c mymalloc.o')
