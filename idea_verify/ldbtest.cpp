#include <iostream>
#include "leveldb/db.h"
#include <stdio.h>
#include <stdlib.h>
using namespace std;
using namespace leveldb;

int main()
{
    int ret;
    DB *db;
    struct Options op;
    op.create_if_missing = true;
    Status s = DB::Open(op, "/tmp/testdb", &db);
    char *value = (char *)malloc(1024 * 1024);
    if (value == NULL)
    {
        cout << "malloc error" << endl;
        return -1;
    }
    memset(value, 0, 1024*1024);

    if (s.ok())
    {
        cout << "create db successfully!"<<endl;

        int i = 0;
        for (i = 0; i < 50; i++)
        {
            char temp[10] = {0};
            sprintf(temp, "%d", i);
            s = db->Put(WriteOptions(), temp, value);
            if (s.ok())
            {
                cout << "put " << temp << " successful" << endl;
            }
            else
            {
                cout << "put " << temp << " failed" << endl;
            }
        }

        Iterator *iter = db->NewIterator(ReadOptions());
        for (iter->SeekToFirst(); iter->Valid(); iter->Next())
        {
            cout << "key is " << iter->key().data() << ", value is " << iter->value().data() << endl;
            iter->Next();
        }
        delete iter;
    }
    else
    {
        cout << "create failed " << endl;
    }

    delete db;
    return 0;
}
