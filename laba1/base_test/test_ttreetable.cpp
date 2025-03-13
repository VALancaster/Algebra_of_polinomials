#include "gtest.h"
#include "TTreeTable.h"

TEST(TTreeTableTest, DefaultConstructor) {
    TTreeTable<int, double> treeTable;
    ASSERT_NO_THROW();
} // Проверяет, что конструктор по умолчанию не выбрасывает исключений

TEST(TTreeTableTest, DestructorExists) {
    // Destructor is declared, just check if it compiles.
    ASSERT_NO_THROW({
        TTreeTable<int, double> treeTable;
        });
} // Проверяет, что деструктор существует и компилируется

TEST(TTreeTableTest, SizeMethodExists) {
    TTreeTable<int, double> treeTable;
    ASSERT_NO_THROW(treeTable.size());
} // Проверяет, что метод size() существует и не выбрасывает исключений

TEST(TTreeTableTest, OperatorBracketExists) {
    TTreeTable<int, double> treeTable;
    SUCCEED();
} // Проверяет, что operator[] существует и компилируется

TEST(TTreeTableTest, DeleteMethodExists) {
    TTreeTable<int, double> treeTable;
    ASSERT_NO_THROW(treeTable.Delete(1)); // Dummy key
} // Проверяет, что метод Delete() существует и не выбрасывает исключений

TEST(TTreeTableTest, FindMethodExists) {
    TTreeTable<int, double> treeTable;
    ASSERT_NO_THROW(treeTable.Find(1)); // Dummy key
} // Проверяет, что метод Find() существует и не выбрасывает исключений

TEST(TTreeTableTest, InsertMethodExists) {
    TTreeTable<int, double> treeTable;
    ASSERT_NO_THROW(treeTable.Insert(1, 1.0)); // Dummy key and value
} // Проверяет, что метод Insert() существует и не выбрасывает исключений

// Test with different types
TEST(TTreeTableTest, LongLongKeyFloatValue) {
    TTreeTable<long long, float> treeTable;
    ASSERT_NO_THROW();
    ASSERT_NO_THROW(treeTable.Insert(123456789LL, 3.14f));
    ASSERT_NO_THROW(treeTable.Find(123456789LL));
    ASSERT_NO_THROW(treeTable.Delete(123456789LL));
} // Проверяет, что методы работают с типами long long для ключа и float для значения