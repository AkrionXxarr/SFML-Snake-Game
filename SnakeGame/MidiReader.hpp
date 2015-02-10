#ifndef _MIDI_READER_HPP_
#define _MIDI_READER_HPP_

#include "General_Include.hpp"
#include "SFML_Include.hpp"

struct MidiHeader
{
    MidiHeader() : chunkId(0), chunkSize(0), formatType(0), numOfTracks(0), timeDivision(0)
    {
    }

    u32 chunkId;
    u32 chunkSize;
    u16 formatType;
    u16 numOfTracks;
    u16 timeDivision;
};

struct TrackData
{
    TrackData() : chunkId(0), chunkSize(0), eventData(NULL)
    {
    }

    u32 chunkId;
    u32 chunkSize;
    std::vector<u8> eventData;
};

struct EventData
{
    enum TYPE { NO_TYPE, CHANNEL, META, SYSEX };

    EventData() : dTime(0), type(NO_TYPE), eventType(0), param1(0), param2(0), metaType(0), length(0)
    {
    }

    u32 dTime;
    TYPE type;

    // Channel event
    u8 eventType;
    u8 param1, param2;

    // Meta event
    u8 metaType;
    u32 length;
    std::vector<u8> metaData;

    // SysEx event
};

struct Midi
{
    MidiHeader header;
    TrackData trackData;
};

class MidiReader
{
public:
    MidiReader();
    ~MidiReader();

public:
    bool LoadMidi(std::string filePath);

    EventData GetTrackData(u32 trackNum, u32& index);
    MidiHeader* const GetHeader() { return this->header; }
    std::vector<TrackData*>*const GetTracks() { return &(this->tracks); }

    void FragmentMidi();
    u32 TempGetNoteCount();

protected:
    bool loaded;
    MidiHeader* header;
    std::vector<TrackData*> tracks;
};

#endif