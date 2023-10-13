#pragma once
#include <utility>

#include "JuceHeader.h"


enum TransportState
{
    Stopped,
    Starting,
    Pausing,
    Paused,
    Playing,
    Stopping
};
//==============================================================================
class FilePlayback   : public juce::AudioAppComponent,
                               public juce::ChangeListener
{
public:
    FilePlayback();
    ~FilePlayback() override;

    bool readFile(const File& file);
    void changeState (TransportState newState);

    double getLengthInSeconds() const;
    double getCurrentPosition() const;

    void seek(double d);
    AudioFormatManager formatManager;
private:
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;
    void changeListenerCallback (juce::ChangeBroadcaster* source) override;
    double lastPosition;
    TransportState state;
    std::unique_ptr<AudioFormatReaderSource> readerSource;
    AudioTransportSource transportSource;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FilePlayback)
};