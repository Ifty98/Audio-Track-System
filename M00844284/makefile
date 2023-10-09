CXX = g++
CXXFLAGS = -Wall -Wextra -Wpedantic

audio: audio_system.cpp 
	$(CXX) $(CXXFLAGS) -o $@ $^

.PHONY: clean
clean:
	$(RM) *.o audio.exe
