#include "Music.hpp"
namespace cte {
	
	bool Music::intBass() {
		if (!BASS_Init(-1, 44100, 0, 0, 0)) {
			spdlog::error("BASS_Init error: ", BASS_ErrorGetCode());
			return 0;
		}
		return 1;
	}
	void Music::musicPlayback(std::string path) {
		HSTREAM stream = BASS_StreamCreateFile(false, path.c_str(), 0, 0, BASS_SAMPLE_LOOP);
		return;
	}
	void Music::startPlayback(HSTREAM stream) {
		BASS_ChannelPlay(stream, false);
		return;
	}
	void Music::bassStop(HSTREAM stream) {
		BASS_ChannelStop(stream);
	}
	void Music::waitMusicFinishPlay(HSTREAM stream,std::string file_name = "未命名mp3文件") {
		spdlog::info("开始播放:" + file_name);
		while (BASS_ChannelIsActive(stream) == BASS_ACTIVE_PLAYING) {
			BASS_ChannelUpdate(stream, 0);
		}
		spdlog::info("播放完毕");
	}
	void Music::bassCleanup(HSTREAM stream) {
		BASS_StreamFree(stream);
		BASS_Free();
	}
	void Music::setMusicNumber(int newSize) {
		MusicNumber.resize(newSize);
	}
}