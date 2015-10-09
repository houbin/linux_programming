#include <stdlib.h>
#include <stdio.h>

#define offsetof(TYPE, MEMBER) ((size_t) &(((TYPE *)0)->MEMBER))

struct student
{
    char gender;
    char grade;
    char prize;
    int id;
    char swimming;
    int age;
    char name[20];
};

int main()
{
    struct student xiaoming;

    printf("offset of gender is %d\n", offsetof(struct student, gender));
    printf("offset of grade is %d\n", offsetof(struct student, grade));
    printf("offset of prize is %d\n", offsetof(struct student, prize));
    printf("offset of id is %d\n", offsetof(struct student, id));
    printf("offset of swimming is %d\n", offsetof(struct student, swimming));
    printf("offset of age is %d\n", offsetof(struct student, age));
    printf("offset of name is %d\n", offsetof(struct student, name));

    return 0;
}
