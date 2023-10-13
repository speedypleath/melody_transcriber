//
// Created by Andrei Gheorghe on 13.10.2023.
//

#include "FilePlaybackComponent.h"

FilePlaybackComponent::FilePlaybackComponent():
        thumbnailCache (5),
        thumbnailComp (512, playback.formatManager, thumbnailCache),
        positionOverlay (playback) {
    addAndMakeVisible (&openButton);
    openButton.setButtonText ("Open...");
    openButton.onClick = [this] { openButtonClicked(); };

    addAndMakeVisible (&playButton);
    playButton.setButtonText ("Play");
    playButton.onClick = [this] { playButtonClicked(); };
    playButton.setColour (juce::TextButton::buttonColourId, juce::Colours::green);
    playButton.setEnabled (false);

    addAndMakeVisible (&stopButton);
    stopButton.setButtonText ("Stop");
    stopButton.onClick = [this] { stopButtonClicked(); };
    stopButton.setColour (juce::TextButton::buttonColourId, juce::Colours::red);
    stopButton.setEnabled (false);

    addAndMakeVisible (&thumbnailComp);
    addAndMakeVisible (&positionOverlay);

    setSize (600, 400);
}

void FilePlaybackComponent::resized() {
    openButton.setBounds (10, 10, getWidth() - 20, 20);
    playButton.setBounds (10, 40, getWidth() - 20, 20);
    stopButton.setBounds (10, 70, getWidth() - 20, 20);

    juce::Rectangle<int> thumbnailBounds (10, 100, getWidth() - 20, getHeight() - 120);
    thumbnailComp.setBounds (thumbnailBounds);
    positionOverlay.setBounds (thumbnailBounds);
}

void FilePlaybackComponent::openButtonClicked() {
    chooser = std::make_unique<juce::FileChooser> ("Select a Wave file to play...",
                                                   juce::File{},
                                                   "*.wav");
    auto chooserFlags = juce::FileBrowserComponent::openMode
                        | juce::FileBrowserComponent::canSelectFiles;

    chooser->launchAsync (chooserFlags, [this] (const juce::FileChooser& fc) {
        auto file = fc.getResult();

        if (file != juce::File{}) {
            if (playback.readFile(file)) {
                thumbnailComp.setFile(file);
                playButton.setEnabled(true);
                stopButton.setEnabled(true);
            }
        }
    });
}

void FilePlaybackComponent::playButtonClicked() {
    if (playButton.getButtonText() == "Play") {
        playButton.setButtonText("Pause");
        playback.changeState(Starting);
    }
    else if(playButton.getButtonText() == "Pause") {
        playButton.setButtonText("Play");
        playback.changeState(Pausing);
    }
}

void FilePlaybackComponent::stopButtonClicked() {
    playButton.setButtonText("Play");
    playback.changeState(Stopping);
}