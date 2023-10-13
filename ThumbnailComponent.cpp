//
// Created by Andrei Gheorghe on 13.10.2023.
//

#include "ThumbnailComponent.h"

ThumbnailComponent::ThumbnailComponent(int sourceSamplesPerThumbnailSample,
                    juce::AudioFormatManager& formatManager,
                    juce::AudioThumbnailCache& cache)
        : thumbnail (sourceSamplesPerThumbnailSample, formatManager, cache) {
    thumbnail.addChangeListener (this);
}

void ThumbnailComponent::setFile(const juce::File &file) {
    thumbnail.setSource (new juce::FileInputSource (file));
}

void ThumbnailComponent::paint(juce::Graphics &g) {
    if (thumbnail.getNumChannels() == 0) {
        g.fillAll (juce::Colours::white);
        g.setColour (juce::Colours::darkgrey);
        g.drawFittedText ("No File Loaded", getLocalBounds(), juce::Justification::centred, 1);
    }
    else {
        g.fillAll(juce::Colours::white);
        g.setColour(juce::Colours::red);
        thumbnail.drawChannels(g, getLocalBounds(), 0.0, thumbnail.getTotalLength(), 1.0f);
    }
}

void ThumbnailComponent::changeListenerCallback(juce::ChangeBroadcaster *source) {
    if (source == &thumbnail)
        repaint();
}