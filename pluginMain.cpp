
#include "PoissonRatio.h"

#include <maya/MFnPlugin.h>


MStatus initializePlugin( MObject obj ) {
	MStatus stat;
	MFnPlugin plugin(obj, "Travis Miller", "2016", "Any");

	stat = plugin.registerNode( "poissonRatio", PoissonRatio::id, PoissonRatio::creator,
								  PoissonRatio::initialize );
	if (!stat) {
		stat.perror("registerNode");
		return stat;
	}

	return stat;
}


MStatus uninitializePlugin( MObject obj) {
	MStatus stat;
	MFnPlugin plugin( obj );

	stat = plugin.deregisterNode( PoissonRatio::id );
	if (!stat) {
		stat.perror("deregisterNode");
		return stat;
	}

	return stat;
}
