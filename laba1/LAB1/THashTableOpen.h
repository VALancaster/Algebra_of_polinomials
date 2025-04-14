#ifndef THASHTABLEOPEN_H
#define THASHTABLEOPEN_H

#include "TTable.h"
#include <vector>
#include <iostream>
#include <optional> // Для std::nullopt

using namespace std;

template <typename TKey, typename TValue>
class THashTableOpen : public TTable<TKey, TValue> // хеш-таблица с открытым перемешиванием
{
    enum class CellState { 
        EMPTY, // никогда не содержала данных
        OCCUPIED, // хранит актуальные данные
        DELETED // помечена как удаленная, но может быть переиспольована
    };

    struct Cell
    {
        TKey key;
        TValue value;
        CellState state; // текущее состояние (EMPTY/ OCCUPIED/ DELETED)
    };

    vector<Cell> data;
    size_t itemCount = 0; // cчетчик элементов/записей в таблице 
    size_t capacity; // емкость таблицы

    size_t HashFunction(const TKey& key) const
    {
        return hash<TKey>()(key) % capacity;
    }

    size_t Probe(size_t index, size_t attempt) const
    {
        return (index + attempt) % capacity;
    }

    void Rehash()
    {
        capacity *= 2;
		vector<Cell> newData(capacity);
        swap(data, newData);
        itemCount = 0;

        for (const auto& cell : newData)
        {
            if (cell.state == CellState::OCCUPIED)
            {
                Insert(cell.key, cell.value);
            }
        }
    }

public:
    THashTableOpen(size_t initialCapacity = 16) : capacity(initialCapacity)
    {
        data.resize(capacity);
    }

    string GetName() const override
    {
        return "Hash Table Open";
    }

    size_t size() const noexcept override
    {
        return itemCount;
    }

    void Insert(const TKey& key, const TValue& value) override
    {
        if (itemCount >= capacity * 0.7)
        {
            Rehash();
        }

        size_t attempt = 0; // счетчик попыток (для пробирования)
		size_t index = HashFunction(key);
        size_t firstDeleted = capacity; // запоминаем первую DELETED-ячейку

        while (attempt < capacity) // поиск места для вставки по всей таблице
        {
            auto& cell = data[index]; // текущая ячейка
            if (cell.state == CellState::OCCUPIED && cell.key == key) // ключ уже существует
            {
                cell.value = value; // перезаписали значение
				return; 
            }
            if (cell.state == CellState::DELETED && firstDeleted == capacity) // ячейка была удалена
            {
                firstDeleted = index; // запомнили ее
            }
            if (cell.state == CellState::EMPTY) // найдена пустая ячейка
            {
                if (firstDeleted != capacity) // если до этого была DELETED - ячейка
                {
                    index = firstDeleted; // вставляем в нее
                }
                data[index] = { key, value, CellState::OCCUPIED }; // успешно вставили
				itemCount++;
                return;
            }
            index = Probe(HashFunction(key), ++attempt); // вычисляет следующий индекс для проверки
        }

        if (firstDeleted != capacity)
        {
            data[firstDeleted] = {key, value, CellState::OCCUPIED};
            itemCount++;
        }
    }

    void Delete(const TKey& key) override
    {
        size_t attempt = 0; // счетчик попыток (для пробирования)
		size_t index = HashFunction(key);

        while (attempt < capacity)
        {
			auto& cell = data[index]; // текущая ячейка
            if (cell.state == CellState::EMPTY) // найдена пустая ячейка
            {
                break;
            }
            if (cell.state == CellState::OCCUPIED && cell.key == key) // ключ существует
            {
                cell.state = CellState::DELETED; 
                itemCount--;
                return;
            }
			index = Probe(HashFunction(key), ++attempt); // вычисляет следующий индекс для проверки
        }
    }

    TValue* Find(const TKey& key) override
    {
		size_t attempt = 0; // счетчик попыток (для пробирования)
        size_t index = HashFunction(key);

        while (attempt < capacity)
        {
			auto& cell = data[index]; // текущая ячейка
            if (cell.state == CellState::EMPTY) // найдена пустая ячейка
            {
                break;
            }
            if (cell.state == CellState::OCCUPIED && cell.key == key) // ключ существует
            {
				return &cell.value; // возвращает значение
            }
            index = Probe(HashFunction(key), ++attempt); // вычисляет следующий индекс для проверки
        }
        return nullptr;
    }

    void Print() const override
    {
        cout << "Hash Table Open Contents:" << endl;
        for (size_t i = 0; i < capacity; ++i)
        {
			const auto& cell = data[i]; // текущая ячейка
            if (cell.state == CellState::OCCUPIED)
            {
                cout << "Key: " << cell.key << ", Value: " << cell.value << endl;
            }
        }
    }

    TValue& operator[](const TKey& key)
    {
        size_t attempt = 0; // счетчик попыток (для пробирования)
        size_t index = HashFunction(key);
        while (attempt < capacity)
        {
            auto& cell = data[index]; // текущая ячейка
            if (cell.state == CellState::OCCUPIED && cell.key == key)
            {
                return cell.value;
            }
            if (cell.state == CellState::EMPTY)
            {
                break;
            }
            index = Probe(HashFunction(key), ++attempt);
        }
        throw out_of_range("Key not found");
    }
};

#endif