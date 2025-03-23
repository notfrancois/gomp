#include <iostream>

#include <gomp/api.hpp>
#include <gomp/Gomp.hpp>

#ifdef __cplusplus
extern "C"
{
#endif

	GOMPONENT_EXPORT unsigned char customModel_add(uint8_t type, int32_t id, int32_t baseId, String dffName, String txdName, int32_t virtualWorld, uint8_t timeOn, uint8_t timeOff)
	{
		ICustomModelsComponent* models = Gomp::Get()->models;

		if (models)
		{
			return models->addCustomModel(ModelType(type), id, baseId, StringView(dffName.buf, dffName.length), StringView(txdName.buf, txdName.length), virtualWorld, timeOn, timeOff) ? 1 : 0;
		}

		return 0;
	}

	GOMPONENT_EXPORT String customModel_getNameFromCheckSum(uint32_t checksum)
	{
		ICustomModelsComponent* models = Gomp::Get()->models;

		if (models)
		{
			StringView nameView = models->getModelNameFromChecksum(checksum);
			return { nameView.data(), nameView.length() };
		}

		return {NULL, 0};
	}

	GOMPONENT_EXPORT unsigned char customModel_isValid(int32_t modelId)
	{
		ICustomModelsComponent* models = Gomp::Get()->models;

		if (!models)
		{
			return 0;
		}

		return models->isValidCustomModel(modelId) ? 1 : 0;
	}

	GOMPONENT_EXPORT unsigned char customModel_getPath(int32_t modelId, String* dffPath, String* txdPath)
	{
		ICustomModelsComponent* models = Gomp::Get()->models;

		if (!models)
		{
			return 0;
		}

		StringView dffPathView {};
		StringView txdPathView {};

		bool status = models->getCustomModelPath(modelId, dffPathView, txdPathView);

		*dffPath = { dffPathView.data(), dffPathView.length() };
		*txdPath = { txdPathView.data(), txdPathView.length() };

		return status ? 1 : 0;
	}

#ifdef __cplusplus
}
#endif
