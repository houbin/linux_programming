#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include <string.h>

struct student
{
    int age;
    char name[10];
    struct ListHead list;
};

int main()
{
    struct student stu;
    struct student *pstu;
    struct ListHead *pos;
    struct ListHead *n;
    int i = 0;

    INIT_LIST_HEAD(&(stu.list));
    
    for (i = 0; i < 10; i++)
    {
        pstu = (struct student *)malloc(sizeof(struct student));
        pstu->age = i;

        memset(pstu->name, 0, 10);
        sprintf(pstu->name, "student %", i);

        ListAddTail(&(stu.list), &(pstu->list));
    }

    printf("list each ====================\n");
    ListForEach(pos, &stu.list)
    {
        pstu = container_of(pos, struct student, list);
        printf("%s: age is %d\n", pstu->name, pstu->age);
    }

    printf("del age = 3 ==================\n");
    ListForEachSafe(pos, n, &stu.list)
    {
        pstu = container_of(pos, struct student, list);
        if (pstu->age == 3)
        {
            ListDel(pos);
            free(pstu);
        }
    }

    printf("list each again ====================\n");
    ListForEach(pos, &stu.list)
    {
        pstu = container_of(pos, struct student, list);
        printf("%s: age is %d\n", pstu->name, pstu->age);
    }

    printf("release resource =================\n");
    ListForEachSafe(pos, n, &stu.list)
    {
        pstu = container_of(pos, struct student, list);
        ListDel(pos);
        free(pstu);
    }

    return 0;
}
