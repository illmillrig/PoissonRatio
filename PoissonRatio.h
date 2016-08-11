#pragma once


#include <maya/MPxNode.h>


class PoissonRatio : public MPxNode {

public:
	PoissonRatio();
	virtual ~PoissonRatio();
	static void* creator();
	static MStatus initialize();
	virtual MStatus compute( const MPlug& plug, MDataBlock& data );
    virtual MPxNode::SchedulingType schedulingType() const override { return MPxNode::kParallel; }

public:
	static MTypeId id;
    static MObject ratio;
    static MObject staticLength;
    static MObject dynamicLength;
    static MObject strain;
};

