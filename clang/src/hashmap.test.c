#include "utils/utils.h"
#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#include <stdbool.h>
#include <string.h>

uint64_t string_hash_func(const void* self);
bool string_compare_func(const void* self, const void* target);

// bookmark: anonymous struct initialization
HashMap_Record new_string_record(const char key[], const char value[]) {
  return (HashMap_Record){
    .hash_func = string_hash_func,
    .compare = string_compare_func,
    .key = (BytesRange) {
      .bytes = &key,
      .bytes_size = strlen(key),
    },
    .value = (BytesRange) {
      .bytes = &value,
      .bytes_size = strlen(value),
    }
  };
};

uint64_t string_hash_func(const void* self) {
  const HashMap_Record* record = (const HashMap_Record*) self;
  return fnv_1(record->key.bytes, record->key.bytes_size);
};

bool string_compare_func(const void* self, const void* target) {
  const HashMap_Record* self_record = (const HashMap_Record*) self;
  const HashMap_Record* target_record = (const HashMap_Record*) target;
  if (self_record->key.bytes_size != target_record->key.bytes_size) return false;
  return memcmp(self_record->key.bytes, target_record->key.bytes, self_record->key.bytes_size) == 0;
}

int add(int a, int b)
{
    return a + b;
}

void test_string_hash(void)
{
    HashMap_Record hr_hello = new_string_record("hello", "world");
    HashMap_Record hr_hello_clone = new_string_record("hello", "world");
    HashMap_Record new_world = new_string_record("new", "world");
    CU_ASSERT(string_hash_func(&hr_hello) == string_hash_func(&hr_hello_clone));
    CU_ASSERT(string_hash_func(&hr_hello) != string_hash_func(&new_world));
}


void test_string_compare(void)
{
    HashMap_Record hr_hello = new_string_record("hello", "world");
    HashMap_Record hr_hello_clone = new_string_record("hello", "world");
    HashMap_Record new_world = new_string_record("new", "world");
    CU_ASSERT(string_compare_func(&hr_hello, &hr_hello_clone) == true);
    CU_ASSERT(string_compare_func(&hr_hello, &new_world) == false);
}

int main()
{
    CU_initialize_registry();
    CU_pSuite suite = CU_add_suite("AddTestSuite", 0, 0);
    CU_add_test(suite, "test of string_hash_func()", test_string_hash);
    CU_add_test(suite, "test of string_compare_func()", test_string_compare);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return 0;
}
