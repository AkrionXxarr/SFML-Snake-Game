#include "App.hpp"
#include "MidiReader.hpp"

int main()
{
    /*
    MidiReader mr;

    mr.LoadMidi("Water_Level_fin.mid");
    u32 noteCount = mr.TempGetNoteCount();
    std::cout << noteCount;
    std::cout << std::endl;

    return 0;
    */

    App app(32, 32, "SnakeGame");

    app.Run();

    return 0;
}