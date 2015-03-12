#include <iostream>

using namespace std;

struct Test
{
    int a_;

    Test(int a) : a_(a) {}
};

typedef struct frag_info
{
    int a_;
}FRAG_INFO;

int main()
{
    FRAG_INFO *f = new FRAG_INFO;
    f->a_ = 55;
    
    cout << "a_ of f is " << f->a_ << endl;
    return 0;
}
