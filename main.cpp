#include <iostream>
#include "Data.cpp"
void input();
void output();

int main() {
    std::cout << "Hello, World!" << std::endl;
    input();
    output();
    return 0;
}

void input(){
    data prop;

    std::cout << "Please input number of line" << std::endl;
    std::cin >> prop.ID;

    std::cout << "Please input name of product" << std::endl;
    std::cin >> prop.name;

    std::cout << "Please write description" << std::endl;
    std::cin >> prop.description;

    FILE *file;
    if((file = fopen("data", "a+"))!= nullptr){
        fprintf(file, "%d", prop.ID);           // Puts an int value into file
        fputs(prop.name, file);                 // Puts a char array into file
        fputs(prop.description, file);          // Puts a char array into file
    }
    fclose(file);
}

void output(){
    data prop;
    FILE *file;
    char string[100];
    if((file = fopen("data", "r"))!= nullptr){
        std::cout << fgets(string, 40, file) << std::endl;
    }
    fclose(file);
}