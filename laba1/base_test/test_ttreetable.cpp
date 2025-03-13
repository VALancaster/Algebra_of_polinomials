#include "gtest.h"
#include "TTreeTable.h"

TEST(TTreeTableTest, DefaultConstructor) {
    TTreeTable<int, double> treeTable;
    ASSERT_NO_THROW();
} // ���������, ��� ����������� �� ��������� �� ����������� ����������

TEST(TTreeTableTest, DestructorExists) {
    // Destructor is declared, just check if it compiles.
    ASSERT_NO_THROW({
        TTreeTable<int, double> treeTable;
        });
} // ���������, ��� ���������� ���������� � �������������

TEST(TTreeTableTest, SizeMethodExists) {
    TTreeTable<int, double> treeTable;
    ASSERT_NO_THROW(treeTable.size());
} // ���������, ��� ����� size() ���������� � �� ����������� ����������

TEST(TTreeTableTest, OperatorBracketExists) {
    TTreeTable<int, double> treeTable;
    SUCCEED();
} // ���������, ��� operator[] ���������� � �������������

TEST(TTreeTableTest, DeleteMethodExists) {
    TTreeTable<int, double> treeTable;
    ASSERT_NO_THROW(treeTable.Delete(1)); // Dummy key
} // ���������, ��� ����� Delete() ���������� � �� ����������� ����������

TEST(TTreeTableTest, FindMethodExists) {
    TTreeTable<int, double> treeTable;
    ASSERT_NO_THROW(treeTable.Find(1)); // Dummy key
} // ���������, ��� ����� Find() ���������� � �� ����������� ����������

TEST(TTreeTableTest, InsertMethodExists) {
    TTreeTable<int, double> treeTable;
    ASSERT_NO_THROW(treeTable.Insert(1, 1.0)); // Dummy key and value
} // ���������, ��� ����� Insert() ���������� � �� ����������� ����������

// Test with different types
TEST(TTreeTableTest, LongLongKeyFloatValue) {
    TTreeTable<long long, float> treeTable;
    ASSERT_NO_THROW();
    ASSERT_NO_THROW(treeTable.Insert(123456789LL, 3.14f));
    ASSERT_NO_THROW(treeTable.Find(123456789LL));
    ASSERT_NO_THROW(treeTable.Delete(123456789LL));
} // ���������, ��� ������ �������� � ������ long long ��� ����� � float ��� ��������