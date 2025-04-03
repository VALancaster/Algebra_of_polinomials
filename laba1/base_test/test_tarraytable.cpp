#include "TArrayTable.h"
#include <gtest.h>

TEST(TArrayTable, can_create_arraytable) {
    ASSERT_NO_THROW(TArrayTable<std::string, int> table);
}

TEST(TArrayTable, can_get_size) {
    TArrayTable<std::string, int> table;
    EXPECT_EQ(0, table.size());

    table.Insert("key1", 1);
    EXPECT_EQ(1, table.size());

    table.Insert("key2", 2);
    EXPECT_EQ(2, table.size());
}

TEST(TArrayTable, can_get_element_by_index) {
    TArrayTable<std::string, int> table;
    table.Insert("key1", 1);
    table.Insert("key2", 2);

    EXPECT_EQ(1, table[0]);
    EXPECT_EQ(2, table[1]);
}

TEST(TArrayTable, can_delete) {
    TArrayTable<std::string, int> table;
    table.Insert("key1", 1);
    table.Insert("key2", 2);

    table.Delete("key1");
    EXPECT_EQ(1, table.size());
    EXPECT_EQ(nullptr, table.Find("key1"));
    EXPECT_EQ(2, table.Find("key2"));
}

TEST(TArrayTable, can_find) {
    TArrayTable<std::string, int> table;
    table.Insert("key1", 1);
    table.Insert("key2", 2);

    EXPECT_NE(nullptr, table.Find("key1"));
    EXPECT_EQ(1, *table.Find("key1"));

    EXPECT_NE(nullptr, table.Find("key2"));
    EXPECT_EQ(2, *table.Find("key2"));

    EXPECT_EQ(nullptr, table.Find("key3"));
}

TEST(TArrayTable, can_insert) {
    TArrayTable<std::string, int> table;
    table.Insert("key1", 1);
    table.Insert("key2", 2);

    EXPECT_EQ(2, table.size());
    EXPECT_EQ(1, *table.Find("key1"));
    EXPECT_EQ(2, *table.Find("key2"));

    table.Insert("key1", 3);
    EXPECT_EQ(2, table.size());
    EXPECT_EQ(1, *table.Find("key1"));
}

TEST(TArrayTable, can_handle_multiple_insert_and_delete) {
    TArrayTable<std::string, int> table;
    table.Insert("key1", 1);
    table.Insert("key2", 2);
    table.Insert("key3", 3);

    EXPECT_EQ(3, table.size());

    table.Delete("key2");
    EXPECT_EQ(2, table.size());
    EXPECT_EQ(nullptr, table.Find("key2"));

    table.Insert("key4", 4);
    EXPECT_EQ(3, table.size());
    EXPECT_EQ(4, *table.Find("key4"));
}

TEST(TArrayTable, can_print_contents) {
    TArrayTable<std::string, int> table;
    ASSERT_NO_THROW(table.Print());

    table.Insert("key1", 1);
    table.Insert("key2", 2);
    ASSERT_NO_THROW(table.Print());
}