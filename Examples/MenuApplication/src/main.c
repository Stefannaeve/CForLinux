#include "menuApplication.h"
#include "linkedList.h"
#include "string.h"

int main(){
    int status = menuApplication();
    if(status != 0){
        return 1;
    }
    return 0;


}