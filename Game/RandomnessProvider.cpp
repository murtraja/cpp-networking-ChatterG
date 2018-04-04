#include "stdafx.h"
#include "RandomnessProvider.h"


CRandomnessProvider::CRandomnessProvider()
	: m_randomGeneratorEngine(time(0))
{
}


CRandomnessProvider& CRandomnessProvider::GetInstance()
{
	static CRandomnessProvider randomnessProvider;
	return randomnessProvider;
}

CRandomnessProvider::~CRandomnessProvider()
{
}

int CRandomnessProvider::GetRandomNumberInclusive(int low, int high)
{
	std::uniform_int_distribution<int> distribution(low, high);
	return distribution(m_randomGeneratorEngine);
}
