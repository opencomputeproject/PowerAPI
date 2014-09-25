#ifndef _PWR_OBJECTEL_H 
#define _PWR_OBJECTEL_H

#include <map>

#include "tinyxml2.h"
#include "objTreeNode.h"

struct _ObjEl : public ObjTreeNode
{
  public:
    _ObjEl( _Cntxt* ctx, TreeNode* parent, tinyxml2::XMLElement* el );
    ~_ObjEl();
    PWR_ObjType type() { return m_type; }
    _Grp* children();

    int attrGetNumber() { return m_attrVector.size(); }
    _Attr* attributeGet( int index ) { return m_attrVector[index]; }
    int attrIsValid( PWR_AttrName type ) { return 0; }

    TreeNode* findChild( const std::string name );
    TreeNode* findDev( const std::string name );

    int attrGetValue( PWR_AttrName, void*, size_t, PWR_Time* );
    int attrSetValue( PWR_AttrName, void*, size_t );

    int attrGetValues( const std::vector<PWR_AttrName>& types,
            void* ptr, std::vector<PWR_Time>& ts, std::vector<int>& status );
    int attrSetValues(  const std::vector<PWR_AttrName>& types,
            void* ptr, std::vector<int>& status );
  private:
    PWR_ObjType m_type;
    _Grp*       m_children;

    std::map< std::string, TreeNode* >       m_devices;

    tinyxml2::XMLElement*   m_xmlElement;
    std::vector< _Attr* >   m_attrVector;
};

inline TreeNode* createObj( _Cntxt* ctx, TreeNode* parent,
										tinyxml2::XMLElement* el )
{
	return rosebud( new _ObjEl( ctx, parent, el ) );
}

#endif
