#ifndef SE_RENDER_H
#define SE_RENDER_H

//Standard library includes

//External library includes

//SE includes
#include <utility/Typedefs.h>

///Brief: virual base class for all other renders (renderers)

namespace se
{
namespace priv
{

class Render
{
public:
	
	Render() {};

	virtual void Initialize() = 0;
	virtual void Uninitialize() = 0;

	virtual void Update(SEfloat deltaTime) = 0;


protected:

	// SE_TODO : Add some logic to engine (set / get current render etc..)
	//(atm engine is hevaily being modified)

};





}// !namespace priv

}// !namespace se



#endif //! SE_RENDER_H