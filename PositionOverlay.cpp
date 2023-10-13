//
// Created by Andrei Gheorghe on 13.10.2023.
//

#include "PositionOverlay.h"

PositionOverlay::PositionOverlay (FilePlayback& transportSourceToUse): playback (transportSourceToUse) {
    startTimer (40);
}

void PositionOverlay::paint(juce::Graphics &g) {
    auto duration = (float) playback.getLengthInSeconds();

    if (duration > 0.0)
    {
        auto audioPosition = (float) playback.getCurrentPosition();
        auto drawPosition = (audioPosition / duration) * (float) getWidth();

        g.setColour (juce::Colours::green);
        g.drawLine (drawPosition, 0.0f, drawPosition, (float) getHeight(), 2.0f);
    }
}

void PositionOverlay::mouseDown(const juce::MouseEvent &event) {
    auto duration = playback.getLengthInSeconds();

    if (duration > 0.0)
    {
        auto clickPosition = event.position.x;
        auto audioPosition = (clickPosition / (float) getWidth()) * duration;

        playback.seek(audioPosition);
    }
}

void PositionOverlay::timerCallback() {
    repaint();
}