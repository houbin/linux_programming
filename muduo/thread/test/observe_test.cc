#include <vector>
#include <stdio.h>

using namespace std;

class Observable;
class Observer
{
public:
    ~Observer();
    virtual void Update() = 0;

    void Observe(Observable *s);

private:
    Observable *subject_;
};

class Observable
{
public:
    void Register(Observer *x)
    {
        observers_.push_back(x);
    }

    void UnRegister(Observer *x)
    {
        vector<Observer*>::iterator iter = observers_.begin();
        for (; iter != observers_.end(); iter++)
        {
            if (*iter == x)
            {
                observers_.erase(iter);
                break;
            }
        }
    }

    void NotifyObserver()
    {
        vector<Observer*>::iterator iter = observers_.begin();
        for (; iter != observers_.end(); iter++)
        {
            Observer *ob = *iter;
            ob->Update();
        }
    }

private:
    vector<Observer*> observers_;
};

Observer::~Observer()
{
    subject_->UnRegister(this);
}

void Observer::Observe(Observable *s)
{
    s->Register(this);
    subject_ = s;
}

class Foo : public Observer
{
public:
    void Update()
    {
        printf("Foo::Update() %p\n", this);
    }
};

int main()
{
    Foo *p = new Foo;
    Observable subject;

    p->Observe(&subject);

    subject.NotifyObserver();
    delete p;
    subject.NotifyObserver();

    return 0;
}

