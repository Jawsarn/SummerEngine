#pragma once

//TODO:: Transform compnoent, not sure where I want the info, but I want it to be XMFLOAT4X4 if we're using windows, which puts me to the mood that we want some sort of interface to it, where
//the graphic and physics(?) engine can work around to get the directx values directly. This because the directX values can compute on the graphics drive in a nice way, and we can upload matrixes to
//graphic card diretly for drawing.

class TransformLibraryInterface
{
public:
	static TransformLibraryInterface* GetInstance();
	~TransformLibraryInterface();

protected:
	TransformLibraryInterface();

	static TransformLibraryInterface* m_Singleton;
};