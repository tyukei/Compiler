#!/bin/bash
echo "rm *.gcda *.gcno *.gcov"
rm *.gcda *.gcno *.gcov
echo "gcc --coverage -o tc id-list.c scan-list.c token-list.c token-list.h" 
gcc --coverage -o tc id-list.c scan-list.c token-list.c token-list.h
echo "./tc sample11pp.mpl" 
./tc sample11pp.mpl
echo "./tc test000.mpl"
./tc test000.mpl
echo "./tc test00.mpl"
./tc test00.mpl
echo "./tc test01.mpl"
./tc test01.mpl
echo "./tc test02.mpl"
./tc test02.mpl
echo "./tc test03.mpl"
./tc test03.mpl
echo "./tc test04.mpl"
./tc test04.mpl
echo "./tc test05.mpl"
./tc test05.mpl
echo "./tc test06.mpl"
./tc test06.mpl
echo "./tc test07.mpl"
./tc test07.mpl
echo "gcov -b scan-list.gcda" 
gcov -b scan-list.gcda