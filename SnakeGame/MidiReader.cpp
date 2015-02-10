#include <fstream>

#include "MidiReader.hpp"

MidiReader::MidiReader() : loaded(false)
{
}

MidiReader::~MidiReader()
{
    SAFE_DELETE(this->header);

    for (u32 i = 0; i < this->tracks.size(); i++)
    {
        SAFE_DELETE(this->tracks[i]);
    }
}

bool MidiReader::LoadMidi(std::string filePath)
{
    #define data(t) reinterpret_cast<char*>(&t)

    std::ifstream midiFile(filePath.c_str(), std::ios::binary);
    midiFile.imbue(std::locale::classic());

    if (!midiFile.is_open()) { return false; }

    this->header = new MidiHeader;

    u8 byte = 0;
    u32 temp = 0;

    this->header->chunkId |= (midiFile.get() << 24);
    this->header->chunkId |= (midiFile.get() << 16);
    this->header->chunkId |= (midiFile.get() << 8);
    this->header->chunkId |= (midiFile.get());

    this->header->chunkSize |= (midiFile.get() << 24);
    this->header->chunkSize |= (midiFile.get() << 16);
    this->header->chunkSize |= (midiFile.get() << 8);
    this->header->chunkSize |= (midiFile.get());

    this->header->formatType |= (midiFile.get() << 8);
    this->header->formatType |= (midiFile.get());

    this->header->numOfTracks |= (midiFile.get() << 8);
    this->header->numOfTracks |= (midiFile.get());

    this->header->timeDivision |= (midiFile.get() << 8);
    this->header->timeDivision |= (midiFile.get());

    for (u32 i = 0; i < this->header->numOfTracks; i++)
    {
        TrackData* t = new TrackData;

        t->chunkId |= (midiFile.get() << 24);
        t->chunkId |= (midiFile.get() << 16);
        t->chunkId |= (midiFile.get() << 8);
        t->chunkId |= (midiFile.get());

        t->chunkSize |= (midiFile.get() << 24);
        t->chunkSize |= (midiFile.get() << 16);
        t->chunkSize |= (midiFile.get() << 8);
        t->chunkSize |= (midiFile.get());

        for (u32 j = 0; j < t->chunkSize; j++)
        {
            t->eventData.push_back(u8(midiFile.get()));
        }

        this->tracks.push_back(t);
    }

    this->loaded = true;
    return true;
}

EventData MidiReader::GetTrackData(u32 trackNum, u32& index)
{
    EventData data;
    TrackData* track = this->tracks[trackNum];

    // Delta time
    for (u32 i = 0; i < 4; i++)
    {
        u8 temp = track->eventData[index++];
        data.dTime |= (temp & 0x7F);

        if ((temp & 0x80) != 0x80)  { break; }
        else { data.dTime <<= 7; }
    }

    // type
    data.eventType = track->eventData[index++];

    if (data.eventType == 0xFF)
    {
        // Meta
        data.type = data.META;
        data.metaType = track->eventData[index++];

        for (u32 i = 0; i < 4; i++)
        {
            u8 temp = track->eventData[index++];
            data.length |= (temp & 0x7F);

            if ((temp & 0x80) != 0x80)  { break; }
            else { data.length <<= 7; }
        }

        for (u32 i = 0; i < data.length; i++)
        {
            data.metaData.push_back(track->eventData[index++]);
        }
    }
    else if (data.eventType == 0xF0)
    {
        // SysEx
        data.type = data.SYSEX;
    }
    else if (data.eventType == 0xF7)
    {
        // Divided SysEx Finish
    }
    else
    {
        // Channel
        data.type = data.CHANNEL;

        u8 temp = data.eventType >> 4;
        
        switch (temp)
        {
        case 0x8:
            data.param1 = track->eventData[index++];
            data.param2 = track->eventData[index++];
            break;

        case 0x9:
            data.param1 = track->eventData[index++];
            data.param2 = track->eventData[index++];
            break;

        case 0xA:
            data.param1 = track->eventData[index++];
            data.param2 = track->eventData[index++];
            break;
            
        case 0xB:
            data.param1 = track->eventData[index++];
            data.param2 = track->eventData[index++];
            break;

        case 0xC:
            data.param1 = track->eventData[index++];
            break;

        case 0xD:
            data.param1 = track->eventData[index++];
            break;

        case 0xE:
            data.param1 = track->eventData[index++];
            data.param2 = track->eventData[index++];
            break;
        }
    }

    return data;
}

void MidiReader::FragmentMidi()
{
    /*
    if (!loaded) { return; }
    if (this->header->formatType == 0) { return; }

    for (u32 trackNum = 0; trackNum < this->tracks.size(); trackNum++)
    {
        // Store track data for like-deltas
        std::vector<
        TrackData* tData = this->tracks[trackNum];

        for (u32 i = 0; i < tData->chunkSize;)
        {
            EventData eData = this->GetTrackData(trackNum, i);
        }
    }
    */
}

u32 MidiReader::TempGetNoteCount()
{
    if (!loaded) { return 0; }

    u32 finalNoteCount = 0;
    u32 lastDeltaTime = 0;

    // A vector of vectors that will hold the "note on" delta times for each track
    std::vector<std::vector<u32> > deltaTimes;
    for (u32 trackNum = 0; trackNum < this->tracks.size(); trackNum++) { deltaTimes.push_back(std::vector<u32>()); }

    for (u32 trackNum = 0; trackNum < this->tracks.size(); trackNum++)
    {
        TrackData* t = this->tracks[trackNum];
        u32 tempNoteCount = 0;
        for (u32 i = 0; i < t->chunkSize;)
        {
            EventData data = this->GetTrackData(trackNum, i);
        
            if (data.type == data.CHANNEL)
            {
                u8 temp = data.eventType;

                if ((temp >> 4) == 0x9) 
                { 
                    deltaTimes[trackNum].push_back(data.dTime);
                }
            }
        }

        if (finalNoteCount < tempNoteCount) { finalNoteCount = tempNoteCount; }
    }

    std::cout << std::endl;

    return finalNoteCount;
}

