#include "FilePlayback.h"

FilePlayback::FilePlayback(): lastPosition(0), state(Stopped) {
    formatManager.registerBasicFormats();
    transportSource.addChangeListener (this);
    setAudioChannels (2, 2);
}

FilePlayback::~FilePlayback() {
    shutdownAudio();
}

void FilePlayback::prepareToPlay (int samplesPerBlockExpected, double sampleRate) {
    transportSource.prepareToPlay (samplesPerBlockExpected, sampleRate);
}

void FilePlayback::getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill) {
    if (readerSource == nullptr)
    {
        bufferToFill.clearActiveBufferRegion();
        return;
    }

    transportSource.getNextAudioBlock (bufferToFill);
}

void FilePlayback::releaseResources() {
    transportSource.releaseResources();
}

void FilePlayback::changeListenerCallback(juce::ChangeBroadcaster *source) {
    if (source == &transportSource)
    {
        if (transportSource.isPlaying())
            changeState (Playing);
        else if (state == Pausing)
            changeState(Paused);
        else
            changeState (Stopped);
    }
}

void FilePlayback::changeState(TransportState newState) {
    if (state != newState)
    {
        state = newState;

        switch (state)
        {
            case Pausing:
                lastPosition = transportSource.getCurrentPosition();
                transportSource.stop();
                break;

            case Paused:
                break;

            case Stopping:
                lastPosition = 0.0;
                transportSource.sendChangeMessage();
                transportSource.stop();
                break;

            case Stopped:
                break;

            case Starting:
                transportSource.setPosition(lastPosition);
                transportSource.start();
                break;

            case Playing:
                break;
        }
    }
}

bool FilePlayback::readFile(const File& file) {
    auto* reader = formatManager.createReaderFor(file);

    if (reader != nullptr) {
        auto buffer = AudioBuffer<float>(2, roundToInt(reader->lengthInSamples));
        bool couldRead = reader->read(&buffer, 0, 0, roundToInt(reader->lengthInSamples), true, true);
        if(!couldRead)
            return false;

        auto newSource = std::make_unique<juce::AudioFormatReaderSource> (reader, true);
        transportSource.setSource(newSource.get(), 0, nullptr, reader->sampleRate);
        readerSource = std::move(newSource);
    }

    return true;
}

double FilePlayback::getLengthInSeconds() const {
    return transportSource.getLengthInSeconds();
}

double FilePlayback::getCurrentPosition() const {
    return transportSource.getCurrentPosition();
}

void FilePlayback::seek(double d) {
    transportSource.setPosition(d);
}
