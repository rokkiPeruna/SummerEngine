#ifndef SUMMER_ENGINE_JSONFILESSTRUCTURES_H
#define SUMMER_ENGINE_JSONFILESSTRUCTURES_H

#include <string>

namespace se
{
namespace priv
{
struct file_and_folder_data
{
	const std::string scene_folder_name{ "scenes/" };					///Name of the folder containing scene files
	const std::string scene_file_suffix{ ".json" };						///Suffix of the scene file
	const std::string scene_names_file_name{ "scenenamelist.json" };	///Name of the file containing 
	const std::string entity_tmpl_fold_name{ "entity_templates/" };		///Name of the folder containing entity template files

};

struct scene_file_structure
{
	const std::string prim_obj_name{ "entities" };
	const std::string tiles_obj_name{ "tiles" };
	const std::string info_obj_name{ "scene_info" };

	/*
	for example, scene file should look something like this:
	{
		"entities": {
			"player": {
				"some_component": {
					"some_value": 50.0
				}
			"enemy": {
				"some_component": {
					"some_value": 25.0
					}
				}
			}
		},
		"tiles": {
			"sheet_name" : "some_sheet.png",
			"tiles" : {
				
			}
		},
		"scene_info": {
		"heigth": 24,
		"width": 24
		"name": "level_1",
		"type": 2,
		}
	}
	*/
};

struct tiles_obj_structure
{
	const std::string sheet_obj_name{ "sheet_name" };
	const std::string tile_width_obj_name{ "tile_width" };
	const std::string tile_heigth_obj_name{ "tile_heigth" };
	const std::string tile_array_obj_name{ "tilearr" };

	/*
	for example, tiles obj should look something like this:
	"tiles" : {
	"sheet_name" : "some_sheet",
	"tile_width" : 32,
	"tile_heigth : 32,
	"tilearr" : [
		5,
		6,
		0,		//Zero means empty tile
		9,
		11,
		...
		]
	}
	*/
};

struct scene_names_file_structure
{
	const std::string scenenamelist_obj_name = "scenenamelist";
	/*
	for example, scene names file should look something like this:
	{
		"scenenamelist": [
			"level_1",
			"level_2"
		]
	}
	*/
};

}//namespace priv	
}//namespace se

struct entity_obj_structure
{
	const std::string id_obj_name{ "_id" };
};

struct component_obj_structure
{
	const std::string type_obj_name{ "_type" };
	const std::string ownerID_obj_name{ "_ownerID" };
	/*
	for example, component object should look something like this:
	
	"collidable": {
		"_ownerID" : 4,
		"_type" : 2,
		"comp_specific_data" : 50.0,
		"other_specific_data" : 50.0
	}
	*/
};

#endif

 //, m_scenes_subfolder_name("scenes/")
 //, m_ent_templ_fold_name("entity_templates/")
 //, m_scene_file_suffix(".json")
 //, m_main_json_obj("entities")