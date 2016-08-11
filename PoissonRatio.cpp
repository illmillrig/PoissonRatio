
#include "PoissonRatio.h"
#include <maya/MFnNumericAttribute.h>
#include <maya/MFnEnumAttribute.h>
#include <maya/MVector.h>


MTypeId PoissonRatio::id = MTypeId(0x00121BD4);
MObject PoissonRatio::ratio;
MObject PoissonRatio::staticLength;
MObject PoissonRatio::dynamicLength;
MObject PoissonRatio::strain;


PoissonRatio::PoissonRatio() {}

PoissonRatio::~PoissonRatio() {}

void* PoissonRatio::creator() {
	return new PoissonRatio();
}

MStatus PoissonRatio::initialize() {
	// attributes are writable by default
	// attributes are storable by default
	// attributes are readable by default
	// attributes not keyable by default

    MStatus stat;
	MFnNumericAttribute fnNum;

    ratio = fnNum.create("ratio", "rat", MFnNumericData::kDouble, 0.0, &stat);
    CHECK_MSTATUS_AND_RETURN_IT(stat);
    fnNum.setKeyable(true);
    fnNum.setMin(-1.0);
    fnNum.setMax(1.0);
    stat = PoissonRatio::addAttribute(ratio);
    CHECK_MSTATUS_AND_RETURN_IT(stat);

    staticLength = fnNum.create("staticLength", "slen", MFnNumericData::kDouble, 0.0, &stat);
    CHECK_MSTATUS_AND_RETURN_IT(stat);
    fnNum.setKeyable(true);
    stat = PoissonRatio::addAttribute(staticLength);
    CHECK_MSTATUS_AND_RETURN_IT(stat);

    dynamicLength = fnNum.create("dynamicLength", "dlen", MFnNumericData::kDouble, 0.0, &stat);
    CHECK_MSTATUS_AND_RETURN_IT(stat);
    fnNum.setKeyable(true);
    stat = PoissonRatio::addAttribute(dynamicLength);
    CHECK_MSTATUS_AND_RETURN_IT(stat);

    strain = fnNum.create("strain", "strn", MFnNumericData::kDouble, 0.0, &stat);
    CHECK_MSTATUS_AND_RETURN_IT(stat);
    fnNum.setStorable(false);
    fnNum.setWritable(false);
    stat = PoissonRatio::addAttribute(strain);
    CHECK_MSTATUS_AND_RETURN_IT(stat);

    PoissonRatio::attributeAffects(ratio, strain);
    PoissonRatio::attributeAffects(staticLength, strain);
    PoissonRatio::attributeAffects(dynamicLength, strain);

    return MS::kSuccess;
}


MStatus PoissonRatio::compute(const MPlug &plug, MDataBlock &data) {

    if (plug != PoissonRatio::strain){
        return MS::kUnknownParameter;
    }

    double nu = data.inputValue(PoissonRatio::ratio).asDouble();
    double slen = data.inputValue(PoissonRatio::staticLength).asDouble();
    double dlen = data.inputValue(PoissonRatio::dynamicLength).asDouble();

    double strn = -(nu * ((dlen - slen) / slen));

    data.outputValue(PoissonRatio::strain).setDouble(strn);
    data.setClean(plug);

    return MS::kSuccess;
}



















