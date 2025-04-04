#include "Controller.h"
#include <gtest.h>

// Тест на установку активной таблицы
TEST(Controller, can_set_active_table) {
    Controller controller;

    EXPECT_NO_THROW(controller.SetActiveTable(0));
    EXPECT_NO_THROW(controller.SetActiveTable(1));
    EXPECT_THROW(controller.SetActiveTable(-1), std::out_of_range);
    EXPECT_THROW(controller.SetActiveTable(10), std::out_of_range);

    controller.SetActiveTable(1);
    ASSERT_EQ(controller.GetActiveTableIndex(), 1); // Предполагается, что метод GetActiveTableIndex существует для проверки текущей активной таблицы.
}

// Тест на добавление полинома
TEST(Controller, can_add_polinom) {
    Controller controller;
    Polinom p("x^2 + y + z");

    EXPECT_NO_THROW(controller.AddPolinom("testPolinom1", p));
    EXPECT_NO_THROW(controller.AddPolinom("testPolinom2", p));

    // Проверяем корректность добавления в активную таблицу
    controller.SetActiveTable(0); // Ставим активной первую таблицу
    EXPECT_TRUE(controller.GetActiveTable()->Find("testPolinom1")); // Предполагаем существование метода Find
    EXPECT_TRUE(controller.GetActiveTable()->Find("testPolinom2"));
}

// Тест на удаление полинома
TEST(Controller, can_delete_polinom) {
    Controller controller;
    Polinom p("x^2 + y + z");

    controller.AddPolinom("testPolinom", p);
    EXPECT_NO_THROW(controller.DeletePolinom("testPolinom"));

    controller.SetActiveTable(0); // Ставим активной первую таблицу
    EXPECT_FALSE(controller.GetActiveTable()->Find("testPolinom")); // Полином должен быть удалён
}

// Тест на вычисление выражения
TEST(Controller, can_evaluate_expression) {
    Controller controller;

    // Корректное выражение
    EXPECT_NO_THROW({
      double result = controller.EvaluateExpression("x^2 + y + z", 1, 2, 3);
      EXPECT_EQ(result, 1 * 1 + 2 + 3);
        });

    // Некорректное выражение
    EXPECT_THROW(controller.EvaluateExpression("x^2 + ", 1, 2, 3), std::exception);
}

// Тест на печать активной таблицы
TEST(Controller, can_print_active_table) {
    Controller controller;

    EXPECT_NO_THROW(controller.PrintActiveTable()); // Ничего не выбрасывается для активной таблицы
    controller.SetActiveTable(0);
    EXPECT_NO_THROW(controller.PrintActiveTable()); // Проверка активной таблицы
}

// Тест на корректное удаление объектов в деструкторе
TEST(Controller, destructor_frees_all_tables) {
    // Создаем контроллер в динамической памяти
    Controller* controller = new Controller();

    // Добавляем и удаляем полиномы
    Polinom p("x^2 + y + z");
    controller->AddPolinom("test", p);

    EXPECT_NO_THROW(delete controller); // Проверяем, что память освобождается без ошибок
}

// Тест на обработку пустого списка таблиц
TEST(Controller, handles_empty_table_list_gracefully) {
    // Создаём контроллер и удаляем все таблицы
    Controller controller;

    for (int i = 0; i < controller.GetTableCount(); i++)
        EXPECT_NO_THROW(controller.DeleteTable(i));

    EXPECT_ANY_THROW(controller.SetActiveTable(0)); // Нельзя установить активную таблицу, если их нет
    EXPECT_NO_THROW(controller.PrintActiveTable()); // Проверяет вывод с пустым списком таблиц
}

// Тест на работу с большим количеством таблиц
TEST(Controller, handles_large_number_of_tables) {
    Controller controller;

    // Добавляем дополнительные таблицы
    for (int i = 0; i < 100; i++) {
        auto newTable = new TArrayTable(); // Или другой тип таблицы
        EXPECT_NO_THROW(controller.AddTable(newTable));
    }

    EXPECT_NO_THROW(controller.SetActiveTable(99)); // Проверка последней таблицы
    ASSERT_EQ(controller.GetActiveTableIndex(), 99); // Убедимся, что активная таблица корректно установилась
    EXPECT_NO_THROW(controller.PrintActiveTable());
}