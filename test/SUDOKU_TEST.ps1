
pushd
cd C:\3ds_dev\Sudoku3DS
gcc -DSUDOKU_TEST -I .\include\ .\source\sudoku.c .\source\mylib.c -o .\test\exe\sudoku_test
.\test\exe\sudoku_test.exe
popd

