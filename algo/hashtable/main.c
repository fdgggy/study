#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include "../../common/util.h"

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
