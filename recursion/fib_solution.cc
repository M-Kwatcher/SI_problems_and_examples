#include <iostream>


int fibonacci(int n){
    if (n == 0){
        return 0;
    }
    if (n == 1){
        return 1;
    }

    return fibonacci(n-1) + fibonacci(n-2);
}



int main(){
    int count = 8;


    std::cout << "Fibonacci sequence up to " << count << " \n";

    for(int i = 0; i < count; i++){
        std::cout << fibonacci(i) << " ";
    }
    std::cout << "\n";

    return 0;
}