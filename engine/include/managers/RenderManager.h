#ifndef SE_RENDER_MANAGER
#define SE_RENDER_MANAGER

namespace se
{
namespace priv
{

class RenderManager
{
public:

	///Default constructor
	RenderManager();

	///Default destructor
	~RenderManager();

	///Delete copy constructor
	RenderManager(const RenderManager&) = delete;

	///Delete copy assingment operator
	void operator=(const RenderManager&) = delete;

	///Initialize Render Manager
	void InitializeRenderManager();

	///Update render manager
	void UpdateRenderManager();


private:


};

}//namespace priv
}//namespace se

#endif // !SE_RENDER_MANAGER