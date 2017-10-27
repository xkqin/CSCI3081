/* This program is just a copy of sample_1.dsl.
You should write your second interesting FCAL
program and save it in a file with this name.

Good showcase for while loop and !, neither of which
have been tested by any previous sample .dsl files. */

main () {
  int x;
  x = 0 ;
  int y;

  while(y != 20) {
    print(y) ;
    print("\n") ;
    x = x + y ;
    y = y + 1;
  }
  print(x) ;
  print("\n") ;

}
