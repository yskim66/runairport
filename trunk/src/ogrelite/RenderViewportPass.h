#pragma once
#include "ogrelitePrefix.h"
#include "ogreliteptr.h"
#include "OgreColourValue.h"
#include "OgreCommon.h"
/*the object represent a render pass to the viewport
*/

BEGIN_NAMESPACE_OGRELITE
///virtual base class represent a render operation to  
//class 
class RenderViewport;
class RenderProcess
{
public:
	virtual void render(RenderViewport* pdest)=0;
	virtual ~RenderProcess(){}
protected:
	String sDesc;
};

// a group of render process
class RenderProcessSquence : public RenderProcess
{
protected:	
	//bool m_bParalle; //no effect yet
	void render(RenderViewport* pdest);
	virtual void preRenderSeq(){}
	virtual void postRenderSeq(){}
protected:
	typedef std::vector<RenderProcess*> SequenceProcessList;
	SequenceProcessList mSequenceProcesses;
	void processRenderSeq(RenderViewport* pdest);
};

//viewport layer to canvas 
class RenderCanvas;
class RenderViewport 
{
public:
	RenderViewport() 
		:mpRenerProcess(NULL)
		,mbVisible(true)
	{
	}
	virtual void renderTo(RenderCanvas* pCanvas);
	bool isVisible()const{ return mbVisible; }
	void setVisible(bool b){ mbVisible = b; }
	void setClearEveryFrame( unsigned int buffers = FBT_COLOUR | FBT_DEPTH);
protected:	
	RenderProcess* mpRenerProcess;		
	// Actual dimensions, based on target dimensions
	int mActLeft, mActTop, mActWidth, mActHeight;	
	/// Viewport orientation
	int mOrientation;
	/// Background options
	ColourValue mClearColour;
	float mClearDepth;
	int mClearStencil;
	unsigned int mClearBuffers;	
	bool mbVisible;
};


typedef nodelete_shared_ptr<RenderViewport> RenderViewportSharedPtr;

//render target
// window support or software support(FBO) which have , have buffers like pixel buffer , stencil buffer, depth buffer..
class RenderSystem;
class RenderCanvas
{
public:	
	virtual uint32 getWidth()const=0;
	virtual uint32 getHeigth()const=0;

	virtual RenderSystem* getSystem()=0;

	void renderOneFrame();
protected:
	virtual void _beginFrame()=0;
	virtual void _beginViewport(RenderViewport*player)=0;	
	virtual void _endFrame()=0;
protected:
	typedef std::list< RenderViewportSharedPtr > RenderLayerList;
	RenderLayerList mRenderLayList;

};
typedef nodelete_shared_ptr<RenderCanvas> RenderCanvasSharedPtr;
//////////////////////////////////////////////////////////////////////////
class RenderWindowCanvas : public RenderCanvas
{
public:
	virtual void swapBuffers(bool waitForVSync)=0;
};

//only manage create/destroy resource
class Texture
{
public:

};
typedef nodelete_shared_ptr<Texture> TextureSharedPtr;





END_NAMESPACE_OGRELITE