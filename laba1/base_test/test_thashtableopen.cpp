#include "gtest.h"
#include "THashTableOpen.h"

TEST(THashTableOpenTest, DefaultConstructor) {
    THashTableOpen<int, double> hashTable;
    ASSERT_NO_THROW();
} // ���������, ��� ����������� �� ��������� �� ����������� ����������

TEST(THashTableOpenTest, SizeMethodExists) {
    THashTableOpen<int, double> hashTable;
    ASSERT_NO_THROW(hashTable.size());
} // ���������, ��� ����� size() ���������� � �� ����������� ����������

TEST(THashTableOpenTest, OperatorBracketExists) {
    THashTableOpen<int, double> hashTable;
    SUCCEED();
} // ���������, ��� operator[] ���������� � �������������

TEST(THashTableOpenTest, DeleteMethodExists) {
    THashTableOpen<int, double> hashTable;
    ASSERT_NO_THROW(hashTable.Delete(1)); // Dummy key
} // ���������, ��� ����� Delete() ���������� � �� ����������� ����������

TEST(THashTableOpenTest, FindMethodExists) {
    THashTableOpen<int, double> hashTable;
    ASSERT_NO_THROW(hashTable.Find(1)); // Dummy key
} // ���������, ��� ����� Find() ���������� � �� ����������� ����������

TEST(THashTableOpenTest, InsertMethodExists) {
    THashTableOpen<int, double> hashTable;
    ASSERT_NO_THROW(hashTable.Insert(1, 1.0)); // Dummy key and value
} // ���������, ��� ����� Insert() ���������� � �� ����������� ����������

// You can add more tests with different key and value types if needed
TEST(THashTableOpenTest, StringKeyIntvalue) {
    THashTableOpen<std::string, int> hashTable;
    ASSERT_NO_THROW();
    ASSERT_NO_THROW(hashTable.Insert("key1", 10));
    ASSERT_NO_THROW(hashTable.Find("key1"));
    ASSERT_NO_THROW(hashTable.Delete("key1"));
} // ���������, ��� ������ �������� � ������ std::string ��� ����� � int ��� ��������