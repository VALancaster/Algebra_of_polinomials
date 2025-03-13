#include "stack.h"
#include <gtest.h>


TEST(TStack, can_create_stack)
{
	ASSERT_NO_THROW(TStack<int> st);
}

TEST(TStack, can_push_and_pop_element)
{
	TStack<int> st;
	st.Push(1);
	ASSERT_EQ(1, st.Pop());
}

TEST(TStack, can_get_size)
{
	TStack<int> st;
	st.Push(1);
	st.Push(2);
	st.Push(3);
	EXPECT_EQ(3, st.GetSize());
}

TEST(TStack, can_get_size_of_empty_stack)
{
	TStack<int> st;
	EXPECT_EQ(0, st.GetSize());
}

TEST(TStack, stack_size_is_correct_after_pushes_and_pops)
{
	TStack<int> st;
	st.Push(6);
	st.Push(5);
	st.Pop();
	ASSERT_EQ(1, st.GetSize());
}

TEST(TStack, can_check_not_empty_stack)
{
	TStack<int> st;
	st.Push(1);
	st.Push(2);
	st.Push(3);
	EXPECT_FALSE(st.IsEmpty());
}

TEST(TStack, can_check_empty_stack)
{
	TStack<int> st;
	EXPECT_TRUE(st.IsEmpty());
}

TEST(TStack, pop_from_empty_stack_throws_exception)
{
	TStack<int> st;
	ASSERT_THROW(st.Pop(), std::underflow_error);
}

TEST(TStack, can_pop)
{
	TStack<int> st;
	st.Push(1);
	st.Push(2);
	st.Push(3);
	EXPECT_EQ(3, st.Pop());
}

TEST(TStack, stack_grows_correctly)
{
	TStack<int> st;
	for (int i = 0; i < 10; ++i) {
		st.Push(i);
	}
	ASSERT_EQ(10, st.GetSize());
}
