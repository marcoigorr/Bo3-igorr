#include "pch.h"
#include "Options.h"


void Options::SetAllFalse()
{
	for (int i = 0; i < 5; i++)
	{
		*options->features[i] = false;
	}
}

void Options::SetAllTrue()
{
	for (int i = 0; i < 5; i++)
	{
		*options->features[i] = true;
	}
}

Options* options = new Options();
