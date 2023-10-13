#pragma once
#include "JuceHeader.h"
#include "FilePlayback.h"

class PositionOverlay : public juce::Component,
                        private juce::Timer
{
public:
    explicit PositionOverlay (FilePlayback& transportSourceToUse);

    void paint (juce::Graphics& g) override;
    void mouseDown (const juce::MouseEvent& event) override;
private:
    void timerCallback() override;
    FilePlayback& playback;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PositionOverlay)
};
