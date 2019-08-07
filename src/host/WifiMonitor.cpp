#include "WifiMonitor.h"
#include "../utils/stream_op.h"

namespace sergomor
{

void WifiMonitor::tick()
{
	static uint8_t times = 0;
	if (waiting())
		return;

	wl_status_t _status = WiFi.status();

	if (status != _status && _status != WL_CONNECTED)
	{
		Serial << "connect to wifi" << endl;
	}

	if (_status != WL_CONNECTED && times_to_connect > times++)
	{
		Serial << ".";
	}
	else if (times_to_connect < times)
	{
		Serial << endl
			   << "connection failed" << endl;
		times = 0;
	}

	if (_status == WL_CONNECTED && status != _status)
	{
		Serial << "connected to " << WiFi.gatewayIP() << " with " << WiFi.localIP()
			   << endl;
	}

	status = _status;

	wait(1000);
}

} // namespace sergomor