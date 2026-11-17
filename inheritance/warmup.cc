#include <iomanip>

void print_from(int input){
    std::cout << "print_from(" << input << "): " << "\n";
    print_from(input - 1);
}

int main(){
    int a{5.5};

    std::cout << "a: " << a << "\n";
    
    print_from(a);
    
    return 0;
}