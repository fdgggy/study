/*
缓存用于提高数据读取性能，大小有限，当缓存用满时，那些被清理，哪些被保留，需要缓存淘汰策略来决定。
1.FIFO(First In, First Out) 先进先出
2.LFU(Least Frequently Used) 最少使用
3.LRU(Least Recently Used) 最近最少使用

基于链表实现LRU缓存淘汰算法
1.越靠近链表尾部的节点是越早访问的。
2.当有新数据被访问时，从链表头开始遍历
  1.如果存在，删除原位置节点，然后插入链表头部
  2.如果不存在
    1.缓存未满，插入头部
    2.缓存已满，删除尾结点，插入头部

基于hashtable和双向链表实现的LRU， 可参考go版本
1.hashtable存储的key，value指向双向链表实现的LRU的节点。
2.LRU存储是基于双向链表实现，预先设置LRU的容量
3.当有新数据被访问时，从hashtable找到目标节点
  1.如果存在，删除原位置节点，然后插入链表头部
  2.如果不存在
    1.缓存未满，插入头部
    2.缓存已满，删除尾结点，插入头部

redis LRU方法，随机取出若干个key，按照访问时间排序，淘汰掉最不经常使用的数据。

哈希算法
散列表就是哈希表，Hash表，哈希算法也叫散列算法。英文就是Hash，翻译导致。
哈希算法：将任意长度的二进制值串映射为固定长度的二进制值串，映射规则就是哈希算法。映射后的二进制直串就是哈希值。
MD5：哈希值为128位，转化为16进制的编码。MD5("jiajia") = cd611a31ea969b908932d44d126d195b
哈希值是固定的128位，能表示的数据有限，最多表示2^128个数据，而要哈希的数据是无穷的，如果对2^128+1个数据求哈希值，
就必然会存在哈希冲突。固哈希值越长的哈希算法，散列冲突的概率越低。
应用:
1.安全加密
用户密码加密后再存储，比如MD5加密后存储。黑客可通过常用密码的字典表，进行哈希计算攻击。针对字典攻击，可以引入一个盐(salt)，
跟用户的密码组合在一起，增加密码复杂度，再做哈希算法加密，再存储，增加破解难度。
2.唯一标识，通过一个较短的二进制编码表示很大的数据
3.数据校验，校验数据完整性和正确性
4.散列函数，散列的平均性和哈希算法的执行效率

分布式应用：
1.负载均衡(轮询，随机，加权轮询),实现同一个客户端在一次会话中的所有请求都路由到同一个服务器上。对客户端IP或者会话IP计算哈希值
再与服务器列表大小进行取模运算，最终得到的就是目标服务器标号。
2.数据分片。海量数据处理，借助分片，可以突破单机内存，cpu等资源的限制。
    1.搜索关键字出现次数
    2.快速判断图片是否在图库中
3.分布式存储
    海量数据采用分布式存储数据。通过哈希算法对数据取哈希值，再对机器个数取模。机器数量变化时，缓存数据失效，所有数据请求都会
    穿透缓存，直接请求数据库，发生雪崩效应，压垮数据库。
一致性哈希算法概念
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct _Node{
    struct _Node *prev;
    struct _Node *next;
    struct _Node *hnext;
    int key;
    int value;
}Node;

typedef struct {
    Node **hashTable;
    Node *head;
    Node *tail;
    int cap;
    int used;
}LRUCache;


LRUCache * create(int cap) {
    LRUCache *cache = malloc(sizeof(LRUCache));
    if (!cache) {
        return NULL;
    }
    cache->hashTable = malloc(sizeof(Node *) * cap);
    if (!cache->hashTable) {
        return NULL;
    }
    for (int i = 0; i < cap; i++) {
        Node * node = malloc(sizeof(Node));
        node->hnext = NULL;
        node->key = 0;
        node->value = 0;
        node->prev = NULL;
        node->next = NULL;
        cache->hashTable[i] = node;
    }
    cache->head = NULL;
    cache->tail = NULL;
    cache->cap = cap;
    cache->used = 0;

    return cache;
}

int hash_func(LRUCache *cache, int key) {
    return key*100%cache->cap;
}

Node* find(LRUCache *cache, int key) {
    if (!cache->tail) {
        return NULL;
    }
    int pos = hash_func(cache, key);
    Node* temp = cache->hashTable[pos]->hnext;
    while (temp) {
        if (temp->key == key) {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

void movehead(LRUCache *cache, Node* node) {
    if (cache->head == node) {
        return;
    }
    if (cache->tail == node) {
        cache->tail = node->prev;
        cache->tail->next = NULL;
    }else {
        node->prev->next = node->next;
        node->next->prev = node->prev;
        node->next = NULL;
    }
    node->prev = NULL;
    cache->head->prev = node;
    node->next = cache->head;
    cache->head = node;
}

void delnode(LRUCache *cache) {
    int pos = hash_func(cache, cache->tail->key);
    Node* prev = cache->hashTable[pos];
    Node* cur = prev->hnext;
    while (cur && cur->key != cache->tail->key) {
        prev = cur;
        cur = cur->hnext;
    }
    if (!cur) {
        return;
    }
    prev->hnext = cur->hnext;
    cache->tail = cur->prev;
    cache->tail->next = NULL;
    cache->used--;
    free(cur);
}

void addnode(LRUCache *cache, int key, int value) {
    Node *node = malloc(sizeof(Node));
    node->key = key;
    node->value = value;
    int pos = hash_func(cache, key);
    Node* temp = cache->hashTable[pos];
    node->hnext = temp->hnext;
    temp->hnext = node;
    cache->used++;

    if (!cache->head) {
        cache->head = cache->tail = node;
        return;
    }
    node->next = cache->head;
    node->prev = NULL;
    cache->head->prev = node;
    cache->head = node;
}

int put(LRUCache *cache, int key, int value) {
    Node* temp = find(cache, key);
    if (temp) {
        temp->value = value;
        movehead(cache, temp);
        return 0;
    }
    if (cache->used >= cache->cap) {
        delnode(cache);
    }
    addnode(cache, key, value);

    return 0;
}

int get(LRUCache *cache, int key) {
    Node *node = find(cache, key);
    movehead(cache, node);
    return node->value;
}

void dump(LRUCache *cache) {
    printf("--------\n");

    for (int i = 0; i < cache->cap; i++) {
        Node *node = cache->hashTable[i];
        while (node) {
            if (node->key != 0) {
                printf("pos:%d key:%d value:%d\n", i, node->key, node->value);
            }
            node = node->hnext;
        }
    }
    printf("--------\n");
    Node *temp = cache->head;
    while(temp) {
        printf("key:%d value:%d\n", temp->key, temp->value);
        temp = temp->next;
    }
}

int main() {
    LRUCache *cache = create(3);
    put(cache, 1, 11);
    put(cache, 2, 12);
    put(cache, 3, 13);
    dump(cache);
    put(cache, 4, 14);
    dump(cache);
    int v = get(cache, 3);
    printf("v:%d\n", v);

    return 0;
}




