

// want to create a class for maya deformer node

#include "maya/MFnPlugin.h"
#include "maya/MGlobal.h"
#include "maya/MStatus.h"
#include "maya/MString.h"
#include "maya/MTypeId.h"
#include "maya/MObject.h"

class MadoodiaDeformer : public MPxDeformerNode
{
public:
  MadoodiaDeformer();
  virtual ~MadoodiaDeformer();

  static void* creator();
  static MStatus initialize();

  virtual MStatus deform(MDataBlock& data, MItGeometry& iter, const MMatrix& mat, unsigned int multiIndex);

  static MTypeId id;
  static MObject aInput;
  static MObject aOutput;
};

MTypeId MadoodiaDeformer::id(0x00000001);
MObject MadoodiaDeformer::aInput;
MObject MadoodiaDeformer::aOutput;

MadoodiaDeformer::MadoodiaDeformer() {}
MadoodiaDeformer::~MadoodiaDeformer() {}

void* MadoodiaDeformer::creator()
{
  return new MadoodiaDeformer();
}

MStatus MadoodiaDeformer::initialize()
{
  MFnNumericAttribute nAttr;
  MStatus status;

  aInput = nAttr.create("input", "in", MFnNumericData::kFloat, 0.0, &status);
  CHECK_MSTATUS_AND_RETURN_IT(status);
  nAttr.setKeyable(true);
  nAttr.setStorable(true);
  nAttr.setReadable(true);
  nAttr.setWritable(true);

  aOutput = nAttr.create("output", "out", MFnNumericData::kFloat, 0.0, &status);
  CHECK_MSTATUS_AND_RETURN_IT(status);
  nAttr.setKeyable(true);
  nAttr.setStorable(true);
  nAttr.setReadable(true);
  nAttr.setWritable(true);

  addAttribute(aInput);
  addAttribute(aOutput);

  attributeAffects(aInput, outputGeom);
  attributeAffects(aOutput, outputGeom);

  return MS::kSuccess;
}

MStatus MadoodiaDeformer::deform(MDataBlock& data, MItGeometry& iter, const MMatrix& mat, unsigned int multiIndex)
{
  MStatus status;

  MDataHandle hInput = data.inputValue(aInput, &status);
  CHECK_MSTATUS_AND_RETURN_IT(status);
  float input = hInput.asFloat();

  MDataHandle hOutput = data.inputValue(aOutput, &status);
  CHECK_MSTATUS_AND_RETURN_IT(status);
  float output = hOutput.asFloat();

  MArrayDataHandle hInputGeom = data.inputArrayValue(input, &status);
  CHECK_MSTATUS_AND_RETURN_IT(status);
  hInputGeom.jumpToArrayElement(multiIndex);
  MObject oInputGeom = hInputGeom.inputValue().child(inputGeom).asMesh();

  MPointArray points;
  iter.allPositions(points, MSpace::kObject);

  MItMeshVertex vertIter(oInputGeom, &status);
  CHECK_MSTATUS_AND_RETURN_IT(status);

  for (; !vertIter.isDone(); vertIter.next())
  {
    int id = vertIter.index();
    MPoint p = points[id];
    p.x += input;
    p.y += output;
    points.set(p, id);
  }

  iter.setAllPositions(points);

  return MS::kSuccess;
}
// ------------------------------

// ------------------------------
MStatus initializePlugin(MObject obj)
{
  MStatus status;
  MFnPlugin plugin(obj, "Madoodia", "1.0", "Any");

  status = plugin.registerNode("madoodiaDeformer", MadoodiaDeformer::id, MadoodiaDeformer::creator, MadoodiaDeformer::initialize, MPxNode::kDeformerNode);
  CHECK_MSTATUS_AND_RETURN_IT(status);

  return MS::kSuccess;
}

MStatus uninitializePlugin(MObject obj)
{
  MStatus status;
  MFnPlugin plugin(obj);

  status = plugin.deregisterNode(MadoodiaDeformer::id);
  CHECK_MSTATUS_AND_RETURN_IT(status);

  return MS::kSuccess;
}