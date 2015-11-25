#include <vector>
#include <stdio.h>
#include <boost/enable_shared_from_this.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>

using namespace boost;
using namespace std;

class Observable;
class Observer : public enable_shared_from_this<Observer>
{
public:
    virtual void Update() = 0;
    void Observe(Observable *s);

private:
    Observable *subject_;
};

class Observable
{
public:
    void Register(weak_ptr<Observer> x)
    {
        observers_.push_back(x);
    }

    void NotifyObservers()
    {
        Iterator iter = observers_.begin();
        while (iter != observers_.end())
        {
            shared_ptr<Observer> obj(iter->lock());
            if (obj)
            {
                obj->Update();
                iter++;
            }
            else
            {
                printf("NotifyObserver erased\n");
                iter = observers_.erase(iter);
            }
        }
    }

private:
    vector<weak_ptr<Observer> > observers_;
    typedef vector<weak_ptr<Observer> >::iterator Iterator;
};

void Observer::Observe(Observable *x)
{
    x->Register(weak_from_this());
    subject_ = x;
}

class Foo : public Observer
{
public:
    void Update()
    {
        printf("Foo::Update, %p\n", this);
    }
};

int main()
{
    Observable subject;

    {
        shared_ptr<Foo> p(new Foo);
        p->Observe(&subject);

        subject.NotifyObservers();
    }

    subject.NotifyObservers();

    return 0;
}

