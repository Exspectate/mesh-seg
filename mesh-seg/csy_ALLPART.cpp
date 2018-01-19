#include "csy_ALLPART.h"

ALLPART::ALLPART()
{
	this->f1 = new bsp_Frame1();
	this->f2 = new bsp_Frame2();
	this->f3 = new bsp_Frame3();
	this->leftVRudder = new VRudder();
	this->rightVRudder = new VRudder();
	this->pitchRudder = new PitchR();
	this->f1->belongTo = this;
	this->f2->belongTo = this;
	this->f3->belongTo = this;
}

ALLPART::~ALLPART()
{
	delete(f1);
	delete(f2);
	delete(f3);
	delete(leftVRudder);
	delete(rightVRudder);
	delete(pitchRudder);
	
}

void ALLPART::initPartDATA(Mesh & mesh)
{
	this->leftVRudder->initSelectData(mesh,mesh.kind_color[5]);
	this->leftVRudder->findFeatureLines(mesh);
	this->leftVRudder->writeFeatureLinesToFile("DataFiles/LeftVFiles/");

	this->rightVRudder->initSelectData(mesh,mesh.kind_color[6]);
	this->rightVRudder->findFeatureLines(mesh);
	this->rightVRudder->writeFeatureLinesToFile("DataFiles/RightVFiles/");

	this->pitchRudder->initSelectData(mesh,mesh.kind_color[4]);
	this->pitchRudder->findFeatureLines(mesh);
	this->pitchRudder->writeFeatureLinesToFile("DataFiles/PitchFiles/");

	this->f1->initSelectData(mesh,mesh.kind_color[1]);
	this->f2->initSelectData(mesh,mesh.kind_color[2]);
	this->f3->initSelectData(mesh,mesh.kind_color[3]);

	this->f3->findRidgeLine(mesh);
	this->f3->findfeatureVerts(mesh);

	this->f2->findfeatureLines(mesh);
	this->f1->findfeatureLines(mesh);

	this->f3->findfeatureLines(mesh);
	this->f3->writeFeatureLinesToFile("DataFiles/Frame/");

}
