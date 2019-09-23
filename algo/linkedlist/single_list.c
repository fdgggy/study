#include <stdio.h>
#include <stdbool.h>

struct single_list {
    struct single_list *next;
    int val;
};

struct single_list_head {
    struct single_list *head;
};

void dump(struct single_list_head *head) {
    if (!head) {
        printf("the single_list head is null\n");
        return;
    }
    int idx = 0;
    for (struct single_list *temp = head->head; temp != NULL; temp = temp->next) {
        printf("idx:%d val :%d\n", idx++, temp->val);
    }
}

//头插法
void insert(struct single_list **prev, struct single_list *elem) {
    if (!elem) {
        printf("insert failed, elem is null\n");
        return;
    }
    if (!prev) {
        printf("insert failed, prev is null\n");
        return;
    }

    if (*prev) {  //有头结点
        elem->next = *prev;
    }
    *prev = elem;  //有无头结点
}
//头插法  A->B->C
void insert_head(struct single_list_head *head, struct single_list *elem) {
    insert(&head->head, elem);
}

struct single_list* del(struct single_list **prev) {
    struct single_list* temp = NULL;

    if (!prev) {
        printf("del failed, prev is null\n");
        return NULL;
    }
    if (!*prev) {
        printf("del failed, *prev is null\n");
        return NULL;
    }   

    temp = *prev;
    *prev = (*prev)->next;
    temp->next = NULL;

    return temp;
}

struct single_list* delete_head(struct single_list_head *head) {
    return del(&head->head);
}

struct single_list* search(struct single_list_head *head, int target) {
    struct single_list* temp;

    for (temp = head->head; temp && temp->val != target; temp = temp->next);

    return temp;
}

//A->B->C  A<-B<-C
void reverse(struct single_list_head *head) {
    if (!head->head) {
        printf("reverse failed\n");
        return;
    }

    struct single_list* temp = head->head;
    struct single_list* post1 = temp->next;
    temp->next = NULL;

    struct single_list* post2 = NULL;

    while(post1) {
        post2 = post1->next;
        post1->next = temp;
        temp = post1;
        post1 = post2;
    }

    head->head = temp;
}

//A->B->C  A<-B<-C
void reverse2(struct single_list_head *head) {
    struct single_list* prev = NULL;
    struct single_list* next = NULL;

    while(head->head) {
        next = head->head->next;
        head->head->next = prev;
        prev = head->head;
        head->head = next;
    }

    head->head = prev;
}

struct single_list* rever(struct single_list* head) {
    if (head == NULL || head->next == NULL) {
        return head;
    }
    struct single_list* temp = rever(head->next);
    head->next->next = head; //回溯
    head->next = NULL;

    return temp;
}

//A->B->C  A<-B<-C
void reverse3(struct single_list_head *head) {
    head->head = rever(head->head);
}
//链表的尾结点指向了链表中的某个结点
//a->b->c->a
//a->b->c->b
bool is_cyclic(struct single_list_head *head) {
    struct single_list* p1 = head->head;
    struct single_list* p2 = head->head;

    while(p1 && p2) {
        if (p2->next == NULL) {
            return false;
        }
        p1 = p1->next;
        p2 = p2->next->next;
        if (p1 == p2) {
            return true;
        }
    }
    return false;
}

//A->B->C->D
struct single_list *middle(struct single_list_head *head) {
    struct single_list* p1 = head->head;
    struct single_list* p2 = head->head;
    while(p1 && p2) {
        if (!p2->next) {
            return p1;
        }
        p1 = p1->next;
        p2 = p2->next->next;
    }
    return p1;
}

//删除倒数第n个元素, 从1开始计数，不是倒数第0个
//A->B->C->D->E->F
void delback_index(struct single_list_head *head, int n) {
    struct single_list* p1 = head->head;
    struct single_list* p2 = head->head;
    if (n < 0) {
        printf("delback_index failed, invalid index\n");
        return;
    }

    while(n-- != 0) {
        if (!p1) {
            printf("delback_index failed, invalid index\n");
            return;
        }
        p1 = p1->next;
    }
    if (!p1) {
        head->head = head->head->next;
        return;
    }

    while(p1->next) {
        p1 = p1->next;
        p2 = p2->next;
    }

    p2->next = p2->next->next;
}

int main() {
    struct single_list_head head = {};
    struct single_list lists[10];
    for (int idx = 0; idx < 10; idx++) {
        lists[idx].val = idx;
        lists[idx].next = NULL;
    }
    insert_head(&head, &lists[1]);
    insert_head(&head, &lists[2]);
    insert_head(&head, &lists[3]);
    insert_head(&head, &lists[4]);
    insert_head(&head, &lists[5]);
    insert_head(&head, &lists[6]);


    dump(&head);
    printf("delete head\n");
    delete_head(&head);
    dump(&head);

    struct single_list* node;
    node = search(&head, 1);
    printf("node val:%d\n", node->val);

    printf("reverse 1\n");
    dump(&head);
    reverse3(&head);
    printf("reverse 2\n");
    dump(&head);

    reverse3(&head);
    printf("reverse 3\n");
    dump(&head);

    printf("midele %d\n", middle(&head)->val);

    // lists[1].next = &lists[3];
    printf("list is%s cyclic\n", is_cyclic(&head)?"": " not");

    printf("del befor\n");
    dump(&head);
    delback_index(&head, 4);
    printf("del after\n");
    dump(&head);

    return 0;
}
