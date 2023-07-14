#include <DGM/classes/DynamicBuffer.hpp>
#include <catch2/catch_all.hpp>

struct Dummy
{
    int value;
};

TEST_CASE("[DynamicBuffer]")
{
    SECTION("Iterators")
    {
        SECTION("Basic iteration works")
        {
            dgm::DynamicBuffer<Dummy> buffer;
            buffer.emplaceBack(1);
            buffer.emplaceBack(2);
            buffer.emplaceBack(3);

            int value = 1;
            for (auto&& [dummy, _] : buffer)
            {
                REQUIRE(value == dummy.value);
                ++value;
            }
        }

        SECTION("Iterator correctly skips elements at the start")
        {
            dgm::DynamicBuffer<Dummy> buffer;
            buffer.emplaceBack(1);
            buffer.emplaceBack(2);
            buffer.eraseAtIndex(0);

            int value = 2;
            for (auto&& [dummy, _] : buffer)
            {
                REQUIRE(value == dummy.value);
                ++value;
            }
        }

        SECTION("Iterator skips deleted elements in the middle")
        {
            dgm::DynamicBuffer<Dummy> buffer;
            buffer.emplaceBack(1);
            buffer.emplaceBack(24);
            buffer.emplaceBack(69);
            buffer.emplaceBack(2);

            buffer.eraseAtIndex(1);
            buffer.eraseAtIndex(2);

            int value = 1;
            for (auto&& [dummy, _] : buffer)
            {
                REQUIRE(value == dummy.value);
                ++value;
            }
        }

        SECTION("Iterator correctly skips deleted elements at the end")
        {
            dgm::DynamicBuffer<Dummy> buffer;
            buffer.emplaceBack(1);
            buffer.emplaceBack(2);
            buffer.emplaceBack(24);
            buffer.eraseAtIndex(2);

            int value = 1;
            for (auto&& [dummy, _] : buffer)
            {
                REQUIRE(value == dummy.value);
                ++value;
            }
        }

        SECTION("Iterated item can be changed")
        {
            dgm::DynamicBuffer<Dummy> buffer;
            buffer.emplaceBack(1);

            for (auto&& [dummy, _] : buffer)
                dummy.value = 42;

            REQUIRE(buffer[0].value == 42);
        }
    }

    SECTION("Basic workflow")
    {
        SECTION("Can insert-delete-insert")
        {
            dgm::DynamicBuffer<Dummy> buffer;
            buffer.emplaceBack(1);
            buffer.emplaceBack(2);
            buffer.eraseAtIndex(0);
            buffer.emplaceBack(3);

            int value = 3;
            for (auto&& [dummy, _] : buffer)
            {
                REQUIRE(value == dummy.value);
                --value;
            }
        }
    }
}