#include "gtest.h"
#include "THashTableOpen.h"

TEST(THashTableOpen, can_create_empty_hashtableopen) {
    ASSERT_NO_THROW(THashTableOpen<std::string, int> table);
    THashTableOpen<std::string, int> table;
    EXPECT_EQ(0, table.size());
}

TEST(THashTableOpen, can_insert_element) {
    THashTableOpen<std::string, int> table;
    table.Insert("key1", 1);
    EXPECT_EQ(1, table.size());
    EXPECT_EQ(1, *table.Find("key1"));
}

TEST(THashTableOpen, size_increases_after_insertion) {
    THashTableOpen<std::string, int> table;
    EXPECT_EQ(0, table.size());

    table.Insert("key1", 1);
    EXPECT_EQ(1, table.size());

    table.Insert("key2", 2);
    EXPECT_EQ(2, table.size());
}

TEST(THashTableOpen, can_find_inserted_element) {
    THashTableOpen<std::string, int> table;
    table.Insert("key1", 42);
    EXPECT_EQ(42, *table.Find("key1"));
}

TEST(THashTableOpen, finding_nonexistent_element_returns_null) {
    THashTableOpen<std::string, int> table;
    EXPECT_EQ(nullptr, table.Find("nonexistent_key"));
}

TEST(THashTableOpen, can_delete_element) {
    THashTableOpen<std::string, int> table;
    table.Insert("key1", 1);
    table.Delete("key1");
    EXPECT_EQ(nullptr, table.Find("key1"));
}

TEST(THashTableOpen, size_decreases_after_deletion) {
    THashTableOpen<std::string, int> table;
    table.Insert("key1", 1);
    table.Delete("key1");
    EXPECT_EQ(0, table.size());
}

TEST(THashTableOpen, deleting_nonexistent_element_does_not_change_size) {
    THashTableOpen<std::string, int> table;
    table.Insert("key1", 1);
    EXPECT_EQ(1, table.size());
    table.Delete("key2");
    EXPECT_EQ(1, table.size());
}

TEST(THashTableOpen, can_handle_collisions) {
    THashTableOpen<int, int> table(1);
    table.Insert(1, 10);
    table.Insert(2, 20);

    EXPECT_EQ(2, table.size());
    EXPECT_EQ(10, *table.Find(1));
    EXPECT_EQ(20, *table.Find(2));
}

TEST(THashTableOpen, can_update_existing_key) {
    THashTableOpen<std::string, int> table;
    table.Insert("key1", 1);
    ASSERT_EQ(1, *table.Find("key1"));

    table.Insert("key1", 2);
    EXPECT_EQ(2, *table.Find("key1"));
}

TEST(THashTableOpen, multiple_insertions_increase_size_correctly) {
    THashTableOpen<std::string, int> table;
    for (int i = 0; i < 100; ++i) {
        table.Insert("key" + std::to_string(i), i);
    }
    EXPECT_EQ(100, table.size());
}

TEST(THashTableOpen, table_allows_duplicate_values) {
    THashTableOpen<std::string, int> table;
    table.Insert("key1", 42);
    table.Insert("key2", 42);

    EXPECT_EQ(42, *table.Find("key1"));
    EXPECT_EQ(42, *table.Find("key2"));
    EXPECT_EQ(2, table.size());
}

TEST(THashTableOpen, deletion_marks_element_as_deleted_only) {
    THashTableOpen<std::string, int> table;
    table.Insert("key1", 1);
    table.Delete("key1");

    EXPECT_EQ(nullptr, table.Find("key1"));
    EXPECT_EQ(0, table.size());
}

TEST(THashTableOpen, handles_large_number_of_collisions) {
    THashTableOpen<int, int> table(3);
    table.Insert(1, 10);
    table.Insert(2, 20);
    table.Insert(3, 30);
    table.Insert(4, 40);

    EXPECT_EQ(4, table.size());
    EXPECT_EQ(10, *table.Find(1));
    EXPECT_EQ(20, *table.Find(2));
    EXPECT_EQ(40, *table.Find(4));
}

TEST(THashTableOpen, performance_under_high_load) {
    THashTableOpen<int, int> table(50);
    for (int i = 0; i < 1000; ++i) {
        table.Insert(i, i * 10);
    }

    EXPECT_EQ(1000, table.size());
    EXPECT_EQ(990, *table.Find(99));
}

TEST(THashTableOpen, insertion_overwrites_deleted_key_correctly) {
    THashTableOpen<std::string, int> table;
    table.Insert("key1", 1);
    table.Delete("key1");
    table.Insert("key1", 2);

    EXPECT_EQ(2, *table.Find("key1"));
    EXPECT_EQ(1, table.size());
}