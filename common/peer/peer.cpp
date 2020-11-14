#include "peer.h"

peer::peer(const connection conn, const uint32_t sid, const uint32_t pid) 
	: _conn(conn), _sid(sid), _pid(pid)
{
	_last_time_refresh = std::chrono::steady_clock::now();
}

int peer::send_message(std::shared_ptr<media_core_message::message> mess)
{
	int result = _conn.send_message(mess);

	if (!result)
	{
		fresh();
	}

	return result;
}

void peer::fresh()
{
	_last_time_refresh = std::chrono::steady_clock::now();
}

bool peer::is_expires()
{
	return (std::chrono::steady_clock::now() - _last_time_refresh) > std::chrono::seconds(120);
}

const connection peer::get_connection()
{
	return _conn;
}

const uint32_t peer::get_pid()
{
	return _pid;
}

const uint32_t peer::get_sid()
{
	return _sid;
}

const uint32_t peer::get_type()
{
	return (_sid & 0xff000000) >> 24;
}

const uint32_t peer::get_load()
{
	return _load;
}

void peer::set_load(uint32_t load)
{
	_load = load;
}
