#include <iostream>
#include <stdint.h>
#include <string.h>

using namespace std;

class StreamAddr
 {
 private:
     char id_[64];        //‘∆ ”Õ®id
     char ip_[16];        
     char name_[64];
     uint32_t channel_;
 
     StreamAddr(const StreamAddr& );
     void operator=(const StreamAddr& );
 public:
     StreamAddr(char *id, char *ip, char *name, uint32_t channel)
     {
         memcpy(id_, id, 64);
         memcpy(ip_, ip, 16);
         memcpy(name_, name, 64);
         channel_ = channel;
     }
};

int main()
{
    int size = 0;

    cout << "sizeof class StreamAddr is " << sizeof(StreamAddr) << endl;
}


