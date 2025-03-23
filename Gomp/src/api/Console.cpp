#include <iostream>

#include <gomp/api.hpp>
#include <gomp/Gomp.hpp>

#ifdef __cplusplus
extern "C"
{
#endif

	GOMPONENT_EXPORT void console_send(String command)
	{
		IConsoleComponent* console = Gomp::Get()->console;

		if (console)
		{
			console->send(StringView(command.buf, command.length));
		}
	}

#ifdef __cplusplus
}
#endif
