#include <iostream>
#include <fstream>
#include "Person.pb.h"

using namespace std;

int main()
{
    {
        Person person;
        person.set_name("houbin");
        person.set_id(1234);

        person.set_email("houbin0504@163.com");

        fstream output("myfile", ios::out|ios::binary);
        person.SerializeToOstream(&output);
    }

    {
        fstream input("myfile", ios::in|ios::binary);
        Person person;
        person.ParseFromIstream(&input);
        cout << "name " << person.name() << endl;
        cout << "E-mail " << person.email() << endl;
    }

    return 0;
}
