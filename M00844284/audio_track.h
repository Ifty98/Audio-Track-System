#include <string>


class AudioTrack {
    private:
        std::string title;
        std::string artist;
        int duration;
        
    public:
        AudioTrack(std::string title, std::string artist, int duration) {
           this->title = title;
           this->artist = artist;
           this->duration = duration;
        }

        // Getters
        std::string getTitle() {
            return title;
        }
        
        std::string getArtist() {
            return artist;
        }
        
        int getDuration() {
            return duration;
        }
};
