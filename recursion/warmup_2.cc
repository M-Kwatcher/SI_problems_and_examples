#include <iostream>

using namespace std;

int something{42};

void printSomething(){
    
    cout << something << "\n";
}

int main(){

    for(int i = 1; i <= 10; i++){
        if(something == i){
            cout << "something: " << something << "\n";
        }
        cout << "i: " << i << "\n";
    }

    return 0;
}

