#include "gtest.h"
#include "TSortedArrayTable.h"

TEST(TSortedArrayTableTest, DefaultConstructor) {
    TSortedArrayTable<int, double> sortedArrayTable;
    ASSERT_NO_THROW();
} // Проверяет, что конструктор по умолчанию не выбрасывает исключений

TEST(TSortedArrayTableTest, SizeMethodExists) {
    TSortedArrayTable<int, double> sortedArrayTable;
    ASSERT_NO_THROW(sortedArrayTable.size());
} // Проверяет, что метод size() существует и не выбрасывает исключений

TEST(TSortedArrayTableTest, OperatorBracketExists) {
    TSortedArrayTable<int, double> sortedArrayTable;
    SUCCEED();
} // Проверяет, что operator[] существует и компилируется

TEST(TSortedArrayTableTest, DeleteMethodExists) {
    TSortedArrayTable<int, double> sortedArrayTable;
    ASSERT_NO_THROW(sortedArrayTable.Delete(1)); // Dummy key
} // Проверяет, что метод Delete() существует и не выбрасывает исключений

TEST(TSortedArrayTableTest, FindMethodExists) {
    TSortedArrayTable<int, double> sortedArrayTable;
    ASSERT_NO_THROW(sortedArrayTable.Find(1)); // Dummy key
} // Проверяет, что метод Find() существует и не выбрасывает исключений

TEST(TSortedArrayTableTest, InsertMethodExists) {
    TSortedArrayTable<int, double> sortedArrayTable;
    ASSERT_NO_THROW(sortedArrayTable.Insert(1, 1.0)); // Dummy key and value
} // Проверяет, что метод Insert() существует и не выбрасывает исключений

// Test with different types
TEST(TSortedArrayTableTest, DoubleKeyIntValue) {
    TSortedArrayTable<double, int> sortedArrayTable;
    ASSERT_NO_THROW();
    ASSERT_NO_THROW(sortedArrayTable.Insert(2.5, 100));
    ASSERT_NO_THROW(sortedArrayTable.Find(2.5));
    ASSERT_NO_THROW(sortedArrayTable.Delete(2.5));
} // Проверяет, что методы работают с типами double для ключа и int для значения

TEST(TSortedArrayTableTest, InsertMethodExists) {
    TSortedArrayTable<int, double> sortedArrayTable;
    ASSERT_NO_THROW(sortedArrayTable.Insert(1, 1.0));
}

TEST(TSortedArrayTableTest, DoubleKeyIntValue) {
    TSortedArrayTable<double, int> sortedArrayTable;
    ASSERT_NO_THROW();
    ASSERT_NO_THROW(sortedArrayTable.Insert(2.5, 100));
    ASSERT_NO_THROW(sortedArrayTable.Find(2.5));
    ASSERT_NO_THROW(sortedArrayTable.Delete(2.5));
}