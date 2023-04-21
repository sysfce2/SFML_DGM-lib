#pragma once

#include <DGM/classes/Animation.hpp>
#include <DGM/classes/Clip.hpp>
#include <istream>

namespace dgm
{
    /**
     *  Interface class for a data loader
     *
     *  Currently used by ResourceManager so you can define your own format for
     * storing certain data structures.
     */
    class LoaderInterface
    {
    public:
        [[nodiscard]] virtual dgm::Clip
        loadClipFromFile(const std::string&) const = 0;

        [[nodiscard]] virtual dgm::AnimationStates
        loadAnimationsFromFile(const std::string&) const = 0;

        virtual ~LoaderInterface() = default;
    };

} // namespace dgm