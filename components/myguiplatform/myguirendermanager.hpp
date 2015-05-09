#ifndef OPENMW_COMPONENTS_MYGUIPLATFORM_MYGUIRENDERMANAGER_H
#define OPENMW_COMPONENTS_MYGUIPLATFORM_MYGUIRENDERMANAGER_H

#include <MyGUI_RenderManager.h>

#include <osg/ref_ptr>

namespace Resource
{
    class TextureManager;
}

namespace osgViewer
{
    class Viewer;
}

namespace osg
{
    class Group;
    class Camera;
    class RenderInfo;
}

namespace osgMyGUI
{

class Drawable;

class RenderManager : public MyGUI::RenderManager, public MyGUI::IRenderTarget
{
    osg::ref_ptr<osgViewer::Viewer> mViewer;
    osg::ref_ptr<osg::Group> mSceneRoot;
    osg::ref_ptr<Drawable> mDrawable;
    Resource::TextureManager* mTextureManager;

    MyGUI::IntSize mViewSize;
    bool mUpdate;
    MyGUI::VertexColourType mVertexFormat;
    MyGUI::RenderTargetInfo mInfo;

    typedef std::map<std::string, MyGUI::ITexture*> MapTexture;
    MapTexture mTextures;

    bool mIsInitialise;

    osg::ref_ptr<osg::Camera> mGuiRoot;

    void destroyAllResources();

public:
    RenderManager(osgViewer::Viewer *viewer, osg::Group *sceneroot, Resource::TextureManager* textureManager);
    virtual ~RenderManager();

    void initialise();
    void shutdown();

    static RenderManager& getInstance() { return *getInstancePtr(); }
    static RenderManager* getInstancePtr()
    { return static_cast<RenderManager*>(MyGUI::RenderManager::getInstancePtr()); }

    /** @see RenderManager::getViewSize */
    virtual const MyGUI::IntSize& getViewSize() const { return mViewSize; }

    /** @see RenderManager::getVertexFormat */
    virtual MyGUI::VertexColourType getVertexFormat() { return mVertexFormat; }

    /** @see RenderManager::isFormatSupported */
    virtual bool isFormatSupported(MyGUI::PixelFormat format, MyGUI::TextureUsage usage);

    /** @see RenderManager::createVertexBuffer */
    virtual MyGUI::IVertexBuffer* createVertexBuffer();
    /** @see RenderManager::destroyVertexBuffer */
    virtual void destroyVertexBuffer(MyGUI::IVertexBuffer *buffer);

    /** @see RenderManager::createTexture */
    virtual MyGUI::ITexture* createTexture(const std::string &name);
    /** @see RenderManager::destroyTexture */
    virtual void destroyTexture(MyGUI::ITexture* _texture);
    /** @see RenderManager::getTexture */
    virtual MyGUI::ITexture* getTexture(const std::string &name);

    // Called by the update traversal
    void update();

    // Called by the cull traversal
    /** @see IRenderTarget::begin */
    virtual void begin();
    /** @see IRenderTarget::end */
    virtual void end();
    /** @see IRenderTarget::doRender */
    virtual void doRender(MyGUI::IVertexBuffer *buffer, MyGUI::ITexture *texture, size_t count);

    /** @see IRenderTarget::getInfo */
    virtual const MyGUI::RenderTargetInfo& getInfo() { return mInfo; }

    bool checkTexture(MyGUI::ITexture* _texture);

/*internal:*/

    void collectDrawCalls();
    void setViewSize(int width, int height);
};

}

#endif