#pragma once
class CRandomnessProvider
{
	std::mt19937 m_randomGeneratorEngine;
	CRandomnessProvider();
public:
	static CRandomnessProvider& GetInstance();
	~CRandomnessProvider();
	int GetRandomNumberInclusive(int lo, int hi);
};

