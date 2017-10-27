/* This program is just a copy of sample_1.dsl. 
You should write your FCAL program to multiply two
2-dimensional matrices and save it
in a file with this name. */

main () { 

  matrix l = matrix_read ( "./samples/my_code_1.data" ) ;
  matrix m = matrix_read ( "./samples/sample_8.data" ) ;
  matrix ans = l * m ;
  
  print ( l ) ;
  print ( m ) ;
  print ( ans ) ;
}



