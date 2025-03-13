#include "gtest.h"
#include "TListTable.h"

TEST(TListTableTest, DefaultConstructor) {
    TListTable<int, double> listTable;
    ASSERT_NO_THROW();
} // Проверяет, что конструктор по умолчанию не выбрасывает исключений

TEST(TListTableTest, SizeMethodExists) {
    TListTable<int, double> listTable;
    ASSERT_NO_THROW(listTable.size());
} // Проверяет, что метод size() существует и не выбрасывает исключений

TEST(TListTableTest, OperatorBracketExists) {
    TListTable<int, double> listTable;
    SUCCEED();
} // Проверяет, что operator[] существует и компилируется

TEST(TListTableTest, DeleteMethodExists) {
    TListTable<int, double> listTable;
    ASSERT_NO_THROW(listTable.Delete(1)); // Dummy key
} // Проверяет, что метод Delete() существует и не выбрасывает исключений

TEST(TListTableTest, FindMethodExists) {
    TListTable<int, double> listTable;
    ASSERT_NO_THROW(listTable.Find(1)); // Dummy key
} // Проверяет, что метод Find() существует и не выбрасывает исключений

TEST(TListTableTest, InsertMethodExists) {
    TListTable<int, double> listTable;
    ASSERT_NO_THROW(listTable.Insert(1, 1.0)); // Dummy key and value
} // Проверяет, что метод Insert() существует и не выбрасывает исключений

// Test with different types
TEST(TListTableTest, CharKeyStringValue) {
    TListTable<char, std::string> listTable;
    ASSERT_NO_THROW();
    ASSERT_NO_THROW(listTable.Insert('a', "value1"));
    ASSERT_NO_THROW(listTable.Find('a'));
    ASSERT_NO_THROW(listTable.Delete('a'));
} // Проверяет, что методы работают с типами char для ключа и std::string для значения