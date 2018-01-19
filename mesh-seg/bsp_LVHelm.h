#pragma once
#include "bsp_part.h"
class bsp_LVHelm : public bsp_part
{
public:
	bsp_LVHelm();
	~bsp_LVHelm();

	void findfeatureLines(Mesh & mesh);
	void findfeatureVerts(Mesh & mesh);
	void initSelectData(Mesh & mesh, int color);	//≥ı ºªØ


	
};

