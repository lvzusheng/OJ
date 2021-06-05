#include <stdio.h>
#include <malloc.h>
#include <uthash.h>

struct ListNode {
    int val;
    struct ListNode* next;
};

typedef struct
{
    int node;
    UT_hash_handle hh;
}Hash;

void HashSet(Hash** hash, int node)
{
    Hash* tmp = NULL;
    HASH_FIND_INT(*hash, &node, tmp);
    if (tmp == NULL) {
        tmp = (Hash*)malloc(sizeof(Hash));
        tmp->node = node;
        HASH_ADD_INT(*hash, node, tmp);
    }
}
void PrintHash(Hash* hash)
{
    for (; hash != NULL; hash = hash->hh.next) {
        printf("%d\n", hash->node);
    }
}

struct ListNode* getIntersectionNode(struct ListNode* headA, struct ListNode* headB)
{
    Hash* hash = NULL;
    while (headA != NULL) {
        HashSet(&hash, (int)headA);
        headA = headA->next;
    }
    while (headB != NULL) {
        Hash* tmp = NULL;
        HASH_FIND_INT(hash, &(int)headB, tmp);
        if (tmp != NULL) {
            return headB;
        }
        headB = headB->next;
    }
    return NULL;
}

int main()
{
    struct ListNode node1[5] = { 0 };
    struct ListNode node2[3] = { 0 };
    struct ListNode* ret = NULL;
    node1[0].val = 4;
    node1[1].val = 1;
    node1[2].val = 8;
    node1[3].val = 4;
    node1[4].val = 5;
    node2[0].val = 5;
    node2[1].val = 6;
    node2[2].val = 1;
    for (int i = 0; i < 4; i++) {
        node1[i].next = &node1[i + 1];
    }
    node2[0].next = &node2[1];
    node2[1].next = &node2[2];
    node2[2].next = &node1[3];
    ret = getIntersectionNode(node1, node2);
    if (ret != NULL)
        printf("%d\n", ret->val);
    else
        printf("NULL\n");
    return 0;
}
