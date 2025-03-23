#include <gomp/api.hpp>
#include <gomp/Gomp.hpp>

#ifdef __cplusplus
extern "C"
{
#endif

	GOMPONENT_EXPORT void* textLabel_create(String text, uint32_t colour, float posX, float posY, float posZ, float drawDistance, int vw, unsigned char los)
	{
		ITextLabelsComponent* textlabels = Gomp::Get()->textlabels;

		if (textlabels)
		{
			ITextLabel* textlabel = textlabels->create(StringView(text.buf, text.length), Colour::FromRGBA(colour), Vector3(posX, posY, posZ), drawDistance, vw, los != 0);

			if (textlabel)
			{
				return static_cast<void*>(textlabel);
			}
		}

		return NULL;
	}

	GOMPONENT_EXPORT void textLabel_release(void* textLabel)
	{
		ITextLabelsComponent* textlabels = Gomp::Get()->textlabels;

		if (textlabels)
		{
			textlabels->release(static_cast<ITextLabel*>(textLabel)->getID());
		}
	}

	GOMPONENT_EXPORT void textLabel_setText(void* textLabel, String text)
	{
		static_cast<ITextLabel*>(textLabel)->setText(StringView(text.buf, text.length));
	}

	GOMPONENT_EXPORT String textLabel_getText(void* textLabel)
	{
		StringView textView = static_cast<ITextLabel*>(textLabel)->getText();

		return { textView.data(), textView.length() };
	}

	GOMPONENT_EXPORT void textLabel_setColour(void* textLabel, uint32_t colour)
	{
		static_cast<ITextLabel*>(textLabel)->setColour(Colour::FromRGBA(colour));
	}

	GOMPONENT_EXPORT uint32_t textLabel_getColour(void* textLabel)
	{
		return static_cast<ITextLabel*>(textLabel)->getColour().RGBA();
	}

	GOMPONENT_EXPORT void textLabel_setDrawDistance(void* textLabel, float drawDist)
	{
		static_cast<ITextLabel*>(textLabel)->setDrawDistance(drawDist);
	}

	GOMPONENT_EXPORT float textLabel_getDrawDistance(void* textLabel)
	{
		return static_cast<ITextLabel*>(textLabel)->getDrawDistance();
	}

	GOMPONENT_EXPORT void textLabel_attachToPlayer(void* textLabel, void* player, float offsetX, float offsetY, float offsetZ)
	{
		static_cast<ITextLabel*>(textLabel)->attachToPlayer(*static_cast<IPlayer*>(player), Vector3(offsetX, offsetY, offsetZ));
	}

	GOMPONENT_EXPORT void textLabel_attachToVehicle(void* textLabel, void* vehicle, float offsetX, float offsetY, float offsetZ)
	{
		static_cast<ITextLabel*>(textLabel)->attachToVehicle(*static_cast<IVehicle*>(vehicle), Vector3(offsetX, offsetY, offsetZ));
	}

	GOMPONENT_EXPORT TextLabelAttachmentData textLabel_getAttachmentData(void* textLabel)
	{
		return static_cast<ITextLabel*>(textLabel)->getAttachmentData();
	}

	GOMPONENT_EXPORT void textLabel_detachFromPlayer(void* textLabel, float posX, float posY, float posZ)
	{
		static_cast<ITextLabel*>(textLabel)->detachFromPlayer(Vector3(posX, posY, posZ));
	}

	GOMPONENT_EXPORT void textLabel_detachFromVehicle(void* textLabel, float posX, float posY, float posZ)
	{
		static_cast<ITextLabel*>(textLabel)->detachFromVehicle(Vector3(posX, posY, posZ));
	}

	GOMPONENT_EXPORT void textLabel_setTestLOS(void* textLabel, unsigned char status)
	{
		static_cast<ITextLabel*>(textLabel)->setTestLOS(status != 0);
	}

	GOMPONENT_EXPORT unsigned char textLabel_getTestLOS(void* textLabel)
	{
		return static_cast<ITextLabel*>(textLabel)->getTestLOS() ? 1 : 0;
	}

	GOMPONENT_EXPORT unsigned char textLabel_isStreamedInForPlayer(void* textLabel, void* player)
	{
		return static_cast<ITextLabel*>(textLabel)->isStreamedInForPlayer(*static_cast<IPlayer*>(player)) ? 1 : 0;
	}

	// entity

	GOMPONENT_EXPORT void textLabel_setPosition(void* textLabel, float posX, float posY, float posZ)
	{
		static_cast<ITextLabel*>(textLabel)->setPosition(Vector3(posX, posY, posZ));
	}

	GOMPONENT_EXPORT Vector3 textLabel_getPosition(void* textLabel)
	{
		return static_cast<ITextLabel*>(textLabel)->getPosition();
	}

	GOMPONENT_EXPORT void textLabel_setVirtualWorld(void* textLabel, int vw)
	{
		static_cast<ITextLabel*>(textLabel)->setVirtualWorld(vw);
	}

	GOMPONENT_EXPORT int textLabel_getVirtualWorld(void* textLabel)
	{
		return static_cast<ITextLabel*>(textLabel)->getVirtualWorld();
	}

	// PlayerTextLabel

	GOMPONENT_EXPORT void* playerTextLabel_create(void* player, String text, uint32_t colour, float posX, float posY, float posZ, float drawDistance, unsigned char los)
	{
		IPlayerTextLabelData* data = queryExtension<IPlayerTextLabelData>(static_cast<IPlayer*>(player));

		if (data)
		{
			IPlayerTextLabel* textlabel = data->create(StringView(text.buf, text.length), Colour::FromRGBA(colour), Vector3(posX, posY, posZ), drawDistance, los != 0);

			if (textlabel)
			{
				return static_cast<void*>(textlabel);
			}
		}

		return NULL;
	}

	GOMPONENT_EXPORT void playerTextLabel_release(void* textLabel, void* player)
	{
		IPlayerTextLabelData* data = queryExtension<IPlayerTextLabelData>(static_cast<IPlayer*>(player));

		if (data)
		{
			data->release(static_cast<IPlayerTextLabel*>(textLabel)->getID());
		}
	}

	GOMPONENT_EXPORT void playerTextLabel_setText(void* textLabel, String text)
	{
		static_cast<IPlayerTextLabel*>(textLabel)->setText(StringView(text.buf, text.length));
	}

	GOMPONENT_EXPORT String playerTextLabel_getText(void* textLabel)
	{
		StringView textView = static_cast<IPlayerTextLabel*>(textLabel)->getText();

		return { textView.data(), textView.length() };
	}

	GOMPONENT_EXPORT void playerTextLabel_setColour(void* textLabel, uint32_t colour)
	{
		static_cast<IPlayerTextLabel*>(textLabel)->setColour(Colour::FromRGBA(colour));
	}

	GOMPONENT_EXPORT uint32_t playerTextLabel_getColour(void* textLabel)
	{
		return static_cast<IPlayerTextLabel*>(textLabel)->getColour().RGBA();
	}

	GOMPONENT_EXPORT void playerTextLabel_setDrawDistance(void* textLabel, float drawDist)
	{
		static_cast<IPlayerTextLabel*>(textLabel)->setDrawDistance(drawDist);
	}

	GOMPONENT_EXPORT float playerTextLabel_getDrawDistance(void* textLabel)
	{
		return static_cast<IPlayerTextLabel*>(textLabel)->getDrawDistance();
	}

	GOMPONENT_EXPORT void playerTextLabel_attachToPlayer(void* textLabel, void* player, float offsetX, float offsetY, float offsetZ)
	{
		static_cast<IPlayerTextLabel*>(textLabel)->attachToPlayer(*static_cast<IPlayer*>(player), Vector3(offsetX, offsetY, offsetZ));
	}

	GOMPONENT_EXPORT void playerTextLabel_attachToVehicle(void* textLabel, void* vehicle, float offsetX, float offsetY, float offsetZ)
	{
		static_cast<IPlayerTextLabel*>(textLabel)->attachToVehicle(*static_cast<IVehicle*>(vehicle), Vector3(offsetX, offsetY, offsetZ));
	}

	GOMPONENT_EXPORT TextLabelAttachmentData playerTextLabel_getAttachmentData(void* textLabel)
	{
		return static_cast<IPlayerTextLabel*>(textLabel)->getAttachmentData();
	}

	GOMPONENT_EXPORT void playerTextLabel_detachFromPlayer(void* textLabel, float posX, float posY, float posZ)
	{
		static_cast<IPlayerTextLabel*>(textLabel)->detachFromPlayer(Vector3(posX, posY, posZ));
	}

	GOMPONENT_EXPORT void playerTextLabel_detachFromVehicle(void* textLabel, float posX, float posY, float posZ)
	{
		static_cast<IPlayerTextLabel*>(textLabel)->detachFromVehicle(Vector3(posX, posY, posZ));
	}

	GOMPONENT_EXPORT void playerTextLabel_setTestLOS(void* textLabel, unsigned char status)
	{
		static_cast<IPlayerTextLabel*>(textLabel)->setTestLOS(status != 0);
	}

	GOMPONENT_EXPORT unsigned char playerTextLabel_getTestLOS(void* textLabel)
	{
		return static_cast<IPlayerTextLabel*>(textLabel)->getTestLOS() ? 1 : 0;
	}

	// entity

	GOMPONENT_EXPORT void playerTextLabel_setPosition(void* textLabel, float posX, float posY, float posZ)
	{
		static_cast<IPlayerTextLabel*>(textLabel)->setPosition(Vector3(posX, posY, posZ));
	}

	GOMPONENT_EXPORT Vector3 playerTextLabel_getPosition(void* textLabel)
	{
		return static_cast<IPlayerTextLabel*>(textLabel)->getPosition();
	}

	GOMPONENT_EXPORT void playerTextLabel_setVirtualWorld(void* textLabel, int vw)
	{
		static_cast<IPlayerTextLabel*>(textLabel)->setVirtualWorld(vw);
	}

	GOMPONENT_EXPORT int playerTextLabel_getVirtualWorld(void* textLabel)
	{
		return static_cast<IPlayerTextLabel*>(textLabel)->getVirtualWorld();
	}

#ifdef __cplusplus
}
#endif
