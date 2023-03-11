#include <audio/mixer/MixerControlsFactory.hpp>

#include <audio/core/ChannelFormat.hpp>
#include <audio/mixer/MainMixControls.hpp>
#include <audio/mixer/MixControls.hpp>
#include <audio/mixer/MixerControlsIds.hpp>
#include <control/CompoundControl.hpp>

using namespace ctoot::audio::mixer;
using namespace ctoot::audio::core;
using namespace ctoot::control;
using namespace std;

MixerControlsFactory::MixerControlsFactory()
{
}

void MixerControlsFactory::createBusStrips(weak_ptr<MixerControls> mixerControls, string mainStripName,
                                           weak_ptr<ChannelFormat> mainFormat, int nreturns)
{
    auto lMixerControls = mixerControls.lock();
    lMixerControls->createStripControls(MixerControlsIds::MAIN_STRIP, mainStripName);
    auto auxControls = lMixerControls->getAuxBusControls();
    auto naux = static_cast<int>(auxControls.size());
    for (int i = 0; i < naux; i++)
    {
        auto busControls = auxControls[i];
        lMixerControls->createStripControls(MixerControlsIds::AUX_STRIP, busControls->getName(), false);
    }
}

void MixerControlsFactory::createChannelStrips(weak_ptr<MixerControls> mixerControls, int nchannels)
{

    auto mbc = mixerControls.lock()->getMainBusControls().lock();
    auto mainFormat = mbc->getChannelFormat();
    for (int i = 0; i < nchannels; i++)
    {
        mixerControls.lock()->createStripControls(MixerControlsIds::CHANNEL_STRIP, to_string(1 + i));
    }
}

void MixerControlsFactory::addMixControls(MixerControls *mixerControls, weak_ptr<AudioControlsChain> controls,
                                          bool hasMixControls)
{
    auto lControls = controls.lock();
    int stripId = lControls->getId();

    if (stripId == MixerControlsIds::AUX_STRIP)
    {
        auto busControls = mixerControls->getBusControls(lControls->getName()).lock();
        if (busControls)
        {
            lControls->add(make_shared<MixControls>(mixerControls, stripId, busControls, true));
        }
    }

    auto mainMixControls = make_shared<MainMixControls>(mixerControls, stripId,
                                                        mixerControls->getMainBusControls().lock(),
                                                        stripId == MixerControlsIds::MAIN_STRIP);

    if (mixerControls->getMainBusControls().lock()->getId() == MixerControlsIds::MAIN_BUS)
    {
        auto routeControl = mainMixControls->createRouteControl(stripId);

        if (routeControl != nullptr)
        {
            mainMixControls->add(shared_ptr<Control>(routeControl));
        }
    }

    if (stripId != MixerControlsIds::MAIN_STRIP && stripId != MixerControlsIds::AUX_STRIP)
    {
        for (int i = 0; i < mixerControls->getAuxBusControls().size(); i++)
        {
            auto busControls = mixerControls->getAuxBusControls()[i];
            if (hasMixControls)
            {
                lControls->add(make_shared<MixControls>(mixerControls, stripId, busControls, false));
            }
        }
    }

    if (hasMixControls)
    {
        lControls->add(std::move(mainMixControls));
    }
}
