#pragma once

#include <bass.h>
#include <string>
#include <vector>
#include "spdlog/spdlog.h"
struct MusicSettings {
	std::string music_path;
	std::string music_type;
	std::string music_name;
	std::string music_author;
};
std::vector<MusicSettings> MusicNumber;
namespace cte {
	class Music
	{
	public:
		bool intBass();
		void musicPlayback(std::string path);
		void startPlayback(HSTREAM stream);
		void bassStop(HSTREAM stream);
		void waitMusicFinishPlay(HSTREAM stream, std::string file_name = "Î´ÃüÃûmp3ÎÄ¼þ");
		void bassCleanup(HSTREAM stream);
		void setMusicNumber(int number);
	};
}//namespace cte
