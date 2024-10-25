#include "MusicPlayer.h"

MusicPlayer::MusicPlayer(vector<LyricEntry> lyrics,vector<int> melody,int sleepTime)
    :lyrics(lyrics),melody(melody),sleepTime(sleepTime){}

void MusicPlayer::play()
{
    HMIDIOUT handle;
    midiOutOpen(&handle, 0, 0, 0, CALLBACK_NULL);
    midiOutShortMsg(handle,34<<8|0xC0);

    int volume=0x7f;
    int voice=0x0;
    int current_time=0;

    vector<int> original_time;
    for(const auto& entry:lyrics)
    {
        original_time.push_back(entry.time);
    }

    for(auto& i:melody)
    {
        if(i==LOW_SPEED||i==MIDDLE_SPEED||i==HIGH_SPEED)
        {
            sleepTime=i;
            continue;
        }
        if(i==0)
        {
            sleepTime=175;
            continue;
        }
        if(i==700)
        {
            Sleep(175);
            continue;
        }
        if (i == _) 
        {
            Sleep(350);
            continue;
        }

        bool lyricShow=false;
        for(auto& lyric:lyrics)
        {
            if(current_time>=lyric.time && !lyricShow)
            {
                cout<<lyric.text<<endl;
                lyric.time=INT_MAX;
                lyricShow=true;
                break;
            }
        }
        
        voice=(volume<<16)+(i<<8)+0x90;
        midiOutShortMsg(handle,voice);
        Sleep(sleepTime);
        current_time+=sleepTime;
    }

    for(size_t i=0;i<melody.size();i++)
    {
        lyrics[i].time=original_time[i];
    }
    
    midiOutClose(handle);
}