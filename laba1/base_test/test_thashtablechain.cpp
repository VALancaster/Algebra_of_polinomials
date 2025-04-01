#include "THashTableChain.h"
#include <gtest.h>

TEST(THashTableChain, can_create_empty_hashtablechain) {
    ASSERT_NO_THROW(THashTableChain<std::string, int> table);
    THashTableChain<std::string, int> table;
    EXPECT_EQ(0, table.size());
}

TEST(THashTableChain, can_get_size) {
    THashTableChain<std::string, int> table;
    EXPECT_EQ(0, table.size());

    table.Insert("key1", 1);
    EXPECT_EQ(1, table.size());

    table.Insert("key2", 2);
    EXPECT_EQ(2, table.size());

    table.Insert("key1", 3);
    EXPECT_EQ(2, table.size());
}

TEST(THashTableChain, can_get_element_by_index) {
    THashTableChain<std::string, int> table;
    table.Insert("key1", 1);
    table.Insert("key2", 2);

    EXPECT_EQ(1, *table.Find("key1"));
    EXPECT_EQ(2, *table.Find("key2"));

    EXPECT_THROW(table["nonexistent_key"], std::out_of_range);
}

TEST(THashTableChain, can_delete) {
    THashTableChain<std::string, int> table;
    table.Insert("key1", 1);
    table.Insert("key2", 2);

    table.Delete("key1");
    EXPECT_EQ(nullptr, table.Find("key1"));
    EXPECT_EQ(1, table.size());
    EXPECT_EQ(2, *table.Find("key2"));

    table.Delete("key2");
    EXPECT_EQ(nullptr, table.Find("key2"));
    EXPECT_EQ(0, table.size());
}

TEST(THashTableChain, can_find) {
    THashTableChain<std::string, int> table;
    table.Insert("key1", 1);
    table.Insert("key2", 2);

    EXPECT_NE(nullptr, table.Find("key1"));
    EXPECT_EQ(1, *table.Find("key1"));

    EXPECT_NE(nullptr, table.Find("key2"));
    EXPECT_EQ(2, *table.Find("key2"));

    EXPECT_EQ(nullptr, table.Find("key3"));
}

TEST(THashTableChain, can_insert) {
    THashTableChain<std::string, int> table;
    table.Insert("key1", 1);
    table.Insert("key2", 2);

    EXPECT_EQ(2, table.size());
    EXPECT_EQ(1, *table.Find("key1"));
    EXPECT_EQ(2, *table.Find("key2"));

    table.Insert("key1", 3);
    EXPECT_EQ(2, table.size());
    EXPECT_EQ(1, *table.Find("key1"));
}

TEST(THashTableChain, handles_collisions_correctly) {
    THashTableChain<int, int> table(1);
    table.Insert(1, 10);
    table.Insert(2, 20); 

    EXPECT_EQ(2, table.size());
    EXPECT_EQ(10, *table.Find(1));
    EXPECT_EQ(20, *table.Find(2));

    table.Delete(1);
    EXPECT_EQ(nullptr, table.Find(1));
    EXPECT_EQ(20, *table.Find(2));
}

TEST(THashTableChain, can_print_contents) {
    THashTableChain<std::string, int> table;

    ASSERT_NO_THROW(table.Print());

    table.Insert("key1", 1);
    table.Insert("key2", 2);
    ASSERT_NO_THROW(table.Print());
}
