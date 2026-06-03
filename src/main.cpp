// #include "network.hpp"
#include "vector.hpp"
#include <iostream>
#include <fstream>
#include <string>

int main()
{
    ifstream file("../docs/miniref.json");
    if (!file)
    {
        cerr << "Failled to open references file, Aborting.";
        exit(1);
    }

    string content((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    const char* json_dict = content.c_str();


    Vector* data = references_parser(json_dict);
    for(int i = 0; i < 10; i++){
        Vector v = data[i];
    }

    if (data[5].label == 'n')
    {
        cout << "que pouca vergonha";
    };

    //serve();
    return 0;
}
