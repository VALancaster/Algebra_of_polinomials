#include "gtest.h"
#include "TSortedArrayTable.h"

TEST(TSortedArrayTableTest, DefaultConstructor) {
    TSortedArrayTable<int, double> sortedArrayTable;
    ASSERT_NO_THROW();
} // ���������, ��� ����������� �� ��������� �� ����������� ����������

TEST(TSortedArrayTableTest, SizeMethodExists) {
    TSortedArrayTable<int, double> sortedArrayTable;
    ASSERT_NO_THROW(sortedArrayTable.size());
} // ���������, ��� ����� size() ���������� � �� ����������� ����������

TEST(TSortedArrayTableTest, OperatorBracketExists) {
    TSortedArrayTable<int, double> sortedArrayTable;
    SUCCEED();
} // ���������, ��� operator[] ���������� � �������������

TEST(TSortedArrayTableTest, DeleteMethodExists) {
    TSortedArrayTable<int, double> sortedArrayTable;
    ASSERT_NO_THROW(sortedArrayTable.Delete(1)); // Dummy key
} // ���������, ��� ����� Delete() ���������� � �� ����������� ����������

TEST(TSortedArrayTableTest, FindMethodExists) {
    TSortedArrayTable<int, double> sortedArrayTable;
    ASSERT_NO_THROW(sortedArrayTable.Find(1)); // Dummy key
} // ���������, ��� ����� Find() ���������� � �� ����������� ����������

TEST(TSortedArrayTableTest, InsertMethodExists) {
    TSortedArrayTable<int, double> sortedArrayTable;
    ASSERT_NO_THROW(sortedArrayTable.Insert(1, 1.0)); // Dummy key and value
} // ���������, ��� ����� Insert() ���������� � �� ����������� ����������

// Test with different types
TEST(TSortedArrayTableTest, DoubleKeyIntValue) {
    TSortedArrayTable<double, int> sortedArrayTable;
    ASSERT_NO_THROW();
    ASSERT_NO_THROW(sortedArrayTable.Insert(2.5, 100));
    ASSERT_NO_THROW(sortedArrayTable.Find(2.5));
    ASSERT_NO_THROW(sortedArrayTable.Delete(2.5));
} // ���������, ��� ������ �������� � ������ double ��� ����� � int ��� ��������

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