#pragma once

#include "JuceHeader.h"
#include "ThumbnailComponent.h"
#include "FilePlayback.h"
#include "PositionOverlay.h"

class FilePlaybackComponent   : public juce::Component {
public:
    FilePlaybackComponent();

    void resized() override;
private:
    void openButtonClicked();
    void playButtonClicked();
    void stopButtonClicked();

    //==========================================================================
    juce::TextButton openButton;
    juce::TextButton playButton;
    juce::TextButton stopButton;

    std::unique_ptr<juce::FileChooser> chooser;

    FilePlayback playback;

    juce::AudioThumbnailCache thumbnailCache;
    ThumbnailComponent thumbnailComp;
    PositionOverlay positionOverlay;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FilePlaybackComponent)
};