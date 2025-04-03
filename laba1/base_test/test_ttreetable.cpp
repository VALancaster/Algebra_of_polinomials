#include "gtest.h"
#include "TTreeTable.h"

TEST(TTreeTable, can_create_treetable) {
    ASSERT_NO_THROW(TTreeTable<std::string, int> table);
}

TEST(TTreeTable, size_of_empty_tree_is_zero) {
    TTreeTable<std::string, int> table;
    EXPECT_EQ(0, table.size());
}

TEST(TTreeTable, can_insert_element) {
    TTreeTable<std::string, int> table;
    ASSERT_NO_THROW(table.Insert("key1", 10));
    EXPECT_EQ(10, *table.Find("key1"));
}

TEST(TTreeTable, insert_increases_size) {
    TTreeTable<std::string, int> table;
    table.Insert("key1", 10);
    EXPECT_EQ(1, table.size());

    table.Insert("key2", 20);
    EXPECT_EQ(2, table.size());
}

TEST(TTreeTable, can_find_inserted_element) {
    TTreeTable<std::string, int> table;
    table.Insert("key1", 100);
    TValue* value = table.Find("key1");
    EXPECT_NE(nullptr, value);
    EXPECT_EQ(100, *value);
}

TEST(TTreeTable, finding_nonexistent_element_returns_null) {
    TTreeTable<std::string, int> table;
    EXPECT_EQ(nullptr, table.Find("nonexistent"));
}

TEST(TTreeTable, tree_size_decreases_after_deletion) {
    TTreeTable<std::string, int> table;
    table.Insert("key1", 10);
    table.Insert("key2", 20);

    EXPECT_EQ(2, table.size());
    table.Delete("key1");
    EXPECT_EQ(1, table.size());
    EXPECT_EQ(nullptr, table.Find("key1"));
}

TEST(TTreeTable, deleting_nonexistent_element_does_not_change_size) {
    TTreeTable<std::string, int> table;
    table.Insert("key1", 10);
    EXPECT_EQ(1, table.size());

    table.Delete("key2");
    EXPECT_EQ(1, table.size());
}

TEST(TTreeTable, can_delete_leaf_node) {
    TTreeTable<int, std::string> table;
    table.Insert(10, "value10");
    table.Insert(20, "value20");
    table.Insert(5, "value5");

    table.Delete(5);
    EXPECT_EQ(nullptr, table.Find(5));
    EXPECT_EQ(2, table.size());
}

TEST(TTreeTable, can_delete_node_with_one_child) {
    TTreeTable<int, std::string> table;
    table.Insert(10, "value10");
    table.Insert(5, "value5");
    table.Insert(3, "value3");

    table.Delete(5);
    EXPECT_EQ(nullptr, table.Find(5));
    EXPECT_NE(nullptr, table.Find(3));
    EXPECT_EQ(2, table.size());
}

TEST(TTreeTable, can_delete_node_with_two_children) {
    TTreeTable<int, std::string> table;
    table.Insert(10, "value10");
    table.Insert(5, "value5");
    table.Insert(15, "value15");
    table.Insert(12, "value12");
    table.Insert(18, "value18");

    table.Delete(15);
    EXPECT_EQ(nullptr, table.Find(15));
    EXPECT_NE(nullptr, table.Find(12));
    EXPECT_NE(nullptr, table.Find(18));
    EXPECT_EQ(4, table.size());
}

TEST(TTreeTable, print_does_not_throw) {
    TTreeTable<std::string, int> table;
    table.Insert("key1", 10);
    table.Insert("key2", 20);

    EXPECT_NO_THROW(table.Print());
}

TEST(TTreeTable, can_handle_empty_tree_print) {
    TTreeTable<std::string, int> table;
    EXPECT_NO_THROW(table.Print());
}

TEST(TTreeTable, destructor_clears_tree) {
    TTreeTable<int, std::string>* table = new TTreeTable<int, std::string>;
    table->Insert(10, "value10");
    table->Insert(20, "value20");
    EXPECT_EQ(2, table->size());
    delete table;
    SUCCEED();
}




/*
TEST(TTreeTable, maintains_binary_search_tree_order) {
    TTreeTable<int, std::string> table;
    table.Insert(20, "value20");
    table.Insert(10, "value10");
    table.Insert(30, "value30");

    std::ostringstream out;
    std::streambuf* defaultBuffer = std::cout.rdbuf();
    std::cout.rdbuf(out.rdbuf());
    table.Print();
    std::cout.rdbuf(defaultBuffer);

    EXPECT_TRUE(out.str().find("10-value10") < out.str().find("20-value20"));
    EXPECT_TRUE(out.str().find("20-value20") < out.str().find("30-value30"));
}
*/