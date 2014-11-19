#ifndef _LIST_H_
#define _LIST_H_

struct ListHead
{
    struct ListHead *pre;
    struct ListHead *next;
};

static inline void INIT_LIST_HEAD(struct ListHead *list)
{
    list->pre = list;
    list->next = list;
}

static inline void _ListAdd(struct ListHead *pre, struct ListHead *next, struct ListHead *add)
{
    add->next = next;
    add->pre = pre;
    pre->next = add;
    next->pre = add;
}

static inline void ListAdd(struct ListHead *list, struct ListHead *add)
{
    _ListAdd(list, list->next, add);
}

static inline void ListAddTail(struct ListHead *list, struct ListHead *add)
{
    _ListAdd(list->pre, list, add);
}

static inline void _ListDel(struct ListHead *pre, struct ListHead *next)
{
    pre->next = next;
    next->pre = pre;
}

static inline void ListDel(struct ListHead *entry)
{
    _ListDel(entry->pre, entry->next);
}

static inline void ListDelInit(struct ListHead *entry)
{
    ListDel(entry);
    INIT_LIST_HEAD(entry);
}

#define offsetof(TYPE, MEMBER) ((size_t) &(((TYPE*)0)->MEMBER))

#define container_of(ptr, type, member) ({ \
    const typeof(((type *)0)->member) *__mptr = ptr; \
    (type *)((char *)__mptr - offsetof(type, member)); \
})

#define ListForEach(pos, list) \
        for(pos = (list)->next; pos != list; pos = pos->next)

#define ListForEachSafe(pos, n, list) \
        for (pos = (list)->next, n = pos->next; pos != list; pos = n, n = pos->next)

#define ListEntry(ptr, type, member) \
        container_of(ptr, type, member)

#endif
