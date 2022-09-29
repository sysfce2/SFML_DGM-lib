#pragma once

#include <DGM/classes/LoaderInterface.hpp>

namespace dgm
{

	/**
	 *  Class that can load certain dgm structures from JSON files or streams
	 */
	class JsonLoader final : public LoaderInterface
	{
	public:
		[[nodiscard]]
		virtual dgm::Clip loadClipFromFile(const std::string&) const override;

		[[nodiscard]]
		dgm::Clip loadClipFromStream(std::istream&) const;

		[[nodiscard]]
		virtual std::shared_ptr<dgm::AnimationStates> loadAnimationsFromFile(const std::string&) const override;

		[[nodiscard]]
		std::shared_ptr<dgm::AnimationStates> loadAnimationsFromStream(std::istream&) const;
	};
}