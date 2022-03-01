#pragma once
#include "..\Q_Vector.h"


extern "C" COLORREF __declspec (dllexport) Plus30(COLORREF color);

extern "C" RGBQUAD __declspec (dllexport)  BrightnessFilter(RGBQUAD pixel, double Brightness, double IncomeBrightness);

extern "C" RGBQUAD __declspec (dllexport) KontrastFilter(RGBQUAD pixel, double Brightness, double IncomeBrightness);

extern "C" RGBQUAD __declspec (dllexport) BrightnessKontrastFilter(RGBQUAD pixel, double FirstValue, double SecondValue);