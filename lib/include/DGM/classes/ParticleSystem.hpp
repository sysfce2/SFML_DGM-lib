#pragma once

#include <DGM/classes/Buffer.hpp>
#include <DGM/classes/Error.hpp>
#include <DGM/classes/ParticleSystemRenderer.hpp>
#include <DGM/classes/Time.hpp>
#include <DGM/classes/Window.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Vertex.hpp>

namespace dgm
{
    namespace ps
    {
        class Particle;

        /**
         *  \brief Interface and base implementation of ParticleSystem
         *
         *  \details Always inherit from this class when creating new
         *  particle system.
         */
        template<unsigned ParticleCount>
        class ParticleSystemInterface
        {
        public:
            [[nodiscard]] ParticleSystemInterface()
            {
                try
                {
                    renderer.init(ParticleCount);
                    for (unsigned i = 0; i < particles.getCapacity(); i++)
                    {
                        particles[i] =
                            createParticle(renderer.getParticleVertices(i), i);
                    }
                }
                catch (std::exception& e)
                {
                    throw dgm::Exception(e.what());
                }
            }

            ParticleSystemInterface(ParticleSystemInterface& other) = delete;
            [[nodiscard]] ParticleSystemInterface(
                ParticleSystemInterface&& other) = default;
            virtual ~ParticleSystemInterface() = default;

        public:
            /**
             *  \brief Render particle system to target window
             */
            void draw(dgm::Window& window)
            {
                window.draw(renderer);
            }

            /**
             *  \brief Bind the texture to the particle system
             *
             *  \param[in]  texture  Texture that will be used for particle
             * rendering
             *
             *  All particles must share the same texture, however they can be
             * textured/animated via clipping the texture.
             */
            void setTexture(sf::Texture& texture) noexcept
            {
                renderer.setTexture(texture);
            }

            /**
             *  \brief Update particle system
             *
             *  \details This is the only method you have to actually
             *  implement in your inherited particle system.
             */
            virtual void update(const dgm::Time& time) = 0;

        protected:
            /**
             *  \brief Method for creating particle objects
             *
             *  \param [in] vertices  Vertices for particle from VBO
             *  \param [in] id        Unique ID of particle
             *
             *  This method is called automatically during init() and
             *  serves the purpose of allocating memory for particles.
             *  If you can work with dgm::ps::Particle, you can ignore
             *  it, if you need ParticleSystem to work with your custom
             *  particle type, then override this method.
             *
             *  Index denotes the index in particles buffer.
             *
             *  \warn Do not call this method by yourself! It is only
             *  supposed to be called during init() to populate particles array.
             */
            virtual std::unique_ptr<dgm::ps::Particle>
            createParticle(sf::Vertex* vertices, unsigned) const
            {
                return std::make_unique<Particle>(vertices);
            }

        protected:
            dgm::ps::ParticleSystemRenderer renderer;
            Buffer<std::unique_ptr<dgm::ps::Particle>, ParticleCount> particles;
        };
    }; // namespace ps
};     // namespace dgm