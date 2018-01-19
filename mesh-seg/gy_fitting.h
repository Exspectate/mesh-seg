#ifndef _GY_FITTING_H_
#define _GY_FITTING_H_
#pragma once
#include <vector>
#include <Eigen\Eigen>
#include "Point3d.h"

using namespace std;

void fittingPlane(vector<Point3d> &points, vector<Point3d> &plane); //�Ը����㼯�����һ��ƽ�档pointsΪ����ϵĵ㣬planeΪ��ϵ�ƽ��(�����ʾ)

void fittingLine(vector<Point3d> &points, vector<Point3d> &line); //�Ը����㼯�����һ��ֱ�ߡ�pointsΪ����ϵĵ㣬lineΪ��ϵ�ֱ��(�����ʾ)
#endif