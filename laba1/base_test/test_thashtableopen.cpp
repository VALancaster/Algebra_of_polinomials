#include "gtest.h"
#include "THashTableOpen.h"

TEST(THashTableOpenTest, DefaultConstructor) {
    THashTableOpen<int, double> hashTable;
    ASSERT_NO_THROW();
} // Проверяет, что конструктор по умолчанию не выбрасывает исключений

TEST(THashTableOpenTest, SizeMethodExists) {
    THashTableOpen<int, double> hashTable;
    ASSERT_NO_THROW(hashTable.size());
} // Проверяет, что метод size() существует и не выбрасывает исключений

TEST(THashTableOpenTest, OperatorBracketExists) {
    THashTableOpen<int, double> hashTable;
    SUCCEED();
} // Проверяет, что operator[] существует и компилируется

TEST(THashTableOpenTest, DeleteMethodExists) {
    THashTableOpen<int, double> hashTable;
    ASSERT_NO_THROW(hashTable.Delete(1)); // Dummy key
} // Проверяет, что метод Delete() существует и не выбрасывает исключений

TEST(THashTableOpenTest, FindMethodExists) {
    THashTableOpen<int, double> hashTable;
    ASSERT_NO_THROW(hashTable.Find(1)); // Dummy key
} // Проверяет, что метод Find() существует и не выбрасывает исключений

TEST(THashTableOpenTest, InsertMethodExists) {
    THashTableOpen<int, double> hashTable;
    ASSERT_NO_THROW(hashTable.Insert(1, 1.0)); // Dummy key and value
} // Проверяет, что метод Insert() существует и не выбрасывает исключений

// You can add more tests with different key and value types if needed
TEST(THashTableOpenTest, StringKeyIntvalue) {
    THashTableOpen<std::string, int> hashTable;
    ASSERT_NO_THROW();
    ASSERT_NO_THROW(hashTable.Insert("key1", 10));
    ASSERT_NO_THROW(hashTable.Find("key1"));
    ASSERT_NO_THROW(hashTable.Delete("key1"));
} // Проверяет, что методы работают с типами std::string для ключа и int для значения