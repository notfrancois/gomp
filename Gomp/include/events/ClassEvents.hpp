#include <sdk.hpp>

#include <gomp/Singleton.hpp>
#include <gomp/Gamemode.hpp>

class ClassEvents : public ClassEventHandler, public Singleton<ClassEvents>
{
public:
	ClassEvents()
	{
		gamemode_ = Gamemode::Get();
	}

	bool onPlayerRequestClass(IPlayer& player, unsigned int classId) override
	{
		IClassesComponent* classes = Gomp::Get()->classes;
		IClass* _class = NULL;

		if (classes)
		{
			_class = classes->get(classId);
		}

		return gamemode_->call<unsigned char>("onPlayerRequestClass", static_cast<void*>(&player), static_cast<void*>(_class)) != 0;
	}

private:
	Gamemode* gamemode_;
};

