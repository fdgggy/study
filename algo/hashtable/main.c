#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include "../../common/util.h"
/*
散列设计：
1.支持快速查询，插入，删除操作
2.内存占用合理
3.性能稳定，极端情况下，散列表性能不会退化到无法接受的情况。如一个slot里很多元素
思路：
1.设计一个合适的散列函数
2.定义装在因子的阀值，超过阀值，动态扩容策略。 
3.选择合适的散列冲突解决办法,线性查找或链表法。
skynet里的netpack对接收到非完整的包处理，一个fd作为key，计算出hash值，插入hash槽中，查找时，遍历槽中属于fd的结点即可
*/

#define HASH_SHIFT 4
#define HASH_SIZE (1 << HASH_SHIFT)
#define HASH_MASK (HASH_SIZE-1)

struct hash_table {
    unsigned int used;
    unsigned long entry[HASH_SIZE];
};

void hash_table_reset(struct hash_table *table) {
    if (table == NULL) {
       printf("table is NULL\n");
       return;
    }
    table->used = 0;
    for (int i=0; i < HASH_SIZE; i++) {
        table->entry[i] = ~0;
    }
}

unsigned int hash_function(unsigned long value) {
    return value & HASH_MASK;
}

void hash_function_test() {
    srandom(time(NULL));
    for(int i=0; i <10; i++) {
        unsigned long val = random();
        printf("%10lu -> %2u\n", val, hash_function(val));
    }
}

unsigned int next_probe(unsigned int prev_key) {
    return (prev_key+1)&HASH_MASK;
}

void next_probe_test(){
    unsigned int key1, key2;
    key1 = 0;

    for(int i=0; i<HASH_SIZE+20;i++) {
        key2 = next_probe(key1);
        printf("%2u -> %2u\n", key1, key2);
        key1 = key2;
    }
}

void hash_table_add(struct hash_table *table, unsigned long value) {
    if (table->used >= HASH_SIZE){
       printf("over hash table size\n");
       return;
    }

    unsigned int key = hash_function(value);
    printf("hash key:%d\n", key);
    while (table->entry[key] != ~0)
        key = next_probe(key);
    
    table->entry[key] = value;
    table->used++;
}

unsigned int hash_table_slot(struct hash_table *table, unsigned long value) {
    unsigned int key = hash_function(value);
    while(table->entry[key] != ~0) {
        if (table->entry[key] == value){
            break;
        }else{
            key = next_probe(key);
        }
    }
    return key;
}

bool hash_table_find(struct hash_table *table, unsigned long value){
    unsigned int key = hash_table_slot(table, value);
    return table->entry[key] == value;
}

void hash_table_add_test(){
    struct hash_table table;
    hash_table_reset(&table);
    hash_table_add(&table, 87654);

    printf("table has%s 87654\n", hash_table_find(&table, 87654)?"":"n't");
}

int main() {
   // struct hash_table ht;
   // hash_table_reset(&ht);
   // hash_function_test();
   // next_probe_test();
    hash_table_add_test();
    return 0;
}
