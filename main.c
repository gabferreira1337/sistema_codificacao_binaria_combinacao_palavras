#include <stdio.h>
#include "functions/functions_1.h"
#include "test_functions/test_functions_1.h"
#include "functions/functions_2.h"

int main(int argc, char **argv) {

    //main_functions_1(argc,argv);
    //main_test_functions_1(argc, argv);
    main_functions_2(argc,argv);

    main_functions_1(argc,argv);
  
    main_functions_2(argc,argv);
  
    return 0;
}
