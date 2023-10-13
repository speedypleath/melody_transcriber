//
// Created by Andrei Gheorghe on 13.10.2023.
//

#pragma once
#include "JuceHeader.h"
#include "FilePlayback.h"

class ThumbnailComponent : public juce::Component,
                                 private juce::ChangeListener
{
public:
    ThumbnailComponent (int sourceSamplesPerThumbnailSample,
                              juce::AudioFormatManager& formatManager,
                              juce::AudioThumbnailCache& cache);

    void setFile (const juce::File& file);
    void paint (juce::Graphics& g) override;
    void changeListenerCallback (juce::ChangeBroadcaster* source) override;

private:
    juce::AudioThumbnail thumbnail;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ThumbnailComponent)
};


