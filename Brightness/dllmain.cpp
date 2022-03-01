// dllmain.cpp : Defines the entry point for the DLL application.
#include "TXLib.h"
#include "dllmain.h"



BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}



COLORREF Plus30(COLORREF color)
{
    COLORREF copyColor = color;

    int red = txExtractColor(color, TX_RED) + 30;
    int green = txExtractColor(color, TX_GREEN) + 30;
    int blue = txExtractColor(color, TX_BLUE) + 30;

    printf("Bibliothek is working\n");


    copyColor = RGB(red, green, blue);

    return copyColor;
}

/*
bool BrightnessFilter(Filter &filter, int screenSize, bool confirmBrightness, double Brightness, double IncomeBrightness)
{
	//nonConfirm = true;
	for (int x = filter.lastX; x < filter.lastX + filter.delta.x; x++)
	{
		for (int y = filter.lastY; y < filter.lastY + filter.delta.y; y++)
		{
			int pixelPos = x + (int)(screenSize - y) * (screenSize - 1);
			RGBQUAD pixel = filter.screen[pixelPos];
			double kOfBrightness = (double)((255 - Brightness) - (255 - IncomeBrightness)) / (255.0); //коэффициент
			double bOfBrightness = 255 - IncomeBrightness;	// b графика

			pixel.rgbRed = pixel.rgbRed * kOfBrightness + bOfBrightness;
			pixel.rgbGreen = pixel.rgbGreen * kOfBrightness + bOfBrightness;
			pixel.rgbBlue = pixel.rgbBlue * kOfBrightness + bOfBrightness;

			//finalDC   [pixelPos] = pixel; //DCMAXSIZE != size.x
			filter.tempScreen[pixelPos] = pixel;

			if (confirmBrightness)
			{
				filter.screen[int(x + (int)((filter.size.y - y)) * (filter.size.x - 1))] = pixel;
			}
		}
	}


	filter.lastY += filter.delta.y;
	filter.currentProgress++;
	if (filter.lastY >= filter.size.y)
	{
		filter.lastY = 0;
		filter.lastX += filter.delta.x;
	}
	if (filter.lastX >= filter.size.y)
	{
		filter.lastY = 0;
		filter.lastX = 0;
		filter.currentProgress = 0;
		return true;//reDraw
	}
	return false;

}  */

RGBQUAD BrightnessFilter(RGBQUAD pixel, double Brightness, double IncomeBrightness)
{
	double kOfBrightness = (double)((255 - Brightness) - (255 - IncomeBrightness)) / (255.0); //коэффициент
	double bOfBrightness = 255 - IncomeBrightness;	// b графика

	pixel.rgbRed = pixel.rgbRed * kOfBrightness + bOfBrightness;
	pixel.rgbGreen = pixel.rgbGreen * kOfBrightness + bOfBrightness;
	pixel.rgbBlue = pixel.rgbBlue * kOfBrightness + bOfBrightness;

	return pixel;
}

RGBQUAD KontrastFilter(RGBQUAD pixel, double FirstValue, double SecondValue)
{
	double kOfBrightness = FirstValue + 1; //коэффициент
	double bOfBrightness = SecondValue;	// b графика
	//printf("%lf %lf\n", kOfBrightness, bOfBrightness);
	

	int red =  (pixel.rgbRed - 128) * kOfBrightness + bOfBrightness + 128;
	pixel.rgbRed = red;
	if (red < 0) pixel.rgbRed = 0;
	if (red > 255) pixel.rgbRed = 255;

	int green = (pixel.rgbGreen - 128) * kOfBrightness + bOfBrightness + 128;
	pixel.rgbGreen = green;
	if (green < 0) pixel.rgbGreen = 0;
	if (green > 255) pixel.rgbGreen = 255;

	int blue = (pixel.rgbBlue - 128) * kOfBrightness + bOfBrightness + 128;
	pixel.rgbBlue = blue;
	if (blue < 0) pixel.rgbBlue = 0;
	if (blue > 255) pixel.rgbBlue = 255;

	return pixel;
}


//FirstValue (0 - 2.00)
RGBQUAD BrightnessKontrastFilter(RGBQUAD pixel, double FirstValue, double SecondValue)
{
	FirstValue += 100;
	FirstValue /= 100;
	//FirstValue += 100;
	//FirstValue /= 100;

	int red = (pixel.rgbRed) * FirstValue;
	pixel.rgbRed = red;
	if (red < 0) pixel.rgbRed = 0;
	if (red > 255) pixel.rgbRed = 255;
	 
	int green = (pixel.rgbGreen) * FirstValue;
	pixel.rgbGreen = green;
	if (green < 0) pixel.rgbGreen = 0;
	if (green > 255) pixel.rgbGreen = 255;
	 
	int blue = (pixel.rgbBlue) * FirstValue;
	pixel.rgbBlue = blue;
	if (blue < 0) pixel.rgbBlue = 0;
	if (blue > 255) pixel.rgbBlue = 255;

	return pixel;
}