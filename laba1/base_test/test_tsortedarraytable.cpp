#include "gtest.h"
#include "TSortedArrayTable.h"

TEST(TSortedArrayTable, can_create_sortedarraytable) {
    ASSERT_NO_THROW(TSortedArrayTable<std::string, int> table);
}

TEST(TSortedArrayTable, size_of_empty_table_is_zero) {
    TSortedArrayTable<std::string, int> table;
    EXPECT_EQ(0, table.size());
}

TEST(TSortedArrayTable, can_insert_element) {
    TSortedArrayTable<std::string, int> table;
    ASSERT_NO_THROW(table.Insert("key1", 10));
    EXPECT_EQ(10, *table.Find("key1"));
}

TEST(TSortedArrayTable, insert_increases_size) {
    TSortedArrayTable<std::string, int> table;
    table.Insert("key1", 10);
    EXPECT_EQ(1, table.size());

    table.Insert("key2", 20);
    EXPECT_EQ(2, table.size());
}

TEST(TSortedArrayTable, can_find_inserted_element) {
    TSortedArrayTable<std::string, int> table;
    table.Insert("key1", 42);
    TValue* value = table.Find("key1");
    EXPECT_NE(nullptr, value);
    EXPECT_EQ(42, *value);
}

TEST(TSortedArrayTable, finding_nonexistent_element_returns_null) {
    TSortedArrayTable<std::string, int> table;
    EXPECT_EQ(nullptr, table.Find("nonexistent_key"));
}

TEST(TSortedArrayTable, size_decreases_after_deletion) {
    TSortedArrayTable<std::string, int> table;
    table.Insert("key1", 10);
    table.Insert("key2", 20);

    EXPECT_EQ(2, table.size());
    table.Delete("key1");
    EXPECT_EQ(1, table.size());
    EXPECT_EQ(nullptr, table.Find("key1"));
}

TEST(TSortedArrayTable, deleting_nonexistent_element_does_not_change_size) {
    TSortedArrayTable<std::string, int> table;
    table.Insert("key1", 10);
    EXPECT_EQ(1, table.size());

    table.Delete("key2");
    EXPECT_EQ(1, table.size());
}

TEST(TSortedArrayTable, maintains_sorted_order_after_insertion) {
    TSortedArrayTable<std::string, int> table;
    table.Insert("key3", 30);
    table.Insert("key1", 10);
    table.Insert("key2", 20);

    EXPECT_EQ("key1", table[0]);
    EXPECT_EQ("key2", table[1]);
    EXPECT_EQ("key3", table[2]);
}

TEST(TSortedArrayTable, insert_does_not_allow_duplicate_keys) {
    TSortedArrayTable<std::string, int> table;
    table.Insert("key1", 10);
    table.Insert("key1", 20);

    EXPECT_EQ(1, table.size());
    EXPECT_EQ(10, *table.Find("key1"));
}

TEST(TSortedArrayTable, throws_out_of_range_on_invalid_index) {
    TSortedArrayTable<std::string, int> table;
    table.Insert("key1", 10);

    EXPECT_NO_THROW(table[0]);
    EXPECT_THROW(table[1], std::out_of_range);
}

TEST(TSortedArrayTable, can_access_elements_by_index) {
    TSortedArrayTable<std::string, int> table;
    table.Insert("key1", 10);
    table.Insert("key2", 20);
    table.Insert("key3", 30);

    EXPECT_EQ(10, table[0]);
    EXPECT_EQ(20, table[1]);
    EXPECT_EQ(30, table[2]);
}

TEST(TSortedArrayTable, print_does_not_throw) {
    TSortedArrayTable<std::string, int> table;
    table.Insert("key1", 10);
    table.Insert("key2", 20);

    EXPECT_NO_THROW(table.Print());
}

TEST(TSortedArrayTable, delete_does_not_affect_non_deleted_elements) {
    TSortedArrayTable<std::string, int> table;
    table.Insert("key1", 10);
    table.Insert("key2", 20);
    table.Insert("key3", 30);

    table.Delete("key2");

    EXPECT_EQ(2, table.size());
    EXPECT_EQ(10, *table.Find("key1"));
    EXPECT_EQ(nullptr, table.Find("key2"));
    EXPECT_EQ(30, *table.Find("key3"));
}