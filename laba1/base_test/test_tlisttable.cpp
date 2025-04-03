#include "gtest.h"
#include "TListTable.h"

TEST(TListTable, can_create_listtable) {
    ASSERT_NO_THROW(TListTable<std::string, int> table);
}

TEST(TListTable, size_of_empty_table_is_zero) {
    TListTable<std::string, int> table;
    EXPECT_EQ(0, table.size());
}

TEST(TListTable, can_insert_element) {
    TListTable<std::string, int> table;
    ASSERT_NO_THROW(table.Insert("key1", 10));
    EXPECT_EQ(10, *table.Find("key1"));
}

TEST(TListTable, insert_increases_size) {
    TListTable<std::string, int> table;
    table.Insert("key1", 10);
    EXPECT_EQ(1, table.size());

    table.Insert("key2", 20);
    EXPECT_EQ(2, table.size());
}

TEST(TListTable, can_find_inserted_element) {
    TListTable<std::string, int> table;
    table.Insert("key1", 42);
    TValue* value = table.Find("key1");
    EXPECT_NE(nullptr, value);
    EXPECT_EQ(42, *value);
}

TEST(TListTable, finding_nonexistent_element_returns_null) {
    TListTable<std::string, int> table;
    EXPECT_EQ(nullptr, table.Find("nonexistent_key"));
}

TEST(TListTable, size_decreases_after_deletion) {
    TListTable<std::string, int> table;
    table.Insert("key1", 10);
    table.Insert("key2", 20);

    EXPECT_EQ(2, table.size());
    table.Delete("key1");
    EXPECT_EQ(1, table.size());
    EXPECT_EQ(nullptr, table.Find("key1"));
}

TEST(TListTable, deleting_nonexistent_element_does_not_change_size) {
    TListTable<std::string, int> table;
    table.Insert("key1", 10);
    EXPECT_EQ(1, table.size());

    table.Delete("key2");
    EXPECT_EQ(1, table.size());
}

TEST(TListTable, insert_does_not_allow_duplicate_keys) {
    TListTable<std::string, int> table;
    table.Insert("key1", 10);
    table.Insert("key1", 20);

    EXPECT_EQ(1, table.size());
    EXPECT_EQ(10, *table.Find("key1"));
}

TEST(TListTable, throws_out_of_range_on_invalid_index) {
    TListTable<std::string, int> table;
    table.Insert("key1", 10);

    EXPECT_NO_THROW(table[0]);
    EXPECT_THROW(table[1], std::out_of_range);
}

TEST(TListTable, can_access_elements_by_index) {
    TListTable<std::string, int> table;
    table.Insert("key1", 10);
    table.Insert("key2", 20);
    table.Insert("key3", 30);

    EXPECT_EQ(10, table[0]);
    EXPECT_EQ(20, table[1]);
    EXPECT_EQ(30, table[2]);
}

TEST(TListTable, print_does_not_throw) {
    TListTable<std::string, int> table;
    table.Insert("key1", 10);
    table.Insert("key2", 20);

    EXPECT_NO_THROW(table.Print());
}

TEST(TListTable, delete_does_not_affect_non_deleted_elements) {
    TListTable<std::string, int> table;
    table.Insert("key1", 10);
    table.Insert("key2", 20);
    table.Insert("key3", 30);

    table.Delete("key2");

    EXPECT_EQ(2, table.size());
    EXPECT_EQ(10, *table.Find("key1"));
    EXPECT_EQ(nullptr, table.Find("key2"));
    EXPECT_EQ(30, *table.Find("key3"));
}






/*
TEST(TListTable, can_iterate_over_table_elements) {
    TListTable<std::string, int> table;
    table.Insert("key1", 10);
    table.Insert("key2", 20);
    table.Insert("key3", 30);

    std::vector<std::pair<std::string, int>> elements;
    for (auto it = table.data.begin(); it != table.data.end(); ++it) {
        elements.emplace_back(it->key, it->value);
    }

    EXPECT_EQ(3, elements.size());
    EXPECT_EQ("key1", elements[0].first);
    EXPECT_EQ(10, elements[0].second);
    EXPECT_EQ("key2", elements[1].first);
    EXPECT_EQ(20, elements[1].second);
    EXPECT_EQ("key3", elements[2].first);
    EXPECT_EQ(30, elements[2].second);
}

*/