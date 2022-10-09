#pragma once

namespace jc::script::event
{
#ifdef JC_CLIENT
	static inline std::string ON_PLAYER_JOIN = "onClientPlayerJoin";
	static inline std::string ON_PLAYER_KILLED = "onClientPlayerKilled";
	static inline std::string ON_TICK = "onClientTick";
	static inline std::string ON_RSRC_START = "onClientResourceStart";
	static inline std::string ON_RSRC_STOP = "onClientResourceStop";
#else
	static inline std::string ON_PLAYER_JOIN = "onPlayerJoin";
	static inline std::string ON_PLAYER_KILLED = "onPlayerKilled";
	static inline std::string ON_TICK = "onTick";
	static inline std::string ON_RSRC_START = "onResourceStart";
	static inline std::string ON_RSRC_STOP = "onResourceStop";
#endif
}