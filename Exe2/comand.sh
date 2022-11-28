#!/bin/bash
echo "rm *.gcda *.gcno *.gcov"
rm *.gcda *.gcno *.gcov
echo "gcc --coverage -o tc id-list.c scan-list.c pprinter-list.c token-list.h ebnf-list.c" 
gcc --coverage -o tc id-list.c scan-list.c pprinter-list.c pprinter-list.h ebnf-list.c
echo "./tc sample2a.mpl" 
./tc sample2a.mpl
echo "./tc sample02a.mpl" 
./tc sample02a.mpl
echo "./tc sample21.mpl"
./tc sample21.mpl
echo "./tc sample021.mpl"
./tc sample021.mpl
echo "./tc sample022.mpl" 
./tc sample022.mpl
echo "./tc sample22.mpl" 
./tc sample22.mpl
echo "./tc sample23.mpl" 
./tc sample23.mpl
echo "./tc sample023.mpl" 
./tc sample023.mpl
echo "./tc sample024.mpl" 
./tc sample024.mpl
echo "./tc sample24.mpl" 
./tc sample24.mpl
echo "./tc sample25.mpl" 
./tc sample25.mpl
echo "./tc sample025.mpl"
./tc sample025.mpl
echo "./tc sample025t.mpl"
./tc sample025t.mpl
echo "./tc sample25t.mpl"
./tc sample25t.mpl
echo "./tc sample26.mpl"
./tc sample26.mpl
echo "./tc sample026.mpl"
./tc sample026.mpl
echo "./tc sample026t.mpl"
./tc sample026t.mpl
echo "./tc sample27.mpl"
./tc sample27.mpl
echo "./tc sample28p.mpl"
./tc sample28p.mpl
echo "./tc sample028p.mpl"
./tc sample028p.mpl
echo "./tc sample028q.mpl"
./tc sample028q.mpl
echo "./tc sample028r.mpl"
./tc sample028r.mpl
echo "./tc sample29p.mpl"
./tc sample29p.mpl
echo "./tc sample029p.mpl"
./tc sample029p.mpl
echo "./tc sample029q.mpl"
./tc sample029q.mpl
echo "./tc sample029r.mpl"
./tc sample029r.mpl
echo "./tc sample029s.mpl"
./tc sample029s.mpl
echo "./tc sample029t.mpl"
./tc sample029t.mpl
echo "test1.mpl"
./tc test1.mpl
echo "test2.mpl"
./tc test2.mpl
echo "test3.mpl"
./tc test3.mpl
echo "test4.mpl"
./tc test4.mpl
echo "test5.mpl"
./tc test5.mpl
echo "test6.mpl"
./tc test6.mpl
echo "test7.mpl"
./tc test7.mpl
echo "test8.mpl"
./tc test8.mpl
echo "test9.mpl"
./tc test9.mpl
echo "test10.mpl"
./tc test10.mpl
echo "test11.mpl"
./tc test11.mpl
echo "test12.mpl"
./tc test12.mpl
echo "test13.mpl"
./tc test13.mpl
echo "test14.mpl"
./tc test14.mpl
echo "test15.mpl"
./tc test15.mpl
echo "test16.mpl"
./tc test16.mpl
echo "tb1.mpl"
./tc tb1.mpl
echo "tb2.mpl"
./tc tb2.mpl
echo "tb3.mpl"
./tc tb3.mpl
echo "tb4.mpl"
./tc tb4.mpl
echo "tb5.mpl"
./tc tb5.mpl
echo "tb6.mpl"
./tc tb6.mpl
echo "tb7.mpl"
./tc tb7.mpl
echo "tb8.mpl"
./tc tb8.mpl
echo "tb9.mpl"
./tc tb9.mpl
echo "tb10.mpl"
./tc tb10.mpl
echo "tb11.mpl"
./tc tb11.mpl
echo "tb12.mpl"
./tc tb12.mpl
echo "tb13.mpl"
./tc tb13.mpl
echo "tb14.mpl"
./tc tb14.mpl
echo "tb15.mpl"
./tc tb15.mpl
echo "tb16.mpl"
./tc tb16.mpl
echo "tb17.mpl"
./tc tb17.mpl
echo "tb18.mpl"
./tc tb18.mpl
echo "tb19.mpl"
./tc tb19.mpl
echo "tb20.mpl"
./tc tb20.mpl
echo "tb21.mpl"
./tc tb21.mpl
echo "tb22.mpl"
./tc tb22.mpl
echo "tb23.mpl"
./tc tb23.mpl
echo "tt1.mpl"
./tc tt1.mpl
echo "tt2.mpl"
./tc tt2.mpl
echo "tt3.mpl"
./tc tt3.mpl
echo "tt4.mpl"
./tc tt4.mpl
echo "tt5.mpl"
./tc tt5.mpl
echo "tt6.mpl"
./tc tt6.mpl
echo "tt7.mpl"
./tc tt7.mpl
echo "ta1.mpl"
./tc ta1.mpl
echo "ta2.mpl"
./tc ta2.mpl
echo "ta3.mpl"
./tc ta3.mpl
echo "ta4.mpl"
./tc ta4.mpl
echo "ta5.mpl"
./tc ta5.mpl
echo "ta6.mpl"
./tc ta6.mpl
echo "ta7.mpl"
./tc ta7.mpl
echo "ta8.mpl"
./tc ta8.mpl
echo "ta9.mpl"
./tc ta9.mpl
echo "ta10.mpl"
./tc ta10.mpl
echo "ta11.mpl"
./tc ta11.mpl
echo "ta12.mpl"
./tc ta12.mpl
echo "tm1.mpl"
./tc tm1.mpl
echo "tm2.mpl"
./tc tm2.mpl
echo "tm3.mpl"
./tc tm3.mpl
echo "tm4.mpl"
./tc tm4.mpl
echo "gcov -b ebnf-list.gcda" 
gcov -b ebnf-list.gcda