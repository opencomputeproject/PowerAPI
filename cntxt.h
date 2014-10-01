#ifndef _PWR_CNTXT_h
#define _PWR_CNTXT_h

#include <string>
#include <deque>
#include <map>

#include "treeNode.h"
#include "util.h"
#include "types.h"
#include "dev.h"

namespace PowerAPI {

struct Grp;
class ObjTreeNode;
class Config;

struct Cntxt {

  public:

    Cntxt( PWR_CntxtType type, PWR_Role role, const char* name );
    ~Cntxt( );

	void initAttr( TreeNode*, TreeNode::AttrEntry& );
	ObjTreeNode* findNode( std::string name );
	Grp* findChildren( ObjTreeNode* );

    ObjTreeNode* getSelf();

    Grp* getGrp( PWR_ObjType type ) {
        Grp* grp = getGrpByName( objTypeToString( type ) ); 
        if ( ! grp ) {
            grp = initGrp( type ); 
            m_groupMap[ objTypeToString( type ) ] = grp;
        }
        return grp; 
    }

    Grp* getGrpByName( std::string name ) {
        if ( m_groupMap.find( name ) == m_groupMap.end() ) {
            return NULL;
        }
        return m_groupMap[name];
    }

    Grp* groupCreate( std::string name );
    int groupDestroy( Grp* grp );

	Config* config() { return m_config; }

  private:
	
    void initPlugins( Config& );
	void finiPlugins( );
    void initDevices( Config& );
	void finiDevices( );
    
    Grp* initGrp( PWR_ObjType type );
	
    std::string 	m_configFile;
    ObjTreeNode*    m_top;
	Config*			m_config;

    std::map<std::string,TreeNode*>	m_objTreeNodeMap;
	std::deque< TreeNode* >			m_devTreeNodes;

    struct DevMapEntry {
        pwr_dev_t dev;
        std::string pluginName;         
    };

    std::map< std::string, plugin_dev_t* >  m_pluginLibMap;
    std::map< std::string, DevMapEntry >    m_devMap;
    std::map< std::string, Grp* > 			m_groupMap;

};

}

#endif
