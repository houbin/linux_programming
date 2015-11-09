#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <boost/shared_ptr.hpp>

using namespace boost;

class Test
{
public:
    Test()
    {
        printf("Test\n");
    }
    ~Test()
    {
        printf("~Test\n");
    }
};

void *ThreadFunc(void *arg)
{
    shared_ptr<Test> t = (shared_ptr<Test>)arg;
    printf("2, test count is %d\n", t.use_count());

    return 0;
}

int main()
{
    pthread_t pid;
    pthread_attr_t *attr = NULL;

    shared_ptr<Test> test(new Test);
    printf("1, test count is %d\n", test.use_count());

    pthread_create(&pid, attr, ThreadFunc, (void *)test);
    pthread_detach(pid);

    sleep(10);
    printf("3, test count is %d\n", test.use_count);

    return 0;
}
