#include <string>
#include <iostream>

class VECTOR3
{
public:
    VECTOR3()
       :x(0.0f),y(0.0f),z(0.0f)
    {
       std::cout<<"VECTOR3 Default Constructor "
               <<std::endl;
    }
 
    VECTOR3(float fx, float fy, float fz)
       :x(0.0f),y(0.0f),z(0.0f)
    {
       std::cout<<"VECTOR3 Parameter Constructor "
               <<std::endl;
    }
 
    VECTOR3(const VECTOR3& rht)
       :x(rht.x), y(rht.y), z(rht.z)
    {
       std::cout<<"VECTOR3 Copy Constructor "
           <<std::endl;
    }
 
    ~VECTOR3()
    {
       std::cout<<"VECTOR3 Destructor "
               <<std::endl;
    }
 
    VECTOR3& operator = (const VECTOR3& rht)
    {
       if( &rht == this )
           return *this;
 
       x = rht.x;
       y = rht.y;
       z = rht.z;
 
       std::cout<<"VECTOR3 operator = left oper : "
               <<std::endl;
 
       return *this;
    }
    float x;
    float y;
    float z;
};
 
VECTOR3 Func1()
{
    return VECTOR3(1.0f, 1.0f, 1.0f);
}
 
VECTOR3 Func2()
{
    VECTOR3 ret;
    ret.x = 2.0f;
    ret.y = 2.0f;
    ret.z = 2.0f;
    return ret;
}
 
 
int main()
{
VECTOR3 v1 = Func1();
    v1 = Func1();
 
VECTOR3 v2 = Func2();
        
VECTOR3 v3;
v3 = Func2();

VECTOR3 v4;
VECTOR3 v5 = v4;
}
