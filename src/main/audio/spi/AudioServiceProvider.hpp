#pragma once

#include <service/ServiceProvider.hpp>
#include <audio/core/ChannelFormat.hpp>
#include <audio/core/AudioControls.hpp>
#include <audio/core/AudioProcess.hpp>

#include <memory>

namespace ctoot::audio::spi {

    class AudioServiceProvider
            : public ctoot::service::ServiceProvider
    {

    private:
        std::weak_ptr<std::vector<std::shared_ptr<ctoot::service::ServiceDescriptor>>> controls;

    public:
        virtual std::shared_ptr<ctoot::audio::core::AudioControls> createControls(int moduleId);

        virtual std::shared_ptr<ctoot::audio::core::AudioControls> createControls(const std::string &name);

        virtual std::shared_ptr<ctoot::audio::core::AudioControls>
        createControls(std::weak_ptr<service::ServiceDescriptor> d);

        virtual std::shared_ptr<ctoot::audio::core::AudioProcess>
        createProcessor(std::weak_ptr<audio::core::AudioControls> c)
        { return {}; };

    public:
        std::string getAvailableControls();

    public:
        AudioServiceProvider
                (
                        const std::string &providerName,
                        const std::string &description,
                        const std::string &version
                );

        AudioServiceProvider(const std::string &providerName)
        { this->providerName = providerName; }
    };
}
