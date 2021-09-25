#include "OptionsManager.h"

#if defined(_WIN32) || defined(__riscos__)
    #include <SDL.h>
#elif defined(__vita__)
    #include <psp2/io/stat.h>
#else
    #include <sys/stat.h>
#endif

void OptionsManager::loadResources()
{
    loadOptions();
}

std::string OptionsManager::getOptionsDir() 
{
    std::string optionsPath;

    #if defined(_WIN32) || defined(__riscos__)
        char *prefPath = SDL_GetPrefPath(NULL, "freegemas");
        if (prefPath) {
            optionsPath = prefPath;
        } else {
            optionsPath = "./";
        }
    #elif defined(__vita__)
        optionsPath = "ux0:/data/freegemas/";

        // Make sure the directory exists
        sceIoMkdir(optionsPath.c_str(), 0755);
    #else
        char *xdgConfHome = getenv("XDG_CONFIG_HOME");
        if (xdgConfHome) {
            optionsPath = std::string(xdgConfHome) + "/freegemas/";
        } else {
            char *home = getenv("HOME");
            if (home) {
                optionsPath = std::string(home) + "/.config/freegemas/";
            } else {
                optionsPath = "./";
            }
        }

        // Make sure the directory exists
        mkdir(optionsPath.c_str(), 0755);
    #endif

    return optionsPath;
}

void OptionsManager::writeOptions()
{
    std::string optionsPath = getOptionsDir() + optionsFile;
    std::ofstream optionsStream(optionsPath, std::ios::binary);
    optionsStream << options;
    optionsStream.close();
}

void OptionsManager::loadOptions()
{
    std::ifstream optionsStream;
    std::string optionsPath = getOptionsDir() + optionsFile;
    optionsStream.open(optionsPath, std::ios::in);

    Json::CharReaderBuilder builder;
    JSONCPP_STRING errs;
    parseFromStream(builder, optionsStream, &options, &errs);
    optionsStream.close();
}

void OptionsManager::setHighscoreTimetrial(int score) {
    options["highscoreTimetrial"] = score;
    writeOptions();
}

void OptionsManager::setHighscoreEndless(int score) {
    options["highscoreEndless"] = score;
    writeOptions();
}

void OptionsManager::setMusicEnabled(bool value) {
    options["musicEnabled"] = value;
    writeOptions();
}

void OptionsManager::setSoundEnabled(bool value) {
    options["soundEnabled"] = value;
    writeOptions();
}

void OptionsManager::setFullscreenEnabled(bool value) {
    options["fullscreenEnabled"] = value;
    writeOptions();
}

int OptionsManager::getHighscoreTimetrial() {
    return options.get("highscoreTimetrial", 0).asInt();
}

int OptionsManager::getHighscoreEndless() {
    return options.get("highscoreEndless", 0).asInt();
}

bool OptionsManager::getMusicEnabled() {
    return options.get("musicEnabled", true).asBool();
}

bool OptionsManager:: getSoundEnabled() {
    return options.get("soundEnabled", true).asBool();
}

bool OptionsManager:: getFullscreenEnabled() {
    return options.get("fullscreenEnabled", false).asBool();
}
