#include "stack.h"
#include <gtest.h>


TEST(TStack, can_create_stack_with_default_size) {
    ASSERT_NO_THROW(TStack<int> st());
}

TEST(TStack, can_create_stack_with_custom_size) {
    ASSERT_NO_THROW(TStack<int> st(5));
}

TEST(TStack, throws_exception_for_invalid_stack_size) {
    ASSERT_THROW(TStack<int> st(0), std::out_of_range);
}

TEST(TStack, new_stack_is_empty) {
    TStack<int> st;
    EXPECT_TRUE(st.IsEmpty());
}

TEST(TStack, full_stack_is_not_empty) {
    TStack<int> st(1);
    st.Push(1);
    EXPECT_FALSE(st.IsEmpty());
}

TEST(TStack, can_push_and_pop_element) {
    TStack<int> st;
    st.Push(1);
    ASSERT_EQ(1, st.Pop());
}

TEST(TStack, throws_exception_when_pop_from_empty) {
    TStack<int> st;
    ASSERT_THROW(st.Pop(), std::out_of_range);
}

TEST(TStack, can_double_size_when_full) {
    TStack<int> st(1);
    st.Push(1);
    st.Push(2);
    EXPECT_EQ(2, st.GetSize());
}

TEST(TStack, can_get_top_element) {
    TStack<int> st;
    st.Push(1);
    EXPECT_EQ(1, st.GetTop());
}

TEST(TStack, throws_exception_when_get_top_from_empty) {
    TStack<int> st;
    ASSERT_THROW(st.GetTop(), std::out_of_range);
}

TEST(TStack, push_increases_stack_size) {
    TStack<int> st;
    st.Push(1);
    EXPECT_FALSE(st.IsEmpty());
}

TEST(TStack, pop_decreases_stack_size) {
    TStack<int> st;
    st.Push(1);
    st.Pop();
    EXPECT_TRUE(st.IsEmpty());
}

TEST(TStack, stack_size_doubles_on_overflow) {
    TStack<int> st(1);
    st.Push(1);
    st.Push(2);
    st.Push(3);
    EXPECT_EQ(4, st.GetSize());
}

TEST(TStack, can_assign_moved_stack) {
    TStack<int> st1;
    st1.Push(1);
    TStack<int> st2 = std::move(st1);
    EXPECT_EQ(1, st2.Pop());
    EXPECT_EQ(st1.GetSize(), 0);
}
