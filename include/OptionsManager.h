#ifndef OPTIONS_MANAGER_H
#define OPTIONS_MANAGER_H

#include <string>
#include <fstream>
#include <json/json.h>

class OptionsManager
{
    public:
        void loadResources();

        void setHighscoreTimetrial(int score);
        void setHighscoreEndless(int score);
        void setMusicEnabled(bool value);
        void setSoundEnabled(bool value);
        void setFullscreenEnabled(bool value);

        int getHighscoreTimetrial();
        int getHighscoreEndless();
        bool getMusicEnabled();
        bool getSoundEnabled();
        bool getFullscreenEnabled();


    private:
        const std::string optionsFile = "options.json";

        Json::Value options;

        void writeOptions();
        void loadOptions();

        std::string getOptionsDir();
};

#endif