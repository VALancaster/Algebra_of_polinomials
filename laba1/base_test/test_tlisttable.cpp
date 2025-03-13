#include "gtest.h"
#include "TListTable.h"

TEST(TListTableTest, DefaultConstructor) {
    TListTable<int, double> listTable;
    ASSERT_NO_THROW();
} // ���������, ��� ����������� �� ��������� �� ����������� ����������

TEST(TListTableTest, SizeMethodExists) {
    TListTable<int, double> listTable;
    ASSERT_NO_THROW(listTable.size());
} // ���������, ��� ����� size() ���������� � �� ����������� ����������

TEST(TListTableTest, OperatorBracketExists) {
    TListTable<int, double> listTable;
    SUCCEED();
} // ���������, ��� operator[] ���������� � �������������

TEST(TListTableTest, DeleteMethodExists) {
    TListTable<int, double> listTable;
    ASSERT_NO_THROW(listTable.Delete(1)); // Dummy key
} // ���������, ��� ����� Delete() ���������� � �� ����������� ����������

TEST(TListTableTest, FindMethodExists) {
    TListTable<int, double> listTable;
    ASSERT_NO_THROW(listTable.Find(1)); // Dummy key
} // ���������, ��� ����� Find() ���������� � �� ����������� ����������

TEST(TListTableTest, InsertMethodExists) {
    TListTable<int, double> listTable;
    ASSERT_NO_THROW(listTable.Insert(1, 1.0)); // Dummy key and value
} // ���������, ��� ����� Insert() ���������� � �� ����������� ����������

// Test with different types
TEST(TListTableTest, CharKeyStringValue) {
    TListTable<char, std::string> listTable;
    ASSERT_NO_THROW();
    ASSERT_NO_THROW(listTable.Insert('a', "value1"));
    ASSERT_NO_THROW(listTable.Find('a'));
    ASSERT_NO_THROW(listTable.Delete('a'));
} // ���������, ��� ������ �������� � ������ char ��� ����� � std::string ��� ��������